using namespace std;

#define RESET_TEXT "\x1B[0m"
#define RED_TEXT "\x1B[31m"
#define GREEN_TEXT "\x1B[32m"

#define ACC_TEST "Accumulator value"
#define REGX_TEST "Register X value"
#define ZERO_TEST "Zero flag"
#define NEG_TEST "Negative flag"

#ifdef VERBOSE				

#define ASSERT(x, y, desc)					\
  cout << __FUNCTION__ << ": " << desc;				\
  if (x == y) {							\
    cout << GREEN_TEXT << " test passed" << RESET_TEXT << endl;	\
    tests_passed++;						\
  }								\
  else {							\
    cout << RED_TEXT << " test failed" << RESET_TEXT << endl;	\
  }								\
  tests_made++;

#else
#define ASSERT(x, y, desc)			\
  if (x == y) {					\
    tests_passed++;				\
  }						\
  tests_made++;
#endif
