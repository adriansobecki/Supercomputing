#include "video_manager.h"
#include "image_processing.h"
#include <opencv2/core.hpp>

videoManager::videoManager()
{
    std::cout << "OpenCV version: " << CV_VERSION << std::endl;
    std::cout << "videoManager constr";
    imageProcessing::toMonochrome();
}

videoManager::~videoManager()
{

}

bool videoManager::loadVideo(std::string videoName)
{
    cv::VideoCapture capture(filename);
    cv::Mat frame;

    if( !capture.isOpened() )
        throw "Error when reading steam_avi";

    while(true)
    {
        capture >> frame;
        if(frame.empty())
            break;
    }
}