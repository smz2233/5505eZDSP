/*
 * timer.h
 *
 *  Created on: 2024Äê3ÔÂ24ÈÕ
 *      Author: 78450
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#define AUDIOBACK_COUNT    (10)
#define SWITCH_SECS        (15)

#define CSL_TEST_FAILED    (1u)
#define CSL_TEST_PASSED    (0)

#define CSL_PLL_DIV_000    (0)
#define CSL_PLL_DIV_001    (1u)
#define CSL_PLL_DIV_002    (2u)
#define CSL_PLL_DIV_003    (3u)
#define CSL_PLL_DIV_004    (4u)
#define CSL_PLL_DIV_005    (5u)
#define CSL_PLL_DIV_006    (6u)
#define CSL_PLL_DIV_007    (7u)

#define CSL_PLL_CLOCKIN    (32768u)

#define PLL_CNTL1        *(ioport volatile unsigned *)0x1C20
#define PLL_CNTL2        *(ioport volatile unsigned *)0x1C21
#define PLL_CNTL3        *(ioport volatile unsigned *)0x1C22
#define PLL_CNTL4        *(ioport volatile unsigned *)0x1C23

#define CSL_SYS_CGCR2_M_MASK                        (0x3000)
#define CSL_SYS_CGCR2_M_SHIFT                       (12)
#define CSL_SYS_CGCR4_OUTDIV2Bypass_MASK            (0x0100)
#define CSL_SYS_CGCR4_OUTDIV2Bypass_SHIFT           (8)

extern void VECSTART(void);

/**
 *  \brief  GPT Count Rate Verification test function
 *
 * This function verifies whether timer is running at the configured
 * rate or not. This function configures and enables the GPT interrupts
 * to indicate the expiry of the timer count. Test counts number of
 * cycles executed by the CPU after starting the timer till the expiry
 * of the timer. These cycles are used to verify the WDT count rate.
 * It is assumed that calculated CPU cycles will be with in the range
 * ï¿?% actual CPU clock cycles. Test will be successful if the calculated
 * CPU cycles fall with in this range.
 *
 * NOTE: Changing the PLL setting in the middle (After getSysClk() call)
 *       of the test will result in test failure.
 *
 *  \param  none
 *
 *  \return CSL_TEST_PASSED  - Success
 *          CSL_TEST_FAILED  - Failure
 */
void CSL_gptIntrTest(void);

/**
 *  \brief  Function to calculate the system clock
 *
 *  \param    none
 *
 *  \return   System clock value in KHz
 */
Uint32 getSysClk(void);

/**
 *  \brief  GPT Interrupt Service Routine
 *
 *  \param  none
 *
 *  \return none
 */
interrupt void gpt0Isr(void);

void timer_disable();

#endif /* INC_TIMER_H_ */
