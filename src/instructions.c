#include "instructions.h"
#include <stdint.h>

#define NNN (chip->current_op & 0x0FFF)
#define X ((chip->current_op & 0x0F00) >> 8)
#define Y ((chip->current_op & 0x00F0) >> 4)
#define KK (chip->current_op & 0x00FF)
#define N (chip->current_op & 0x000F)

/*
** OP: 00E0
** Description: clear the display
*/
void clear_display(Chip8 *chip) {
  for (int i = 0; i < DISPLAY_HEIGHT; i++)
    for (int j = 0; j < DISPLAY_WIDTH; j++)
      chip->display[i][j] = 0;

  chip->draw_flag = TRUE;
  chip->pc_register += 2;
}

/*
** OP: 00EE
** Description: set the program counter to address at top of stack and decrement
*stack pointer.
*/
void return_from_subroutine(Chip8 *chip) {
  chip->pc_register = chip->stack[--chip->stack_pointer_register] + 2;
}

/*
** OP: 1nnn
** Description: set program counter to nnn
*/
void jump_to(Chip8 *chip) { chip->pc_register = NNN; }

void call_subroutine(Chip8 *chip) { printf("TODO: implement.\n"); }

void skip_if_Vx_equals_next(Chip8 *chip) {
  printf("TODO: implement.\n");
}; // 3xkk
void skip_if_Vx_not_equals_next(Chip8 *chip) {
  printf("TODO: implement.\n");
};                                                                       // 4xkk
void skip_if_Vx_equal_Vy(Chip8 *chip) { printf("TODO: implement.\n"); }; // 5xy0

/*
** OP: 6xkk
** Description: put the value kk into register x
*/
void set_Vx_to(Chip8 *chip) {
  chip->V_registers[X] = KK;
  chip->pc_register += 2;
}

/*
** OP: 7xkk
** Description: add the value kk to the register x
*/
void add_to_Vx(Chip8 *chip) {
  chip->V_registers[X] += KK;
  chip->pc_register += 2;
}

void set_Vx_to_Vy(Chip8 *chip) { printf("TODO: implement.\n"); };        // 8xy0
void set_Vx_to_Vy_OR(Chip8 *chip) { printf("TODO: implement.\n"); };     // 8xy1
void set_Vx_to_Vy_AND(Chip8 *chip) { printf("TODO: implement.\n"); };    // 8xy2
void set_Vx_to_Vy_XOR(Chip8 *chip) { printf("TODO: implement.\n"); };    // 8xy3
void add_Vy_to_Vx(Chip8 *chip) { printf("TODO: implement.\n"); };        // 8xy4
void substract_Vy_to_Vx(Chip8 *chip) { printf("TODO: implement.\n"); };  // 8xy5
void perform_right_shift(Chip8 *chip) { printf("TODO: implement.\n"); }; // 8xy6
void substract_Vx_from_Vy(Chip8 *chip) {
  printf("TODO: implement.\n");
};                                                                      // 8xy7
void perform_left_shift(Chip8 *chip) { printf("TODO: implement.\n"); }; // 8xyE
void skip_if_not_equal(Chip8 *chip) { printf("TODO: implement.\n"); };  // 9xy0

/*
** OP: Annn
** Description: set the value of the I register to nnn
*/
void set_I_to(Chip8 *chip) {
  chip->I_register = NNN;
  chip->pc_register += 2;
}

void jump_to_with_offset(Chip8 *chip) { printf("TODO: implement.\n"); }; // Bnnn
void set_Vx_random(Chip8 *chip) { printf("TODO: implement.\n"); };       // Cxkk

/*
** OP: Dxyn
** Description: Display n-byte sprite starting at memory localtion I at (Vx, Vy)
*/
void display_sprite(Chip8 *chip) {
  uint8_t Vx = chip->V_registers[X];
  uint8_t Vy = chip->V_registers[Y];

  uint8_t sprite;

  chip->V_registers[0xF] = FALSE;
  for (int y = 0; y < N; y++) {
    sprite = chip->ram[chip->I_register + y];
    for (int x = 0; x < 8; x++) {
      if ((sprite & (0x80 >> x)) != 0) {
        if (chip->display[Vy + y][Vx + x] == 1)
          chip->V_registers[0xF] = TRUE;

        chip->display[Vy + y][Vx + x] ^= 1;
      }
    }
  }

  chip->draw_flag = TRUE;
  chip->pc_register += 2;
}

void skip_if_pressed(Chip8 *chip) { printf("TODO: implement.\n"); };     // Ex9E
void skip_if_not_pressed(Chip8 *chip) { printf("TODO: implement.\n"); }; // ExA1
void set_Vx_to_delay(Chip8 *chip) { printf("TODO: implement.\n"); };     // Fx07
void wait_for_keypress(Chip8 *chip) { printf("TODO: implement.\n"); };   // Fx0A
void set_delay_to_Vx(Chip8 *chip) { printf("TODO: implement.\n"); };     // Fx15
void set_sound_to_Vx(Chip8 *chip) { printf("TODO: implement.\n"); };     // Fx18
void add_Vx_to_I(Chip8 *chip) { printf("TODO: implement.\n"); };         // Fx1E
void set_I_to_sprite(Chip8 *chip) { printf("TODO: implement.\n"); };     // Fx29
void store_BCD_representation(Chip8 *chip) {
  printf("TODO: implement.\n");
}; // Fx33
void store_registers_in_I(Chip8 *chip) {
  printf("TODO: implement.\n");
}; // Fx55
void read_registers_from_I(Chip8 *chip) {
  printf("TODO: implement.\n");
}; // Fx65
