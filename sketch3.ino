#include <WiFi.h>
#include <esp_now.h>

void formatMacAddress(const uint8_t *macAddress, char *buffer, int len) {
  snprintf(buffer, len, "%02x:%02x:%02x:%02x:%02x:%02x",
  macAddress[0], macAddress[1], macAddress[2], macAddress[3], macAddress[4], macAddress[5]);
}

void receiveCallBack(const uint8_t *macAddress, const uint8_t *data, int dataLen) {
  char buffer[ESP_NOW_MAX_DATA_LEN + 1];
  int msgLen = min(ESP_NOW_MAX_DATA_LEN, dataLen);
  strncpy(buffer, (const char*) data, msgLen);

  buffer[msgLen] = 0;

  char macStr[18];
  formatMacAddress(macAddress, macStr, 18);

  Serial.printf("%s sayed %s", macStr, buffer);
}

void sentCallBack(const uint8_t *macAddress, esp_now_send_status_t status) {
  char macStr[18];
  formatMacAddress(macAddress, macStr, 18);
  // Serial.print("Last Packet Sent to : ");
  // Serial.println(macStr);
  Serial.print("Message ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Sent Successfully" : "Sending Proccess Failed!");
}

void broadCast(const String &message) {
  uint8_t macAddress[] = {0xEC, 0x62, 0x60, 0x94, 0xC7, 0xA4};
  //EC:62:60:9C:E7:4C
  esp_now_peer_info_t peerInfo = {};
  memcpy(&peerInfo.peer_addr, macAddress, 6);
  if(!esp_now_is_peer_exist(macAddress)) {
    esp_now_add_peer(&peerInfo);
  }

  esp_err_t result = esp_now_send(macAddress, (const uint8_t *)message.c_str(), message.length());

  if (result == ESP_OK) {}
  else if (result == ESP_ERR_ESPNOW_NOT_INIT)
  {
    Serial.println("ESP-NOW not Init.");
  }
  else if (result == ESP_ERR_ESPNOW_ARG)
  {
    Serial.println("Invalid Argument");
  }
  else if (result == ESP_ERR_ESPNOW_INTERNAL)
  {
    Serial.println("Internal Error");
  }
  else if (result == ESP_ERR_ESPNOW_NO_MEM)
  {
    Serial.println("ESP_ERR_ESPNOW_NO_MEM");
  }
  else if (result == ESP_ERR_ESPNOW_NOT_FOUND)
  {
    Serial.println("Peer not found.");
  }
  else
  {
    Serial.println("Unknown error");
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_MODE_STA);
  Serial.println("ESP_NOW STARTED");

  WiFi.disconnect();

  if(esp_now_init() == ESP_OK) {
    Serial.println("ESP_NOW Init Successful");
    esp_now_register_recv_cb(receiveCallBack);
    esp_now_register_send_cb(sentCallBack);
  } else {
    Serial.println("ESP_NOW Init Failed");
    delay(5000);
    ESP.restart();
  }
}

void loop() {
  while(Serial.available() == 0) {}
  String msg = Serial.readString();

  Serial.print(WiFi.macAddress());
  Serial.print(" sayed ");
  Serial.print(msg);

  broadCast(msg);
}
