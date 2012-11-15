#ifndef FINDD_CONFIGTEST_H
#define FINDD_CONFIGTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "config.h"

using findd::Config;

class ConfigTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( ConfigTest );
  CPPUNIT_TEST( testRestoreDefaultValues );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp ();
  void tearDown ();

  void testRestoreDefaultValues ();

protected: 
  Config *_config;
};

#endif // FINDD_CONFIGTEST_H