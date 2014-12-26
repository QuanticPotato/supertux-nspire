//  resource-scanner
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

#include "config_file.h"

#include <boost/filesystem.hpp>

/* This program produce two headers files :
 * 	- An "array" file : It contains a function that map the file names (string) to the corresponding data (in the "raw file")
 * 	- A "raw data" file : It contains the data contents writen in raw arrays
 * 	- A "string" file : It contains every text-file content in strings
 *
 * You must give the data/ folder path (At the project root)
 *
 * If there is no "resoure-maker" in the PATH, you must give it in the last parameter.
 *
 */

using namespace std;
using namespace boost::filesystem;

void scan_directory(path directory, map<string, FiletypeConfig> files);
string make_label(path &filepath, string extension);

// The number of characters to skip in the paths (i.e. the user specific part, such as /home ...)
int path_offset = 0;
string resource_maker_exe;
// Wether it has to write "if" of "else if"

int main(int argc, char **argv) 
{
	if(argc < 3) {
		cout << "Usage : " << endl << "\tscanner <datadir> <configFile> [ressource-maker]" << endl;
		return 0;
	}

	vector<FiletypeConfig> config;
	try {
		config = readConfigFile(string(argv[2]));
	} catch(string error) {
		cout << "[ERROR] " << error <<  endl;
		return 0;
	}
	map<string, FiletypeConfig> fileTypes = mapFileTypes(config);

	resource_maker_exe = argc >= 4 ? string(argv[3]) : "resource-maker";
	// Check the exe path is valid
	string check_cmd = resource_maker_exe + " -magic_code";
	if((system(check_cmd.c_str()) >> 8) != 42) { // Don't forget the shift !!
		if(argc >= 5) cout << resource_maker_exe << " : No such executable file !"<< endl;
		else cout << "Cannot find resource-maker in PATH ! " << endl;
		return 0;
	}
	
	path data(argv[1]);
	path_offset = data.string().size();
	// If there is no slash at the end, we must be sure to skip it !
	if(data.string().back() != '/')
	       path_offset++;	

	try {
		if(exists(data)) {
			if(is_directory(data)) {
				scan_directory(data, fileTypes);
			} else 
				cout << data << " is not a directory !" << endl;
		} else
			cout << data << " : no such file or directory !" << endl;
	} catch(const filesystem_error& e) {
		cout << "An error occured : " << e.what() << endl;
	}
	
	closeFiles(true);
	return 0;
}

void scan_directory(path directory, map<string, FiletypeConfig> files)
{
	if(is_directory(directory)) {
		cout << "Scanning   " << directory << "  ... " << endl;
		directory_iterator end_dir;
		for(directory_iterator dir_it(directory) ; dir_it != end_dir ; ++dir_it) {
			directory_entry entry(*dir_it);
			path entry_path(entry.path());
			if(is_directory(entry_path)) {
				scan_directory(entry_path, files);
			} else {
				try {
					cout << "Proccess " << entry_path.filename() << endl;
					// The file type detection is based on the filename extension
					string fileExtension = entry_path.extension().string().substr(1);
					map<string, FiletypeConfig>::iterator fileIt = files.find(fileExtension);
					if(fileIt != files.end()) {
						FiletypeConfig file = fileIt->second;
						string label = make_label(entry_path, fileExtension);
						if(file.type == IMAGE) { // Image format
							string img_cmd = resource_maker_exe + " img " + entry_path.string() + " " + label + " >> " + file.outputFile; 
							system(img_cmd.c_str());
						} else if(file.type == TEXT) { // Text formats
							label = label + "_" + fileExtension;
							string txt_cmd = resource_maker_exe + " txt " + entry_path.string() + " " + label + " >> " + file.outputFile;
							system(txt_cmd.c_str());
							label = "file_" + label;
						}
						if(file.useIndexing) {
							file.write(string("\t") + (file.firstLine ? string("if") : string("else if")));
							file.firstLine = false;
							file.write(string("(file == \"data/") + entry_path.string().substr(path_offset) + string("\")"), true);
							file.write(string("\t\treturn ") + label + string(";"), true);
						}
					}
				} catch(out_of_range) {
					// If the file has no extension ...
				}
			}

		}
	}
}

// Use the path offset to only keep the relevant part.
string make_label(path &filepath, string extension)
{
	string relevant = filepath.string().substr(path_offset);
	return escape_filepath(relevant, extension);
}


