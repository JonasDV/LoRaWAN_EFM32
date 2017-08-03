/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Bleeper board I2C driver implementation

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
#include "board.h"
#include "i2c-board.h"
#include "i2cspm.h"
#include "gpio.h"
#include "em_i2c.h"
#include "hal_i2c.h"
/*!
 *  The value of the maximal timeout for I2C waiting loops
 */
#define TIMEOUT_MAX                                 0x8000

I2cAddrSize I2cInternalAddrSize = I2C_ADDR_SIZE_8;

/*!
 * MCU I2C peripherals enumeration
 */
/*
typedef enum {
    I2C_1 = ( uint32_t )I2C1_BASE,
    I2C_2 = ( uint32_t )I2C2_BASE,
} I2cName;
*/

void I2cMcuInit( I2c_t *obj, uint8_t sclPort, uint8_t sclPin, uint8_t sdaPort, uint8_t sdaPin, uint8_t portLocation )
{
	/* Identify the object */
	obj->I2c.Instance  = ( I2C_TypeDef * )I2C0_BASE;
	obj->Scl.pinIndex = sclPin;
	obj->Scl.portIndex = sclPort;
	obj->Sda.pinIndex = sdaPin;
	obj->Sda.portIndex = sclPort;

	/* Enable necessary clocks */
	CMU_ClockEnable(cmuClock_GPIO,true);

	/* Initialize I2C */
	HAL_I2CInit(sclPort,sdaPin,sclPin,portLocation);

	/* Deactivate clocks */
	CMU_ClockEnable(cmuClock_GPIO,false);
}

void I2cMcuFormat( I2c_t *obj, I2cMode mode, I2cDutyCycle dutyCycle, bool I2cAckEnable, I2cAckAddrMode AckAddrMode, uint32_t I2cFrequency )
{
	assert_param(FAIL);
}

void I2cMcuDeInit( I2c_t *obj )
{
	assert_param(FAIL);
}

void I2cSetAddrSize( I2c_t *obj, I2cAddrSize addrSize )
{
    I2cInternalAddrSize = addrSize;
}

uint8_t I2cMcuWriteBuffer( I2c_t *obj, uint8_t deviceAddr, uint8_t addr, uint8_t *buffer, uint8_t size )
// Register address set to 8 bits and methode set to "void"
{
	/* Activate necessary clocks */
	CMU_ClockEnable(cmuClock_GPIO,true);
	HAL_I2CEnableClock(cmuClock_I2C0);

	/* Transfer structure */
	I2C_TransferSeq_TypeDef seq;
	I2C_TransferReturn_TypeDef ret;
	uint8_t writeBuf[2] = {addr,*buffer};

	/* Initializing I2C transfer */
	seq.addr = deviceAddr <<1;
	seq.flags = I2C_FLAG_WRITE;
	seq.buf[0].data = writeBuf;
	seq.buf[0].len = size+1;

	/* Sending data */
	ret = I2C_TransferInit(I2C0, &seq); // Start I2C Write transaction
	while(ret == i2cTransferInProgress){
		ret = I2C_Transfer(I2C0);
	} // Continue until all data has been sent

	/* Disable clocks */
	HAL_I2CDisableClock(cmuClock_I2C0);
	CMU_ClockEnable(cmuClock_GPIO,false);

	return SUCCESS;
	/*assert_param(FAIL);
	return FAIL;*/
}

uint8_t I2cMcuReadBuffer( I2c_t *obj, uint8_t deviceAddr, uint8_t addr, uint8_t *buffer, uint8_t size )
// Register address set to 8 bits.
{
	/* Activate necessary clocks */
	CMU_ClockEnable(cmuClock_GPIO,true);
	HAL_I2CEnableClock(cmuClock_I2C0);

	/* Transfer structure */
	I2C_TransferSeq_TypeDef seq;
	I2C_TransferReturn_TypeDef ret;
	uint8_t readBuf [1];
	readBuf[0] = addr;

	/* Initializing I2C transfer */
	seq.addr 		= deviceAddr <<1;
	seq.flags 		= I2C_FLAG_WRITE_READ;
	seq.buf[0].data = readBuf;
	seq.buf[0].len 	= 1;
	seq.buf[1].data = buffer;
	seq.buf[1].len 	= size;

	/* Sending data */

	ret = I2C_TransferInit(I2C0, &seq); // Start I2C Write transaction
	while(ret == i2cTransferInProgress){
		ret = I2C_Transfer(I2C0);
	} // Continue until all data has been sent

	/* Deactivate clocks */
	HAL_I2CDisableClock(cmuClock_I2C0);
	CMU_ClockEnable(cmuClock_GPIO,false);

	return SUCCESS;
	/*
	assert_param(FAIL);
	return FAIL;*/
}

uint8_t I2cMcuWaitStandbyState( I2c_t *obj, uint8_t deviceAddr )
{


	assert_param(FAIL);
	return FAIL;
}
