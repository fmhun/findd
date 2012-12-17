#include <cppunit/extensions/HelperMacros.h>

#include "enginetest.h"

#include "engine.h"
#include "comparator.h"
#include "scanner.h"
#include "filesystem.h"

using namespace findd;
using filesystem::real_path;

CPPUNIT_TEST_SUITE_REGISTRATION( EngineTest );

void EngineTest::setUp () {
  _engine = new Engine();
  _comparator = new Comparator();
  _scanner = new Scanner();
}

void EngineTest::tearDown () {
  delete _engine;
  delete _comparator;
  delete _scanner;
}

void EngineTest::testSearchOnEmptyFileList () {
  file_list fl = _scanner->files();
  _engine->search(fl, *_comparator);
  CPPUNIT_ASSERT( _engine->duplicates().size() == 0 );
}

void EngineTest::testSearchOnNotEmptyFileListWithNameComparator () {
  _scanner->scan("unittest/fixtures/test_not_empty_dir/test_files_with_same_name", true, true);
  file_list fl = _scanner->files();
  _comparator->enable(NAME);
  
  _engine->search(fl, *_comparator);
  
  const duplicate_list &dups = _engine->duplicates();
  CPPUNIT_ASSERT( _engine->duplicates().size() == 1 ); // number of duplicates
  CPPUNIT_ASSERT( dups[0].size() == 2); // number of duplicate files
  CPPUNIT_ASSERT( dups[0][0].path() == real_path("unittest/fixtures/test_not_empty_dir/test_files_with_same_name/test_sub_dir/file_a.txt") );
  CPPUNIT_ASSERT( dups[0][1].path() == real_path("unittest/fixtures/test_not_empty_dir/test_files_with_same_name/file_a.txt") );
}