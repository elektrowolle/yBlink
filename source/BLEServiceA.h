/*
 * BLEServiceA.h
 *
 *  Created on: 26.06.2016
 *      Author: inter
 */

#include "BLEServiceI.h"
#include "mbed-drivers/mbed.h"
#include "ble/BLE.h"

#ifndef YBLINK_SOURCE_BLESERVICEA_H_
#define YBLINK_SOURCE_BLESERVICEA_H_

template <typename T>
class BLEServiceA : public BLEServiceI{
public:
//    static const uint16_t SERVICE_UUID        = 0xA000;
//    static const uint16_t CHARACTERISTIC_UUID = 0xA001;

    BLEServiceA(BLEDevice &_ble, T initialValue);
//    :
//    ble(_ble),
//	state(CHARACTERISTIC_UUID,
//	&initialValue)
//	{
//		GattCharacteristic *charTable[] = {&state};
//		GattService         gattService(
//				SERVICE_UUID,
//				charTable,
//				sizeof(charTable) / sizeof(GattCharacteristic *)
//				);
//
//		ble.addService(gattService);
//	}

    GattAttribute::Handle_t getValueHandle() const;
//    {
//        return state.getValueHandle();
//    }

private:
BLEDevice                       &ble;
ReadWriteGattCharacteristic<T>  state;
};

template<typename T>
BLEServiceA<T>::BLEServiceA(BLEDevice &_ble, T initialValue) :
	ble(_ble),
	state(CHARACTERISTIC_UUID,
	&initialValue)
{
	GattCharacteristic *charTable[] = {&state};
	GattService         gattService(
			SERVICE_UUID,
			charTable,
			sizeof(charTable) / sizeof(GattCharacteristic *)
			);

	ble.addService(gattService);
}

template<typename T>
GattAttribute::Handle_t BLEServiceA<T>::getValueHandle() const{
	return state.getValueHandle();
}

#endif /* YBLINK_SOURCE_BLESERVICEA_H_ */
