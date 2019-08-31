//#include <math.h>
#include "ACS712.h"

#define ADC_SCALE       (1024)

ACS712::ACS712(
  const ACS712_type _type,
  const uint8_t _pin,
  const uint32_t _vref) :
sensitivity(0.066f),
zero(ADC_SCALE/2),
vref(_vref),
pin(_pin)
{
  switch (_type) {
    case ACS712_05B:
      sensitivity = 0.185f;
      break;
    case ACS712_20A:
      sensitivity = 0.100f;
      break;
    case ACS712_30A:
    default:
      break;
  }
}

int32_t ACS712::calibrate(void) {
  zero = 0;
  for (int i = 0; i < 32; i++) {
    zero += analogRead(pin);
    delay(10);
  }
  zero >>= 5;
  return zero;
}

void ACS712::setZeroPoint(const int32_t _zero) {
  zero = _zero;
}

float ACS712::getCurrentDC(void) {
  const float I = (((float)(analogRead(pin) - zero)) / ADC_SCALE) * vref / sensitivity;
  return I;
}

float ACS712::getCurrentAC(const uint16_t frequency) {
  uint32_t period = 1000000 / frequency;
  uint32_t t_start = micros();

  uint32_t Isum = 0, measurements_count = 0;
  int32_t Inow;

  while (micros() < period+t_start) {
    Inow  = analogRead(pin) - zero;
    Isum += Inow*Inow;
    measurements_count++;
  }

  const float Irms = (sqrt(Isum / measurements_count) / ADC_SCALE) * vref / sensitivity;
  return Irms;
}
