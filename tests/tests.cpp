#include "../cpu.h"

#include "general.h"
#include "memory.h"
#include "lda.h"
#include "tax.h"
#include "inx.h"

using namespace std;

int main() {

  int tests_made = 0;
  int tests_passed = 0;

  cout << "Instruction tests:" << endl;
  test_0xa9_lda(tests_made, tests_passed);
  test_0xa9_lda_zero(tests_made, tests_passed);
  test_0xa9_lda_negative(tests_made, tests_passed);

  test_0xaa_n_zero(tests_made, tests_passed);
  
  test_inx_overflow(tests_made, tests_passed);
  
  test_first_ops(tests_made, tests_passed);
  
  cout << "Passed " << tests_passed << "/" << tests_made << endl;

  tests_made = tests_passed = 0;

  cout << "Memory tests:" << endl;
  read_8000(tests_made, tests_passed);
  write_and_read(tests_made, tests_passed);
  cout << "Passed " << tests_passed << "/" << tests_made << endl;
}
