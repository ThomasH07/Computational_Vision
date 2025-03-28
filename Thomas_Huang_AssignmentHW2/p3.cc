// Program 3 - HW2
// Author: <Thomas Huang>

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <cstdio>
#include <cmath>
#include "image.h"
using namespace ComputerVisionProjects;
int main(int argc, char **argv){ 
  if (argc != 4) {
    std::cout << "Usage: " <<
      argv[0] << " {input_image_name} {output descriptions} {output_image_name}" << std::endl;
    return 0;
  }
  const std::string input_file(argv[1]);
  const std::string output_object_descriptions(argv[2]);
  const std::string output_file(argv[3]);

  std::cout << "Running p3 " << input_file << " " 
            << output_object_descriptions << " " << output_file << std::endl;
  Image one_image;
  Image* one_ptr = &one_image;
  ReadImage(input_file, one_ptr);
  int rows = one_image.num_rows();
  int columns = one_image.num_columns();
  int newlabel = 0;
  struct object {
    long area = 0.0,
    sumx = 0.0, 
    sumy = 0.0;
    double centroidx = 0.0,
    centroidy = 0.0, 
    emin = 0.0,
    emax = 0.0,
    roundness = 0.0,
    orientation = 0.0,
    a = 0.0,
    b = 0.0,
    c = 0.0;
    int label;
  };
  // key is label
  //
  std::unordered_map<int,object> objlist;

  //std::vector<object> objs;
  //first pass
  //i = x ,j = y
  for(int i = 0; i < rows; i++){
    for (int j = 0;j < columns;j++){
      int getp = one_image.GetPixel(i,j);
        if(getp == 0){
          continue; 
        }
        if(objlist.find(getp) == objlist.end()){
          objlist[getp] = {1,i,j};
        }else{
          objlist[getp].area++;
          objlist[getp].sumx+=i;
          objlist[getp].sumy+=j;
          
        }
    }
  }
  for (auto &[label, object] : objlist) {
      if (object.area > 0) { 
          object.centroidx = (object.sumx*1.0) / object.area;
          object.centroidy = (object.sumy*1.0) / object.area;
      }
  }
  //second pass
  //calculate sum
  for(int i = 0; i < rows; i++){
    for (int j = 0;j < columns;j++){
      int getp = one_image.GetPixel(i,j);

      if (getp == 0){
        continue;
      }
      //
      double x = i - objlist[getp].centroidx; 
      double y = j - objlist[getp].centroidy;



      objlist[getp].a += x * x;
      objlist[getp].b += x * y;
      objlist[getp].c += y * y;
  
    }
  }

  for (auto &[label, object] : objlist) { 


    double theta = 0.5 * atan2(2* object.b, object.a - object.c);
    //orientation
    object.orientation = theta * (180/M_PI);
    // if (object.orientation < 0) {
    //   object.orientation += 180.0;
    // } 
    double sintheta = sin(theta);
    double costheta = cos(theta);
    //E min
    double emin = object.a * sintheta * sintheta - 2 * object.b * sintheta * costheta + object.c * costheta * costheta;
    object.emin = emin;

    //E max
    double emax = object.a * costheta * costheta + 2 * object.b * sintheta * costheta + object.c * sintheta * sintheta;
    object.emax = emax;
    //roundness
    object.roundness = object.emin/object.emax;
    object.label = newlabel++;
  }
  
  std::ofstream outputfile(output_object_descriptions);
  if (!outputfile.is_open()){
    std::cerr << "Can't open file " << std::endl;
    return 0;
  }
  int c = 0;
  for (auto& [label, obj] : objlist){
    std::string output;
    if(obj.orientation < 0){
      
      output = std::to_string(obj.label) + " " + std::to_string(obj.centroidx) + " " + std::to_string(obj.centroidy) + " " + std::to_string(obj.emin) + " " + std::to_string(obj.area) + " " + std::to_string(obj.roundness) + " " + std::to_string(obj.orientation+180.0);
    }else{
      output = std::to_string(obj.label) + " " + std::to_string(obj.centroidx) + " " + std::to_string(obj.centroidy) + " " + std::to_string(obj.emin) + " " + std::to_string(obj.area) + " " + std::to_string(obj.roundness) + " " + std::to_string(obj.orientation);
    }
    outputfile << output << std::endl;
    DrawLine(obj.centroidx, obj.centroidy, obj.centroidx + 100 * cos(obj.orientation * (M_PI / 180.0)), obj.centroidy + 100 * sin(obj.orientation * (M_PI / 180.0)), 255, &one_image);
  }
  outputfile.close();
  if (!WriteImage(output_file, one_image)){
    std::cout << "Can't write to file " << output_file << std::endl;
    return 0;
  }

  return 0;
}

/* 
./p3 outputp2.pgm output.txt outputp3.pgm
*/
//0 256.527451 195.367647 363516.096275 2040 0.482194 129.788517
//1 263.409163 349.568653 3810176.434220 7618 0.521131 18.215075
//object label, row position of the center , column position of the center , the minimum moment of inertia (i.e. Emin), 
//object area, roundedness, and the orientation (i.e. orientation angle in degrees as described in Binary Images slides).
