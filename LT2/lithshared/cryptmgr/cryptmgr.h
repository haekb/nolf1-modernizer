#if !defined(_CRYPTMGR_H_)
#define _CRYPTMGR_H_


#if _MSC_VER >= 1300
#include <iostream>
#define STD std::
#else
#include "iostream.h"
#define STD 
#endif



class CCryptMgr
{
public:

	CCryptMgr();
	CCryptMgr(char* key);
	~CCryptMgr();

	void SetKey(const char* key);  // Max of 56 characters

	// if using fstreams be sure to open them in binary mode
	void Encrypt(STD istream& is, STD ostream& os);

	// if using fstreams be sure to open them in binary mode
	void Decrypt(STD istream& is, STD ostream& os);

};





#endif
