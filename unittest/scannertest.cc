#include <cppunit/extensions/HelperMacros.h>

#include "scannertest.h"

#include <stdexcept>

#include "scanner.h"

using namespace findd;

CPPUNIT_TEST_SUITE_REGISTRATION( ScannerTest );

void ScannerTest::setUp () {
  _scanner = new Scanner();
}

void ScannerTest::tearDown () {
  delete _scanner;
}

void ScannerTest::testScanWithNotExistingDirectory () {
  CPPUNIT_ASSERT_THROW( _scanner->scan("directory_not_exist"), std::logic_error );
}
  
void ScannerTest::testScanWithEmptyDirectory () {
  _scanner->scan("unittest/fixtures/test_empty_dir");
  CPPUNIT_ASSERT( _scanner->files().size() == 0 );
  CPPUNIT_ASSERT( _scanner->scanned_directories().size() == 1 );
}

void ScannerTest::testScanNotEmptyDirectory () {
  _scanner->scan("unittest/fixtures/test_not_empty_dir/test_scan");
  CPPUNIT_ASSERT( _scanner->files().size() == 4 );
  CPPUNIT_ASSERT( _scanner->scanned_directories().size() == 1 );
}

void ScannerTest::testReset () {
  _scanner->scan("unittest/fixtures/test_not_empty_dir/test_scan");
  _scanner->reset();
  CPPUNIT_ASSERT( _scanner->files().size() == 0 );
  CPPUNIT_ASSERT( _scanner->scanned_directories().size() == 0 );
}

void ScannerTest::testScanRecusiveWithNotEmptyDirectory () {
  _scanner->scan("unittest/fixtures/test_not_empty_dir/test_scan", false, true);
  CPPUNIT_ASSERT( _scanner->files().size() == 8 );
  CPPUNIT_ASSERT( _scanner->scanned_directories().size() == 2 );
}

void ScannerTest::testScanWithNotEmptyDirectoryIncludingHiddenFiles () {
  _scanner->scan("unittest/fixtures/test_not_empty_dir/test_scan", true, false);
  CPPUNIT_ASSERT( _scanner->files().size() == 5 );
  CPPUNIT_ASSERT( _scanner->scanned_directories().size() == 1 );
}

void ScannerTest::testScanRecursiveWithNotEmptyDirectoryIncludingHiddenFiles () {
  _scanner->scan("unittest/fixtures/test_not_empty_dir/test_scan", true, true);
  CPPUNIT_ASSERT( _scanner->files().size() == 10 );
  CPPUNIT_ASSERT( _scanner->scanned_directories().size() == 3 );
}

void ScannerTest::testScanManyDirectories () {
  _scanner->scan("unittest/fixtures/test_not_empty_dir/test_scan");
  _scanner->scan("unittest/fixtures/test_not_empty_dir/test_scan/test_sub_dir");
  
  // it should perform scan to the last directory (was not scanned by the first scan)
  CPPUNIT_ASSERT( _scanner->files().size() == 8 );
  CPPUNIT_ASSERT( _scanner->scanned_directories().size() == 2 );
}

void ScannerTest::testScanRecursiveManyDirectories () {
  _scanner->scan("unittest/fixtures/test_not_empty_dir/test_scan", false, true);
  _scanner->scan("unittest/fixtures/test_not_empty_dir/test_scan_bis", false, true);
  
  CPPUNIT_ASSERT( _scanner->files().size() == 16 );
  CPPUNIT_ASSERT( _scanner->scanned_directories().size() == 4 );
}

void ScannerTest::testScanRecursiveManyDirectoriesButAlreadyScanned () {
  _scanner->scan("unittest/fixtures/test_not_empty_dir/test_scan", false, true);
  _scanner->scan("unittest/fixtures/test_not_empty_dir/test_scan/test_sub_dir", false, true);
  
  // it should not perform new scan to the last directory (already scanned)
  CPPUNIT_ASSERT( _scanner->files().size() == 8 );
  CPPUNIT_ASSERT( _scanner->scanned_directories().size() == 2 );
}