#ifndef CHIP_8_STRUCT_H_
#define CHIP_8_STRUCT_H_

#define NUM_KEYS 16
#define NUM_REGISTERS 16
#define FONTSET_SIZE 80
#define STACK_CAPACITY 16
#define RAM_CAPACITY 4 * 1024
#define MAX_TIMER 255

/* ADDRESSES */
#define PC_START 0x200
#define CHIP_8_START_RAM_ADDR 0X000
#define CHIP_8_END_RAM_ADDR 0X1FF
#define PROGRAM_START_ADDR 0X200
#define PROGRAM_END_ADDR 0XFFF

#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32

#define TRUE 1
#define FALSE 0

const static uint8_t FONTSET[FONTSET_SIZE] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

typedef struct Chip8_t Chip8;

struct Chip8_t {
  uint8_t ram[RAM_CAPACITY];
  uint8_t stack[STACK_CAPACITY];

  uint8_t V_registers[NUM_REGISTERS];
  uint8_t I_register;
  uint16_t pc_register;
  uint16_t stack_pointer_register;

  uint8_t delay_timer;
  uint8_t sound_timer;

  uint16_t current_op;

  uint8_t display[DISPLAY_HEIGHT][DISPLAY_WIDTH];

  uint8_t keyboard[NUM_KEYS];
  uint8_t key_pressed;

  uint8_t is_running_flag;
  uint8_t is_paused_flag;
  uint8_t draw_flag;
};

#endif // CHIP_8_STRUCT_H_
