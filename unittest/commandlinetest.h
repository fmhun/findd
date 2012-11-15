#ifndef FINDD_COMMANDLINETEST_H
#define FINDD_COMMANDLINETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class CommandlineTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( CommandlineTest );
  CPPUNIT_TEST( testParseArgsWithValidFlags );
  CPPUNIT_TEST( testParseArgsWithInvalidFLags );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp ();
  void tearDown ();
  
  void testParseArgsWithValidFlags ();
  void testParseArgsWithInvalidFLags ();
};

#endif // FINDD_COMMANDLINETEST_H