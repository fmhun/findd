#ifndef FINDD_FILTERTEST_H_
#define FINDD_FILTERTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class FilterTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( FilterTest );
  //CPPUNIT_TEST( testSomething );
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
  void testCompareDifferentFilesByTheirContent ();
  void testCompareDifferentFilesByTheirContent ();
  void testCompareDifferentFilesByTheirContent ();
  void testCompareDifferentFilesByTheirContent ();
  void testCompareDifferentFilesByTheirContent ();
  void testCompareIdenticalFiles ();
  
  
  // Test only filtering and not compare function. It doesn't make sense to test filtering for each combination of 
  // filter modes because it's tested by testCompare* tests.
	
  void testFileListFilteringWithNoDuplicate ();
	void testFileListFilteringWithDuplicates ();
  
};

#endif // FINDD_FILTERTEST_H_