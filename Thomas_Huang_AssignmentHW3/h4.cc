// Program 4 - HW3
// Author: <YOUR NAME>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <cstdio>
#include <cmath>

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

  std::cout << "Running h4: " << input_filenm << " " << input_array_filenm << " " << threshold << "  " << output_line_filenm << std::endl;
  
  Image one_image;
  ReadImage(input_filenm, &one_image);
  int rows = one_image.num_rows();
  int cols = one_image.num_columns();
  Image localmaxima;
  localmaxima.SetNumberGrayLevels(one_image.num_gray_levels());

  struct object {
    int area = 0,
    sumtheta = 0.0, 
    sumrho = 0.0;
    double centroidtheta = 0.0,
    centroidrho = 0.0;
  };

  int r_bins = 0;
  int t_bins = 0;
  // accumulator vector
  // label map vector

  std::fstream file;
  file.open(input_array_filenm);
  file >> t_bins >> r_bins;
  std::vector<std::vector<int>> accumulator(t_bins, std::vector<int>(r_bins, 0));
  std::vector<std::vector<int>> labelmap(t_bins, std::vector<int>(r_bins, 0));
  localmaxima.AllocateSpaceAndSetSize(t_bins,r_bins);
  //inputs all the values of the file into the accumulator
  for (int y = 0; y < t_bins ;y++){
    for (int x = 0; x < r_bins;x++){
      file >> accumulator[y][x];
    }
  }
  file.close();

  for (int y = 0; y < t_bins; y++) {
    for (int x = 0; x < r_bins; x++) {
      if (accumulator[y][x] > threshold) {
        //get local maximas
        localmaxima.SetPixel(y,x,accumulator[y][x]);
      }else{
        localmaxima.SetPixel(y,x,0);
      }
    }
  }

  // labels
  int newlabel = 1; 
  DisjSets djs(t_bins * r_bins);
  //first pass
  for (int i = 0; i < t_bins; ++i){ // # of rows
    for (int j = 0; j < r_bins; ++j){ //# of cols
      int left = 0, top = 0,toproot = 0 ,leftroot = 0, min = 0;
      if (localmaxima.GetPixel(i, j) < threshold){
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
  for (int i = 0; i < t_bins; i++) {
    for (int j = 0; j < r_bins; j++) {
      if (labelmap[i][j] != 0) {
        // running it twice 
        labelmap[i][j] = djs.find(labelmap[i][j]);
        localmaxima.SetPixel(i,j,labelmap[i][j]+10*2);
      }
    }
  }

  //go throguh each label, add them up, find centroid, find orientation
  //loop through labelmap, if it has a threshold map[getpixel]
  std::unordered_map<int,object> objlist;
  for(int i = 0; i < t_bins; i++){
    for (int j= 0;j < r_bins;j++){
      int getp = localmaxima.GetPixel(i,j);
        if(getp == 0){
          continue; 
        }
        if(objlist.find(getp) == objlist.end()){
          objlist[getp] = {1,i,j};
        }else{
          objlist[getp].area++;
          objlist[getp].sumtheta+=i;
          objlist[getp].sumrho+=j;
        }
    }
  }
for(auto &[label, object] : objlist){
  if(object.area > 0){
    object.centroidrho = (object.sumrho*1.0) / object.area;
    object.centroidtheta = (object.sumtheta*1.0) / object.area;
    object.centroidtheta = object.centroidtheta * (M_PI/180);
    // std::cout << "centroidrho: " << object.centroidrho << std::endl;
    // std::cout << "centroidtheta: " << object.centroidtheta << std::endl;
    int x1 = 0.0,y1 = 0.0,x2 = 0.0,y2 = 0.0;
    //possible cordinates
    std::vector< std::pair<int,int>> inbounds;
    double x = object.centroidrho / cos(object.centroidtheta);
    if(x >= 0 && x < rows){
      inbounds.push_back({x,0});
    }
    x = (object.centroidrho - (rows-1) * cos(object.centroidtheta)/sin(object.centroidtheta));
    if(x >= 0 && x < rows){
      inbounds.push_back({x,cols-1});
    }
    double y = (object.centroidrho - (rows-1) * cos(object.centroidtheta)/sin(object.centroidtheta));
    if(y >= 0 && y < cols){
      inbounds.push_back({rows-1,y});
    }
    y = object.centroidrho/sin(object.centroidtheta);
    if(y >= 0 && y < cols){
      inbounds.push_back({0,y});
    }
    if(inbounds.size() >= 2){

      x1 = inbounds[0].first;
      y1 = inbounds[0].second;
      x2 = inbounds[1].first;
      y2 = inbounds[1].second;
      std::cout << "x1: " << x1 << std::endl;
      std::cout << "y1: " << y1 << std::endl;
      DrawLine(x1,y1,x2,y2,255,&one_image);
    }
    if(x1 >= 0 && x1 < rows && y1 >= 0 && y1 < cols && x2 >= 0 && x2 < rows && y2 >=0 && y2 < cols){
      DrawLine(x1,y1,x2,y2,255,&one_image);
    }
  }
}
  if(!WriteImage(output_line_filenm,one_image)){
    std::cout << "cant write image" << std::endl;
    return 0;
  }
  return 0;
}
//h4 {input original gray–level image} {input Hough–voting array} {input Hough threshold value} {output gray–level line image}

/*
./h4 hough_simple_1.pgm outputtexth3.txt 225 outputh4.pgm
*/
