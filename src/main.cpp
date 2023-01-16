
#include <iostream>
#include "image_manager.h"
#include <mpi.h>
#include <chrono>

const std::string baseNameWithPath = "data/image";
const std::string baseExtension = ".ppm";

int main(int argc, char *argv[])
{
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int amountOfFiles = atoi(argv[1]);
    int userChoice = 3;
    int filesPerProcessor = amountOfFiles/size;
    int restFiles = amountOfFiles%size;

    //std::cout << "\nVideo manager:\n1 - To monochrome\n2 - Thresholding\n3 - Edge detection\n";
    //while(!(std::cin >> userChoice) || !(userChoice>0 && userChoice<4)){std::cin.clear();std::cin.ignore();}  
    //std::cout << amountOfFiles << " " << filesPerProcessor <<  " " << rank*filesPerProcessor+1 << " " <<  rank*filesPerProcessor+1+filesPerProcessor;
    auto start = std::chrono::steady_clock::now();
    for(int i=rank*filesPerProcessor+1; i<=rank*filesPerProcessor+filesPerProcessor;i++)
    {
        imageManager test(baseNameWithPath+std::to_string(i)+baseExtension);
        test.loadImage();
        test.toMonochrome();
        if(userChoice==2)
            test.thresholding();
        else if(userChoice==3)
        {
            test.edgeDetection();
            test.thresholding(40);
        }
            
        test.saveImage();
    }
    if(restFiles>rank)
    {
        imageManager test(baseNameWithPath+std::to_string(amountOfFiles-rank)+baseExtension);
        test.loadImage();
        test.toMonochrome();
        if(userChoice==2)
            test.thresholding();
        else if(userChoice==3)
            test.edgeDetection();
            
        test.saveImage();
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Rank: "<< rank << " elapsed time: " << elapsed_seconds.count() << "s\n";
    MPI_Finalize();

    return 0;
}
