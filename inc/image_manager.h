#include <iostream>
#include <vector>


class imageManager
{
    private:
        char headerInfo[3];
        int width, height, colorDepth;
        unsigned char* image;
        int* imageEdgeDetection;
        std::string fileName;
        bool edgeDetectionCalled;

    public:
        imageManager(std::string Name);
        ~imageManager();
        bool loadImage();
        bool saveImage();
        bool toMonochrome();
        bool thresholding(int threshold=125);
        bool edgeDetection();
};