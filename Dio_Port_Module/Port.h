/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for Port Module.
 *
 * Author: Rana Tarek
 ******************************************************************************/

#ifndef PORT_H_
#define PORT_H_
/* Id for the company in the AUTOSAR*/
#define PORT_VENDOR_ID    (70U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.3.1
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for PORT Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Std_Types.h does not match the expected version"
#endif

/* PORT Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
//#error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for Port INIT */
#define PORT_INIT_SID           			 (uint8)0x00

/*Service ID for Port Set Pin Direction*/
#define PORT_SET_PIN_DIRECTION_SID           (uint8)0x01

/*Service ID for Port Set Pin Direction*/
#define PORT_Refresh_PORT_DIRECTION_SID      (uint8)0x02

/*Service ID for PORT GetVersionInfo*/
#define PORT_GET_VERSION_INFO_SID       	 (uint8)0x03

/*Service ID for Set Pin Mode*/
#define PORT_SET_PIN_MODE_SID           	 (uint8)0x04

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* PORT code to report Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN               		 (uint8)0x0A

/* Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE  		 (uint8)0x0B

/* API Port_Init service called with wrong parameter */
#define PORT_E_INIT_FAILED             		 (uint8)0x0c

/* API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_PARAM_INVALID_MODE      		 (uint8)0x0D

/* API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE       		 (uint8)0x0E

/*API service called without module initialization*/
#define PORT_E_UNINIT                        (uint8)0x0F

/*APIs called with a Null Pointer*/
#define PORT_E_PARAM_POINTER           		 (uint8)0x10
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
/* Type definition for Port_PinType used by the Port APIs */
typedef uint8 Port_PinType;
/* Type definition for Port_PinModeType used by the Port APIs */
typedef uint8 Port_PinModelType;
/* Type definition for Port_PinModeTypeChangeable used by the Port APIs */
typedef uint8 Port_PinModeTypeChangeable;
/* Type definition for Port_PinDirectionType used by the Port APIs */
typedef enum {
	PORT_PIN_IN = STD_LOW, PORT_PIN_OUT = STD_HIGH
} Port_PinDirectionType;

/* Type definition for Port_PinInitialValue
 * if PIN Direction is Output the value of mode is initial value high/low
 * if PIN Direction is Input  the value of mode is Pull_up resistor enable/disable
 *  used by the Port APIs */
typedef enum {
	PIN_MODE_LOW = STD_LOW, PIN_MODE_High = STD_HIGH
} Port_PinInitialValue;
/* Type definition for Port_PinModeType
 * if PIN Direction is Output the value of mode is initial value high/low
 * if PIN Direction is Input  the value of mode is Pull_up resistor enable/disable
 *  used by the Port APIs */
typedef enum {
	CHANGABLE = STD_ON, NOT_CHANGABLE = STD_LOW
} Port_PinModeType;

typedef enum {
	YES = E_OK, NO = E_NOT_OK
} Port_PinDirectionChangeable;

typedef struct {
	Port_PinType port;
	Port_PinType pin_num;
	Port_PinDirectionType directionType;
	Port_PinInitialValue initialValue;
	Port_PinDirectionChangeable directionChangeable;
	Port_PinModeTypeChangeable modeTypeChangeable;
} Port_ConfigChannel;

typedef struct {
	Port_ConfigChannel Channel[PORT_CONFIGURED_CHANNLES];
} Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Function for PORT Initialization API */
void Port_Init(const Port_ConfigType *ConfigPtr);
/* Function for PORT Set Pin Direction API */
#if(PORT_SET_PIN_DIRECTION_API==STD_ON)
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
#endif
/* Function for Refresh Port Direction API */
void Port_RefreshPortDirection(void);
/* Function for Set Port Pin Mode API */
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);
/* Function for PORT Get Version Info API */
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo);
#endif
/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
/* Extern PB structures to be used by PORT and other modules */
extern const Port_ConfigType Port_Configuration;

#endif /* PORT_H_ */
