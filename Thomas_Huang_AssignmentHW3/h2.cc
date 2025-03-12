// Program 2 - HW3
// Author: <YOUR NAME>

#include "image.h"
#include <iostream>
#include <string>

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

  std::cout << "Running h2 " << input_file << " " 
            << threshold << " " << output_file << std::endl;

            //image
  Image one_image,result;
  Image* one_ptr = &one_image;
  ReadImage(input_file, one_ptr);

  int rows = one_image.num_rows();
  int cols = one_image.num_columns();

  result.AllocateSpaceAndSetSize(rows,cols);
  result.SetNumberGrayLevels(one_image.num_gray_levels());
  // nested for loop on each pixel of the image
   for (int i = 0; i < rows; ++i){ // # of rows
    for (int j = 0; j < cols; ++j){ //# of cols
      if (one_image.GetPixel(i,j) > threshold){
        result.SetPixel(i, j, 255);
      }
    }
  }
    WriteImage(output_file,result);
    return 0;
}
/* 
./h2 outputh1.pgm 50 outputh2.pgm
*/ 
