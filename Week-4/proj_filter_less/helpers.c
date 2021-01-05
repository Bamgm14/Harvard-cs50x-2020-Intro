#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            BYTE gray = round((image[x][y].rgbtBlue + image[x][y].rgbtGreen + image[x][y].rgbtRed) / 3.0); //Converts to Gray
            image[x][y].rgbtBlue = gray;
            image[x][y].rgbtGreen = gray; 
            image[x][y].rgbtRed = gray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            int sepiaRed = round(.393 * image[x][y].rgbtRed + .769 * image[x][y].rgbtGreen + .189 * image[x][y].rgbtBlue);
            int sepiaGreen = round(.349 * image[x][y].rgbtRed + .686 * image[x][y].rgbtGreen + .168 * image[x][y].rgbtBlue);
            int sepiaBlue = round(.272 * image[x][y].rgbtRed + .534 * image[x][y].rgbtGreen + .131 * image[x][y].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;// Checks Overflow Conditions
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255; // Checks Overflow Conditions
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255; // Checks Overflow Conditions
            }
            image[x][y].rgbtRed = sepiaRed;
            image[x][y].rgbtBlue = sepiaBlue;
            image[x][y].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int mid = width / 2;
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < mid; y++)
        {
            RGBTRIPLE temp = image[x][y]; //Saves pixel temporary
            image[x][y] = image[x][width - y - 1];
            image[x][width - y - 1] = temp; // Switches Pixels
        }
    }
    return;
}
typedef struct // Unique Structure 
{
    float red;
    float green;
    float blue;
}
setup;
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    setup temp[height][width];
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            //Sets variable
            temp[x][y].red = 0;
            temp[x][y].green = 0;
            temp[x][y].blue = 0;
            float divisor = 0.0;
            for (int a = -1; a < 2; a++)
            {
                for (int b = -1; b < 2; b++)
                {
                    int neighx = x + a;  //Boundary Conditions
                    int neighy = y + b;
                    if ((neighx > -1) && (neighy > -1) && (neighx < height) && (neighy < width)) //Checks if looks for pixels are out of bound
                    {
                        temp[x][y].red += image[neighx][neighy].rgbtRed;
                        temp[x][y].green += image[neighx][neighy].rgbtGreen;
                        temp[x][y].blue += image[neighx][neighy].rgbtBlue;
                        divisor += 1.0;
                    }
                }
            }
            temp[x][y].red = temp[x][y].red / divisor;
            temp[x][y].green = temp[x][y].green / divisor;
            temp[x][y].blue = temp[x][y].blue / divisor; // Calculates final value
        }
    }
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y].rgbtRed = round(temp[x][y].red);
            image[x][y].rgbtGreen = round(temp[x][y].green);
            image[x][y].rgbtBlue = round(temp[x][y].blue);
        }
    }
    return;
}
