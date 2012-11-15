#ifndef FINDD_FILELISTTEST_H_
#define FINDD_FILELISTTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class FileListTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( FileListTest );
  CPPUNIT_TEST( testCreateFileListFromValidBackup );
  CPPUNIT_TEST( testCreateFileListFromInvalidBackup );
  CPPUNIT_TEST( testSaveWithValidPath );
  CPPUNIT_TEST( testSaveWithInvalidPath );
  CPPUNIT_TEST_SUITE_END();

public:
	void setUp ();
	void tearDown ();

	void testCreateFileListFromValidBackup ();
	void testCreateFileListFromInvalidBackup ();
  
  void testSaveWithValidPath ();
  void testSaveWithInvalidPath ();

private:
  FileList *_filelist;
};

#endif // FINDD_FILELISTTEST_H_