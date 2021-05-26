#include "helpers.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float favg;
    int avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <  width; j++)
        {
            favg = (float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;
            avg = round(favg);

            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imagecpy [height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <  width; j++)
        {
            imagecpy[i][j].rgbtRed = image[i][j].rgbtRed;
            imagecpy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            imagecpy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <  width; j++)
        {
            image[i][j].rgbtRed = imagecpy[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = imagecpy[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = imagecpy[i][width - 1 - j].rgbtBlue;
        }
    }

}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imagecpy [height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <  width; j++)
        {
            imagecpy[i][j].rgbtRed = image[i][j].rgbtRed;
            imagecpy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            imagecpy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    float R;
    float G;
    float B;
    int counter;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <  width; j++)
        {
            R = 0;
            G = 0;
            B = 0;
            counter = 0;
            for (int x = -1 ; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    if (((i + x) >= 0) && ((j + y) >= 0) && ((i + x) < height) && ((j + y) < width))
                    {
                        R += imagecpy[i + x][j + y].rgbtRed;
                        G += imagecpy[i + x][j + y].rgbtGreen;
                        B += imagecpy[i + x][j + y].rgbtBlue;
                        counter += 1;
                    }
                }
            }
            image[i][j].rgbtRed = (int) round(R / counter);
            image[i][j].rgbtGreen = (int) round(G / counter);
            image[i][j].rgbtBlue = (int) round(B / counter);
        }
    }
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imagecpy [height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <  width; j++)
        {
            imagecpy[i][j].rgbtRed = image[i][j].rgbtRed;
            imagecpy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            imagecpy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    
    float Gx [3][3];
    Gx[0][0] = -1;
    Gx[0][1] = 0;
    Gx[0][2] = 1;
    Gx[1][0] = -2;
    Gx[1][1] = 0;
    Gx[1][2] = 2;
    Gx[2][0] = -1;
    Gx[2][1] = 0;
    Gx[2][2] = 1;
    
    float Gy [3][3];
    Gy[0][0] = -1;
    Gy[0][1] = -2;
    Gy[0][2] = -1;
    Gy[1][0] = 0;
    Gy[1][1] = 0;
    Gy[1][2] = 0;
    Gy[2][0] = 1;
    Gy[2][1] = 2;
    Gy[2][2] = 1;
    
    float RGx;
    float RGy;
    float GGx;
    float GGy;
    float BGx;
    float BGy;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <  width; j++)
        {
            RGx = 0;
            RGy = 0;
            GGx = 0;
            GGy = 0;
            BGx = 0;
            BGy = 0;
            for (int x = -1 ; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    if (((i + x) >= 0) && ((j + y) >= 0) && ((i + x) < height) && ((j + y) < width))
                    {
                        RGx += imagecpy[i + x][j + y].rgbtRed * Gx[x + 1][y + 1];
                        GGx += imagecpy[i + x][j + y].rgbtGreen * Gx[x + 1][y + 1];
                        BGx += imagecpy[i + x][j + y].rgbtBlue * Gx[x + 1][y + 1];
                        RGy += imagecpy[i + x][j + y].rgbtRed * Gy[x + 1][y + 1];
                        GGy += imagecpy[i + x][j + y].rgbtGreen * Gy[x + 1][y + 1];
                        BGy += imagecpy[i + x][j + y].rgbtBlue * Gy[x + 1][y + 1];
                    }
                }
            }   
            float RG = sqrt(pow(RGx, 2) + pow(RGy, 2));
            float GG = sqrt(pow(GGx, 2) + pow(GGy, 2));
            float BG = sqrt(pow(BGx, 2) + pow(BGy, 2));
            if (RG >= 255)
            {
                RG = 255;
            }
            if (GG >= 255)
            {
                GG = 255;
            }
            if (BG >= 255)
            {
                BG = 255;
            }
            image[i][j].rgbtRed = (int) round(RG);
            image[i][j].rgbtGreen = (int) round(GG);
            image[i][j].rgbtBlue = (int) round(BG);
        }
    } 
}
