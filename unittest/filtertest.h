#ifndef FINDD_FILTERTEST_H_
#define FINDD_FILTERTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class FilterTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( FilterTest );
  //CPPUNIT_TEST( testSomething );
  CPPUNIT_TEST_SUITE_END();

 public:
  void setUp ();
  void tearDown ();

  //void testSomething(void); 
};

#endif // FINDD_FILTERTEST_H_