//  SuperTux
//  Copyright (C) 2004 Tobias Glaesser <tobi.web@gmx.de>
//
//  Adaptation for the TI nspire calculator by
// 	CHAUVIN Barnabe <barnabe.chauvin@gmail.com>
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
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//  02111-1307, USA.

#ifndef SUPERTUX_TEXTURE_H
#define SUPERTUX_TEXTURE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <string>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <list>

#include "setup.h"
#include "screen.h"

SDL_Surface *sdl_surface_from_sdl_surface(SDL_Surface *sdl_surf, int use_alpha);

class SurfaceImpl;
class SurfaceSDL;

/** This class holds all the data necessary to construct a surface */
class SurfaceData
{
	public:
		enum ConstructorType { LOAD, LOAD_PART, SURFACE };
		ConstructorType type;
		SDL_Surface *surface;
		std::string file;
		int use_alpha;
		int x;
		int y;
		int w;
		int h;

		SurfaceData(SDL_Surface *surf, int use_alpha_);
		SurfaceData(const std::string &file_, int use_alpha_);
		SurfaceData(const std::string &file_, int x_, int y_, int w_, int h_,
		            int use_alpha_);
		~SurfaceData();

		SurfaceSDL *create_SurfaceSDL();
		SurfaceImpl *create();
};

/** Container class that holds a SDL surface */
class Surface
{
	public:
		SurfaceData data;
		SurfaceImpl *impl;
		int w;
		int h;

		typedef std::list<Surface *> Surfaces;
		static Surfaces surfaces;
	public:
		static void reload_all();
		static void debug_check();

		Surface(SDL_Surface *surf, int use_alpha);
		Surface(const std::string &file, int use_alpha);
		Surface(const std::string &file, int x, int y, int w, int h, int use_alpha);
		~Surface();

		/** Captures the screen and returns it as Surface*, the user is expected to call the destructor. */
		static Surface *CaptureScreen();

		/** Reload the surface, which is necesarry in case of a mode swich */
		void reload();

		void draw(float x, float y, Uint8 alpha = 255, bool update = false);
		void draw_bg(Uint8 alpha = 255, bool update = false);
		void draw_part(float sx, float sy, float x, float y, float w, float h,
		               Uint8 alpha = 255, bool update = false);
		void draw_stretched(float x, float y, int w, int h, Uint8 alpha,
		                    bool update = false);
		void resize(int w_, int h_);
};

/** Surface implementation, all implementation have to inherit from
    this class */
class SurfaceImpl
{
	protected:
		SDL_Surface *sdl_surface;

	public:
		int w;
		int h;

	public:
		SurfaceImpl();
		virtual ~SurfaceImpl();

		/** Return 0 on success, -2 if surface needs to be reloaded */
		virtual int draw(float x, float y, Uint8 alpha, bool update) = 0;
		virtual int draw_bg(Uint8 alpha, bool update) = 0;
		virtual int draw_part(float sx, float sy, float x, float y, float w, float h,
		                      Uint8 alpha, bool update) = 0;
		virtual int draw_stretched(float x, float y, int w, int h, Uint8 alpha,
		                           bool update) = 0;
		int resize(int w_, int h_);

		SDL_Surface *get_sdl_surface() const; // @evil@ try to avoid this function
};

class SurfaceSDL : public SurfaceImpl
{
	public:
		SurfaceSDL(SDL_Surface *surf, int use_alpha);
		SurfaceSDL(const std::string &file, int use_alpha);
		SurfaceSDL(const std::string &file, int x, int y, int w, int h, int use_alpha);
		virtual ~SurfaceSDL();

		int draw(float x, float y, Uint8 alpha, bool update);
		int draw_bg(Uint8 alpha, bool update);
		int draw_part(float sx, float sy, float x, float y, float w, float h,
		              Uint8 alpha, bool update);
		int draw_stretched(float x, float y, int w, int h, Uint8 alpha, bool update);
};

#endif /*SUPERTUX_TEXTURE_H*/

/* Local Variables: */
/* mode: c++ */
/* End: */
