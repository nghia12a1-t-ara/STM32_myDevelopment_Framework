
#include "USART.h"
#include "ESP_AT_CMD.h"

/*#################################################################
*/
void ESP_AT_SendCmd(const uint8 * Command)
{
	const uint8 * pCmd = Command;
	USART_SendData(pCmd, len);
}

void ESP_AT_Init()
{
	/* Check if ESP available = AT Command */
	ESP_AT_SendCmd(ESP_AT_HEADER);
	ESP_AT_Wait();
	
	/* Restore Default Configuration = AT+RESTORE */
	ESP_Wifi_Restore();
}

/*#################################################################
*/
void ESP_Wifi_Restore(void)
{
	ESP_AT_SendCmd(ESP_AT_RESTORE);
	ESP_AT_Wait();
}