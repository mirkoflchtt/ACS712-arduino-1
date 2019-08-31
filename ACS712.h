#ifndef ACS712_h
#define ACS712_h
#include <stdint.h>
#include <Arduino.h>

#define VREF                (5000)
#define DEFAULT_FREQUENCY   (50)

typedef enum {
  ACS712_05B      = 0x0,
  ACS712_20A,
  ACS712_30A,
} ACS712_type;

class ACS712 {
public:
  ACS712(
    const ACS712_type _type,
    const uint8_t _pin,
    const uint32_t _vref=VREF);

  int32_t   calibrate(void);
  void      setZeroPoint(const int32_t _zero);
  float     getCurrentDC(void);
  float     getCurrentAC(const uint16_t frequency=DEFAULT_FREQUENCY);

private:
  float     sensitivity;
  int32_t   zero;
  uint32_t  vref;   // in millivolt
  uint8_t   pin;
};

#endif      /*ACS712_h*/
