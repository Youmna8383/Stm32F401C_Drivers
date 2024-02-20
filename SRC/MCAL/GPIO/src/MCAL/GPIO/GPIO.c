/*
 * GPIO.c
 *
 *  Created on: Feb 18, 2024
 *      Author: Youmna
 */

#include<MCAL/GPIO/GPIO.h>

/*
 * @description : function to config Pin mode
 * @parm        : GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH
 *              : GPIO_PIN_NO(0->15)
 *              : input mode
 * @ret         : error state
 */
void GPIO_ConfgPinMode(GPIO_strReg *GPIOx, u16 Pin_num,u32 mode){
	GPIOx->MODER |= (mode<<(2*Pin_num));
}

/*
 * @description : function to config Pin mode
 * @parm        : GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH
 *              : GPIO_PIN_NO(0->15)
 *              : output type
 * @ret         : error state
 */

void GPIO_ConfigPinOtype(GPIO_strReg *GPIOx, u16 Pin_num,u32 otype){
	GPIOx->OTYPER |= (otype<<(Pin_num));
}

/*
 * @description : function to config Pin mode
 * @parm        : GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH
 *              : GPIO_PIN_NO(0->15)
 *              : speed
 * @ret         : error state
 */

void GPIO_ConfigPinSpeed(GPIO_strReg *GPIOx, u16 Pin_num,u32 Speed){
	GPIOx->OSPEEDR |= (Speed<<(2*Pin_num));
}

/*
 * @description : function to config Pin mode
 * @parm        : GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH
 *              : GPIO_PIN_NO(0->15)
 *              : Pu or PD
 * @ret         : error state
 */

void GPIO_ConfgPin_PUPD(GPIO_strReg *GPIOx, u16 Pin_num, u32 PUPD){
	GPIOx->PUPDR |= (PUPD<<(2*Pin_num));
}

/*
 * @description : function to config Pin mode
 * @parm        : GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH
 *              : GPIO_PIN_NO(0->15)
 *              : Alt function
 * @ret         : error state
 */

void GPIO_SET_AltFun(GPIO_strReg *GPIOx, u16 Pin_num, u16 AltFunVal){
if(Pin_num<=7)
{
	GPIOx->AFR[0]|=(AltFunVal<<(4*Pin_num));
}
else
{
	GPIOx->AFR[1]|=(AltFunVal<<((Pin_num %8) * 4));
}
}

/*
 * @description : function to config Pin mode
 * @parm        : GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH
 *              : GPIO_PIN_NO(0->15)
 *              : 1 or 0 as pin val
 * @ret         : error state
 */

void GPIO_writePin(GPIO_strReg *GPIOx, u16 Pin_num, u8 PinVal){
if (PinVal)
{
	GPIOx->ODR |=(PinVal<<Pin_num);
}
else
{
	GPIOx->ODR &= ~((PinVal<<Pin_num));
}
}

/*
 * @description : function to config Pin mode
 * @parm        : GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH
 *              : GPIO_PIN_NO(0->15)
 *              : pointer to tha value to be read
 * @ret         : error state
 */
void GPIO_ReadPin(GPIO_strReg *GPIOx, u16 Pin_num, u8* ADDVal){
	*ADDVal= ((GPIOx->IDR>>Pin_num) & 0x00000001);
}

