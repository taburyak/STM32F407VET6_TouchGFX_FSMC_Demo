/**
  ******************************************************************************
  * File Name          : TouchGFXGeneratedHAL.cpp
  ******************************************************************************
  * This file is generated by TouchGFX Generator 4.19.1. Please, do not edit!
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include <TouchGFXGeneratedHAL.hpp>
#include <touchgfx/hal/OSWrappers.hpp>
#include <gui/common/FrontendHeap.hpp>

#include "stm32f4xx.h"

using namespace touchgfx;

/* ******************************************************
 * Functions required by Partial Frame Buffer Strategy
 * ******************************************************
 *
 *  int touchgfxDisplayDriverTransmitActive() must return whether or not data is currently being transmitted, over e.g. SPI.
 *  void touchgfxDisplayDriverTransmitBlock(const uint8_t* pixels, uint16_t x, uint16_t y, uint16_t w, uint16_t h) will be called
 *  when the framework wants to send a block. The user must then transfer the data represented by the arguments.
 *
 *  A user must call touchgfx::startNewTransfer(); once touchgfxDisplayDriverTransmitBlock() has successfully sent a block.
 *  E.g. if using DMA to transfer the block, this could be called in the "Transfer Completed" interrupt handler.
 *
 */

extern "C" int touchgfxDisplayDriverTransmitActive();
extern "C" void touchgfxDisplayDriverTransmitBlock(const uint8_t* pixels, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
extern "C" void touchgfxSignalVSync(void);

// Block Allocator for Partial Framebuffer strategy
static ManyBlockAllocator<1920, /* block size */
                   3, /* number of blocks */
                   2  /* bytes per pixel */
                   > blockAllocator;

void TouchGFXGeneratedHAL::initialize()
{
    HAL::initialize();
    registerEventListener(*(Application::getInstance()));
    enableLCDControllerInterrupt();
    enableInterrupts();
    // Partial framebuffer strategy
    setFrameBufferAllocator(&blockAllocator);
    setFrameRefreshStrategy(HAL::REFRESH_STRATEGY_PARTIAL_FRAMEBUFFER);
}

void TouchGFXGeneratedHAL::configureInterrupts()
{
}

void TouchGFXGeneratedHAL::enableInterrupts()
{
}

void TouchGFXGeneratedHAL::disableInterrupts()
{
}

void TouchGFXGeneratedHAL::enableLCDControllerInterrupt()
{
}

bool TouchGFXGeneratedHAL::beginFrame()
{
    return HAL::beginFrame();
}

void TouchGFXGeneratedHAL::endFrame()
{
    // We must guard the next frame until we're done transferring all blocks over our display interface
    // through either a semaphore if user is running an OS or a simple variable if not
    // Wait until all blocks have been transmitted
    while(touchgfxDisplayDriverTransmitActive()){}

    HAL::endFrame();
    touchgfx::OSWrappers::signalRenderingDone();
}

uint16_t* TouchGFXGeneratedHAL::getTFTFrameBuffer() const
{
    //getTFTFrameBuffer() not used for selected Frame Buffer Strategy
    return 0;
}

void TouchGFXGeneratedHAL::setTFTFrameBuffer(uint16_t* adr)
{
    //setTFTFrameBuffer() not used for selected display interface
}

void TouchGFXGeneratedHAL::flushFrameBuffer(const touchgfx::Rect& rect)
{
    HAL::flushFrameBuffer(rect);
    // Once flushFrameBuffer() is called by the framework a block is already for transfer
    // Mark it ready for transfer and transmit it if user defined method isTransmittingData() does not return false
    // If data is not being transmitted, transfer the data with user defined method transmitFrameBufferBlock().
    frameBufferAllocator->markBlockReadyForTransfer();
    if (!touchgfxDisplayDriverTransmitActive())
    {
        touchgfx::Rect r;
        // Get pointer to block buffer and coordinates of the rect
        const uint8_t* pixels = frameBufferAllocator->getBlockForTransfer(r);
        // Start transmission of the block
        touchgfxDisplayDriverTransmitBlock((uint8_t*)pixels, r.x, r.y, r.width, r.height);
    }
}

bool TouchGFXGeneratedHAL::blockCopy(void* RESTRICT dest, const void* RESTRICT src, uint32_t numBytes)
{
    return HAL::blockCopy(dest, src, numBytes);
}

/*
 * ******************************************************
 * Required by Partial Frame Buffer Strategy
 * ******************************************************
 */
namespace touchgfx
{
/**
 * This function is called by FrameBufferAllocator if no block is
 * available.
 */
__weak void FrameBufferAllocatorWaitOnTransfer()
{
  /* NOTE: This function should not be modified, when the fuction is needed,
   *       FrameBufferAllocatorWaitOnTransfer should be implemented in the user file
   */
}

/**
 * Called by FrameBufferAllocator when a block is drawn and
 * therefore ready for transfer. The LCD driver should use this
 * method to start a transfer.
 */
__weak void FrameBufferAllocatorSignalBlockDrawn()
{
  /* NOTE: This function should not be modified, when the fuction is needed,
   *       FrameBufferAllocatorSignalBlockDrawn should be implemented in the user file
   */
}

// A user must call touchgfx::startNewTransfer(); once transmitFrameBufferBlock() has successfully sent a block.
void startNewTransfer()
{
    FrameBufferAllocator* fba = HAL::getInstance()->getFrameBufferAllocator();

  // Free the previous transmitted block, marking it ready for rendering
    fba->freeBlockAfterTransfer();
    if (fba->hasBlockReadyForTransfer())
    {
        touchgfx::Rect r;
        // Get pointer to block buffer and coordinates of the rect
        const uint8_t* pixels = fba->getBlockForTransfer(r);
        // Start transmission of the block
        touchgfxDisplayDriverTransmitBlock((uint8_t*)pixels, r.x, r.y, r.width, r.height);
    }
}

extern "C"
void DisplayDriver_TransferCompleteCallback()
{
  // After completed transmission start new transfer if blocks are ready.
    touchgfx::startNewTransfer();
}
}

extern "C"
void touchgfxSignalVSync(void)
{
    /* VSync has occurred, increment TouchGFX engine vsync counter */
    touchgfx::HAL::getInstance()->vSync();

    /* VSync has occurred, signal TouchGFX engine */
    touchgfx::OSWrappers::signalVSync();
}

/**
  * STM32 FMC Interface
  *  - Base Address           : 0x60000000
  *  - Bank Size              : 0x04000000
  *  - Bank ID                : 1
  *  - Bank Register Address  : 0x60000000
  *  - Bank Memory Address    : 0x60080000
  *  - Data Size              : 16 bits
  */
extern "C" {
    /**
     * @brief LCD constroller REG and RAM addresses
     */
#define FMC_BANK1_REG ((uint16_t *) 0x60000000)
#define FMC_BANK1_MEM ((uint16_t *) 0x60080000)

    /**
      * @brief  Writes register address.
      * @param  Reg: Register to be written
      */
    __STATIC_INLINE void FMC_BANK1_WriteReg(uint8_t Reg)
    {
        /* Write 16-bits Index, then write register */
        *FMC_BANK1_REG = Reg;
        __DSB();
    }

    /**
      * @brief  Writes register value.
      * @param  Data: Data to be written
      */
    __STATIC_INLINE void FMC_BANK1_WriteData(uint16_t Data)
    {
        /* Write 16-bits Reg */
        *FMC_BANK1_MEM = Data;
        __DSB();
    }

    /**
      * @brief  Reads register value.
      * @retval Read value
      */
    __STATIC_INLINE uint16_t FMC_BANK1_ReadData(void)
    {
        return *FMC_BANK1_MEM;
    }

    /********************************* LINK LCD ***********************************/
    /**
      * @brief  Initialize the LCD IO.
      * @param  None
      * @retval None
      */
    __weak void LCD_IO_Init(void)
    {
        // Already Done by MX_FMC_Init()
    }

    /**
      * @brief  Writes data on LCD data register.
      * @param  Data: Data to be written
      * @retval None
      */
    __weak void LCD_IO_WriteData(uint16_t RegValue)
    {
        /* Write 16-bits Reg */
        FMC_BANK1_WriteData(RegValue);
    }

    /**
      * @brief  Writes several data on LCD data register.
      * @param  Data: pointer on data to be written
      * @param  Size: data amount in 16bits short unit
      * @retval None
      */
    __weak void LCD_IO_WriteMultipleData(uint16_t* pData, uint32_t Size)
    {
        uint32_t  i;

        for (i = 0; i < Size; i++)
        {
            FMC_BANK1_WriteData(pData[i]);
        }
    }

    /**
      * @brief  Writes register on LCD register.
      * @param  Reg: Register to be written
      * @retval None
      */
    __weak void LCD_IO_WriteReg(uint8_t Reg)
    {
        /* Write 16-bits Index, then Write Reg */
        FMC_BANK1_WriteReg(Reg);
    }

    /**
      * @brief  Reads data from LCD data register.
      * @param  None
      * @retval Read data.
      */
    __weak uint16_t LCD_IO_ReadData(void)
    {
        return FMC_BANK1_ReadData();
    }

    /**
      * @brief  LCD delay
      * @param  Delay: Delay in ms
      * @retval None
      */
    __weak void LCD_IO_Delay(uint32_t Delay)
    {
        HAL_Delay(Delay);
    }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
