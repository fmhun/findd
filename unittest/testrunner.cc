#include "uitest.h"
#include "commandlinetest.h"
#include "configtest.h"

// scanning
#include "file.h"
#include "filelist.h"
#include "scanner.h"

// filtering
#include "duplicate.h"
#include "filter.h"

#include "apptest.h"

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

int main(void) {
	CppUnit::TextUi::TestRunner runner;
	
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
	runner.addTest( registry.makeTest() );
	  
	bool wasSuccessful = runner.run("", false);
	
	return wasSuccessful;
}