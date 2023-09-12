#include "../cpu.h"

using namespace std;
using std::vector;

void test_first_ops(int &tests_made, int &tests_passed) {
  cpu cpu;
  vector<uint8_t> program = {0xa9, 0xc0, 0xaa, 0xe8, 0x00};

  cpu.load_and_run(program);
  
  if (cpu.get_reg_x() == 0xc1) { tests_passed++; }
  tests_made++;
}
