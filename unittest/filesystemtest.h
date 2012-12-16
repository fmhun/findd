#ifndef FINDD_FILESYSTEMTEST_H_
#define FINDD_FILESYSTEMTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace findd {
  
  class FilesystemTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( FilesystemTest );
    CPPUNIT_TEST( testExists );
    CPPUNIT_TEST( testTrimPath );
    CPPUNIT_TEST_SUITE_END();

   public:
    void setUp ();
    void tearDown ();

    void testExists ();
    void testTrimPath ();
  };
  
}

#endif // FINDD_FILESYSTEMTEST_H_