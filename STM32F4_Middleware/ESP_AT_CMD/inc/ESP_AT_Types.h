#ifndef __ESP_AT_TYPES__
#define __ESP_AT_TYPES__

/**
 * Define all AT Commands
 */
#define ESP_AT_HEADER			(const char *)("AT\r\n")
#define ESP_AT_RST				(const char *)("AT+RST\r\n")
#define ESP_AT_RESTORE			(const char *)("AT+RESTORE\r\n")
#define ESP_AT_EOF				(const char)('\r')
#define 

/**
 * Define Data Struct Types
 */
/* Define Wifi Modes */
typedef enum 
{
	ESP_WifiMode_Error			= 0,
	ESP_WifiMode_Station		= 1,
	ESP_WifiMode_SoftAP			= 2,
	ESP_WifiMode_Station_SoftAP	= 3,
} ESP_WifiMode_Types;

/* Define Wifi Status */
typedef enum
{
	ESP_WifiStatus_Error			= 0,
	ESP_WifiStatus_GotIP			= 2,
	ESP_WifiStatus_Connected		= 3,
	ESP_WifiStatus_Disconnected		= 4,
	ESP_WifiStatus_ConnectFail		= 5,
} ESP_WifiStatus_Types;



#endif	/* __ESP_AT_TYPES__ */
