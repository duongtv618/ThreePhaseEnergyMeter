#include "serial_plot.h"
#include "uart_dma.h"

#define START_STR ">"
#define END_STR "\r\n"
#define SPLIT_STR ","
#define MIDDLE_STR ":"

static char msg[64];
static char* itoa(int32_t value, char* str, int32_t base);
static char* ftoa(float32_t value, char* str, int digit);

static char* ftoa(float32_t value, char* str, int digit) {
  char* ptr = str;
  char* ptr1;
  int32_t int_part, remain;

  if (value == NAN) {
    *str = '\0';
    return str;
  }

  if (value == INFINITY) {
    strcpy(str, "Inf");
    return str;
  }

  int_part = (int32_t) value;

  ptr = itoa(int_part, str, 10);//Convert to string
  ptr1 = ptr;
  ptr += strlen(ptr);//ptr is in last position now
  *ptr++ = '.';

  value -= (float32_t)int_part;

  if (value < 0.0f) {
    value = -1.0f * value;
  }

  value *= (powf(10.0f, (float32_t)digit));
  remain = (int32_t)value;
  itoa(remain, ptr, 10);
  return ptr1;
}

/** Support funtcion interget to ascii */
static char* itoa(int32_t value, char* str, int32_t base) {
  char *ptr = str, *ptr1 = str, tmp_char;
  int tmp_value;

  if (base < 2 || base > 36) {
    *str = '\0';
    return str;
  }

  do {
    tmp_value = value;
    value /= base;
    *ptr++ =
        "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxy"
        "z"[35 + (tmp_value - value * base)];
  } while (value);

  if (tmp_value < 0) {
    *ptr++ = '-';
  }
  *ptr-- = '\0';

  while (ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = tmp_char;
  }
  return str;
}

void serial_plot_write_point(struct serial_plot_point_s point, float32_t data) {
    uart_dma_write_block((uint8_t*)START_STR, strlen(START_STR));
    uart_dma_write_block((uint8_t*)point.label, strlen(point.label));
    uart_dma_write_block((uint8_t*)MIDDLE_STR, strlen(MIDDLE_STR));
    uart_dma_write_block((uint8_t*)ftoa(data, msg, 3), strlen(msg));
    uart_dma_write_block((uint8_t*)END_STR, strlen(END_STR));
}
void serial_plot_write_start(void) {
    uart_dma_write_block((uint8_t*)START_STR, strlen(START_STR));
}
void serial_plot_write_end(void) {
    uart_dma_write_block((uint8_t*)END_STR, strlen(END_STR));
}