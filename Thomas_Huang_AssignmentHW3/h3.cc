// Program 3 - HW3
// Author: <YOUR NAME>

#include "image.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
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
    Image result;

    int rows = one_image.num_rows();
    int cols = one_image.num_columns();

    result.SetNumberGrayLevels(one_image.num_gray_levels());


    // rho takes values from 0 to sqrt(M^2 + N^2)
    double r = sqrt((rows*rows) + (cols*cols));
    // delta rho - the amount of steps
    double r_steps = 1;
    double t_steps = 1;
    // number of samples (T) for Rho
    // accounting for negatives
    int r_bins = round(r / r_steps);
    // number of samples (R) for Theta
    int t_bins = round(180/t_steps);

    // accumulator array
    std::vector<std::vector<int>> accumulator(t_bins, std::vector<int>(r_bins, 0));

    result.AllocateSpaceAndSetSize(t_bins,r_bins);
    // std::cout << "R: " << r << "\nT: " << t_bins;

    // nested for loop on each pixel of the image
    for (int y = 0; y < rows ;y++){
        for (int x = 0; x < cols ;x++){
            if(one_image.GetPixel(y,x) > 0){
                for(int h = 0; h < t_bins;h++){    
                    // h * pi / 180 = h * delta theta
                    double theta = (h*t_steps)*(M_PI/180);
                    // compute rho
                    double rho = y*cos(theta)+ x*sin(theta);
                    // finding K
                    double k = round(rho/r_steps);
                    // increment accumulator
                    if (k >= 0 && k < r_bins) {
                        accumulator[h][k]++;  // Increment accumulator
                    }
                }
            }
        }
    }
    //the output text file, for the accumulator array
    std::string output;
    
    std::ofstream outputfile(output_txt_filenm);
    if (!outputfile.is_open()){
        std::cerr << "Can't open file " << std::endl;
        return 0;
    }
    output +=  std::to_string(t_bins) +  '\n';
    output += std::to_string(r_bins) + '\n';
    for(int y = 0; y < accumulator.size(); y++){
        for(int x = 0; x < accumulator[0].size(); x++){
            output += std::to_string(accumulator[y][x]) + ' ';
            //std::cout << accumulator[y][x] << " ";
            if(accumulator[y][x] > 1){
                result.SetPixel(y,x,accumulator[y][x]); 
            }
        }
        //output += "\n";
        //std::cout << output;
    }

    outputfile << output;
    outputfile.close();
    if(!WriteImage(output_pgm_filenm,result)){
        std::cout << "Can't write Image"<< std::endl;
    }
    
    return 0;
}
/* 
./h3 outputh2.pgm outputh3.pgm outputtexth3.txt

*/