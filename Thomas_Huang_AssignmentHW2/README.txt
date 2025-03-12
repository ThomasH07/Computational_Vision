Author: <Thomas Huang>
CSCI 49369 - Computational Vision


# Provide short descriptions of your algorithms / problem you encountered.
I have completed p1 to p3, not p4
p1

It loads a pgm image, loops through each pixel and processes each pixel to either white or black. If the intensity of the pixel reach over the given threshold, set it to 255, else set to 0. 
It then writes a modified image into a new pgm. For Program 1, I set a default Threshold value 127 because it looked more accurate to the example binary images.
One of my problems I had was, thinking that since it was gray scale to binary, I had to set pixels based on 0s and 1s. 
Then I realized after looking at it again its 1 is not white, I forgot it was 0 to 255.

run in terminal
./p1 two_objects.pgm 127 outputp1.pgm

p2

For Program 2, was more difficult then I expected. The program uses a binary image, from the output of p1 and labels each imagine giving their own gray scale value.
I had to review slides about the disjoint set, and asking for help to fully understand it. 
Another minor issue was thinking I had to check the top-left pixel.
But figured out that I dont need to look for that since, the previous pixel should have gotten the top, which would be the top left of the next pixel.

run in terminal
./p2 outputp1.pgm outputp2.pgm

p3

For program 3, was difficult but not as difficult as 2. The program used the gray scale image given from p2, calculating each of the objects(based on their gray value) area, centroidx and y, enim, etc.  
However for some reason I had a really big problem with finding the orientation for some reason. While my Emin was very accurate, my orientation was completely off. 
After a couple of hours I figured out the issues, my first nested for loop focused on collecting the sum of x and y and the areas, having my first loop i = x, and second loop j = y . 
However for my second nested for loop, calculating centroid and x prime(used to find a,b,c), I swapped and thought of the values as, j = x and i = y. Thus I fixed it, and I was able to get a accurate orientation of each object. 
I also found another bug that would mess with the drawline, which was adding 180 whenever it was lower than 0, which disrupted the drawline. (sorry the last part of p3 was a bit of a rush)

run in terminal
./p3 outputp2.pgm output.txt outputp3.pgm