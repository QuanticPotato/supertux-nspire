//  SuperTux -  A Jump'n Run
//  Copyright (C) 2004 Michael George <mike@georgetech.com>
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
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include <stdlib.h>
#include <string>
#include "configfile.h"
#include "setup.h"
#include "globals.h"
#include "lispreader.h"
#include "player.h"

const char *config_filename = "/config";

static void defaults()
{
	/* Set defaults: */
	debug_mode = false;

	show_fps = false;
}

void loadconfig(void)
{
	FILE *file = NULL;

	defaults();

	/* override defaults from config file */

	file = opendata(config_filename, "r");

	if (file == NULL)
		return;

	/* read config file */

	lisp_stream_t   stream;
	lisp_object_t *root_obj = NULL;

	lisp_stream_init_file(&stream, file);
	root_obj = lisp_read(&stream);

	if (root_obj->type == LISP_TYPE_EOF || root_obj->type == LISP_TYPE_PARSE_ERROR)
		return;

	if (strcmp(lisp_symbol(lisp_car(root_obj)), "supertux-config") != 0)
		return;

	LispReader reader(lisp_cdr(root_obj));

	reader.read_bool("show_fps",   &show_fps);

	reader.read_int("keyboard-jump", &keymap.jump);
	reader.read_int("keyboard-duck", &keymap.duck);
	reader.read_int("keyboard-left", &keymap.left);
	reader.read_int("keyboard-right", &keymap.right);
	reader.read_int("keyboard-fire", &keymap.fire);

	lisp_free(root_obj);
	fclose(file);
}

void saveconfig(void)
{
	/* write settings to config file */

	FILE *config = opendata(config_filename, "w");

	if (config) {
		fprintf(config, "(supertux-config\n");
		fprintf(config, "\t;; the following options can be set to #t or #f:\n");
		fprintf(config, "\t(show_fps   %s)\n", show_fps       ? "#t" : "#f");

		fprintf(config, "\t(keyboard-jump  %d)\n", keymap.jump);
		fprintf(config, "\t(keyboard-duck  %d)\n", keymap.duck);
		fprintf(config, "\t(keyboard-left  %d)\n", keymap.left);
		fprintf(config, "\t(keyboard-right %d)\n", keymap.right);
		fprintf(config, "\t(keyboard-fire  %d)\n", keymap.fire);

		fprintf(config, ")\n");

		fclose(config);
	}

}

/* EOF */
