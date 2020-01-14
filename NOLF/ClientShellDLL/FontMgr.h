#pragma once
#include <string>

class FontMgr
{
public:
	FontMgr();
	~FontMgr();

	bool Init();
	bool Term();

	bool LoadAndExport(std::string font, int size, std::string filename);

protected:
	void GlyphCheckForEmpty(SDL_Surface* pSurface, int start, int& minX, int& maxX);
	void GetTrimDims(SDL_Surface* pSurface, int startX, int* outLeft, int* outRight);
	void SetPixel(SDL_Surface* pSurface, int x, int y, int r, int g, int b);

};

