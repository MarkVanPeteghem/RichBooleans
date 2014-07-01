//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "richbool/functors.hpp"
#include "richbool/bit_iterator.hpp"
#include "richbool/fileutils.hpp"

#ifndef RICHBOOL_USE_WX
    #include <iomanip>
#endif

#if !defined(RICHBOOL_WIN)
#include <pwd.h>
#include <grp.h>
#else
#include <io.h>
#include <sys/types.h>
#endif

#include <stdio.h>

#include <errno.h>
#include <algorithm>

#if !defined(RICHBOOL_WIN)
namespace
{
	const uid_t RootUid = 0;
}
#endif

namespace RichBool
{
	RICHBOOL_DLL_API TmpBool OrBothEvaluated(const TmpBool &bool1, const TmpBool &bool2, int level)
	{
		switch (level)
		{
		case 0:
		default:
			return TmpBool(true);
		case 1:
			return TmpBool(bool1() || bool2());
		case 2:
			if (bool1() || bool2())
				return TmpBool(true);
			// intended fallthrough
		case 3:
			return TmpBool(new OrAnalysis(bool1, bool2));
		}
	}

	RICHBOOL_DLL_API TmpBool AndBothEvaluated(const TmpBool &bool1, const TmpBool &bool2,
		int level)
	{
		switch (level)
		{
		case 0:
		default:
			return TmpBool(true);
		case 1:
			return TmpBool(bool1() && bool2());
		case 2:
			if (bool1() && bool2())
				return TmpBool(true);
			// intended fallthrough
		case 3:
			return TmpBool(new AndAnalysis(bool1, bool2));
		}
	}

	RICHBOOL_DLL_API TmpBool XorBothEvaluated(const TmpBool &bool1, const TmpBool &bool2,
		bool analyseOnSucceed)
	{
		if (XorBool(bool1(), bool2()) && !analyseOnSucceed)
			return TmpBool(true);
		else
			return TmpBool(new XorAnalysis(bool1, bool2));
	}

	detail::String binary(unsigned char byte)
	{
		detail::String str;
		str += (byte & 0x80) ? '1' : '0';
		str += (byte & 0x40) ? '1' : '0';
		str += (byte & 0x20) ? '1' : '0';
		str += (byte & 0x10) ? '1' : '0';
		str += (byte & 0x08) ? '1' : '0';
		str += (byte & 0x04) ? '1' : '0';
		str += (byte & 0x02) ? '1' : '0';
		str += (byte & 0x01) ? '1' : '0';
		return str;
	}

	template<typename CompareBits>
	void GetBitAnalysis(
		const unsigned char *bits1,
		const unsigned char *bits2,
		size_t len,
		CompareBits compareBits,
		BriefAnalysisOfTwoSequences* analysis)
	{
		detail::String str1, str2, diff;
		for (size_t i=0; i<len; ++i, ++bits1, ++bits2)
		{
			str1 += binary(*bits1);
			str2 += binary(*bits2);

// macro to simplify workaround for warning on level 4 with MSVC 6.0:
#define BW_AND(a, b) ((unsigned char)((a)&(b)))
			diff += compareBits(BW_AND(*bits1, 0x80), BW_AND(*bits2, 0x80)) ? ' ' : 'X';
			diff += compareBits(BW_AND(*bits1, 0x40), BW_AND(*bits2, 0x40)) ? ' ' : 'X';
			diff += compareBits(BW_AND(*bits1, 0x20), BW_AND(*bits2, 0x20)) ? ' ' : 'X';
			diff += compareBits(BW_AND(*bits1, 0x10), BW_AND(*bits2, 0x10)) ? ' ' : 'X';
			diff += compareBits(BW_AND(*bits1, 0x08), BW_AND(*bits2, 0x08)) ? ' ' : 'X';
			diff += compareBits(BW_AND(*bits1, 0x04), BW_AND(*bits2, 0x04)) ? ' ' : 'X';
			diff += compareBits(BW_AND(*bits1, 0x02), BW_AND(*bits2, 0x02)) ? ' ' : 'X';
			diff += compareBits(BW_AND(*bits1, 0x01), BW_AND(*bits2, 0x01)) ? ' ' : 'X';
#undef BW_AND
		}
		analysis->SetString1(str1);
		analysis->SetString2(str2);
		analysis->SetStringDiff(diff);
		analysis->SetBlockSize(8);
		analysis->SetBlocksPerLine(8);
	}

	bool BitOn(unsigned char bits, unsigned char mask)
	{
		return (bits&mask)==mask;
	}

	Analysis* BitsOnCore::Analyse(const unsigned char *bits, SharedExpression expr1,
			const unsigned char *mask, SharedExpression expr2,
			size_t len, bool ok) const
	{
		BriefAnalysisOfTwoSequences *analysis =
			new BriefAnalysisOfTwoSequences(ok, expr1, expr2,
			"", " has bits ", " on");
		GetBitAnalysis(bits, mask, len, BitOn,
			analysis);
		analysis->SetTitle1("bits");
		analysis->SetTitle2("mask");
		analysis->SetTitleDiff("err ");
		return analysis;
	}

	static bool IsBitSpecifier(char ch)
	{
		return ch=='0' || ch=='1' || ch=='#';
	}

	static bool IsBitIgnorer(char ch)
	{
		return ch=='#';
	}

    static bool IsBitSeparator(char ch)
    {
        return ch==' ' || ch=='.' || ch==',' || ch==':' || ch=='-';
    }

	BitsAreCore::BitCompareResult BitsAreCore::Match(const void *bits, int nrBytes, const detail::String &mask) const
	{
		BitIterator it(bits, nrBytes);
		detail::String::const_iterator maskIt = mask.begin();
		for (int bit=0; bit<nrBytes*8; ++bit, ++it, ++maskIt)
		{
		    // skip separators
			while (maskIt!=mask.end() && IsBitSeparator(*maskIt))
				++maskIt;

			if (maskIt==mask.end())
				return MaskTooShort;

			if (IsBitIgnorer(*maskIt))
				continue;

            if (IsBitSpecifier(*maskIt))
            {
                bool bitShouldBeOn = *maskIt == '1';
                bool bitIsOn = *it;
                if (bitShouldBeOn != bitIsOn)
                    return Mismatch;
            }
            else
            {
                return IllegalCharacter;
            }
		}

		while (maskIt!=mask.end())
		{
			if (IsBitSpecifier(*maskIt))
			{
				return MaskTooLong;
			}
			++maskIt;
		}

        return Ok;
	}

	Analysis* BitsAreCore::Analyse(const unsigned char *bits, SharedExpression expr1,
			const detail::String &mask, SharedExpression expr2,
			size_t nrBytes, bool ok) const
	{
		BriefAnalysisOfTwoSequences *analysis =
			new BriefAnalysisOfTwoSequences(ok, expr1, expr2,
			"bits of ", " are ", "");
		analysis->SetTitle1("bits");
		analysis->SetTitle2("mask");
		analysis->SetTitleDiff("err ");

		detail::String strBits, diff;
		char illegalChar = ' ';

		BitIterator it(bits, nrBytes);
		detail::String::const_iterator maskIt = mask.begin();
		for (int bit=0; bit<nrBytes*8; ++bit, ++it, ++maskIt)
		{
			while (maskIt!=mask.end() && IsBitSeparator(*maskIt))
			{
				++maskIt;
				strBits += ' ';
				diff += ' ';
			}
			if (maskIt==mask.end())
			{
				analysis->SetEpilogue("not sufficient bits in mask");
				break;
			}
			bool bitIsOn = *it;
			strBits += bitIsOn ? '1' : '0';

			if (IsBitIgnorer(*maskIt))
			{
				diff += ' ';
			}
			else if (IsBitSpecifier(*maskIt))
			{
				bool bitShouldBeOn = *maskIt == '1';
				diff += bitShouldBeOn == bitIsOn ? ' ' : 'X';
			}
			else
			{
			    diff += 'E';
			    illegalChar = *maskIt;
			}
		}
		if (illegalChar!=' ')
		{
            analysis->SetEpilogue(detail::String("illegal character `")+illegalChar+"' in mask");
		}
		else
		{
		    while (maskIt!=mask.end())
            {
                if (IsBitSpecifier(*maskIt))
                {
                    analysis->SetEpilogue("too many bits in mask");
                    break;
                }
                ++maskIt;
            }
		}

		analysis->SetString1(strBits);
		analysis->SetString2(mask);
		analysis->SetStringDiff(diff);
		analysis->SetBlockSize(1000);
		analysis->SetBlocksPerLine(1000);

		return analysis;
	}

	bool BitOff(unsigned char bits, unsigned char mask)
	{
		return (bits&mask)==0;
	}

	Analysis* BitsOffCore::Analyse_(
		const unsigned char *bits, const detail::String &, SharedExpression expr1,
		const unsigned char *mask, const detail::String &, SharedExpression expr2,
		size_t len, bool ok) const
	{
		BriefAnalysisOfTwoSequences *analysis =
			new BriefAnalysisOfTwoSequences(ok, expr1, expr2,
			"", " has bits ", " off");
		GetBitAnalysis(bits, mask, len, BitOff, analysis);
		analysis->SetTitle1("bits");
		analysis->SetTitle2("mask");
		analysis->SetTitleDiff("err ");
		return analysis;
	}

	bool EqualBit(unsigned char bits, unsigned char mask)
	{
		return bits==mask;
	}

	Analysis* EqualBitwiseCore::Analyse(const unsigned char *bits1,
		const unsigned char *bits2,
		size_t len,
		const detail::String &, const detail::String &,
		SharedExpression expr1, SharedExpression expr2, bool ok) const
	{
		BriefAnalysisOfTwoSequences *analysis =
			new BriefAnalysisOfTwoSequences(ok, expr1, expr2,
			"", " .==. ", "");
		analysis->SetState(ok ? Analysis::Ok : Analysis::NotOk);
		GetBitAnalysis(bits1, bits2, len, EqualBit, analysis);
		return analysis;
	}

	detail::String ByteToHex(unsigned char n)
	{
#ifdef RICHBOOL_USE_WX
			wxString str;
			str.Printf("%02x", (unsigned int)n);
			return str;
#else
			std::ostringstream strstr;
			strstr.width(2);
			strstr << std::hex << std::setfill('0') << (int)n;
			return strstr.str();
#endif
	}

	BriefAnalysisOfTwoSequences* EqualDataCore::AnalyseBytes(const unsigned char *buf1, const detail::String &, SharedExpression expr1,
			const unsigned char *buf2, const detail::String &, SharedExpression expr2,
			const size_t nrBytes, const detail::String &, SharedExpression expr3,
			bool ok) const
	{
		BriefAnalysisOfTwoSequences *ba = new BriefAnalysisOfTwoSequences(
			ok,
			expr1, expr2, expr3,
			"", " == ", " (", " bytes)");

		ba->SetBlockSize(2);
		ba->SetBlocksPerLine(16);

		detail::String str1, str2, strDiff;
		for (size_t pos=0; pos<nrBytes; ++pos)
		{
			str1 += ByteToHex(buf1[pos]);
			str2 += ByteToHex(buf2[pos]);
			strDiff += (buf1[pos]==buf2[pos]) ? "  " : "XX";
		}

		ba->SetString1(str1);
		ba->SetString2(str2);
		ba->SetStringDiff(strDiff);

		return ba;
	}

	Analysis* EqualDataBitwiseCore::AnalyseBytes(const unsigned char *buf1, SharedExpression expr1,
			const unsigned char *buf2, SharedExpression expr2,
			const size_t nrBytes, const detail::String &, SharedExpression expr3,
			bool ok) const
	{
		BriefAnalysisOfTwoSequences *ba = new BriefAnalysisOfTwoSequences(
			ok,
			expr1, expr2, expr3,
			"", " .==. ", " (", " bytes)");

		GetBitAnalysis(buf1, buf2, nrBytes, EqualBit, ba);

		return ba;
	}








#if defined(RICHBOOL_WIN)

#if defined(__CYGWIN__)
#define RICHBOOL_FLAG(flag) S_##flag
#define RICHBOOL_ACCESS access
#else
#define RICHBOOL_FLAG(flag) _S_##flag
#define RICHBOOL_ACCESS _access
#endif

	bool IsReadableCore::operator()(const char *, const struct RICHBOOL_STAT &fs) const
	{
		return (fs.st_mode&RICHBOOL_FLAG(IREAD))!=0;
	}

	bool IsWritableCore::operator()(const char *, const struct RICHBOOL_STAT &fs) const
	{
		return (fs.st_mode&RICHBOOL_FLAG(IWRITE))!=0;
	}

	bool IsExecutableCore::operator()(const char *, const struct RICHBOOL_STAT &fs) const
	{
		return (fs.st_mode&RICHBOOL_FLAG(IEXEC))!=0;
	}

#if defined(RICHBOOL_WIN)
	bool IsReadableCore::operator()(const wchar_t *, const struct RICHBOOL_STAT &fs) const
	{
		return (fs.st_mode&RICHBOOL_FLAG(IREAD))!=0;
	}

	bool IsWritableCore::operator()(const wchar_t *, const struct RICHBOOL_STAT &fs) const
	{
		return (fs.st_mode&RICHBOOL_FLAG(IWRITE))!=0;
	}

	bool IsExecutableCore::operator()(const wchar_t *, const struct RICHBOOL_STAT &fs) const
	{
		return (fs.st_mode&RICHBOOL_FLAG(IEXEC))!=0;
	}
#endif

	detail::String ToString(const struct RICHBOOL_STAT &fs)
	{
		detail::String str;
		if (!(fs.st_mode&RICHBOOL_FLAG(IREAD)))
			str += "not ";
		str += "readable, ";
		if (!(fs.st_mode&RICHBOOL_FLAG(IWRITE)))
			str += "not ";
		str += "writable, ";
		if (!(fs.st_mode&RICHBOOL_FLAG(IEXEC)))
			str += "not ";
		str += "executable";

		return str;
	}

#else // #if !defined(RICHBOOL_WIN)

#define RICHBOOL_ACCESS access
#define RICHBOOL_FLAG(flag) S_##flag

	namespace
	{
		bool fsuid_set=false, fsgid_set=false;
		uid_t fsuid=0, fsgid=0;

		uid_t GetEUid()
		{
			return fsuid_set ? fsuid : geteuid();
		}
		uid_t GetEGid()
		{
			return fsgid_set ? fsgid : getegid();
		}
	}
	void SetFsUid(uid_t fsuid_)
	{
		fsuid = fsuid_;
		fsuid_set = true;
	}
	void SetFsGid(uid_t fsgid_)
	{
		fsgid = fsgid_;
		fsgid_set = true;
	}

#ifdef RICHBOOL_USE_WX
WX_DEFINE_ARRAY_INT(gid_t, gid_t_array);
#endif

	static bool haveGroup(gid_t grp)
	{
		if (grp==GetEGid())
			return true;

		int nrGroups = getgroups(0, 0);
#ifdef RICHBOOL_USE_WX
		gid_t_array groups;
		groups.SetCount(nrGroups, 0);
		getgroups(nrGroups, &groups[0]);
		return groups.Index(grp)!=wxNOT_FOUND;
#else
		std::vector<gid_t> groups(nrGroups);
		getgroups(nrGroups, &groups[0]);
		return std::find(groups.begin(), groups.end(), grp)!=groups.end();
#endif
	}

	static bool allowed(const struct stat &st, int userflag, int grpflag, int otherflag)
	{
		if (GetEUid()==RootUid)
		{
			if (S_IXUSR!=userflag)
				return true;

			// root can only execute a file if it is executable for the owner, its group or others:
			return (st.st_mode&userflag)!=0 || (st.st_mode&grpflag)!=0 || (st.st_mode&otherflag)!=0;
		}
		if (st.st_uid==GetEUid())
			return (st.st_mode&userflag)!=0;
		if (haveGroup(st.st_gid))
			return (st.st_mode&grpflag)!=0;
		return (st.st_mode&otherflag)!=0;
	}

	bool IsReadableCore::operator()(const char *name, const struct RICHBOOL_STAT &st) const
	{
		if (name)
			return RICHBOOL_ACCESS(name, R_OK)==0;
		return allowed(st, S_IRUSR, S_IRGRP, S_IROTH);
	}

	bool IsWritableCore::operator()(const char *name, const struct RICHBOOL_STAT &st) const
	{
		if (name)
			return RICHBOOL_ACCESS(name, W_OK)==0;
		return allowed(st, S_IWUSR, S_IWGRP, S_IWOTH);
	}

	bool IsExecutableCore::operator()(const char *name, const struct RICHBOOL_STAT &st) const
	{
		if (name)
			return RICHBOOL_ACCESS(name, X_OK)==0;
		return allowed(st, S_IXUSR, S_IXGRP, S_IXOTH);
	}

#if defined(RICHBOOL_WIN)
	bool IsReadableCore::operator()(const wchar_t *name, const struct RICHBOOL_STAT &st) const
	{
		if (name)
			return _waccess(name, R_OK)==0;
		return allowed(st, S_IRUSR, S_IRGRP, S_IROTH);
	}

	bool IsWritableCore::operator()(const wchar_t *name, const struct RICHBOOL_STAT &st) const
	{
		if (name)
			return _waccess(name, W_OK)==0;
		return allowed(st, S_IWUSR, S_IWGRP, S_IWOTH);
	}

	bool IsExecutableCore::operator()(const wchar_t *name, const struct RICHBOOL_STAT &st) const
	{
		if (name)
			return _waccess(name, X_OK)==0;
		return allowed(st, S_IXUSR, S_IXGRP, S_IXOTH);
	}
#endif

	static char GetFileType(mode_t mode)
	{
		if ((mode&S_IFMT)==S_IFBLK)
			return 'b';
		if ((mode&S_IFMT)==S_IFCHR)
			return 'c';
		if ((mode&S_IFMT)==S_IFIFO)
			return 'p';
		if ((mode&S_IFMT)==S_IFREG)
			return '-';
		if ((mode&S_IFMT)==S_IFDIR)
			return 'd';
		if ((mode&S_IFMT)==S_IFSOCK)
			return 's';
		return '-';
	}

	static detail::String GetUserName(uid_t uid)
	{
		char buffer[200];
		size_t bufsize = sizeof(buffer);

		passwd pwd, *ppwd;
                detail::String str;
		if (getpwuid_r(uid, &pwd, buffer, bufsize, &ppwd))
			str = "???";
		else
			str = pwd.pw_name;
                return str+"("+ToString(uid)+")";
	}

	static detail::String GetGroupName(gid_t gid)
	{
		char buffer[200];
		size_t bufsize = sizeof(buffer);

		group grp, *pgrp;
		detail::String str;
		if (getgrgid_r(gid, &grp, buffer, bufsize, &pgrp))
			str = "???";
		else
			str = grp.gr_name;
		return str+"("+ToString(gid)+")";
	}

	detail::String ToString(const struct RICHBOOL_STAT &st)
	{
		detail::String str;

		str += GetFileType(st.st_mode);
		str += (st.st_mode&S_IRUSR) ? 'r' : '-';
		str += (st.st_mode&S_IWUSR) ? 'w' : '-';
		str += (st.st_mode&S_IXUSR) ? 'x' : '-';
		str += (st.st_mode&S_IRGRP) ? 'r' : '-';
		str += (st.st_mode&S_IWGRP) ? 'w' : '-';
		str += (st.st_mode&S_IXGRP) ? 'x' : '-';
		str += (st.st_mode&S_IROTH) ? 'r' : '-';
		str += (st.st_mode&S_IWOTH) ? 'w' : '-';
		str += (st.st_mode&S_IXOTH) ? 'x' : '-';

		str += ' ';
		str += ToString(st.st_nlink);

		str += ' ';
		str += GetUserName(st.st_uid);
		if (RootUid==GetEUid())
			str += "* ";
		else
			str += (st.st_uid==GetEUid()) ? "+ " : "- ";
		str += GetGroupName(st.st_gid);
		if (RootUid==GetEUid())
			str += "*";
		else
			str += haveGroup(st.st_gid) ? "+" : "-";

		return str;
	}

    detail::String LinkStatus(const char *name)
	{
		struct stat st;
		int result = lstat(name, &st);
		bool isLink = (result==0) && S_ISLNK(st.st_mode);
		return isLink ? "l" : "";
	}

    detail::String LinkStatus(int )
	{
		return "";
	}

	detail::String LinkStatus(FILE* )
	{
		return "";
	}

	detail::String GetUserAndGroup()
	{
		return GetUserName(GetEUid())+" "+GetGroupName(GetEGid());
	}

#endif // #if !defined(RICHBOOL_WIN)

	bool IsRegularCore::operator()(const char *, const struct RICHBOOL_STAT &fs) const
	{
		return (fs.st_mode&RICHBOOL_FLAG(IFMT))==RICHBOOL_FLAG(IFREG);
	}

	bool IsDeviceCore::operator()(const char *, const struct RICHBOOL_STAT &fs) const
	{
		return (fs.st_mode&RICHBOOL_FLAG(IFMT))==RICHBOOL_FLAG(IFCHR);
	}

	bool IsPipeCore::operator()(const char *, const struct RICHBOOL_STAT &fs) const
	{
		return (fs.st_mode&RICHBOOL_FLAG(IFMT))==RICHBOOL_FLAG(IFIFO);
	}

#if defined(RICHBOOL_WIN)
	bool IsRegularCore::operator()(const wchar_t *, const struct RICHBOOL_STAT &fs) const
	{
		return (fs.st_mode&RICHBOOL_FLAG(IFMT))==RICHBOOL_FLAG(IFREG);
	}

	bool IsDeviceCore::operator()(const wchar_t *, const struct RICHBOOL_STAT &fs) const
	{
		return (fs.st_mode&RICHBOOL_FLAG(IFMT))==RICHBOOL_FLAG(IFCHR);
	}

	bool IsPipeCore::operator()(const wchar_t *, const struct RICHBOOL_STAT &fs) const
	{
		return (fs.st_mode&RICHBOOL_FLAG(IFMT))==RICHBOOL_FLAG(IFIFO);
	}
#endif

#if !defined(RICHBOOL_WIN)
	bool IsCharacterSpecialCore::operator()(const char *, const struct RICHBOOL_STAT &fs) const
	{
		return S_ISCHR(fs.st_mode);
	}

	bool IsBlockSpecialCore::operator()(const char *, const struct RICHBOOL_STAT &fs) const
	{
		return S_ISBLK(fs.st_mode);
	}

	bool IsLinkCore::operator()(const char *name, const struct RICHBOOL_STAT &) const
	{
		// stat doesn't tell whether it is a link, so we have to use lstat:
		struct stat st;
		int result = lstat(name, &st);
		return (result==0) && S_ISLNK(st.st_mode);
	}

	bool IsSocketCore::operator()(const char *, const struct RICHBOOL_STAT &fs) const
	{
		return S_ISSOCK(fs.st_mode);
	}
#endif


	namespace detail
	{
        int GetFileNo(FILE *file)
        {
            return
            #if defined(_MSC_VER)
                _fileno(file);
            #else
                fileno(file);
            #endif
        }

		bool Exists(const String &path)
		{
			return RICHBOOL_ACCESS(path.c_str(), 0)==0;
		}

#if defined(RICHBOOL_WIN) && defined(RICHBOOL_HAS_WSTRING) && !defined(__CYGWIN__)
		bool Exists(const std::wstring &path)
		{
			return _waccess(path.c_str(), 0)==0;
		}
#endif

		template<class Str>
		String PathCheck_(const Str &path_org, size_t pathLen)
		{
	        if (Exists(path_org))
               		return ToString(path_org)+" exists";
	        Str path = path_org;
	        size_t pos = ReverseFindNextSeparator(path, pathLen);
			if (errno==EACCES)
			{
		        	while (pos!=path.size())
			        {
        	        		path.resize(pos+1);

			                if (Exists(path))
                		        	return "only "+ToString(path)+" is accessible";
			                pos = ReverseFindNextSeparator(path, pos);
			        }
			        return ToString(path)+" is not accessible";
			}
			else
			{
		        	while (pos!=path.size())
			        {
        	        		path.resize(pos+1);

			                if (Exists(path))
                		        	return "only "+ToString(path)+" exists";
			                pos = ReverseFindNextSeparator(path, pos);
			        }
			        return ToString(path)+" doesn't exist";
			}
		}

		String PathCheck(const String &path)
		{
			return PathCheck_(path, path.size());
		}

#if defined(RICHBOOL_WIN) && !defined(__CYGWIN__)
#ifdef RICHBOOL_HAS_WSTRING
		String PathCheck(const std::wstring &path)
		{
			return PathCheck_(path, path.size());
		}
#endif
		String PathCheck(const wchar_t *path)
		{
			return PathCheck(std::wstring(path));
		}
#endif
	}
}
