/**************************************************************************//**
*   @file   ad5629r.h
*   @brief  Header file of AD5629R Driver for Microblaze processor.
*   @author Lucian Sin (Lucian.Sin@analog.com)
*
*******************************************************************************
* Copyright 2013(c) Analog Devices, Inc.
*
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*  - Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*  - Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
*  - Neither the name of Analog Devices, Inc. nor the names of its
*    contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*  - The use of this software may or may not infringe the patent rights
*    of one or more patent holders.  This license does not release you
*    from the requirement that you obtain separate licenses from these
*    patent holders to use this software.
*  - Use of the software either in source or binary form, must be run
*    on or directly connected to an Analog Devices Inc. component.
*
* THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT, MERCHANTABILITY
* AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************/

#ifndef _AD5629R_H_
#define _AD5629R_H_

/******************************************************************************/
/******************* Macros and Constants Definitions *************************/
/******************************************************************************/
/* AD5629R Device I2C Address */
#define AD5629R_I2C_ADDR_0          0x54 // A1=0 and A0=0 (A0_Pin=High)
#define AD5629R_I2C_ADDR_1          0x56 // A1=1 and A0=0 (A0_Pin=NC)
#define AD5629R_I2C_ADDR_2          0x57 // A1=1 and A0=1 (A0_Pin=Low)

#define MAX_RESOLUTION              16

/* Commands */
#define AD5629R_WRITE_N             0x0
#define AD5629R_UPDATE_N            0x1
#define AD5629R_WRITE_N_UPDATE_ALL  0x2
#define AD5629R_WRITE_N_UPDATE_N    0x3
#define AD5629R_POWER               0x4
#define AD5629R_LOAD_CLEAR_REG      0x5
#define AD5629R_LOAD_LDAC_REG       0x6
#define AD5629R_RESET               0x7
#define AD5629R_REFERENCE           0x8

/* AD5629R GPIO */
/* LDAC - GPIO0 */
#define AD5629R_LDAC_OUT            gpio_direction_output(dev->gpio_ldac, \
			            GPIO_HIGH);
#define AD5629R_LDAC_LOW            gpio_set_value(dev->gpio_ldac,        \
			            GPIO_LOW)
#define AD5629R_LDAC_HIGH           gpio_set_value(dev->gpio_ldac,        \
			            GPIO_HIGH)
/* CLR - GPIO1 */
#define AD5629R_CLR_OUT             gpio_direction_output(dev->gpio_clr,  \
			            GPIO_HIGH);
#define AD5629R_CLR_LOW             gpio_set_value(dev->gpio_clr,         \
			            GPIO_LOW)
#define AD5629R_CLR_HIGH            gpio_set_value(dev->gpio_clr,         \
			            GPIO_HIGH)

/* DAC Addresses */
#define AD5629R_DAC_A_ADDR          0x0
#define AD5629R_DAC_B_ADDR          0x1
#define AD5629R_DAC_C_ADDR          0x2
#define AD5629R_DAC_D_ADDR          0x3
#define AD5629R_DAC_E_ADDR          0x4
#define AD5629R_DAC_F_ADDR          0x5
#define AD5629R_DAC_G_ADDR          0x6
#define AD5629R_DAC_H_ADDR          0x7
#define AD5629R_DAC_ALL_ADDR        0xF

/* DAC Selection */
#define DAC_A_SEL           1
#define DAC_B_SEL           2
#define DAC_C_SEL           4
#define DAC_D_SEL           8
#define DAC_E_SEL           16
#define DAC_F_SEL           32
#define DAC_G_SEL           64
#define DAC_H_SEL           128

/* Power modes */
#define PWR_NORMAL              0
#define PWR_1K_TO_GND           1
#define PWR_100K_TO_GND         2
#define PWR_3_STATE             3

/* Clear code values */
#define CLR_TO_ZEROSCALE        0
#define CLR_TO_MIDSCALE         1
#define CLR_TO_FULLSCALE        2
#define CLR_NOOP                3

/* Internal reference status */
#define REF_ON          1
#define REF_OFF         0

/******************************************************************************/
/*************************** Types Declarations *******************************/
/******************************************************************************/
/* Supported devices */
typedef enum {
    ID_AD5629R,
    ID_AD5669R,
    ID_AD5668,
    ID_AD5648,
    ID_AD5628,
} AD5629R_type;

typedef enum {
    com_spi,
    com_i2c
} comm_type_t;

typedef struct {
    unsigned int resolution;
    comm_type_t communication;
} ad5629r_chip_info;

typedef struct {
	/* I2C */
	i2c_desc		*i2c_desc;
	/* SPI */
	spi_desc		*spi_desc;
	/* GPIO */
	gpio_desc		*gpio_ldac;
	gpio_desc		*gpio_clr;
	/* Device Settings */
	AD5629R_type		act_device;
} ad5629r_dev;

typedef struct {
	/* I2C */
	i2c_init_param	i2c_init;
	/* SPI */
	spi_init_param	spi_init;
	/* GPIO */
	int8_t		gpio_ldac;
	int8_t		gpio_clr;
	/* Device Settings */
	AD5629R_type	act_device;
} ad5629r_init_param;

/******************************************************************************/
/************************ Functions Declarations ******************************/
/******************************************************************************/
/* Initializes the communication with the device. */
char AD5629R_Init(ad5629r_dev **device,
		  ad5629r_init_param init_param);
/* Free the resources allocated by AD5629R_Init(). */
int32_t AD5629R_remove(ad5629r_dev *dev);
/* Writes a value to Input Register N of selected DAC channel. */
void AD5629R_WriteRegN(ad5629r_dev *dev,
		       unsigned char dacN,
		       unsigned short dacValue);
/* Updates selected DAC register. */
void AD5629R_UpdateDacN(ad5629r_dev *dev,
			unsigned char dacN);
/* Writes a value to Input Register N of selected DAC channel, then updates all. */
void AD5629R_WriteRegNUpdateAll(ad5629r_dev *dev,
				unsigned char dacN,
				unsigned short dacValue);
/* Writes a value to Input Register N and updates the respective DAC channel. */
void AD5629R_WriteRegNUpdateN(ad5629r_dev *dev,
			      unsigned char dacN,
			      unsigned short dacValue);
/* Sets the power mode for one or more selected DAC channels. */
void AD5629R_SetPowerMode(ad5629r_dev *dev,
			  unsigned char dacSel,
			  unsigned char mode);
/* Loads the Clear Code Register with a certain value. */
void AD5629R_LoadClearCodeReg(ad5629r_dev *dev,
			      unsigned char clearValue);
/* Loads the LDAC register with a certain value. */
void AD5629R_LoadLdacReg(ad5629r_dev *dev,
			 unsigned char dacSel);
/* Makes a power-on reset. */
void AD5629R_Reset(ad5629r_dev *dev);
/* Turns on/off the internal reference. */
void AD5629R_SetRef(ad5629r_dev *dev,
		    unsigned char status);


#endif /* AD5629_H_ */
