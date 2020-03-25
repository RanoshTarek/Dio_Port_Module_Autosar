/******************************************************************************
 *
 * Module: PORT
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for Port Module.
 *
 * Author: Rana Tarek
 ******************************************************************************/
#ifndef PORT_CFG_H_
#define PORT_CFG_H_


#define PORT_CFG_SW_MAJOR_VERSION             		(1U)
#define PORT_CFG_SW_MINOR_VERSION             		(0U)
#define PORT_CFG_SW_PATCH_VERSION             		(0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     		(4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     		(0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION    		(3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                 		(STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                 	    (STD_ON)

/* Pre-compile option for presence of PORT_MODEL_CHANNEL_API API */
#define PORT_MODEL_CHANNEL_API           		    (STD_ON)

#define PORT_SET_PIN_DIRECTION_API         		    (STD_ON)
/* Number of the configured PORT Channels */
#define PORT_CONFIGURED_CHANNLES              		PINS_NUM


/* Configuration OF PORTS */
#define PORT_NUM 									(4U)
#define PINS_NUM									(32U)

/* Definition for PORTS Registers */
#define PORTA_REG									(*(volatile uint8 *)0x003B)/* Definition for PORTA Registers */
#define PORTB_REG									(*(volatile uint8 *)0x0038)/* Definition for PORTB Registers */
#define PORTC_REG									(*(volatile uint8 *)0x0035)/* Definition for PORTC Registers */
#define PORTD_REG									(*(volatile uint8 *)0x0032)/* Definition for PORTD Registers */


#define PINS_OF_PORT_NUM 							(8U)

#define PORTA_NUM				    				(0U)
#define PORTB_NUM									(1U)
#define PORTC_NUM				    				(2U)
#define PORTD_NUM									(3U)

//Port Pins Range
#define PORTA_PIN_START         					(0U)
#define PORTA_PIN_END           					(7U)

#define PORTB_PIN_START         					(8U)
#define PORTB_PIN_END           					(15U)

#define PORTC_PIN_START         					(16U)
#define PORTC_PIN_END           					(23U)

#define PORTD_PIN_START         					(24U)
#define PORTD_PIN_END           					(31U)

#define PORT_A_PIN_0 								(Port_PinType)0
#define PORT_A_PIN_1 								(Port_PinType)1
#define PORT_A_PIN_2 								(Port_PinType)2
#define PORT_A_PIN_3 								(Port_PinType)3
#define PORT_A_PIN_4 								(Port_PinType)4
#define PORT_A_PIN_5 								(Port_PinType)5
#define PORT_A_PIN_6 								(Port_PinType)6
#define PORT_A_PIN_7 								(Port_PinType)7

#define PORT_B_PIN_0 								(Port_PinType)0
#define PORT_B_PIN_1 								(Port_PinType)1
#define PORT_B_PIN_2 								(Port_PinType)2
#define PORT_B_PIN_3 								(Port_PinType)3
#define PORT_B_PIN_4 								(Port_PinType)4
#define PORT_B_PIN_5 								(Port_PinType)5
#define PORT_B_PIN_6 								(Port_PinType)6
#define PORT_B_PIN_7 								(Port_PinType)7

#define PORT_C_PIN_0 								(Port_PinType)0
#define PORT_C_PIN_1 								(Port_PinType)1
#define PORT_C_PIN_2 								(Port_PinType)2
#define PORT_C_PIN_3 								(Port_PinType)3
#define PORT_C_PIN_4 								(Port_PinType)4
#define PORT_C_PIN_5 								(Port_PinType)5
#define PORT_C_PIN_6 								(Port_PinType)6
#define PORT_C_PIN_7 								(Port_PinType)7

#define PORT_D_PIN_0 								(Port_PinType)0
#define PORT_D_PIN_1 								(Port_PinType)1
#define PORT_D_PIN_2 								(Port_PinType)2
#define PORT_D_PIN_3 								(Port_PinType)3
#define PORT_D_PIN_4 								(Port_PinType)4
#define PORT_D_PIN_5 								(Port_PinType)5
#define PORT_D_PIN_6 								(Port_PinType)6
#define PORT_D_PIN_7 								(Port_PinType)7

/* Channel Index in the array of structures in PORT_PBcfg.c */
#define PORTConf_LED1_CHANNEL_ID_INDEX        		(uint8)0x00
#define PORTConf_BUTTON1_CHANNEL_ID_INDEX     		(uint8)0x01

/* Port Configured Port ID's  */
#define PortConf_LED1_PORT_NUM                		PORTC_NUM /* PORTC */
#define PortConf_BUTTON1_PORT_NUM             		PORTA_NUM /* PORTA */

/* Port Configured Port ID's  */
#define PortConf_LED1_PIN_NUM                 		PORT_C_PIN_5
#define PortConf_BUTTON1_PIN_NUM              		PORT_D_PIN_2

/* Port Configured Port Direction  */
#define PortConf_LED1_PIN_DIRECTION          		PORT_PIN_OUT
#define PortConf_BUTTON1_PIN_DIRECTION        		PORT_PIN_IN

/* Port Configured Port Initial Value  */
#define PortConf_LED1_PIN_initial             		STD_ON /* initial value low */
#define PortConf_BUTTON1_PIN_RESISTOR         		STD_OFF /* Disable resistor */

/* Port Configured Direction Changeable   */
#define PortConf_LED1_PIN_DIRECTION_CHANGEABLE      YES/* changeable */
#define PortConf_BUTTON1_DIRECTION_CHANGEABLE       YES/* changeable */

/* Port Configured Mode Changeable   */
#define PortConf_LED1_PIN_MODE_CHANGEABLE           CHANGABLE/* changeable */
#define PortConf_BUTTON1_MODE_CHANGEABLE            CHANGABLE/* changeable */


/* Port Default value to Configure each pin */
#define PortConf_DEFAULT_PIN_DIRECTION  			PORT_PIN_OUT
#define PortConf_DEFAULT_PIN_INITIAL_VALUE	 		PIN_MODE_LOW
#define PortConf_DEFAULT_DIRECTION_CHANGEABLE  		YES
#define PortConf_DEFAULT_PIN_MODE_CHANGEABLE	    CHANGABLE
#endif /* PORT_CFG_H_ */
