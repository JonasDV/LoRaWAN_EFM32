/*
 * @file hal_i2c.h
 * @brief Hardware Abstraction Layer for I2C
 * @author Bart Thoen
 * @version 0.0
 *
 *  Created on: 01 Sept 2015
 *      Author: Bart Thoen
 * @edited by Jonas De Vos
 */

#ifndef HAL_I2C_H_
#define HAL_I2C_H_

#include <stdint.h>
#include <stdbool.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_i2c.h"
#include "em_rtc.h"

/*******************************************************************************
 *****************************   Declarations   **********************************
 ******************************************************************************/
#define PORT_I2C0			gpioPortC			// Port I2C0
#define SDA_PIN_I2C0		0					// SDA Pin I2C0
#define SCL_PIN_I2C0		1					// SCL Pin I2C0
#define LOCATION_I2C0		4					// Location I2C0

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

/**************************************************************************//**
 * @brief Setup I2C
 *
 *****************************************************************************/
void HAL_I2CInit(uint8_t i2c_port, uint8_t i2c_sda_pin, uint8_t i2c_scl_pin, uint8_t location);
/**************************************************************************//**
 * @brief Enable I2C clock
 * @param[in] clock source
 *****************************************************************************/
void HAL_I2CEnableClock(CMU_Clock_TypeDef clockSource);
/**************************************************************************//**
 * @brief Disable I2C clock
 * @param[in] clock source
 *****************************************************************************/
void HAL_I2CDisableClock(CMU_Clock_TypeDef clockSource);
/**************************************************************************//**
 * @brief  Setup I2C
 * @param[in]
 *****************************************************************************/
void HAL_I2CDefaultSetup(uint8_t i2c_port, uint8_t i2c_sda_pin, uint8_t i2c_scl_pin, uint8_t location);
/**************************************************************************//**
 * @brief  Transmitting I2C data. Will busy-wait until the transfer is complete.
 * @param[in]
 *****************************************************************************/
void HAL_I2CTransferByte(uint8_t i2c_address, uint8_t reg, uint8_t *data);
/**************************************************************************//**
 * @brief  Transmitting I2C data. Will busy-wait until the transfer is complete.
 * @param[in]
 *****************************************************************************/
void HAL_I2CTransferString(uint8_t i2c_address, uint8_t* buffer,uint8_t length);


#endif /* HAL_I2C_H_ */
