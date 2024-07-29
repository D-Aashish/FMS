#include "../headers/splitter.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cstdlib>  // For atoi

using namespace std;

// Correct constructor definition
FileSplitter::FileSplitter(const string& filename, int parts_size) 
    : filename(filename), parts_size(parts_size) {
    // Constructor body can remain empty or include additional initialization if needed
}

void FileSplitter::open_file(ifstream& file, const string& filename) {
    file.open(filename.c_str(), ios::in | ios::binary);  // Use c_str() to convert to C-style string
    if (!file) {
        throw runtime_error("Error opening file: " + filename);
    }
}

int FileSplitter::get_file_length(ifstream& file) {
    file.seekg(0, ios::end);
    int length = file.tellg();
    file.seekg(0, ios::beg);
    if (length == 0) {
        throw runtime_error("The file is empty.");
    }
    return length;
}

void FileSplitter::create_part_file(ofstream& part_file, const string& partname) {
    part_file.open(partname.c_str(), ios::out | ios::binary);  // Use c_str() to convert to C-style string
    if (!part_file) {
        throw runtime_error("Error opening output file: " + partname);
    }
}

void FileSplitter::write_part(ofstream& part_file, vector<char>& buffer, int size) {
    part_file.write(&buffer[0], size);
    if (!part_file) {
        throw runtime_error("Error writing to output file.");
    }
}

void FileSplitter::split_file(ifstream& operation_file, const string& filename, int parts_size) {
    vector<char> buffer(parts_size);
    int parts_index = 0;

    while (true) {
        operation_file.read(&buffer[0], parts_size);
        int current_parts_size = operation_file.gcount();

        if (current_parts_size == 0) {
            break;
        }

        stringstream ss;
        ss << filename << "." << parts_index;
        string partname = ss.str();

        ofstream part_file;
        create_part_file(part_file, partname);
        write_part(part_file, buffer, current_parts_size);
        part_file.close();
        ++parts_index;
    }
}

void FileSplitter::split() {
    cout << "Parts size: " << parts_size << endl;

    ifstream operation_file;
    open_file(operation_file, filename);
    int length = get_file_length(operation_file);
    split_file(operation_file, filename, parts_size);
    operation_file.close();
}

void FileSplitter::setFilename(const std::string& filename) {
    this->filename = filename;
}

void FileSplitter::setPartsSize(int size) {
    this->parts_size = size;
}

int main2(int argc, char** argv) {
    try {
        // Directly pass parameters for testing
        FileSplitter splitter("test.txt", 1024);  // Example parameters
        splitter.split();
    } catch (const invalid_argument& e) {
        cerr << "Invalid argument: " << e.what() << endl;
        return 1;
    } catch (const out_of_range& e) {
        cerr << "Out of range error: " << e.what() << endl;
        return 1;
    } catch (const runtime_error& e) {
        cerr << "Runtime error: " << e.what() << endl;
        return 1;
    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        return 1;
    }

    return 0;
}
