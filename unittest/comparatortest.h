#ifndef FINDD_COMPARATORTEST_H_
#define FINDD_COMPARATORTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace findd {
  
  class Comparator;
  class File;

  class ComparatorTest : public CppUnit::TestFixture {
  	CPPUNIT_TEST_SUITE( ComparatorTest );
    CPPUNIT_TEST( testIsEnable );
    CPPUNIT_TEST( testComparaisionByName );
    CPPUNIT_TEST( testComparaisionBySize );
    CPPUNIT_TEST( testComparaisionByContent );
    CPPUNIT_TEST( testComparaisionByNameAndSize );
    CPPUNIT_TEST( testComparaisionByNameAndContent );
    CPPUNIT_TEST( testComparaisionBySizeAndContent );
    CPPUNIT_TEST( testComparaisionByNameAndSizeAndContent );
    CPPUNIT_TEST_SUITE_END();

  public:
  	void setUp ();
  	void tearDown ();

    void testIsEnable ();
    void testComparaisionByName ();
    void testComparaisionBySize ();
    void testComparaisionByContent ();
    void testComparaisionByNameAndSize ();
    void testComparaisionByNameAndContent ();
    void testComparaisionBySizeAndContent ();
    void testComparaisionByNameAndSizeAndContent ();
  
  private:
    Comparator *_comparator;
    File *_first;
    File *_second;
  };
  
}

#endif // FINDD_SCANNERTEST_H_