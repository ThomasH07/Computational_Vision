# CS493-HW3

## To compile: make all
Alternatively: make h1, make h2, make h3, make h4

--> Add information based on your programs
I have completed h1, h2, h3, and h4 is not correct

h1: h1 locates the edges of a gay scale image, using the squared gradient operator, using the discrete convolution, to apply the 3x3 sobels for x and y to each pixel. 
A difficulty I had was figuring out how to apply discrete convolution to each pixel, I was thinking of hard coding each value into of the pixels, 
I thought of using another nested for loop to make the code shorter and simplier, but sadly having a larger complexity.

h2: h2 is fairly simple, It uses the output of h1, then thresholds the edges of the gray scale image, setting each edge thats over the threshold to white, converting the gray scale image to a binary image.
I didn't have too many problems with h2, since the code is very similar to p1 from homework two

h3: h3 was a little bit harder, I had difficulty understanding what k was, but then I realized that k was acounting for the delta rho and rho. 
What h3 does it essentially, creates sineoids based on the binary images, checking each pixel is white, if so compute rho and k based on each theta and increment the voting vector if their is a line within the boundaries.

h4: h4 is by far the hardest one, as I had a problem understanding and was confusing to me, until I figured out that finding the local maximas allows up to find the peaks of the sineoids, and we use them to calculate the centroid and position on our image.
The problem is that its easier said than done, it was hard to code.