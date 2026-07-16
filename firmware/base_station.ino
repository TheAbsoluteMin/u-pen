//base_solver code for external ESP32 to process pen packet data in real time

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <HTTPClient.h>

#define CANVAS_WIDTH 128
#define CANVAS_HEIGHT 32

const char* WIFI_SSID = "example_wifi_name";
const char* WIFI_PASSWORD = "example_wifi_password";
const char* AI_SOLVER_URL = "example_api_url.com";

//data packet structure
typedef struct {
    int16_t x_pos;
    int16_t y_pos;
    uint8_t is_pressed;
} SimplePoint;

uint8_t virtualCanvas[CANVAS_WIDTH][CANVAS_HEIGHT];
int16_t prevX = CANVAS_WIDTH / 4;
int16_t prevY = CANVAS_HEIGHT / 2;

//API solver function
String connectAndCallAI() {
    Serial.println("\nConnecting to Wi-Fi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    
    uint32_t startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi Connection Failed");
        return "Big Error";
    }
    Serial.println("\nConnected!");

    HTTPClient http;
    http.begin(AI_SOLVER_URL);
    http.addHeader("Content-Type", "application/json");

    String jsonPayload = "{\"width\":128,\"height\":32,\"strokes\":[";
    bool firstPoint = true;

    for (int x = 0; x < CANVAS_WIDTH; x++) {
        for (int y = 0; y < CANVAS_HEIGHT; y++) {
            if (virtualCanvas[x][y] == 1) {
                if (!firstPoint) jsonPayload += ",";
                jsonPayload += "{\"x\":" + String(x) + ",\"y\":" + String(y) + "}";
                firstPoint = false;
            }
        }
    }
    jsonPayload += "]}";

    int httpResponseCode = http.POST(jsonPayload);
    String resultString = "Error";

    if (httpResponseCode > 0) {
        String responseBody = http.getString();
        Serial.println("API Response: " + responseBody);
        
        resultString = responseBody;
    } else {
        Serial.printf("API HTTP POST Failure. Error Code: %d\n", httpResponseCode);
        resultString = "API Fail";
    }

    http.end();
    WiFi.disconnect(true);
    WiFi.mode(WIFI_STA);
    return resultString;
}

//get data packets
void OnDataRecv(const esp_now_recv_info *recvInfo, const uint8_t *incomingData, int len) {
    if (len == sizeof(SimplePoint)) {
        SimplePoint point;
        memcpy(&point, incomingData, sizeof(SimplePoint));

        int16_t curX = point.x_pos;
        int16_t curY = point.y_pos;

        if (point.is_pressed == 1) {
            Serial.printf("Drawing line from (%d,%d) to (%d,%d)\n", prevX, prevY, curX, curY);
            virtualCanvas[constrain(curX, 0, CANVAS_WIDTH-1)][constrain(curY, 0, CANVAS_HEIGHT-1)] = 1;
            prevX = curX;
            prevY = curY;
        } 
        else if (point.is_pressed == 0) {
            Serial.printf("Hover cursor to (%d,%d)\n", curX, curY);
            prevX = curX;
            prevY = curY;
        } 
        else if (point.is_pressed == 255) {
            //ask API
            Serial.println("Complete: 5 second inactivity. Asking API...");
            String solutionAnswer = connectAndCallAI();

            char replyPayloadBuffer[32];
            memset(replyPayloadBuffer, 0, sizeof(replyPayloadBuffer));
            solutionAnswer.toCharArray(replyPayloadBuffer, sizeof(replyPayloadBuffer) - 1);

            //send back answer to pen
            esp_now_init();

            esp_now_peer_info_t penPeer = {};
            memcpy(penPeer.peer_addr, recvInfo->src_addr, 6);
            penPeer.channel = 1;
            penPeer.encrypt = false;
            
            if (!esp_now_is_peer_exist(recvInfo->src_addr)) {
                esp_now_add_peer(&penPeer);
            }

            esp_now_send(recvInfo->src_addr, (uint8_t*)replyPayloadBuffer, strlen(replyPayloadBuffer) + 1);
            Serial.printf("Response Complete: Dispatched text string '%s' to Pen.\n", replyPayloadBuffer);

            //reset
            memset(virtualCanvas, 0, sizeof(virtualCanvas));
        }
    }
}

void setup() {
    Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    if (esp_now_init() == ESP_OK) {
        Serial.println("Base Station Activated. Monitoring wireless pen telemetry channels...");
        esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
    }
    
    memset(virtualCanvas, 0, sizeof(virtualCanvas));
}

void loop() {
    //nothing here!
}
