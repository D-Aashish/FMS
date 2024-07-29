#include "headers/splitter.h"
#include "headers/merger.h"
#include "headers/udata.h"

#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [split|merge|login|signup] [args...]" << std::endl;
        return 1;
    }

    std::string command = argv[1];

    try {
        if (command == "split" && argc == 4) {
            FileSplitter splitter(argc, argv);
            splitter.split();
        } else if (command == "merge" && argc == 4) {
            FileMerger merger(argc, argv);
            merger.merge();
        } else if (command == "login" && argc == 3) {
            UserDetails user;
            ifstream infile("user_data.txt");
            if (!infile) {
                cerr << "Error opening user data file." << std::endl;
                return 1;
            }
            string stored_user, stored_pass;
            bool found = false;
            while (infile >> stored_user >> stored_pass) {
                if (user.login(stored_user, argv[2])) {
                    found = true;
                    break;
                }
            }
            infile.close();
            if (found) {
                std::cout << "Login successful." << std::endl;
            } else {
                std::cerr << "Invalid username or password." << std::endl;
                return 1;
            }
        } else if (command == "signup" && argc == 4) {
            UserDetails user;
            user.input(argv[2], argv[3]);
            ofstream outfile("user_data.txt", std::ios_base::app);
            if (!outfile) {
                cerr << "Error opening user data file." << std::endl;
                return 1;
            }
            outfile << user.store() << std::endl;
            outfile.close();
            cout << "Signup successful." << std::endl;
        } else {
            cerr << "Invalid arguments. Usage: " << argv[0] << " [split|merge|login|signup] [args...]" << std::endl;
            return 1;
        }
    } catch (const std::exception& e) {
        cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
