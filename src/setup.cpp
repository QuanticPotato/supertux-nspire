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

#include "setup.h"
#include "globals.h"
#include "gameloop.h"

/* Screen proprities: */
/* Don't use this to test for the actual screen sizes. Use screen->w/h
 * instead! */
#define SCREEN_W 320
#define SCREEN_H 240

/* Does the given file exist and is it accessible? */
int faccessible(const char *filename)
{
	struct stat filestat;
	if (stat(filename, &filestat) == -1)
		return false;
	else {
		if (S_ISREG(filestat.st_mode))
			return true;
		else
			return false;
	}
}

/* Can we write to this location? */
int fwriteable(const char *filename)
{
	FILE *fi;
	fi = fopen(filename, "wa");
	if (fi == NULL)
		return false;
	fclose(fi);
	return true;
}

/* Makes sure a directory is created in either the SuperTux home directory or
 * the SuperTux base directory.*/
int fcreatedir(const char *relative_dir)
{
	char path[1024];
	snprintf(path, 1024, "%s/%s/", st_dir, relative_dir);
	if (mkdir(path, 0755) != 0) {
		snprintf(path, 1024, "%s/%s/", datadir.c_str(), relative_dir);
		if (mkdir(path, 0755) != 0)
			return false;
		else
			return true;
	} else
		return true;
}

FILE *opendata(const char *rel_filename, const char *mode)
{
	char *filename = NULL;
	FILE *fi;

	filename = (char *) malloc(sizeof(char) * (strlen(st_dir) +
	                           strlen(rel_filename) + 1));

	strcpy(filename, st_dir);
	/* Open the high score file: */

	strcat(filename, rel_filename);

	/* Try opening the file: */
	fi = fopen(filename, mode);

	if (fi == NULL) {
		fprintf(stderr, "Warning: Unable to open the file \"%s\" ", filename);

		if (strcmp(mode, "r") == 0)
			fprintf(stderr, "for read!!!\n");
		else if (strcmp(mode, "w") == 0)
			fprintf(stderr, "for write!!!\n");
	}
	free(filename);

	return (fi);
}

/* Get all names of sub-directories in a certain directory. */
/* Returns the number of sub-directories found. */
/* Note: The user has to free the allocated space. */
string_list_type dsubdirs(const char *rel_path, const char *expected_file)
{
	DIR *dirStructP;
	struct dirent *direntp;
	string_list_type sdirs;
	char filename[1024];
	char path[1024];

	string_list_init(&sdirs);
	sprintf(path, "%s/%s", st_dir, rel_path);
	if ((dirStructP = opendir(path)) != NULL) {
		while ((direntp = readdir(dirStructP)) != NULL) {
			char absolute_filename[1024];
			struct stat buf;

			sprintf(absolute_filename, "%s/%s", path, direntp->d_name);

			if (stat(absolute_filename, &buf) == 0 && S_ISDIR(buf.st_mode)) {
				if (expected_file != NULL) {
					sprintf(filename, "%s/%s/%s", path, direntp->d_name, expected_file);
					if (!faccessible(filename))
						continue;
				}

				string_list_add_item(&sdirs, direntp->d_name);
			}
		}
		closedir(dirStructP);
	}

	sprintf(path, "%s/%s", datadir.c_str(), rel_path);
	if ((dirStructP = opendir(path)) != NULL) {
		while ((direntp = readdir(dirStructP)) != NULL) {
			char absolute_filename[1024];
			struct stat buf;

			sprintf(absolute_filename, "%s/%s", path, direntp->d_name);

			if (stat(absolute_filename, &buf) == 0 && S_ISDIR(buf.st_mode)) {
				if (expected_file != NULL) {
					sprintf(filename, "%s/%s/%s", path, direntp->d_name, expected_file);
					if (!faccessible(filename))
						continue;
					else {
						sprintf(filename, "%s/%s/%s/%s", st_dir, rel_path, direntp->d_name,
						        expected_file);
						if (faccessible(filename))
							continue;
					}
				}

				string_list_add_item(&sdirs, direntp->d_name);
			}
		}
		closedir(dirStructP);
	}

	return sdirs;
}

string_list_type dfiles(const char *rel_path, const char *glob,
                        const char *exception_str)
{
	DIR *dirStructP;
	struct dirent *direntp;
	string_list_type sdirs;
	char path[1024];

	string_list_init(&sdirs);
	sprintf(path, "%s/%s", st_dir, rel_path);
	if ((dirStructP = opendir(path)) != NULL) {
		while ((direntp = readdir(dirStructP)) != NULL) {
			char absolute_filename[1024];
			struct stat buf;

			sprintf(absolute_filename, "%s/%s", path, direntp->d_name);

			if (stat(absolute_filename, &buf) == 0 && S_ISREG(buf.st_mode)) {
				if (exception_str != NULL) {
					if (strstr(direntp->d_name, exception_str) != NULL)
						continue;
				}
				if (glob != NULL)
					if (strstr(direntp->d_name, glob) == NULL)
						continue;

				string_list_add_item(&sdirs, direntp->d_name);
			}
		}
		closedir(dirStructP);
	}

	sprintf(path, "%s/%s", datadir.c_str(), rel_path);
	if ((dirStructP = opendir(path)) != NULL) {
		while ((direntp = readdir(dirStructP)) != NULL) {
			char absolute_filename[1024];
			struct stat buf;

			sprintf(absolute_filename, "%s/%s", path, direntp->d_name);

			if (stat(absolute_filename, &buf) == 0 && S_ISREG(buf.st_mode)) {
				if (exception_str != NULL) {
					if (strstr(direntp->d_name, exception_str) != NULL)
						continue;
				}
				if (glob != NULL)
					if (strstr(direntp->d_name, glob) == NULL)
						continue;

				string_list_add_item(&sdirs, direntp->d_name);
			}
		}
		closedir(dirStructP);
	}

	return sdirs;
}

void free_strings(char **strings, int num)
{
	int i;
	for (i = 0; i < num; ++i)
		free(strings[i]);
}

/* --- SETUP --- */
/* Set SuperTux configuration and save directories */
void st_directory_setup(void)
{
	char str[1024];

	/* For now, use the current directory (i.e. ".") */
	st_dir = (char *) malloc(sizeof(char) * (strlen(SUPERTUX_DIRECTORY + 1)));
	strcpy(st_dir, SUPERTUX_DIRECTORY);

	st_save_dir = (char *) malloc(sizeof(char) * (strlen(st_dir) + strlen("/save") +
	                              1));

	strcpy(st_save_dir, st_dir);
	strcat(st_save_dir, "/save");

	/* Create them. In the case they exist they won't destroy anything. */
	mkdir(st_dir, 0755);
	mkdir(st_save_dir, 0755);

	sprintf(str, "%s/levels", st_dir);
	mkdir(str, 0755);

	// User has not that a datadir, so we try some magic
	if (datadir.empty())
		datadir = "data";
}

/* Create and setup menus. */
void st_menu(void)
{
	DEBUG_START("Setup menu", 0);
	main_menu      = new Menu();
	options_menu   = new Menu();
	options_keys_menu     = new Menu();
	options_joystick_menu = new Menu();
	load_game_menu = new Menu();
	save_game_menu = new Menu();
	game_menu      = new Menu();
	highscore_menu = new Menu();
	contrib_menu   = new Menu();
	contrib_subset_menu   = new Menu();
	worldmap_menu  = new Menu();

	main_menu->set_pos(screen->w / 2, 150);
	main_menu->additem(MN_GOTO, "Start Game", 0, load_game_menu, MNID_STARTGAME);
	main_menu->additem(MN_GOTO, "Bonus Levels", 0, contrib_menu, MNID_CONTRIB);
	main_menu->additem(MN_GOTO, "Options", 0, options_menu, MNID_OPTIONMENU);
	main_menu->additem(MN_ACTION, "Credits", 0, 0, MNID_CREDITS);
	main_menu->additem(MN_ACTION, "Quit", 0, 0, MNID_QUITMAINMENU);

	options_menu->additem(MN_LABEL, "Options", 0, 0);
	options_menu->additem(MN_HL, "", 0, 0);
	options_menu->additem(MN_TOGGLE, "Show FPS  ", show_fps, 0, MNID_SHOWFPS);
	options_menu->additem(MN_GOTO, "Keyboard Setup", 0, options_keys_menu);
	options_menu->additem(MN_HL, "", 0, 0);
	options_menu->additem(MN_BACK, "Back", 0, 0);

	options_keys_menu->additem(MN_LABEL, "Key Setup", 0, 0);
	options_keys_menu->additem(MN_HL, "", 0, 0);
	/** TODO 
	options_keys_menu->additem(MN_CONTROLFIELD, "Left move", 0, 0, 0, &keymap.left);
	options_keys_menu->additem(MN_CONTROLFIELD, "Right move", 0, 0, 0,
	                           &keymap.right);
	options_keys_menu->additem(MN_CONTROLFIELD, "Jump", 0, 0, 0, &keymap.jump);
	options_keys_menu->additem(MN_CONTROLFIELD, "Duck", 0, 0, 0, &keymap.duck);
	options_keys_menu->additem(MN_CONTROLFIELD, "Power/Run", 0, 0, 0, &keymap.fire);
	options_keys_menu->additem(MN_HL, "", 0, 0);
	options_keys_menu->additem(MN_BACK, "Back", 0, 0);*/

	load_game_menu->additem(MN_LABEL, "Start Game", 0, 0);
	load_game_menu->additem(MN_HL, "", 0, 0);
	load_game_menu->additem(MN_DEACTIVE, "Slot 1", 0, 0, 1);
	load_game_menu->additem(MN_DEACTIVE, "Slot 2", 0, 0, 2);
	load_game_menu->additem(MN_DEACTIVE, "Slot 3", 0, 0, 3);
	load_game_menu->additem(MN_DEACTIVE, "Slot 4", 0, 0, 4);
	load_game_menu->additem(MN_DEACTIVE, "Slot 5", 0, 0, 5);
	load_game_menu->additem(MN_HL, "", 0, 0);
	load_game_menu->additem(MN_BACK, "Back", 0, 0);

	save_game_menu->additem(MN_LABEL, "Save Game", 0, 0);
	save_game_menu->additem(MN_HL, "", 0, 0);
	save_game_menu->additem(MN_DEACTIVE, "Slot 1", 0, 0, 1);
	save_game_menu->additem(MN_DEACTIVE, "Slot 2", 0, 0, 2);
	save_game_menu->additem(MN_DEACTIVE, "Slot 3", 0, 0, 3);
	save_game_menu->additem(MN_DEACTIVE, "Slot 4", 0, 0, 4);
	save_game_menu->additem(MN_DEACTIVE, "Slot 5", 0, 0, 5);
	save_game_menu->additem(MN_HL, "", 0, 0);
	save_game_menu->additem(MN_BACK, "Back", 0, 0);

	game_menu->additem(MN_LABEL, "Pause", 0, 0);
	game_menu->additem(MN_HL, "", 0, 0);
	game_menu->additem(MN_ACTION, "Continue", 0, 0, MNID_CONTINUE);
	game_menu->additem(MN_GOTO, "Options", 0, options_menu);
	game_menu->additem(MN_HL, "", 0, 0);
	game_menu->additem(MN_ACTION, "Abort Level", 0, 0, MNID_ABORTLEVEL);

	worldmap_menu->additem(MN_LABEL, "Pause", 0, 0);
	worldmap_menu->additem(MN_HL, "", 0, 0);
	worldmap_menu->additem(MN_ACTION, "Continue", 0, 0, MNID_RETURNWORLDMAP);
	worldmap_menu->additem(MN_GOTO, "Options", 0, options_menu);
	worldmap_menu->additem(MN_HL, "", 0, 0);
	worldmap_menu->additem(MN_ACTION, "Quit Game", 0, 0, MNID_QUITWORLDMAP);

	highscore_menu->additem(MN_TEXTFIELD, "Enter your name:", 0, 0);

	DEBUG_DONE()
}

void update_load_save_game_menu(Menu *pmenu)
{
	for (int i = 2; i < 7; ++i) {
		// FIXME: Insert a real savegame struct/class here instead of
		// doing string vodoo
		std::string tmp = slotinfo(i - 1);
		pmenu->item[i].kind = MN_ACTION;
		pmenu->item[i].change_text(tmp.c_str());
	}
}

bool process_load_game_menu()
{
	int slot = load_game_menu->check();

	if (slot != -1 && load_game_menu->get_item_by_id(slot).kind == MN_ACTION) {
		char slotfile[1024];
		snprintf(slotfile, 1024, "%s/slot%d.stsg", st_save_dir, slot);

		if (access(slotfile, F_OK) != 0)
			draw_intro();

		fadeout();
		WorldMapNS::WorldMap worldmap;

		//TODO: Define the circumstances under which BonusIsland is chosen
		worldmap.set_map_file("world1.stwm");
		worldmap.load_map();

		// Load the game or at least set the savegame_file variable
		worldmap.loadgame(slotfile);

		worldmap.display();

		Menu::set_current(main_menu);

		st_pause_ticks_stop();
		return true;
	} else
		return false;
}

/* Handle changes made to global settings in the options menu. */
void process_options_menu(void)
{
	switch (options_menu->check()) {
		case MNID_SHOWFPS:
			if (show_fps != options_menu->isToggled(MNID_SHOWFPS))
				show_fps = !show_fps;
			break;
	}
}

void st_general_setup(void)
{
	/* Seed random number generator: */
	srand(SDL_GetTicks());

	/* Unicode needed for input handling: */
	SDL_EnableUNICODE(1);

	DEBUG_MSG("Load letter bitmaps ..");
	/* Load global images: */
	black_text  = new Text(datadir + "/images/status/letters-black.png", TEXT_TEXT, 16, 18);
	gold_text    = new Text(datadir + "/images/status/letters-gold.png", TEXT_TEXT, 16, 18);
	silver_text = new Text(datadir + "/images/status/letters-silver.png", TEXT_TEXT, 16, 18);
	blue_text    = new Text(datadir + "/images/status/letters-blue.png", TEXT_TEXT, 16, 18);
	red_text        = new Text(datadir + "/images/status/letters-red.png", TEXT_TEXT, 16, 18);
	green_text  = new Text(datadir + "/images/status/letters-green.png", TEXT_TEXT, 16, 18);
	white_text  = new Text(datadir + "/images/status/letters-white.png", TEXT_TEXT, 16, 18);
	white_small_text = new Text(datadir + "/images/status/letters-white-small.png", TEXT_TEXT, 8, 9);
	white_big_text   = new Text(datadir + "/images/status/letters-white-big.png", TEXT_TEXT, 20, 22);
	yellow_nums = new Text(datadir + "/images/status/numbers.png", TEXT_NUM, 32,32);

	/* Load GUI/menu images: */
	checkbox = new Surface(datadir + "/images/status/checkbox.png", USE_ALPHA);
	checkbox_checked = new Surface(datadir + "/images/status/checkbox-checked.png",
	                               USE_ALPHA);
	back = new Surface(datadir + "/images/status/back.png", USE_ALPHA);
	arrow_left = new Surface(datadir + "/images/icons/left.png", USE_ALPHA);
	arrow_right = new Surface(datadir + "/images/icons/right.png", USE_ALPHA);
	DEBUG_MSG("DONE")
}

void st_general_free(void)
{

	/* Free global images: */
	delete black_text;
	delete gold_text;
	delete silver_text;
	delete white_text;
	delete blue_text;
	delete red_text;
	delete green_text;
	delete white_small_text;
	delete white_big_text;
	delete yellow_nums;

	/* Free GUI/menu images: */
	delete checkbox;
	delete checkbox_checked;
	delete back;
	delete arrow_left;
	delete arrow_right;

	/* Free menus */
	delete main_menu;
	delete game_menu;
	delete options_menu;
	delete highscore_menu;
	delete save_game_menu;
	delete load_game_menu;
}

void st_video_setup(void)
{
	/* Init SDL Video: */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr,
		        "\nError: I could not initialize video!\n"
		        "The Simple DirectMedia error that occured was:\n"
		        "%s\n\n", SDL_GetError());
		exit(1);
	}

	st_video_setup_sdl();

	Surface::reload_all();

	/* Set window manager stuff: */
	//SDL_WM_SetCaption("SuperTux " VERSION, "SuperTux");
}

void st_video_setup_sdl(void)
{
	DEBUG_START("SDL : SetVideoMode", 0);
	screen = SDL_SetVideoMode(320 , 240 , 16 , SDL_SWSURFACE);

	if (screen == NULL) {
		fprintf(stderr,
		        "\nError: I could not set up video for 640x480 mode.\n"
		        "The Simple DirectMedia error that occured was:\n"
		        "%s\n\n", SDL_GetError());
		exit(1);
	}
	DEBUG_DONE()
}

/* --- SHUTDOWN --- */

void st_shutdown(void)
{
	SDL_Quit();
	saveconfig();
}

/* --- ABORT! --- */

void st_abort(const std::string &reason, const std::string &details)
{
	DEBUG_ERR3("%s : \n        %s\n", reason.c_str(), details.c_str())
	st_shutdown();
	abort();
}

/* Parse command-line arguments: */

void parseargs(int argc, char *argv[])
{
	enable_relative_paths(argv);

	loadconfig();
}

