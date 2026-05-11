/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    14/10/2022
  * @brief   Main program body.
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE IS FOR GUIDANCE ONLY. IT AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING MILANDR'S PRODUCTS IN ORDER TO FACILITATE
  * THE USE AND SAVE TIME. MILANDR SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES RESULTING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR A USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2022 Milandr</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01_port.h"
#include "MDR1986VK01_clk.h"
#include "MDR1986VK01_i2c.h"
#include "demoboard.h"
#include "dac.h"
#include "adc.h"
#include "i2c.h"
#include "arraymusic.h"

/** @addtogroup  __MDR1986VK01_StdPeriph_Examples MDR1986VK01 StdPeriph Examples
 *  @{
 */

/** @addtogroup __MDR1986VK01_EVALBOARD MDR1986VK01 Demo Board
 *  @{
 */

/** @addtogroup dac_music dac_music
 *  @{
 */
#define DAC_DATA_SIZE               512

uint32_t sizearraymusic;

void ClockInit()
{
    MDR_CLK->KEY = 0x8555AAA1;
    MDR_CLK->PER0_CLK =  0xFFFFFFFF;
    MDR_CLK->PER1_CLK =  0xFFFFFFFF;

    MDR_COMP0->ANABG_CTRL= ANABG_IREFEN | ANABG_BGEN | 
                     ANABG_BFEN( 0x3F ) | ANABG_SWMODE( 0x3F );
    
    MDR_BKP->KEY = 0x8555AAA1;

    CLK_XSEConfig( CLK_HSE0, CLK_XSE_ON );
    if( !CLK_XSEWaitReady( CLK_HSE0 ) )
        while(1){}

    CLK_SetPllClk( &MDR_CLK->PLL[2], PLL_CLK_HSE0, 100000000 ); // Frequency 100 MHz
    CLK_PllState( &MDR_CLK->PLL[2], ENABLE );
    if( !CLK_PLLWaitReady( &MDR_CLK->PLL[2] ) )
        while(1){}

    CLK_SetSystemClock( MAX_CLK_PLL2 );
}

static void vShifterInit( void )
{
    PORT_InitTypeDef ShifterPort;
    PORT_StructInit( &ShifterPort );
    MDR_PORTA->KEY = 0x8555AAA1;
    ShifterPort.PORT_Pin     = PORT_Pin_31;
    ShifterPort.PORT_SOE     = PORT_SOE_OUT;
    ShifterPort.PORT_SFUNC   = PORT_SFUNC_PORT;
    ShifterPort.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    ShifterPort.PORT_SPWR    = PORT_SPWR_10;
    PORT_Init( MDR_PORTA, &ShifterPort );
    BUF_OE_OFF;
}

int main()
{
		uint8_t EnChannels[1] = 0xC0; // Data for Enable Right and Left channels Amp
		uint8_t Volume[1] =0x3F; // Data for settings volume
	  uint16_t i;

		sizearraymusic = sizeof(arraymusic); // Calculation size music array
	
    ClockInit();
    
    vShifterInit();
  
		GenSin();
	  InitI2c(400000); // Frequency I2C 400 kHz
    InitDac( 22050 ); // Frequency DAC Sample Rate 22100 Hz
    
		I2C_Mem_Write(96, 1, 8, EnChannels, 1); // Write for address 96 Register 1 Amp
		I2C_Mem_Write(96, 2, 8, Volume, 1); // Write for address 96 Register 2 Amp


    while(1)
    {
    static uint32_t i = 0;
    static uint32_t j = 0;

		while( ! ( MDR_DAC1->STS & ( 1 << 3 ) ) )
		{
				MDR_DAC1->DATA = arraymusic[ i++ ]; // Play Left Channel

				if( i == sizearraymusic )
						i = 0;
		}

    while( ! ( MDR_DAC2->STS & ( 1 << 3 ) ) )
    {
        MDR_DAC2->DATA = arraymusic[ j++ ]; // Play Right Channel

        if( j == sizearraymusic )
            j = 0;
    }
    }
    
}

/** @} */ /* End of group dac_music */

/** @} */ /* End of group __MDR1986VK01_EVALBOARD */

/** @} */ /* End of group __MDR1986VK01_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2022 Milandr *********/

/* END OF FILE main.c */



