/**
  ******************************************************************************
  * @file    py32f002b_hal_flash.h
  * @author  MCU Application Team
  * @brief   Header file of FLASH HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Puya under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PY32F002B_HAL_FLASH_H
#define __PY32F002B_HAL_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f002b_hal_def.h"

/** @addtogroup PY32F002B_HAL_Driver
  * @{
  */

/** @addtogroup FLASH
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup FLASH_Exported_Types FLASH Exported Types
  * @{
  */

/**
  * @brief  FLASH Erase structure definition
  */
typedef struct
{
  uint32_t TypeErase;        /*!< Mass erase or page erase.
                                  This parameter can be a value of @ref FLASH_Type_Erase */
  uint32_t PageAddress;      /*!< PageAdress: Initial FLASH page address to erase when mass erase and sector erase is disabled
                                  This parameter must be a number between Min_Data = FLASH_BASE and Max_Data = FLASH_END */
  uint32_t NbPages;          /*!< Number of pages to be erased.
                                  This parameter must be a value between 1 and (FLASH_PAGE_NB - value of initial page)*/
  uint32_t SectorAddress;    /*!< PageAdress: Initial FLASH page address to erase when mass erase and page erase is disabled
                                  This parameter must be a number between Min_Data = FLASH_BASE and Max_Data = FLASH_BANK1_END */    
  uint32_t NbSectors;        /*!< Number of sectors to be erased.
                                  This parameter must be a value between 1 and (FLASH_SECTOR_NB - value of initial sector)*/
    
} FLASH_EraseInitTypeDef;

/**
  * @brief  FLASH Option Bytes PROGRAM structure definition
  */
typedef struct
{
  uint32_t  OptionType;       /*!< OptionType: Option byte to be configured.
                                   This parameter can be a value of @ref FLASH_Option_Type */

  uint32_t  WRPSector;        /*!< WRPSector: This bitfield specifies the sector (s) which are write protected.
                                   This parameter can be a combination of @ref FLASH_Option_Bytes_Write_Protection */

  uint32_t  SDKStartAddr;     /*!< SDK Start address (used for FLASH_SDKR). It represents first address of start block
                                   to protect. Make sure this parameter is multiple of SDK granularity: 2048 Bytes.*/

  uint32_t  SDKEndAddr;       /*!< SDK End address (used for FLASH_SDKR). It represents first address of end block
                                   to protect. Make sure this parameter is multiple of SDK granularity: 2048 Bytes.*/

  uint32_t  USERType;         /*!< User option byte(s) to be configured (used for OPTIONBYTE_USER).
                                   This parameter can be a combination of @ref FLASH_OB_USER_Type */

  uint32_t  USERConfig;       /*!< Value of the user option byte (used for OPTIONBYTE_USER).
                                   This parameter can be a combination of
                                   @ref FLASH_OB_USER_BOR_ENABLE,
                                   @ref FLASH_OB_USER_BOR_LEVEL,
                                   @ref FLASH_OB_USER_IWDG_SW,
                                   @ref FLASH_OB_USER_IWDG_STOP,
                                   @ref FLASH_OB_USER_SWD_NRST */
} FLASH_OBProgramInitTypeDef;



/**
  * @brief  FLASH Option Bytes PROGRAM structure definition
  */
typedef struct
{
  uint32_t  BOOTType;         /*!< BOOTType: Option byte to be configured.
                                   This parameter can be a value of @ref FLASH_Option_BOOT_TYPE */

  uint32_t  BOOTSize;         /*!< BOOTSize: This bitfield specifies the load boot size.
                                   This parameter can be a value of @ref FLASH_Option_BOOT_SIZE */

} FLASH_OBBootProgramInitTypeDef;

/**
* @brief  FLASH handle Structure definition
*/
typedef struct
{
  HAL_LockTypeDef   Lock;              /* FLASH locking object */
  uint32_t          ErrorCode;         /* FLASH error code */
  uint32_t          ProcedureOnGoing;  /* Internal variable to indicate which procedure is ongoing or not in IT context */
  uint32_t          Address;           /* Internal variable to save address selected for program in IT context */
  uint32_t          PageOrSector;      /* Internal variable to define the current page or sector which is erasing in IT context */
  uint32_t          NbPagesSectorsToErase;    /* Internal variable to save the remaining pages to erase in IT context */
} FLASH_ProcessTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup FLASH_Exported_Constants FLASH Exported Constants
  * @{
  */

/** @defgroup FLASH_Latency FLASH Latency
  * @{
  */
#define FLASH_LATENCY_0                 0x00000000UL                                /*!< FLASH Zero wait state */
#define FLASH_LATENCY_1                 FLASH_ACR_LATENCY                           /*!< FLASH One wait state */
/**
  * @}
  */
  
/** @defgroup FLASH_Type_Erase FLASH erase type
  * @{
  */
#define FLASH_TYPEERASE_MASSERASE       FLASH_CR_MER  /*!<Flash mass erase activation*/
#define FLASH_TYPEERASE_PAGEERASE       FLASH_CR_PER  /*!<Flash Pages erase activation*/
#define FLASH_TYPEERASE_SECTORERASE     FLASH_CR_SER  /*!<Flash sectore erase activation*/
/**
  * @}
  */

/** @defgroup FLASH_Type_Program FLASH type program
  * @{
  */
#define FLASH_TYPEPROGRAM_PAGE          FLASH_CR_PG  /*!<Program 128bytes at a specified address.*/
/**
  * @}
  */
  
/** @defgroup FLASH_Flags FLASH Flags Definition
  * @{
  */
#define FLASH_FLAG_BSY                  FLASH_SR_BSY      /*!< FLASH Operation Busy flag */
#define FLASH_FLAG_OPTVERR              FLASH_SR_OPTVERR  /*!< FLASH Option validity error flag */
#define FLASH_FLAG_WRPERR               FLASH_SR_WRPERR   /*!< FLASH Write protection error flag */
#define FLASH_FLAG_EOP                  FLASH_SR_EOP      /*!< FLASH End of operation flag */

#define FLASH_FLAG_ALL_ERRORS           (FLASH_FLAG_WRPERR | FLASH_FLAG_OPTVERR)
/**
  * @}
  */

/** @defgroup FLASH_Interrupt_definition FLASH Interrupts Definition
  * @brief FLASH Interrupt definition
  * @{
  */
#define FLASH_IT_EOP                    FLASH_CR_EOPIE              /*!< End of FLASH Operation Interrupt source */
#define FLASH_IT_OPERR                  FLASH_CR_ERRIE              /*!< Error Interrupt source */
/**
  * @}
  */

/** @defgroup FLASH_Error FLASH Error
  * @{
  */
#define HAL_FLASH_ERROR_NONE            0x00000000U
#define HAL_FLASH_ERROR_WRP             FLASH_FLAG_WRPERR
#define HAL_FLASH_ERROR_OPTV            FLASH_FLAG_OPTVERR
/**
  * @}
  */

/** @defgroup FLASH_PROGRAM_ERASE_CLOCK FLASH Program and Erase Clock
  * @{
  */
#define FLASH_PROGRAM_ERASE_CLOCK_24MHZ       0x00000004U           /*!< 24MHz */
#if defined(RCC_HSI48M_SUPPORT)
#define FLASH_PROGRAM_ERASE_CLOCK_48MHZ       0x00000005U           /*!< 48MHz */
#endif
/**
  * @}
  */


/** @defgroup FLASH_Option_Bytes_Write_Protection FLASH Option Bytes Write Protection
  * @{
  */
#define OB_WRP_SECTOR_0            ((uint32_t)0x00000001U) /* Write protection of Sector0 */
#define OB_WRP_SECTOR_1            ((uint32_t)0x00000002U) /* Write protection of Sector1 */
#define OB_WRP_SECTOR_2            ((uint32_t)0x00000004U) /* Write protection of Sector2 */
#define OB_WRP_SECTOR_3            ((uint32_t)0x00000008U) /* Write protection of Sector3 */
#define OB_WRP_SECTOR_4            ((uint32_t)0x00000010U) /* Write protection of Sector4 */
#define OB_WRP_SECTOR_5            ((uint32_t)0x00000020U) /* Write protection of Sector5 */


#define OB_WRP_Pages0to31          ((uint32_t)0x00000001U) /* Write protection from page0   to page31 */
#define OB_WRP_Pages32to63         ((uint32_t)0x00000002U) /* Write protection from page32  to page63 */
#define OB_WRP_Pages64to95         ((uint32_t)0x00000004U) /* Write protection from page64  to page95 */
#define OB_WRP_Pages96to127        ((uint32_t)0x00000008U) /* Write protection from page96  to page127 */
#define OB_WRP_Pages128to159       ((uint32_t)0x00000010U) /* Write protection from page128 to page159 */
#define OB_WRP_Pages160to191       ((uint32_t)0x00000020U) /* Write protection from page160 to page191 */

#define OB_WRP_AllPages            ((uint32_t)0x0000003FU) /*!< Write protection of all Sectors */
/**
  * @}
  */



/** @defgroup FLASH_OB_USER_Type FLASH User Option Type
  * @{
  */
#define OB_USER_BOR_EN          FLASH_OPTR_BOR_EN
#define OB_USER_BOR_LEV         FLASH_OPTR_BOR_LEV
#define OB_USER_IWDG_SW         FLASH_OPTR_IWDG_SW
#define OB_USER_SWD_NRST_MODE   (FLASH_OPTR_SWD_MODE | FLASH_OPTR_NRST_MODE)

#if defined(FLASH_OPTR_IWDG_STOP)
#define OB_USER_IWDG_STOP       FLASH_OPTR_IWDG_STOP
#define OB_USER_ALL             (OB_USER_BOR_EN  | OB_USER_BOR_LEV   | OB_USER_IWDG_SW | \
                                 OB_USER_SWD_NRST_MODE | OB_USER_IWDG_STOP)
#else
#define OB_USER_ALL             (OB_USER_BOR_EN  | OB_USER_BOR_LEV   | OB_USER_IWDG_SW | \
                                 OB_USER_SWD_NRST_MODE)
#endif
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_BOR_ENABLE FLASH Option Bytes BOR Enable
  * @{
  */
#define OB_BOR_DISABLE                  0x00000000U        /*!< BOR Reset set to default */
#define OB_BOR_ENABLE                   FLASH_OPTR_BOR_EN  /*!< Use option byte to define BOR thresholds */
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_BOR_LEVEL FLASH Option Bytes BOR Level
  * @{
  */
#define OB_BOR_LEVEL_1p7_1p8    ((uint32_t)0x0000U)                                                              /*!< BOR Reset threshold levels for 1.7V - 1.8V VDD power supply    */
#define OB_BOR_LEVEL_1p9_2p0    ((uint32_t)FLASH_OPTR_BOR_LEV_0)                                                 /*!< BOR Reset threshold levels for 1.9V - 2.0V VDD power supply    */
#define OB_BOR_LEVEL_2p1_2p2    ((uint32_t)FLASH_OPTR_BOR_LEV_1)                                                 /*!< BOR Reset threshold levels for 2.1V - 2.2V VDD power supply    */
#define OB_BOR_LEVEL_2p3_2p4    ((uint32_t)(FLASH_OPTR_BOR_LEV_0 | FLASH_OPTR_BOR_LEV_1))                        /*!< BOR Reset threshold levels for 2.3V - 2.4V VDD power supply    */
#define OB_BOR_LEVEL_2p5_2p6    ((uint32_t)FLASH_OPTR_BOR_LEV_2)                                                 /*!< BOR Reset threshold levels for 2.5V - 2.6V VDD power supply    */
#define OB_BOR_LEVEL_2p7_2p8    ((uint32_t)(FLASH_OPTR_BOR_LEV_0 | FLASH_OPTR_BOR_LEV_2))                        /*!< BOR Reset threshold levels for 2.7V - 2.8V VDD power supply    */
#define OB_BOR_LEVEL_2p9_3p0    ((uint32_t)(FLASH_OPTR_BOR_LEV_1 | FLASH_OPTR_BOR_LEV_2))                        /*!< BOR Reset threshold levels for 2.9V - 3.0V VDD power supply    */
#define OB_BOR_LEVEL_3p1_3p2    ((uint32_t)(FLASH_OPTR_BOR_LEV_0 | FLASH_OPTR_BOR_LEV_1 | FLASH_OPTR_BOR_LEV_2)) /*!< BOR Reset threshold levels for 3.1V - 3.2V VDD power supply    */

/**
  * @}
  */

/** @defgroup FLASH_WRP_State FLASH WRP State
  * @{
  */
#define OB_WRPSTATE_DISABLE        ((uint32_t)0x00U)  /*!<Disable the write protection of the desired sectors*/
#define OB_WRPSTATE_ENABLE         ((uint32_t)0x01U)  /*!<Enable the write protection of the desired sectors*/

/**
  * @}
  */

/** @defgroup FLASH_OB_USER_IWDG_SW FLASH Option Bytes IWatchdog
  * @{
  */

#define OB_IWDG_SW                     FLASH_OPTR_IWDG_SW  /*!< Software IWDG selected */
#define OB_IWDG_HW                     0x00000000U         /*!< Hardware IWDG selected */

/**
  * @}
  */
  
/** @defgroup FLASH_OB_USER_IWDG_STOP FLASH IWDG Counter Freeze in STOP
  * @{
  */
#if defined(FLASH_OPTR_IWDG_STOP)
#define OB_IWDG_STOP_FREEZE            0x00000000U  /*!< Freeze IWDG counter in STOP mode */
#define OB_IWDG_STOP_ACTIVE            ((uint32_t)FLASH_OPTR_IWDG_STOP) /*!< IWDG counter active in STOP mode */
#endif
/**
  * @}
  */

/** @defgroup FLASH_OB_USER_SWD_NRST FLASH Option Bytes SWD_NRST
  * @{
  */

#define OB_SWD_PB6_NRST_PC0            0x00000000U                                         /*!< PB6:SWD,PC0:NRST */
#define OB_SWD_PB6_GPIO_PC0            FLASH_OPTR_NRST_MODE                                /*!< PB6:SWD,PC0:GPIO */
#define OB_SWD_PC0_GPIO_PB6           (FLASH_OPTR_NRST_MODE | FLASH_OPTR_SWD_MODE )        /*!< PC0:SWD,PB6:GPIO */

/**
  * @}
  */

/** @defgroup FLASH_Option_Type FLASH Option Type
  * @{
  */
#define OPTIONBYTE_WRP            ((uint32_t)0x01U)  /*!<WRP option byte configuration*/
#define OPTIONBYTE_SDK            ((uint32_t)0x02U)  /*!<SDK option byte configuration*/
#define OPTIONBYTE_USER           ((uint32_t)0x08U)  /*!<USER option byte configuration*/
#define OPTIONBYTE_ALL            (OPTIONBYTE_WRP  | \
                                   OPTIONBYTE_SDK  | \
                                   OPTIONBYTE_USER)

/**
  * @}
  */

/** @defgroup FLASH_Option_BOOT_TYPE FLASH Option Bytes BOOT TYPE
  * @{
  */
#define OB_BOOT_MODE_MAINFLASH    ((uint32_t)0x00000000U)                                       /*!< BOOT from MainFlash */
#define OB_BOOT_MODE_SRAM         ((uint32_t)FLASH_BTCR_BOOT0)                                  /*!< BOOT from SRAM */
#define OB_BOOT_MODE_LOADFLASH    ((uint32_t)(FLASH_BTCR_BOOT0 | FLASH_BTCR_NBOOT1))            /*!< BOOT From LOADFLASH */
/**
  * @}
  */

/** @defgroup FLASH_Option_BOOT_SIZE FLASH Option Bytes BOOT SIZE
  * @{
  */
#define OB_BOOT_SIZE_NONE    ((uint32_t)0x00000000U)                                       /*!< LOAD FLASH SIZE :0K */  
#define OB_BOOT_SIZE_1K      ((uint32_t)FLASH_BTCR_BOOT_SIZE_0)                            /*!< LOAD FLASH SIZE :1K*/
#define OB_BOOT_SIZE_2K      ((uint32_t)FLASH_BTCR_BOOT_SIZE_1)                            /*!< LOAD FLASH SIZE :2K*/
#define OB_BOOT_SIZE_3K      ((uint32_t)FLASH_BTCR_BOOT_SIZE_0 | FLASH_BTCR_BOOT_SIZE_1)   /*!< LOAD FLASH SIZE :3K*/
#define OB_BOOT_SIZE_4K      ((uint32_t)FLASH_BTCR_BOOT_SIZE_2)                            /*!< LOAD FLASH SIZE :4K*/
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup FLASH_Exported_Macros FLASH Exported Macros
  *  @brief macros to control FLASH features
  *  @{
  */

/**
  * @brief  Set the FLASH Latency.
  * @param  __LATENCY__ FLASH Latency
  *         This parameter can be one of the following values :
  *     @arg @ref FLASH_LATENCY_0  FLASH Zero wait state
  *     @arg @ref FLASH_LATENCY_1  FLASH One wait state
  * @retval None
  */
#define __HAL_FLASH_SET_LATENCY(__LATENCY__)    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, (__LATENCY__))

/**
  * @brief  Get the FLASH Latency.
  * @retval FLASH Latency
  *         Returned value can be one of the following values :
  *     @arg @ref FLASH_LATENCY_0 FLASH Zero wait state
  *     @arg @ref FLASH_LATENCY_1 FLASH One wait state
  *
  */
#define __HAL_FLASH_GET_LATENCY()               READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY)

/** @defgroup FLASH_Interrupt FLASH Interrupts Macros
 *  @brief macros to handle FLASH interrupts
 * @{
 */

/**
  * @brief  Enable the specified FLASH interrupt.
  * @param  __INTERRUPT__ FLASH interrupt
  *         This parameter can be any combination of the following values:
  *     @arg @ref FLASH_IT_EOP End of FLASH Operation Interrupt
  *     @arg @ref FLASH_IT_OPERR Error Interrupt
  * @note (*) availability depends on devices
  * @retval none
  */
#define __HAL_FLASH_ENABLE_IT(__INTERRUPT__)    SET_BIT(FLASH->CR, (__INTERRUPT__))

/**
  * @brief  Disable the specified FLASH interrupt.
  * @param  __INTERRUPT__ FLASH interrupt
  *         This parameter can be any combination of the following values:
  *     @arg @ref FLASH_IT_EOP End of FLASH Operation Interrupt
  *     @arg @ref FLASH_IT_OPERR Error Interrupt
  * @note (*) availability depends on devices
  * @retval none
  */
#define __HAL_FLASH_DISABLE_IT(__INTERRUPT__)   CLEAR_BIT(FLASH->CR, (__INTERRUPT__))

/**
  * @brief  Check whether the specified FLASH flag is set or not.
  * @param  __FLAG__ specifies the FLASH flag to check.
  *   This parameter can be one of the following values:
  *     @arg @ref FLASH_FLAG_EOP FLASH End of Operation flag
  *     @arg @ref FLASH_FLAG_WRPERR FLASH Write protection error flag
  *     @arg @ref FLASH_FLAG_OPTVERR FLASH Option validity error flag
  *     @arg @ref FLASH_FLAG_BSY FLASH write/erase operations in progress flag
  *     @arg @ref FLASH_FLAG_ALL_ERRORS FLASH All errors flags
  * @note (*) availability depends on devices
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
#define __HAL_FLASH_GET_FLAG(__FLAG__)                    (READ_BIT(FLASH->SR,   (__FLAG__)) == (__FLAG__))

/**
  * @brief  Clear the FLASHs pending flags.
  * @param  __FLAG__ specifies the FLASH flags to clear.
  *   This parameter can be any combination of the following values:
  *     @arg @ref FLASH_FLAG_EOP FLASH End of Operation flag
  *     @arg @ref FLASH_FLAG_WRPERR FLASH Write protection error flag
  *     @arg @ref FLASH_FLAG_OPTVERR FLASH Option validity error flag
  *     @arg @ref FLASH_FLAG_ALL_ERRORS FLASH All errors flags
  * @retval None
  */
#define __HAL_FLASH_CLEAR_FLAG(__FLAG__)                do {  WRITE_REG(FLASH->SR, (__FLAG__)); \
                                                           } while(0U)


#define __HAL_FLASH_TIME_REG_SET(__EPPARA0__,__EPPARA1__,__EPPARA2__,__EPPARA3__,__EPPARA4__)           \
                                                        do {                                            \
                                                            FLASH->TS0  = (__EPPARA0__)&0x1FF;           \
                                                            FLASH->TS1  = ((__EPPARA0__)>>18)&0x3FF;    \
                                                            FLASH->TS3  = ((__EPPARA0__)>>9)&0x1FF;      \
                                                            FLASH->TS2P = (__EPPARA1__)&0x1FF;           \
                                                            FLASH->TPS3 = ((__EPPARA1__)>>16)&0xFFF;    \
                                                            FLASH->PERTPE = (__EPPARA2__)&0x3FFFF;      \
                                                            FLASH->SMERTPE = (__EPPARA3__)&0x3FFFF;     \
                                                            FLASH->PRGTPE = (__EPPARA4__)&0xFFFF;       \
                                                            FLASH->PRETPE = ((__EPPARA4__)>>16)&0x3FFF; \
                                                         } while(0U)

#define __HAL_FLASH_IS_INVALID_TIMMING_SEQUENCE(_INDEX_)  (((FLASH->TS0)     !=  ((*(uint32_t *)(_FlashTimmingParam[_INDEX_]))&0x1FF))          ||  \
                                                           ((FLASH->TS1)     != (((*(uint32_t *)(_FlashTimmingParam[_INDEX_]))>>18)&0x3FF))    ||  \
                                                           ((FLASH->TS3)     != (((*(uint32_t *)(_FlashTimmingParam[_INDEX_]))>>9)&0x1FF))      ||  \
                                                           ((FLASH->TS2P)    !=  ((*(uint32_t *)(_FlashTimmingParam[_INDEX_]+4))&0x1FF))        ||  \
                                                           ((FLASH->TPS3)    != (((*(uint32_t *)(_FlashTimmingParam[_INDEX_]+4))>>16)&0xFFF))  ||  \
                                                           ((FLASH->PERTPE)  !=  ((*(uint32_t *)(_FlashTimmingParam[_INDEX_]+8))&0x3FFFF))     ||  \
                                                           ((FLASH->SMERTPE) !=  ((*(uint32_t *)(_FlashTimmingParam[_INDEX_]+12))&0x3FFFF))    ||  \
                                                           ((FLASH->PRGTPE)  !=  ((*(uint32_t *)(_FlashTimmingParam[_INDEX_]+16))&0xFFFF))     ||  \
                                                           ((FLASH->PRETPE)  != (((*(uint32_t *)(_FlashTimmingParam[_INDEX_]+16))>>16)&0x3FFF)))

#define __HAL_FLASH_TIMMING_SEQUENCE_CONFIG() do{                                                                            \
                                                uint32_t tmpreg = (RCC->ICSCR & RCC_ICSCR_HSI_FS) >> RCC_ICSCR_HSI_FS_Pos;   \
                                                if (__HAL_FLASH_IS_INVALID_TIMMING_SEQUENCE(tmpreg))                         \
                                                {                                                                            \
                                                  __HAL_FLASH_TIME_REG_SET((*(uint32_t *)(_FlashTimmingParam[tmpreg])),      \
                                                                           (*(uint32_t *)(_FlashTimmingParam[tmpreg]+4)),    \
                                                                           (*(uint32_t *)(_FlashTimmingParam[tmpreg]+8)),    \
                                                                           (*(uint32_t *)(_FlashTimmingParam[tmpreg]+12)),   \
                                                                           (*(uint32_t *)(_FlashTimmingParam[tmpreg]+16)));  \
                                                }                                                                            \
                                              }while(0U)
/**
  * @}
  */

/**
  * @}
  */

/* Include FLASH HAL Extended module */
/* Exported variables --------------------------------------------------------*/
/** @defgroup FLASH_Exported_Variables FLASH Exported Variables
  * @{
  */
extern FLASH_ProcessTypeDef pFlash;
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup FLASH_Exported_Functions
  * @{
  */

/* Program operation functions  ***********************************************/
/** @addtogroup FLASH_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef  HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint32_t *DataAddr );
HAL_StatusTypeDef  HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t Address, uint32_t *DataAddr);
HAL_StatusTypeDef  HAL_FLASH_PageProgram(uint32_t Address, uint32_t *DataAddr );
HAL_StatusTypeDef  HAL_FLASH_PageProgram_IT(uint32_t Address, uint32_t *DataAddr);
/* FLASH IRQ handler method */
void               HAL_FLASH_IRQHandler(void);
/* Callbacks in non blocking modes */
void               HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue);


void               HAL_FLASH_OperationErrorCallback(uint32_t ReturnValue);
HAL_StatusTypeDef  HAL_FLASH_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *PageError);
HAL_StatusTypeDef  HAL_FLASH_Erase_IT(FLASH_EraseInitTypeDef *pEraseInit);

#define HAL_FLASHEx_Erase        HAL_FLASH_Erase
#define HAL_FLASHEx_Erase_IT     HAL_FLASH_Erase_IT
/**
  * @}
  */

/* Peripheral Control functions  **********************************************/
/** @addtogroup FLASH_Exported_Functions_Group2
  * @{
  */
HAL_StatusTypeDef  HAL_FLASH_Unlock(void);
HAL_StatusTypeDef  HAL_FLASH_Lock(void);
/* Option bytes control */
HAL_StatusTypeDef  HAL_FLASH_OB_Unlock(void);
HAL_StatusTypeDef  HAL_FLASH_OB_Lock(void);
HAL_StatusTypeDef  HAL_FLASH_OB_Launch(void);
HAL_StatusTypeDef  HAL_FLASH_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit);
void               HAL_FLASH_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit);
HAL_StatusTypeDef  HAL_FLASH_OBBOOTProgram(FLASH_OBBootProgramInitTypeDef *pBOOTInit);
void               HAL_FLASH_OBBOOTGetConfig(FLASH_OBBootProgramInitTypeDef *pBOOTInit);
/**
  * @}
  */

/* Peripheral State functions  ************************************************/
/** @addtogroup FLASH_Exported_Functions_Group3
  * @{
  */
uint32_t HAL_FLASH_GetError(void);
/**
  * @}
  */

/**
  * @}
  */

/* Private types --------------------------------------------------------*/
/** @defgroup FLASH_Private_types FLASH Private Types
  * @{
  */
HAL_StatusTypeDef  FLASH_WaitForLastOperation(uint32_t Timeout);
/**
  * @}
  */

/* Private constants --------------------------------------------------------*/
/** @defgroup FLASH_Private_Constants FLASH Private Constants
  * @{
  */
#define FLASH_TIMEOUT_VALUE             1000U          /*!< FLASH Execution Timeout, 1 s */

#define FLASH_TYPENONE                  0x00000000U    /*!< No Programmation Procedure On Going */

#define FLASH_FLAG_SR_ERROR             (FLASH_FLAG_OPTVERR  | FLASH_FLAG_WRPERR)     /*!< All SR error flags */

#define FLASH_FLAG_SR_CLEAR             (FLASH_FLAG_SR_ERROR | FLASH_SR_EOP)
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup FLASH_Private_Macros FLASH Private Macros
 *  @{
 */
#define IS_FLASH_MAIN_MEM_ADDRESS(__ADDRESS__)         (((__ADDRESS__) >= (FLASH_BASE)) && ((__ADDRESS__) <= (FLASH_BASE + FLASH_SIZE - 1UL)))

#define IS_FLASH_PROGRAM_MAIN_MEM_ADDRESS(__ADDRESS__) (((__ADDRESS__) >= (FLASH_BASE)) && ((__ADDRESS__) <= (FLASH_BASE + FLASH_SIZE - 8UL)))

#define IS_FLASH_PROGRAM_ADDRESS(__ADDRESS__)          (IS_FLASH_PROGRAM_MAIN_MEM_ADDRESS(__ADDRESS__))

#define IS_FLASH_NB_PAGES(__ADDRESS__, __VALUE__)      (((__ADDRESS__) >= (FLASH_BASE)) && ((__ADDRESS__ + (__VALUE__*FLASH_PAGE_SIZE) - 1) <= (FLASH_BASE + FLASH_SIZE - 1UL)))

#define IS_FLASH_NB_SECTORS(__ADDRESS__, __VALUE__)    (((__ADDRESS__) >= (FLASH_BASE)) && ((__ADDRESS__ + (__VALUE__*FLASH_SECTOR_SIZE) - 1) <= (FLASH_BASE + FLASH_SIZE - 1UL)))

#define IS_FLASH_FAST_PROGRAM_ADDRESS(__ADDRESS__)     (((__ADDRESS__) >= (FLASH_BASE)) && ((__ADDRESS__) <= (FLASH_BASE + FLASH_SIZE - 256UL)))

#define IS_FLASH_PAGE(__PAGE__)                        ((__PAGE__) < FLASH_PAGE_NB)

#define IS_FLASH_BANK(__BANK__)                        ((__BANK__) == 0x00UL)

#define IS_FLASH_TYPEERASE(__VALUE__)                  (((__VALUE__) == FLASH_TYPEERASE_PAGEERASE) || \
                                                        ((__VALUE__) == FLASH_TYPEERASE_SECTORERASE) || \
                                                        ((__VALUE__) == FLASH_TYPEERASE_MASSERASE))

#define IS_FLASH_TYPEPROGRAM(__VALUE__)                ((__VALUE__) == FLASH_TYPEPROGRAM_PAGE)

#define IS_FLASH_TIMECONFIG_CLOCK(__VALUE__)           (((__VALUE__) == FLASH_PROGRAM_ERASE_CLOCK_24MHZ) || \
                                                        ((__VALUE__) == FLASH_PROGRAM_ERASE_CLOCK_48MHZ))

#define IS_OPTIONBYTE(__VALUE__)                       ((((__VALUE__) & OPTIONBYTE_ALL) != 0x00U) && \
                                                       (((__VALUE__) & ~OPTIONBYTE_ALL) == 0x00U))
                                                       
#define IS_OB_BOOTTYPE(__VALUE__)                      (((__VALUE__) == OB_BOOT_MODE_MAINFLASH) || \
                                                        ((__VALUE__) == OB_BOOT_MODE_SRAM) || \
                                                        ((__VALUE__) == OB_BOOT_MODE_LOADFLASH))
                                                        
#define IS_OB_BOOTSIZE(__VALUE__)                      (((__VALUE__) == OB_BOOT_SIZE_NONE) || \
                                                        ((__VALUE__) == OB_BOOT_SIZE_1K) || \
                                                        ((__VALUE__) == OB_BOOT_SIZE_2K) || \
                                                        ((__VALUE__) == OB_BOOT_SIZE_3K) || \
                                                        ((__VALUE__) == OB_BOOT_SIZE_4K))

#define IS_OB_USER_TYPE(__TYPE__)                      ((((__TYPE__) & OB_USER_ALL) != 0x00U) && \
                                                        (((__TYPE__) & ~OB_USER_ALL) == 0x00U))

#define IS_OB_USER_CONFIG(__TYPE__,__CONFIG__)         ((~(__TYPE__) & (__CONFIG__)) == 0x00U)

#if defined(FLASH_PCROP_SUPPORT)
#define IS_OB_PCROP_CONFIG(__CONFIG__)                 (((__CONFIG__) & ~(OB_PCROP_ZONE_A | OB_PCROP_ZONE_B | OB_PCROP_RDP_ERASE)) == 0x00U)
#endif

#if defined(FLASH_SECURABLE_MEMORY_SUPPORT)
#define IS_OB_SEC_BOOT_LOCK(__VALUE__)                 (((__VALUE__) == OB_BOOT_ENTRY_FORCED_NONE) || ((__VALUE__) == OB_BOOT_ENTRY_FORCED_FLASH))

#define IS_OB_SEC_SIZE(__VALUE__)                      ((__VALUE__) < (FLASH_PAGE_NB + 1U))
#endif

#define IS_FLASH_LATENCY(__LATENCY__)                  (((__LATENCY__) == FLASH_LATENCY_0) || \
                                                        ((__LATENCY__) == FLASH_LATENCY_1))

#define IS_WRPSTATE(__VALUE__)                         (((__VALUE__) == OB_WRPSTATE_DISABLE) || \
                                                        ((__VALUE__) == OB_WRPSTATE_ENABLE))

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __PY32F002B_HAL_FLASH_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
