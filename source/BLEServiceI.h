/*
 * BLEServiceI.h
 *
 *  Created on: 26.06.2016
 *      Author: inter
 */
#include "mbed-drivers/mbed.h"
#include "ble/BLE.h"
#ifndef YBLINK_SOURCE_BLESERVICEI_H_
#define YBLINK_SOURCE_BLESERVICEI_H_

class BLEServiceI {
public:
	static const uint16_t SERVICE_UUID        = 0xA000;
	static const uint16_t CHARACTERISTIC_UUID = 0xA001;
	BLEServiceI();
	virtual ~BLEServiceI();
	virtual void onWriteCallback(const GattWriteCallbackParams *params) = 0;
};

#endif /* YBLINK_SOURCE_BLESERVICEI_H_ */
