// Program 1 - HW3
// Author: Thomas Huang

#include "image.h"
#include <iostream>
#include <unordered_map>
#include <cmath>
using namespace ComputerVisionProjects;

// Since the Laplacian requires you to find zero–crossings in the image, you should choose to use
// the squared gradient operator. The convolution masks proposed by Sobel should work
// reasonably well. Else, try your favorite masks. 
//squared gradiant sobel 3x3
// col = x, row = y
int main(int argc, char **argv){
  if (argc != 3) {
    std::cout << "Usage: " <<
      argv[0] << " {input_image_name} {output_edge_image_name}" << std::endl;
      return 0;
  }

  const std::string input_file(argv[1]);
  const std::string output_file(argv[2]);

  std::cout << "Running h1 " << input_file << " " << output_file << std::endl;
  
  //image
  Image one_image;
  Image* one_ptr = &one_image;
  ReadImage(input_file, one_ptr);
  Image result = one_image;
  //
  int xsobel[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
  int ysobel[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};

  int rows = one_image.num_rows();
  int cols = one_image.num_columns();
  
  // nested for loop on each pixel of the image
  for (int y = 1; y < rows-1 ;y++){
    for (int x = 1; x < cols-1 ;x++){
      // sums from applying the sobel to the pixel
      int xsum = 0;
      int ysum = 0;

      // discrete Convolution
      for (int ky = 0; ky < 3; ky++) {
        for (int kx = 0; kx < 3; kx++) {
          // getting the nearby neighbors of the pixel
          int imageY = y + ky - 1;
          int imageX = x + kx - 1;
          // adds the sums of the pixel with the sobel
          xsum += one_image.GetPixel(imageY,imageX) * xsobel[ky][kx];
          ysum += one_image.GetPixel(imageY,imageX) * ysobel[ky][kx]; 
        }
      }

      //calculate the magnitude with the sobel of x and y
      int magnitude = sqrt(xsum * xsum + ysum * ysum);
      result.SetPixel(y, x, magnitude);

    }
  }
  // for(int i = 0 ;i < rows; i++){
  //   for(int j = 0;j < cols; j++){
  //     std::cout << result.GetPixel(i,j) << " " ;
  //   }
  // }
    WriteImage(output_file,result);
    return 0;
}
/* 
./h1 hough_simple_1.pgm testone.pgm
./h1 hough_simple_2.pgm testone.pgm
./h1 hough_complex_1.pgm testone.pgm
*/