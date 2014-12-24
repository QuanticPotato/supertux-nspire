//  resource-maker
//  Copyright (C) 2014 CHAUVIN Barnabe <barnabe.chauvin@gmail.com>
//  
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include <iostream>
#include <iomanip>
#include <fstream>

#include "SDL/SDL_image.h"

using namespace std;

unsigned short getPixel(SDL_Surface *surface, int x, int y);

int main(int argc, char **argv) 
{
	if(argc >= 2) {
		string first_arg = string(argv[1]);
		// This is a simple feature to be easily recognize by the scanner.
		if(first_arg == "-magic_code") {
			exit(42);
		}
		else if(first_arg == "--help" || first_arg == "-help" || first_arg == "-h" || first_arg == "--usage") {
			cout << "Usage : " << endl << "\tresource-scanner img img1 lbl1 [img2 lbl2] ..." << endl << "\tresource-scanner txt txt1 lbl1 [txt2 lbl2] ..." << endl;
			return 0;
		}
		if(first_arg == "img") {
			for(int i = 2 ; i < argc ; i+=2) {
				SDL_Surface *image = IMG_Load(argv[i]);
				SDL_LockSurface(image); // Probably useless, but we keep the good habits :p
				int width = image->w, height = image->h;
				cout << "static unsigned short " << argv[i + 1] << "[] = {" << endl;
				cout << hex << "\t0x2a01, 0x" << width << ", 0x" << height <<  ", 0x0000";
				int col = 4;
				for(int k = 0 ; k < height ; k++) {
					for(int l = 0 ; l < width ; l++) {
						if(col % 8 == 0) {
							col = 0;
							cout << endl << "\t";
						}
						cout << hex << setw(4) <<  ", 0x" << (getPixel(image, l, k));
						col++;
					}
				}
				cout << endl << "};" << endl << endl << endl;
				SDL_UnlockSurface(image);
				SDL_FreeSurface(image);	
			}
		} else if(first_arg == "txt") {
			// The txt option only escape the newlines and quotes
			for(int i = 2 ; i < argc ; i+=2) {
				// First, be sure we can open the file ..
				ifstream input_file(argv[i], ios::in);
				if(!input_file)
					continue;
				cout << "static const char *file_" << string(argv[i+1]) << " = \"";
				string line;
				while(getline(input_file, line)) {
					for(int j = 0 ; j < line.size() ; j++) {
						if(line.at(j) == '\"')
							cout << "\\\"";
						else if(line.at(j) == EOF)
							; // Do not copy it !
						else
							cout << line.at(j);
					}	
					cout << "\\n\\" << endl;
				}
				cout << "\";" << endl << endl;
			}
		}
	}
}

/* This function convert the 32 bits pixel (retrieved from the image) to a 16-bit high color.
 *  The 16-bit high color follow this scheme : 
 *      RRRRRGGGGGGBBBBB   (there is one more bit for the green)
 */
unsigned short getPixel(SDL_Surface *surface, int x, int y) 
{
	int bpp = surface->format->BytesPerPixel;
	Uint8 *pixel0 = (Uint8 *)surface->pixels + y * surface->pitch + x*bpp;
	Uint32 pixel = 0;
	switch(bpp) {
	case 1:
		pixel = *pixel0;
		break;
	case 2:
		pixel = *(Uint16 *)pixel0;
		break;
	case 3:		// Probably useless ..
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			pixel = pixel0[0] << 16 | pixel0[1] << 8 | pixel0[2];
		else
			pixel = pixel0[0] | pixel0[1] << 8 | pixel0[2] << 16;
		break;
	case 4:
		pixel = *(Uint32 *)pixel0;
		break;
	default: 	// Avoid warnings
		pixel = 0;
	}
	Uint8 r, g, b, a;
	SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);
	/* The Uint8 has to be the equivalent of an unsigned char !
	 * Hack the following code if your platform deals with different size.
	 *
	 * For the red and the blue, we get rid of the 3 last bits (the less significant ones)
	 * For the green, we get rid of the 2 last bits.
	 *
	 * We discard the alpha level, it's just transparent or not.
	 */
	if(a == 0) // Transparent pixel
		return 0xf81f;  // 1111100000011111
	unsigned short red = (((unsigned char)r) >> 3) << 11;
	unsigned short green = (((unsigned char)g) >> 2) << 5;
	unsigned short blue = ((unsigned char)b) >> 3;
	// Finaly, regroup the 3 colors ..
	return red | green | blue;
}

