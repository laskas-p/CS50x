#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            //printf("RED: %i, GREEN: %i, BLUE: %i", image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);
            //find average
            float avg = (float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;
            //printf("AVG: %i", avg);
            //replace RGB values as of average
            image[i][j].rgbtRed = (int)roundf(avg);
            image[i][j].rgbtGreen = (int)roundf(avg);
            image[i][j].rgbtBlue = (int)roundf(avg);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {

            //making sepia equivalent
            float sepiaRed =  image[i][j].rgbtRed * 0.393 + image[i][j].rgbtGreen * 0.769 + image[i][j].rgbtBlue * 0.189;
            float sepiaGreen =  image[i][j].rgbtRed * 0.349 + image[i][j].rgbtGreen * 0.686 + image[i][j].rgbtBlue * 0.168;
            float sepiaBlue =  image[i][j].rgbtRed * 0.272 + image[i][j].rgbtGreen * 0.534 + image[i][j].rgbtBlue * 0.131;

            //replacing image bits with sepia color
            if ((int)roundf(sepiaRed) <= 255)
            {
                image[i][j].rgbtRed = (int)roundf(sepiaRed);
            }
            else
            {
                image[i][j].rgbtRed = 255;
            }
            if ((int)roundf(sepiaGreen) <= 255)
            {
                image[i][j].rgbtGreen = (int)roundf(sepiaGreen);
            }
            else
            {
                image[i][j].rgbtGreen = 255;
            }
            if ((int)roundf(sepiaBlue) <= 255)
            {
                image[i][j].rgbtBlue = (int)roundf(sepiaBlue);
            }
            else
            {
                image[i][j].rgbtBlue = 255;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < (int)(width / 2) ; j++)
        {
            //if there's no middle row of pixels
            if (width % 2 == 1)
            {
                int tmp_wdt = width - 1 - j;
                int tmp_red = image[i][tmp_wdt].rgbtRed;
                int tmp_green = image[i][tmp_wdt].rgbtGreen;
                int tmp_blue = image[i][tmp_wdt].rgbtBlue;

                image[i][tmp_wdt].rgbtRed = image[i][j].rgbtRed;
                image[i][tmp_wdt].rgbtGreen = image[i][j].rgbtGreen;
                image[i][tmp_wdt].rgbtBlue = image[i][j].rgbtBlue;

                image[i][j].rgbtRed = tmp_red;
                image[i][j].rgbtGreen = tmp_green;
                image[i][j].rgbtBlue = tmp_blue;
            }
            else
            {
                //if there's middle row of pixels, we ommit it
                if (j != width / 2)
                {
                    int tmp_wdt = width - 1 - j;
                    int tmp_red = image[i][tmp_wdt].rgbtRed;
                    int tmp_green = image[i][tmp_wdt].rgbtGreen;
                    int tmp_blue = image[i][tmp_wdt].rgbtBlue;
                    //printf("%i = %i\n", tmp_red, image[i][tmp_wdt].rgbtRed);
                    image[i][tmp_wdt].rgbtRed = image[i][j].rgbtRed;
                    image[i][tmp_wdt].rgbtGreen = image[i][j].rgbtGreen;
                    image[i][tmp_wdt].rgbtBlue = image[i][j].rgbtBlue;
                    //printf("%i = %i\n", image[i][tmp_wdt].rgbtRed, image[i][j].rgbtRed );
                    image[i][j].rgbtRed = tmp_red;
                    image[i][j].rgbtGreen = tmp_green;
                    image[i][j].rgbtBlue = tmp_blue;
                    //printf("%i = %i\n", image[i][j].rgbtRed, tmp_red );
                    //printf("%i , %i\n", image[i][j].rgbtRed, image[i][tmp_wdt].rgbtRed);

                }
            }

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int red, green, blue, avg_times;
    
    //copy the table to another for calculating original valuse
    RGBTRIPLE or_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            or_image[i][j] = image[i][j];
        }
    }
    

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = 0;
            green = 0;
            blue = 0;
            avg_times = 0;
            // different senarios #1
            if (i >= 0 && j >= 0)
            {
                red += or_image[i][j].rgbtRed;
                green += or_image[i][j].rgbtGreen;
                blue += or_image[i][j].rgbtBlue;
                avg_times++;
            }
            // different senarios #2
            if (i >= 0 && j - 1 >= 0)
            {
                red += or_image[i][j - 1].rgbtRed;
                green += or_image[i][j - 1].rgbtGreen;
                blue += or_image[i][j - 1].rgbtBlue;
                avg_times++;
            }
            // different senarios #3
            if (i - 1 >= 0 && j >= 0)
            {
                red += or_image[i - 1][j].rgbtRed;
                green += or_image[i - 1][j].rgbtGreen;
                blue += or_image[i - 1][j].rgbtBlue;
                avg_times++;
            }
            // different senarios #4
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                red += or_image[i - 1][j - 1].rgbtRed;
                green += or_image[i - 1][j - 1].rgbtGreen;
                blue += or_image[i - 1][j - 1].rgbtBlue;
                avg_times++;
            }
            // different senarios #5
            if (i >= 0 && j + 1 >= 0 && i >= 0 && j + 1 < width)
            {
                red += or_image[i][j + 1].rgbtRed;
                green += or_image[i][j + 1].rgbtGreen;
                blue += or_image[i][j + 1].rgbtBlue;
                avg_times++;
            }
            // different senarios #6
            if (i - 1 >= 0 && j + 1 >= 0 && i - 1 >= 0 && j + 1 < width)
            {
                red += or_image[i - 1][j + 1].rgbtRed;
                green += or_image[i - 1][j + 1].rgbtGreen;
                blue += or_image[i - 1][j + 1].rgbtBlue;
                avg_times++;
            }
            // different senarios #7
            if (i + 1 >= 0 && j >= 0 && i + 1 < height && j >= 0)
            {
                red += or_image[i + 1][j].rgbtRed;
                green += or_image[i + 1][j].rgbtGreen;
                blue += or_image[i + 1][j].rgbtBlue;
                avg_times++;
            }
            // different senarios #8
            if (i + 1 >= 0 && j - 1 >= 0 && i + 1 < height && j - 1 >= 0)
            {
                red += or_image[i + 1][j - 1].rgbtRed;
                green += or_image[i + 1][j - 1].rgbtGreen;
                blue += or_image[i + 1][j - 1].rgbtBlue;
                avg_times++;
            }
            // different senarios #9
            if (i + 1 >= 0 && j + 1 >= 0 && i + 1 < height && j + 1 < width)
            {
                red += or_image[i + 1][j + 1].rgbtRed;
                green += or_image[i + 1][j + 1].rgbtGreen;
                blue += or_image[i + 1][j + 1].rgbtBlue;
                avg_times++;
            }
            // calculate the average of the surrounding pixels and put it as a value at the image structure
            image[i][j].rgbtRed = (int)roundf(red / (float)avg_times);
            image[i][j].rgbtGreen = (int)roundf(green / (float)avg_times);
            image[i][j].rgbtBlue = (int)roundf(blue / (float)avg_times);
        }
    }


    return;
}
