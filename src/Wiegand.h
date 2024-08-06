#ifndef _WIEGAND_H
#define _WIEGAND_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

enum WIEGAND_RESULT {
    WIEGAND_RESULT_EMPTY = 0,
    WIEGAND_RESULT_SUCCESS,
    WIEGAND_RESULT_ERROR,
};

class WIEGAND {

public:
	WIEGAND();
	void begin();
	void begin(int pinD0, int pinD1, uint8_t inputMode = INPUT, bool inverted = false);
	void begin(int pinD0, int pinIntD0, int pinD1, int pinIntD1);
	bool available();
	unsigned long getCode();
	int getWiegandType();
	
private:
	static void ReadD0();
	static void ReadD1();
	static WIEGAND_RESULT DoWiegandConversion ();
	static unsigned long GetCardId (volatile unsigned long *codehigh, volatile unsigned long *codelow, char bitlength);
	
	static volatile unsigned long 	_cardTempHigh;
	static volatile unsigned long 	_cardTemp;
	static volatile unsigned long 	_lastWiegand;
	static volatile int				_bitCount;	
	static int				_wiegandType;
	static unsigned long	_code;
};

#endif
