#include "adc_glove.h"


const uint8_t dacBits[12] = {41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30};
const int aReadPinP = A8, aReadPinN = A9;
const uint32_t buffer_size = 10;
DMAMEM static volatile uint16_t __attribute__((aligned(32))) dma_adc_buff1[buffer_size];
DMAMEM static volatile uint16_t __attribute__((aligned(32))) dma_adc_buff2[buffer_size];
AnalogBufferDMA abdma1(dma_adc_buff1, buffer_size, dma_adc_buff2, buffer_size);

#ifdef ADC_DUAL_ADCS
DMAMEM static volatile uint16_t __attribute__((aligned(32))) dma_adc2_buff1[buffer_size];
DMAMEM static volatile uint16_t __attribute__((aligned(32))) dma_adc2_buff2[buffer_size];
AnalogBufferDMA abdma2(dma_adc2_buff1, buffer_size, dma_adc2_buff2, buffer_size);
#endif

void adc_set(ADC *adc) {
  
  pinMode(aReadPinP, INPUT); pinMode(aReadPinN, INPUT);
  adc->adc0->setAveraging(10); // set number of averages
  adc->adc0->setResolution(12); // set bits of resolution
  abdma1.init(adc, ADC_0); 
#ifdef ADC_DUAL_ADCS
  adc->adc1->setAveraging(10); // set number of averages
  adc->adc1->setResolution(12); // set bits of resolution
  abdma2.init(adc, ADC_1); 
  adc->adc1->startContinuous(aReadPinN);
#endif
  adc->adc0->startContinuous(aReadPinP);
}

void ProcessAnalogData(AnalogBufferDMA *pabdma, int8_t adc_num) {
  uint32_t sum_values = 0;
  uint16_t min_val = 0xffff;
  uint16_t max_val = 0;

  uint32_t average_value = pabdma->userData();

  volatile uint16_t *pbuffer = pabdma->bufferLastISRFilled();
  volatile uint16_t *end_pbuffer = pbuffer + pabdma->bufferCountLastISRFilled();
  
  if ((uint32_t)pbuffer >= 0x20200000u)  arm_dcache_delete((void*)pbuffer, sizeof(dma_adc_buff1));
  while (pbuffer < end_pbuffer) {
    if (*pbuffer < min_val) min_val = *pbuffer;
    if (*pbuffer > max_val) max_val = *pbuffer;
    sum_values += *pbuffer;
    pbuffer++;
  }  
  average_value = sum_values / buffer_size;
  //Serial.printf(" %d - %u(%u): %u <= %u <= %u ", adc_num, pabdma->interruptCount(), pabdma->interruptDeltaTime(), min_val,
  //              average_value, max_val);
                
  pabdma->clearInterrupt();
  pabdma->userData(average_value);
}

void processADC(){
      // Maybe only when both have triggered?
  #ifdef ADC_DUAL_ADCS
      if ( abdma1.interrupted() && abdma2.interrupted()) {
          if (abdma1.interrupted()) ProcessAnalogData(&abdma1, 0);
          if (abdma2.interrupted()) ProcessAnalogData(&abdma2, 1);
          //Serial.println();
      }
  #else
      if ( abdma1.interrupted()) {
          ProcessAnalogData(&abdma1, 0);
          //Serial.println();
      }
  #endif
}