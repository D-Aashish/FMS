#include "../headers/merger.h"

#include <iostream>
#include <fstream>
// #include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cstdlib>  // For atoi

using namespace std;

    // Filemerger::FileMerger(int argc, char** argv) {
    FileMerger::FileMerger(int argc, char** argv) {
        check_arguments(argc, argv);
        parts_count = get_parts_count(argv[2]);
        base_filename = argv[1];
    }

    void FileMerger:: check_arguments(int argc, char** argv) {
        if (argc < 3) {
            throw invalid_argument("Usage: " + string(argv[0]) + " <base_filename> <number_of_parts>");
        }
    }

    int FileMerger:: get_parts_count(const char* parts_str) {
        int count = atoi(parts_str);
        if (count <= 0) {
            throw out_of_range("Parts count must be positive.");
        }
        return count;
    }

    void FileMerger:: open_part_file(ifstream& file, const string& partname) {
        file.open(partname.c_str(), ios::in | ios::binary);
        if (!file) {
            cerr << "Debug: Failed to open file: " << partname << endl;
            throw runtime_error("Error opening file: " + partname);
        }
    }

    void FileMerger:: create_output_file(ofstream& file, const string& filename) {
        file.open(filename.c_str(), ios::out | ios::binary);
        if (!file) {
            cerr << "Debug: Failed to create output file: " << filename << endl;
            throw runtime_error("Error creating output file: " + filename);
        }
    }

    void FileMerger:: merge_parts(const string& base_filename, int parts_count) {
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
                cerr << "Debug: Error writing to output file: " << base_filename << endl;
                throw runtime_error("Error writing to output file.");
            }
            part_file.close();
        }
        output_file.close();
    }

    void FileMerger:: merge() {
        cout << "Merging " << parts_count << " parts into " << base_filename << endl;
        merge_parts(base_filename, parts_count);
    }


int main1(int argc, char** argv) {
    try {
        FileMerger merger(argc, argv);
        merger.merge();
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
