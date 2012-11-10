#ifndef FINDD_SCANNERTEST_H_
#define FINDD_SCANNERTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ScannerTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE( ScannerTest );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp ();
	void tearDown ();

  void testScanWithDirectoryThatNotExists ();
  void testScanWithManyDirectoryOneNotExists ();
  
  void testRecursiveScanWithOneDirectory ();
  void testRecursiveScanWithManyDirectoriesNotChildOfAnOther ();    // /home and /usr
  void testRecursiveScanWithManyDirectoriesOneIsAChildOfAnOther (); // /home and /home/foo
};

#endif // FINDD_SCANNERTEST_H_