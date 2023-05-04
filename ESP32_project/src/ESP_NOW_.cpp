#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

typedef uint8_t MAC_ADDRESS[6];

String lastReceivedPacket = "\0";

void formatMacAddress(const MAC_ADDRESS macAddress, char* buffer, int len) 
// convert mac to standard format
{
    snprintf(buffer, len, "%02x:%02x:%02x:%02x:%02x:%02x",
    macAddress[0], macAddress[1], macAddress[2], macAddress[3], macAddress[4], macAddress[5]);
}

String getLastReceivedPacket() 
// get just received packet
{
    return lastReceivedPacket;
}

void receiveCallBack(const MAC_ADDRESS macAddress, const uint8_t *data, int dataLen) 
// receive call back func for esp_now library, no use for us
{
    char buffer[ESP_NOW_MAX_DATA_LEN + 1];
    int msgLen = min(ESP_NOW_MAX_DATA_LEN, dataLen);
    strncpy(buffer, (const char*) data, msgLen);

    buffer[msgLen] = 0;

    char macStr[18];
    formatMacAddress(macAddress, macStr, 18);

    lastReceivedPacket = buffer;
}

void sentCallBack(const MAC_ADDRESS macAddress, esp_now_send_status_t status) 
// send call back func for esp_now library, no use for us
{
    char macStr[18];
    formatMacAddress(macAddress, macStr, 18);
    Serial.print(">> Last Packet Sent to : ");
    Serial.println(macStr);
    Serial.print("\n>> Message ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Sent Successfully\n" : "Sending Proccess Failed!\n");
}

void broadCast(const String &message, MAC_ADDRESS macAddr)
// main func for sending message to macAddr
{
    esp_now_peer_info_t peerInfo = {};
    memcpy(&peerInfo.peer_addr, macAddr, 6);
    if(!esp_now_is_peer_exist(macAddr)) {
        esp_now_add_peer(&peerInfo);
    }

    esp_err_t result = esp_now_send(macAddr, (const uint8_t *)message.c_str(), message.length());

    switch (result) {
        case ESP_OK:
            break;
        case ESP_ERR_ESPNOW_NOT_INIT:
            Serial.println("\n*!* ESP-NOW not Init. *!*\n");
            break;
        case ESP_ERR_ESPNOW_ARG:
            Serial.println("\n*!* Invalid Argument *!*\n");
            break;
        case ESP_ERR_ESPNOW_INTERNAL:
            Serial.println("\n*!* Internal Error *!*\n");
            break;
        case ESP_ERR_ESPNOW_NO_MEM:
            Serial.println("\n*!* ESP_ERR_ESPNOW_NO_MEM *!* \n");
            break;
        case ESP_ERR_ESPNOW_NOT_FOUND:
            Serial.println("\n*!* Peer not found. *!*\n");
            break;
        default:
            Serial.println("\n*!* Unknown error *!*\n");
            break;
    }
}

void initESPNOW() 
// initialize ESP_NOW protocol
{
    Serial.println("\n** ESP_NOW started **\n");                       
    WiFi.mode(WIFI_MODE_STA);
    
    Serial.print(">> Your mac address: ");
    Serial.print(WiFi.macAddress());
    Serial.print("\n");

    WiFi.disconnect();

    if(esp_now_init() == ESP_OK) {
        esp_now_register_recv_cb(receiveCallBack);
        esp_now_register_send_cb(sentCallBack);
        Serial.println("** ESP_NOW init successful **\n");
    } else {
        Serial.println("** ESP_NOW init failed **\n");
        delay(500);
        ESP.restart();
    }
}