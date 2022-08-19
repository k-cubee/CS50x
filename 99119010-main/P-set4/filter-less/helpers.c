#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            // Calculates the average value of the three colors
            float nonr_average_value = (pixel.rgbtBlue + pixel.rgbtGreen +  pixel.rgbtRed) / 3.0;
            // Rounds the average value to the nearest whole number
            int average_value = round(nonr_average_value);
            // Sets all three colors to have the same average value
            image[i][j].rgbtBlue = average_value;
            image[i][j].rgbtGreen = average_value;
            image[i][j].rgbtRed = average_value;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Gets the original color values
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;
            // Calculates the new color values according to the formula
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            // Caps sepia values at 255
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            // Sets the new color values
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Sets the last pixel of the image
            int last_pixel = width - 1;
            // Swaps a pixel on one side with its opposite (e.g 0 and last, 1 and last - 1)
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][last_pixel - j];
            image[i][last_pixel - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Gets a copy of the image where the rgb values will be calculated, but not modified
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initializes variables
            int totalRed = 0;
            int totalGreen = 0;
            int totalBlue = 0;
            float pixel_count = 0.00;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Calculates the total box value and increments the pixel count if it is valid
                    if (!((i + k < 0 || i + k > height - 1) || (j + l < 0 || j + l > width - 1)))
                    {
                        totalRed += copy[i + k][j + l].rgbtRed;
                        totalGreen += copy[i + k][j + l].rgbtGreen;
                        totalBlue += copy[i + k][j + l].rgbtBlue;
                        pixel_count++;
                    }
                }
            }
            // Calculates average and sets the new rgb values
            image[i][j].rgbtRed = round(totalRed / pixel_count);
            image[i][j].rgbtGreen = round(totalGreen / pixel_count);
            image[i][j].rgbtBlue = round(totalBlue / pixel_count);
        }
    }
    return;
}
