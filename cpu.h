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
  uint8_t accumulator;
  uint8_t reg_x;
  uint8_t status;
  uint16_t pc;
  uint8_t memory[0xFFFF];

  inline void zero_pc() { this->pc = 0; }
  void set_zero_flag(bool flag) { flag ? this->status |= STATUS_ZERO : this->status &= STATUS_N_ZERO; }
  void set_negative_flag(bool flag) { flag ? this->status |= STATUS_NEGATIVE : this->status &= STATUS_N_NEGATIVE; }


  void update_zero_and_negative(uint8_t val) {
    (val == 0) ? set_zero_flag(true) : set_zero_flag(false);
    (val & STATUS_NEGATIVE) ? set_negative_flag(true) : set_negative_flag(false);
  }

  uint8_t mem_read(uint16_t address) { return memory[address]; }
  void mem_write(uint16_t address, uint8_t data) { memory[address] = data; }
  
  
public:
  cpu() : accumulator(0), status(0), pc(PC_INITIAL_VALUE) {}
  void print_status() { cout << bitset<8>(this->status) << endl; }
  inline uint8_t get_acc() { return this->accumulator; }
  inline uint8_t get_reg_x() { return this->reg_x; }

  inline uint8_t get_status() { return this->status; }
  inline bool get_zero() { return (this->get_status() & STATUS_ZERO); }
  inline bool get_negative() { return (this->get_status() & STATUS_NEGATIVE); }

  void set_acc(uint8_t val) { this->accumulator = val; }
  void set_reg_x(uint8_t val) { this->reg_x = val; }

  void reset() {
    accumulator = 0;
    reg_x = 0;
    status = 0;
    pc = mem_read_u16(PC_INITIAL_VALUE_ADDRESS);
  }
    
  void run() {
    
    while (true) {
      auto opcode = mem_read(pc);
      pc++;

      switch (opcode) {
      case 0x00:
	return;

      case 0xA9: { /* LDA */
	auto param = mem_read(pc);
	pc++;

	accumulator = param;

	update_zero_and_negative(accumulator);
	break;
      }

      case 0xAA: { /* TAX */	
	reg_x = accumulator;

	update_zero_and_negative(reg_x);
	break;
      }

      case 0xE8: { /* INX */
	reg_x++;

	update_zero_and_negative(reg_x);
	break;
      }
      }
    }
  }

  void load(vector<uint8_t> program) {
    uint16_t program_offset = PC_INITIAL_VALUE;
    mem_write_u16(PC_INITIAL_VALUE_ADDRESS, PC_INITIAL_VALUE);

    for (int i = 0; i < program.size(); i++) {
      memory[program_offset + i] = program[i];
    }
  }

  inline void load_and_run(vector<uint8_t> program) {
    load(program);
    reset();
    run();
  }

  uint16_t mem_read_u16(uint16_t address) {
    uint8_t low = mem_read(address);
    uint8_t high = mem_read(address+1);

    return high << 8 | (uint16_t) low;
  }

  void mem_write_u16(uint16_t address, uint16_t data) {
    uint8_t low = data & 0xff;
    uint8_t high = (data >> 8) & 0xff;

    mem_write(address, low);
    mem_write(address+1, high);
  }
};
