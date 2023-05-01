#include <WiFi.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

WiFiServer server(80);

void setup() {
    Serial.begin(115200);

    // Connect to Wi-Fi network
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");

    // Start server
    server.begin();
}

void loop() {
    // Check if a client has connected
    WiFiClient client = server.available();
    if (client) {
        Serial.println("New client connected");

        // Wait for data from client
        while (client.connected()) {
            if (client.available()) {
                String request = client.readStringUntil('\r');
                Serial.println(request);

                // Send response to client
                client.println("HTTP/1.1 200 OK");
                client.println("Content-Type: text/html");
                client.println("");
                client.println("<html><body><h1>Hello, World!</h1></body></html>");
                break;
            }
        }

        // Close the connection
        client.stop();
        Serial.println("Client disconnected");
    }
}
