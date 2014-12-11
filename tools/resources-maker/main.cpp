#include <iostream>
#include <iomanip>

#include "SDL/SDL_image.h"

using namespace std;

Uint32 getPixel(SDL_Surface *surface, int x, int y);

int main(int argc, char **argv) 
{
	for(int i = 1 ; i < argc ; i+=2) {
		SDL_Surface *image = IMG_Load(argv[i]);
		int width = image->w, height = image->h;
		cout << "static unsigned short " << argv[i + 1] << "[] {" << endl;
		cout << hex << setw(8) << "\t0x2a01, 0x" << width << ", 0x" << height;
		int col = 3;
		for(int k = 0 ; k < width ; k++) {
			for(int l = 0 ; l < height ; l++) {
				if(col % 8 == 0) {
					col = 0;
					cout << endl << "\t";
				}
				cout << ", 0x" << getPixel(image, k, l);
				col++;
			}
		}
		cout << endl << "};" << endl << endl << endl;
		SDL_FreeSurface(image);	
	}
}

Uint32 getPixel(SDL_Surface *surface, int x, int y) {
	int bpp = surface->format->BytesPerPixel;
	Uint8 *pixel0 = (Uint8 *)surface->pixels + y * surface->pitch + x*bpp;
	switch(bpp) {
	case 1:
		return *pixel0;
	case 2:
		return *(Uint16 *)pixel0;
	case 3:		// Probably useless ..
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return pixel0[0] << 16 | pixel0[1] << 8 | pixel0[2];
		else
			return pixel0[0] | pixel0[1] << 8 | pixel0[2] << 16;
	case 4:
		return *(Uint32 *)pixel0;
	default: 	// Avoid warnings
		return 0;
	}
}
