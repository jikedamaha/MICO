#ifndef __ACQUISITION_H
#define __ACQUISITION_H

#define ADC_VREF (3.3)
#define ADC_FULLSCALE(n) ((1 << n) - 1)

extern mico_queue_t acq_queue;

struct acq_message{
  uint16_t adc_value[3];
  uint8_t on_off;
};

float get_adc2volt(uint16_t adc_value);


#endif
