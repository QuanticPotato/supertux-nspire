//  SuperTux -  A Jump'n Run
//  Copyright (C) 2000 Bill Kendrick <bill@newbreedsoftware.com>
//
//  Adaptation for the TI nspire calculator by
//      CHAUVIN Barnabe <barnabe.chauvin@gmail.com>
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

#ifndef SUPERTUX_SETUP_H
#define SUPERTUX_SETUP_H

#include <assert.h>
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <sys/types.h>
#include <dirent.h>
#include <libgen.h>
#include <ctype.h>

/* os.h include sys/stat.h */
#include <os.h>
#include <libndls.h>

#include "defines.h"
#include "menu.h"
#include "type.h"
#include "defines.h"
#include "screen.h"
#include "texture.h"
#include "menu.h"
//#include "gameloop.h"
#include "configfile.h"
#include "scene.h"
//#include "worldmap.h"
//#include "ressources.h"
//#include "intro.h"
//#include "player.h"

#define SUPERTUX_DIRECTORY "supertux"

int faccessible(const char *filename);
int fcreatedir(const char *relative_dir);
int fwriteable(const char *filename);
FILE *opendata(const char *filename, const char *mode);
string_list_type dsubdirs(const char *rel_path, const char *expected_file);
string_list_type dfiles(const char *rel_path, const char *glob,
                        const char *exception_str);
void free_strings(char **strings, int num);
void st_directory_setup(void);
void st_general_setup(void);
void st_general_free();
void st_video_setup_sdl(void);
void st_video_setup(void);
void st_shutdown(void);
void st_menu(void);
void st_abort(const std::string &reason, const std::string &details);
void process_options_menu(void);

/** Return true if the gameloop() was entered, false otherwise */
bool process_load_game_menu();

void update_load_save_game_menu(Menu *pmenu);
void parseargs(int argc, char *argv[]);

#endif /*SUPERTUX_SETUP_H*/

