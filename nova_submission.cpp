#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

const std::string outfilename = "output.csv";

void process_line()
{

}

int main(const int argc, const char *argv[])
{
    try
    {
        std::ifstream pointcloud;
        std::ofstream downsampled;

        if (argc != 2)  // argv[1] is the 
        {
            throw std::invalid_argument("Invalid number of arguments provided. Expected value of argc = 2.\nActual value = " + std::to_string(argc) + ".\nUSAGE: ./<executable name> <file path>");
        }

        pointcloud.open(std::string(argv[1]));  // Opening the csv file

        if (!pointcloud)
        {
            throw std::domain_error("Invalid file path - \"" + std::string(argv[1]) + "\" - provided. Please check your file path and make sure that the file actually exists.");
        }

        std::string line;

        while (getline(pointcloud, line))
        {
            
        }

        pointcloud.close();
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << '\n';

        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}