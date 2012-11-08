#ifndef FINDD_SCANNERTEST_H_
#define FINDD_SCANNERTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ScannerTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE( ScannerTest );
	CPPUNIT_TEST( testScan );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp ();
	void tearDown ();

	void testScan ();

	// void testScanWithDirectoryThatNotExisting ();
	// void testScanWithManyDirectory ();
	// void testRecursiveScan ();
	// 
	// // Test this kind of directories : /home /home/florian
	// // It should only scan /home
	// void testManyRecursiveScanWithManyDirectory ();
};

#endif // FINDD_SCANNERTEST_H_