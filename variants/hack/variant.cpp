/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.
  Copyright (c) 2016 Michele Perla.  All right reserved.
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
/*
 * +------------+------------------+--------+-----------------+-------------------------------------------------------------------------------------------------------------------
 * + Pin number +  HACK Board pin  |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+-------------------------------------------------------------------------------------------------------------------
 * |            | GPIO/USART       |        |                 |
 * +------------+------------------+--------+-----------------+-------------------------------------------------------------------------------------------------------------------
 * | 0          | 0                |  PA08  | RX              | EIC/NMI        ADC/AIN[16]           PTC/X[0] *SERCOM0/PAD[0]  SERCOM2/PAD[0]  TCC0/WO[0]  TCC1/WO[2]  I2S/SD[1]
 * | 1          | 1                |  PA09  | TX              | EIC/EXTINT[9]  ADC/AIN[17]           PTC/X[1] *SERCOM0/PAD[1]  SERCOM2/PAD[1]  TCC0/WO[1]  TCC1/WO[3]  I2S/MCK[0]
 * +------------+------------------+--------+-----------------+-------------------------------------------------------------------------------------------------------------------
 * |            | GPIO             |        |                 |
 * +------------+------------------+--------+-----------------+-------------------------------------------------------------------------------------------------------------------
 * | 2          | ~2               |  PA10  |                 | EIC/EXTINT[10] ADC/AIN[18]           PTC/X[2]  SERCOM0/PAD[2]  SERCOM2/PAD[2]  TCC1/WO[0] *TCC0/WO[2]  I2S/SCK[0]
 * | 3          | ~3               |  PA11  |                 | EIC/EXTINT[11] ADC/AIN[19]           PTC/X[3]  SERCOM0/PAD[3]  SERCOM2/PAD[3]  TCC1/WO[1] *TCC0/WO[3]  I2S/FS[0]
 * | 4          | ~4               |  PA14  |                 | EIC/EXTINT[14]                                 SERCOM2/PAD[2]  SERCOM4/PAD[2]  TC3/WO[0]  *TCC0/WO[4]
 * | 5          | ~5               |  PA15  |                 | EIC/EXTINT[15]                                 SERCOM2/PAD[3]  SERCOM4/PAD[3]  TC3/WO[1]  *TCC0/WO[5]
 * +------------+------------------+--------+-----------------+-------------------------------------------------------------------------------------------------------------------
 * |            | GPIO/SPI         |        |                 |
 * +------------+------------------+--------+-----------------+-------------------------------------------------------------------------------------------------------------------
 * | 6          | ~6               |  PA16  | MISO            | EIC/EXTINT[0]                        PTC/X[4]  SERCOM1/PAD[0]  SERCOM3/PAD[0] *TCC2/WO[0]  TCC0/WO[6]
 * | 7          | ~7               |  PA17  | SCK             | EIC/EXTINT[1]                        PTC/X[5]  SERCOM1/PAD[1]  SERCOM3/PAD[1] *TCC2/WO[1]  TCC0/WO[7]
 * | 8          | ~8               |  PA18  | SS              | EIC/EXTINT[2]                        PTC/X[6]  SERCOM1/PAD[2]  SERCOM3/PAD[2] *TC3/WO[0]   TCC0/WO[2]
 * | 9          | ~9               |  PA19  | MOSI            | EIC/EXTINT[3]                        PTC/X[7]  SERCOM1/PAD[3]  SERCOM3/PAD[3] *TC3/WO[1]   TCC0/WO[3]  I2S/SD[0]
 * +------------+------------------+--------+-----------------+-------------------------------------------------------------------------------------------------------------------
 * |            | GPIO/I2C         |        |                 |
 * +------------+------------------+--------+-----------------+-------------------------------------------------------------------------------------------------------------------
 * | 10         | 10               |  PA22  | SDA             | EIC/EXTINT[6]                        PTC/X[10] *SERCOM3/PAD[0] SERCOM5/PAD[0]  TC4/WO[0]   TCC0/WO[4]  
 * | 11         | 11               |  PA23  | SCL             | EIC/EXTINT[7]                        PTC/X[11] *SERCOM3/PAD[1] SERCOM5/PAD[1]  TC4/WO[1]   TCC0/WO[5]  USB/SOF
 * +------------+------------------+--------+-----------------+-------------------------------------------------------------------------------------------------------------------
 * |            | GPIO             |        |                 |
 * +------------+------------------+--------+-----------------+-------------------------------------------------------------------------------------------------------------------
 * | 12         | 12               |  PA27  |                 | EIC/EXTINT[15]
 * | 13         | 13               |  PA28  | LED             | EIC/EXTINT[8]
 * +------------+------------------+--------+-----------------+-------------------------------------------------------------------------------------------------------------------
 * |            | Analog Connector |        |                 |
 * +------------+------------------+--------+-----------------+-------------------------------------------------------------------------------------------------------------------
 * | 14         | A0               |  PA02  | A0              | EIC/EXTINT[2] *ADC/AIN[0]  DAC/VOUT  PTC/Y[0]
 * | 15         | A1               |  PA03  | A1              | EIC/EXTINT[3] *ADC/AIN[1]  VREFA     PTC/Y[1]
 * | 16         | A2               |  PA04  | A2              | EIC/EXTINT[4] *ADC/AIN[4]  AC/AIN[0] PTC/Y[2]  SERCOM0/PAD[0]                  TCC0/WO[0]
 * | 17         | A3               |  PA05  | A3              | EIC/EXTINT[5] *ADC/AIN[5]  AC/AIN[1] PTC/Y[3]  SERCOM0/PAD[1]                  TCC0/WO[1]
 * | 18         | A4               |  PA06  | A4              | EIC/EXTINT[6] *ADC/AIN[6]  AC/AIN[2] PTC/Y[4]  SERCOM0/PAD[2]                  TCC1/WO[0]
 * | 19         | A5               |  PA07  | A5              | EIC/EXTINT[7] *ADC/AIN[7]  AC/AIN[3] PTC/Y[5]  SERCOM0/PAD[3]                  TCC1/WO[1]              I2S/SD[0]
 * +------------+------------------+--------+-----------------+-------------------------------------------------------------------------------------------------------------------
 * |            | GPIO/SWD         |        |                 |
 * +------------+------------------+--------+-----------------+-------------------------------------------------------------------------------------------------------------------
 * | 20         | SWDIO            |  PA30  | SWDIO           | EIC/EXTINT[10]                                 SERCOM1/PAD[2]                  TCC1/WO[0]             *SWDIO
 * | 21         | SWCLK            |  PA31  | SWCLK           | EIC/EXTINT[11]                                 SERCOM1/PAD[3]                  TCC1/WO[1]             *SWCLK
 * +------------+------------------+--------+-----------------+-------------------------------------------------------------------------------------------------------------------
 * |            | Alt. config.     |        |                 |
 * +------------+------------------+--------+-----------------+-------------------------------------------------------------------------------------------------------------------
 * |            | A0               |  PA02  | VOUT            | EIC/EXTINT[2]  ADC/AIN[0]  *DAC/VOUT  PTC/Y[0]
 * |            | A1               |  PA03  | AREF            | EIC/EXTINT[3]  ADC/AIN[1]  *VREFA     PTC/Y[1]
 * +------------+------------------+--------+-----------------+-------------------------------------------------------------------------------------------------------------------
 * |            | USB              |        |                 |
 * +------------+------------------+--------+-----------------+-------------------------------------------------------------------------------------------------------------------
 * | 22         |                  |  PA24  | USB_NEGATIVE    | EIC/EXTINT[12]                                 SERCOM3/PAD[2]                  TC5/WO[0]   TCC1/WO[2] *USB/DM
 * | 23         |                  |  PA25  | USB_POSITIVE    | EIC/EXTINT[13]                                 SERCOM3/PAD[3]                  TC5/WO[1]   TCC1/WO[3] *USB/DP
 * +------------+------------------+--------+-----------------+-------------------------------------------------------------------------------------------------------------------
 * |            |32.768KHz Crystal |        |                 |
 * +------------+------------------+--------+-----------------+-------------------------------------------------------------------------------------------------------------------
 * |            |                  |  PA00  | XIN32           | EIC/EXTINT[0] SERCOM1/PAD[0] TCC2/WO[0]
 * |            |                  |  PA01  | XOUT32          | EIC/EXTINT[1] SERCOM1/PAD[1] TCC2/WO[1]
 * +------------+------------------+--------+-----------------+-------------------------------------------------------------------------------------------------------------------
 */


#include "variant.h"

/*
 * Pins descriptions
 */
const PinDescription g_APinDescription[]=
{
  // 0..13 - Digital pins
  // ----------------------
  // 0/1 - USART (Serial1)
  { PORTA, 8, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NMI }, // RX: SERCOM0/PAD[0]
  { PORTA, 9, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_9 },   // TX: SERCOM0/PAD[1]

  // 2..5 - GPIO
  { PORTA, 10, PIO_TIMER_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT), No_ADC_Channel, PWM0_CH2, TCC0_CH2, EXTERNAL_INT_10 }, // TCC0/WO[2]
  { PORTA, 11, PIO_TIMER_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT), No_ADC_Channel, PWM0_CH3, TCC0_CH3, EXTERNAL_INT_11 }, // TCC0/WO[3]
  { PORTA, 14, PIO_TIMER_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT), No_ADC_Channel, PWM0_CH4, TCC0_CH4, EXTERNAL_INT_14 }, // TCC0/WO[4]
  { PORTA, 15, PIO_TIMER_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT), No_ADC_Channel, PWM0_CH5, TCC0_CH5, EXTERNAL_INT_15 }, // TCC0/WO[5]
  
  // 6..9 - SPI
  { PORTA, 16, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM2_CH0, TCC2_CH0, EXTERNAL_INT_0 },  // MISO: SERCOM1/PAD[0] / TCC2/WO[0]
  { PORTA, 17, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM2_CH1, TCC2_CH1, EXTERNAL_INT_1 },  // SCK:  SERCOM1/PAD[1] / TCC2/WO[1]
  { PORTA, 18, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM3_CH0, TC3_CH0, EXTERNAL_INT_2 },   // SS:   SERCOM1/PAD[2] / TC3/WO[0]
  { PORTA, 19, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM3_CH1, TC3_CH1, EXTERNAL_INT_3 },   // MOSI: SERCOM1/PAD[3] / TC3/WO[1]
  
  // 10/11 - I2C pins (SDA/SCL)
  { PORTA, 22, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM4_CH0, TC4_CH0, EXTERNAL_INT_6 }, // SDA: SERCOM3/PAD[0] / TC4/WO[0]
  { PORTA, 23, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM4_CH0, TC4_CH1, EXTERNAL_INT_7 }, // SCL: SERCOM3/PAD[1] / TC4/WO[1]
  // 12
  { PORTA, 27, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_15 }, // GPIO
  // 13 (LED)
  { PORTA, 28, PIO_COM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // LED

  // 14..19 - Analog pins
  // --------------------
  { PORTA, 2, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },      // ADC/AIN[0]
  { PORTA, 3, PIO_ANALOG, PIN_ATTR_NONE, ADC_Channel1, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },        // ADC/AIN[1]
  { PORTA, 4, PIO_ANALOG, (PIN_ATTR_PWM|PIN_ATTR_TIMER), ADC_Channel4, PWM0_CH0, TCC0_CH0, EXTERNAL_INT_4 }, // ADC/AIN[4]
  { PORTA, 5, PIO_ANALOG, (PIN_ATTR_PWM|PIN_ATTR_TIMER), ADC_Channel5, PWM0_CH1, TCC0_CH1, EXTERNAL_INT_5 }, // ADC/AIN[5]
  { PORTA, 6, PIO_ANALOG, PIN_ATTR_NONE, ADC_Channel6, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6 },           // ADC/AIN[6]
  { PORTA, 7, PIO_ANALOG, PIN_ATTR_NONE, ADC_Channel7, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7 },           // ADC/AIN[7]

  // 20..21 SWD
  // ----------------------
  { PORTA, 30, PIO_COM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_10 }, // SWDIO
  { PORTA, 31, PIO_COM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_11 }, // SCLK

  // 22/23 - Alt. Conf.
  // --------------------
  //{ PORTA, 2, PIO_ANALOG, PIN_ATTR_ANALOG, DAC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2 }, // DAC/VOUT
  //{ PORTA, 3, PIO_ANALOG, PIN_ATTR_ANALOG, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3 }, // [ADC-DAC]/VREFA
  
  // 22/23 USB
  // --------------------
  { PORTA, 24, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // USB/DM
  { PORTA, 25, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // USB/DP
} ;

const void* g_apTCInstances[TCC_INST_NUM+TC_INST_NUM]={ TCC0, TCC1, TCC2, TC3, TC4, TC5 } ;

// Multi-serial objects instantiation
SERCOM sercom0( SERCOM0 ) ;
SERCOM sercom1( SERCOM1 ) ;
SERCOM sercom2( SERCOM2 ) ;
SERCOM sercom3( SERCOM3 ) ;

Uart Serial( &sercom0, PIN_SERIAL_RX, PIN_SERIAL_TX, PAD_SERIAL_RX, PAD_SERIAL_TX ) ;

void SERCOM0_Handler()
{
  Serial.IrqHandler();
}

