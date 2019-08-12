// mfcs_string.h - MFC Stub CString class header

#ifndef __MFCS_STRING_H__
#define __MFCS_STRING_H__

#include "..\mfcstub\mfcs_types.h"

#include <stdarg.h> // for va_list

/* CString wrapper class

	Known differences from MFC implementation:
	- Most of the functions aren't implemented because of non-use
	- UniCode is not used
	- ReleaseBuffer is only necessary if you've changed the length of the string
	- I64's are not supported by FormatV
	- in FormatV, doubles can't take up more than 318 characters in the string (gasp!)
	- The data class is a little different
*/

class CStringData
{
public:
	DWORD m_Length; // Length of the string (not including terminator)
	DWORD m_BufferSize; // Length of the buffer
	LPSTR data() { return (LPSTR)(this + 1); }
};

class CString
{
public:
	CString();
	~CString();
	CString(LPCTSTR pString);
	CString(const CString &cString);

	// Member functions
#if 1
	DWORD GetLength() const {
		if (!GetData()) {
			return 0;
		}

		return GetData()->m_Length;
	};
	BOOL IsEmpty() const {
		return GetLength() == 0;
	};
	void Empty() { ShrinkBuffer(0); };

	LPSTR GetBuffer() { return m_pBuffer; }
	LPCTSTR GetBuffer() const { return m_pBuffer; }
	LPSTR GetBuffer(DWORD minLength);
	DWORD GetBufferSize() const;
#else
	DWORD GetLength() const {
		if (!GetData()) {
			return 0;
		}

		return GetData()->m_Length;
	};
	BOOL IsEmpty() const {
		return GetLength() == 0;
	};
	void Empty() { ShrinkBuffer(0); };

	LPSTR GetBuffer() { return m_pBuffer; }
	LPCTSTR GetBuffer() const { return m_pBuffer; }
	LPSTR GetBuffer(DWORD minLength);
	DWORD GetBufferSize() const { if (!GetData()) return 0; else return GetData()->m_BufferSize; }
#endif
	void ReleaseBuffer(int32 length = -1);

	void FormatV(LPCTSTR pFormat, va_list args);
	void Format(LPCTSTR pFormat, ...);

	int Find(char ch, DWORD start) const;
	int Find(char ch) const { return Find(ch, 0); }
	int Find(LPCTSTR pSub, DWORD start) const;
	int Find(LPCTSTR pSub) const { return Find(pSub, 0); }
	int Replace(LPCTSTR pOld, LPCTSTR pNew);
	// replace occurrences of chOld with chNew
	int Replace( char chOld, char chNew);

	int Compare(LPCTSTR lpsz) const;
	int CompareNoCase(LPCTSTR lpsz) const;


	void Concat(LPCTSTR pString);
	void Concat(char ch);

	CString Mid(DWORD nFirst, DWORD nCount) const;
	CString Mid(DWORD nFirst) const;
	CString Left(DWORD nCount) const;
	CString Right(DWORD nCount) const;

	// Note : access past the end of the string is undefined, since this is a thin wrapper..
	char GetAt(int nIndex) const { if (!GetBuffer()) return 0; else return GetBuffer()[nIndex];}
	void SetAt(int nIndex, char ch) { if (!GetBuffer()) return; else GetBuffer()[nIndex] = ch; }

#if 0
	// NLS aware conversion to uppercase
	void MakeUpper();
	// NLS aware conversion to lowercase
	void MakeLower();
	// reverse string right-to-left
	void MakeReverse();
#endif

	// Operators
	operator LPCTSTR () const { return m_pBuffer; }
	char &operator[](int nIndex) { return GetBuffer()[nIndex]; }
	const char &operator[](int nIndex) const { return GetBuffer()[nIndex]; }
	const CString& operator+=(const CString& string) { Concat(string); return *this; }
	const CString& operator+=(char ch) { Concat(ch); return *this; }
	const CString& operator=(const CString& stringSrc) { CopyString(stringSrc); return *this; }
	const CString& operator=(LPCTSTR pString) { CopyString(pString); return *this; }
	const CString& operator=(const unsigned char* psz) { CopyString((LPCTSTR)psz); return *this; }

protected:
	// Internal utility functions

	// Copy a string (expands the buffer if needed)
#if 1
	void CopyString(LPCTSTR pString);
#else
	void CopyString(LPCTSTR pString)
	{
		if (pString)
		{
			DWORD newLength = (DWORD)strlen(pString);
			memcpy(GetBuffer(newLength + 1), pString, newLength + 1);
			SetLength(newLength);
		}
		else
			Empty();
	}
#endif
	// Make sure the buffer is at least minLength characters in size (including null)
	BOOL ExpandBuffer(DWORD minLength);
	// Make sure the buffer is no larger than maxLength characters in size (including null)
	BOOL ShrinkBuffer(DWORD maxLength);

	// Internal member access
	void SetLength(DWORD length) { if (GetData()) GetData()->m_Length = length; }

	CStringData *GetData() { if (!m_pBuffer) return NULL; else return ((CStringData *)m_pBuffer) - 1; }
	const CStringData *GetData() const { if (!m_pBuffer) return NULL; else return ((CStringData *)m_pBuffer) - 1; }
private:
	char *m_pBuffer;
};

typedef CSignedMoArray<CString> CStringArray;

#endif // __MFCS_STRING_H__