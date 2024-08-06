#ifndef _WIEGAND_H
#define _WIEGAND_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#if defined(ESP8266)
    #define INTERRUPT_ATTR ICACHE_RAM_ATTR
#elif defined(ESP32)
	#define INTERRUPT_ATTR IRAM_ATTR
#else
    #define INTERRUPT_ATTR
#endif

#define WIEGAND_BIT_MAX_WAIT_TIME 50000ul // Bit timeout in micro seconds

class WIEGAND;

#define MAKE_WIEGAND_INSTANCE(VAR_NAME) \
void wiegandPinD0_##VAR_NAME(void); \
void wiegandPinD1_##VAR_NAME(void); \
WIEGAND VAR_NAME(wiegandPinD0_##VAR_NAME, wiegandPinD1_##VAR_NAME); \
INTERRUPT_ATTR void wiegandPinD0_##VAR_NAME(void) \
{\
    VAR_NAME.ReadD0();\
};\
INTERRUPT_ATTR void wiegandPinD1_##VAR_NAME(void)\
{\
    VAR_NAME.ReadD1();\
};

enum WIEGAND_RESULT {
    WIEGAND_RESULT_EMPTY = 0,
    WIEGAND_RESULT_SUCCESS,
    WIEGAND_RESULT_ERROR,
};

class WIEGAND {

public:
	WIEGAND(void (*ISR_D0)(void),void (*ISR_D1)(void));
	~WIEGAND();

	void begin(int pinD0, int pinD1, uint8_t inputMode = INPUT, bool inverted = false);
	bool available();
	unsigned long getCode();
	int getWiegandType();

	void ReadD0();
	void ReadD1();
	
private:
    void (*ISR_D0)(void);
    void (*ISR_D1)(void);

	WIEGAND_RESULT DoWiegandConversion ();
	unsigned long GetCardId (volatile unsigned long *codehigh, volatile unsigned long *codelow, char bitlength);
	
	volatile unsigned long 	_cardTempHigh = 0;
	volatile unsigned long 	_cardTemp = 0;
	volatile unsigned long 	_lastWiegand = 0;
	volatile int				_bitCount = 0;	
	int				_wiegandType = 0;
	unsigned long	_code = 0;
};

#endif
