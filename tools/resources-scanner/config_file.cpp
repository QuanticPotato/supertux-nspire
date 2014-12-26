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

using namespace std;

FiletypeConfig::FiletypeConfig() :
	extension(""), type(NONE), outputFile(""), 
	useIndexing(false), outputIndexing(""),
	firstLine(true)
{}

void FiletypeConfig::write(string content, bool newLine)
{
	// We assume the file is well opened	
	(*(openedFiles[this->outputIndexing])) << content;
	if(newLine)
		(*(openedFiles[this->outputIndexing])) << endl;
}

vector<FiletypeConfig> readConfigFile(string configFile)
{
	ifstream input(configFile.c_str());
	if(!input)
		throw (string("Cannot open ") + configFile);
	vector<FiletypeConfig> files;
	string extension, line;
	while(getline(input, extension)) {
		FiletypeConfig file;
		file.extension = extension;
		if(!getLine(input, line)) break;
		file.type = parseContentType(line);
		if(file.type == NONE) {
			cout << "[WARN] Skip " << extension << " : Invalid content type !" << endl;
			 continue;
		}
		if(!getLine(input, line)) break;
		file.outputFile = line;
		if(!getLine(input, line)) break;
		file.useIndexing = parseBoolean(line);
		if(file.useIndexing) {
			if(!getLine(input, line)) break;
			file.outputIndexing = line;
			string header = parseText(input);
			openFile(file, header);
		}
		startFile(file);
		files.push_back(file);
		cout << "[INFO] Configuration saved for : ." << extension << endl;
	}
	return files;
}

map<string, FiletypeConfig> mapFileTypes(vector<FiletypeConfig> files)
{
	map<string, FiletypeConfig> fileTypes;
	for(vector<FiletypeConfig>::iterator i = files.begin() ; i != files.end() ; i++) {
		if(fileTypes.find(i->extension) == fileTypes.end()) {
		       fileTypes[i->extension] = *i;
		}	       
	}
	return fileTypes;
}

bool getLine(ifstream &file, string &line)
{
	if(! getline(file, line)) {
		cout << "[WARN] Uncomplete field !" << endl;
		return false;
	}
	return true;
}

ContentType parseContentType(string line) 
{
	if(line == "IMAGE" || line == "image" || line == "img") {
		return IMAGE;
	} else if(line == "TEXT" || line == "text" || line == "txt") {
		return TEXT;
	}
	return NONE;
}

bool parseBoolean(string line)
{
	if(line == "TRUE" || line == "True" || line == "true" || line == "1" || line == "yes")
		return true;
	return false;
}

string parseText(ifstream &file)
{
	string text = "", line;
	while(getline(file, line)) {
		if(line.back() == '\\')
			text += line.substr(0, line.size() - 1) + "\n";
		else {
			text += line;
			break;
		}
	}
	return text;
}

void openFile(FiletypeConfig file, string header)
{
	// Make sure we haven't already opened the file
	if(find(openedFileNames.begin(), openedFileNames.end(), file.outputIndexing) == openedFileNames.end()) {
		// Check whether we can access the file, and truncate it
		ofstream fileStream(file.outputIndexing.c_str(), ios::out | ios::trunc);
		if(!fileStream) {
			// Close the files and exit
			closeFiles(false);
			cout << "[ERROR] Cannot open : " << file.outputIndexing << endl;
			throw string("Exiting ..");
		}
		fileStream.close();
		openedFileNames.push_back(file.outputIndexing);
		openedFiles[file.outputIndexing] = make_shared<ofstream>(file.outputIndexing);
		string fileConstant = makeConstant(file.outputIndexing, file.extension);
		file.write(string("#ifndef ") + fileConstant, true);
		file.write(string("#define ") + fileConstant + string("\n"), true);
		file.write(header, true);
	}
}

// Escape every '/' and '-' characters (With underscores '_')
string escape_filepath(string filepath, string extension)
{
	replace(filepath.begin(), filepath.end(), '-',  '_');
	replace(filepath.begin(), filepath.end(), separator(), '_');
	// Remove the file extension (Don't forget the . !
	return filepath.substr(0, filepath.size() - extension.size() - 1);
}

string makeConstant(string filename, string extension) 
{
	locale loc;
	string escaped = escape_filepath(filename, extension);
	string constant = "__";
	// Upper case  (std::toupper)
	for(string::size_type i = 0 ; i < escaped.length() ; i++) {
		constant += toupper(escaped[i], loc);
	}
	return (constant + string("__"));
}

void startFile(FiletypeConfig file)
{
	// Write the header of the file, if it hasn't be already done.
	if(find(startedFileNames.begin(), startedFileNames.end(), file.outputFile) == startedFileNames.end()) {
		string constant = makeConstant(file.outputFile, file.extension);
		outputSystem(file.outputFile, string("#ifndef ") + constant, true);
		outputSystem(file.outputFile, string("#define ") + constant);
		outputSystem(file.outputFile, "");
		startedFileNames.push_back(file.outputFile);
	}
}

void outputSystem(string filename, string content, bool truncate)
{
	string cmd = "";
	if(truncate)
		cmd = string("echo \"") + content + string("\" > ") + filename;
	else
		cmd = string("echo \"") + content + string("\">> ") + filename;
	system(cmd.c_str());
}

void closeFiles(bool success)
{
	for(map<string, shared_ptr<ofstream>>::iterator i = openedFiles.begin() ; i != openedFiles.end() ; i++) {
		if(success) 
			(*(i->second)) << "\t return 0;" << endl << "}" << endl << endl << "#endif" << endl;
		// The file might have already been closed
		if(*(i->second))
			i->second->close();
	}
	openedFileNames.clear();
	openedFiles.clear();
	if(success) {
		for(vector<string>::iterator i = startedFileNames.begin() ; i != startedFileNames.end() ; i++) {
			outputSystem(*i, "");
			outputSystem(*i, string("#endif"));
			outputSystem(*i, "");
		}
	}
	startedFileNames.clear();
}
