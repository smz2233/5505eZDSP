/*****************************************************************************/
/*                                                                           */
/* FILENAME                                                                  */
/* 	IIR_filters_fourth_order.c                                               */
/*                                                                           */
/* DESCRIPTION                                                               */
/*   Infinite Impulse Response (IIR) filters fourth order type I and type II */
/*   Takes 3 numerator coefficients and 3 denominator coefficients.          */
/*                                                                           */
/* REVISION                                                                  */
/*   Revision: 1.00	                                                         */
/*   Author  : Richard Sikora                                                */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* HISTORY                                                                   */
/*   Revision 1.00                                                           */
/*   7th February 2010. Created by Richard Sikora from C5510 code.           */
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

/*****************************************************************************/
/*                                                                           */
/* A second infinite impulse response (IIR) filter can be represented by     */
/* the following equation:                                                   */
/*                                                                           */
/* H(z) = b0 + b1.z^-1 + b2.z^-2                                             */
/*        ----------------------                                             */
/*        a0 + a1.z^-1 + a2.z^-2                                             */  
/*                                                                           */ 
/* where H(z) is the transfer function. a0 is always 1.000                   */
/*                                                                           */
/* To implement a fourth order filter, two of these stages are cascaded.     */
/*                                                                           */
/* In order to implement this function on a fixed point processor, the value */
/* 32767 is used to represent 1.000                                          */
/*                                                                           */
/* Because the coefficients b1 and a1 can lie in the range -2.000 to +2.000, */
/* the coeffients supplied to the function are b1/2 and a1/2.                */
/*                                                                           */
/*****************************************************************************/


/* Numerator coefficients */
#define B0 0
#define B1 1
#define B2 2

/* Denominator coefficients */
#define A0 3
#define A1 4
#define A2 5

/*****************************************************************************/
/* fourth_order_IIR_direct_form_I()                                          */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* Fourth order direct form I IIR filter implemented by cascading two second */
/* order filters.                                                            */
/*                                                                           */
/* This implementation uses two buffers, one for x[n] and the other for y[n] */
/*                                                                           */
/*****************************************************************************/

signed int fourth_order_IIR_direct_form_I( const signed int * coefficients, signed int input)
{
  long temp;
  static signed int x[2][3] = { 0, 0, 0, 0, 0, 0 };  /* x(n), x(n-1), x(n-2). Must be static */
  static signed int y[2][3] = { 0, 0, 0, 0, 0, 0 };  /* y(n), y(n-1), y(n-2). Must be static */ 
  unsigned int stages;

  temp = (long) input; /* Copy input to temp */

  for ( stages = 0 ; stages < 2 ; stages++)
    {
     x[stages][0] = (signed int) temp; /* Copy input to x[stages][0] */
    
     temp =  ( (long) coefficients[B0] * x[stages][0]) ;   /* B0 * x(n)     */
  
     temp += ( (long) coefficients[B1] * x[stages][1]);    /* B1/2 * x(n-1) */

     temp += ( (long) coefficients[B1] * x[stages][1]);    /* B1/2 * x(n-1) */

     temp += ( (long) coefficients[B2] * x[stages][2]);    /* B2 * x(n-2)   */
  
     temp -= ( (long) coefficients[A1] * y[stages][1]);    /* A1/2 * y(n-1) */
  
     temp -= ( (long) coefficients[A1] * y[stages][1]);    /* A1/2 * y(n-1) */

     temp -= ( (long) coefficients[A2] * y[stages][2]);    /* A2 * y(n-2)   */
 
     /* Divide temp by coefficients[A0] */    

     temp >>= 15;

     /* Range limit temp between maximum and minimum */

     if ( temp > 32767 )
       {
         temp = 32767;
       }
     else if ( temp < -32767)
       {
         temp = -32767;
       }

     y[stages][0] = (short int) ( temp );

     /* Shuffle values along one place for next time */
  
     y[stages][2] = y[stages][1];   /* y(n-2) = y(n-1) */
     y[stages][1] = y[stages][0];   /* y(n-1) = y(n)   */
    
     x[stages][2] = x[stages][1];   /* x(n-2) = x(n-1) */
     x[stages][1] = x[stages][0];   /* x(n-1) = x(n)   */

     /* temp is used as input next time through */
   }

 return ( (short int) temp ); 
}

signed int fourth_order_IIR_direct_form_IA( const signed int * coefficients, signed int input)
{
  long temp;
  static signed int x[2][3] = { 0, 0, 0, 0, 0, 0 };  /* x(n), x(n-1), x(n-2). Must be static */
  static signed int y[2][3] = { 0, 0, 0, 0, 0, 0 };  /* y(n), y(n-1), y(n-2). Must be static */ 
  unsigned int stages;

  temp = (long) input; /* Copy input to temp */

  for ( stages = 0 ; stages < 2 ; stages++)
    {
     x[stages][0] = (signed int) temp; /* Copy input to x[stages][0] */
    
     temp =  ( (long) coefficients[B0] * x[stages][0]) ;   /* B0 * x(n)     */
  
     temp += ( (long) coefficients[B1] * x[stages][1]);    /* B1/2 * x(n-1) */

     temp += ( (long) coefficients[B1] * x[stages][1]);    /* B1/2 * x(n-1) */

     temp += ( (long) coefficients[B2] * x[stages][2]);    /* B2 * x(n-2)   */
  
     temp -= ( (long) coefficients[A1] * y[stages][1]);    /* A1/2 * y(n-1) */
  
     temp -= ( (long) coefficients[A1] * y[stages][1]);    /* A1/2 * y(n-1) */

     temp -= ( (long) coefficients[A2] * y[stages][2]);    /* A2 * y(n-2)   */
 
     /* Divide temp by coefficients[A0] */    

     temp >>= 15;

     /* Range limit temp between maximum and minimum */

     if ( temp > 32767 )
       {
         temp = 32767;
       }
     else if ( temp < -32767)
       {
         temp = -32767;
       }

     y[stages][0] = (short int) ( temp );

     /* Shuffle values along one place for next time */
  
     y[stages][2] = y[stages][1];   /* y(n-2) = y(n-1) */
     y[stages][1] = y[stages][0];   /* y(n-1) = y(n)   */
    
     x[stages][2] = x[stages][1];   /* x(n-2) = x(n-1) */
     x[stages][1] = x[stages][0];   /* x(n-1) = x(n)   */

     /* temp is used as input next time through */
   }

 return ( (short int) temp ); 
}

/*****************************************************************************/
/* fourth_order_IIR_direct_form_II()                                         */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* Cascades two second order IIR filters.                                    */
/* Uses 32767 to represent 1.000.                                            */
/* Note that input is divided by 128 to prevent overload.                    */
/*                                                                           */
/*****************************************************************************/

signed int fourth_order_IIR_direct_form_II ( const signed int * coefficients, signed int input)
{
  long temp;
  static short int delay[2][3] = { 0, 0, 0, 0, 0, 0};
  unsigned int stages;

  /* Copy input to temp for temporary storage */

  temp = (long) input; 

  for ( stages = 0 ; stages < 2 ; stages++)
    {
      /* Process denominator coefficients */

     delay[stages][0] = (signed int) temp;

     temp = (( (long) coefficients[A0] * delay[stages][0] ) >> 7); /* Divide by 128 */
  
     temp -= ( (long) coefficients[A1] * delay[stages][1] );  /* A1/2 */

     temp -= ( (long) coefficients[A1] * delay[stages][1] );  /* A1/2 */  

     temp -= ( (long) coefficients[A2] * delay[stages][2] );
  
     temp >>= 15;  /* Divide temp by coefficients[A0] */

     if ( temp > 32767)
       {
         temp = 32767;
       }
     else if ( temp < -32767)
       {
         temp = -32767;
       }  

     delay[stages][0] = ( signed int ) temp;

     /* Process numerator coefficients */

     temp = ((long) coefficients[B0] * delay[stages][0] );

     temp += ((long) coefficients[B1] * delay[stages][1] ) ;  /* B1/2 */ 

     temp += ((long) coefficients[B1] * delay[stages][1] ) ;  /* B1/2 */

     temp += ((long) coefficients[B2] * delay[stages][2] ) ;  

     delay[stages][2] = delay[stages][1];
     delay[stages][1] = delay[stages][0];

     /* Divide temp by coefficients[A0] then multiply by 128 */

     temp >>= ( 15 - 7 );

     /* Range limit temp between maximum and minimum */

     if ( temp > 32767)
       {
         temp = 32767;
       }
     else if ( temp < -32767)
       {
         temp = -32767;
       }  

     /* Temp will be fed into input of filter next time through */
    }

  return ( (short int) temp ); 
}

/*****************************************************************************/
/* second_order_IIR_direct_form_I()                                          */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* Second order direct form I IIR filter implemented by cascading two second */
/* order filters.                                                            */
/*                                                                           */
/* This implementation uses two buffers, one for x[n] and the other for y[n] */
/*                                                                           */
/*****************************************************************************/

signed int second_order_IIR_direct_form_I( const signed int * coefficients, signed int input)
{
  long temp;
  static signed int x[3] = { 0, 0, 0 };  /* x(n), x(n-1), x(n-2). Must be static */
  static signed int y[3] = { 0, 0, 0 };  /* y(n), y(n-1), y(n-2). Must be static */ 

     x[0] = input; /* Copy input to x[0] */
      
     temp =  ( (long) coefficients[B0] * x[0]) ;   /* B0 * x(n)     */
     temp += ( (long) coefficients[B1] * x[1]);    /* B1/2 * x(n-1) */
     temp += ( (long) coefficients[B1] * x[1]);    /* B1/2 * x(n-1) */
     temp += ( (long) coefficients[B2] * x[2]);    /* B2 * x(n-2)   */
     temp -= ( (long) coefficients[A1] * y[1]);    /* A1/2 * y(n-1) */
     temp -= ( (long) coefficients[A1] * y[1]);    /* A1/2 * y(n-1) */
     temp -= ( (long) coefficients[A2] * y[2]);    /* A2 * y(n-2)   */
 
     /* Divide temp by coefficients[A0] to remove fractional part */    
     temp >>= 15;

     y[0] = (short int) ( temp );

     /* Shuffle values along one place for next time */
  
     y[2] = y[1];   /* y(n-2) = y(n-1) */
     y[1] = y[0];   /* y(n-1) = y(n)   */
    
     x[2] = x[1];   /* x(n-2) = x(n-1) */
     x[1] = x[0];   /* x(n-1) = x(n)   */

 return ( (short int) temp ); 
}



/*****************************************************************************/
/* End of IIR_filters_fourth_order.c                                         */
/*****************************************************************************/

