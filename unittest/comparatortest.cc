#include <cppunit/extensions/HelperMacros.h>

#include "comparatortest.h"

#include "comparator.h"
#include "filesystem.h"
#include "file.h"

using namespace findd;
using filesystem::real_path;

CPPUNIT_TEST_SUITE_REGISTRATION( ComparatorTest );

void ComparatorTest::setUp () {
  _comparator = new Comparator();
}

void ComparatorTest::tearDown () {
  delete _comparator;
}

void ComparatorTest::testIsEnable () {
  CPPUNIT_ASSERT( _comparator->is_enabled(NAME) == false );
  CPPUNIT_ASSERT( _comparator->is_enabled(SIZE) == false );
  CPPUNIT_ASSERT( _comparator->is_enabled(CONTENT) == false );
  
  _comparator->enable(NAME);
  CPPUNIT_ASSERT( _comparator->is_enabled(NAME) == true );
  CPPUNIT_ASSERT( _comparator->is_enabled(SIZE) == false );
  CPPUNIT_ASSERT( _comparator->is_enabled(CONTENT) == false );
  
  _comparator->enable(SIZE);
  CPPUNIT_ASSERT( _comparator->is_enabled(NAME) == true );
  CPPUNIT_ASSERT( _comparator->is_enabled(SIZE) == true );
  CPPUNIT_ASSERT( _comparator->is_enabled(CONTENT) == false );
  
  _comparator->enable(CONTENT);
  CPPUNIT_ASSERT( _comparator->is_enabled(NAME) == true );
  CPPUNIT_ASSERT( _comparator->is_enabled(SIZE) == true );
  CPPUNIT_ASSERT( _comparator->is_enabled(CONTENT) == true );
}

void ComparatorTest::testComparaisionByName () {
  _comparator->enable(NAME);
  File f1("/foo/bar", 0), f2("/foo/bar", 1), f3("/bar/foo", 1);
  
  CPPUNIT_ASSERT( (*_comparator)(f1, f2) == true );
  CPPUNIT_ASSERT( (*_comparator)(f1, f3) == false );
}


void ComparatorTest::testComparaisionBySize () {
  _comparator->enable(SIZE);
  File f1("/foo/bar", 1), f2("/bar/foo", 1), f3("/bar/foo", 0);

  CPPUNIT_ASSERT( (*_comparator)(f1, f2) == true );
  CPPUNIT_ASSERT( (*_comparator)(f1, f3) == false );
}

void ComparatorTest::testComparaisionByContent () {
  _comparator->enable(CONTENT);
  File f1(real_path("unittest/fixtures/test_not_empty_dir/test_files_with_same_content/test_sub_dir/file_c.txt"), 1);
  File f2(real_path("unittest/fixtures/test_not_empty_dir/test_files_with_same_content/file_a.txt"), 1);
  File f3(real_path("unittest/fixtures/test_not_empty_dir/test_files_with_same_content/file_b.txt"), 2);

  CPPUNIT_ASSERT( (*_comparator)(f1, f2) == true );
  CPPUNIT_ASSERT( (*_comparator)(f1, f3) == false );
}

void ComparatorTest::testComparaisionByNameAndSize () {
  _comparator->enable(NAME);
  _comparator->enable(SIZE);
  File f1("/foo/bar", 1), f2("/foo/bar", 1), f3("/foo/bar", 0), f4("/bar/foo", 1);

  CPPUNIT_ASSERT( (*_comparator)(f1, f2) == true );
  CPPUNIT_ASSERT( (*_comparator)(f1, f3) == false );
  CPPUNIT_ASSERT( (*_comparator)(f1, f4) == false );
}

void ComparatorTest::testComparaisionByNameAndContent () {
  _comparator->enable(NAME);
  _comparator->enable(CONTENT);
  File f1(real_path("unittest/fixtures/test_not_empty_dir/test_files_with_same_content/file_a.txt"), 1);
  File f2(real_path("unittest/fixtures/test_not_empty_dir/test_files_with_same_name/file_a.txt"), 1);
  File f3(real_path("unittest/fixtures/test_not_empty_dir/test_files_with_same_content/file_b.txt"), 2);
  

  CPPUNIT_ASSERT( (*_comparator)(f1, f2) == true );
  CPPUNIT_ASSERT( (*_comparator)(f1, f3) == false );
  CPPUNIT_ASSERT( (*_comparator)(f1, f4) == false );
}

void ComparatorTest::testComparaisionBySizeAndContent () {
  
}

void ComparatorTest::testComparaisionByNameAndSizeAndContent () {
  
}
