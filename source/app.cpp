#include "mbed-drivers/mbed.h"
#include "ble/BLE.h"
#include "BlinkService.h"
#include <map>

DigitalOut alivenessLED(LED1, 0);
DigitalOut actuatedLED(LED2, 0);

const static char     DEVICE_NAME[] = "KeyChain";
static const uint16_t uuid16_list[] = {BlinkService::SERVICE_UUID};

BlinkService *ledServicePtr;
std::map<GattAttribute::Handle_t, BLEServiceI *> services;
typedef pair<GattAttribute::Handle_t, BlinkService*> intServicePair;


void onBleInitError(BLE &ble, ble_error_t error)
{
    /* Initialization error handling should go here */
}

void blinkCallback(void)
{
    alivenessLED = !alivenessLED; /* Do blinky on LED1 to indicate system aliveness. */
}

void onDataWrittenCallback(const GattWriteCallbackParams *params) {
    if(params->len == 1){
		services.at(params->handle)->onWriteCallback(params);
    }

}

void disconnectionCallback(const Gap::DisconnectionCallbackParams_t *params)
{
    (void) params;
    BLE::Instance().gap().startAdvertising();
}

void bleInitComplete(BLE::InitializationCompleteCallbackContext *params)
{
    BLEDevice&  ble   = params->ble;
    ble_error_t error = params->error;

    if (error != BLE_ERROR_NONE) {
        /* In case of error, forward the error handling to onBleInitError */
        onBleInitError(ble, error);
        return;
    }

    /* Ensure that it is the default instance of BLE */
    if(ble.getInstanceID() != BLE::DEFAULT_INSTANCE) {
        return;
    }

    ble.gap().onDisconnection(disconnectionCallback);
    ble.gattServer().onDataWritten(onDataWrittenCallback);

    bool initialValueForLEDCharacteristic = false;
    ledServicePtr = new BlinkService(ble, initialValueForLEDCharacteristic);
    services.insert(intServicePair(ledServicePtr->getValueHandle(), ledServicePtr));

    /* setup advertising */
    ble.gap().accumulateAdvertisingPayload(GapAdvertisingData::BREDR_NOT_SUPPORTED | GapAdvertisingData::LE_GENERAL_DISCOVERABLE);
    ble.gap().accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LIST_16BIT_SERVICE_IDS, (uint8_t *)uuid16_list, sizeof(uuid16_list));
    ble.gap().accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LOCAL_NAME, (uint8_t *)DEVICE_NAME, sizeof(DEVICE_NAME));
    ble.gap().setAdvertisingType(GapAdvertisingParams::ADV_CONNECTABLE_UNDIRECTED);
    ble.gap().setAdvertisingInterval(1000); /* 1000ms. */
    ble.gap().startAdvertising();
}

void app_start(int, char**) {
//    minar::Scheduler::postCallback(blinkCallback).period(minar::milliseconds(500));
    BLE & ble = BLE::Instance();
    ble.init(bleInitComplete);
}
