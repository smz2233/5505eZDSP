/*****************************************************************************/
/*                                                                           */
/* FILENAME                                                                  */
/*   SweepGenerator.c                                                        */
/*                                                                           */
/* DESCRIPTION                                                               */
/*   Generate frequencies between 20Hz and 20000Hz using a logarithmic       */
/*   sweep.                                                                  */
/*                                                                           */
/*   Uses e power x using the expn() function from 55xdsph.lib               */
/*   This produces a Q4.12 output between 1000h (1.000) to 2B7Dh (2.718 = e) */   
/*                                                                           */
/* REVISION                                                                  */
/*   Revision: 1.01                                                          */
/*   Author  : Richard Sikora                                                */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* HISTORY                                                                   */
/*                                                                           */
/*   Revision 1.00                                                           */
/*   20th December 2009. Created by Richard Sikora.                          */
/*   Revision 1.01                                                           */
/*   14th March 2010. step made static to suppress linker error in main      */
/*                                                                           */
/*****************************************************************************/

#include "tms320.h"
#include "dsplib.h"

#define SAMPLES_PER_SECOND 48000

#define E__3  0xA0AFUL   // 20.0855 in unsigned Q6:10 format
#define E__4  0xDA64UL   // 54.5981 in unsigned Q6:10 format
#define E__5  0x9469UL   // 148.413 in unsigned Q8:8 format
#define E__6  0xC980UL   // 403.28  in unsigned Q9:7 format
#define E__7  0x8910UL   // 1096.53 in unsigned Q11:5 format
#define E__8  0xBA4FUL   // 2980.95 in unsigned Q12:4 format
#define E__9  0xFD38UL   // 8103.08 in unsigned Q13:3 format

#define TICKS_1s 	22369   // Scaling factor for ticks for 1 second per scan
#define TICKS_2_8s 	 7829   // Scaling factor for ticks for 2.8 seconds per scan

static DATA counter = 0;
static unsigned long ticks = 0; // May need to exceed 48000

static enum {step_e3, step_e4, step_e5, step_e6, step_e7, step_e8, step_e9 } step = step_e3;

/*****************************************************************************/
/* SweepGenerator()                                                          */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* Generate frequencies between 20Hz and 20000Hz on a logarithmic scale.     */
/*                                                                           */
/*                                                                           */
/* CALLED BY: Called by main() loop once every 1/48000 second.               */ 
/* RETURNS: Frequency between 20Hz and 20000Hz.                              */
/*                                                                           */
/*****************************************************************************/


unsigned int SweepGenerator(void)
{
 DATA exponent;
 unsigned int frequency = 0;	
 long temp;

 temp = (ticks * TICKS_2_8s); // Multiply ticks by scaling factor for time.
 temp >>=15;                  // Remove fractional part 
 counter = (DATA) temp;
 ticks++;
 
 /* Always calculate the exponent */
 expn(&counter, &exponent, 1); // Determine e power x
  	
 switch (step)
 {
  case step_e3:
  default:
  	temp = ( exponent * E__3);    // Multiply by e power 3
  	frequency = (unsigned int)(temp >> 23);  // Remove fractional part. Shift before cast.

  	if ( counter >= 32767)
   	{
   		ticks = 0;       // Reset counter back to beginning
   		step = step_e4;    // Go to next step of sweep
   	} 

  break;
  
  case step_e4:
    temp = (exponent * E__4);
    frequency = (unsigned int)(temp >> 22); 

   if ( counter >= 32767)
     {
      	ticks = 0;
      	step = step_e5; // Go to next step of sweep.
     } 
     
   break;
  
  case step_e5:
    temp = (exponent * E__5);
    frequency = (unsigned int)(temp >> 20); 
  
    if ( counter >= 32767)
     {
      	ticks = 0;
      	step = step_e6; // Go to next step of sweep.
     } 

   break;  
  
  case step_e6:
    temp = (exponent * E__6);
    frequency = (unsigned int)(temp >> 19); 
  
   if ( counter >= 32767)
     {
      	ticks = 0;
      	step = step_e7; // Go to next step of sweep.
     } 

   break; 
  
  case step_e7:
    temp = (exponent * E__7);
    frequency = (unsigned int)(temp >> 17); 
  
    if ( counter >= 32767)
     {
      	ticks = 0;
      	step = step_e8; // Go to next step of sweep.
     } 

   break; 
  
  case step_e8:
    temp = (exponent * E__8);
    frequency = (unsigned int)(temp >> 16); 
  
    if ( counter >= 32767)
     {
      	ticks = 0;
      	step = step_e9; // Go to next step of sweep.
     } 

   break; 
   
  case step_e9:
    temp = (exponent * E__9);
    frequency = (unsigned int)(temp >> 15); 
  
    if ( counter >= 32767)
     {
      	ticks = 0;
      	step = step_e3; // Go to next step of sweep.
     } 

   break;   
 }

 return (frequency);
}

/******************************************************************************/
/* End of SweepGenerator.c                                                    */
/******************************************************************************/


