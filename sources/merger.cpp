#include "../headers/merger.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cstdlib>  // For atoi

using namespace std;

FileMerger::FileMerger(const string& base_filename, int parts_count) 
    : base_filename(base_filename), parts_count(parts_count) {
}

void FileMerger::open_part_file(ifstream& file, const string& partname) {
    file.open(partname.c_str(), ios::in | ios::binary);
    if (!file) {
        cerr << "Failed to open file: " << partname << endl;
        throw runtime_error("Error opening file: " + partname);
    }
}

void FileMerger::create_output_file(ofstream& file, const string& filename) {
    file.open(filename.c_str(), ios::out | ios::binary);
    if (!file) {
        cerr << "Failed to create output file: " << filename << endl;
        throw runtime_error("Error creating output file: " + filename);
    }
}

void FileMerger::merge_parts(const string& base_filename, int parts_count) {
    ofstream output_file;
    create_output_file(output_file, base_filename);

    for (int i = 0; i < parts_count; ++i) {
        stringstream ss;
        ss << base_filename << "." << i;
        string partname = ss.str();
        
        cout << "Trying to open part file: " << partname << endl;

        ifstream part_file;
        open_part_file(part_file, partname);
        
        vector<char> buffer((istreambuf_iterator<char>(part_file)), istreambuf_iterator<char>());
        output_file.write(&buffer[0], buffer.size());
        if (!output_file) {
            cerr << "Error writing to output file: " << base_filename << endl;
            throw runtime_error("Error writing to output file.");
        }
        part_file.close();
    }
    output_file.close();
}

void FileMerger::merge() {
    cout << "Merging " << parts_count << " parts into " << base_filename << endl;
    merge_parts(base_filename, parts_count);
}

void FileMerger::setFilename(const std::string& filename) {
    this->base_filename = filename;
}

void FileMerger::setNumParts(int numParts) {
    this->parts_count = numParts;
}

