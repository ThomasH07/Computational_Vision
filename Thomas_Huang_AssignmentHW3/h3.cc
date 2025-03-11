// Program 3 - HW3
// Author: <YOUR NAME>

#include "image.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace ComputerVisionProjects;

int main(int argc, char **argv){
    if (argc != 4) {
       std::cout << "Usage: " <<
         argv[0] << " {input_binary_image_name} {output_hough_image_name} {output_hough_array_name}" << std::endl;
        return 0;
    }
    const std::string input_filenm(argv[1]);
    const std::string output_pgm_filenm(argv[2]);
    const std::string output_txt_filenm(argv[3]);

    std::cout << "Running h3: " << input_filenm << " " << output_pgm_filenm << " " << output_txt_filenm << std::endl;
    
    //first loop throug each pixel
    //get sampling size of rho and theta
    //create accumalator array with the size of the sampling rho and theta - used to hold the votes
    //loop through samping size of theta
    //compute rho from the given theta 
    //adjust the rho to the k index(the degree of each pixel) 
    // if theta is 0.5 degrees then the sampling size of rho will be bigger, 
    // increment the array based on theta, 
    //find all local maximum sych that array(y,x) > T
    //output stuff
    Image one_image;
    Image* one_ptr = &one_image;
    ReadImage(input_filenm, one_ptr);
    Image result = one_image;

    int rows = one_image.num_rows();
    int cols = one_image.num_columns();

    double rho =  sqrt(pow(rows,2) + pow(cols,2));
    double theta = (M_PI); //radians
    double delta_theta = theta/180; //radians to degree


    std::cout 
    << "rho: " << rho 
    << "\ntheta: " << theta;
    // nested for loop on each pixel of the image
    for (int y = 1; y < rows-1 ;y++){
        for (int x = 1; x < cols-1 ;x++){
            if(one_image.GetPixel(y,x) > 0){
                //for(int h = 0; h < )
            }
        }
    }
    return 0;
}
/* 
./h3 testtwo.pgm testthree.pgm textthree.txt

*/