#include "setup.h"

int main(int argc, char *argv[]) 
{
	st_directory_setup();
	parseargs(argc, argv);

	st_video_setup();
	st_general_setup();
	st_menu();

	return 0;
}
