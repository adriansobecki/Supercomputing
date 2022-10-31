
#include <iostream>
#include "image_manager.h"

const std::string baseNameWithPath = "data/image";
const std::string baseExtension = ".ppm";

int main(int argc, char *argv[])
{
    int amountOfFiles = atoi(argv[1]);
    int userChoice = 0;


    std::cout << "\nVideo manager:\n1 - To monochrome\n2 - Thresholding\n3 - Edge detection\n";
    while(!(std::cin >> userChoice) || !(userChoice>0 && userChoice<4)){std::cin.clear();std::cin.ignore();}  

    std::cout << "Please wait...\n";

    for(int i=1; i<=amountOfFiles;i++)
    {
        imageManager test(baseNameWithPath+std::to_string(i)+baseExtension);
        test.loadImage();
        test.toMonochrome();
        if(userChoice==2)
            test.thresholding();
        else if(userChoice==3)
            test.edgeDetection();
            
        test.saveImage();
    }

    return 0;
}
