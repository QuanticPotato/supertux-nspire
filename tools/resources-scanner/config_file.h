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

#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <locale>
#include <map>

typedef enum { NONE, IMAGE, TEXT } ContentType;

class FiletypeConfig {
	public:
		FiletypeConfig();
		std::string extension;
		ContentType type;
		std::string outputFile;
		bool useIndexing;
		std::string outputIndexing;
		bool firstLine;

		// Write in the index file
		void write(std::string content, bool newLine = false);
};

// Read the configuration file given in the command line
std::vector<FiletypeConfig> readConfigFile(std::string configFile);
// Map the FiletypeConfig with their extensions, and drop the duplicates
std::map<std::string, FiletypeConfig> mapFileTypes(std::vector<FiletypeConfig> files);
bool getLine(std::ifstream &file, std::string &line);

ContentType parseContentType(std::string line);
bool parseBoolean(std::string line);
std::string parseText(std::ifstream &file);

void openFile(FiletypeConfig file, std::string header);
void startFile(FiletypeConfig file);
void closeFiles(bool success);
void outputSystem(std::string filename, std::string content, bool truncate = false);

// Create a preprocessor-like constant from a filename
// For example :  data_manager.h => __DATA_MANAGER__
std::string makeConstant(std::string filename, std::string extension);
// Escape the '-' and the newlines
std::string escape_filepath(std::string filepath, std::string extension);

// Rawdata files
static std::vector<std::string> startedFileNames;

// Indexing files
static std::vector<std::string> openedFileNames;
static std::map<std::string, std::shared_ptr<std::ofstream> > openedFiles;

// Returns the file separator of the running OS
inline char separator() {
#ifdef __WIN32
	return '\\';
#else
	return '/';
#endif
}


