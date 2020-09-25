/**
  *
  * @file    hr_driver.h
  * @author  ProfHindsight
  * @version x
  * @date    8/5/2020
  * @brief   The HR driver will spit out whether it detects a peak pulse and last detected heart rate 
  */

#include <stdint.h>

typedef struct cur_heart_rate
{
    bool peak;
    uint8_t hr;
} cur_heart_rate_t;

cur_heart_rate_t get_hr_periodic(void);