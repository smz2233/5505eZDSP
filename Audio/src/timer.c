/*
 * timer.c
 *
 *  Created on: 2024Äê3ÔÂ24ÈÕ
 *      Author: 78450
 */

#include <stdio.h>
#include "csl_gpt.h"
#include "csl_intc.h"
#include <csl_general.h>
#include "timer.h"

CSL_Handle    hGpt;
Uint32        sysClk;


unsigned long int i = 0;
unsigned int Step = 0;
unsigned int playnum = 0;

void CSL_gptIntrTest(void)
{
    CSL_Status    status;
    CSL_Config    hwConfig;
    CSL_GptObj    gptObj;
    Uint32        TIMPRD;

    status   = 0;

    /* Get the System clock value at which CPU is currently running */
    sysClk = getSysClk();

    printf("\nCPU clock is running at %ldKHz\n", sysClk);
    printf("Timer Prescaler Divide Value is Set to Divide by 4\n");

    /* Open the CSL GPT module */
    hGpt = GPT_open (GPT_0, &gptObj, &status);

    /* Reset the GPT module */
    status = GPT_reset(hGpt);

    /* Clear any pending interrupts */
    IRQ_clearAll();

    /* Disable all the interrupts */
    IRQ_disableAll();

    IRQ_setVecs((Uint32)(&VECSTART));
    IRQ_plug(TINT_EVENT, &gpt0Isr);
    IRQ_enable(TINT_EVENT);

    TIMPRD = sysClk*1000/4;
    hwConfig.autoLoad    = GPT_AUTO_ENABLE;
    hwConfig.ctrlTim     = GPT_TIMER_ENABLE;
    hwConfig.preScaleDiv = GPT_PRE_SC_DIV_1;
    hwConfig.prdLow      = (TIMPRD)%65536;
    hwConfig.prdHigh     = (TIMPRD)/65536;

    /* Configure the GPT module */
    status =  GPT_config(hGpt, &hwConfig);

    /* Enable CPU Interrupts */
    IRQ_globalEnable();

    /* Start the Timer */
    GPT_start(hGpt);
}

/**
 *  \brief  GPT Interrupt Service Routine
 *
 *  \param  none
 *
 *  \return none
 */
interrupt void gpt0Isr(void)
{
    i++;
    if(i == SWITCH_SECS)
    {
        i = 0;
        Step = ++playnum % 2;
    }
    IRQ_clear(TINT_EVENT);
    /* Clear Timer Interrupt Aggregation Flag Register (TIAFR) */
    CSL_SYSCTRL_REGS->TIAFR = 0x01;
}

/**
 *  \brief  Function to calculate the clock at which system is running
 *
 *  \param    none
 *
 *  \return   System clock value in KHz
 */
#if (defined(CHIP_C5505_C5515) || defined(CHIP_C5504_C5514) || defined(CHIP_C5535) || defined(CHIP_C5545))

Uint32 getSysClk(void)
{
    Bool      pllRDBypass;
    Bool      pllOutDiv;
    Bool      pllOutDivBypass;
    Uint32    sysClk;
    Uint16    pllMH;
    Uint16    pllML;
    Uint16    pllRD;
    Uint16    pllOD;

    pllMH = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR1, SYS_CGCR1_M);
    pllML = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR2, SYS_CGCR2_M);

    pllRD = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR2, SYS_CGCR2_RDRATIO);
    pllOD = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR4, SYS_CGCR4_ODRATIO);

    pllRDBypass = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR2, SYS_CGCR2_RDBYPASS);
    pllOutDiv   = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR4, SYS_CGCR4_OUTDIVEN);
    pllOutDivBypass   = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR4, SYS_CGCR4_OUTDIV2Bypass);

    sysClk = CSL_PLL_CLOCKIN;

    if (0 == pllRDBypass)
    {
        sysClk = sysClk/(pllRD + 4);
    }

    sysClk = (sysClk * (pllMH*4 + pllML + 4));

    if (1 == pllOutDivBypass)
    {
        sysClk = sysClk/2;
    }
    if(1 == pllOutDiv)
    {
        sysClk = sysClk/(pllOD + 4);
    }

    /* Return the value of system clock in KHz */
    return(sysClk/1000);
}

#elif (defined(CHIP_C5517))
Uint32 getSysClk(void)
{
    Uint32    sysClk;
    float    Multiplier;
    Uint16    OD;
    Uint16    OD2;
    Uint16    RD, RefClk;
    Uint32    temp1, temp2, temp3, vco;

    temp2 =  PLL_CNTL2;
    temp3 =  (temp2 & 0x8000) <<1 ;
    temp1 = temp3 + PLL_CNTL1;
    Multiplier = temp1/256 +1;
    RD = (PLL_CNTL2 & 0x003F) ;

    RefClk = 12000/(RD+1);

    vco = Multiplier * (Uint32)RefClk;

    OD = (PLL_CNTL4 & 0x7);

    sysClk = vco/(OD+1);

    OD2 = ((PLL_CNTL4 >> 10) & 0x1F) ;

    if (PLL_CNTL3 & 0x8000) // PLL Bypass
        sysClk = RefClk;
    else
        sysClk = vco/(OD+1);

    if ((PLL_CNTL4 & 0x0020) == 0)  /* OutDiv2 */
        sysClk = sysClk / ( 2*(OD2+1));

    /* Return the value of system clock in KHz */
    return(sysClk);
}
#else

Uint32 getSysClk(void)
{
    Bool      pllRDBypass;
    Bool      pllOutDiv;
    Bool      pllOutDiv2;
    Uint32    sysClk;
    Uint16    pllVP;
    Uint16    pllVS;
    Uint16    pllRD;
    Uint16    pllVO;
    Uint16    pllDivider;
    Uint32    pllMultiplier;

    pllVP = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR1, SYS_CGCR1_MH);
    pllVS = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR2, SYS_CGCR2_ML);

    pllRD = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR2, SYS_CGCR2_RDRATIO);
    pllVO = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR4, SYS_CGCR4_ODRATIO);

    pllRDBypass = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR2, SYS_CGCR2_RDBYPASS);
    pllOutDiv   = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR4, SYS_CGCR4_OUTDIVEN);
    pllOutDiv2  = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR4, SYS_CGCR4_OUTDIV2BYPASS);
    pllDivider = ((pllOutDiv2) | (pllOutDiv << 1) | (pllRDBypass << 2));

    pllMultiplier = ((Uint32)CSL_PLL_CLOCKIN * ((pllVP << 2) + pllVS + 4));

    switch(pllDivider)
    {
        case CSL_PLL_DIV_000:
        case CSL_PLL_DIV_001:
            sysClk = pllMultiplier / (pllRD + 4);
        break;

        case CSL_PLL_DIV_002:
            sysClk = pllMultiplier / ((pllRD + 4) * (pllVO + 4) * 2);
        break;

        case CSL_PLL_DIV_003:
            sysClk = pllMultiplier / ((pllRD + 4) * 2);
        break;

        case CSL_PLL_DIV_004:
        case CSL_PLL_DIV_005:
            sysClk = pllMultiplier;
        break;

        case CSL_PLL_DIV_006:
            sysClk = pllMultiplier / ((pllVO + 4) * 2);
        break;

        case CSL_PLL_DIV_007:
            sysClk = pllMultiplier / 2;
        break;
    }

    /* Return the value of system clock in KHz */
    return(sysClk/1000);
}

#endif

void timer_disable()
{
    /* Disable the CPU interrupts */
    IRQ_globalDisable();

    /* Clear any pending interrupts */
    IRQ_clearAll();

    /* Disable all the interrupts */
    IRQ_disableAll();

    /* Stop the Timer */
    GPT_stop(hGpt);

    /* Close The GPT Module */
    GPT_close(hGpt);
}
