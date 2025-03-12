// Program 2 - HW2
// Author: <Thomas Huang>

#include <iostream>
#include <string>

#include "image.h"
#include "DisjSets.h"
using namespace ComputerVisionProjects;
//a labeling program named p2 that segments a binary image into several connected regions
// Note that you may have to make two passes of the image to resolve possible equivalences in the labels.
int main(int argc, char **argv){
  
  if (argc!=3) {
    std::cout << "Usage: " <<
      argv[0] << " {input_image_name} {output_image_name}" << std::endl;
    return 0;
  }
  const std::string input_file(argv[1]);
  const std::string output_file(argv[2]);

  std::cout << "Running p2 " << input_file << " " << output_file << std::endl;  
  int newlabel = 1; 
  //creates Image and disjoint set
  Image one_image;
  Image* one_ptr = &one_image;
  DisjSets djs(480 * 640);
  ReadImage(input_file, one_ptr);
  int rows = one_image.num_rows();
  int columns = one_image.num_columns();
  std::vector<std::vector<int>> labelmap(rows,std::vector<int>(columns,0));
  //assigning labels
  //first pass
  for (int i = 0; i < rows; ++i){ // # of rows
    for (int j = 0; j < columns; ++j){ //# of cols
      int left = 0, top = 0,toproot = 0 ,leftroot = 0, min = 0;
      if (one_image.GetPixel(i, j) == 0){
        continue;
      }
      //top
      if (i > 0) {
          top = labelmap[i-1][j];
      }
      //left
      if (j > 0) {
          left = labelmap[i][j-1];
      }
      //recursively finding the root of the set to get the correct label
      if (top > 0) {
        toproot = djs.find(top);
      }
      if (left > 0) {
        leftroot = djs.find(left);
      }
      //we are finding min label of the adjacent #s
      if (left > 0) {
        min = left;
      }
      //Check top label
      if (top > 0 && (min == 0 || top < min)) {
        min = top;
      }
      if (min > 0) {
          //current white pixel will have the minimum label
          labelmap[i][j] = min;

          if (left > 0 && top > 0  && leftroot != toproot){
            djs.unionSets(toproot, leftroot);
          }
      }else{
          // if the current white pixel does not have a top,left,topleft white pixel
          labelmap[i][j] = newlabel++;   
        }      
      }
    }
  //second pass 
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (labelmap[i][j] != 0) {
        // running it twice 
        labelmap[i][j] = djs.find(labelmap[i][j]);
        one_image.SetPixel(i,j,labelmap[i][j]+10*2);
      }
    }
  }
  WriteImage(output_file, one_image);
  return 0;
}
/* 
./p2 outputp1.pgm outputp2.pgm
*/