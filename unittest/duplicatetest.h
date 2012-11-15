#ifndef FINDD_DUPLICATETEST_H
#define FINDD_DUPLICATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class DuplicateTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( DuplicateTest );
  CPPUNIT_TEST( testGetMinGainOfBytes );
  CPPUNIT_TEST( testGetMaxGainOfBytes );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp ();
  void tearDown (); 
  
  void testGetMinGainOfBytes ();
  void testGetMaxGainOfBytes ();
};

#endif // FINDD_DUPLICATETEST_H