# Miniqbt, a runtime for the IBM Quantum experience
## Introduction
IBM research  [released](https://www.research.ibm.com/ibm-q/) a quantum computer accessable for the cloud.
MiniQbt emulates the assembly language up to 20 qubits (the header can go up to infinite qubits). It's written in c++ 14 and the library actually emulating the quantum instructions is header only.


## Installation
### MacOS
Install Eigen3 through [brew ](https://brew.sh) and install cmake, after that download the source of miniQbt.
Navigate to the directory you downloaded miniqbt and create a new directory called build. execute in the build directory cmake .. , after it's done execute make install.

### Ubuntu
Compile  [Eigen3](http://eigen.tuxfamily.org/index.php?title=Main_Page) from source and install it. download the source of miniQbt and navigate to the directory you saved it. Create a new directory called build. execute in the build directory cmake.. , after it's done execute make install. 

### Windows 10
Install ubuntu for windows 10 and execute the ubuntu instructions


