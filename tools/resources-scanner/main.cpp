#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

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

void scan_directory(path directory, ofstream& output_array, string output_raw, string output_string);
void create_output_array(char *, ofstream&, string output_raw);
void create_output_raw(string output_raw);
void create_output_string(string output_string);
string escape_filepath(path &filepath, string extension);

// Returns the file separator of the running OS
inline char separator() {
#ifdef __WIN32
	return '\\';
#else
	return '/';
#endif
}

// The number of characters to skip in the paths (i.e. the user specific part, such as /home ...)
int path_offset = 0;
string resource_maker_exe;
// Wether it has to write "if" of "else if"
bool firstLine = true;

int main(int argc, char **argv) 
{
	if(argc < 5) {
		cout << "Usage : " << endl << "\tscanner <datadir> <output_array> <output_raw> <output_string> [ressource-maker]" << endl;
		return 0;
	}

	resource_maker_exe = argc >= 6 ? string(argv[5]) : "resource-maker";
	// Check the exe path is valid
	string check_cmd = resource_maker_exe + " -magic_code";
	if((system(check_cmd.c_str()) >> 8) != 42) { // Don't forget the shift !!
		if(argc >= 5) cout << resource_maker_exe << " : No such executable file !"<< endl;
		else cout << "Cannot find resource-maker in PATH ! " << endl;
		return 0;
	}

	string output_raw = string(argv[3]);
	create_output_raw(output_raw);
	string output_string = string(argv[4]);
	create_output_string(output_string);
	ofstream output_array;
	create_output_array(argv[2], output_array, output_raw);
	if(!output_array)
		return 0;

	path data(argv[1]);
	path_offset = data.string().size();
	// If there is no slash at the end, we must be sure to skip it !
	if(data.string().back() != '/')
	       path_offset++;	

	try {
		if(exists(data)) {
			if(is_directory(data)) {
				scan_directory(data, output_array, output_raw, output_string);
			} else 
				cout << data << " is not a directory !" << endl;
		} else
			cout << data << " : no such file or directory !" << endl;
	} catch(const filesystem_error& e) {
		cout << "An error occured : " << e.what() << endl;
	}

	output_array << "\treturn 0;" << endl << "}" << endl;
	output_array.close();
	system(((string)("echo >> " + output_raw)).c_str());
	system(((string)("echo \"#endif\" >> " + output_raw)).c_str());
	system(((string)("echo >> " + output_string)).c_str());
	system(((string)("echo \"#endif\" >> " + output_string)).c_str());
	return 0;
}

void scan_directory(path directory, ofstream &output_array, string output_raw, string output_string) 
{
	if(is_directory(directory)) {
		cout << "Scanning   " << directory << "  ... " << endl;
		directory_iterator end_dir;
		for(directory_iterator dir_it(directory) ; dir_it != end_dir ; ++dir_it) {
			directory_entry entry(*dir_it);
			path entry_path(entry.path());
			if(is_directory(entry_path)) {
				scan_directory(entry_path, output_array, output_raw, output_string);
			} else {
				try {
				// The file type detection is based on the filename extension
					string fileExtension = entry_path.extension().string().substr(1);
					string label = escape_filepath(entry_path, fileExtension);
					if(fileExtension == "png") { // Image formats supported
						string img_cmd = resource_maker_exe + " img " + entry_path.string() + " " + label + " >> " + output_raw; 
						cout << "Proccess " << entry_path.filename() << endl;
						system(img_cmd.c_str());

						output_array << "\t" + (firstLine ? string("if") : string("else if"));
						firstLine = false;
						output_array << "(file == \"" << "data/" << entry_path.string().substr(path_offset) << "\")" << endl;
						output_array << "\t\treturn " << label << ";" << endl;
					} else if(fileExtension == "txt" || fileExtension == "strf") { // Text formats supported
						label += "_" + fileExtension;
						string txt_cmd = resource_maker_exe + " txt " + entry_path.string() + " " + label + " >> " + output_string;
						cout << "Proccess " << entry_path.filename() << endl;
						system(txt_cmd.c_str());
					}
				} catch(out_of_range) {
					// If the file has no extension ...
				}
			}

		}
	}
}

void create_output_array(char * filepath, ofstream &output_array, string output_raw)
{
	output_array.open(filepath, ios::out | ios::trunc);
	if(!output_array) {
		cout << "Cannot open " << filepath << " ... " << endl;
		return;
	}
	// TODO : Parametrizable header filename !
	output_array << "#include \"data_manager.h\"" << endl << endl << endl;
	output_array << "unsigned short *getSpriteData(const std::string &file)" << endl << "{" << endl;
}

void create_output_raw(string output_raw)
{
	// We use the system pipes to avoid concurency problems ..
	// This line truncate the file if it already exists
	system(((string)("echo \"#ifndef __DATA_RAW__\" > " + output_raw)).c_str()); 
	system(((string)("echo \"#define __DATA_RAW__\" >> " + output_raw)).c_str());
	// Append two newlines
	system(((string)("echo >> " + output_raw)).c_str());
	system(((string)("echo >> " + output_raw)).c_str());
}

void create_output_string(string output_string)
{
	// We use the system pipes to avoid concurency problems ..
	// This line truncate the file if it already exists
	system(((string)("echo \"#ifndef __DATA_STRING__\" > " + output_string)).c_str()); 
	system(((string)("echo \"#define __DATA_STRING__\" >> " + output_string)).c_str());
	// Append two newlines
	system(((string)("echo >> " + output_string)).c_str());
	system(((string)("echo >> " + output_string)).c_str());
}

// Use the path_offset to only keep the relevant part.
// Escape every '/' and '-' characters (With underscores '_')
string escape_filepath(path &filepath, string extension)
{
	string escaped = filepath.string().substr(path_offset);
	replace(escaped.begin(), escaped.end(), '-',  '_');
	replace(escaped.begin(), escaped.end(), separator(), '_');
	// Remove the file extension (Don't forget the . !
	return escaped.substr(0, escaped.size() - extension.size() - 1);
}
