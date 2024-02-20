#ifndef GPIO_H_
#define GPIO_H_

#include <LIB/std_types.h>


/*Reg Base Adress*/

#define GPIO_A_BASE 0x40020000
#define GPIO_B_BASE 0x40020400
#define GPIO_C_BASE 0x40020800
#define GPIO_D_BASE 0x40020C00
#define GPIO_E_BASE 0x40021000
#define GPIO_H_BASE 0x40021C00
/*Port options */
#define GPIOA  GPIO_A_BASE
#define GPIOB  GPIO_B_BASE
#define GPIOC  GPIO_C_BASE
#define GPIOD  GPIO_D_BASE
#define GPIOE  GPIO_E_BASE
#define GPIOH  GPIO_H_BASE
/*Pin_num options*/
#define GPIO_PIN_NO_0		0
#define GPIO_PIN_NO_1		1
#define GPIO_PIN_NO_2		2
#define GPIO_PIN_NO_3		3
#define GPIO_PIN_NO_4		4
#define GPIO_PIN_NO_5		5
#define GPIO_PIN_NO_6		6
#define GPIO_PIN_NO_7		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9		9
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_NO_15		15

/*GPIO input modes*/
#define GPIO_PIN_INPUT_MODE          0X00000000
#define GPIO_PIN_OUTPUT_MODE         0X00000001
#define GPIO_PIN_ALTFUNCTION_MODE    0X00000002
#define GPIO_PIN_ANALOG_MODE         0X00000003

/*GPIO OP type selection */

#define GPIO_PIN_Output_push_pull    0X00000000
#define GPIO_PIN_Output_open_drain   0X00000001

/*GPIO speed*/
#define GPIO_PINSPEED_LOW         0X00000000
#define GPIO_PINSPEED_MEDIUM      0X00000001
#define GPIO_PINSPEED_HIGH        0X00000002
#define GPIO_PINSPEED_VERYHIGH    0X00000003

/*GPIO pull up pull down */

#define GPIO_PIN_NOPUPD   0X00000000
#define GPIO_PIN_PU       0X00000001
#define GPIO_PIN_PD       0X00000002
/* AF options */
#define GPIO_ALTERNATIVE_SYSTEM		0x00
#define GPIO_ALTERNATIVE_TIM1		0x01
#define GPIO_ALTERNATIVE_TIM3		0x02
#define GPIO_ALTERNATIVE_TIM9		0x03
#define GPIO_ALTERNATIVE_I2C		0x04
#define GPIO_ALTERNATIVE_SPI		0x05
#define GPIO_ALTERNATIVE_SPI3		0x06
#define GPIO_ALTERNATIVE_USART1		0x07
#define GPIO_ALTERNATIVE_USART6		0x08
#define GPIO_ALTERNATIVE_SYSTEM		0x00
#define GPIO_ALTERNATIVE_SYSTEM		0x00
#define GPIO_ALTERNATIVE_SYSTEM		0x00
#define GPIO_ALTERNATIVE_SYSTEM		0x00
#define GPIO_ALTERNATIVE_SYSTEM		0x00
#define GPIO_ALTERNATIVE_SYSTEM		0x00

typedef struct{
u32 MODER;
u32 OTYPER;
u32 OSPEEDR;
u32 PUPDR;
u32 IDR;
u32 ODR;
u32 BSRR;
u32 LCKR;
u32 AFR[2];
}GPIO_strReg;

typedef struct{
	u32 Pin ;
	u32 mode ;
	u32 op_type ;
	u32 pull ;
	u32 speed ;
	u32 alternate;

}GPIO_strPinConfg;

/*
 */
void GPIO_Init(GPIO_strReg *GPIOx, GPIO_strPinConfg *PinConfg);
/*
 * @description : function to config Pin mode
 * @parm        : GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH
 *              : GPIO_PIN_NO(0->15)
 *              : input mode
 * @ret         : error state
 */
void GPIO_ConfgPinMode(GPIO_strReg *GPIOx, u16 Pin_num,u32 mode);
/*
 * @description : function to config Pin mode
 * @parm        : GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH
 *              : GPIO_PIN_NO(0->15)
 *              : output type
 * @ret         : error state
 */
void GPIO_ConfigPinOtype(GPIO_strReg *GPIOx, u16 Pin_num,u32 otype);
/*
 * @description : function to config Pin mode
 * @parm        : GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH
 *              : GPIO_PIN_NO(0->15)
 *              : speed
 * @ret         : error state
 */
void GPIO_ConfigPinSpeed(GPIO_strReg *GPIOx, u16 Pin_num,u32 Speed);
/*
 * @description : function to config Pin mode
 * @parm        : GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH
 *              : GPIO_PIN_NO(0->15)
 *              : Pu or PD
 * @ret         : error state
 */
void GPIO_ConfgPin_PUPD(GPIO_strReg *GPIOx, u16 Pin_num, u32 PUPD);
/*
 * @description : function to config Pin mode
 * @parm        : GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH
 *              : GPIO_PIN_NO(0->15)
 *              : Alt function
 * @ret         : error state
 */
void GPIO_SET_AltFun(GPIO_strReg *GPIOx, u16 Pin_num, u16 AltFunVal);
/*
 * @description : function to config Pin mode
 * @parm        : GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH
 *              : GPIO_PIN_NO(0->15)
 *              : 1 or 0 as pin val
 * @ret         : error state
 */
void GPIO_writePin(GPIO_strReg *GPIOx, u16 Pin_num, u8 PinVal);
/*
 * @description : function to config Pin mode
 * @parm        : GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH
 *              : GPIO_PIN_NO(0->15)
 *              : pointer to tha value to be read
 * @ret         : error state
 */
void GPIO_ReadPin(GPIO_strReg *GPIOx, u16 Pin_num, u8* ADDVal);








#endif
