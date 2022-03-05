// **** INCLUDES *****
#include "LowPowerWdt.h"
#include <avr/wdt.h>


// OPTIONAl CODE needed if there is a need to know the restart reason - see also inside Setup()
// The following is taken from: https://forum.arduino.cc/t/how-to-distinguish-between-reset-and-real-power-loss/239738/4
// I have no idea how it works, but apparently it is needed to extract the MCUSR value which is saved in r2 by Optiboot 
// See AVR datasheet regarding MCUSR
// It should work with Optiboot 4.6 or later
// Tested with ATMega328P running MiniCore (https://github.com/MCUdude/MiniCore)

uint8_t mcusr __attribute__ ((section (".noinit")));
void getMCUSR(void) __attribute__((naked)) __attribute__((section(".init0")));

void getMCUSR(void)
{
    __asm__ __volatile__ ( "mov %0, r2 \n" : "=r" (mcusr) : );
}

void setup()
{
    Serial.begin(115200);
    // Attempt to identify the reset source. Note: this may not work with all bootloaders. Should work with boards usign Optiboot 6.6 or later, see https://github.com/Optiboot/optiboot/wiki/HowOptibootWorks 

    // OPTIONAL code to determine the restart reason   
    // From MCUSR we can get the reason for a reset. Multiple bits can be set at the same time, the logic below seems to work, at least in my case
    // DISCLAIMER: YMMV! May not work for your application due to a large number of possible differences in microcontroller, board, bootloader, etc.
    // However, often there is no need to know the reason for a reset. 
    Serial.print(F("MCUSR: ")); Serial.println(mcusr);
    Serial.print(F("Reset reason: "));  
    if ( bitRead(mcusr, PORF) ) {
        Serial.print(F("Power_On"));
    } else if ( bitRead(mcusr, EXTRF) ) { 
        Serial.print(F("External"));
    } else if ( bitRead(mcusr, WDRF) ) {
        Serial.print(F("Watchdog"));  
    } else if ( bitRead(mcusr, BORF) ) {
        Serial.print(F("BOD"));
    } else {
        Serial.print(F("Unknown"));
    }
    MCUSR = 0x00;
    Serial.println();
    Serial.flush();

    // MANDATORY when using LowPowerWdt   
    // Contrary to LowPower, Setup is almost always required for LowPowerWdt, otherwise:
    //                           1) after using one of the sleep modes the watchdog will be active, potentially with a too short timeout
    //                           2) if a bug cause the watchdog to restart immdiately after reset, there may not be enough time to reload the sketch
    //                           
    LowPower.setup(WDTO_2S);    // Setup the watchdog with 4s timeout
    Serial.println("Setup complete");
    Serial.flush();  
}

static unsigned int loop_counter = 0;
void loop() 
{
    // Enter power down state for 8 s with ADC and BOD module disabled
    LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);  
    Serial.print("Just woke up from a 4s power down - counter = "); Serial.println(loop_counter); Serial.flush();
    // Normally you would something here
    // Example: Read sensor, data logging, data transmission.
    if (++loop_counter >5) { //Now we simulate a hanging
       Serial.println("Ops, I know we are going to hung now..."); Serial.flush();
       while(true);
    }   
    wdt_reset();
}

