#include "image_manager.h"
#include <string>
#include <algorithm>

imageManager::imageManager(std::string Name):
fileName(Name),
image(nullptr),
imageEdgeDetection(nullptr),
edgeDetectionCalled(false)
{
    headerInfo[2] = '\0';
}

imageManager::~imageManager()
{
    if(image)
        free(image);
    if(imageEdgeDetection)
        free(imageEdgeDetection);
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
    FILE *Result;
    std::string newFileName;
    if(std::string(headerInfo)=="P5")
        newFileName = fileName.substr(0, fileName.size()-3)+"pgm";
    else
        newFileName = fileName;

    Result = fopen(newFileName.c_str(), "wb");
    if(Result == NULL)
        return false;

    if(!edgeDetectionCalled)
    {
        fprintf(Result, "P5\n%d %d\n%d\n", width, height, colorDepth);
        for(int i=0; i<width*height*3;i+=3)
            fprintf(Result, "%c", image[i]);
    }
    else
    {
        fprintf(Result, "P5\n%d %d\n%d\n", width-2, height-2, colorDepth);
        for(int i=0; i<(width-2)*(height-2);i++)
            fprintf(Result, "%c", static_cast<unsigned char>(imageEdgeDetection[i]));
    }

    fclose(Result);
    return true;
}

bool imageManager::toMonochrome()
{
    if(std::string(headerInfo)=="P6")
    {
        for(int i=0; i<width*height*3;i+=3)
            image[i] = image[i]/3 + image[i+1]/3 + image[i+2]/3;

        headerInfo[1] = '5';
        return true;
    }
    else
        return false;
}

bool imageManager::thresholding(int threshold)
{
    if(std::string(headerInfo)=="P5")
    {
        if(!edgeDetectionCalled)
        {
            for(int i=0; i<width*height*3;i+=3)
            {
                if(image[i]>threshold)
                    image[i] = 255;
                else
                    image[i] = 0;
            }
            return true;
        }
        else
        {
            for(int i=0; i<(width-2)*(height-2);i++)
            {
                if(imageEdgeDetection[i]>threshold)
                    imageEdgeDetection[i] = 255;
                else
                    imageEdgeDetection[i] = 0;
            }
            return true;
        }
    }
    else
        return false;
}

bool imageManager::edgeDetection()
{
    imageEdgeDetection = (int*)malloc(sizeof(int)*(width-2)*(height-2)); //unsigned char*
    if(std::string(headerInfo)=="P5")
    {
        int z = 0;
        int max,min;
        max = min = 0;
        for(int k=1;k<height-1;k++)
        {
            for(int i=3;i<width*3-3;i+=3)
            {
                int val = static_cast<int>(image[i+k*width*3])*(-8) + static_cast<int>(image[(i-3)+(k-1)*width*3]) + static_cast<int>(image[(i)+(k-1)*width*3]) + static_cast<int>(image[(i+3)+(k-1)*width*3]) + static_cast<int>(image[(i-3)+k*width*3]) + static_cast<int>(image[(i+3)+k*width*3]) + static_cast<int>(image[(i-3)+(k+1)*width*3]) + static_cast<int>(image[(i)+(k+1)*width*3]) + static_cast<int>(image[(i+3)+(k+1)*width*3]);
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
        for(int i=0; i<(width-2)*(height-2);i++)
        {
            imageEdgeDetection[i] = int((double(imageEdgeDetection[i]-min)*scale));
        }
        //std::cout << max << " "<< min << "\n";
        edgeDetectionCalled = true;
        return true;
    }
    else
        return false;
}