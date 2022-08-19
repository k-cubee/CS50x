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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Declares the Gx and Gy values
    int Gx_arr[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy_arr[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
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
            int GxRed = 0;
            int GyRed = 0;
            int GxGreen = 0;
            int GyGreen = 0;
            int GxBlue = 0;
            int GyBlue = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Calculates the Gx and Gy value of each color according to their corresponding Gx and Gy values
                    if (!((i + k < 0 || i + k > height - 1) || (j + l < 0 || j + l > width - 1)))
                    {
                        GxRed += copy[i + k][j + l].rgbtRed * Gx_arr[1 + k][1 + l];
                        GyRed += copy[i + k][j + l].rgbtRed * Gy_arr[1 + k][1 + l];
                        GxGreen += copy[i + k][j + l].rgbtGreen * Gx_arr[1 + k][1 + l];
                        GyGreen += copy[i + k][j + l].rgbtGreen * Gy_arr[1 + k][1 + l];
                        GxBlue += copy[i + k][j + l].rgbtBlue * Gx_arr[1 + k][1 + l];
                        GyBlue += copy[i + k][j + l].rgbtBlue * Gy_arr[1 + k][1 + l];
                    }
                }
            }
            // Calculates the final color values
            int finalRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
            int finalGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
            int finalBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
            // Caps the final value at 255
            if (finalRed > 255)
            {
                finalRed = 255;
            }
            if (finalGreen > 255)
            {
                finalGreen = 255;
            }
            if (finalBlue > 255)
            {
                finalBlue = 255;
            }
            // Sets the new rgb values
            image[i][j].rgbtRed = finalRed;
            image[i][j].rgbtGreen = finalGreen;
            image[i][j].rgbtBlue = finalBlue;
        }
    }
    return;
}
