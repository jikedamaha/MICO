#include "MICO.h"
#include "MICODefine.h"
#include "MICOAppDefine.h"

#include "acquisition.h"

#define acquisition_log(M, ...) custom_log("ACQ", M, ##__VA_ARGS__)
#define acquisition_log_trace() custom_log_trace("ACQ")

mico_queue_t acq_queue;
acq_data_t acq_message;

void acquisition_thread(void *inFd)
{
  OSStatus err;

  #if 0
  uint16_t adc_value = 0;
  int i = 0;
  uint16_t max_val = 0;
  uint16_t min_val = 0;
  #endif

  err = MicoAdcInitialize(MICO_ADC_1, 50);
  if(!err)
  {
    acquisition_log("MicoAdcInitialize err = %d", err);
  }

  err = Mico

  sleep(10);

  while(1)
  {
    #if 0
    max_val = 0;
    min_val = 0;

    for(i = 0; i < 500; i++)
    {
        err = MicoAdcTakeSample(MICO_ADC_1, (uint16_t *)&adc_value);
        if( adc_value > max_val )
        {
           max_val = adc_value;
        }

        if( adc_value < min_val )
        {
           min_val = adc_value;
        }

        msleep(2);
    }


    acq_message.adc_value[0] = (max_val - min_val)/0.707;
    #endif

    err = MicoAdcTakeSample(MICO_ADC_1, (uint16_t *)&acq_message.adc_value[0]);
    acquisition_log("MicoAdcTakeSample: %d, err = %d", acq_message.adc_value[0], err);
    if(!err)
    {
      err = mico_rtos_push_to_queue(&acq_queue, (void *)&acq_message, 0);
      acquisition_log("adc_value pushed");
    }

    sleep(6);
  }
}

float get_adc2volt(uint16_t adc_value)
{
  float volt = 0;

  volt = ADC_VREF * adc_value / ADC_FULLSCALE(12);

  return volt;
}
