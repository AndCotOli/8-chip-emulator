#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "chip_8_struct.h"

/*
** Chip instructions.
** - Multiple 'n' substitute for an address
** - Multiple 'k' substitute for a value
** - 'x' and 'y' substitute for an address (in V)
*/
void clear_display(Chip8 *chip);              // 00E0
void return_from_subroutine(Chip8 *chip);     // 00EE
void jump_to(Chip8 *chip);                    // 1nnn
void call_subroutine(Chip8 *chip);            // 2nnn
void skip_if_Vx_equals_next(Chip8 *chip);     // 3xkk
void skip_if_Vx_not_equals_next(Chip8 *chip); // 4xkk
void skip_if_Vx_equal_Vy(Chip8 *chip);        // 5xy0
void set_Vx_to(Chip8 *chip);                  // 6xkk
void add_to_Vx(Chip8 *chip);                  // 7xkk
void set_Vx_to_Vy(Chip8 *chip);               // 8xy0
void set_Vx_to_Vy_OR(Chip8 *chip);            // 8xy1
void set_Vx_to_Vy_AND(Chip8 *chip);           // 8xy2
void set_Vx_to_Vy_XOR(Chip8 *chip);           // 8xy3
void add_Vy_to_Vx(Chip8 *chip);               // 8xy4
void substract_Vy_to_Vx(Chip8 *chip);         // 8xy5
void perform_right_shift(Chip8 *chip);        // 8xy6
void substract_Vx_from_Vy(Chip8 *chip);       // 8xy7
void perform_left_shift(Chip8 *chip);         // 8xyE
void skip_if_not_equal(Chip8 *chip);          // 9xy0
void set_I_to(Chip8 *chip);                   // Annn
void jump_to_with_offset(Chip8 *chip);        // Bnnn
void set_Vx_random(Chip8 *chip);              // Cxkk
void display_sprite(Chip8 *chip);             // Dxyn
void skip_if_pressed(Chip8 *chip);            // Ex9E
void skip_if_not_pressed(Chip8 *chip);        // ExA1
void set_Vx_to_delay(Chip8 *chip);            // Fx07
void wait_for_keypress(Chip8 *chip);          // Fx0A
void set_delay_to_Vx(Chip8 *chip);            // Fx15
void set_sound_to_Vx(Chip8 *chip);            // Fx18
void add_Vx_to_I(Chip8 *chip);                // Fx1E
void set_I_to_sprite(Chip8 *chip);            // Fx29
void store_BCD_representation(Chip8 *chip);   // Fx33
void store_registers_in_I(Chip8 *chip);       // Fx55
void read_registers_from_I(Chip8 *chip);      // Fx65

#endif // INSTRUCTIONS_H_
