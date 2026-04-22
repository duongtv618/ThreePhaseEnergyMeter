#include "share_data.h"
#include "ema.h"

#define EMA_ALPHA 0.2f

static struct meter_data_s meter_data[2];
static struct meter_data_s* r_ptr = &meter_data[0];
static struct meter_data_s* w_ptr = &meter_data[1];
static enum meter_state_e _state = METER_STATE_START;

static struct meter_data_s shdat_get_ema_data(struct meter_data_s* datPtr);


struct meter_data_s shdat_get_ema_data(struct meter_data_s* datPtr) {
  struct meter_data_s ema_data;
  ema_data.frequency = ema_get(datPtr->frequency, r_ptr->frequency, EMA_ALPHA);
  ema_data.energy_hWh = datPtr->energy_hWh;
  ema_data.energy_Ws = datPtr->energy_Ws;
  ema_data.vol_line.ab = ema_get(datPtr->vol_line.ab, r_ptr->vol_line.ab, EMA_ALPHA);
  ema_data.vol_line.bc = ema_get(datPtr->vol_line.bc, r_ptr->vol_line.bc, EMA_ALPHA);
  ema_data.vol_line.ca = ema_get(datPtr->vol_line.ca, r_ptr->vol_line.ca, EMA_ALPHA);

  for (int i = 0; i < METER_PHASE_COUNT; i++) {
    ema_data.phase_data[i].rms_voltage =
        ema_get(datPtr->phase_data[i].rms_voltage, r_ptr->phase_data[i].rms_voltage, EMA_ALPHA);
    ema_data.phase_data[i].rms_current =
        ema_get(datPtr->phase_data[i].rms_current, r_ptr->phase_data[i].rms_current, EMA_ALPHA);
    ema_data.phase_data[i].act_pwr =
        ema_get(datPtr->phase_data[i].act_pwr, r_ptr->phase_data[i].act_pwr, EMA_ALPHA);
    ema_data.phase_data[i].react_pwr =
        ema_get(datPtr->phase_data[i].react_pwr, r_ptr->phase_data[i].react_pwr, EMA_ALPHA);
    ema_data.phase_data[i].app_pwr =
        ema_get(datPtr->phase_data[i].app_pwr, r_ptr->phase_data[i].app_pwr, EMA_ALPHA);
    ema_data.phase_data[i].pf =
        ema_get(datPtr->phase_data[i].pf, r_ptr->phase_data[i].pf, EMA_ALPHA);
    ema_data.phase_data[i].thd.voltage =
        ema_get(datPtr->phase_data[i].thd.voltage, r_ptr->phase_data[i].thd.voltage, EMA_ALPHA);
    ema_data.phase_data[i].thd.current =
        ema_get(datPtr->phase_data[i].thd.current, r_ptr->phase_data[i].thd.current, EMA_ALPHA);
  }
  return ema_data;
}

/**
 * @brief Get meter data
 * 
 * @return struct meter_data_s 
 */
struct meter_data_s shdat_get_meter_data(void) { return (*r_ptr); }

void shdat_wrt_meter_data(struct meter_data_s* datPtr) {
  /** r_ptr contains the last data */
  struct meter_data_s after_ema = shdat_get_ema_data(datPtr);

  memcpy(w_ptr, &after_ema, sizeof(struct meter_data_s));

  /** Swap pointers */
  struct meter_data_s* tmp = w_ptr;
  w_ptr = r_ptr;
  r_ptr = tmp;
}

/**
 * @brief Return current meter state
 * 
 * @return meter_state_t 
 */
enum meter_state_e shdat_get_meter_current_state(void) {
    return  _state;
}

/**
 * @brief Set meter state
 * 
 * @param state State
 */
void shdat_set_meter_state(enum meter_state_e state){
  _state = state;
}

