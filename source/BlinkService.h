#include "BLEServiceA.h"
#ifndef __BLINK_SERVICE_H__
#define __BLINK_SERVICE_H__

class BlinkService : public BLEServiceA<bool>{
public:
	const static uint16_t SERVICE_UUID        = 0xA003;
	const static uint16_t CHARACTERISTIC_UUID = 0xA001;

	BlinkService(BLEDevice &_ble, bool initialValue)
	: BLEServiceA<bool>(_ble, initialValue){
		alivenessLED = new DigitalOut(LED3, 0);
	}

	void onWriteCallback(const GattWriteCallbackParams *params){
//		alivenessLED = !alivenessLED;
		alivenessLED->write(*(params->data));
	}
private:
	DigitalOut * alivenessLED;
};

#endif //__BLINK_SERVICE_H__
