Image (bit-map) structure

BITMAPFILEHEADER,   is 14 bytes long
BITMAPINFOHEADER,   is 40 bytes long
Following them is the actual bit-map,

an array of bytes, triples of which represent a pixel’s color.
However, BMP stores these triples backwards (i.e., as BGR), with 8 bits for blue, followed by 8 bits for green, followed by 8 bits for red.
(Some BMPs also store the entire bitmap backwards, with an image’s top row at the end of the BMP file.
But we’ve stored this problem set’s BMPs as described herein, with each bitmap’s top row first and bottom row last.)

"bmp.h"

Why are these structs useful? Well, recall that a file is just a sequence of bytes (or, ultimately, bits) on disk.
But those bytes are generally ordered in such a way that the first few represent something, the next few represent something else, and so on.
“File formats” exist because the world has standardized what bytes mean what.
Now, we could just read a file from disk into RAM as one big array of bytes. And we could just remember that the byte at array[i] represents one thing, while the byte at array[j] represents another.
But why not give some of those bytes names so that we can retrieve them from memory more easily? That’s precisely what the structs in bmp.h allow us to do.
Rather than think of some file as one long sequence of bytes, we can instead think of it as a sequence of structs.

"filter.c"

That string tells the program what the allowable command-line arguments to the program are: b, g, r, and s.
Each of them specifies a different filter that we might apply to our images: blur, grayscale, reflection, and sepia.

The next several lines open up an image file, make sure it’s indeed a BMP file, and read all of the pixel information into a 2D array called image.

Scroll down to the switch statement that begins on line 101. Notice that, depending on what filter we’ve chosen, a different function is called:
if the user chooses filter b, the program calls the blur function; if g, then grayscale is called; if r, then reflect is called;
and if s, then sepia is called.

Notice, too, that each of these functions take as arguments the height of the image, the width of the image, and the 2D array of pixels.

"helpers.h"

Next, take a look at helpers.h. and just provides the function prototypes for the functions you saw earlier.


"Reflection Function"

Base function

    //print the orginal image
    for (int i=1; i < 10; i++){
        for (int j=1; j < 10; j++){
           printf("[%i,",i);
           printf(" %i]",j);
           //reflect_placeholder[i][k] = pixel_value;
        }
        printf("\n");
    }

        printf("\n");
        printf("\n");
        printf("\n");

    int k;
    // Loop through the image
    for (int i=1; i < 10; i++){
        for (int j=1; j < 10; j++){
            // Value of the pixel 0x000000, Read a single pixel value
            //pixel_value = image[i][j];
            // Place pixel in the reflect_placeholder
            /*
            k = width - j
            */
           k = 10 - j;
           printf("[%i,",i);
           printf(" %i]",k);
           //reflect_placeholder[i][k] = pixel_value;
        }
        printf("\n");
    }
    //image = reflect_placeholder;

There's a problem here
In C arrays are passed by reference, so changes to the orginal "image" array should reflect
reflect directly in the array passed to the function.

the command "image = reflect_placeholder;" is ineffective. This assignment only changes the local pointer "image"
and dose not effecr the orginal array.
You need to modify the image array directly instead of assigning to it.


// The blur

not a great way to do it

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //RGBTRIPLE pixel_value;
    //int pixel_value;
    //RGBTRIPLE new_pixel_value;
    int new_pixel_value;
    int average = 9;
    width = 10;
    height = 10;

    //Generate a random matrix for testing
    int _image[height][width];
    int blured_image[height][width];

    // Seed the random number generator with the current time
    srand(time(NULL));

    // Initialize the matrix with random values
    for (int i=0; i < height; i++){
        for (int j=0; j < width; j++){
            _image[i][j] = rand() % 100; // Random values between 0 and 99
        }
    }

    //print the orginal image
    for (int i=0; i < height; i++){
        for (int j=0; j < width; j++){
            printf("%i ",_image[i][j]);
        }
        printf("\n");
    }
        printf("\n");
        printf("\n");

    // Loop through the image;
    for (int i=0; i < height; i++){
        for (int j=0; j < width; j++){
            //select a pixel;
            //pixel_value = _image[i][j];
            // Use a place holder to get the 1-row and 1-column pixels around;
            // Loop through rows (i-1) to (i+1) and columns (j-1) to (j+1)
            for (int row = (i-1); row <= (i+1); row++){
                for (int col = (j-1); col <= (j+1); col++){
                    // Check bounds to avoid acessing out-of-range elements
                    if ((row < 0 || row > height) || (col < 0 || col > width)){
                        average = average - 1;
                        new_pixel_value = 0;
                        //printf("%i ",average);
                    }else{
                    //printf("\n");
                    //printf("%i ",_image[row][col]);
                    printf("[%i,",row);
                    printf(" %i]",col);
                    new_pixel_value = new_pixel_value + _image[row][col];
                    }
                }
            }
            printf("\n");
            blured_image[i][j] = (new_pixel_value)/average;
            new_pixel_value = 0;
            average = 9;
        }
    }

    printf("\n");
    printf("\n");

    //print the orginal image
    for (int i=0; i < height; i++){
        for (int j=0; j < width; j++){
            printf("%i ",_image[i][j]);
        }
        printf("\n");
    }

        printf("\n");
        printf("\n");

    return;
}

// void blur(int height, int width, RGBTRIPLE image[height][width])
// {
//     //RGBTRIPLE pixel_value;
//     //int pixel_value;
//     //RGBTRIPLE new_pixel_value;
//     int new_pixel_value;
//     int average = 0;
//     width = 10;
//     height = 10;

//     //Generate a random matrix for testing
//     int _image[height][width];
//     int blured_image[height][width];

//     // Seed the random number generator with the current time
//     srand(time(NULL));

//     // Initialize the matrix with random values
//     for (int i=0; i < height; i++){
//         for (int j=0; j < width; j++){
//             _image[i][j] = rand() % 100; // Random values between 0 and 99
//         }
//     }

//     //print the orginal image
//     for (int i=0; i < height; i++){
//         for (int j=0; j < width; j++){
//             printf("%i ",_image[i][j]);
//         }
//         printf("\n");
//     }
//         printf("\n");
//         printf("\n");

//     // Loop through the image;
//     for (int i=0; i < height; i++){
//         for (int j=0; j < width; j++){
//             //select a pixel;
//             //pixel_value = _image[i][j];
//             // Use a place holder to get the 1-row and 1-column pixels around;
//             // Loop through rows (i-1) to (i+1) and columns (j-1) to (j+1)
//             for (int row = (i-1); row <= (i+1); row++){
//                 for (int col = (j-1); col <= (j+1); col++){
//                     // Check bounds to avoid acessing out-of-range elements
//                     if ((row >= 0 && row < height) && (col >= 0 && col < width)){
//                         average ++;
//                         new_pixel_value = new_pixel_value + _image[row][col];
//                         //printf("[%i,",row);
//                         //printf(" %i]",col);
//                         printf("%i ",average);
//                     }
//                 }
//             }
//             //printf("\n");
//             blured_image[i][j] = (new_pixel_value)/average;
//             new_pixel_value = 0;
//             average = 0;
//         }
//     }

//     printf("\n");
//     printf("\n");

//     //print the orginal image
//     for (int i=0; i < height; i++){
//         for (int j=0; j < width; j++){
//             printf("%i ",_image[i][j]);
//         }
//         printf("\n");
//     }

//     printf("\n");
//     printf("\n");

//     return;
// }


// void blur(int height, int width, RGBTRIPLE image[height][width])
// {
//     //RGBTRIPLE pixel_value;
//     int pixel_value;
//     //RGBTRIPLE new_pixel_value;
//     int new_pixel_value;
//     int average = 9;
//     width = 10;
//     height = 10;

//     //Generate a random matrix for testing
//     int _image[height][width];
//     int blured_image[height][width];

//     // Seed the random number generator with the current time
//     srand(time(NULL));

//     // Initialize the matrix with random values
//     for (int i=0; i < height; i++){
//         for (int j=0; j < width; j++){
//             _image[i][j] = rand() % 100; // Random values between 0 and 99
//         }
//     }

//     //print the orginal image
//     for (int i=0; i < height; i++){
//         for (int j=0; j < width; j++){
//             printf("%i ",_image[i][j]);
//         }
//         printf("\n");
//     }
//         printf("\n");
//         printf("\n");

//     // Loop through the image;
//     for (int i=0; i < height; i++){
//         for (int j=0; j < width; j++){
//             //select a pixel;
//             //pixel_value = _image[i][j];
//             // Use a place holder to get the 1-row and 1-column pixels around;
//             // Loop through rows (i-1) to (i+1) and columns (j-1) to (j+1)
//             for (int row = (i-1); row <= (i+1); row++){
//                 for (int col = (j-1); col <= (j+1); col++){
//                     // Check bounds to avoid acessing out-of-range elements
//                     if ((row < 0 || row >= height) || (col < 0 || col >= width)){
//                         average = average - 1;
//                         pixel_value = 0;
//                         //printf("%i ",average);
//                         printf("%i ",pixel_value);
//                     }else{
//                     //printf("\n");
//                     printf("[%i,",row);
//                     printf(" %i]",col);
//                     printf(" - ");
//                     pixel_value = _image[row][col];
//                     printf("%i , ",_image[row][col]);
//                     }
//                     new_pixel_value = new_pixel_value + pixel_value;
//                 }
//             }
//             printf("\n");
//             blured_image[i][j] = (new_pixel_value)/average;
//             new_pixel_value = 0;
//             average = 9;
//         }
//     }

//     printf("\n");
//     printf("\n");

//     //print the orginal image
//     for (int i=0; i < height; i++){
//         for (int j=0; j < width; j++){
//             printf("%i ",blured_image[i][j]);
//         }
//         printf("\n");
//     }

//         printf("\n");
//         printf("\n");

//     return;
// }



void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //RGBTRIPLE pixel_value;
    int pixel_value;
    //RGBTRIPLE new_pixel_value;
    int new_pixel_value;
    int average = 9;
    width = 10;
    height = 10;

    //Generate a random matrix for testing
    int _image[height][width];
    int blured_image[height][width];

    // Seed the random number generator with the current time
    srand(time(NULL));

    // Initialize the matrix with random values
    for (int i=0; i < height; i++){
        for (int j=0; j < width; j++){
            _image[i][j] = rand() % 100; // Random values between 0 and 99
        }
    }

    //print the orginal image
    for (int i=0; i < height; i++){
        for (int j=0; j < width; j++){
            printf("%i ",_image[i][j]);
        }
        printf("\n");
    }
        printf("\n");
        printf("\n");

///
    printf("Function 01 -");
    printf("\n");
    // Loop through the image;
    for (int i=0; i < height; i++){
        for (int j=0; j < width; j++){
            //select a pixel;
            //pixel_value = _image[i][j];
            // Use a place holder to get the 1-row and 1-column pixels around;
            // Loop through rows (i-1) to (i+1) and columns (j-1) to (j+1)
            for (int row = (i-1); row <= (i+1); row++){
                for (int col = (j-1); col <= (j+1); col++){
                    // Check bounds to avoid acessing out-of-range elements
                    if ((row < 0 || row >= height) || (col < 0 || col >= width)){
                        average = average - 1;
                        pixel_value = 0;
                        //printf("%i ",average);
                        //printf("%i ",pixel_value);
                    }else{
                    //printf("\n");
                    //printf("[%i,",row);
                    //printf(" %i]",col);
                    //printf(" - ");
                    pixel_value = _image[row][col];
                    //printf("%i , ",_image[row][col]);
                    }
                    new_pixel_value = new_pixel_value + pixel_value;
                }
            }
            //printf("\n");
            blured_image[i][j] = (new_pixel_value)/average;
            new_pixel_value = 0;
            average = 9;
        }
    }

    //printf("\n");
    //printf("\n");

    //print the orginal image
    for (int i=0; i < height; i++){
        for (int j=0; j < width; j++){
            printf("%i ",blured_image[i][j]);
        }
        printf("\n");
    }

        printf("\n");
        printf("\n");

    printf("Function 02 -");
    printf("\n");

        // Loop through the image;
    for (int i=0; i < height; i++){
        for (int j=0; j < width; j++){
            //select a pixel;
            //pixel_value = _image[i][j];
            // Use a place holder to get the 1-row and 1-column pixels around;
            // Loop through rows (i-1) to (i+1) and columns (j-1) to (j+1)
            for (int row = (i-1); row <= (i+1); row++){
                for (int col = (j-1); col <= (j+1); col++){
                    // Check bounds to avoid acessing out-of-range elements
                    if ((row >= 0 && row < height) && (col >= 0 && col < width)){
                        average ++;
                        new_pixel_value = new_pixel_value + _image[row][col];
                        //printf("[%i,",row);
                        //printf(" %i]",col);
                        //printf("%i ",average);
                    }
                }
            }
            //printf("\n");
            blured_image[i][j] = (new_pixel_value)/average;
            new_pixel_value = 0;
            average = 0;
        }
    }

    //printf("\n");
    //printf("\n");

    //print the orginal image
    for (int i=0; i < height; i++){
        for (int j=0; j < width; j++){
            printf("%i ",blured_image[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    printf("\n");

    return;
}
