#ifndef FINDD_FILETEST_H_
#define FINDD_FILETEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class FileTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( FileTest );
  //CPPUNIT_TEST( testSomething );
  CPPUNIT_TEST_SUITE_END();

 public:
  void setUp ();
  void tearDown ();

  //void testSomething(void); 
};

#endif // FINDD_FILETEST_H_