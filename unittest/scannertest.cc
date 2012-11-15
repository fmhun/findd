#include <cppunit/extensions/HelperMacros.h>

#include "scanner.h"
#include "scannertest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( ScannerTest );

using findd::Scanner;

void ScannerTest::setUp () {
  _scanner = new Scanner();
}

void ScannerTest::tearDown () {
  delete _scanner;
}

void ScannerTest::testScanWithDirectoryThatNotExists () {
  CPPUNIT_ASSERT_THROW( _scanner->scan("directory_not_exist"), DirectoryNotFoundException );
}

void ScannerTest::testScanManyTimeTheSameDirectoryWhichExists () {
  _scanner->scan("directory_exist");
  CPPUNIT_ASSERT( _scanner->scanned_directories().front() == "directory_exist" );
}

// dir
//  |_ f1
//  |_ f2
void ScannerTest::testScanWithDirectoryWhichContainsOnlyFiles () {
  _scanner->scan("dir");
  CPPUNIT_ASSERT( scanner->file_list().size() == 2 );
}

// dir
//  |_ f1
//  |_ dir
//      |_ f1
void ScannerTest::testScanWithDirectoryThatContainsAnOtherDirectory () {
  _scanner->scan("dir");
  CPPUNIT_ASSERT( scanner->file_list().size() == 1 );
}

// dir
//  |_ f1
//  |_ dir
//      |_ f1
void ScannerTest::testRecursiveScanWithDirectoryThatContainsAnOtherDirectory () {
  _scanner->scan("dir");
  CPPUNIT_ASSERT( scanner->file_list().size() == 2 );
}