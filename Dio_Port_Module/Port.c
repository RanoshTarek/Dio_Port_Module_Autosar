/******************************************************************************
 *
 * Module: PORT
 *
 * File Name: Port.c
 *
 * Description: Source file for PORT Module.
 *
 * Author: Rana Tarek
 ******************************************************************************/

#include "Port.h"
#include "Dio_Regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#endif
/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/
/*responsible the port number and pin's number related to port.*/
STATIC void Port_getPinNumberAndPortNumber(Port_PinType Pin,
		Port_PinType *Pin_Num, Port_PinType *Port_Num);
/*responsible the set Configuration of every pin.*/
STATIC void Port_setConfiguration();
/*responsible the set Direction of every pin.*/
STATIC void Port_setDirection();

/*******************************************************************************
 *                      Variable (Private)                                     *
 *******************************************************************************/
STATIC Port_ConfigChannel *Port_PortChannels = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

/************************************************************************************
 * Service Name: Port_Init
 * Service ID[hex]: 0x00
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): ConfigPtr - Pointer to configuration set.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initializes the Port Driver module.
 ************************************************************************************/
void Port_Init(const Port_ConfigType *ConfigPtr) {
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr) {
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
		PORT_E_UNINIT);
	} else
#endif
	{
		/*
		 * Set the module state to initialized and point to the PB configuration structure using a global pointer.
		 * This global pointer is global to be used by other functions to read the PB configuration structures
		 * then to set direction and initial value for pins
		 */
		Port_PortChannels = ConfigPtr->Channel; /* address of the first Channels structure --> Channels[0] */
		Port_setConfiguration();
		Port_Status = PORT_INITIALIZED;
	}
}

/************************************************************************************
 * Service Name: Port_SetPinDirection
 * Service ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Pin       - Port Pin ID number.
 * 					Direction - Port Pin Direction
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Sets the port pin direction.
 ************************************************************************************/
#if(PORT_SET_PIN_DIRECTION_API==STD_ON)
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction) {
	Port_PinType *DDR_Ptr = NULL_PTR;
	Port_PinType Pin_Num;
	Port_PinType Port_Num;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == Port_PortChannels) {
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
		PORT_SET_PIN_DIRECTION_SID,
		PORT_E_UNINIT);
	} else if (Pin > PINS_NUM) {
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
		PORT_SET_PIN_DIRECTION_SID,
		PORT_E_PARAM_PIN);
	} else
#endif
	{
		/* 1-check pin to get port number and pin number related to port by check range of every port
		 * 2-get direction dependence on port number
		 * 3-check and set Direction is input or output*/
		Port_getPinNumberAndPortNumber(Pin, &Pin_Num, &Port_Num);
		switch (Port_Num) {
		case 0:
			DDR_Ptr = &DDRA_REG;
			break;
		case 1:
			DDR_Ptr = &DDRB_REG;
			break;
		case 2:
			DDR_Ptr = &DDRC_REG;
			break;
		case 3:
			DDR_Ptr = &DDRD_REG;
			break;
		}
		/*
		 * 1-get position of configured pin inside Port_PortChannels
		 * 2-check if find element if not found report error
		 * 3-check if changeable yes set direction
		 * 4-check if changeable no  report error
		 * */
		uint8 position = -1;
		for (int i = 0; i < PORT_CONFIGURED_CHANNLES; ++i) {
			if (Port_PortChannels[i].pin_num == Pin_Num
					&& Port_PortChannels[i].port == Port_Num) {
				position = i;
			}
		}

		if (-1 != position) {
			if (YES == Port_PortChannels[position].directionChangeable) {
				if (PORT_PIN_IN == Direction) {
					CLEAR_BIT(*DDR_Ptr, Pin_Num);
				} else if (PORT_PIN_OUT == Direction) {
					SET_BIT(*DDR_Ptr, Pin_Num);
				} else {

				}

			} else if (NO == Port_PortChannels[position].directionChangeable) {
#if (PORT_DEV_ERROR_DETECT == STD_ON)
				Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_DIRECTION_SID,
				PORT_E_DIRECTION_UNCHANGEABLE);
#endif
			} else {

			}
		} else {
#if (PORT_DEV_ERROR_DETECT == STD_ON)
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
			PORT_SET_PIN_DIRECTION_SID,
			PORT_E_PARAM_PIN);
#endif
		}
	}
}
#endif
/************************************************************************************
 * Service Name: Port_RefreshPortDirection
 * Service ID[hex]: 0x02
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: SRefreshes port direction.
 ************************************************************************************/
void Port_RefreshPortDirection(void) {
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if (NULL_PTR == Port_PortChannels) {
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
		PORT_Refresh_PORT_DIRECTION_SID,
		PORT_E_UNINIT);
	} else
#endif
	{
		Port_setDirection();
	}
}

/************************************************************************************
 * Service Name: Port_SetPinMode
 * Service ID[hex]: 0x04
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Pin  - Port Pin ID number.
 * 					Mode - New Port Pin mode to be set on port pin.
 * Parameters (inout): None
 * Parameters (out)  : None
 * Return value: None
 * Description: Sets the port pin mode..
 ************************************************************************************/
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode) {
	Port_PinType Pin_Num;
	Port_PinType Port_Num;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if (NULL_PTR == Port_PortChannels) {
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
		PORT_SET_PIN_MODE_SID,
		PORT_E_UNINIT);
	} else if (Pin > PINS_NUM) {
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
		PORT_SET_PIN_MODE_SID,
		PORT_E_PARAM_PIN);
	} else
#endif

	{
		/* 1-check pin to get port number and pin number related to port by check range of every port
		 * 2-get direction dependence on port number*/
		Port_getPinNumberAndPortNumber(Pin, &Pin_Num, &Port_Num);
		/* 1-get position of configured pin inside Port_PortChannels
		 * 2-check if find element if not found report error
		 * 3-check if changeable yes set Mode
		 * 4-check if changeable no  report error
		 * */
		uint8 position = -1;
		for (int i = 0; i < PORT_CONFIGURED_CHANNLES; ++i) {
			if (Port_PortChannels[i].pin_num == Pin_Num
					&& Port_PortChannels[i].port == Port_Num) {
				position = i;
			}
		}

		if (-1 != position) {
			if (CHANGABLE == Port_PortChannels[position].modeTypeChangeable) {
				/* not applicable in AVR MicroController */
			} else if (NOT_CHANGABLE
					== Port_PortChannels[position].modeTypeChangeable) {
#if (PORT_DEV_ERROR_DETECT == STD_ON)
				Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID,
				PORT_E_MODE_UNCHANGEABLE);
#endif
			} else {

			}
		} else {
#if (PORT_DEV_ERROR_DETECT == STD_ON)
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
			PORT_SET_PIN_MODE_SID,
			PORT_E_PARAM_PIN);
#endif
		}
	}
}
/************************************************************************************
 * Service Name: Port_GetVersionInfo
 * Service ID[hex]: 0x03
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): versioninfo - Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Returns the version information of this module.
 ************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo) {
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if (NULL_PTR == versioninfo) {
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
		PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
	} else
#endif
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16) PORT_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16) PORT_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8) PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8) PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8) PORT_SW_PATCH_VERSION;
	}
}

/************************************************************************************
 * Non AUTOSAR Function
 * Function Name: Port_getPinNumberAndPortNumber
 * Parameters (in): Pin
 * Parameters (inout): None
 * Parameters (out): Pin_Num  - Pointer to where to store Pin Number.
 * 					 Port_Num - Pointer to where to store Port Number.
 * Return value: None
 * Description: Returns the port number and pin's number related to port.
 ************************************************************************************/
STATIC void Port_getPinNumberAndPortNumber(Port_PinType Pin,
		Port_PinType *Pin_Num, Port_PinType *Port_Num) {
	/* 1-check pin number to get port number by check range of every port
	 * 2-get pin number related to port*/
	if (Pin >= PORTA_PIN_START && Pin <= PORTA_PIN_END) {
		*Port_Num = PORTA_NUM;
		*Pin_Num = Pin - PORTA_PIN_START;
	} else if (Pin >= PORTB_PIN_START && Pin <= PORTB_PIN_END) {
		*Port_Num = PORTB_NUM;
		*Pin_Num = Pin - PORTB_PIN_START;
	} else if (Pin >= PORTC_PIN_START && Pin <= PORTC_PIN_END) {
		*Port_Num = PORTC_NUM;
		*Pin_Num = Pin - PORTC_PIN_START;
	} else if (Pin >= PORTD_PIN_START && Pin <= PORTD_PIN_END) {
		*Port_Num = PORTD_NUM;
		*Pin_Num = Pin - PORTD_PIN_START;
	}
}
/************************************************************************************
 * Non AUTOSAR Function
 * Function Name: Port_setConfiguration
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: responsible the set Configuration of every pin.
 ************************************************************************************/
STATIC void Port_setConfiguration() {
	Port_PinType *Port_Ptr = NULL_PTR;
	Port_PinType *DDR_Ptr = NULL_PTR;
	for (int i = 0; i < PORT_CONFIGURED_CHANNLES; ++i) {
		switch (Port_PortChannels[i].port) {
		case 0:
			Port_Ptr = &PORTA_REG;
			DDR_Ptr = &DDRA_REG;
			break;
		case 1:
			Port_Ptr = &PORTB_REG;
			DDR_Ptr = &DDRB_REG;
			break;
		case 2:
			Port_Ptr = &PORTC_REG;
			DDR_Ptr = &DDRC_REG;
			break;
		case 3:
			Port_Ptr = &PORTD_REG;
			DDR_Ptr = &DDRD_REG;
			break;
		}
		/* 1-check and set Direction is input or output
		 * 2-if PIN Direction is Output the value of InitialValue is initial value high/low
		 * 3-if PIN Direction is Input  the value of InitialValue is Pull_up resistor enable/disable
		 */
		if (PORT_PIN_IN == Port_PortChannels[i].directionType) {
			CLEAR_BIT(*DDR_Ptr, Port_PortChannels[i].pin_num);
			//Enable/Disable Pull_up
			if (PIN_MODE_LOW == Port_PortChannels[i].initialValue) { //Disable Pull Up
				CLEAR_BIT(*Port_Ptr, Port_PortChannels[i].pin_num);
			} else if (PIN_MODE_High == Port_PortChannels[i].initialValue) { //Enable Pull Up
				SET_BIT(*Port_Ptr, Port_PortChannels[i].pin_num);
			} else {

			}

		} else if (PORT_PIN_OUT == Port_PortChannels[i].directionType) {
			SET_BIT(*DDR_Ptr, Port_PortChannels[i].pin_num);
			//SET initial value lOW/high
			if (PIN_MODE_LOW == Port_PortChannels[i].initialValue) { //SET initial value lOW
				CLEAR_BIT(*Port_Ptr, Port_PortChannels[i].pin_num);
			} else if (PIN_MODE_High == Port_PortChannels[i].initialValue) { //SET initial value HIGH
				SET_BIT(*Port_Ptr, Port_PortChannels[i].pin_num);
			} else {

			}

		} else {

		}
	}
}
/************************************************************************************
 * Non AUTOSAR Function
 * Function Name: Port_setDirection
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: responsible the set Direction of every pin.
 ************************************************************************************/
STATIC void Port_setDirection() {
	Port_PinType *DDR_Ptr = NULL_PTR;
	for (int i = 0; i < PORT_CONFIGURED_CHANNLES; ++i) {
		switch (Port_PortChannels[i].port) {
		case 0:
			DDR_Ptr = &DDRA_REG;
			break;
		case 1:
			DDR_Ptr = &DDRB_REG;
			break;
		case 2:
			DDR_Ptr = &DDRC_REG;
			break;
		case 3:
			DDR_Ptr = &DDRD_REG;
			break;
		}
		/*check and set Direction is input or output*/
		if (PORT_PIN_IN == Port_PortChannels[i].directionType) {
			CLEAR_BIT(*DDR_Ptr, Port_PortChannels[i].pin_num);

		} else if (PORT_PIN_OUT == Port_PortChannels[i].directionType) {
			SET_BIT(*DDR_Ptr, Port_PortChannels[i].pin_num);
		} else {

		}
	}
}

#endif
