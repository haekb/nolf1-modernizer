#include "stdafx.h"
#include "FontMgr.h"
#include "SDL.h"
#include "SDL_ttf.h"

#include <iostream>
#include <sstream>
#include <fstream>

// Pretend this is a header for now!

#define PCX_MAX_PALETTE 48
// Thanks https://www.fileformat.info/format/pcx/egff.htm
typedef struct _PcxHeader
{
	BYTE	Identifier;        /* PCX Id Number (Always 0x0A) */
	BYTE	Version;           /* Version Number */
	BYTE	Encoding;          /* Encoding Format */
	BYTE	BitsPerPixel;      /* Bits per Pixel */
	WORD	XStart;            /* Left of image */
	WORD	YStart;            /* Top of Image */
	WORD	XEnd;              /* Right of Image */
	WORD	YEnd;              /* Bottom of image */
	WORD	HorzRes;           /* Horizontal Resolution */
	WORD	VertRes;           /* Vertical Resolution */
	BYTE	Palette[PCX_MAX_PALETTE];       /* 16-Color EGA Palette */
	BYTE	Reserved1;         /* Reserved (Always 0) */
	BYTE	NumBitPlanes;      /* Number of Bit Planes */
	WORD	BytesPerLine;      /* Bytes per Scan-line */
	WORD	PaletteType;       /* Palette Type */
	WORD	HorzScreenSize;    /* Horizontal Screen Size */
	WORD	VertScreenSize;    /* Vertical Screen Size */
	BYTE	Reserved2[54];     /* Reserved (Always 0) */
} PCXHEAD;

//
// Returns the number of bytes written to data
//
int PCXEncodedPut(BYTE byte, int counter, std::ofstream* outFile)
{
	if (!counter) {
		return 0;
	}

	if ( (counter == 1) && (0xC0 != (0xC0 & byte) ) )
	{
		outFile->write(reinterpret_cast<const char*>(&byte), sizeof(byte));
		return 1;
	}
	unsigned char end = 0xC0 | counter;
	outFile->write(reinterpret_cast<const char*>(&end), sizeof(end));
	outFile->write(reinterpret_cast<const char*>(&byte), sizeof(byte));

	return 2;
}

void MakePCX(SDL_Surface* pSurface)
{	
	BYTE colourMap[PCX_MAX_PALETTE] = { 0 };


	int nImageSize = pSurface->pitch * pSurface->h;

	_PcxHeader PCX;
	memset(&PCX, 0, sizeof(PCX));

	PCX.Identifier = 0x0A;
	PCX.Version = 5;
	PCX.Encoding = 1;
	PCX.BitsPerPixel = 8;
	PCX.XStart = 0;
	PCX.XEnd = pSurface->w;
	PCX.YStart = 0;
	PCX.YEnd = pSurface->h;
	memcpy(PCX.Palette , colourMap, sizeof(colourMap));
	PCX.PaletteType = 1;
	PCX.HorzRes = 96;
	PCX.VertRes = 96;
	PCX.BytesPerLine = pSurface->pitch;
	PCX.NumBitPlanes = 1;

	// Start up a file
	std::ofstream outFile("NOLF\\Modernizer\\Fonts\\font_large_0.pcx", std::ios::binary | std::ios::out);

	//
	// Header time!
	//

	// Write out the header, there's probably a better way to do this...
	outFile.write(reinterpret_cast<const char*>(&PCX.Identifier), sizeof(PCX.Identifier));
	outFile.write(reinterpret_cast<const char*>(&PCX.Version), sizeof(PCX.Version));
	outFile.write(reinterpret_cast<const char*>(&PCX.Encoding), sizeof(PCX.Encoding));
	outFile.write(reinterpret_cast<const char*>(&PCX.BitsPerPixel), sizeof(PCX.BitsPerPixel));
	outFile.write(reinterpret_cast<const char*>(&PCX.XStart), sizeof(PCX.XStart));
	outFile.write(reinterpret_cast<const char*>(&PCX.YStart), sizeof(PCX.YStart));
	outFile.write(reinterpret_cast<const char*>(&PCX.XEnd), sizeof(PCX.XEnd));
	outFile.write(reinterpret_cast<const char*>(&PCX.YEnd), sizeof(PCX.YEnd));
	outFile.write(reinterpret_cast<const char*>(&PCX.HorzRes), sizeof(PCX.HorzRes));
	outFile.write(reinterpret_cast<const char*>(&PCX.VertRes), sizeof(PCX.VertRes));
	outFile.write(reinterpret_cast<const char*>(&PCX.Palette), sizeof(PCX.Palette));
	outFile.write(reinterpret_cast<const char*>(&PCX.Reserved1), sizeof(PCX.Reserved1));
	outFile.write(reinterpret_cast<const char*>(&PCX.NumBitPlanes), sizeof(PCX.NumBitPlanes));
	outFile.write(reinterpret_cast<const char*>(&PCX.BytesPerLine), sizeof(PCX.BytesPerLine));
	outFile.write(reinterpret_cast<const char*>(&PCX.PaletteType), sizeof(PCX.PaletteType));
	outFile.write(reinterpret_cast<const char*>(&PCX.HorzScreenSize), sizeof(PCX.HorzScreenSize));
	outFile.write(reinterpret_cast<const char*>(&PCX.VertScreenSize), sizeof(PCX.VertScreenSize));
	outFile.write(reinterpret_cast<const char*>(&PCX.Reserved2), sizeof(PCX.Reserved2));
	
	//
	// Encoding time!
	// 

	// Get a reference to the pixels, and setup our last and current pixel
	BYTE* pixelBuffer = (BYTE*)pSurface->pixels;

	// Used to cover a weird bug, see the FIXME below!
	SDL_Surface* black = SDL_CreateRGBSurface(0, pSurface->w, pSurface->h, 8, 0, 0, 0, 0);
	SDL_Rect rect = { 0, 0, pSurface->w, pSurface->h + 8 };
	SDL_FillRect(black, &rect, 0);

	for (int y = 0; y < pSurface->h + 1; y++)
	{
		int counter = 1;
		int total = 0;

		// FIXME: There's some over/under reading, not sure what the cause is, as my code is pretty close to the sample C code the spec has...
		// So let's just write black!
		if (y >= pSurface->h - 1) {
			pixelBuffer = (BYTE*)black->pixels;
		}

		BYTE pixel = pixelBuffer[y * pSurface->pitch];
		BYTE lastPixel = pixel;

		// This will run through every pixel of the image, and encode it with RLE.
		for (int x = 1; x < pSurface->pitch; x++)
		{
			// Increment our pixel
			pixel = pixelBuffer[(y * pSurface->pitch) + x];

			if (pixel == lastPixel) {
				counter++;
				// We hit our max, write!
				if (counter == 63)
				{
					int i = PCXEncodedPut(lastPixel, counter, &outFile);
					total += i;
					counter = 0;
				}
			}
			else
			{
				if (counter)
				{
					int i = PCXEncodedPut(lastPixel, counter, &outFile);
					total += i;
				}

				lastPixel = pixel;
				counter = 1;
			}
		}
		if (counter) {
			int i = PCXEncodedPut(lastPixel, counter, &outFile);
			total += i;
		}
	}

	// Clean up the bugfix surface
	SDL_FreeSurface(black);

	//
	// Palette time, mark a palette, and write out SDL2's one!
	// 

	int paletteIdentifier = 0x0C;
	outFile.write(reinterpret_cast<const char*>(&paletteIdentifier), sizeof(paletteIdentifier));

	SDL_Color* sdlPal = pSurface->format->palette->colors;
	BYTE pal[768] = { 0 };
	for (int i = 0; i < 256; i++) {
		pal[3 * i] =	 sdlPal[i].r;
		pal[3 * i + 1] = sdlPal[i].g;
		pal[3 * i + 2] = sdlPal[i].b;
	}
	outFile.write(reinterpret_cast<const char*>(&pal), 768);

	// We're done folks!
	outFile.close();

}


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
		ASSERT(LTFALSE);
		return false;
	}

	return true;
}

bool FontMgr::Term()
{
	return true;
}


//
// Same as CheckForSolids, except in the opposite direction!
//
int GlyphCheckForSolids(SDL_Surface* pSurface, int x)
{
	int originalX = x;

	// So fonts kinda lie. The width is usually not the real solid width!
	// So we'll check our current x position against the height and see if it's empty
	// Then we'll slowly retreat until we find solid!
	bool bFoundSolid = false;

	while (!bFoundSolid)
	{
		for (int y = 0; y < pSurface->h; y++)
		{
			int bpp = pSurface->format->BytesPerPixel;
			/* Here p is the address to the pixel we want to retrieve */
			Uint8* p = (Uint8*)pSurface->pixels + y * pSurface->pitch + x * bpp;

			if (*p != 0) {
				bFoundSolid = true;
				break;
			}
		}

		// Retreat!
		if (!bFoundSolid) {
			x++;
		}

		if (x == pSurface->w) {
			//x = 0;
			break;
		}
	}

	return x;

	// If our x position matches our originalX
	// then increment our x by one, because they need a single space!
	if (x == originalX) {
		x--;
	}

	// Add the one line of empty!
	x--;

	return x;
}

int CheckForSolids(SDL_Surface* pSurface, int x, bool glyphCheck)
{
	int originalX = x;

	// So fonts kinda lie. The width is usually not the real solid width!
	// So we'll check our current x position against the height and see if it's empty
	// Then we'll slowly retreat until we find solid!
	bool bFoundSolid = false;

	while (!bFoundSolid)
	{
		for (int y = 0; y < pSurface->h; y++)
		{
			int bpp = pSurface->format->BytesPerPixel;
			/* Here p is the address to the pixel we want to retrieve */
			Uint8* p = (Uint8*)pSurface->pixels + y * pSurface->pitch + x * bpp;

			if (*p != 0) {
				bFoundSolid = true;
				break;
			}
		}

		// Retreat!
		if (!bFoundSolid) {
			x--;
		}

		if (x < 0) {
			break;
		}
	}

	// If we're on a glyph check, don't increment!
	if (glyphCheck)
	{
		if (x > -1) {
			x++;
		}
		return x;
	}

	// If our x position matches our originalX
	// then increment our x by one, because they need a single space!
	if (x == originalX) {
		x++;
	}

	// Add the one line of empty!
	x++;

	return x;
}

bool FontMgr::Load(std::string font, int size)
{
	// load font.ttf at size 16 into font
	TTF_Font* pFont;
	pFont = TTF_OpenFont(font.c_str(), size);
	if (!pFont) {
		g_pLTClient->CPrint("TTF_OpenFont: %s\n", TTF_GetError());
		return false;
	}

	SDL_Color color = { 255,255,255 };
	SDL_Color bg = { 0,0,0 };
	SDL_Surface* pSurface;

	// Old character sheet, none of the fonts seem to have { } ~ ...
	//std::string sFontCharacters = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]#_`abcdefghijklmnopqrstuvwxyz{|}~";
	std::string sFontCharacters = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]#_`abcdefghijklmnopqrstuvwxyz(|)-";

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

	// Ok let's loop through every character in our beautiful font alphabet
	// We only want ONE PIXEL of space between characters.
	for (auto glyph : sFontCharacters)
	{
		int minX, minY, maxX, maxY, advance;
		TTF_GlyphMetrics(pFont, glyph, &minX, &maxX, &minY, &maxY, &advance);

		int glyphWidth = maxX - minX;

		SDL_Surface* pGlyph = TTF_RenderGlyph_Shaded(pFont, glyph, color, bg);

		// Check to see if the glyph has any spaces at the start
		int glyphCheck = GlyphCheckForSolids(pGlyph, 0);

		minX = glyphCheck;//glyphCheck -= (minX - x);

		// Use glyphCheck's positioning in case we need to get rid of some extra spaces at the start!
		rect = { x, 0, x + glyphWidth, 0 };
		SDL_Rect srcRect = { minX, 0, maxX, pGlyph->h };

		SDL_BlitSurface(pGlyph, &srcRect, pSurface, &rect);
		SDL_SaveBMP(pSurface, "pSurface.bmp");
		// Advance our x position!
		x += glyphWidth + 1;

		//x = CheckForSolids(pSurface, x, false);

#if 0
		int originalX = x;

		// So fonts kinda lie. The width is usually not the real solid width!
		// So we'll check our current x position against the height and see if it's empty
		// Then we'll slowly retreat until we find solid!
		bool bFoundSolid = false;
		
		while(!bFoundSolid) 
		{
			for (int y = 0; y < pSurface->h; y++) 
			{
				int bpp = pSurface->format->BytesPerPixel;
				/* Here p is the address to the pixel we want to retrieve */
				Uint8* p = (Uint8*)pSurface->pixels + y * pSurface->pitch + x * bpp;
				
				if (*p != 0) {
					bFoundSolid = true;
					break;
				}
			}

			// Retreat!
			if (!bFoundSolid) {
				x--;
			}
		}

		// If our x position matches our originalX
		// then increment our x by one, because they need a single space!
		if (x == originalX) {
			x++;
		}

		// Add the one line of empty!
		x++;
#endif
	}

	// Create a new scaled surface
	SDL_Surface* pRealSurface = SDL_CreateRGBSurface(0, x + 2, pSurface->h, 8, 0, 0, 0, 0);

	// Set the palette colours so we'll actually get something!
	SDL_SetPaletteColors(pRealSurface->format->palette, pSurface->format->palette->colors, 0, pSurface->format->palette->ncolors);

	// Blit the old surface onto the new scaled surface
	rect = { 0, 0, x, pSurface->h };
	SDL_BlitSurface(pSurface, NULL, pRealSurface, &rect);

	// Debug!
	SDL_SaveBMP(pSurface, "fontold.bmp");
	SDL_SaveBMP(pRealSurface, "font.bmp");

	MakePCX(pRealSurface);


	SDL_FreeSurface(pSurface);
	SDL_FreeSurface(pRealSurface);

}


