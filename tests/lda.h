#include "../cpu.h"
#include "assert.h"

using namespace std;
using std::vector;

#define LDA_TESTS(acc, zero, neg)\
  ASSERT(cpu.get_acc(), acc, ACC_TEST);\
  ASSERT(cpu.get_zero(), zero, ZERO_TEST);\
  ASSERT(cpu.get_negative(), neg, NEG_TEST);

/* 0xA9 */
void test_0xa9_lda(int &tests_made, int &tests_passed) {
  cpu cpu;
  vector<uint8_t> program = {0xa9, 0x05, 0x00};

  cpu.load_and_run(program);
  LDA_TESTS(0x05, false, false);
}

void test_0xa9_lda_zero(int &tests_made, int &tests_passed) {
  cpu cpu;
  vector<uint8_t> program = {0xa9, 0x00, 0x00};

  cpu.load_and_run(program);
  LDA_TESTS(0x00, true, false);
}  

void test_0xa9_lda_negative(int &tests_made, int &tests_passed) {
  cpu cpu;
  vector<uint8_t> program = {0xa9, 0xFF, 0x00};

  cpu.load_and_run(program);
  LDA_TESTS(0XFF, false, true);
}
