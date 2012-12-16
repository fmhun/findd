#ifndef FINDD_FILETEST_H_
#define FINDD_FILETEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace findd {
  
  class File;
  
  class FileTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( FileTest );
    CPPUNIT_TEST( testComputeChecksum );
    CPPUNIT_TEST_SUITE_END();

   public:
    void setUp ();
    void tearDown ();

    void testComputeChecksum ();
    
    File *_file;
  };
  
}

#endif // FINDD_FILETEST_H_