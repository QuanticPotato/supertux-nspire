#include <iostream>
#include <fstream>
#include <string>

#include <boost/filesystem.hpp>

/* This program produce two headers files :
 * 	- An "array" file : It contains a function that map the file names (string) to the corresponding data (in the "raw file")
 * 	- A "raw data" file : It contains the data contents writen in raw arrays
 *
 * You must give the data/ folder path (At the project root)
 */

using namespace std;
using namespace boost::filesystem;

void scan_directory(path, ofstream&, ofstream&);
void create_output_array(char *, ofstream&);
void create_output_raw(char *, ofstream&);

int main(int argc, char **argv) 
{
	if(argc < 4) {
		cout << "Usage : " << endl << "\tscanner <datadir> <output_array> <output_raw>" << endl;
		return 0;
	}
	ofstream output_array;
	create_output_array(argv[2], output_array);
	if(!output_array)
		return 0;
	ofstream output_raw;
	create_output_raw(argv[3], output_raw);
	if(!output_raw) {
		output_array.close();
		return 0;
	}
	path data(argv[1]);
	try {
		if(exists(data)) {
			if(is_directory(data)) {
				scan_directory(data, output_array, output_raw);
			} else 
				cout << data << " is not a directory !" << endl;
		} else
			cout << data << " : no such file or directory !" << endl;
	} catch(const filesystem_error& e) {
		cout << "An error occured : " << e.what() << endl;
	}
	output_array << endl << "#endif" << endl;
	output_array.close();
	output_raw << endl << "#endif" << endl;
	output_raw.close();
	return 0;
}

void scan_directory(path directory, ofstream &output_array, ofstream &output_raw) 
{
	if(is_directory(directory)) {
		directory_iterator end_dir;
		for(directory_iterator dir_it(directory) ; dir_it != end_dir ; ++dir_it) {
			directory_entry entry(*dir_it);
			path entry_path(entry.path());
			if(is_directory(entry_path)) {
				scan_directory(entry_path, output_array, output_raw);
			} else
				cout << entry_path << endl;

		}
	}
}

void create_output_array(char * filepath, ofstream &output_array)
{
	output_array.open(filepath, ios::out | ios::trunc);
 
	if(!output_array) {
		cout << "Cannot open " << filepath << " ... " << endl;
		return;
	}
	output_array << "#ifndef __DATA_ARRAY__" << endl;
	output_array << "#define __DATA_ARRAY__" << endl << endl;
}

void create_output_raw(char * filepath, ofstream &output_raw)
{
	output_raw.open(filepath, ios::out | ios::trunc);
	if(!output_raw) {
		cout << "Cannot open " << filepath << " ... " << endl;
		return;
	}
	output_raw << "#ifndef __DATA_RAW__" << endl;
	output_raw << "#define __DATA_RAW__" << endl << endl;
}
