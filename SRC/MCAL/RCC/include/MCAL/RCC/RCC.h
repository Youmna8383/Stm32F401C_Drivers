#ifndef RCC_H_
#define RCC_H_
#include <LIB/std_types.h>

/*error status */
typedef enum {
  RCC_enuOK,
  RCC_enuNotOK
}RCC_enuErrorStatus;

typedef enum{
	HSI,
	HSE
}RCC_enuPLLSrc;

typedef struct{
	RCC_enuPLLSrc PLL_Src;
	u32           PLL_M ;
	u32           PLL_N ;
	u32           PLL_P ;
	u32           PLL_Q ;
}RCC_strClkPLL;

typedef enum{
	OFF,
	ON
}RCC_enuCLK_ON_OFF;

typedef enum{
	REDY,
	NOTREADY
}RCC_enuReadyStatus;
/* ==================================================================== */
/* ========================== Clock Types ============================= */
/* ==================================================================== */
#define RCC_HSI                 0
#define RCC_HSE                 1
#define RCC_PLL                 2

#define MASK_GET_RDY_HSI         0x00000002
#define MASK_GET_RDY_HSE         0x00020000
#define MASK_GET_RDY_PLL         0x02000000

#define MASK_GET_SYSCLK          0x0000000C

#define MASK_GET_ON_PLL          0x01000000

#define MASK_SET_PPL_M           0x0000003F
#define MASK_SET_PPL_N           0x00007FC0
#define MASK_SET_PPL_P           0x00030000
#define MASK_SET_PPL_Q           0x0F000000

#define MASK_SET_PPL_SRC         0x00400000

#define SHIFT_PLL_M              0
#define SHIFT_PLL_N              6
#define SHIFT_PLL_P              16
#define SHIFT_PLL_Q              24
#define SHIFT_PLL_SRC            22

#define  MASK_HSI_ON             0x00000001
#define  MASK_HSI_RDY            0x00000002
#define  MASK_HSE_ON             0x00010000
#define  MASK_HSE_RDY            0x00020000
#define  MASK_PLL_ON             0x01000000
#define  MASK_PLL_RDY            0x02000000

#define  MASK_SW                 0x00000003
#define  MASK_GET_SWS            0x0000000C

#define MASK_SWS_HSI 			 0x00000000
#define MASK_SWS_HSE 			 0x00000004
#define MASK_SWS_PLL 			 0x00000008

#define RCC_NOT_RDY_STATUS 		 0
#define RCC_RDY_STATUS 			 1

/*==============================AHB PRESCALER=========================*/
#define AHB_PRESCALE_NoDiv   0x00000000
#define AHB_PRESCALE_2       0X00000080
#define AHB_PRESCALE_4       0X00000090
#define AHB_PRESCALE_8       0X000000A0
#define AHB_PRESCALE_16      0X000000B0
#define AHB_PRESCALE_64      0X000000C0
#define AHB_PRESCALE_128     0X000000D0
#define AHB_PRESCALE_256     0X000000E0
#define AHB_PRESCALE_512     0X000000F0
#define AHB_CLEAN_PRE        0X000000F0
/*==============================APB1 PRESCALER=========================*/
#define APB1_PRESCALE_NoDiv  0x00000000
#define APB1_PRESCALE_2      0x00001000
#define APB1_PRESCALE_4      0x00001400
#define APB1_PRESCALE_8      0x00001800
#define APB1_PRESCALE_16     0x00001C00
#define APB1_CLEAN_PRE       0x00001C00
/*==============================APB2 PRESCALER=========================*/
#define AB2_PRESCALE_NoDiv   0x00000000
#define AB2_PRESCALE_2       0x00008000
#define APB2_PRESCALE_4      0x0000A000
#define APB2_PRESCALE_8      0x0000C000
#define APB2_PRESCALE_16     0x0000E000
#define APB2_CLEAN_PRE       0x0000E000


/* ================================ AHB1 ============================== */
#define GPIOA_RCC                       0
#define GPIOB_RCC                       1
#define GPIOC_RCC                       2
#define GPIOD_RCC                       3
#define GPIOE_RCC                       4
#define GPIOH_RCC                       7
#define CRC_RCC                         12
#define DMA1_RCC                        21
#define DMA2_RCC                        22

/* ================================ AHB2 ============================== */
#define OTGFS_RCC 7


/* ================================ APB1 ============================== */
#define TIM2_RCC                        0
#define TIM3_RCC                        1
#define TIM4_RCC                        2
#define TIM5_RCC                        3
#define WWDG_RCC                        11
#define SPI2_RCC                        14
#define SPI3_RCC                        15
#define USART2_RCC                      17
#define I2C1_RCC                        21
#define I2C2_RCC                        22
#define I2C3_RCC                        23
#define PWR_RCC                         28

/* ================================ APB2 ============================== */
#define TIM1_RCC                        0
#define USART1_RCC                      4
#define USART6_RCC                      5
#define ADC1_RCC                        8
#define SDIO_RCC                        11
#define SPI1_RCC                        12
#define SPI4_RCC                        13
#define SYSCFG_RCC                      14
#define TIM9_RCC                        16
#define TIM10_RCC                       17
#define TIM11_RCC                       18
/*************************************************************************/
#define AHB1_BUS                        0
#define AHB2_BUS                        1
#define APB1_BUS                        2
#define APB2_BUS                        3

/* ==================================================================================== */
/* ============================== RCC_enuSelectClk ==================================== */
/* @description :  select the clock of the system ======================================*/
/* @param       :        Copy_enuClk (RCC_CLK)             : RCC_HSI, RCC_HSE, RCC_PLL--*/
/* @return      :  error, choosing a wrong clock, or the clock isn't ready or on ,    --*/
/*                 or failed to set the clock as a system clock ------------------------*/
/* ==================================================================================== */
RCC_enuErrorStatus  RCC_enuSelectClk(u8 Copy_u8ClockSystem);

/* ==================================================================================== */
/* ============================== RCC_enuControlClk =================================== */
/* @description : control the clock on/off =============================================*/
/* @param       :        Copy_enuClk (RCC_CLK)               : RCC_HSI, RCC_HSE, RCC_PLL*/
/*                       Copy_enuClkStatus (RCC_enuClkStatus): ON, OFF                  */
/* @return      :  error, choosing a wrong clock, or the clock isn't ready or on ,      */
/*                 or failed to set the clock as a system clock ------------------------*/

RCC_enuErrorStatus RCC_enuControlClk(u8 Copy_u8ClockSystem,RCC_enuCLK_ON_OFF Copy_enuClkStatus);

/* ==================================================================================== */
/* ============================== RCC_enuCheckReady =================================== */
/* @description : check the clock ready/not ready ======================================*/
/* @param       :        Copy_enuClk (RCC_CLK)               : RCC_HSI, RCC_HSE, RCC_PLL*/
/*                       Add_enuReadyStatus (RCC_enuReadyStatus) ====================== */
/* @return      :  error, choosing a wrong clock, or the clock isn't ready or on ,      */
/*                 or failed to set the clock as a system clock ------------------------*/

RCC_enuErrorStatus RCC_enuCheckReady(u8 Copy_u8ClockSystem, u8* Add_pu8ReadyStatus);
/*
* @brief     :configure PLL parameters
* @param       : RCC_enuPLLSCR : HSI, HSE.
*                RCC_enuPLL_M : 2 : 63
*                RCC_enuPLL_N : 2 : 511
*                RCC_enuPLL_P : 2,4,6,8
*                RCC_enuPLL_Q : 2 : 15
* @return      :  error, choosing a wrong clock, or the clock isn't ready or on
*/

RCC_enuErrorStatus RCC_ConfigPLL(RCC_strClkPLL Copy_structPLLCongif);
/*
 * @brief     :configure APB1 prescaler
 * @parameters:0,2,4,8,16,64,128,256,512
 * @cautions  :The clocks are divided with the new prescaler factor from 1 to 16 AHB cycles after HPRE write
 * @return    :error (wrong choice)
 * */
RCC_enuErrorStatus  RCC_ControlPrescalerAHB(u32 Copy_u32AHBPrescaler);
/*
 * @brief     :configure APB1 prescaler
 * @parameters:0,2,4,8,16
 * !!!        :The software has to set these bits correctly not to exceed 42 MHz on this domain
 * @return    :error (wrong choice)
 * */
RCC_enuErrorStatus  RCC_ControlPrescalerAPB1(u32 Copy_u32APB1Prescaler);
/*
 * @brief     :configure APB2 prescaler
 * @parameters:0,2,4,8,16
 * !!!        :The software has to set these bits correctly not to exceed 84 MHz on this domain.
 * @return    :error (wrong choice)
 * */
RCC_enuErrorStatus  RCC_ControlPrescalerAPB2(u32 Copy_u32APB2Prescaler);
/*
 * @brief     : Enable the preipheral selected on the select bus
 * @parameters: AHB1, AHB2, APB1, APB2
 *            : Name of the peripheral
 *@return     : error (wrong input parameter)
 * */
RCC_enuErrorStatus  RCC_EnablePreipheral      (u32 Copy_u32PeripheralBus, u32 Copy_u32Peripheral);
/*
 * @brief     : Disable the preipheral selected on the select bus
 * @parameters: AHB1, AHB2, APB1, APB2
 *            : Name of the peripheral
 *@return     : error (wrong input parameter)
 * */
RCC_enuErrorStatus  RCC_DisablePreipheral     (u32 Copy_u32PeripheralBus, u32 Copy_u32Peripheral);

#endif
