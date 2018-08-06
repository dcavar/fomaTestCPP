# Foma example codes

Copyright 2015-2018 by [Damir Cavar](http://damir.cavar.me/)

Last edited: 2018-08-06, Damir Cavar


## Includes and Libraries

You will need [Foma](https://fomafst.github.io) and all its include and library files on your system to be able to compile this test code.

Included is a simplified and reduced English morphology compiled into a Finite State Transducer for the use with Foma.


## Build the binary

To compile this example, you need to have the entire Foma collection of binaries, includes and libraries set up on your system. You will also need some C++11 compiler and various other libraries for it, for example the [Boost](https://www.boost.org) libraries.

The project is a [CMake](https://cmake.org) project. Make sure that you have also [CMake](https://cmake.org) installed and set up on your system.

To create the running binary for the code in *FomaMWT*, in the folder run:

	cmake CMakeList.txt

This will generate the *Makefile* and other files in the same folder. Run:

	make

and it should compile correctly, if all the paths and folders are OK, and if the libraries were found.


If you want to test the speed of the processor, run the following command:

	time ./fomatest test.txt > res.txt

Create a larger list of words in a text file and run it through the test tool. On an Intel i7 CPU with Fedora Linux I achieve something in the range of 300,000 tokens per second, with average number of ambiguous morphological analyses for each string.
