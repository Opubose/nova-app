# README for the downsampler!

## What is this?

You're looking at a fairly simple downsampling program written in pure `C++`, utilizing the STL thoroughly. It reads in a pointcloud in the form of a `csv` file. It then downsamples it by distributing all the points into a voxel grid and randomly chooses one point from each voxel. The downsampled points are then written to another `csv` file for your perusal. The size of a voxel can be tweaked to get different results. A smaller voxel means a finer approximation at the cost of less points downsampled. A larger voxel means a coarser approximation with the cost(?) of more points downsampled. I have tried to follow modern `C++` design principles in this project and the final product is fairly fast and efficient in my unbiased opinion.

## Okay, how do I run it?

I was waiting for you to ask that.

### Important: `C++17` (or above) is required to run this program!!! I have tested this program using both the `g++` and `clang` compilers on an Linux machine. You may want to tweak these steps if you are on a Windows machine.

1. Make a directory named `bin` inside the project directory.
2. Compile the file (`Agastya Bose.cpp`) with the following command in your terminal, depending on what compiler you have:

    `clang++ -std=c++17 -O3 'Agastya Bose.cpp' -o bin/a.out`

    or

    `g++ -std=c++17 -O3 'Agastya Bose.cpp' -o bin/a.out`

    (*Hint*: The `-std=c++17` flag can be set to any valid C++ version >= 17)
3. Run the compiled binary from the previous step by typing the following command in your terminal:

    `bin/a.out <path to your input.csv file>`

    Obviously, replace `<path to your input.csv file>` with the actual path to the `csv` file. I usually keep that in the same directory as my source code.
4. If everything went according to plan, you'll be able to see a freshly written `output.csv` file in the project directory!

# That was some mighty fine downsampling. Thank you!