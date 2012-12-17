#ifndef FINDD_COMPARATORTEST_H_
#define FINDD_COMPARATORTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace findd {
  
  class Comparator;

  class ComparatorTest : public CppUnit::TestFixture {
  	CPPUNIT_TEST_SUITE( ComparatorTest );
    // CPPUNIT_TEST( testScanWithNotExistingDirectory );
    CPPUNIT_TEST_SUITE_END();

  public:
  	void setUp ();
  	void tearDown ();

    // void testScanWithNotExistingDirectory ();
  private:
    Comparator *_comparator;
  };
  
}

#endif // FINDD_SCANNERTEST_H_