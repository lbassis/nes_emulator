#include "../cpu.h"

#include "assert.h"

using namespace std;
using std::vector;

#define TAX_TESTS(regx, zero, neg)\
  ASSERT(cpu.get_reg_x(), regx, REGX_TEST);\
  ASSERT(cpu.get_zero(), zero, ZERO_TEST);\
  ASSERT(cpu.get_negative(), neg, NEG_TEST);

/* 0xAA */
void test_0xaa_n_zero(int &tests_made, int &tests_passed) {
  cpu cpu;
  vector<uint8_t> program = {0xa9, 0x05, 0xaa, 0x00};

  cpu.load_and_run(program);
  TAX_TESTS(0x05, false, false);
}
