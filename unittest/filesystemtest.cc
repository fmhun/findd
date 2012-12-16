#include <cppunit/extensions/HelperMacros.h>

#include "filesystemtest.h"

#include "filesystem.h"

using namespace findd;
using namespace findd::filesystem;

CPPUNIT_TEST_SUITE_REGISTRATION( FilesystemTest );

void FilesystemTest::setUp () {
  
}

void FilesystemTest::tearDown () {
	
}

void FilesystemTest::testExists () {
  CPPUNIT_ASSERT ( exists("unittest/fixtures/test_file.txt") == true );
  CPPUNIT_ASSERT ( exists("not_exist") == false );
}

void FilesystemTest::testTrimPath () {
  CPPUNIT_ASSERT ( trim_path("foo/bar/") == "foo/bar" );
  CPPUNIT_ASSERT ( trim_path("foo/bar") == "foo/bar" );
}