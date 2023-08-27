#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

const std::string OUTFILEPATH = "output.csv";

/**
 * A simple 3D point class
 */
struct point3
{
    double x, y, z;
    point3(const double x_, const double y_, const double z_) : x(x_), y(y_), z(z_) {}
};

std::vector<point3> readFile(const std::string&);
void writeFile();

int main(const int argc, const char *argv[])
{
    try
    {
        if (argc != 2)  // Only one argument (the path to the input.csv file) should be provided, along with the name of the executable
        {
            throw std::invalid_argument("Invalid number of arguments provided. Expected value of argc = 2.\nActual value = " + std::to_string(argc) + ".\nUSAGE: ./<executable name> <file path>");
        }

        std::vector<point3> points = readFile(std::string(argv[1]));

        writeFile();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';

        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

/**
 * Reads the input file
 * @param filepath: the path to the input file as a string
 * @throws an std::domain_error() if no file exists at the given file path or if the path is invalid
 * @returns an std::vector of all the 3D points read from the input file
 */
std::vector<point3> readFile(const std::string &filepath)
{
    std::ifstream pointcloud(filepath);

    if (!pointcloud)
    {
        throw std::domain_error("Invalid file path - \"" + filepath + "\" - provided. Please check your file path and make sure that the file actually exists.");
    }

    std::vector<point3> points;
    std::string line;

    getline(pointcloud, line);  // Skipping the first line of the csv (the headers are not useful!)
    
    // Reading the data
    while (getline(pointcloud, line))
    {
        double x, y, z;
        char comma;

        std::istringstream iss(line);   // To read from a line 
        while (iss)
        {
            iss >> x >> comma >> y >> comma >> z; // comma is a dummy variable used only to parse the comma between two numbers
            points.emplace_back(point3(x, y, z));
        }
    }
    pointcloud.close();

    return points;
}

void writeFile()
{
    std::ofstream downsampled(OUTFILEPATH);
    downsampled << "x,y,z\n";    // Writing the headers
    
    downsampled.close();
}