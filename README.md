# BANK2BMP
 A tool for extracting image data from Balite/Baltik 2.0/3.0 BANK files.  
  
# About
This project is a part of a bigger project called "Project B" that aims to reimplement Baltie/Baltik 2.0 in C++.  
This tool allows to extract the image data from the Bank files Baltie/Baltik uses to store tiles.  
  
# Usage
`bank2bmp <infile> [params]`  
## Parameters
`-o <path>  -  output path`  
If output path is not provided, the input file name will be used as output with added .bmp extension.  
  
# Compiling / Requirements
This project was made in the Code::Blocks IDE.  
You can also compile it using these commands (requires cmake):  
`mkdir build && cd build`  
`cmake ..`  
`make`  
  
In order to compile the project, you need to install essentials build tools as well as SDL2 development libraries.  
You can install them on Linux using:  
`# apt install build-essential`  
`# apt install libsdl2-dev`  
or if you're using Windows, you can find the library [here](https://github.com/libsdl-org/SDL/releases/latest).  
  
# License
bank2bmp is licensed under the MIT License, see [LICENSE](https://github.com/GreffMASTER/bank2bmp/blob/main/LICENSE) for details.
