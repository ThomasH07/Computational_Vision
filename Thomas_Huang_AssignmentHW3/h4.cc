// Program 4 - HW3
// Author: <YOUR NAME>

#include <iostream>
#include <string>

#include "image.h"
#include "DisjSets.h"
using namespace ComputerVisionProjects;

int main(int argc, char **argv){
    if (argc != 5) {
      std::cout << " Usage: " <<
        argv[0] << " input_image input_hough_array input_threshold output_line_image" << std::endl;
      return 0;
    }
    const std::string input_filenm(argv[1]);
    const std::string input_array_filenm(argv[2]);
    const int threshold = std::stoi(argv[3]);
    const std::string output_line_filenm(argv[4]);

    std::cout << "Running h4: " << input_filenm << " " << input_array_filenm << " " << threshold
              << "  " << output_line_filenm << std::endl;

    return 0;
}
