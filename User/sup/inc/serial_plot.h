#ifndef SERIAL_PLOT_H
#define SERIAL_PLOT_H

#include "app_cfg.h"
#include "arm_math.h"

#define PLOT_BUFFER_SIZE 1024

struct serial_plot_point_s {
  const char* label;
};

void serial_plot_write_point(struct serial_plot_point_s point, float32_t data);
void serial_plot_write_start(void);
void serial_plot_write_end(void);

#endif /* SERIAL_PLOT_H */