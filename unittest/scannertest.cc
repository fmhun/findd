#include <cppunit/extensions/HelperMacros.h>

#include "scanner.h"
#include "scannertest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( ScannerTest );

void ScannerTest::setUp () {
	
}

void ScannerTest::tearDown () {
	
}

void ScannerTest::testScan () {
	Scanner scanner;
	
	scanner.scan("./unittest");
}