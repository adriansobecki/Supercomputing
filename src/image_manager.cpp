#include "image_manager.h"
#include <string>
#include <algorithm>

imageManager::imageManager(std::string Name):
fileName(Name),
image(nullptr),
outputImage(nullptr)
{
    headerInfo[2] = '\0';
}

imageManager::~imageManager()
{
    if(image)
        free(image);
    if(outputImage)
        free(outputImage);
}

bool imageManager::loadImage()
{
    FILE *File;
    File = fopen(fileName.c_str(), "rb");
    if(File == NULL) {
        return 0;
    }
    fscanf(File, "%c%c\n", &headerInfo[0], &headerInfo[1]);
    fscanf(File, "%d %d\n", &width, &height);
    fscanf(File, "%d\n", &colorDepth);

    //std::cout << headerInfo << std::endl;
    //std::cout << width << std::endl << height << std::endl;
    //std::cout << colorDepth << std::endl;
    if(std::string(headerInfo)=="P6")
    {
        image = (unsigned char*)malloc(sizeof(char)*width*height*3);
        fread(image, width*height*3, 1, File);
        return true;
    }
    fclose(File);
    return false;
}

bool imageManager::saveImage()
{
    if(outputImage == nullptr)
        return false;

    FILE *Result;
    std::string newFileName = fileName.substr(0, fileName.size()-3)+"pgm";

    Result = fopen(newFileName.c_str(), "wb");
    if(Result == NULL)
        return false;

    fprintf(Result, "P5\n%d %d\n%d\n", width, height, colorDepth);

    for(int i=0; i<width*height;i++)
        fprintf(Result, "%c", static_cast<unsigned char>(outputImage[i]));

    fclose(Result);
    return true;
}

bool imageManager::toMonochrome()
{
    if(outputImage == nullptr)
        outputImage = (int*)malloc(sizeof(int)*(width)*(height));

    if(std::string(headerInfo)=="P6")
    {
        int k = 0;
        for(int i=0; i<width*height*3;i+=3)
            outputImage[k++] = int(image[i]/3 + image[i+1]/3 + image[i+2]/3);

        headerInfo[1] = '5';
        return true;
    }

    return false;
}

bool imageManager::thresholding(int threshold)
{
    if(outputImage == nullptr)
        return false;

    if(std::string(headerInfo)=="P5")
    {
        for(int i=0; i<width*height;i++)
        {
            if(outputImage[i]>threshold)
                outputImage[i] = 255;
            else
                outputImage[i] = 0;
        }
        return true;
    }
    return false;
}

bool imageManager::edgeDetection()
{
    if(outputImage == nullptr)
        return false;

    int* imageEdgeDetection = (int*)malloc(sizeof(int)*(width-2)*(height-2)); //unsigned char*
    if(std::string(headerInfo)=="P5")
    {
        int z = 0;
        int max,min;
        max = min = 0;
        for(int k=1;k<height-1;k++)
        {
            for(int i=1;i<width-1;i++)
            {
                int val = static_cast<int>(outputImage[i+k*width])*(-8) + static_cast<int>(image[(i-1)+(k-1)*width]) + static_cast<int>(image[(i)+(k-1)*width]) + static_cast<int>(image[(i+1)+(k-1)*width]) + static_cast<int>(image[(i-1)+k*width]) + static_cast<int>(image[(i+1)+k*width]) + static_cast<int>(image[(i-1)+(k+1)*width]) + static_cast<int>(image[(i)+(k+1)*width]) + static_cast<int>(image[(i+1)+(k+1)*width]);
                //image[i+k*width*3] = (val + 8 * 255)/16;
                //imageEdgeDetection[z] = static_cast<unsigned char>((val + 8 * 255)/16);
                //std::cout << val << '\n';
                imageEdgeDetection[z] = val;
                z++;
                if(val>max)
                    max = val;
                if(val<min)
                    min = val;
                //image[i+k*width*3] = val;
                //std::cout << val << " ";
            }
        }
        double diff = max - min;
        double scale = 255/diff;

        width = width - 2;
        height = height - 2;

        if(outputImage != nullptr)
        {
            free(outputImage);
            outputImage = (int*)malloc(sizeof(int)*(width)*(height));
        }

        for(int i=0; i<(width)*(height);i++)
            outputImage[i] = int((double(imageEdgeDetection[i]-min)*scale));
            
        free(imageEdgeDetection);
        //std::cout << max << " "<< min << "\n";
        return true;
    }
    else
        return false;
}