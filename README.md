#Installation

For linux and darwin platforms, just run the following commands :

	$ make
	$ make install

The final executable is installed into `/usr/local/bin`, then test the installation by running :

	$ findd -h

For windows user, run `make dist` and copy 32 bits or 64 bits executable from `dist` directory in your preferred location.

#Development

## Compiling

Compile project source files :

	$ make findd

The executable will be generated in the root directory as `findd`.

## Run test

First, compile test files which are located in the `unittest/` directory :

	$ make test

Then, run the generated executable and check if all tests succeed :

	$ ./test

# Code

For developer, you should respect these rules before submitting your changes :

+ Don't push your code if it doesn't compile. 
+ Use 2 spaces for indentation (no tabs).
+ Test your code as much as possible.
+ Respect the project's coding style, inspired from [google c++ style guide](http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml)

# License

This software is under BSD license. View the LICENSE file for terms of use.

Copyright © 2012 Florian Mhun, Sara Ressam, Jérôme Cornet, Bastien Nouhant, from University of Poitier (FR).