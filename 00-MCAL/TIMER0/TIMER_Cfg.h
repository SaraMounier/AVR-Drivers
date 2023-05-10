/*************************************************************
 * 
 * Filename: TIMER_Cfg.h
 * Description: Configuration header file of the TIMER driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __TIMER_CFG_H__
#define __TIMER_CFG_H__

#define MC_frequency  1000000UL
#define SELECTED_PRESCALER				CLK_DivBy1024

#define WAVE_FORM_GEN_MODE_CGF			WGM_NORMAL
#define OUTUT_COMPARE_MATCH_MODE_CFG   	OC0_NON_PWM_TOGGLE_ON_COMPARE_MATCH

// #define INTx_TIMER0_OVER_FLOW               INT11_vect
// #define INTx_TIMER0_OUTPUT_COMPARE_MATCH  	INT10_vect


#endif /* __TIMER_CFG_H__ */