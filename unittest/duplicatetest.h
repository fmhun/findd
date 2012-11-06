#ifndef FINDD_DUPLICATETEST_H
#define FINDD_DUPLICATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class DuplicateTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( DuplicateTest );
  //CPPUNIT_TEST( testSomething );
  CPPUNIT_TEST_SUITE_END();

 public:
  void setUp ();
  void tearDown ();

  //void testSomething(void); 
};

#endif // FINDD_DUPLICATETEST_H