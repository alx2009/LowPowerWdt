// **** INCLUDES *****
// Note: this example is not yet tested. Note that LowPower should work in this case, as the watchdog timer is not used for sleep modes
#include "LowPowerWdt.h"
#include <avr/wdt.h>

// Use pin 2 as wake up pin
const int wakeUpPin = 2;

void wakeUp()
{
    // Just a handler for the pin interrupt.
}

void setup()
{
    // MANDATORY when using LowPowerWdt   
    // Contrary to LowPower, Setup is almost always required for LowPowerWdt, otherwise:
    //                           1) after using one of the sleep modes the watchdog will be active, potentially with a too short timeout
    //                           2) if a bug cause the watchdog to restart immdiately after reset, there may not be enough time to reload the sketch
    //                           
    LowPower.setup(WDTO_2S);    // Setup the watchdog with 4s timeout

    // Configure wake up pin as input.
    // This will consumes few uA of current.
    pinMode(wakeUpPin, INPUT);   
}

void loop() 
{
    // Allow wake up pin to trigger interrupt on low.
    attachInterrupt(0, wakeUp, LOW);
    
    // Enter power down state with ADC and BOD module disabled.
    // Wake up when wake up pin is low.
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 
    
    // Disable external pin interrupt on wake up pin.
    detachInterrupt(0); 
    
    // Do something here
    // Example: Read sensor, data logging, data transmission.
    
    wdt_reset(); // This should be called often enough (when the CPU is running, not during sleep modes - obviously) in order to reset the watchdog timer

}
