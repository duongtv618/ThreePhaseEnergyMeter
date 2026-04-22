#ifndef SHARE_DATA_H
#define SHARE_DATA_H

#include "share_types.h"

enum meter_state_e shdat_get_meter_current_state(void);
void shdat_set_meter_state(enum meter_state_e state);

struct meter_data_s shdat_get_meter_data(void);
void shdat_wrt_meter_data(struct meter_data_s* datPtr);

#endif