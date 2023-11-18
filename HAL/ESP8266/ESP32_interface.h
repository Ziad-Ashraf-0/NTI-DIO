/*
 * ESP32_interface.h
 *
 * Created: 11/17/2023 11:29:35 PM
 *  Author: zashr
 */ 


#ifndef ESP32_INTERFACE_H_
#define ESP32_INTERFACE_H_

/* Connection Mode */
#define SINGLE				0
#define MULTIPLE			1

/* Application Mode */
#define NORMAL				0
#define TRANSPERANT			1

/* Application Mode */
#define STATION				1
#define ACCESSPOINT			2
#define BOTH_STATION_AND_ACCESPOINT	3

/* Select Demo */
#define RECEIVE_DEMO		/* Define RECEIVE demo */
//#define SEND_DEMO			/* Define SEND demo */

/* Define Required fields shown below */
#define DOMAIN				"api.thingspeak.com"
#define PORT				"80"
#define API_WRITE_KEY		"C7JFHZY54GLCJY38"
#define CHANNEL_ID			"119922"

#define SSID				"ssid"
#define PASSWORD			"password"

enum ESP8266_RESPONSE_STATUS{
	ESP8266_RESPONSE_WAITING,
	ESP8266_RESPONSE_FINISHED,
	ESP8266_RESPONSE_TIMEOUT,
	ESP8266_RESPONSE_BUFFER_FULL,
	ESP8266_RESPONSE_STARTING,
	ESP8266_RESPONSE_ERROR
};

enum ESP8266_CONNECT_STATUS {
	ESP8266_CONNECTED_TO_AP,
	ESP8266_CREATED_TRANSMISSION,
	ESP8266_TRANSMISSION_DISCONNECTED,
	ESP8266_NOT_CONNECTED_TO_AP,
	ESP8266_CONNECT_UNKNOWN_ERROR
};

enum ESP8266_JOINAP_STATUS {
	ESP8266_WIFI_CONNECTED,
	ESP8266_CONNECTION_TIMEOUT,
	ESP8266_WRONG_PASSWORD,
	ESP8266_NOT_FOUND_TARGET_AP,
	ESP8266_CONNECTION_FAILED,
	ESP8266_JOIN_UNKNOWN_ERROR
};


void ESP8266_Init(void);
u8 ESP8266_Begin();
u8 ESP8266_WIFIMode(u8 _mode);
u8 ESP8266_ConnectionMode(u8 Mode);
u8 ESP8266_ApplicationMode(u8 Mode);
u8 ESP8266_connected();
u8 ESP8266_JoinAccessPoint(char* _SSID, char* _PASSWORD);
u8 ESP8266_Start(u8 _ConnectionNumber, char* Domain, char* Port);
u8 ESP8266_Send(char* Data);
u16 Read_Data(char* _buffer);



#endif /* ESP32_INTERFACE_H_ */