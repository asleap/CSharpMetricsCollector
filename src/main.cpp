//
// Created by Timofey Lysenko on 05.10.16.
//

#include <iostream>
#include <cstdlib>
#include <cstring>

#include "MetricsDriver.hpp"

using namespace std;

int main(const int argc, const char **argv)
{
    // Check for the right number of arguments
    if (argc == 2) {
        Metrics::MetricsDriver driver;

        if (strncmp(argv[1], "-o", 2) == 0) { // Example for piping input from terminal, i.e., using cat
            driver.parse(std::cin);
        }
        else if (strncmp(argv[1], "-h", 2) == 0) { // Simple help menu
            cout << "Use -o for pipe to std::cin" << endl;
            cout << "Just give a filename to count from a file" << endl;
            cout << "Use -h to get this menu" << endl;
            return (EXIT_SUCCESS);
        }
        else { // Example of reading input from a file
            // Assume file, prod code, use stat to check
            driver.parse(argv[1]);
        }
        cout << driver << endl;
    }
    else {
        // Exit with failure
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}