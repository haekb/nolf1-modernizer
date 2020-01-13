#pragma once
#include <string>

class FontMgr
{
public:
	FontMgr();
	~FontMgr();

	bool Init();
	bool Term();

	bool Load(std::string font, int size);

};

