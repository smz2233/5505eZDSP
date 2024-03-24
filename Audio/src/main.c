
/*****************************************************************************/
/*                                                                           */
/* PROJECT                                                                   */
/*   IIRFilters                                                              */
/*                                                                           */
/* FILENAME                                                                  */
/*   main.c                                                                  */
/*                                                                           */
/* DESCRIPTION                                                               */
/*   Finite Impulse Response (IIR) Filters.                                  */
/*   Low pass and high pass filters. Audio line in / audio headphones out.   */
/*                                                                           */
/* REVISION                                                                  */
/*   Revision: 1.00                                                          */
/*   Author  : Richard Sikora                                                */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* HISTORY                                                                   */
/*                                                                           */
/*   Revision 1.00   Richard Sikora                                          */
/*   5th March 2010. Original template code from Spectrum Digital.           */
/*                                                                           */
/*   Revision 1.01   Richard Sikora                                          */
/*   10th August 2010. Converted to use CSL                                  */
/*                                                                           */
/*****************************************************************************/
/*
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 *
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#include <stdio.h>
#include "usbstk5505.h"
#include "aic3204.h"
#include "PLL.h"
#include "stereo.h"
#include "IIR_band_pass_filters.h"
#include "IIR_band_stop_filters.h"
#include "IIR_filters_fourth_order.h"
#include "IIR_low_pass_filters.h"
#include "IIR_high_pass_filters.h"
#include "SweepGenerator.h"
#include "timer.h"

#define SAMPLES_PER_SECOND 48000
#define GAIN_IN_dB  10

Int16 left_input;
Int16 right_input;
Int16 left_output;
Int16 right_output;
Int16 mono_input;

extern unsigned int Step;
extern unsigned int playnum;

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  main( )                                                                 *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void main( void )
{
    /* Initialize BSL */
    USBSTK5505_init( );

    /* Initialize the Phase Locked Loop in EEPROM */
    pll_frequency_setup(100);

    /* Initialise hardware interface and I2C for code */
    aic3204_hardware_init();

    /* Initialise the AIC3204 codec */
    aic3204_init();

    printf("\n\nRunning IIR Filters Project using main.c\n");
    printf( "<-> Audio Loopback from Stereo Line IN --> to HP/Lineout\n\n" );

    /* Set sampling frequency in Hz and ADC gain in dB */
    set_sampling_frequency_and_gain(SAMPLES_PER_SECOND, GAIN_IN_dB);

    puts("Changes configuration once every 15 seconds");
    printf("The program will end after %d changes\n", AUDIOBACK_COUNT);

    CSL_gptIntrTest();
    while(playnum < AUDIOBACK_COUNT)
    {

        aic3204_codec_read(&left_input, &right_input); // Configured for one interrupt per two channels.

        mono_input = stereo_to_mono(left_input, right_input); // Generate mono signal

        if ( Step == 0 )
        {
            left_output = left_input;      // Directly connect inputs to outputs for reference.
            right_output = right_input;
        }
        else if ( Step == 1 )
        {
            /* Low pass filter 4800 Hz */
            left_output = fourth_order_IIR_direct_form_I ( &IIR_low_pass_4800Hz[0], mono_input);
            /* High pass filter 4800 Hz */
            right_output = fourth_order_IIR_direct_form_I ( &IIR_low_pass_4800Hz[0], mono_input);
        }

        aic3204_codec_write(left_output, right_output);
    }

    /* Disable I2S and put codec into reset */
    aic3204_disable();
    /* Disable all interrupts and put timer into reset */
    timer_disable();
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  End of main.c                                                           *
 *                                                                          *
 * ------------------------------------------------------------------------ */

