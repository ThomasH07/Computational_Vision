// Program 4 - HW2 OPTIONAL
// Author: <Thomas Huang>

#include <iostream>
#include <string>

#include "image.h"
using namespace ComputerVisionProjects;

int main(int argc, char **argv){
  if (argc!=4) {
    std::cout << "Usage: " <<
      argv[0] << " {input_image_name} {input descriptions} {output_image_name}" << std::endl;
    return 0;
  }
  const std::string input_file(argv[1]);
  const std::string input_object_descriptions(argv[2]);
  const std::string output_file(argv[3]);

  std::cout << "Running p4 " << input_file << " " 
            << input_object_descriptions << " " << output_file << std::endl;

  return 0;
}
