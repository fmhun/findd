#ifndef FINDD_UITEST_H_
#define FINDD_UITEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class UiTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( UiTest );
  //CPPUNIT_TEST( testSomething );
  CPPUNIT_TEST_SUITE_END();

 public:
  void setUp ();
  void tearDown ();

  //void testSomething(void); 
};

#endif // FINDD_UITEST_H_