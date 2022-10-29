#include <iostream>
#include <vector>


class videoManager
{
    private:
        //std::vector<cv::Mat*> video;

    public:
        videoManager();
        ~videoManager();
        bool loadVideo(std::string videoName);
};