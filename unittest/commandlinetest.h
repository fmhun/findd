#ifndef FINDD_COMMANDLINETEST_H
#define FINDD_COMMANDLINETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class CommandlineTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( CommandlineTest );
  //CPPUNIT_TEST( testSomething );
  CPPUNIT_TEST_SUITE_END();

 public:
  void setUp ();
  void tearDown ();

  //void testSomething(void); 
};

#endif // FINDD_COMMANDLINETEST_H