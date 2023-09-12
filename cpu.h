#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <vector>
#include <bitset>

#define STATUS_ZERO 1<<1 // 0b00000010
#define STATUS_N_ZERO 255-(1<<1) //0b11111101

#define STATUS_NEGATIVE 1<<7
#define STATUS_N_NEGATIVE 255-(1<<7)

#define PC_INITIAL_VALUE_ADDRESS 0xFFFC
#define PC_INITIAL_VALUE 0x8000

using namespace std;
using std::vector;

class cpu {
private:

  enum AddressingMode {
    Immediate,
    ZeroPage,
    ZeroPage_X,
    ZeroPage_Y,
    Absolute,
    Absolute_X,
    Absolute_Y,
    Indirect_X,
    Indirect_Y,
    None
  };

  uint8_t accumulator;
  uint8_t reg_x, reg_y;
  uint8_t status;
  uint16_t pc;
  uint8_t memory[0xFFFF];

  /* cpu general */
  uint16_t get_operand_address(AddressingMode mode);

  /* cpu_registers.cpp */
  void set_zero_flag(bool flag);
  void set_negative_flag(bool flag);
  void update_zero_and_negative(uint8_t val);

  /* cpu_memory.cpp */
  uint8_t mem_read(uint16_t address);
  void mem_write(uint16_t address, uint8_t data);

public:

  cpu() : accumulator(0), status(0), pc(PC_INITIAL_VALUE) {}

  /* cpu_general.cpp */
  void reset();
  void load(vector<uint8_t> program);
  void run();
  void load_and_run(vector<uint8_t> program);
  void lda(AddressingMode mode);

  /* cpu_registers.cpp */
  uint8_t get_acc();
  uint8_t get_reg_x();
  uint8_t get_reg_y();

  uint8_t get_status();
  bool get_zero();
  bool get_negative();

  void set_acc(uint8_t val);
  void set_reg_x(uint8_t val);

  void print_status();

  /* cpu_memory.cpp */
  uint16_t mem_read_u16(uint16_t address);
  void mem_write_u16(uint16_t address, uint16_t data);

};

#endif
