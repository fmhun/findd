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

void EngineTest::testSearchWithNameComparator () {
  _scanner->scan("unittest/fixtures/test_not_empty_dir/test_files_with_same_name", false, true);
  file_list fl = _scanner->files();
  _comparator->enable(NAME);
  
  _engine->search(fl, *_comparator);
  
  const duplicate_list &dups = _engine->duplicates();
  // std::cout << std::endl << _engine->duplicates().size() << std::endl;
  CPPUNIT_ASSERT( _engine->duplicates().size() == 1 ); // number of duplicates
  CPPUNIT_ASSERT( dups[0].size() == 2); // number of duplicate files
  CPPUNIT_ASSERT( dups[0][0].path() == real_path("unittest/fixtures/test_not_empty_dir/test_files_with_same_name/test_sub_dir/file_a.txt") );
  CPPUNIT_ASSERT( dups[0][1].path() == real_path("unittest/fixtures/test_not_empty_dir/test_files_with_same_name/file_a.txt") );
}

void EngineTest::testSearchWithSizeComparator () {
  _scanner->scan("unittest/fixtures/test_not_empty_dir/test_files_with_same_size", false, true);
  file_list fl = _scanner->files();
  _comparator->enable(SIZE);
  
  _engine->search(fl, *_comparator);
  
  const duplicate_list &dups = _engine->duplicates();
  CPPUNIT_ASSERT( _engine->duplicates().size() == 1 ); // number of duplicates
  CPPUNIT_ASSERT( dups[0].size() == 2); // number of duplicate files
  CPPUNIT_ASSERT( dups[0][0].path() == real_path("unittest/fixtures/test_not_empty_dir/test_files_with_same_size/test_sub_dir/file_c.txt") );
  CPPUNIT_ASSERT( dups[0][1].path() == real_path("unittest/fixtures/test_not_empty_dir/test_files_with_same_size/file_a.txt") );  
}

void EngineTest::testSearchWithContentComparator () {
  _scanner->scan("unittest/fixtures/test_not_empty_dir/test_files_with_same_content", false, true);
  file_list fl = _scanner->files();
  _comparator->enable(CONTENT);
  
  _engine->search(fl, *_comparator);
  
  const duplicate_list &dups = _engine->duplicates();
  CPPUNIT_ASSERT( _engine->duplicates().size() == 1 ); // number of duplicates
  CPPUNIT_ASSERT( dups[0].size() == 2); // number of duplicate files
  CPPUNIT_ASSERT( dups[0][0].path() == real_path("unittest/fixtures/test_not_empty_dir/test_files_with_same_content/test_sub_dir/file_c.txt") );
  CPPUNIT_ASSERT( dups[0][1].path() == real_path("unittest/fixtures/test_not_empty_dir/test_files_with_same_content/file_a.txt") );    
}

void EngineTest::testSearchWithNameAndSizeComparator () {
  _scanner->scan("unittest/fixtures/test_not_empty_dir/test_files_with_same_name_and_size", false, true);
  file_list fl = _scanner->files();
  _comparator->enable(NAME);
  _comparator->enable(SIZE);
  
  _engine->search(fl, *_comparator);
  
  const duplicate_list &dups = _engine->duplicates();
  CPPUNIT_ASSERT( _engine->duplicates().size() == 1 ); // number of duplicates
  CPPUNIT_ASSERT( dups[0].size() == 2); // number of duplicate files
  CPPUNIT_ASSERT( dups[0][0].path() == real_path("unittest/fixtures/test_not_empty_dir/test_files_with_same_name_and_size/test_sub_dir/file_a.txt") );
  CPPUNIT_ASSERT( dups[0][1].path() == real_path("unittest/fixtures/test_not_empty_dir/test_files_with_same_name_and_size/file_a.txt") );    
}

void EngineTest::testSearchWithNameAndContentComparator () {
  _scanner->scan("unittest/fixtures/test_not_empty_dir/test_files_with_same_name_and_content", false, true);
  file_list fl = _scanner->files();
  _comparator->enable(NAME);
  _comparator->enable(CONTENT);
  
  _engine->search(fl, *_comparator);
  
  const duplicate_list &dups = _engine->duplicates();
  CPPUNIT_ASSERT( _engine->duplicates().size() == 1 ); // number of duplicates
  CPPUNIT_ASSERT( dups[0].size() == 2); // number of duplicate files
  CPPUNIT_ASSERT( dups[0][0].path() == real_path("unittest/fixtures/test_not_empty_dir/test_files_with_same_name_and_content/test_sub_dir/file_a.txt") );
  CPPUNIT_ASSERT( dups[0][1].path() == real_path("unittest/fixtures/test_not_empty_dir/test_files_with_same_name_and_content/file_a.txt") );  
}

void EngineTest::testSearchWithSizeAndContentComparator () {
  _scanner->scan("unittest/fixtures/test_not_empty_dir/test_files_with_same_size_and_content", false, true);
  file_list fl = _scanner->files();
  _comparator->enable(SIZE);
  _comparator->enable(CONTENT);
  
  _engine->search(fl, *_comparator);
  
  const duplicate_list &dups = _engine->duplicates();
  CPPUNIT_ASSERT( _engine->duplicates().size() == 1 ); // number of duplicates
  CPPUNIT_ASSERT( dups[0].size() == 2); // number of duplicate files
  CPPUNIT_ASSERT( dups[0][0].path() == real_path("unittest/fixtures/test_not_empty_dir/test_files_with_same_size_and_content/test_sub_dir/file_c.txt") );
  CPPUNIT_ASSERT( dups[0][1].path() == real_path("unittest/fixtures/test_not_empty_dir/test_files_with_same_size_and_content/file_a.txt") );    
}

void EngineTest::testSearchWithNameAndSizeAndContentComparator () {
  _scanner->scan("unittest/fixtures/test_not_empty_dir/test_files_with_same_name_and_size_and_content", false, true);
  file_list fl = _scanner->files();
  _comparator->enable(NAME);
  _comparator->enable(SIZE);
  _comparator->enable(CONTENT);
  
  _engine->search(fl, *_comparator);
  
  const duplicate_list &dups = _engine->duplicates();
  CPPUNIT_ASSERT( _engine->duplicates().size() == 1 ); // number of duplicates
  CPPUNIT_ASSERT( dups[0].size() == 2); // number of duplicate files
  CPPUNIT_ASSERT( dups[0][0].path() == real_path("unittest/fixtures/test_not_empty_dir/test_files_with_same_name_and_size_and_content/test_sub_dir/file_a.txt") );
  CPPUNIT_ASSERT( dups[0][1].path() == real_path("unittest/fixtures/test_not_empty_dir/test_files_with_same_name_and_size_and_content/file_a.txt") );    
}