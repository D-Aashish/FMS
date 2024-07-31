#ifndef SPLITTER_H
#define SPLITTER_H

#pragma once

#include <string>
#include <vector>
#include <fstream>

using namespace std;

class FileSplitter {
private:
    string fileName;
    int partsSize;

public:
    FileSplitter(const string& filename, int parts_size);  // Updated constructor
    void check_arguments(int argc, char** argv);
    int get_parts_size(const char* parts_str);
    void open_file(ifstream& file, const string& filename);
    int get_file_length(ifstream& file);
    void create_part_file(ofstream& part_file, const string& partname);
    void write_part(ofstream& part_file, vector<char>& buffer, int size);
    void split_file(ifstream& operation_file, const string& filename, int parts_size);
    void split();

    // Public setter methods
    void setFilename(const std::string& filename);
    void setPartsSize(int size);
};

#endif
