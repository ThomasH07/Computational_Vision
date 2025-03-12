// Program 1 - HW2
// Author: <Thomas Huang>

//gray scale to binary 
// only 0 and 255
#include <iostream>
#include <string>

#include "image.h"
using namespace ComputerVisionProjects;

int main(int argc, char **argv){
  
  if (argc != 4) {
    std::cout << "Usage: " <<
      argv[0] << " {input_image_name} {threshold} {output_image_name}" << std::endl;
    return 0;
  }

  const std::string input_file(argv[1]);
  const int threshold = std::stoi(argv[2]);
  const std::string output_file(argv[3]);

  std::cout << "Running p1 " << input_file << " " 
            << threshold << " " << output_file << std::endl;
  //creates Image
  Image one_image;
  Image* one_ptr = &one_image;
  //read the images 
  //(Finds file type, finds width/height/read # of gray levels, reads each pixel)
  ReadImage(input_file, one_ptr);
  //one_image.SetNumberGrayLevels(255); done in ReadImage
  int rows = one_image.num_rows();
  int columns = one_image.num_columns();
  
  for (int i = 0; i < rows; ++i){ // # of rows
    for (int j = 0; j < columns; ++j){ //# of cols
      if (one_image.GetPixel(i,j) > threshold){
        one_image.SetPixel(i, j, 255);
      }else{
        one_image.SetPixel(i, j, 0);
      }
    }
  }
  //image to pgm file
  WriteImage(output_file, one_image);
}
// ./p1 images/two_objects.pgm 127 images/outputp1.pgm
// ./p1 many_objects_1.pgm 123 outputp1.pgm