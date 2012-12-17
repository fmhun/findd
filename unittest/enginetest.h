#ifndef FINDD_ENGINETEST_H_
#define FINDD_ENGINETEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace findd {
  class Engine;
  class Comparator;
  class Scanner;
  
  class EngineTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( EngineTest );
    CPPUNIT_TEST( testSearchOnEmptyFileList );
    CPPUNIT_TEST( testSearchWithNameComparator );
    CPPUNIT_TEST( testSearchWithSizeComparator );
    CPPUNIT_TEST( testSearchWithContentComparator );
    CPPUNIT_TEST( testSearchWithNameAndSizeComparator );
    CPPUNIT_TEST( testSearchWithNameAndContentComparator );
    CPPUNIT_TEST( testSearchWithSizeAndContentComparator );
    CPPUNIT_TEST( testSearchWithNameAndSizeAndContentComparator );
    CPPUNIT_TEST_SUITE_END();
    
   public:
    void setUp ();
    void tearDown ();
    
    void testSearchOnEmptyFileList ();
    void testSearchWithNameComparator ();
    void testSearchWithSizeComparator ();
    void testSearchWithContentComparator ();
    void testSearchWithNameAndSizeComparator ();
    void testSearchWithNameAndContentComparator ();
    void testSearchWithSizeAndContentComparator ();
    void testSearchWithNameAndSizeAndContentComparator ();
  private:
    Engine *_engine;
    Comparator *_comparator;
    Scanner *_scanner;
  };
  
}

#endif // FINDD_ENGINETEST_H_