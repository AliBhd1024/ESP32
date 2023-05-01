#include <WiFi.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* host = "SERVER_IP_ADDRESS";
const int port = 80;

void setup() {
    Serial.begin(115200);

    // Connect to Wi-Fi network
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");
}

void loop() {
    // Connect to server
    WiFiClient client;
    if (client.connect(host, port)) {
        Serial.println("Connected to server");

        // Send request to server
        client.print("GET / HTTP/1.1\r\n");
        client.print("Host: ");
        client.print(host);
        client.print("\r\n");
        client.print("Connection: close\r\n");
        client.print("\r\n");

        // Wait for response from server
        while (client.connected()) {
            if (client.available()) {
                String response = client.readStringUntil('\r');
                Serial.println(response);
            }
        }

        // Close the connection
        client.stop();
        Serial.println("Server disconnected");
    } else {
        Serial.println("Connection failed");
    }

    // Wait for a few seconds before sending the next request
    delay(5000);
}
