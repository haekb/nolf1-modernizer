#include "stdafx.h"
#include "FontMgr.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "MakePCX.h"

#include <iostream>
#include <sstream>
#include <fstream>

// Uncomment for helpful debugging, it'll break the font though.
//#define IMAGE_DEBUG 

FontMgr* g_pFontMgr = NULL;

FontMgr::FontMgr()
{
	g_pFontMgr = this;
}

FontMgr::~FontMgr()
{
	Term();
}

bool FontMgr::Init()
{
	if (TTF_Init() == -1) {
		g_pLTClient->CPrint("TTF_Init: %s\n", TTF_GetError());
		SDL_Log("TTF_Init: %s\n", TTF_GetError());
		ASSERT(LTFALSE);
		return false;
	}

	return true;
}

bool FontMgr::Term()
{
	return true;
}

void FontMgr::SetPixel(SDL_Surface* pSurface, int x, int y, int r, int g, int b)
{
	int bpp = pSurface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8* p = (Uint8*)pSurface->pixels + y * pSurface->pitch + x * bpp;

	uint32 colour = SDL_MapRGB(pSurface->format, r, g, b);

	*p = colour & 0xFF;
}

//
// Get Trim Dimensions
// Terms:	SOLID		= a non black pixel
//			VOID/BLACK	= a fully black pixel (rgb: 0, 0, 0)
//
void FontMgr::GetTrimDims(SDL_Surface* pSurface, int startX, int* outLeft, int* outRight)
{
	int x = startX;
	int bpp = pSurface->format->BytesPerPixel;
	int left = 0;
	int right = 0;

	bool bFoundLeft = false;
	bool bThisColumnIsSolid = false;
	bool bLastColumnIsSolid = false;
	bool bFoundSolidAfterRight = false;

	int debug_found_solid_at_y = -1;

	const int BLACK = 0;

	// Loop through every column!
	while (x < pSurface->w) {
		
		bThisColumnIsSolid = false;

		for (int y = 0; y < pSurface->h; y++)
		{
			/* Here p is the address to the pixel we want to retrieve */
			Uint8* p = (Uint8*)pSurface->pixels + y * pSurface->pitch + x * bpp;

			int pixel = *p;

			// Check if we've found the first solid block
			if (!bFoundLeft && pixel != BLACK)
			{
				bFoundLeft = true;
				left = x;
			}

			// We found a solid! Mark this row as solid.
			if (pixel != BLACK)
			{
				debug_found_solid_at_y = y;
				bThisColumnIsSolid = true;
			}
		}

		// Hey we found a possible right position!
		// Save our current x position.
		if (bLastColumnIsSolid && !bThisColumnIsSolid)
		{
			right = x;
		}

		// This allows to determine if might be some middle void
		// In case the surface ends in a solid.
		if (right && !bFoundSolidAfterRight)
		{
			bFoundSolidAfterRight = true;
		}

		// Carry forward...
		bLastColumnIsSolid = bThisColumnIsSolid;

		// Foward!
		x++;
	}

	// If we never wrote our right value...
	// OR
	// If we found solid after we wrote our right value
	// and the last row is solid, that means there was some middle void
	// and we want to ignore that, and use the surface width as our right value!
	if (right == 0 || (bFoundSolidAfterRight && bLastColumnIsSolid))
	{
		right = pSurface->w;
	}


	if (outLeft != NULL)
	{
		*outLeft = left;
	}

	if (outRight != NULL)
	{
		*outRight = right;
	}
}

//
// Because symbols like " exists we have to actually find the break in the middle so we can draw a barely transparent line to connect them..
//
void FontMgr::GlyphCheckForEmpty(SDL_Surface* pSurface, int start, int &minX, int &maxX)
{
	int originalX = minX;


	bool bFoundMin = false;
	bool bFoundMax = false;

	while (!bFoundMin || !bFoundMax)
	{
		bool bFoundUninterruptedMin = true;
		bool bFoundUninterruptedMax = false;
		for (int y = 0; y < pSurface->h; y++)
		{
			int bpp = pSurface->format->BytesPerPixel;
			/* Here p is the address to the pixel we want to retrieve */
			Uint8* p = (Uint8*)pSurface->pixels + y * pSurface->pitch + start * bpp;

			if (*p != 0)
			{
				bFoundUninterruptedMin = false;
			}

			// We want to find the first solid
			if (bFoundMin && *p != 0)
			{
				bFoundUninterruptedMax = true;
			}
		}

		if (!bFoundMin && bFoundUninterruptedMin)
		{
			minX = start;
			bFoundMin = true;
		}

		if (!bFoundMax && bFoundUninterruptedMax)
		{
			maxX = start;
			bFoundMax = true;
		}

		// Retreat!
		if (!bFoundMin || !bFoundMax) {
			start++;
		}

		if (start == pSurface->w) {
			break;
		}

	}

}



bool FontMgr::LoadAndExport(std::string font, int size, std::string filename)
{
	// load font.ttf at size 16 into font
	TTF_Font* pFont;
	pFont = TTF_OpenFont(font.c_str(), size);
	if (!pFont) {
		g_pLTClient->CPrint("TTF_OpenFont: %s\n", TTF_GetError());
		SDL_Log("TTF_OpenFont: %s\n", TTF_GetError());
		return false;
	}

	SDL_Color color = { 255,255,255 };
	SDL_Color bg = { 0,0,0 };
	SDL_Surface* pSurface;

	// Our character map
	std::string sFontCharacters = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]#_`abcdefghijklmnopqrstuvwxyz{|}~";

	std::string sFillerCharacters = sFontCharacters;

	// Add some extra width
	sFillerCharacters += "==========================================";

	// Create the initial file to cheat the width and height!
	pSurface = TTF_RenderText_Shaded(pFont, sFillerCharacters.c_str(), color, bg);
	SDL_Rect rect = { 0, 0, pSurface->w, pSurface->h };
	
	// Ok fill it with black!
	SDL_FillRect(pSurface, &rect, 0);

	// X starts at 1, because we need one black space.
	int x = 1;

#ifdef IMAGE_DEBUG
	SDL_Rect line = { x, 0, 1, pSurface->h };
	SDL_FillRect(pSurface, &line, SDL_MapRGB(pSurface->format, 255, 255, 255));

	SDL_SaveBMP(pSurface, "pSurface.bmp");
#endif

	// Ok let's loop through every character in our beautiful font alphabet
	// We only want ONE PIXEL of space between characters.
	for (auto glyph : sFontCharacters)
	{
		int minX, minY, maxX, maxY, advance;
		TTF_GlyphMetrics(pFont, glyph, &minX, &maxX, &minY, &maxY, &advance);

		SDL_Surface* pGlyph = TTF_RenderGlyph_Shaded(pFont, glyph, color, bg);

#ifdef IMAGE_DEBUG 
		// Debug dump every glyph
		std::string filename = "chars\\";
		filename += glyph;
		filename += ".bmp";

		SDL_SaveBMP(pGlyph, filename.c_str());
#endif

		// Get our REAL minX and maxX. Fonts like to lie.
		GetTrimDims(pGlyph, 0, &minX, &maxX);

		int glyphWidth = maxX - minX;

		// Ok special case for symbols that are separated but are actually one
		// We need to draw a barely transparent line (fonts are blended, so darker the better!)
		// So that the engine picks it up as one character!
		//
		// We could probably run this on every character, but our map only has one character like this... 
		//
		if (glyph == '\"')
		{
			int emptyMin = 0;
			int emptyMax = 0;

			GlyphCheckForEmpty(pGlyph, minX, emptyMin, emptyMax);

			for (int i = emptyMin; i < emptyMax; i++)
			{
				SetPixel(pGlyph, i, 0, 128, 128, 128);
			}
			
		}
		
		// Use glyphCheck's positioning in case we need to get rid of some extra spaces at the start!
		rect = { x, 0, x + glyphWidth, 0 };
		SDL_Rect srcRect = { minX, 0, maxX, pGlyph->h };

		SDL_BlitSurface(pGlyph, &srcRect, pSurface, &rect);

		// Advance our x position!
		x += glyphWidth + 1;

#ifdef IMAGE_DEBUG
		line = { x, 0, 1, pSurface->h };
		SDL_FillRect(pSurface, &line, SDL_MapRGB(pSurface->format, 255, 255, 255));

		SDL_SaveBMP(pSurface, "pSurface.bmp");
#endif
	}

	// Create a new scaled surface
	SDL_Surface* pRealSurface = SDL_CreateRGBSurface(0, x + 2, pSurface->h, 8, 0, 0, 0, 0);

	// Set the palette colours so we'll actually get something!
	SDL_SetPaletteColors(pRealSurface->format->palette, pSurface->format->palette->colors, 0, pSurface->format->palette->ncolors);

	// Blit the old surface onto the new scaled surface
	rect = { 0, 0, x, pSurface->h };
	SDL_BlitSurface(pSurface, NULL, pRealSurface, &rect);

	MakePCX(pRealSurface, filename);

	SDL_FreeSurface(pSurface);
	SDL_FreeSurface(pRealSurface);

	return true;
}


