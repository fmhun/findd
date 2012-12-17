#ifndef FINDD_SCANNERTEST_H_
#define FINDD_SCANNERTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace findd {
  
  class Scanner;

  class ScannerTest : public CppUnit::TestFixture {
  	CPPUNIT_TEST_SUITE( ScannerTest );
    CPPUNIT_TEST( testScanWithNotExistingDirectory );
    CPPUNIT_TEST( testScanWithEmptyDirectory );
    CPPUNIT_TEST( testScanNotEmptyDirectory );
    CPPUNIT_TEST( testReset );
    CPPUNIT_TEST( testScanRecusiveWithNotEmptyDirectory );
    CPPUNIT_TEST( testScanWithNotEmptyDirectoryIncludingHiddenFiles );
    CPPUNIT_TEST( testScanRecursiveWithNotEmptyDirectoryIncludingHiddenFiles );
    CPPUNIT_TEST( testScanManyDirectories );
    CPPUNIT_TEST( testScanRecursiveManyDirectories );
    CPPUNIT_TEST( testScanRecursiveManyDirectoriesButAlreadyScanned );
    CPPUNIT_TEST_SUITE_END();

  public:
  	void setUp ();
  	void tearDown ();

    void testScanWithNotExistingDirectory ();
    void testScanWithEmptyDirectory ();
    void testScanNotEmptyDirectory ();
    void testReset ();
    void testScanRecusiveWithNotEmptyDirectory ();
    void testScanWithNotEmptyDirectoryIncludingHiddenFiles ();
    void testScanRecursiveWithNotEmptyDirectoryIncludingHiddenFiles ();
    void testScanManyDirectories ();
    void testScanRecursiveManyDirectories ();
    void testScanRecursiveManyDirectoriesButAlreadyScanned ();
  private:
    Scanner *_scanner;
  };
  
}

#endif // FINDD_SCANNERTEST_H_