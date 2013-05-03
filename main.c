/**************************************************************************/
/*! 
    @file     main.c
    @author   K. Townsend (microBuilder.eu)

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2011, microBuilder SARL
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "projectconfig.h"
#include "sysinit.h"

#include "core/gpio/gpio.h"
#include "core/cpu/cpu.h"
#include "core/timer16/timer16.h"
#include "core/timer32/timer32.h"
#include "core/systick/systick.h"

#ifdef CFG_INTERFACE
  #include "core/cmd/cmd.h"
#endif

/**************************************************************************/
/*! 
    Main program entry point.  After reset, normal code execution will
    begin here.
*/
/**************************************************************************/

uint16_t trigger;
extern volatile uint32_t timer32_1_counter;
uint32_t counterLast;

void setup(){
	  // Configure cpu and mandatory peripherals
	  systemInit();

	  //set up timer, delay is only here for reference
	  timer16Init(0, 0xafc8);

	  //enable the timer
	  timer16Enable(0);

	  // set start interval
	  trigger = 500;

	  // set counter
	  timer32Init(1, 72);
	  timer32Enable(1);

	  // Setup gpio
	  gpioInit();
	  gpioSetDir(2,0,gpioDirection_Output);
	  gpioSetValue(2,0,0);

	  // Setup an interrupt
	  gpioSetDir(1,5, gpioDirection_Input);
	  //gpioSetPullup(&IOCON_PIO1_8, gpioPullupMode_Inactive);
	  gpioSetInterrupt(1,
			  	  	   5,
			  	  	   gpioInterruptSense_Edge,
			  	  	   gpioInterruptEdge_Single,
			  	  	   gpioInterruptEvent_ActiveHigh);
	  gpioIntEnable(1,5);
	  gpioSetDir(1,8, gpioDirection_Input);
	  //gpioSetPullup(&IOCON_PIO1_8, gpioPullupMode_Inactive);
	  gpioSetInterrupt(1,
			  	  	   8,
			  	  	   gpioInterruptSense_Edge,
			  	  	   gpioInterruptEdge_Single,
			  	  	   gpioInterruptEvent_ActiveHigh);
	  gpioIntEnable(1,8);

	  gpioSetDir(2,1, gpioDirection_Input);
	  //gpioSetPullup(&IOCON_PIO1_8, gpioPullupMode_Inactive);
	  gpioSetInterrupt(2,
			  	  	   1,
			  	  	   gpioInterruptSense_Edge,
			  	  	   gpioInterruptEdge_Single,
			  	  	   gpioInterruptEvent_ActiveHigh);
	  gpioIntEnable(2,1);
}

int main(void)
{
	setup();

	while (1){
	  timer16DelayUS(0, trigger);
	  gpioSetValue(2,0,1);
	  gpioSetValue(2,0,0);
	}

	return 0;
}

// IRQ Handler for GPIO Port 1
void PIOINT1_IRQHandler(void){
	uint32_t regVal;

	//Check if we're pin1.5
	regVal = gpioIntStatus(1, 5);
	if (regVal){
		// Bottom button

		//clear the interrupt
		gpioIntClear(1, 5);
	}
	regVal = gpioIntStatus(1, 8);
	if (regVal){
		// Top button

		//clear the interrupt
		gpioIntClear(1,8);
	}
	return;
}

// IRQ Handler for GPIO Port 0
void PIOINT2_IRQHandler(void){
	uint32_t regVal;

	//Check if we're pin0.6
	regVal = gpioIntStatus(2, 1);
	if (regVal){
		//Do stuff here for the motor
		uint32_t time = timer32_1_counter;
		trigger = (time - counterLast) / 12;
		counterLast = time;

		// Clear
		gpioIntClear(2,1);
	}
	return;
}


