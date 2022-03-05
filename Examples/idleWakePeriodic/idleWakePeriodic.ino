// **** INCLUDES *****
#include "LowPowerWdt.h"
#include <avr/wdt.h>


void setup()
{
    // MANDATORY when using LowPowerWdt   
    // Contrary to LowPower, Setup is almost always required for LowPowerWdt, otherwise:
    //                           1) after using one of the sleep modes the watchdog will be active, potentially with a too short timeout
    //                           2) if a bug cause the watchdog to restart immdiately after reset, there may not be enough time to reload the sketch
    //                           
    LowPower.setup(WDTO_2S);    // Setup the watchdog with 4s timeout
}

void loop() 
{
  // Enter idle state for 8 s with the rest of peripherals turned off
  // Each microcontroller comes with different number of peripherals
  // Comment off line of code where necessary


#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega168__) 
  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
                SPI_OFF, USART0_OFF, TWI_OFF);
#elif defined __AVR_ATmega644P__ || defined (__AVR_ATmega1284P__)
  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF,
    TIMER1_OFF, TIMER0_OFF, SPI_OFF,
    USART1_OFF, USART0_OFF, TWI_OFF);
#endif
               
  // ATmega32U4
  //LowPower.idle(SLEEP_8S, ADC_OFF, TIMER4_OFF, TIMER3_OFF, TIMER1_OFF, 
  //      TIMER0_OFF, SPI_OFF, USART1_OFF, TWI_OFF, USB_OFF);

  // ATmega2560
  //LowPower.idle(SLEEP_8S, ADC_OFF, TIMER5_OFF, TIMER4_OFF, TIMER3_OFF, 
  //      TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART3_OFF, 
  //      USART2_OFF, USART1_OFF, USART0_OFF, TWI_OFF);

  // ATmega256RFR2
  //LowPower.idle(SLEEP_8S, ADC_OFF, TIMER5_OFF, TIMER4_OFF, TIMER3_OFF, 
  //      TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF,
  //      USART1_OFF, USART0_OFF, TWI_OFF);

  // Do something here
  // Example: Read sensor, data logging, data transmission.
  wdt_reset(); // This should be called often enough (when the CPU is running, not during sleep modes - obviously) in order to reset the watchdog timer
}

