#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <chrono>
#include <random>
#include <algorithm>
#include <cmath>
#include <sstream>

// A simple 3D point class
struct point3
{
    float x, y, z;

    point3(const double x_, const double y_, const double z_) : x(x_), y(y_), z(z_) {}
};

std::vector<point3> readFile(const std::string&);
std::vector<point3> downsample(const std::vector<point3>&);
void writeFile(const std::vector<point3>&);

int main(const int argc, const char *argv[])
{
    try
    {
        if (argc != 2)  // Only one argument (the path to the input.csv file) should be provided, along with the name of the executable
        {
            throw std::invalid_argument("ERROR: Invalid number of arguments provided.\n"
                                        "Expected value of argc = 2\n"
                                        "Actual value = " + std::to_string(argc) + "\n"
                                        "USAGE: <executable path> <input file path>");
        }

        std::vector<point3> points = readFile(argv[1]);
        std::vector<point3> downsampled_points = downsample(points);
        writeFile(downsampled_points);
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
 * @returns a vector of all the 3D points read from the input file
 */
std::vector<point3> readFile(const std::string &filepath)
{
    std::ifstream pointcloud(filepath);

    if (!pointcloud)
    {
        throw std::domain_error("ERROR: Could not open the input file.\n"
                                "Please check your file path and make sure that the file actually exists.");
    }

    std::vector<point3> points;
    std::string line;

    getline(pointcloud, line);  // Skipping the first line of the csv (the headers are not useful!)
    
    // Reading the data
    while (getline(pointcloud, line))
    {
        float x, y, z;
        char comma;

        std::istringstream iss(line);   // To read from a line 
        while (iss)
        {
            iss >> x >> comma >> y >> comma >> z >> comma; // comma is a dummy variable used to parse the comma between two numbers as well as the newline character at the end of the line
            points.emplace_back(x, y, z);
        }
    }
    pointcloud.close();

    std::cout << "The original pointcloud has " << points.size() << " points.\n\n";

    return points;  // I love return-value optimization
}

/**
 * Downsamples the points read from the input file. The process used to downsample involves distributing all the points in a voxel grid and randomly choosing a point from each voxel.
 * @param points: the vector of all points read from the input file
 * @returns a vector of randomly chosen points from each voxel in the voxel grid
 */
std::vector<point3> downsample(const std::vector<point3> &points)
{
    std::vector<point3> lesser_points;

    const float VOXELSIZE = 0.01f;  // Change this as needed. A greater voxel size tends to give a coarser downsample (less points overall) while a lesser voxel size tends to give a finer downsample (more points overall).
    std::map<std::tuple<int, int, int>, std::vector<point3>> voxelmap;  // Voxel grid
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();    // Seed for the random number engine

    for (const point3 &point : points)
    {
        // Voxels are discrete structures
        const int voxel_x = static_cast<int>(round(point.x / VOXELSIZE));
        const int voxel_y = static_cast<int>(round(point.y / VOXELSIZE));
        const int voxel_z = static_cast<int>(round(point.z / VOXELSIZE));

        voxelmap[{voxel_x, voxel_y, voxel_z}].push_back(point); // Distributing all the points from the cloud to a voxel grid
    }

    for (const auto &voxel : voxelmap)  // For each voxel...
    {
        const std::vector<point3> &voxel_points = voxel.second; // Takes the vector of points in the current voxel
        if (!voxel_points.empty())
        {
            /*
             * The below function will select a point at random from voxel_points and will put it in lesser_points. Uses the mersenne twister engine to remove bias from the sampling.
             */
            // CAUTION: std::sample needs C++17 or above!
            std::sample(voxel_points.begin(),
                        voxel_points.end(),
                        std::back_inserter(lesser_points),
                        1,
                        std::mt19937{seed});
        }
    }

    std::cout << "The downsampled pointcloud has " << lesser_points.size() << " points.\n\n";

    return lesser_points;
}

/**
 * Writes to the output file
 * @param downsampled_points: the vector of downsampled points from the downsample() function
 */
void writeFile(const std::vector<point3> &downsampled_points)
{
    const std::string OUTFILEPATH = "output.csv";   // Change this as needed
    std::ofstream downsampled(OUTFILEPATH);
    downsampled << "x,y,z\n";    // Writing the headers

    for (const point3 &p : downsampled_points)
    {
        downsampled << p.x << ',' << p.y << ',' << p.z << '\n';
    }
    
    downsampled.close();

    std::cout << "The downsampled data can be found in " << OUTFILEPATH << std::endl;
}