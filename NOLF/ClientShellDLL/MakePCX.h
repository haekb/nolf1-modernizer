#pragma once
#include "Stdafx.h"
#include <SDL.h>

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
#define USE_SDL_RW

//
// Returns the number of bytes written to data
//
int PCXEncodedPut(BYTE byte, int counter, SDL_RWops* outFile)
{
	if (!counter) {
		return 0;
	}

	if ((counter == 1) && (0xC0 != (0xC0 & byte)))
	{
		SDL_RWwrite(outFile, &byte, sizeof(byte), 1);
		return 1;
	}
	unsigned char end = 0xC0 | counter;
	SDL_RWwrite(outFile, &end, sizeof(end), 1);
	SDL_RWwrite(outFile, &byte, sizeof(byte), 1);

	return 2;
}


void MakePCX(SDL_Surface* pSurface, std::string filename)
{
	BYTE colourMap[PCX_MAX_PALETTE] = { 0 };

	_PcxHeader PCX;
	memset(&PCX, 0, sizeof(PCX));

	PCX.Identifier = 0x0A;
	PCX.Version = 5;
	PCX.Encoding = 1;
	PCX.BitsPerPixel = 8;
	PCX.XStart = 0;
	PCX.XEnd = pSurface->w - 1;
	PCX.YStart = 0;
	PCX.YEnd = pSurface->h - 1;
	memcpy(PCX.Palette, colourMap, sizeof(colourMap));
	PCX.PaletteType = 1;
	PCX.HorzRes = 96;
	PCX.VertRes = 96;
	PCX.BytesPerLine = pSurface->pitch;
	PCX.NumBitPlanes = 1;

	// Start up a file
	SDL_RWops* outFile = SDL_RWFromFile(filename.c_str(), "w+b");

	//
	// Header time!
	//
	SDL_RWwrite(outFile, &PCX, sizeof(_PcxHeader), 1);

	//
	// Encoding time!
	// 

	// Get a reference to the pixels, and setup our last and current pixel
	BYTE* pixelBuffer = (BYTE*)pSurface->pixels;

	for (int y = 0; y < pSurface->h; y++)
	{
		int counter = 1;
		int total = 0;

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
					int i = PCXEncodedPut(lastPixel, counter, outFile);
					total += i;
					counter = 0;
				}
			}
			else
			{
				if (counter)
				{
					int i = PCXEncodedPut(lastPixel, counter, outFile);
					total += i;
				}

				lastPixel = pixel;
				counter = 1;
			}
		}
		if (counter) {
			int i = PCXEncodedPut(lastPixel, counter, outFile);
			total += i;
		}
	}

	//
	// Palette time, mark a palette, and write out SDL2's one!
	// 
	int paletteIdentifier = 0x0C;
	SDL_RWwrite(outFile, &paletteIdentifier, sizeof(paletteIdentifier), 1);

	SDL_Color* sdlPal = pSurface->format->palette->colors;
	BYTE pal[768] = { 0 };
	for (int i = 0; i < 256; i++) {
		pal[3 * i] = sdlPal[i].r;
		pal[3 * i + 1] = sdlPal[i].g;
		pal[3 * i + 2] = sdlPal[i].b;
	}
	SDL_RWwrite(outFile, &pal, 768, 1);

	SDL_RWclose(outFile);

}
