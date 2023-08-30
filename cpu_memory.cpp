#include "cpu.h"

uint8_t cpu::mem_read(uint16_t address) { return memory[address]; }
void cpu::mem_write(uint16_t address, uint8_t data) { memory[address] = data; }

uint16_t cpu::mem_read_u16(uint16_t address) {
  uint8_t low = mem_read(address);
  uint8_t high = mem_read(address+1);

  return high << 8 | (uint16_t) low;
}

void cpu::mem_write_u16(uint16_t address, uint16_t data) {
  uint8_t low = data & 0xff;
  uint8_t high = (data >> 8) & 0xff;

  mem_write(address, low);
  mem_write(address+1, high);
}
