#ifndef FINDD_SCANNERTEST_H_
#define FINDD_SCANNERTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class Scanner;

class ScannerTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE( ScannerTest );
  CPPUNIT_TEST( testScanWithDirectoryThatNotExists );
  CPPUNIT_TEST( testScanManyTimeTheSameDirectoryWhichExists );
	CPPUNIT_TEST( testScanWithDirectoryWhichContainsOnlyFiles );
  CPPUNIT_TEST( testScanWithDirectoryThatContainsAnOtherDirectory );
  CPPUNIT_TEST( testRecursiveScanWithDirectoryThatContainsAnOtherDirectory );
  CPPUNIT_TEST_SUITE_END();

public:
	void setUp ();
	void tearDown ();

  void testScanWithDirectoryThatNotExists ();
  void testScanWithManyDirectoryOneNotExists ();
  
  void testScanWithDirectoryWhichContainsOnlyFiles ();
private:
  Scanner *_scanner;
};

#endif // FINDD_SCANNERTEST_H_