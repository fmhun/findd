#include <cppunit/extensions/HelperMacros.h>

#include "configtest.h"
#include "config.h"

CPPUNIT_TEST_SUITE_REGISTRATION( ConfigTest );

using findd::Config;

void ConfigTest::setUp () {
	_config = new Config ();
}

void ConfigTest::tearDown () {
  delete _config;
}

void ConfigTest::testRestoreDefaultValues () {
  bool old = _config->recursive;
	_config->recursive = !(_config->recursive);
  _config->restoreDefaultValues();
	
	CPPUNIT_ASSERT( old == _config->recursive ); 
}