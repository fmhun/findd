#include <cppunit/extensions/HelperMacros.h>

#include "filelist.h"
#include "filelisttest.h"

using findd::FileList;
using findd::InvalidBackupException;

CPPUNIT_TEST_SUITE_REGISTRATION( FileListTest );

void FileListTest::setUp () {
	_filelist = new FileList();
}

void FileListTest::tearDown () {
	delete _filelist;
}

void FileListTest::testCreateFileListFromValidBackup () {
  CPPUNIT_ASSERT_NO_THROW( FileList::createFromBackup("backup") );
}

void FileListTest::testCreateFileListFromInvalidBackup () {
  CPPUNIT_ASSERT_THROW( FileList::createFromBackup("invalid_backup"), InvalidBackupException );
}

void FileListTest::testSaveWithValidPath () {
  File a(), b();
  _filelist.add(a);
  _filelist.add(b);
  
  _filelist.save("backup_");
  // A file backup_ should exist.
}

void FileListTest::testSaveWithInvalidPath () {
  File a(), b();
  _filelist.add(a);
  _filelist.add(b);
  
  CPPUNIT_ASSERT_THROW(_filelist.save("directory"), FileListException);
}