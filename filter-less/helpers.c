#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
// Convert image to grayscale
/*
To make an image a gray scale RGB pixel values are set to equal, resulting in varying shades of gray along the black and white spectrum,
with higher vlues meaning lighter shades closer to white and lower meaning darker shades closer to black.
Ensure each pixel of the new image still has the same general brightness or darkness of the old image, taking the average of red,green and blue
values to determine the shades of gray to make the new pixel.

If RGB values of the pixel is high, then the new pixel value should also be high, and if the orginal values are low, then new values
should also be low. Take the average of paticular pixel RGB values to determine the RGB values of the new pixel
*/
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    // Place holder to save pixel value
    RGBTRIPLE pixel_value;
    // Loop over all pixels
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            // Value of the piexl 0x000000, Read a single pixel value
            pixel_value = image[i][j];
            // Red_value = (Red_Mask && Pixel value) << 0;
            uint8_t red = pixel_value.rgbtRed;
            // Green_value = (Green_Mask && Pixel value) << 8;
            uint8_t green = pixel_value.rgbtGreen;
            // Blue value = (Blue_Mask && Pixel value) << 16;
            uint8_t blue = pixel_value.rgbtBlue;
            // Take the resulting average of red, green and blue
            uint8_t new_pixel_value = ((red + green + blue)/3.0 + 0.5);
            // Assigning the new_pixel_value
            pixel_value.rgbtRed = new_pixel_value;
            pixel_value.rgbtGreen = new_pixel_value;
            pixel_value.rgbtBlue = new_pixel_value;
            // Replace the original pixel values of the image
            image[i][j] = pixel_value;
        }
    }

    return;
}

// Convert image to sepia
// "sepia" filter, which gives images an old-timely feel by making the whole image look
// redish-brown.
/*
For each pixel, the sepia color values should be calculated besed on orginal color value
The result of each of these formulas may not be an integer, but each value could be rounded to the nearest integer.
It’s also possible that the result of the formula is a number greater than 255, the maximum value for an 8-bit color value.
In that case, the red, green, and blue values should be capped at 255.

float input = 256.554;
uint8_t num = (uint8_t)fmin(input, 255);

When assign a value like 256.554 to a varibale of type uin8_t (unsigned 8-bit integer), the following
happens;
1. Truncation of DEcimal Part
- The decimal value 256.554 is truncated to 256. The fractional part (.554) is discarded because
uint8_t can store integers.

2. Modulo Operation
- The value 256 exceeds the maximum value of uint8_t, which is 255. When this happens, the
value wraps around, modulo 256.
In this case, 256 % 256 = 0. so value stired in the uint8_t variable is 0.
*/
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //Place holder to save pixel value
    RGBTRIPLE pixel_value;
    // Loop over all pixels
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            // value of the piexl 0x000000, Read a single pixel value
            pixel_value = image[i][j];
            // Red_value = (Red_Mask && Pixel value) << 0;
            uint8_t originalRed = pixel_value.rgbtRed;
            // Green_value = (Green_Mask && Pixel value) << 8;
            uint8_t originalGreen = pixel_value.rgbtGreen;
            // Blue value = (Blue_Mask && Pixel value) << 16;
            uint8_t originalBlue = pixel_value.rgbtBlue;
            // Take the resulting average of red, green and blue
            float sepia_red_value = (.393 * originalRed + .769 * originalGreen + .189 * originalBlue + 0.5);
            uint8_t red_value = (uint8_t)fmin(sepia_red_value,255);
            float sepia_green_value = (.349 * originalRed + .686 * originalGreen + .168 * originalBlue + 0.5);
            uint8_t green_value = (uint8_t)fmin(sepia_green_value,255);
            float sepia_blue_value = (.272 * originalRed + .534 * originalGreen + .131 * originalBlue + 0.5);
            uint8_t blue_value = (uint8_t)fmin(sepia_blue_value,255);
            // Assigning the new_pixel_value
            pixel_value.rgbtRed = red_value;
            pixel_value.rgbtGreen = green_value;
            pixel_value.rgbtBlue = blue_value;
            // Replace the original pixel values of the image
            image[i][j] = pixel_value;
        }
    }

    return;
}

// Reflect image horizontally
/*
Filters might also move pixels around. Reflecting an image, where the resulting image is what you would
get by placinng the orginal image infront of a mirror.
- Any pixels on the left side of the image should end up on the right, and vice versa.
- All of the orginal pixels of the orginal image will represent in the reflected image,
it's just that those pixels may have been rearranged to be in a differenct place in the image.
*/
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Place holder to save the image
    RGBTRIPLE reflect_placeholder[height][width];
    // Place holder to save the pixel
    RGBTRIPLE pixel_value;
    int k;
    // Loop through the image
    for (int i=0; i < height; i++){
        for (int j=0; j < width; j++){
            // Value of the pixel 0x000000, Read a single pixel value
            pixel_value = image[i][j];
            // Place pixel in the reflect_placeholder
            k = width - j - 1;
            reflect_placeholder[i][k] = pixel_value;
        }
    }
    //loop through the reflect_placeholder, inplace of orginal image
    for (int i=0; i < height; i++){
        for (int j=0; j < width; j++){
            image[i][j] = reflect_placeholder[i][j];
        }
    }

    return;
}

// Blur image
/*
The "box blur" works by taking each pixel and, for each color value, giving it a new
value by averaging the colour values of neighboring pixels.

The new value of each pixel would be the average of the values of all the pixels that are
within 1 row and column of the orginal pixel (3x3 box).

For pixels along the edge or corner, would still look for all pixels within 1 row and column.
*/
void blur(int height, int width, RGBTRIPLE _image[height][width])
{
    RGBTRIPLE pixel_value;
    RGBTRIPLE new_pixel_value;
    int average = 9;
    RGBTRIPLE blured_image[height][width];
    // int blured_image[height][width];

    // printf("Function 01 -");
    // printf("\n");
    // Loop through the image;
    for (int i=0; i < height; i++){
        for (int j=0; j < width; j++){
            //select a pixel;
             //new_pixel_value = 0;
            new_pixel_value.rgbtBlue = 0;
            new_pixel_value.rgbtGreen = 0;
            new_pixel_value.rgbtRed = 0;
            average = 9;
            pixel_value.rgbtBlue = 0;
            pixel_value.rgbtGreen = 0;
            pixel_value.rgbtRed = 0;

            // Use a place holder to get the 1-row and 1-column pixels around;
            // Loop through rows (i-1) to (i+1) and columns (j-1) to (j+1)
            for (int row = (i-1); row <= (i+1); row++){

                for (int col = (j-1); col <= (j+1); col++){

                    // Check bounds to avoid acessing out-of-range elements
                    if ((row < 0 || row >= height) || (col < 0 || col >= width)){
                        average -= 1;
                        pixel_value.rgbtBlue = 0;
                        pixel_value.rgbtGreen = 0;
                        pixel_value.rgbtRed = 0;
                    }else{
                        pixel_value.rgbtBlue = _image[row][col].rgbtBlue;
                        pixel_value.rgbtGreen = _image[row][col].rgbtGreen;
                        pixel_value.rgbtRed = _image[row][col].rgbtRed;
                    }
                    new_pixel_value.rgbtBlue = new_pixel_value.rgbtBlue + pixel_value.rgbtBlue;
                    new_pixel_value.rgbtGreen = new_pixel_value.rgbtGreen + pixel_value.rgbtGreen;
                    new_pixel_value.rgbtRed = new_pixel_value.rgbtRed + pixel_value.rgbtRed;
                }
            }

            blured_image[i][j].rgbtBlue = (new_pixel_value.rgbtBlue/average);
            blured_image[i][j].rgbtGreen = (new_pixel_value.rgbtGreen/average);
            blured_image[i][j].rgbtRed = (new_pixel_value.rgbtRed/average);
        }
    }


    // printf("Function 02 -");
    // printf("\n");

    //     // Loop through the image;
    // for (int i=0; i < height; i++){
    //     for (int j=0; j < width; j++){
    //         //select a pixel;
    //         // Use a place holder to get the 1-row and 1-column pixels around;
    //         // Loop through rows (i-1) to (i+1) and columns (j-1) to (j+1)
    //         for (int row = (i-1); row <= (i+1); row++){
    //             for (int col = (j-1); col <= (j+1); col++){
    //                 // Check bounds to avoid acessing out-of-range elements
    //                 if ((row >= 0 && row < height) && (col >= 0 && col < width)){
    //                     average ++;
    //                     new_pixel_value.rgbtBlue = new_pixel_value.rgbtBlue + pixel_value.rgbtBlue;
    //                     new_pixel_value.rgbtGreen = new_pixel_value.rgbtGreen + pixel_value.rgbtGreen;
    //                     new_pixel_value.rgbtRed = new_pixel_value.rgbtRed + pixel_value.rgbtRed;
    //                 }
    //             }
    //         }

    //         blured_image[i][j].rgbtBlue = (new_pixel_value.rgbtBlue/average);
    //         blured_image[i][j].rgbtGreen = (new_pixel_value.rgbtGreen/average);
    //         blured_image[i][j].rgbtRed = (new_pixel_value.rgbtRed/average);

    //         new_pixel_value.rgbtBlue = 0;
    //         new_pixel_value.rgbtGreen = 0;
    //         new_pixel_value.rgbtRed = 0;
    //         average = 0;
    //     }
    // }

        //loop through the reflect_placeholder, inplace of orginal image
    for (int i=0; i < height; i++){
        for (int j=0; j < width; j++){
            _image[i][j] = blured_image[i][j];
        }
    }

    // Loop to print the values of the output image
    printf("Blurred Image:\n");
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("Pixel [%d][%d]: (%d, %d, %d)\n",
                   i, j,
                   _image[i][j].rgbtRed,
                   _image[i][j].rgbtGreen,
                   _image[i][j].rgbtBlue);
        }
    }

    return;
}



