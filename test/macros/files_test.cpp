//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com


// disable deprecation warnings in Visual C++ 2005 and higher:
#define _CRT_SECURE_NO_DEPRECATE

#include "richbool/richbool.hpp"
#include "richbool/fileutils.hpp"

#include "rbtest.hpp"

#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fstream>
#include <wchar.h>

#if defined(__GNUC__) && defined(RICHBOOL_WIDE_CHAR_FILENAMES)
#include <direct.h>
#endif

bool IsRoot()
{
#if defined(RICHBOOL_WIN)
	return false;
#else
	return geteuid()==0;
#endif
}

class TmpFile
{
	const char *m_filename;
public:
	TmpFile(const char *filename, const char *content)
		: m_filename(filename)
	{
		FILE *file = fopen(filename, "w");
		fprintf(file, content);
		fclose(file);
	}
	~TmpFile()
	{
#ifdef WIN32
		_unlink(m_filename);
#else
		unlink(m_filename);
#endif
	}
};

#if defined(RICHBOOL_WIDE_CHAR_FILENAMES)
class TmpFileW
{
	const wchar_t *m_filename;
public:
	TmpFileW(const wchar_t *filename, const char *content=0)
		: m_filename(filename)
	{
		if (!content)
			content = "Text";
#if _MSC_VER
		FILE *file = _wfopen(filename, L"w");
		fprintf(file, content);
		fclose(file);
#else
		int file = _wopen(filename, _O_CREAT|_O_WRONLY, _S_IWRITE );
		write(file, content, strlen(content));
		_close(file);
#endif
	}
	~TmpFileW()
	{
		_wunlink(m_filename);
	}
};

#if defined(RICHBOOL_WIDE_CHAR_FILENAMES)
// This is pretty annoying: functions to perform checks on a directory with a
// wide character name are available with MingW, but functions to create and
// remove a directory with a wide character name are not available, so we cannot test this.
// The alternative is to always have directories with wide character names present,
// but certain compression formats mess this up, as well as Linux.
class TmpDirW
{
	const wchar_t *m_dirname;
public:
	TmpDirW(const wchar_t *dirname)
		: m_dirname(dirname)
	{
		_wmkdir(dirname);
	}
	~TmpDirW()
	{
		_wrmdir(m_dirname);
	}
};
#endif
#endif

#if defined(RICHBOOL_WIN) && !defined(__CYGWIN__)
	#include <io.h>

	#define pipe _pipe
	#define open _open
	#define close _close
	#define S_IREAD _S_IREAD
	#define S_IWRITE _S_IWRITE
	#define O_RDONLY _O_RDONLY
	#define O_TEXT _O_TEXT
	#ifndef __GNUC__
		#define S_IRUSR _S_IREAD
		#define S_IWUSR _S_IWRITE
		#define S_IXUSR _S_IXUSR
		#define S_IRWXU _S_IRWXU
	#endif

	#define PATH_SEP "\\"
	#define STR_PATH_SEP "\\\\"
#else
	#include <pwd.h>
	#include <grp.h>
	#define PATH_SEP "/"
	#define STR_PATH_SEP "/"

	RichBool::detail::String plus, minus;
	struct SetPlusAndMinus
	{
		SetPlusAndMinus()
		{
			if (IsRoot())
			{
				plus = "*";
				minus = "*";
			}
			else
			{
				plus = "+";
				minus = "-";
			}
		}
	} setPlusAndMinus;
#endif

#if defined(NDEBUG) && defined(_MSC_VER) && (_MSC_VER <= 1200)
#define MSVC6_RELEASE
#endif

// tests for rbFILE_EXISTS

RB_TEST(FileExists_Pass)
{
	RB_PASS(rbFILE_EXISTS("file-owner-rwx.txt"));
}

RB_TEST(FileExists_Pass_v)
{
	RB_PASS_IV(rbvFILE_EXISTS("file-owner-rwx.txt"));
}

#if defined(RICHBOOL_WIDE_CHAR_FILENAMES)
RB_TEST(FileExists_Pass_W)
{
	TmpFileW tmpFile(L"file-owner-rwx\x0111.txt");

	RB_PASS(rbFILE_EXISTS(L"file-owner-rwx\x0111.txt"));
}
#endif

RB_TEST(FileExists_DoesntExist)
{
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("file ").expr("\"nofile.cpp\"", ":")("nofile.cpp", true)
			(" should exist").ep("nofile.cpp doesn't exist");
	RB_FAIL(rbFILE_EXISTS("nofile.cpp"), *an);
	RB_FAIL_IV(rbvFILE_EXISTS("nofile.cpp"), *an);
}

#if defined(RICHBOOL_WIDE_CHAR_FILENAMES)
RB_TEST(FileExists_DoesntExist_W)
{
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("file ").expr("L\"nofile\\x0111.cpp\"", ":")("nofile\\x0111.cpp", true)
			(" should exist").ep("nofile\\x0111.cpp doesn't exist");
	RB_FAIL(rbFILE_EXISTS(L"nofile\x0111.cpp"), *an);
	RB_FAIL_IV(rbvFILE_EXISTS(L"nofile\x0111.cpp"), *an);
}
#endif

RB_TEST(FileExists_DoesntExistInSubDir)
{
	RichBool::detail::String name = "dir-owner-rwx" PATH_SEP "nofile.cpp";
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("file ").
		expr("name", ":")("dir-owner-rwx" STR_PATH_SEP "nofile.cpp", true)(" should exist")
		.ep("only dir-owner-rwx" STR_PATH_SEP " exists");
	RB_FAIL(rbFILE_EXISTS(name), *an);
}

RB_TEST(FileExists_DoesntExistInNonExistentSubDir)
{
	RichBool::detail::String name = "nodir" PATH_SEP "nofile.cpp";
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("file ").
		expr("name", ":")("nodir" STR_PATH_SEP "nofile.cpp", true)(" should exist")
		.ep("nodir" STR_PATH_SEP " doesn't exist");
	RB_FAIL(rbFILE_EXISTS(name), *an);
}

RB_TEST(FileExists_IsDirectory)
{
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("file ").expr("\"dir-owner-r\"", ":")("dir-owner-r", true)
			(" should exist").ep(" is a directory");
	RB_FAIL(rbFILE_EXISTS("dir-owner-r"), *an);
	RB_FAIL_IV(rbvFILE_EXISTS("dir-owner-r"), *an);
}


// tests for rbFILE

RB_TEST(FileIsReadable)
{
	RB_PASS(rbFILE("file-owner-rwx.txt", RichBool::IsReadable()));
}

#if defined(RICHBOOL_WIDE_CHAR_FILENAMES)
RB_TEST(FileIsReadable_W)
{
	TmpFileW tmpFile(L"file-owner-rwx\x0111.txt");
	RB_PASS(rbFILE(L"file-owner-rwx\x0111.txt", RichBool::IsReadable()));
}
#endif

RB_TEST(FileIsReadable_FileDescriptor)
{
	int fd = open("file-owner-rwx.txt", O_RDONLY, 0);
	RB_PASS(rbFILE(fd, RichBool::IsReadable()));
	close(fd);
}

RB_TEST(FileIsReadable_FileObject)
{
	FILE *file = fopen("file-owner-rwx.txt", "r");
	RB_PASS(rbFILE(file, RichBool::IsReadable()));
	fclose(file);
}

RB_TEST(FileIsReadable_NonExistent)
{
	RichBool::SharedAnalysis core = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotEvaluated)("readable");
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("file ").expr("\"nofile.cpp\"", ":")("nofile.cpp", true)
			(" should be ")(core, true).ep("nofile.cpp doesn't exist");
	RB_FAIL(rbFILE("nofile.cpp", RichBool::IsReadable()), *an);
	RB_FAIL_IV(rbvFILE("nofile.cpp", RichBool::IsReadable()), *an);
}

RB_TEST(FileIsReadable_FILE_NonExistent)
{
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("file ").expr("(FILE*)0", ":")("0x00000000", true)
			(" is NULL");
	RB_FAIL(rbFILE((FILE*)0, RichBool::IsReadable()), *an);
	RB_FAIL_IV(rbvFILE((FILE*)0, RichBool::IsReadable()), *an);
}

RB_TEST(FileIsReadable_Negate_NonExistent)
{
        RichBool::SharedAnalysis core = (RichBool::Analysis*)
	        RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotEvaluated)("readable").neg();
        RichBool::SharedAnalysis an = (RichBool::Analysis*)
                RichBool::MakeGeneralAnalysis(false)("file ").expr("\"nofile.cpp\"", ":")("nofile.cpp", true)
                        (" should be ")(core, true).ep("nofile.cpp doesn't exist");
        RB_FAIL(rbFILE("nofile.cpp", !RichBool::IsReadable()), *an);
        RB_FAIL_IV(rbvFILE("nofile.cpp", !RichBool::IsReadable()), *an);
}

#if !defined(RICHBOOL_WIN)
RB_TEST(FileIsReadable_Negate)
{
	if (!IsRoot())
	{
		RB_PASS(rbFILE("file-owner-n.txt", !RichBool::IsReadable()));
	}
	else
	{
		RB_PASS(rbFILE("file-owner-n.txt", RichBool::IsReadable()));
	}
}

#if defined(RICHBOOL_WIN)
RB_TEST(FileIsReadable_Negate_W)
{
	_chmod("file-owner-n\x0111.txt", 0);
	if (!IsRoot())
	{
		RB_PASS(rbFILE(L"file-owner-n\x0111.txt", !RichBool::IsReadable()));
	}
	else
	{
		RB_PASS(rbFILE(L"file-owner-n\x0111.txt", RichBool::IsReadable()));
	}
}
#endif

#endif


#if defined(RICHBOOL_WIN)

// This test will fail if you run as administrator:
RB_TEST(DirectoryIsReadable_NotAccessible)
{
    RichBool::SharedAnalysis core = (RichBool::Analysis*)
        RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotEvaluated)("readable");
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("directory ")
			.expr("\"C:/Documents and Settings/Administrator/My Documents/\"", ":")
			("C:/Documents and Settings/Administrator/My Documents/", true)(" should be ")(core, true)
#ifdef __CYGWIN__
			.ep("only C:/Documents and Settings/Administrator/ exists"); // to be checked out
#else
			.ep("only C:/Documents and Settings/Administrator/ is accessible");
#endif

	RB_FAIL(rbDIRECTORY("C:/Documents and Settings/Administrator/My Documents/", RichBool::IsReadable()), *an);
}

#endif



RB_TEST(FileIsReadable_IsDirectory)
{
    RichBool::SharedAnalysis core = (RichBool::Analysis*)
        RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotEvaluated)("readable");
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("file ").expr("\"dir-owner-rwx\"", ":")("dir-owner-rwx", true)
			(" should be ")(core, true).ep(" is a directory");
	RB_FAIL(rbFILE("dir-owner-rwx", RichBool::IsReadable()), *an);
}

RB_TEST(FileIsWritable)
{
	RB_PASS(rbFILE("file-owner-rwx.txt", RichBool::IsWritable()));
}

RB_TEST(FileIsWritable_FileDescriptor)
{
	int fd = open("file-owner-rwx.txt", O_RDONLY, 0);
	RB_PASS(rbFILE(fd, RichBool::IsWritable()));
	close(fd);
}

RB_TEST(FileIsWritable_FileObject)
{
	FILE *file = fopen("file-owner-rwx.txt", "r");
	RB_PASS(rbFILE(file, RichBool::IsWritable()));
	fclose(file);
}

#if defined(RICHBOOL_WIN) && defined(__CYGWIN__)
    #define _chmod chmod
#endif

RB_TEST(FileIsWritable_Negate)
{
#if defined(RICHBOOL_WIN)
    _chmod("file-owner-n.txt", 0);
#endif

	if (!IsRoot())
	{
		RB_PASS(rbFILE("file-owner-n.txt", !RichBool::IsWritable()));
	}
	else
	{
		RB_PASS(rbFILE("file-owner-n.txt", RichBool::IsWritable()));
	}
}

RB_TEST(FileIsWritable_NonExistent)
{
	RichBool::SharedAnalysis core = (RichBool::Analysis*)
        RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotEvaluated)("writable");
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("file ").expr("\"nofile.cpp\"", ":")("nofile.cpp", true)
			(" should be ")(core, true).ep("nofile.cpp doesn't exist");
	RB_FAIL(rbFILE("nofile.cpp", RichBool::IsWritable()), *an);
}


#if !defined(RICHBOOL_WIN)

RichBool::detail::String GetUser(uid_t uid)
{
	char buffer[200];
	size_t bufsize = sizeof(buffer);

	passwd pwd, *ppwd;
	RichBool::detail::String str;
	if (getpwuid_r(uid, &pwd, buffer, bufsize, &ppwd))
		str = "???";
	else
		str = pwd.pw_name;
        return str+"("+RichBool::ToString(uid)+")";
}

#if defined(RICHBOOL_WIN)
#define RICHBOOL_STAT _stat
#else
#define RICHBOOL_STAT stat
#endif

RichBool::detail::String GetUser(const char *filename)
{
        struct RICHBOOL_STAT st;
        int result = RICHBOOL_STAT(filename, &st);
	if (result==0)
		return GetUser(st.st_uid);
	else
		return "?";
}

RichBool::detail::String GetUser()
{
	return GetUser(geteuid());
}

static RichBool::detail::String GetGroup(gid_t gid)
{
	char buffer[200];
	size_t bufsize = sizeof(buffer);

	group grp, *pgrp;
	RichBool::detail::String str;
	if (getgrgid_r(gid, &grp, buffer, bufsize, &pgrp))
		str = "???";
	else
		str = grp.gr_name;
	return str+"("+RichBool::ToString(gid)+")";
}

RichBool::detail::String GetGroup(const char *filename)
{
        struct RICHBOOL_STAT st;
        int result = RICHBOOL_STAT(filename, &st);
	if (result==0)
		return GetGroup(st.st_gid);
	else
		return "?";
}

RichBool::detail::String GetGroup()
{
	return GetGroup(getegid());
}

#endif


RB_TEST(FileIsWritable_ReadOnly)
{
#if defined(RICHBOOL_WIN)
	_chmod("file-owner-r.txt", S_IREAD);
#endif

	RichBool::SharedAnalysis core = (RichBool::Analysis*)
        RichBool::MakeGeneralAnalysis(false)("writable");
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
	RichBool::MakeGeneralAnalysis(false)("file ").expr("\"file-owner-r.txt\"", ":")("file-owner-r.txt", true)
		(" should be ").core(core, true)
#if !defined(RICHBOOL_WIN)
		.ep("-r-------- 1 "+GetUser("file-owner-r.txt")+plus+" "+GetGroup("file-owner-r.txt")+plus+"; "
			"process user and group: "+GetUser()+" "+GetGroup())
#else
		.ep("readable, not writable, not executable")
#endif
		;

	if (!IsRoot())
	{
		RB_FAIL(rbFILE("file-owner-r.txt", RichBool::IsWritable()), *an);
	}
	else
	{
		RB_PASS(rbFILE("file-owner-r.txt", RichBool::IsWritable()));
	}
}

RB_TEST(FileIsWritable_ReadOnly_FileDescriptor)
{
#if defined(RICHBOOL_WIN)
	_chmod("file-owner-r.txt", S_IREAD);
#endif

	int fd = open("file-owner-r.txt", O_RDONLY, 0);

	RichBool::SharedAnalysis core = (RichBool::Analysis*)
        RichBool::MakeGeneralAnalysis(false)("writable");
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("file with descriptor ").expr("fd", ":")
		(RichBool::ToString(fd), true)(" should be ").core(core, true)
#if !defined(RICHBOOL_WIN)
             .ep("-r-------- 1 "+GetUser("file-owner-r.txt")+plus+" "+GetGroup("file-owner-r.txt")+plus+"; "
                 "process user and group: "+GetUser()+" "+GetGroup())
#else
		.ep("readable, not writable, not executable")
#endif
		;

	if (!IsRoot())
	{
		RB_FAIL(rbFILE(fd, RichBool::IsWritable()), *an);
	}
	else
	{
		RB_PASS(rbFILE(fd, RichBool::IsWritable()));
	}
	close(fd);
}

RB_TEST(FileIsWritable_ReadOnly_FileObject)
{
#if defined(RICHBOOL_WIN)
	_chmod("file-owner-r.txt", S_IREAD);
#endif

	FILE *file = fopen("file-owner-r.txt", "r");

	RichBool::SharedAnalysis core = (RichBool::Analysis*)
        RichBool::MakeGeneralAnalysis(false)("writable");
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("file ").expr("file", ":")
		(RichBool::ToString(file), true)(" should be ").core(core, true)
#if !defined(RICHBOOL_WIN)
             .ep("-r-------- 1 "+GetUser("file-owner-r.txt")+plus+" "+GetGroup("file-owner-r.txt")+plus+"; "
                 "process user and group: "+GetUser()+" "+GetGroup())
#else
		.ep("readable, not writable, not executable")
#endif
		;

	if (!IsRoot())
	{
		RB_FAIL(rbFILE(file, RichBool::IsWritable()), *an);
	}
	else
	{
		RB_PASS(rbFILE(file, RichBool::IsWritable()));
	}
	fclose(file);
}

RB_TEST(FileIsWritable_ReadOnly_Negate)
{
    chmod("file-owner-rw.txt", S_IREAD|S_IWRITE);

	RichBool::SharedAnalysis core = (RichBool::Analysis*)
        RichBool::MakeGeneralAnalysis(true)("writable").neg();
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("file ").expr("\"file-owner-rw.txt\"", ":")("file-owner-rw.txt", true)
			(" should be ").core(core, true)
#if !defined(RICHBOOL_WIN)
                .ep("-rw------- 1 "+GetUser("file-owner-rw.txt")+plus+" "+GetGroup("file-owner-rw.txt")+plus+"; "
                        "process user and group: "+GetUser()+" "+GetGroup())
#else
		.ep("readable, writable, not executable")
#endif
		;

	RB_FAIL(rbFILE("file-owner-rw.txt", !RichBool::IsWritable()), *an);
}

RB_TEST(FileIsExecutable)
{
	RB_PASS(rbFILE("test.bat", RichBool::IsExecutable()));
}

RB_TEST(FileIsExecutable_FileDescriptor)
{
#if !defined(RICHBOOL_WIN) || defined(__CYGWIN__)
	int fd = open("test.bat", O_RDONLY, 0);
	RB_PASS(rbFILE(fd, RichBool::IsExecutable()));
	close(fd);
#else
	// executable files are not recognized as executable by their file handles:
	int fd = open("test.bat", O_RDONLY, 0);
	RB_PASS(rbFILE(fd, !RichBool::IsExecutable()));
	close(fd);
#endif
}

RB_TEST(FileIsExecutable_FileObject)
{
#if !defined(RICHBOOL_WIN) || defined(__CYGWIN__)
	FILE *file = fopen("test.bat", "r");
	RB_PASS(rbFILE(file, RichBool::IsExecutable()));
	fclose(file);
#else
	// executable files are not recognized as executable by their file handles:
	FILE *file = fopen("test.bat", "r");
	RB_PASS(rbFILE(file, !RichBool::IsExecutable()));
	fclose(file);
#endif
}

RB_TEST(FileIsExecutable_Negate)
{
	RB_PASS(rbFILE("file-owner-r.txt", !RichBool::IsExecutable()));
}

RB_TEST(FileIsExecutable_NonExistent)
{
	RichBool::SharedAnalysis core = (RichBool::Analysis*)
        RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotEvaluated)("executable");
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("file ").expr("\"nofile.cpp\"", ":")("nofile.cpp", true)
			(" should be ")(core, true).ep("nofile.cpp doesn't exist");
	RB_FAIL(rbFILE("nofile.cpp", RichBool::IsExecutable()), *an);
}

RB_TEST(FileIsExecutable_NotExecutable)
{
	RichBool::SharedAnalysis core = (RichBool::Analysis*)
        RichBool::MakeGeneralAnalysis(false)("executable");
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("file ").expr("\"file-owner-r.txt\"", ":")("file-owner-r.txt", true)
			(" should be ").core(core, true)
#if !defined(RICHBOOL_WIN)
                .ep("-r-------- 1 "+GetUser("file-owner-r.txt")+plus+" "+GetGroup("file-owner-r.txt")+plus+"; "
                        "process user and group: "+GetUser()+" "+GetGroup())
#else
		.ep("readable, not writable, not executable")
#endif
		;

	RB_FAIL(rbFILE("file-owner-r.txt", RichBool::IsExecutable()), *an);
}

RB_TEST(FileIsExecutable_ReadOnly_FileDescriptor)
{
	int fd = open("file-owner-r.txt", O_RDONLY, 0);

	RichBool::SharedAnalysis core = (RichBool::Analysis*)
        RichBool::MakeGeneralAnalysis(false)("executable");
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("file with descriptor ").expr("fd", ":")
			(RichBool::ToString(fd), true)(" should be ").core(core, true)
#if !defined(RICHBOOL_WIN)
                .ep("-r-------- 1 "+GetUser("file-owner-r.txt")+plus+" "+GetGroup("file-owner-r.txt")+plus+"; "
                        "process user and group: "+GetUser()+" "+GetGroup())
#else
		.ep("readable, not writable, not executable")
#endif
		;

	RB_FAIL(rbFILE(fd, RichBool::IsExecutable()), *an);
	close(fd);
}

RB_TEST(FileIsExecutable_NotSo_Negate)
{
	RichBool::SharedAnalysis core = (RichBool::Analysis*)
        RichBool::MakeGeneralAnalysis(true)("executable").neg();
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("file ").expr("\"test.bat\"", ":")("test.bat", true)
			(" should be ").core(core, true)
#if !defined(RICHBOOL_WIN)
                .ep("-rwx------ 1 "+GetUser("test.bat")+plus+" "+GetGroup("test.bat")+plus+"; "
                        "process user and group: "+GetUser()+" "+GetGroup())
#else
		.ep("readable, writable, executable")
#endif
		;

	RB_FAIL(rbFILE("test.bat", !RichBool::IsExecutable()), *an);
}

RB_TEST(FileIsNotPipe_Negate_FileDescriptor)
{
	int fd = open("file-owner-rwx.txt", O_RDONLY, 0);
	RB_PASS(rbFILE(fd, !RichBool::IsPipe()));
	close(fd);
}

RB_TEST(FileIsPipe_FileDescriptor)
{
	int fd[2];
#if defined(RICHBOOL_WIN) && !defined(__CYGWIN__)
	pipe(fd, 10, O_TEXT);
#else
	pipe(fd);
#endif
	RB_PASS(rbFILE(fd[0], RichBool::IsPipe()));
	close(fd[0]);
	close(fd[1]);
}

RB_TEST(FileIsPipe_Fail)
{
	RichBool::SharedAnalysis core = (RichBool::Analysis*)
        RichBool::MakeGeneralAnalysis(false)("pipe");
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("file ").expr("\"file-owner-rwx.txt\"", ":")("file-owner-rwx.txt", true)
			(" should be ").core(core, true)
#if !defined(RICHBOOL_WIN)
                .ep("-rwx------ 1 "+GetUser("file-owner-rwx.txt")+plus+" "+GetGroup("file-owner-rwx.txt")+plus+"; "
                        "process user and group: "+GetUser()+" "+GetGroup())
#elif defined(__CYGWIN__)
		.ep("readable, writable, executable")
#else
		.ep("readable, writable, not executable")
#endif
		;

	RB_FAIL(rbFILE("file-owner-rwx.txt", RichBool::IsPipe()), *an);
}

RB_TEST(FileIsReadableAndWritable)
{
	RB_PASS(rbFILE("file-owner-rwx.txt", RichBool::IsReadable()&&RichBool::IsWritable()));
}

RB_TEST(FileIsReadableAndWritable_NonExistent)
{
	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotEvaluated)("readable"),
		*an2 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotEvaluated)("writable");
	RichBool::SharedAnalysis core = new RichBool::AndAnalysis(an1, an2);

	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("file ").expr("\"nofile.cpp\"", ":")("nofile.cpp", true)
			(" should be ")(core, true).ep("nofile.cpp doesn't exist");
	RB_FAIL(rbFILE("nofile.cpp", RichBool::IsReadable()&RichBool::IsWritable()), *an);
}

RB_TEST(FileIsReadableAndWritable_ReadOnly)
{
#if defined(RICHBOOL_WIN)
	_chmod("file-owner-r.txt", S_IREAD);
#endif

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(true)("readable"),
		*an2 = RichBool::MakeGeneralAnalysis(false)("writable");
	RichBool::SharedAnalysis core = new RichBool::AndAnalysis(an1, an2);

	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("file ").expr("\"file-owner-r.txt\"", ":")("file-owner-r.txt", true)
			(" should be ").core(core, true)
#if !defined(RICHBOOL_WIN)
                .ep("-r-------- 1 "+GetUser("file-owner-r.txt")+plus+" "+GetGroup("file-owner-r.txt")+plus+"; "
                        "process user and group: "+GetUser()+" "+GetGroup())
#else
		.ep("readable, not writable, not executable")
#endif
		;

	if (!IsRoot())
	{
		RB_FAIL(rbFILE("file-owner-r.txt", RichBool::IsReadable()&RichBool::IsWritable()), *an);
	}
	else
	{
		RB_PASS(rbFILE("file-owner-r.txt", RichBool::IsReadable()&RichBool::IsWritable()));
	}
}

#if !defined(RICHBOOL_WIN)

RB_TEST(File_IsRegular_Pass)
{
        RB_PASS(rbFILE("file-owner-rwx.txt", RichBool::IsRegular()));
}

RB_TEST(FileIsRegular_Fail)
{
        RichBool::SharedAnalysis core = (RichBool::Analysis*)
        RichBool::MakeGeneralAnalysis(false)("regular");
        RichBool::SharedAnalysis an = (RichBool::Analysis*)
                RichBool::MakeGeneralAnalysis(false)("file ").expr("\"/dev/sda\"", ":")("/dev/sda", true)
                        (" should be ").core(core, true)
                .ep("brw-rw---- 1 root(0)"+minus+" disk(6)"+minus+"; "
                        "process user and group: "+GetUser()+" "+GetGroup())
		;

        RB_FAIL(rbFILE("/dev/sda", RichBool::IsRegular()), *an);
}

RB_TEST(File_IsCharacterSpecial_Pass)
{
        RB_PASS(rbFILE("/dev/null", RichBool::IsCharacterSpecial()));
}

RB_TEST(FileIsCharacterSpecial_Fail)
{
        RichBool::SharedAnalysis core = (RichBool::Analysis*)
        RichBool::MakeGeneralAnalysis(false)("character special");
        RichBool::SharedAnalysis an = (RichBool::Analysis*)
                RichBool::MakeGeneralAnalysis(false)("file ").expr("\"file-owner-rwx.txt\"", ":")("file-owner-rwx.txt", true)
                        (" should be ").core(core, true)
                .ep("-rwx------ 1 "+GetUser("file-owner-rwx.txt")+plus+" "+GetGroup("file-owner-rwx.txt")+plus+"; "
                        "process user and group: "+GetUser()+" "+GetGroup())
		;

        RB_FAIL(rbFILE("file-owner-rwx.txt", RichBool::IsCharacterSpecial()), *an);
}

RB_TEST(File_IsBlockSpecial_Pass)
{
	struct stat st;
	stat("/dev/sda", &st);
	int mode = st.st_mode;
        RB_PASS(rbFILE("/dev/sda", RichBool::IsBlockSpecial()));
}

RB_TEST(FileIsBlockSpecial_Fail)
{
        RichBool::SharedAnalysis core = (RichBool::Analysis*)
        RichBool::MakeGeneralAnalysis(false)("block special");
        RichBool::SharedAnalysis an = (RichBool::Analysis*)
                RichBool::MakeGeneralAnalysis(false)("file ").expr("\"file-owner-rwx.txt\"", ":")("file-owner-rwx.txt", true)
                        (" should be ").core(core, true)
                .ep("-rwx------ 1 "+GetUser("file-owner-rwx.txt")+plus+" "+GetGroup("file-owner-rwx.txt")+plus+"; "
                        "process user and group: "+GetUser()+" "+GetGroup())
		;

        RB_FAIL(rbFILE("file-owner-rwx.txt", RichBool::IsBlockSpecial()), *an);
}


RB_TEST(FileOfOwnerIsReadable)
{
	RB_PASS(rbFILE("file-owner-rwx.txt", RichBool::IsReadable()));
}

RB_TEST(FileOfOwnerIsNotReadable)
{
	if (!IsRoot())
	{
		RB_PASS(rbFILE("file-owner-n.txt", !RichBool::IsReadable()));
	}
	else
	{
		RB_PASS(rbFILE("file-owner-n.txt", RichBool::IsReadable()));
	}
}

RB_TEST(FileOfGroupIsReadable)
{
	RB_PASS(rbFILE("file-group-rwx.txt", RichBool::IsReadable()));
}

RB_TEST(FileOfGroupIsNotReadable)
{
	if (!IsRoot())
	{
		RB_PASS(rbFILE("file-group-n.txt", !RichBool::IsReadable()));
	}
	else
	{
		RB_PASS(rbFILE("file-group-n.txt", RichBool::IsReadable()));
	}
}

RB_TEST(FileOfOtherIsReadable)
{
	RB_PASS(rbFILE("file-other-rwx.txt", RichBool::IsReadable()));
}

RB_TEST(FileOfOtherIsNotReadable)
{
	if (!IsRoot())
	{
		RB_PASS(rbFILE("file-other-n.txt", !RichBool::IsReadable()));
	}
	else
	{
		RB_PASS(rbFILE("file-other-n.txt", RichBool::IsReadable()));
	}

}

#endif


// tests for rbDIRECTORY_EXISTS

RB_TEST(DirectoryExists)
{
	RB_PASS(rbDIRECTORY_EXISTS("dir-owner-rwx"));
}

RB_TEST(DirectoryExists_v)
{
	RB_PASS_IV(rbvDIRECTORY_EXISTS("dir-owner-rwx"));
}

#if defined(RICHBOOL_WIDE_CHAR_FILENAMES) && !defined(__MINGW32__)
RB_TEST(DirectoryExists_W)
{
	TmpDirW tmpDirW(L"dir-owner-rwx\x0111");
	RB_PASS(rbDIRECTORY_EXISTS(L"dir-owner-rwx\x0111"));
}
#endif

RB_TEST(DirectoryExists_DoesntExist)
{
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("directory ").expr("\"nodir\"", ":")("nodir", true)
			(" should exist").ep("nodir doesn't exist");
	RB_FAIL(rbDIRECTORY_EXISTS("nodir"), *an);
	RB_FAIL_IV(rbvDIRECTORY_EXISTS("nodir"), *an);
}

#if defined(RICHBOOL_WIDE_CHAR_FILENAMES)
RB_TEST(DirectoryExists_DoesntExist_W)
{
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("directory ").expr("L\"nodir\\x0111\"", ":")("nodir\\x0111", true)
			(" should exist").ep("nodir\\x0111 doesn't exist");
	RB_FAIL(rbDIRECTORY_EXISTS(L"nodir\x0111"), *an);
	RB_FAIL_IV(rbvDIRECTORY_EXISTS(L"nodir\x0111"), *an);
}
#endif

RB_TEST(DirectoryExists_IsFile)
{
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("directory ").expr("\"file-owner-rwx.txt\"", ":")("file-owner-rwx.txt", true)
			(" should exist").ep(" is a file");
	RB_FAIL(rbDIRECTORY_EXISTS("file-owner-rwx.txt"), *an);
	RB_FAIL_IV(rbvDIRECTORY_EXISTS("file-owner-rwx.txt"), *an);
}


// tests for rbDIRECTORY

RB_TEST(DirectoryIsReadable)
{
	RB_PASS(rbDIRECTORY("dir-owner-rwx", RichBool::IsReadable()));
}

#if defined(RICHBOOL_WIDE_CHAR_FILENAMES) && !defined(__MINGW32__)
RB_TEST(DirectoryIsReadable_W)
{
	TmpDirW tmpDirW(L"dir-owner-rwx\x0111");
	RB_PASS(rbDIRECTORY(L"dir-owner-rwx\x0111", RichBool::IsReadable()));
}
#endif

RB_TEST(DirectoryIsReadable_NonExistent)
{
	RichBool::Analysis *core = RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotEvaluated)("readable");
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("directory ").expr("\"nodir\"", ":")("nodir", true)
			(" should be ")(core, true).ep("nodir doesn't exist");
	RB_FAIL(rbDIRECTORY("nodir", RichBool::IsReadable()), *an);
	RB_FAIL_IV(rbvDIRECTORY("nodir", RichBool::IsReadable()), *an);
}

#if defined(RICHBOOL_WIDE_CHAR_FILENAMES)
RB_TEST(DirectoryIsReadable_NonExistent_W)
{
	RichBool::Analysis *core = RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotEvaluated)("readable");
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("directory ").expr("L\"nodir\\x0111\"", ":")("nodir\\x0111", true)
			(" should be ")(core, true).ep("nodir\\x0111 doesn't exist");
	RB_FAIL(rbDIRECTORY(L"nodir\x0111", RichBool::IsReadable()), *an);
	RB_FAIL_IV(rbvDIRECTORY(L"nodir\x0111", RichBool::IsReadable()), *an);
}
#endif

RB_TEST(DirectoryIsReadable_IsFile)
{
	RichBool::Analysis *core = RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotEvaluated)("readable");
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("directory ").expr("\"file-owner-rwx.txt\"", ":")("file-owner-rwx.txt", true)
			(" should be ")(core, true).ep(" is a file");
	RB_FAIL(rbDIRECTORY("file-owner-rwx.txt", RichBool::IsReadable()), *an);
}

RB_TEST(DirectoryIsReadable_Negate_NonExistent)
{
	RichBool::Analysis *core = RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotEvaluated)("readable").neg();
    RichBool::SharedAnalysis an = (RichBool::Analysis*)
                RichBool::MakeGeneralAnalysis(false)("directory ").expr("\"nodir\"", ":")("nodir", true)
                        (" should be ")(core, true).ep("nodir doesn't exist");
        RB_FAIL(rbDIRECTORY("nodir", !RichBool::IsReadable()), *an);
        RB_FAIL_IV(rbvDIRECTORY("nodir", !RichBool::IsReadable()), *an);
}

RB_TEST(DirectoryIsReadable_Negate_IsFile)
{
	RichBool::Analysis *core = RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotEvaluated)("readable").neg();
    RichBool::SharedAnalysis an = (RichBool::Analysis*)
                RichBool::MakeGeneralAnalysis(false)("directory ").expr("\"file-owner-rwx.txt\"", ":")("file-owner-rwx.txt", true)
				(" should be ")(core, true).ep(" is a file");
        RB_FAIL(rbDIRECTORY("file-owner-rwx.txt", !RichBool::IsReadable()), *an);
}

RB_TEST(DirectoryIsWritable)
{
	RB_PASS(rbDIRECTORY("dir-owner-rwx", RichBool::IsWritable()));
}

RB_TEST(DirectoryIsWritable_Negate)
{
#if defined(RICHBOOL_WIN)
	_chmod("dir-owner-r", S_IREAD);
#endif

	if (!IsRoot())
	{
		RB_PASS(rbDIRECTORY("dir-owner-r", !RichBool::IsWritable()));
	}
	else
	{
		RB_PASS(rbDIRECTORY("dir-owner-r", RichBool::IsWritable()));
	}
}

RB_TEST(DirectoryIsWritable_NonExistent)
{
	RichBool::Analysis *core = RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotEvaluated)("writable");
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("directory ").expr("\"nodir\"", ":")("nodir", true)
			(" should be ")(core, true).ep("nodir doesn't exist");
	RB_FAIL(rbDIRECTORY("nodir", RichBool::IsWritable()), *an);
}

RB_TEST(DirectoryIsNotWritable_NonExistent)
{
	RichBool::Analysis *core = RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotEvaluated)("writable").neg();
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("directory ").expr("\"nodir\"", ":")("nodir", true)
			(" should be ")(core, true).ep("nodir doesn't exist");
	RB_FAIL(rbDIRECTORY("nodir", !RichBool::IsWritable()), *an);
}

RB_TEST(DirectoryIsWritable_ReadOnly)
{
#if defined(RICHBOOL_WIN)
	_chmod("dir-owner-r", S_IREAD);
#endif

	RichBool::SharedAnalysis core = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("writable");
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("directory ").expr("\"dir-owner-r\"", ":")("dir-owner-r", true)
			(" should be ").core(core, true)
#if !defined(RICHBOOL_WIN)
                .ep("dr-------- 2 "+GetUser("dir-owner-r")+plus+" "+GetGroup("dir-owner-r")+plus+"; "
                        "process user and group: "+GetUser()+" "+GetGroup())
#elif defined(__CYGWIN__)
		.ep("readable, not writable, not executable")
#else
		.ep("readable, not writable, executable")
#endif
		;

	if (!IsRoot())
	{
		RB_FAIL(rbDIRECTORY("dir-owner-r", RichBool::IsWritable()), *an);
	}
	else
	{
		RB_PASS(rbDIRECTORY("dir-owner-r", RichBool::IsWritable()));
	}
}

RB_TEST(DirectoryIsWritable_ReadOnly_Negate)
{
	RichBool::SharedAnalysis core = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(true)("writable").neg();
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)("directory ").expr("\"dir-owner-rwx\"", ":")("dir-owner-rwx", true)
			(" should be ").core(core, true)
#if !defined(RICHBOOL_WIN)
                .ep("drwx------ 4 "+GetUser("dir-owner-rwx")+plus+" "+GetGroup("dir-owner-rwx")+plus+"; "
                        "process user and group: "+GetUser()+" "+GetGroup())
#else
		.ep("readable, writable, executable")
#endif
		;

	RB_FAIL(rbDIRECTORY("dir-owner-rwx", !RichBool::IsWritable()), *an);
}

// tests for rbDOES_NOT_EXIST

RB_TEST(DoesNotExist_Ok)
{
	RB_PASS(rbDOES_NOT_EXIST("nofile.cpp"));
#ifndef MSVC6_RELEASE
	RB_PASS_IV(rbvDOES_NOT_EXIST("nofile.cpp"));
#endif
}

#if defined(RICHBOOL_WIDE_CHAR_FILENAMES)
RB_TEST(DoesNotExist_Ok_W)
{
	RB_PASS(rbDOES_NOT_EXIST(L"nofile\x0111.cpp"));
#ifndef MSVC6_RELEASE
	RB_PASS_IV(rbvDOES_NOT_EXIST(L"nofile\x0111.cpp"));
#endif
}
#endif

RB_TEST(DoesNotExist_Fail_IsFile)
{
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false).expr("\"file-owner-rwx.txt\"", ":")("file-owner-rwx.txt", true)
			(" should not exist").ep(" is a file");
	RB_FAIL(rbDOES_NOT_EXIST("file-owner-rwx.txt"), *an);
#ifndef MSVC6_RELEASE
	RB_FAIL_IV(rbvDOES_NOT_EXIST("file-owner-rwx.txt"), *an);
#endif
}

#if defined(RICHBOOL_WIDE_CHAR_FILENAMES)
RB_TEST(DoesNotExist_Fail_IsFile_W)
{
	TmpFileW tmpFile(L"file-owner-rwx\x0111.txt");

	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false).expr("L\"file-owner-rwx\\x0111.txt\"", ":")("file-owner-rwx\\x0111.txt", true)
			(" should not exist").ep(" is a file");
	RB_FAIL(rbDOES_NOT_EXIST(L"file-owner-rwx\x0111.txt"), *an);
#ifndef MSVC6_RELEASE
	RB_FAIL_IV(rbvDOES_NOT_EXIST(L"file-owner-rwx\x0111.txt"), *an);
#endif
}
#endif

RB_TEST(DoesNotExist_Fail_IsDirectory)
{
	RichBool::SharedAnalysis an = (RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false).expr("\"dir-owner-r\"", ":")("dir-owner-r", true)
			(" should not exist").ep(" is a directory");
	RB_FAIL(rbDOES_NOT_EXIST("dir-owner-r"), *an);
#ifndef MSVC6_RELEASE
	RB_FAIL_IV(rbvDOES_NOT_EXIST("dir-owner-r"), *an);
#endif
}


///////////////////////////////////////////////////////////
// tests for RichBool::detail::PathChecker

namespace RichBool
{
	namespace detail
	{
		String PathCheck(const RichBool::detail::String &path_org);
	}
}

RB_TEST(FindNextSeparator_NoSeparator)
{
	RichBool::detail::String str = "file.cpp";
	RB_ASSERT(rbEQUAL(RichBool::detail::ReverseFindNextSeparator(str, 5), str.size()));
}

RB_TEST(FindNextSeparator_OneSeparator)
{
	RichBool::detail::String str = "dir" PATH_SEP "file.cpp";
	size_t pos = str.size();
	pos = RichBool::detail::ReverseFindNextSeparator(str, pos);
	RB_ASSERT(rbEQUAL(pos, 3u));
	pos = RichBool::detail::ReverseFindNextSeparator(str, pos);
        RB_ASSERT(rbEQUAL(pos, str.size()));
}

RB_TEST(FindNextSeparator_TwoSeparators)
{
        RichBool::detail::String str = "dir" PATH_SEP "dir" PATH_SEP "file.cpp";
	size_t pos = str.size();
	pos = RichBool::detail::ReverseFindNextSeparator(str, pos);
        RB_ASSERT(rbEQUAL(pos, 7u));
	pos = RichBool::detail::ReverseFindNextSeparator(str, pos);
        RB_ASSERT(rbEQUAL(pos, 3u));
	pos = RichBool::detail::ReverseFindNextSeparator(str, pos);
        RB_ASSERT(rbEQUAL(pos, str.size()));
}


RB_TEST(PathChecker_OnlyFile_Exists)
{
	RichBool::detail::String str = RichBool::detail::PathCheck("file-owner-rwx.txt");
	RB_PASS(rbEQUAL(str, "file-owner-rwx.txt exists"));
}

RB_TEST(PathChecker_OnlyFile_DoesntExist)
{
	RichBool::detail::String str = RichBool::detail::PathCheck("no_file.cpp");
	RB_PASS(rbEQUAL(str, "no_file.cpp doesn't exist"));
}

RB_TEST(PathChecker_DirAndFile_Exists)
{
	RichBool::detail::String str = RichBool::detail::PathCheck("dir-owner-rwx" PATH_SEP "dummy.hpp");
	RB_PASS(rbEQUAL(str, "dir-owner-rwx" STR_PATH_SEP "dummy.hpp exists"));
}

RB_TEST(PathChecker_DirAndFile_OnlyDirExists)
{
	RichBool::detail::String str = RichBool::detail::PathCheck("dir-owner-rwx" PATH_SEP "nofile.hpp");
	RB_PASS(rbEQUAL(str, "only dir-owner-rwx" STR_PATH_SEP " exists"));
}

#if !defined(RICHBOOL_WIN)

// These three tests will fail, unless you make root the owner of the directories
// dir-owner-n and dir/dir-owner-n, and make it only accessible to root.
// You can do this with the command `sudo ./dir-owner-n-unlock'.
// You can undo this with the command `sudo ./dir-unroot-unlock <user>'.

RB_TEST(PathChecker_DirAndFile_DirNotAccessible)
{
	if (!IsRoot())
	{
		RichBool::detail::String str = RichBool::detail::PathCheck("dir-owner-n" PATH_SEP "test.txt");
		RB_PASS(rbEQUAL(str, "only dir-owner-n" STR_PATH_SEP " is accessible"));
	}
}

RB_TEST(PathChecker_DirAndFile_DirInDirNotAccessible1)
{
	if (!IsRoot())
	{
		RichBool::detail::String str = RichBool::detail::PathCheck("dir-owner-n" PATH_SEP "dir-owner-r" PATH_SEP "dummy.hpp");
		RB_PASS(rbEQUAL(str, "only dir-owner-n" STR_PATH_SEP " is accessible"));
	}
}

RB_TEST(PathChecker_DirAndFile_DirInDirNotAccessible2)
{
	if (!IsRoot())
	{
		RichBool::detail::String str = RichBool::detail::PathCheck("dir-owner-rwx" PATH_SEP "dir-root" PATH_SEP "dummy.hpp");
		RB_PASS(rbEQUAL(str, "only dir-owner-rwx" STR_PATH_SEP "dir-root" STR_PATH_SEP " is accessible"));
	}
}

#endif

RB_TEST(PathChecker_DirAndFile_NoneExists)
{
	RichBool::detail::String str = RichBool::detail::PathCheck("nodir" PATH_SEP "dummy.hpp");
	RB_PASS(rbEQUAL(str, "nodir" STR_PATH_SEP " doesn't exist"));
}

RB_TEST(PathChecker_TwoDirsAndFile_Exists)
{
	RichBool::detail::String str = RichBool::detail::PathCheck("dir-owner-rwx" PATH_SEP "dir2" PATH_SEP "dummy.hpp");
	RB_PASS(rbEQUAL(str, "dir-owner-rwx" STR_PATH_SEP "dir2" STR_PATH_SEP "dummy.hpp exists"));
}

RB_TEST(PathChecker_TwoDirsAndFile_OnlyTwoDirsExists)
{
	RichBool::detail::String str = RichBool::detail::PathCheck("dir-owner-rwx" PATH_SEP "dir2" PATH_SEP "nofile.hpp");
	RB_PASS(rbEQUAL(str, "only dir-owner-rwx" STR_PATH_SEP "dir2" STR_PATH_SEP " exists"));
}

RB_TEST(PathChecker_TwoDirsAndFile_OneDirExists)
{
	RichBool::detail::String str = RichBool::detail::PathCheck("dir-owner-rwx" PATH_SEP "nodir" PATH_SEP "dummy.hpp");
	RB_PASS(rbEQUAL(str, "only dir-owner-rwx" STR_PATH_SEP " exists"));
}

RB_TEST(PathChecker_TwoDirsAndFile_NoneExists)
{
	RichBool::detail::String str = RichBool::detail::PathCheck("nodir1" PATH_SEP "nodir2" PATH_SEP "dummy.hpp");
	RB_PASS(rbEQUAL(str, "nodir1" STR_PATH_SEP " doesn't exist"));
}

#if defined(RICHBOOL_WIN)

RB_TEST(PathChecker_RootExists)
{
        RichBool::detail::String str = RichBool::detail::PathCheck("c:\\");
        RB_PASS(rbEQUAL(str, "c:\\\\ exists"));
}

RB_TEST(PathChecker_WinDirExists)
{
	// this test will may fail on systems that don't have a directory c:\Windows
        RichBool::detail::String str = RichBool::detail::PathCheck("c:\\Windows");
        RB_PASS(rbEQUAL(str, "c:\\\\Windows exists"));
}

RB_TEST(PathChecker_NonExistent)
{
        RichBool::detail::String str = RichBool::detail::PathCheck("c:\\nodir");
        RB_PASS(rbEQUAL(str, "only c:\\\\ exists"));
}

#else

RB_TEST(PathChecker_RootExists)
{
        RichBool::detail::String str = RichBool::detail::PathCheck("/");
        RB_PASS(rbEQUAL(str, "/ exists"));
}

RB_TEST(PathChecker_UsrExists)
{
        RichBool::detail::String str = RichBool::detail::PathCheck("/usr");
        RB_PASS(rbEQUAL(str, "/usr exists"));
}

RB_TEST(PathChecker_NoDirDoesntExist)
{
        RichBool::detail::String str = RichBool::detail::PathCheck("/nodir");
        RB_PASS(rbEQUAL(str, "only / exists"));
}




// we put these at the end of the file,
// so that they are run first and the link counts will be correct in analyses

RB_TEST(File_IsLink_Pass)
{
	symlink("file-owner-rwx.txt", "link");
	RB_PASS(rbFILE("link", RichBool::IsLink()));
	unlink("link");
}

RB_TEST(FileIsLink_Fail)
{
        RichBool::SharedAnalysis core = (RichBool::Analysis*)
        RichBool::MakeGeneralAnalysis(false)("link");
        RichBool::SharedAnalysis an = (RichBool::Analysis*)
                RichBool::MakeGeneralAnalysis(false)("file ").expr("\"file-owner-rwx.txt\"", ":")("file-owner-rwx.txt", true)
                        (" should be ").core(core, true)
                .ep("-rwx------ 1 "+GetUser("file-owner-rwx.txt")+plus+" "+GetGroup("file-owner-rwx.txt")+plus+"; "
                        "process user and group: "+GetUser()+" "+GetGroup());

        RB_FAIL(rbFILE("file-owner-rwx.txt", RichBool::IsLink()), *an);
	unlink("link");
}

RB_TEST(File_IsNotLink_Pass)
{
        RB_PASS(rbFILE("file-owner-rwx.txt", !RichBool::IsLink()));
}

RB_TEST(FileIsNotLink_Fail)
{
	symlink("file-owner-rwx.txt", "link");

	RichBool::SharedAnalysis core = (RichBool::Analysis*)
        RichBool::MakeGeneralAnalysis(true)("link").neg();
        RichBool::SharedAnalysis an = (RichBool::Analysis*)
                RichBool::MakeGeneralAnalysis(false)("file ").expr("\"link\"", ":"
)("link", true)
                        (" should be ").core(core, true)
                .ep("l-rwx------ 1 "+GetUser("link")+plus+" "+GetGroup("link")+plus+"; "
                        "process user and group: "+GetUser()+" "+GetGroup());

        RB_FAIL(rbFILE("link", !RichBool::IsLink()), *an);
	unlink("link");
}

RB_TEST(Dir_IsLink_Pass)
{
        symlink("dir-owner-rwx", "dirlink");
        RB_PASS(rbDIRECTORY("dirlink", RichBool::IsLink()));
	unlink("dirlink");
}

RB_TEST(DirIsLink_Fail)
{
        RichBool::SharedAnalysis core = (RichBool::Analysis*)
        RichBool::MakeGeneralAnalysis(false)("link");
        RichBool::SharedAnalysis an = (RichBool::Analysis*)
                RichBool::MakeGeneralAnalysis(false)("directory ").expr("\"dir-owner-r\"", ":")("dir-owner-r", true)
                        (" should be ").core(core, true)
                .ep("dr-------- 2 "+GetUser("dir-owner-r")+plus+" "+GetGroup("dir-owner-r")+plus+"; "
                        "process user and group: "+GetUser()+" "+GetGroup());

        RB_FAIL(rbDIRECTORY("dir-owner-r", RichBool::IsLink()), *an);
}

RB_TEST(Dir_IsNotLink_Pass)
{
        RB_PASS(rbDIRECTORY("dir-owner-r", !RichBool::IsLink()));
}

RB_TEST(DirIsNotLink_Fail)
{
        symlink("dir-owner-r", "dirlink");

        RichBool::SharedAnalysis core = (RichBool::Analysis*)
        RichBool::MakeGeneralAnalysis(true)("link").neg();
        RichBool::SharedAnalysis an = (RichBool::Analysis*)
                RichBool::MakeGeneralAnalysis(false)("directory ").expr("\"dirlink\"", ":")("dirlink", true)
                        (" should be ").core(core, true)
                .ep("ldr-------- 2 "+GetUser("dirlink")+plus+" "+GetGroup("dirlink")+plus+"; "
                        "process user and group: "+GetUser()+" "+GetGroup());
	RichBool::LinkStatus("dirlink");
        RB_FAIL(rbDIRECTORY("dirlink", !RichBool::IsLink()), *an);
	unlink("dirlink");
}
#endif

RB_TEST(FileLen_1)
{
	TmpFile tmpFile("filelen_test.txt", "a");
	RB_ASSERT(rbEQUAL(RichBool::GetFileLength("filelen_test.txt"), 1));
}

RB_TEST(FileLen_4)
{
	TmpFile tmpFile("filelen_test.txt", "Text");
	RB_ASSERT(rbEQUAL(RichBool::GetFileLength("filelen_test.txt"), 4));
}

RB_TEST(FileLen_NonExisting)
{
	RB_ASSERT(rbEQUAL(RichBool::GetFileLength("none.txt"), -1));
}

RB_TEST(FileLen_IsDirectory)
{
	RB_ASSERT(rbEQUAL(RichBool::GetFileLength("dir-owner-rwx"), -1));
}

#if defined(RICHBOOL_WIDE_CHAR_FILENAMES)

RB_TEST(FileLenW_1)
{
	TmpFileW tmpFile(L"filelen_test\x0111.txt", "a");
	RB_ASSERT(rbEQUAL(RichBool::GetFileLength(L"filelen_test\x0111.txt"), 1));
}

RB_TEST(FileLenW_4)
{
	TmpFileW tmpFile(L"filelen_test\x0111.txt", "Text");
	RB_ASSERT(rbEQUAL(RichBool::GetFileLength(L"filelen_test\x0111.txt"), 4));
}

RB_TEST(FileLenW_NonExisting)
{
	RB_ASSERT(rbEQUAL(RichBool::GetFileLength(L"none\x0111.txt"), -1));
}

RB_TEST(FileLenW_IsDirectory)
{
	TmpDirW tmpDirW(L"dir\x0111");
	RB_ASSERT(rbEQUAL(RichBool::GetFileLength(L"dir\x0111"), -1));
}

#endif
