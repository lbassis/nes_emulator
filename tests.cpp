#include "cpu.hpp"

using namespace std;
using std::vector;

/* 0xA9 */
void test_0xa9_lda(int &tests_made, int &tests_passed) {
  cpu cpu;
  vector<uint8_t> program = {0xa9, 0x05, 0x00};

  cpu.load_and_run(program);
  
  if (cpu.get_acc() == 0x05) { tests_passed++; }
  tests_made++;

  if (cpu.get_zero() == false) { tests_passed++; }
  tests_made++;

  if (cpu.get_negative() == false) { tests_passed++; } 
  tests_made++;
}

void test_0xa9_lda_zero(int &tests_made, int &tests_passed) {
  cpu cpu;
  vector<uint8_t> program = {0xa9, 0x00, 0x00};

  cpu.load_and_run(program);
  
  if (cpu.get_acc() == 0x00) { tests_passed++; }
  tests_made++;

  if (cpu.get_zero() == true) { tests_passed++; }
  tests_made++;

  if (cpu.get_negative() == false) { tests_passed++; } 
  tests_made++;
}  

void test_0xa9_lda_negative(int &tests_made, int &tests_passed) {
  cpu cpu;
  vector<uint8_t> program = {0xa9, 0xFF, 0x00};

  cpu.load_and_run(program);
  
  if (cpu.get_acc() == 0xFF) { tests_passed++; }
  tests_made++;

  if (cpu.get_zero() == false) { tests_passed++; }
  tests_made++;

  if (cpu.get_negative() == true) { tests_passed++; } 
  tests_made++;
}

/* 0xAA */
void test_0xaa_n_zero(int &tests_made, int &tests_passed) {
  cpu cpu;
  vector<uint8_t> program = {0xa9, 0x05, 0xaa, 0x00};

  cpu.load_and_run(program);
  
  if (cpu.get_reg_x() == 0x05) { tests_passed++; }
  tests_made++;

  if (cpu.get_zero() == false) { tests_passed++; }
  tests_made++;

  if (cpu.get_negative() == false) { tests_passed++; } 
  tests_made++;
}

/* 0xE8 */
void test_inx_overflow(int &tests_made, int &tests_passed) {
  cpu cpu;
  vector<uint8_t> program = {0xa9, 0xff, 0xaa, 0xe8, 0xe8, 0x00};

  cpu.load_and_run(program);
  
  if (cpu.get_reg_x() == 0x1) { tests_passed++; }
  tests_made++;
}

/* general */
void test_first_ops(int &tests_made, int &tests_passed) {
  cpu cpu;
  vector<uint8_t> program = {0xa9, 0xc0, 0xaa, 0xe8, 0x00};

  cpu.load_and_run(program);
  
  if (cpu.get_reg_x() == 0xc1) { tests_passed++; }
  tests_made++;
}

/* memory */
void read_8000(int &tests_made, int &tests_passed) {
  cpu cpu;
  vector<uint8_t> program = {0xa9, 0xc0};

  cpu.load(program);

  if (cpu.mem_read_u16(0x8000) == 0xc0a9) { tests_passed++; }
  tests_made++;
}

void write_and_read(int &tests_made, int &tests_passed) {
  cpu cpu;

  cpu.mem_write_u16(0x8000, 0xc0a9);

  if (cpu.mem_read_u16(0x8000) == 0xc0a9) { tests_passed++; }
  tests_made++;
}


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
