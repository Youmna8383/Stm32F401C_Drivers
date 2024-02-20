/*
 * RCC.c
 *
 *  Created on: Feb 12, 2024
 *      Author: Youmna
 */
#include <MCAL/RCC/RCC.h>

/*RCC Registers */
typedef struct
{
	volatile u32 RCC_CR;
	volatile u32 RCC_PLLCFGR;
	volatile u32 RCC_CFGR;
	volatile u32 RCC_CIR;
	volatile u32 RCC_AHB1RSTR;
	volatile u32 RCC_AHB2RSTR;
	volatile u32 RESERVED[2];
	volatile u32 RCC_APB1RSTR;
	volatile u32 RCC_APB2RSTR;
	volatile u32 RESERVED1[2];
	volatile u32 RCC_AHB1ENR;
	volatile u32 RCC_AHB2ENR;
	volatile u32 RESERVED2[2];
	volatile u32 RCC_APB1ENR;
	volatile u32 RCC_APB2ENR;
	volatile u32 RESERVED3[2];
	volatile u32 RCC_AHB1LPENR;
	volatile u32 RCC_AHB2LPENR;
	volatile u32 RESERVED4[2];
	volatile u32 RCC_APB1LPENR;
	volatile u32 RCC_APB2LPENR;
	volatile u32 RESERVED5[2];
	volatile u32 RCC_BDCR;
	volatile u32 RCC_CSR;
	volatile u32 RESERVED6[2];
	volatile u32 RCC_SSCGR;
	volatile u32 RCC_PLLI2SCFGR;
	volatile u32 RESERVED7;
	volatile u32 RCC_DCKCFGR;


}RCC_tstrReg;


/*RCC base address */
#define RCC_u32BASED_ADDRESS 0x40023800

/*RCC is a pointer of type RCC_tstrReg to map the real Registers in the memory*/
#define RCC		((RCC_tstrReg* )(RCC_u32BASED_ADDRESS))

/*******************************************************************************************/
/* ==================================================================================== */
/* ============================== RCC_enuSelectClk ==================================== */
/* @description :  select the clock of the system ======================================*/
/* @param       :        Copy_enuClk (RCC_CLK)             : RCC_HSI, RCC_HSE, RCC_PLL--*/
/* @return      :  error, choosing a wrong clock, or the clock isn't ready or on ,    --*/
/*                 or failed to set the clock as a system clock ------------------------*/
/* ==================================================================================== */
RCC_enuErrorStatus  RCC_enuSelectClk(u8 Copy_u8ClockSystem){
  RCC_enuErrorStatus Ret_enuSystemCLOCK = RCC_enuOK;
  u32 Loc_u32CFGR_Register;
  u32 Loc_u32TimeOut = 0;

  /* CHECKING ERROR : RIGHT CLOCK */
  if(Copy_u8ClockSystem >= RCC_HSI && Copy_u8ClockSystem <= RCC_PLL){

    switch(Copy_u8ClockSystem){

       case RCC_HSI:{

    	   /* CHECK ON */
           if( ((RCC->RCC_CR & MASK_HSI_ON) == MASK_HSI_ON) ){

        	    /* CHECK READY FLAG */
                if((RCC->RCC_CR & MASK_HSI_RDY) == MASK_HSI_RDY){

					/* SET SW */
					Loc_u32CFGR_Register  = RCC->RCC_CFGR;
					Loc_u32CFGR_Register &= ~MASK_SW;
					Loc_u32CFGR_Register |= (RCC_HSI<<0);
					RCC->RCC_CFGR = Loc_u32CFGR_Register;

					while( ((RCC->RCC_CFGR & MASK_GET_SWS) != MASK_SWS_HSI) && (Loc_u32TimeOut<100000)){
						Loc_u32TimeOut++;
					}
					if( Loc_u32TimeOut >= 100000 ){
						/* TIMEOUT */
						Ret_enuSystemCLOCK = RCC_enuNotOK;
					}
                }

                /* ERROR : NOT READY */
                else{
                	Ret_enuSystemCLOCK = RCC_enuNotOK;
                }
            }
            /* CLOCK OFF */
            else{
                Ret_enuSystemCLOCK = RCC_enuNotOK;
            }

            break;
        }
        case RCC_HSE:

        /* CHECK ON */
        if((RCC->RCC_CR & MASK_HSE_ON) == MASK_HSE_ON){

          /* CHECK READY FLAG */
          if((RCC->RCC_CR & MASK_HSE_RDY) == MASK_HSE_RDY){

            /* SET SW */
            Loc_u32CFGR_Register  = RCC->RCC_CFGR;
            Loc_u32CFGR_Register &= ~MASK_SW;
            Loc_u32CFGR_Register |= (RCC_HSE<<0);
            RCC->RCC_CFGR = Loc_u32CFGR_Register;

            while(( (RCC->RCC_CFGR & MASK_SWS_HSE)!=MASK_SWS_HSE) && (Loc_u32TimeOut<100000)){
              Loc_u32TimeOut++;
            }
            if( Loc_u32TimeOut >= 100000 ){

              /* TIMEOUT */
              Ret_enuSystemCLOCK = RCC_enuNotOK;
            }
          }

          /* ERROR : NOT READY */
          else{
            Ret_enuSystemCLOCK = RCC_enuNotOK;
          }
        }

        /* CLOCK OFF */
        else{
          Ret_enuSystemCLOCK = RCC_enuNotOK;
        }

      break;

      case RCC_PLL:

        /* CHECK ON */
        if((RCC->RCC_CR & MASK_PLL_ON) == MASK_PLL_ON){

          /* CHECK READY FLAG */
          if((RCC->RCC_CR & MASK_PLL_RDY) == MASK_PLL_RDY){

            /* SET SW */
            Loc_u32CFGR_Register  = RCC->RCC_CFGR;
            Loc_u32CFGR_Register &= ~MASK_SW;
            Loc_u32CFGR_Register |= (RCC_PLL<<0);
            RCC->RCC_CFGR = Loc_u32CFGR_Register;

            while(( (RCC->RCC_CFGR & MASK_GET_SWS) !=MASK_SWS_PLL) && (Loc_u32TimeOut<100000)){
              Loc_u32TimeOut++;
            }
            if( Loc_u32TimeOut >= 100000 ){

              /* TIMEOUT */
              Ret_enuSystemCLOCK = RCC_enuNotOK;
            }
            else{
              /* DO NOTHING */
            }
          }
          /* ERROR : NOT READY */
          else{
            Ret_enuSystemCLOCK = RCC_enuNotOK;
          }
        }
        /* CLOCK OFF */
        else{
          Ret_enuSystemCLOCK = RCC_enuNotOK;
        }

      break;
    };

  }

  /* ERROR : NOT VALID CLOCK */
  else{
    Ret_enuSystemCLOCK = RCC_enuNotOK;
  }

  return Ret_enuSystemCLOCK;
}

/* ==================================================================================== */
/* ============================== RCC_enuControlClk =================================== */
/* @description : control the clock on/off =============================================*/
/* @param       :        Copy_enuClk (RCC_CLK)               : RCC_HSI, RCC_HSE, RCC_PLL*/
/*                       Copy_enuClkStatus (RCC_enuClkStatus): ON, OFF                  */
/* @return      :  error, choosing a wrong clock, or the clock isn't ready or on ,      */
/*                 or failed to set the clock as a system clock ------------------------*/
/* ==================================================================================== */
RCC_enuErrorStatus  RCC_enuControlClk(u8 Copy_u8ClockSystem,RCC_enuCLK_ON_OFF Copy_enuClkStatus){
  u32 Loc_u32SystemCLOCK = ((RCC->RCC_CFGR & MASK_GET_SYSCLK)>>2);
  RCC_enuErrorStatus Ret_enuSystemCLOCK = RCC_enuOK;
  u32 Loc_u32TimeOut = 0;

  /* ERROR : CHANGING ON THE SYSTEM CLOCK */
  if(Loc_u32SystemCLOCK == Copy_u8ClockSystem){
    Ret_enuSystemCLOCK = RCC_enuNotOK;
  }

  /* ERROR : CHOOSING WRONG CLOCK */
  else if(!(Copy_u8ClockSystem >= RCC_HSI) &&  (Copy_u8ClockSystem <= RCC_PLL)){
    Ret_enuSystemCLOCK = RCC_enuNotOK;
  }

  else{
      switch(Copy_u8ClockSystem){

        /* CONTROL HSI CLK ON/OFF */
        case RCC_HSI:

          /* HSI : OFF */
          if(Copy_enuClkStatus == OFF){
        	  RCC->RCC_CR &= (~MASK_HSI_ON);
          }

          /* HSI : ON */
          else{
        	  RCC->RCC_CR |= (MASK_HSI_ON);

				/* WAIT TILL READY */
				while( ((RCC->RCC_CR & MASK_HSI_RDY) == 0) && (Loc_u32TimeOut<100000)){
					Loc_u32TimeOut++;
				}
				if( Loc_u32TimeOut >= 100000 ){

					/* TIMEOUT */
					Ret_enuSystemCLOCK = RCC_enuNotOK;
				}
          }
        break;

        /* CONTROL HSE CLK ON/OFF */
        case RCC_HSE:

          /* HSE : OFF */
          if(Copy_enuClkStatus == OFF){
        	  RCC->RCC_CR &= (~MASK_HSE_ON);
          }

          /* HSE : ON */
          else{
        	  RCC->RCC_CR |= (MASK_HSE_ON);

			   /* WAIT TILL READY */
			   while( ((RCC->RCC_CR & MASK_HSE_RDY) == 0) && (Loc_u32TimeOut<100000)){
				   Loc_u32TimeOut++;
			   }
			   if( Loc_u32TimeOut >= 100000 ){

				   /* TIMEOUT */
				   Ret_enuSystemCLOCK = RCC_enuNotOK;
			   }
		 }
        break;

        /* CONTROL PLL CLK ON/OFF */
        case RCC_PLL:

          /* PLL : OFF */
          if(Copy_enuClkStatus == OFF){
        	  RCC->RCC_CR &= (~MASK_PLL_ON);
          }

          /* PLL : ON */
          else{

        	/* SET PLL ON */
        	  RCC->RCC_CR |= (MASK_PLL_ON);

            /* WAIT TILL READY */
            while( (( RCC->RCC_CR & MASK_PLL_RDY) == 0) && (Loc_u32TimeOut<100000)){
				Loc_u32TimeOut++;
			}
			if( Loc_u32TimeOut >= 100000 ){

				/* TIMEOUT */
				Ret_enuSystemCLOCK = RCC_enuNotOK;
			}
          }
        break;
      };
  }

  return Ret_enuSystemCLOCK;
}

RCC_enuErrorStatus  RCC_enuCheckReady(u8 Copy_u8ClockSystem, u8* Add_pu8ReadyStatus){
  RCC_enuErrorStatus Ret_enuSystemCLOCK = RCC_enuOK;


  if((Copy_u8ClockSystem >= RCC_HSI) && (Copy_u8ClockSystem <= RCC_PLL)){

      switch(Copy_u8ClockSystem){

        /* GET HSI CLK READY/NOT_READY */
        case RCC_HSI:
          if((RCC->RCC_CR & MASK_GET_RDY_HSI) == MASK_GET_RDY_HSI){
            *Add_pu8ReadyStatus = RCC_RDY_STATUS;
          }
          else{
            *Add_pu8ReadyStatus = RCC_NOT_RDY_STATUS;
          }
        break;

        /* GET HSE CLK READY/NOT_READY */
        case RCC_HSE:
          if((RCC->RCC_CR & MASK_GET_RDY_HSE) ==MASK_GET_RDY_HSE){
            *Add_pu8ReadyStatus = RCC_RDY_STATUS;
          }
          else{
            *Add_pu8ReadyStatus = RCC_NOT_RDY_STATUS;
          }
        break;

        /* GET PLL CLK READY/NOT_READY */
        case RCC_PLL:
          if((RCC->RCC_CR & MASK_GET_RDY_PLL) == MASK_GET_RDY_PLL){
            *Add_pu8ReadyStatus = RCC_RDY_STATUS;
          }
          else{
            *Add_pu8ReadyStatus = RCC_NOT_RDY_STATUS;
          }

        break;
      };
  }

  /* ERROR : CLOCK IS NOT TRUE */
  else{
      Ret_enuSystemCLOCK = RCC_enuNotOK;
  }

  return Ret_enuSystemCLOCK;
}
/*
* @brief     :configure PLL parameters
* @param       : RCC_enuPLLSCR : HSI, HSE.
*                RCC_enuPLL_M : 2 : 63
*                RCC_enuPLL_N : 2 : 511
*                RCC_enuPLL_P : 2,4,6,8
*                RCC_enuPLL_Q : 2 : 15
* @return      :  error, choosing a wrong clock, or the clock isn't ready or on
*/

RCC_enuErrorStatus RCC_ConfigPLL(RCC_strClkPLL Copy_structPLLConfig){

	RCC_enuErrorStatus Ret_enuErrorStatus = RCC_enuOK;

	RCC_enuPLLSrc Loc_enuPLLSource = Copy_structPLLConfig.PLL_Src;

	  u32 Loc_u32PLL_M = Copy_structPLLConfig.PLL_M;
	  u32 Loc_u32PLL_N = Copy_structPLLConfig.PLL_N;
	  u32 Loc_u32PLL_P = Copy_structPLLConfig.PLL_P;
	  u32 Loc_u32PLL_Q = Copy_structPLLConfig.PLL_Q;

	  u32 Loc_u32PLLCFGR_Register;

	  /* CHECKING ERROR : M CONFIGURATION */
	  if(Loc_u32PLL_M == 0 || Loc_u32PLL_M == 1 || Loc_u32PLL_M > 63){
		  Ret_enuErrorStatus = RCC_enuNotOK;
	  }

	  /* CHECKING ERROR : N CONFIGURATION */
	  else if(Loc_u32PLL_N == 0 || Loc_u32PLL_N == 1 || Loc_u32PLL_N == 433 || Loc_u32PLL_N >= 511){
		  Ret_enuErrorStatus = RCC_enuNotOK;
	  }

	  /* CHECKING ERROR : P CONFIGURATION */
	  else if((Loc_u32PLL_P != 2) && (Loc_u32PLL_P != 4) && (Loc_u32PLL_P != 6) && (Loc_u32PLL_P != 8)){
		  Ret_enuErrorStatus = RCC_enuNotOK;
	  }

	  /* CHECKING ERROR : Q CONFIGURATION */
	  else if(Loc_u32PLL_Q == 0 || Loc_u32PLL_Q == 1 || Loc_u32PLL_Q > 15){
		  Ret_enuErrorStatus = RCC_enuNotOK;
	  }
	  /* CHECKING ERROR : CLOCK SOURCE */
	   else if(Loc_enuPLLSource>HSE){
		   Ret_enuErrorStatus = RCC_enuNotOK;
	   }

	   /* CHICKING ERROR : PLL ON */
	   else if((RCC->RCC_CR&MASK_GET_ON_PLL) != OFF){
		   Ret_enuErrorStatus = RCC_enuNotOK;
	   }
	   else {
		   /*** CONFIGURE THE PPL ***/
		     /* 1: CONFIGURE M */
		     Loc_u32PLLCFGR_Register = RCC->RCC_PLLCFGR;
		     Loc_u32PLLCFGR_Register &= ~MASK_SET_PPL_M;
		     Loc_u32PLLCFGR_Register |= (Loc_u32PLL_M<<SHIFT_PLL_M);
		     RCC->RCC_PLLCFGR = Loc_u32PLLCFGR_Register;

		     /* 2: CONFIGURE N */
		     Loc_u32PLLCFGR_Register = RCC->RCC_PLLCFGR;
		     Loc_u32PLLCFGR_Register &= ~MASK_SET_PPL_N;
		     Loc_u32PLLCFGR_Register |= (Loc_u32PLL_N<<SHIFT_PLL_N);
		     RCC->RCC_PLLCFGR = Loc_u32PLLCFGR_Register;

		     /* 3: CONFIGURE P */
		     Loc_u32PLLCFGR_Register = RCC->RCC_PLLCFGR;
		     Loc_u32PLLCFGR_Register &= ~MASK_SET_PPL_P;
		     Loc_u32PLLCFGR_Register |= (Loc_u32PLL_P<<SHIFT_PLL_P);
		     RCC->RCC_PLLCFGR = Loc_u32PLLCFGR_Register;

		     /* 4: CONFIGURE Q */
		     Loc_u32PLLCFGR_Register = RCC->RCC_PLLCFGR;
		     Loc_u32PLLCFGR_Register &= ~ MASK_SET_PPL_Q;
		     Loc_u32PLLCFGR_Register |= (Loc_u32PLL_Q<<SHIFT_PLL_Q);
		     RCC->RCC_PLLCFGR = Loc_u32PLLCFGR_Register;

		     /* 5: CONFIGURE CLOCK SOURCE */
		     Loc_u32PLLCFGR_Register = RCC->RCC_PLLCFGR;
		     Loc_u32PLLCFGR_Register &= ~MASK_SET_PPL_SRC;
		     Loc_u32PLLCFGR_Register |= (Loc_enuPLLSource<<SHIFT_PLL_SRC);
		     RCC->RCC_PLLCFGR = Loc_u32PLLCFGR_Register;
		   }



	return Ret_enuErrorStatus;
}
/*
 * @brief     :configure APB1 prescaler
 * @parameters:0,2,4,8,16,64,128,256,512
 * @cautions  :The clocks are divided with the new prescaler factor from 1 to 16 AHB cycles after HPRE write
 * @return    :error (wrong choice)
 * */
RCC_enuErrorStatus  RCC_ControlPrescalerAHB(u32 Copy_u32AHBPrescaler){
	RCC_enuErrorStatus Ret_enuErrorStatus = RCC_enuOK;
	u32 Loc_CFGR_Reg;
	switch(Copy_u32AHBPrescaler){
	case AHB_PRESCALE_NoDiv:
		Loc_CFGR_Reg = RCC->RCC_CFGR;
		Loc_CFGR_Reg &= (~(AHB_CLEAN_PRE));
		Loc_CFGR_Reg |= AHB_PRESCALE_NoDiv;
		RCC->RCC_CFGR = Loc_CFGR_Reg;
		break;
	case AHB_PRESCALE_2:
		        Loc_CFGR_Reg = RCC->RCC_CFGR;
				Loc_CFGR_Reg &= (~(AHB_CLEAN_PRE));
				Loc_CFGR_Reg |= AHB_PRESCALE_2;
				RCC->RCC_CFGR = Loc_CFGR_Reg;
				break;
	case AHB_PRESCALE_4:
		                Loc_CFGR_Reg = RCC->RCC_CFGR;
						Loc_CFGR_Reg &= (~(AHB_CLEAN_PRE));
						Loc_CFGR_Reg |= AHB_PRESCALE_4;
						RCC->RCC_CFGR = Loc_CFGR_Reg;
						break;
	case AHB_PRESCALE_8:
			                Loc_CFGR_Reg = RCC->RCC_CFGR;
							Loc_CFGR_Reg &= (~(AHB_CLEAN_PRE));
							Loc_CFGR_Reg |= AHB_PRESCALE_8;
							RCC->RCC_CFGR = Loc_CFGR_Reg;
							break;
	case AHB_PRESCALE_16:
				                Loc_CFGR_Reg = RCC->RCC_CFGR;
								Loc_CFGR_Reg &= (~(AHB_CLEAN_PRE));
								Loc_CFGR_Reg |= AHB_PRESCALE_16;
								RCC->RCC_CFGR = Loc_CFGR_Reg;
								break;
	case AHB_PRESCALE_64:
					                Loc_CFGR_Reg = RCC->RCC_CFGR;
									Loc_CFGR_Reg &= (~(AHB_CLEAN_PRE));
									Loc_CFGR_Reg |= AHB_PRESCALE_64;
									RCC->RCC_CFGR = Loc_CFGR_Reg;
									break;
	case AHB_PRESCALE_128:
						                Loc_CFGR_Reg = RCC->RCC_CFGR;
										Loc_CFGR_Reg &= (~(AHB_CLEAN_PRE));
										Loc_CFGR_Reg |= AHB_PRESCALE_128;
										RCC->RCC_CFGR = Loc_CFGR_Reg;
										break;
	case AHB_PRESCALE_256:
							                Loc_CFGR_Reg = RCC->RCC_CFGR;
											Loc_CFGR_Reg &= (~(AHB_CLEAN_PRE));
											Loc_CFGR_Reg |= AHB_PRESCALE_256;
											RCC->RCC_CFGR = Loc_CFGR_Reg;
											break;
	case AHB_PRESCALE_512:
								                Loc_CFGR_Reg = RCC->RCC_CFGR;
												Loc_CFGR_Reg &= (~(AHB_CLEAN_PRE));
												Loc_CFGR_Reg |= AHB_PRESCALE_512;
												RCC->RCC_CFGR = Loc_CFGR_Reg;
												break;
	default:
			Ret_enuErrorStatus =   RCC_enuNotOK;
			break;

	}
	return Ret_enuErrorStatus;
}
/*
 * @brief     :configure APB1 prescaler
 * @parameters:0,2,4,8,16
 * !!!        :The software has to set these bits correctly not to exceed 42 MHz on this domain
 * @return    :error (wrong choice)
 * */
RCC_enuErrorStatus  RCC_ControlPrescalerAPB1(u32 Copy_u32APB1Prescaler){
	RCC_enuErrorStatus Ret_enuErrorStatus = RCC_enuOK;
	u32 Loc_CFGR_Reg;
	switch(Copy_u32APB1Prescaler){
	case APB1_PRESCALE_NoDiv:
		Loc_CFGR_Reg = RCC->RCC_CFGR;
		Loc_CFGR_Reg &= (~(APB1_CLEAN_PRE));
		Loc_CFGR_Reg |= APB1_PRESCALE_NoDiv;
		RCC->RCC_CFGR = Loc_CFGR_Reg;
		break;
	case APB1_PRESCALE_2:
			Loc_CFGR_Reg = RCC->RCC_CFGR;
			Loc_CFGR_Reg &= (~(APB1_CLEAN_PRE));
			Loc_CFGR_Reg |= APB1_PRESCALE_2;
			RCC->RCC_CFGR = Loc_CFGR_Reg;
			break;
	case APB1_PRESCALE_4:
				Loc_CFGR_Reg = RCC->RCC_CFGR;
				Loc_CFGR_Reg &= (~(APB1_CLEAN_PRE));
				Loc_CFGR_Reg |= APB1_PRESCALE_4;
				RCC->RCC_CFGR = Loc_CFGR_Reg;
				break;
	case APB1_PRESCALE_8:
					Loc_CFGR_Reg = RCC->RCC_CFGR;
					Loc_CFGR_Reg &= (~(APB1_CLEAN_PRE));
					Loc_CFGR_Reg |= APB1_PRESCALE_8;
					RCC->RCC_CFGR = Loc_CFGR_Reg;
					break;
	case APB1_PRESCALE_16:
						Loc_CFGR_Reg = RCC->RCC_CFGR;
						Loc_CFGR_Reg &= (~(APB1_CLEAN_PRE));
						Loc_CFGR_Reg |= APB1_PRESCALE_16;
						RCC->RCC_CFGR = Loc_CFGR_Reg;
						break;
	default:
		Ret_enuErrorStatus =   RCC_enuNotOK;
		break;


	}
	return Ret_enuErrorStatus;
}
/*
 * @brief     :configure APB2 prescaler
 * @parameters:0,2,4,8,16
 * !!!        :The software has to set these bits correctly not to exceed 84 MHz on this domain.
 * @return    :error (wrong choice)
 * */
RCC_enuErrorStatus  RCC_ControlPrescalerAPB2(u32 Copy_u32APB2Prescaler){

	RCC_enuErrorStatus Ret_enuErrorStatus = RCC_enuOK;
	u32 Loc_CFGR_REG;
	switch(Copy_u32APB2Prescaler){
	case AB2_PRESCALE_NoDiv:

		Loc_CFGR_REG = RCC->RCC_CFGR;
		Loc_CFGR_REG &= (~(APB2_CLEAN_PRE));
		Loc_CFGR_REG |=  AB2_PRESCALE_NoDiv;
		RCC->RCC_CFGR =Loc_CFGR_REG;
		break;
	case AB2_PRESCALE_2:
		Loc_CFGR_REG = RCC->RCC_CFGR;
				Loc_CFGR_REG &= (~(APB2_CLEAN_PRE));
				Loc_CFGR_REG |=  AB2_PRESCALE_2;
				RCC->RCC_CFGR =Loc_CFGR_REG;

				break;
	case APB2_PRESCALE_4:
			Loc_CFGR_REG = RCC->RCC_CFGR;
					Loc_CFGR_REG &= (~(APB2_CLEAN_PRE));
					Loc_CFGR_REG |=  APB2_PRESCALE_4;
					RCC->RCC_CFGR =Loc_CFGR_REG;

					break;
	case APB2_PRESCALE_8:
				Loc_CFGR_REG = RCC->RCC_CFGR;
						Loc_CFGR_REG &= (~(APB2_CLEAN_PRE));
						Loc_CFGR_REG |=  APB2_PRESCALE_8;
						RCC->RCC_CFGR =Loc_CFGR_REG;

						break;
	case APB2_PRESCALE_16:
					Loc_CFGR_REG = RCC->RCC_CFGR;
							Loc_CFGR_REG &= (~(APB2_CLEAN_PRE));
							Loc_CFGR_REG |=  APB2_PRESCALE_16;
							RCC->RCC_CFGR =Loc_CFGR_REG;

							break;
	default:
		Ret_enuErrorStatus =   RCC_enuNotOK;
		break;


	}
return Ret_enuErrorStatus;
}
/*
 * @brief     : Enable the preipheral selected on the select bus
 * @parameters: AHB1, AHB2, APB1, APB2
 *            : Name of the peripheral
 *@return     : error (wrong input parameter)
 * */
RCC_enuErrorStatus  RCC_EnablePreipheral      (u32 Copy_u32PeripheralBus, u32 Copy_u32Peripheral){
	RCC_enuErrorStatus Ret_enuErrorStatus = RCC_enuOK;
	switch (Copy_u32PeripheralBus){

	case AHB1_BUS:
		RCC->RCC_AHB1ENR |=(1<<Copy_u32Peripheral);
		break;
	case AHB2_BUS:
		RCC->RCC_AHB2ENR |=(1<<Copy_u32Peripheral);
		break;
	case APB1_BUS:
		RCC->RCC_APB1ENR |=(1<<Copy_u32Peripheral);
		break;
	case APB2_BUS:
		RCC->RCC_APB2ENR |=(1<<Copy_u32Peripheral);
		break;
	 default:
	      Ret_enuErrorStatus =   RCC_enuNotOK;
	    break;



	}
	 return Ret_enuErrorStatus;
}
/*
 * @brief     : Disable the preipheral selected on the select bus
 * @parameters: AHB1, AHB2, APB1, APB2
 *            : Name of the peripheral
 *@return     : error (wrong input parameter)
 * */
RCC_enuErrorStatus  RCC_DisablePreipheral     (u32 Copy_u32PeripheralBus, u32 Copy_u32Peripheral){

	RCC_enuErrorStatus Ret_enuErrorStatus = RCC_enuOK;

	switch(Copy_u32PeripheralBus){
	case AHB1_BUS:
		RCC->RCC_AHB1ENR &=(~(1<< Copy_u32Peripheral));
		break;
	case AHB2_BUS:
		RCC->RCC_AHB2ENR &=(~(1<< Copy_u32Peripheral));
		break;
	case APB1_BUS:
		RCC->RCC_APB1ENR &=(~(1<< Copy_u32Peripheral));
		break;
	case APB2_BUS:
		RCC->RCC_APB2ENR &=(~(1<< Copy_u32Peripheral));
		break;
	default:
		Ret_enuErrorStatus= RCC_enuNotOK;
	}
	return Ret_enuErrorStatus;
}
