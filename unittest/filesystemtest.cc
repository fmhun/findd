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

void FilesystemTest::testDirConcat () {
  CPPUNIT_ASSERT ( dir_concat("foo", "bar" ) == "foo/bar" );
  CPPUNIT_ASSERT ( dir_concat("/foo", "bar" ) == "/foo/bar" );
}

void FilesystemTest::testFileName () {
  CPPUNIT_ASSERT ( filename("foo/bar.ext" ) == "bar.ext" );
  CPPUNIT_ASSERT ( filename("bar.ext" ) == "bar.ext" );
}

void FilesystemTest::testExtension () {
  CPPUNIT_ASSERT ( extension("foo/bar.ext" ) == "ext" );
  CPPUNIT_ASSERT ( extension("bar.ext" ) == "ext" );
}

void FilesystemTest::testIsHidden () {
  CPPUNIT_ASSERT ( is_hidden("foo/bar/.file" ) == true );
  CPPUNIT_ASSERT ( is_hidden(".file" ) == true );
}

void FilesystemTest::testRealPath () {
#ifdef _WIN32
  CPPUNIT_ASSERT ( real_path("unittest\\fixtures\\test_file.txt" ).at(1) == ':' );
#endif
  CPPUNIT_ASSERT ( real_path("./unittest/fixtures/test_file.txt" ).at(0) == '/' );
}




