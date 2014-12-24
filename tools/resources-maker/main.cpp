#include <iostream>
#include <iomanip>
#include <fstream>

#include "SDL/SDL_image.h"

using namespace std;

Uint32 getPixel(SDL_Surface *surface, int x, int y);

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
				int width = image->w, height = image->h;
				cout << "static unsigned short " << argv[i + 1] << "[] = {" << endl;
				cout << hex << "\t0x2a01, 0x" << width << ", 0x" << height;
				int col = 3;
				for(int k = 0 ; k < width ; k++) {
					for(int l = 0 ; l < height ; l++) {
						if(col % 8 == 0) {
							col = 0;
							cout << endl << "\t";
						}
						cout << hex << setw(4) <<  ", 0x" << (getPixel(image, k, l) >> 16);
						col++;
					}
				}
				cout << endl << "};" << endl << endl << endl;
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
