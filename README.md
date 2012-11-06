
#Development

## Install Dependancies

The project depends of the following libraries :

+ [gflags 2.0](http://code.google.com/p/gflags)
+ [boost 1.52.0](http://www.boost.org/)

Check if these libraries are installed on your system, otherwise get a local copyon your machine and install each one.
Choose the easy build install for boost.

## Compiling

Compile project source files :

	$ make findd

The final executable will be generated in the root directory as `findd`.

## Run test

First, compile test files which are located in the `unittest/` directory :

	$ make test

Then, run the generated executable and check if all tests succeed :

	$ ./test
	
# License

This software is under BSD license. View the LICENSE file for terms of use.

Copyright © 2012 Florian Mhun, Sara Ressam, Jérôme Cornet, Bastien Nouhant.