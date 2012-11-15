#ifndef FINDD_FILTERTEST_H_
#define FINDD_FILTERTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class FilterTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( FilterTest );
  CPPUNIT_TEST( testCompareFilesByTheirContent );
  CPPUNIT_TEST( testCompareFilesByTheirSize );
  CPPUNIT_TEST( testCompareFilesByTheirName );
  CPPUNIT_TEST( testCompareFilesByTheirContentAndSize );
  CPPUNIT_TEST( testCompareFilesByTheirContentAndName );
  CPPUNIT_TEST( testCompareFilesByTheirSizeAndName );
  CPPUNIT_TEST( testCompareFilesByTheirContentSizeName );
  CPPUNIT_TEST( testFileListFilteringWithNoDuplicate );
	CPPUNIT_TEST( testFileListFilteringWithDuplicates );
  CPPUNIT_TEST_SUITE_END();

 public:
	void setUp ();
	void tearDown ();
    
  /**
   * Filter mode to compare files :
   *  - C : content
   *  - S : size
   *  - N : name
   */
  void testCompareFilesByTheirContent ();
  void testCompareFilesByTheirSize ();
  void testCompareFilesByTheirName ();
  void testCompareFilesByTheirContentAndSize ();
  void testCompareFilesByTheirContentAndName ();
  void testCompareFilesByTheirSizeAndName ();
  void testCompareFilesByTheirContentSizeName ();
  
  // Test only filtering and not compare function. It doesn't make sense to test filtering for each combination of 
  // filter modes because it's tested by testCompare* tests.
	
  void testFileListFilteringWithNoDuplicate ();
	void testFileListFilteringWithDuplicates ();
  
};

#endif // FINDD_FILTERTEST_H_