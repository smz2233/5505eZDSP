/*****************************************************************************/
/*                                                                           */
/* FILENAME                                                                  */ 
/* 	sinewaves.h                                                              */                           
/*                                                                           */
/* DESCRIPTION                                                               */
/*   Header file for generating sine waves.                                  */
/*                                                                           */
/* REVISION                                                                  */
/*   Revision: 1.00	                                                         */ 
/*   Author  : Richard Sikora                                                */ 
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* HISTORY                                                                   */
/*   Revision 1.00                                                           */
/*   15th February 2010. Created by Richard Sikora from TMS320C5510 code.    */
/*   16th June 2010. Sinewave generator added for 8000 Hz sampling rate.     */
/*                                                                           */
/*****************************************************************************/
/*
 *
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

#ifndef SINE_WAVES_H
#define SINE_WAVES_H

 signed int generate_sinewave_1( signed short int frequency, 
                                signed short int amplitude);

 signed int generate_sinewave_2( unsigned short int frequency, 
                                unsigned short int amplitude);                                

 signed int generate_sinewave_3( unsigned short int frequency, 
                                unsigned short int amplitude); 
#endif

/*****************************************************************************/
/* End of sinewaves.h                                                        */
/*****************************************************************************/
