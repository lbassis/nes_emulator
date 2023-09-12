using namespace std;

#define ACC_TEST "Accumulator value"
#define REGX_TEST "Register X value"
#define ZERO_TEST "Zero flag"
#define NEG_TEST "Negative flag"

#ifdef VERBOSE				

#define ASSERT(x, y, desc)			\
  cout << __FUNCTION__ << ": " << desc;		\
  if (x == y) {					\
      cout << " test passed\n";			\
      tests_passed++;				\
  }						\
  else {					\
      cout << " test failed\n";			\
      }						\
  tests_made++;

#else
#define ASSERT(x, y, desc)			\
  if (x == y) {					\
      tests_passed++;				\
  }						\
  tests_made++;
#endif
