/**************************************************************************//**
 * @file hal_i2c.c
 * @brief Hardware Abstraction Layer for I2C
 * @author Bart Thoen
 * @edited by Jonas De Vos
 * @version 0.0
 * @date Created on: 01 Sept 2015
 *****************************************************************************/

#include "hal_i2c.h"

/**************************************************************************//**
 * @brief Setup I2C
 *
 *****************************************************************************/
void HAL_I2CInit(uint8_t i2c_port, uint8_t i2c_sda_pin, uint8_t i2c_scl_pin, uint8_t location)
{
	HAL_I2CEnableClock(cmuClock_I2C0);
	HAL_I2CDefaultSetup(i2c_port,i2c_sda_pin, i2c_scl_pin, location);
	HAL_I2CDisableClock(cmuClock_I2C0);
}
/**************************************************************************//**
 * @brief Enable I2C clock
 * @param[in] clock source
 *****************************************************************************/
void HAL_I2CEnableClock(CMU_Clock_TypeDef clockSource)
{
	CMU_ClockEnable(clockSource, true); 	//Enable I2C clock
}
/**************************************************************************//**
 * @brief Disable I2C clock
 * @param[in] clock source
 *****************************************************************************/
void HAL_I2CDisableClock(CMU_Clock_TypeDef clockSource)
{
	CMU_ClockEnable(clockSource, false); 	//Disable I2C clock
}
/**************************************************************************//**
 * @brief  Setup I2C
 * @param[in]
 *****************************************************************************/
void HAL_I2CDefaultSetup(uint8_t i2c_port, uint8_t i2c_sda_pin, uint8_t i2c_scl_pin, uint8_t location)
{
  // Using default settings
  I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;

  /* Configure SCA and SCL pins */
  GPIO_PinModeSet(i2c_port, i2c_sda_pin, gpioModeWiredAnd, 0);      // configure SDA pin as open drain output
  GPIO_PinModeSet(i2c_port, i2c_scl_pin, gpioModeWiredAnd, 0);      // configure SCL pin as open drain output

  /* Initializing the I2C */
  I2C_Init(I2C0, &i2cInit);

  /* Enable pins at selected location */
  I2C0->ROUTE = I2C_ROUTE_SDAPEN |
                I2C_ROUTE_SCLPEN |
                (location << _I2C_ROUTE_LOCATION_SHIFT);
}


/**************************************************************************//**
 * @brief  Transmitting I2C byte. Will busy-wait until the transfer is complete.
 * @param[in]
 *****************************************************************************/
void HAL_I2CTransferByte(uint8_t i2c_address, uint8_t reg, uint8_t *data)
{
  /* Transfer structure */
  I2C_TransferSeq_TypeDef i2cTransfer;
  I2C_TransferReturn_TypeDef ret;

  uint8_t writeBuf[1];
  writeBuf[0] = reg;

  /* Initializing I2C transfer */
  i2cTransfer.addr          = i2c_address<<1;
  i2cTransfer.flags         = I2C_FLAG_WRITE_READ;
  i2cTransfer.buf[0].data   = writeBuf;
  i2cTransfer.buf[0].len    = 1;
  i2cTransfer.buf[1].data 	= data;
  i2cTransfer.buf[1].len 	= 1;

  /* Sending data */
  ret = I2C_TransferInit(I2C0, &i2cTransfer); 				//Start I2C write transaction
  while(ret == i2cTransferInProgress) {
	  ret = I2C_Transfer(I2C0);
  }     //Continue until all data has been sent
}
/**************************************************************************//**
 * @brief  Transmitting I2C string. Will busy-wait until the transfer is complete.
 * @param[in]
 *****************************************************************************/
void HAL_I2CTransferString(uint8_t i2c_address, uint8_t* buffer,uint8_t length)
{
	HAL_I2CEnableClock(cmuClock_I2C0);
	/* Transfer structure */
	I2C_TransferSeq_TypeDef i2cTransfer;

	/* Initializing I2C transfer */
	i2cTransfer.addr          = i2c_address << 1;
	i2cTransfer.flags         = I2C_FLAG_WRITE;
	i2cTransfer.buf[0].data   = buffer;
	i2cTransfer.buf[0].len    = length;

	/* Sending data */
	I2C_TransferInit(I2C0, &i2cTransfer); 					//Start I2C write transaction
	while(I2C_Transfer(I2C0) == i2cTransferInProgress) {}     //Continue until all data has been sent
	HAL_I2CDisableClock(cmuClock_I2C0);
}
