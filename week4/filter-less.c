// actual file name is helpers.c
#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate through rows
    for(int i = 0; i < height; i++ ){
        // iterate through columns of each rows
        for(int j = 0; j < width; j++){
            // find average all all RGB values in a pixel
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0);
            // put that values in all RGB so the pixel becomes a shade of grey
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
     // iterate through rows
    for(int i = 0; i < height; i++ ){
        // iterate through columns of each rows
        for(int j = 0; j < width; j++){
            int originalRed = image[i][j].rgbtRed;
            int originalBlue = image[i][j].rgbtBlue;
            int originalGreen = image[i][j].rgbtGreen;
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            if(sepiaRed>255){
                sepiaRed = 255;
            }
            if(sepiaBlue>255){
                sepiaBlue = 255;
            }
            if(sepiaGreen>255){
                sepiaGreen = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate through rows
    for(int i = 0; i < height; i++ ){
        // iterate through columns of each rows up to half
        for(int j = 0; j < width/2; j++){

            // temp rgbt
            RGBTRIPLE temp;
            // swap left and right columns in same row and keep moving them close till half

            // put original in temp;
            temp = image[i][j];
            // put mirror in original;
            image[i][j] = image[i][(width - 1 ) - j];
            // put temp in mirror;
            image[i][(width - 1 ) - j] = temp;

            // i was first using too much pointers on this one, then i realised u don't need pointers for arrays
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }


    // iterate over original image to replace the colors
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int pixelsAround = 0;
            int totalRed = 0;
            int totalBlue = 0;
            int totalGreen = 0;

            // running nested loop to visit rows and column of 3x3 neighbours
            for(int row = -1; row <=1; row++){
                for(int col = -1; col <=1; col++){
                    // find the original row and column index im actually at in the image
                    int originalRow = i+row;
                    int originalColumn = j+col;
                    // if the original index is inside image, increment the pixelCounter and store the rgb values
                    if(originalRow < height && originalRow >=0 && originalColumn < width && originalColumn >=0){
                        pixelsAround++;
                        totalRed += copy[originalRow][originalColumn].rgbtRed;
                        totalGreen += copy[originalRow][originalColumn].rgbtGreen;
                        totalBlue += copy[originalRow][originalColumn].rgbtBlue;
                    }

                }
            }
            // put the average values of rgb in original image pixel
            image[i][j].rgbtRed = round(totalRed/(float)pixelsAround);
            image[i][j].rgbtBlue = round(totalBlue/(float)pixelsAround);
            image[i][j].rgbtGreen = round(totalGreen/(float)pixelsAround);
        }
    }
    return;
}
