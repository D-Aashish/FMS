#ifndef MERGER_H
#define MERGER_H

// #pragma once

#include <string>
#include <vector>
#include <fstream>

using namespace std;

class FileMerger {
private:
    string base_filename;
    int parts_count;

public:
    FileMerger(const string& base_filename, int parts_count);
    void open_part_file(ifstream& file, const string& partname);
    void create_output_file(ofstream& file, const string& filename);
    void merge_parts(const string& base_filename, int parts_count);
    void merge();

    // Public setter methods
    void setFilename(const std::string& filename);
    void setNumParts(int numParts);
};

#endif // MERGER_H
