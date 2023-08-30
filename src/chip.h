#ifndef CHIP_H_
#define CHIP_H_

#include "instructions.h"

void init(Chip8 *chip);
void load_roam(Chip8 *chip, const char *path);
uint16_t get_opcode(Chip8 *chip);
void execute_instruction(Chip8 *chip);
void handle_user_input(Chip8 *chip);
void update_timers(Chip8 *chip);

#endif // CHIP_H_
