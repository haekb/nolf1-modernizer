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
	SDL_Surface* black = SDL_CreateRGBSurface(0, pSurface->w, pSurface->h + 128, 8, 0, 0, 0, 0);
	SDL_Rect rect = { 0, 0, pSurface->w, pSurface->h + 128 };
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
}

void SetPixel(SDL_Surface* pSurface, int x, int y, int r, int g, int b)
{
	int bpp = pSurface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8* p = (Uint8*)pSurface->pixels + y * pSurface->pitch + x * bpp;

	uint32 colour = SDL_MapRGB(pSurface->format, r, g, b);

	*p = colour & 0xFF;
}

//
// This doesn't actually affect an image, but it provides the dims to re-blit it onto a new surface!
//
void Trim(SDL_Surface* pSurface, int startX, int* outLeft, int* outRight)
{
	int x = startX;
	int bpp = pSurface->format->BytesPerPixel;

	bool bFoundLeft = false;

	int left = 0;
	int right = 0;
	int rightColour = 0;

	bool bPreviousColumnHadSolid = false;

	bool lastColumnHasSpace = false;

	while (x < pSurface->w) {
		bool bFoundSolidThisColumn = false;

		for (int y = 0; y < pSurface->h; y++)
		{
			/* Here p is the address to the pixel we want to retrieve */
			Uint8* p = (Uint8*)pSurface->pixels + y * pSurface->pitch + x * bpp;

			// 
			// First find the left solid side of this surface
			//
			if (!bFoundLeft) {

				if (*p != 0) {
					bFoundLeft = true;
					left = x;
					//break;
				}
			}

			//
			// Second find the right side of this surface
			// Only if we've found the left side first of course!
			// Note: Due to some characters having breaks in the middle, 
			// we have to actually go through the entire width of a character!
			//
			/*
			if (bFoundLeft)
			{
				if (right != x && bPreviousColumnHadSolid && *p == 0) {
					right = x;
					rightColour = *p;
				}
			}
			*/
			
			if (*p != 0) { 
				bFoundSolidThisColumn = true;
			}

			
		}
		// end loop 1

		if (bFoundLeft)
		{
			if (bPreviousColumnHadSolid && !bFoundSolidThisColumn) {
				right = x;
				rightColour = 0;
			}
		}

		// Copy over the solid info for next loop
		bPreviousColumnHadSolid = bFoundSolidThisColumn;

		if (!bFoundSolidThisColumn) {
			if (x == pSurface->w - 1) {
				lastColumnHasSpace = true;
			}
		}

		// Increment our x position!
		x++;
	}
	// end loop 2 
	if (outLeft != NULL)
	{
		*outLeft = left;
	}

	if (outRight != NULL)
	{


		// If right isn't the width of the surface then it had a space at the end. Trim that!
		if (!lastColumnHasSpace) {
			right = pSurface->w;
		}

		// If there's no spaces on the right side...make it the width!
		if (right == 0) {
			right = pSurface->w;
		}
		else {
			//right -= 1;
		}

		*outRight = right;
		SDL_Log("Found right colour <%d> at pos x <%d>", rightColour, right);
	}
}


//
// Because symbols like " exists we have to actually find the break in the middle so we can draw a barely transparent line to connect them..
//
void GlyphCheckForEmpty(SDL_Surface* pSurface, int start, int &minX, int &maxX)
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
	std::string sFontCharacters = ".!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]#_`abcdefghijklmnopqrstuvwxyz{|}~";
	//std::string sFontCharacters = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]#_`abcdefghijklmnopqrstuvwxyz(|)-";

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

		

		SDL_Surface* pGlyph = TTF_RenderGlyph_Shaded(pFont, glyph, color, bg);
		SDL_SaveBMP(pGlyph, "glyph.bmp");
		// Check to see if the glyph has any spaces at the start
		//int glyphCheck = GlyphCheckForSolids(pGlyph, 0);

		Trim(pGlyph, 0, &minX, &maxX);

		int glyphWidth = maxX - minX;

		//minX = glyphCheck;//glyphCheck -= (minX - x);

		// Ok special case for symbols that are separated but are actually one
		// We need to draw a barely transparent line (fonts are blended, so darker the better!)
		// So that the engine picks it up as one character!
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
		
		SDL_SaveBMP(pSurface, "pSurface.bmp");

#if 1
		// Advance our x position!
		x += glyphWidth + 1;
#else // TEST
		// Advance our x position!
		x += glyphWidth;

		for (int y = 0; y < pSurface->h; y++)
		{
			SetPixel(pSurface, x, y, 128, 0, 128);
		}

		x++;
#endif
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


