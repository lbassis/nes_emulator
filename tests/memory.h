#include "../cpu.h"

using namespace std;
using std::vector;

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
