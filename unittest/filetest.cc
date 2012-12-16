#include <cppunit/extensions/HelperMacros.h>

#include "file.h"
#include "filetest.h"

using namespace findd;

CPPUNIT_TEST_SUITE_REGISTRATION( FileTest );

void FileTest::setUp () {
  _file = new File("unittest/fixtures/test_file.txt", 10);
}

void FileTest::tearDown () {
	delete _file;
}

void FileTest::testComputeChecksum () {
  _file->compute_checksum();
  CPPUNIT_ASSERT (_file->content_digest() == "0944483cd90a293923c8244520132de1");
}