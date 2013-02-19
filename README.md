#Installation

For unix platforms, just run the following commands :

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

Windows users can compile the project using [MinGw](http://www.mingw.org/wiki/Getting_Started), then running `make` command will output a win32 compatible executable.

## Run tests

Test files are located into `unittest/` directory. Run the test suites with :

	$ make check

# Code

For developers, you should respect the following rules before submitting your changes :

+ Don't push your code if it doesn't compile. 
+ Use 2 spaces for indentation (no tabs).
+ Test your code as much as possible.
+ Respect the project's coding style, inspired from [google c++ style guide](http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml)

# License

This software is under BSD license. View the LICENSE file for terms of use.

Copyright © 2012 Florian Mhun, Sara Ressam, Jérôme Cornet, Bastien Nouhant, from University of Poitiers (FR).
