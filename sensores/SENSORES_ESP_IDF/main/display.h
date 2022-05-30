#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>

void display_init();
void display_test(void);

void display_write_string(const char *str, uint8_t x, uint8_t y);
void display_write_float(float num, uint8_t x, uint8_t y);
void display_load_bitmap(uint8_t *bitmap);


#endif