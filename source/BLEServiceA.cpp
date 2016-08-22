/*
 * BLEServiceA.cpp
 *
 *  Created on: 26.06.2016
 *      Author: inter
 */

#include <BLEServiceA.h>

//template<typename T>
//BLEServiceA<T>::BLEServiceA(BLEDevice &_ble, T initialValue) :
//	ble(_ble),
//	state(CHARACTERISTIC_UUID,
//	&initialValue)
//{
//	GattCharacteristic *charTable[] = {&state};
//	GattService         gattService(
//			SERVICE_UUID,
//			charTable,
//			sizeof(charTable) / sizeof(GattCharacteristic *)
//			);
//
//	ble.addService(gattService);
//}

//template<typename T>
//GattAttribute::Handle_t BLEServiceA<T>::getValueHandle() const{
//	return state.getValueHandle();
//}
