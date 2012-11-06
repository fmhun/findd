#ifndef FINDD_APPTEST_H
#define FINDD_APPTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class AppTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( AppTest );
  //CPPUNIT_TEST( testSomething );
  CPPUNIT_TEST_SUITE_END();

 public:
  void setUp ();
  void tearDown ();

  //void testSomething(void); 
};

#endif // FINDD_APPTEST_H