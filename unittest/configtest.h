#ifndef FINDD_CONFIGTEST_H
#define FINDD_CONFIGTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ConfigTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( ConfigTest );
  //CPPUNIT_TEST( testSomething );
  CPPUNIT_TEST_SUITE_END();

 public:
  void setUp ();
  void tearDown ();

  //void testSomething(void); 
};

#endif // FINDD_CONFIGTEST_H