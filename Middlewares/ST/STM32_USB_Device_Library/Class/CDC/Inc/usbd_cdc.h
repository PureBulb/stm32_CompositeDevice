/**
 ******************************************************************************
 * @file    usbd_cdc.h
 * @author  MCD Application Team
 * @brief   header file for the usbd_cdc.c file.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                      www.st.com/SLA0044
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_CDC_H
#define __USB_CDC_H

#include <stdint.h>

#include "usbd_conf.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "usbd_ioreq.h"

/** @addtogroup STM32_USB_DEVICE_LIBRARY
 * @{
 */

/** @defgroup usbd_cdc
 * @brief This file is the Header file for usbd_cdc.c
 * @{
 */

/** @defgroup usbd_cdc_Exported_Defines
 * @{
 */
#define CDC_IN_EP             0x81U /* EP1 for data IN */
#define CDC_OUT_EP            0x01U /* EP1 for data OUT */
#define CDC_CMD_EP            0x82U /* EP2 for CDC commands */

#define CUSTOM_HID_EPIN_ADDR  0x83U
#define CUSTOM_HID_EPIN_SIZE  0x02U

#define CUSTOM_HID_EPOUT_ADDR 0x02U
#define CUSTOM_HID_EPOUT_SIZE 0x02U

#ifndef CDC_HS_BINTERVAL
#define CDC_HS_BINTERVAL 0x10U
#endif /* CDC_HS_BINTERVAL */

#ifndef CDC_FS_BINTERVAL
#define CDC_FS_BINTERVAL        0x10U
#define CUSTOM_HID_FS_BINTERVAL 0x5
#endif /* CDC_FS_BINTERVAL */

/* CDC Endpoints parameters: you can fine tune these values depending on the
 * needed baudrates and performance. */
#define CDC_DATA_HS_MAX_PACKET_SIZE   512U /* Endpoint IN & OUT Packet size */
#define CDC_DATA_FS_MAX_PACKET_SIZE   64U /* Endpoint IN & OUT Packet size */
#define CDC_CMD_PACKET_SIZE           8U /* Control Endpoint Packet size */

#define USB_CDC_CONFIG_DESC_SIZ       107U
#define CDC_DATA_HS_IN_PACKET_SIZE    CDC_DATA_HS_MAX_PACKET_SIZE
#define CDC_DATA_HS_OUT_PACKET_SIZE   CDC_DATA_HS_MAX_PACKET_SIZE

#define CDC_DATA_FS_IN_PACKET_SIZE    CDC_DATA_FS_MAX_PACKET_SIZE
#define CDC_DATA_FS_OUT_PACKET_SIZE   CDC_DATA_FS_MAX_PACKET_SIZE

/*---------------------------------------------------------------------*/
/*  CDC definitions                                                    */
/*---------------------------------------------------------------------*/
#define CDC_SEND_ENCAPSULATED_COMMAND 0x00U
#define CDC_GET_ENCAPSULATED_RESPONSE 0x01U
#define CDC_SET_COMM_FEATURE          0x02U
#define CDC_GET_COMM_FEATURE          0x03U
#define CDC_CLEAR_COMM_FEATURE        0x04U
#define CDC_SET_LINE_CODING           0x20U
#define CDC_GET_LINE_CODING           0x21U
#define CDC_SET_CONTROL_LINE_STATE    0x22U
#define CDC_SEND_BREAK                0x23U

#define CUSTOM_HID_DESCRIPTOR_TYPE    0x21U
#define CUSTOM_HID_REPORT_DESC        0x22U
#define USB_CUSTOM_HID_DESC_SIZ       9U
    /**
     * @}
     */

#define INTERFACE_MAX_EP_NUM          3
#define CUSTOM_HID_REQ_SET_PROTOCOL          0x0BU
#define CUSTOM_HID_REQ_GET_PROTOCOL          0x03U

#define CUSTOM_HID_REQ_SET_IDLE              0x0AU
#define CUSTOM_HID_REQ_GET_IDLE              0x02U

#define CUSTOM_HID_REQ_SET_REPORT            0x09U
#define CUSTOM_HID_REQ_GET_REPORT            0x01U
    /** @defgroup USBD_CORE_Exported_TypesDefinitions
     * @{
     */

    /**
     * @}
     */
    typedef struct
    {
        uint32_t bitrate;
        uint8_t format;
        uint8_t paritytype;
        uint8_t datatype;
    } USBD_CDC_LineCodingTypeDef;

    typedef struct _USBD_CDC_Itf
    {
        uint8_t *pReport;
        int8_t (*Init)(void);
        int8_t (*DeInit)(void);
        int8_t (*Control)(uint8_t cmd, uint8_t *pbuf, uint16_t length);
        int8_t (*Receive)(uint8_t *Buf, uint32_t *Len);
        uint8_t interfaceEpAddr[INTERFACE_MAX_EP_NUM];
        uint8_t interfaceEpAttr[INTERFACE_MAX_EP_NUM];
        uint8_t endpointSize;
        uint8_t interfaceClassType[INTERFACE_MAX_EP_NUM];
        uint8_t interfaceNumbers[USBD_MAX_NUM_INTERFACES];
        uint8_t interfaceSize;
        int8_t isRegistered;
    } USBD_CDC_ItfTypeDef;

    typedef struct
    {
        uint32_t
            data[CDC_DATA_HS_MAX_PACKET_SIZE / 4U]; /* Force 32bits alignment */
        uint8_t CmdOpCode;
        uint8_t CmdLength;
        uint8_t *RxBuffer;
        uint8_t *TxBuffer;
        uint32_t RxLength;
        uint32_t TxLength;

        __IO uint32_t TxState;
        __IO uint32_t RxState;
        uint8_t              Report_buf[USBD_CUSTOMHID_OUTREPORT_BUF_SIZE];
  
        uint32_t             Protocol;
        uint32_t             IdleState;
        uint32_t             AltSetting;
        uint32_t             IsReportAvailable;

    } USBD_CDC_HandleTypeDef;

    /** @defgroup USBD_CORE_Exported_Macros
     * @{
     */

    /**
     * @}
     */

    /** @defgroup USBD_CORE_Exported_Variables
     * @{
     */

    extern USBD_ClassTypeDef USBD_CDC;
#define USBD_CDC_CLASS &USBD_CDC
    /**
     * @}
     */

    /** @defgroup USB_CORE_Exported_Functions
     * @{
     */
    uint8_t USBD_CDC_RegisterInterface(USBD_HandleTypeDef *pdev,
                                       USBD_CDC_ItfTypeDef *fops);

    uint8_t USBD_CDC_SetTxBuffer(USBD_HandleTypeDef *pdev, uint8_t *pbuff,
                                 uint16_t length);

    uint8_t USBD_CDC_SetRxBuffer(USBD_HandleTypeDef *pdev, uint8_t *pbuff);

    uint8_t USBD_CDC_ReceivePacket(USBD_HandleTypeDef *pdev);

    uint8_t USBD_CDC_TransmitPacket(USBD_HandleTypeDef *pdev);
    /**
     * @}
     */

#ifdef __cplusplus
}
#endif

#endif /* __USB_CDC_H */
/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
