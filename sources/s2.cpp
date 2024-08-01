#include "../headers/splitter.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cstdlib>  // For atoi

using namespace std;

FileSplitter::FileSplitter(const string& file_name, int size) 
    : fileName(file_name), partsSize(size) {
    // Constructor body can remain empty or include additional initialization if needed
}

void FileSplitter::open_file(ifstream& file_ptr, const string& file_name) {
    file_ptr.open(file_name.c_str(), ios::in | ios::binary);  // Use c_str() to convert to C-style string
    if (!file_ptr) {
        throw runtime_error("Error opening file: " + file_name);
    }
}

int FileSplitter::get_file_length(ifstream& file_ptr) {
    file_ptr.seekg(0, ios::end);
    int length = file_ptr.tellg();
    file_ptr.seekg(0, ios::beg);
    if (length == 0) {
        throw runtime_error("The file is empty.");
    }
    return length;
}

void FileSplitter::create_part_file(ofstream& part_file, const string& part_name) {
    part_file.open(part_name.c_str(), ios::out | ios::binary);  // Use c_str() to convert to C-style string
    if (!part_file) {
        throw runtime_error("Error opening output file: " + part_name);
    }
}

void FileSplitter::write_part(ofstream& part_file, vector<char>& buffer, int size) {
    part_file.write(&buffer[0], size);
    if (!part_file) {
        throw runtime_error("Error writing to output file.");
    }
}

void FileSplitter::split_file(ifstream& operation_file, const string& file_name, int parts_size) {
    vector<char> buffer(parts_size);
    int parts_index = 0;

    while (true) {
        operation_file.read(&buffer[0], parts_size);
        int current_parts_size = operation_file.gcount();

        if (current_parts_size == 0) {
            break;
        }

        stringstream ss;
        ss << file_name << "." << parts_index;
        string partname = ss.str();

        ofstream part_file;
        create_part_file(part_file, partname);
        write_part(part_file, buffer, current_parts_size);
        part_file.close();
        ++parts_index;
    }
}

void FileSplitter::split() {
    cout << "Parts size: " << partsSize << endl;

    ifstream operation_file;
    open_file(operation_file, fileName);
    int length = get_file_length(operation_file);
    split_file(operation_file, fileName, partsSize);
    operation_file.close();
}

void FileSplitter::setFilename(const std::string& file_name) {
    this->fileName = file_name;
}

void FileSplitter::setPartsSize(int size) {
    this->partsSize = size;
}
