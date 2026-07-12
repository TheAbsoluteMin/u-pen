//main pen code

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SparkFun_MAX17048_Arduino_Library.h>
#include <LSM6DSV16XSensor.h>

#define PEN_TIP_PIN 7
#define BAT_ALERT_PIN 5
#define IMU_INT1_PIN 14
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1

uint8_t baseStationMac[] = {0x24, 0x4C, 0xAB, 0x11, 0x22, 0x33};

//dual I2C buses
TwoWire I2C_Bus1 = TwoWire(0); // bus 1: IMU + battery gauge
TwoWire I2C_Bus2 = TwoWire(1); // bus 2: OLED display screen

LSM6DSV16XSensor IMU(&I2C_Bus1);
SFE_MAX17048 FuelGauge;
Adafruit_SSD1306 Display(SCREEN_WIDTH, SCREEN_HEIGHT, &I2C_Bus2, OLED_RESET);

//data packet structure
typedef struct {
    int16_t x_pos;
    int16_t y_pos;
    uint8_t is_pressed;
} SimplePoint;

//pen system states
enum PenSystemState { MODE_DRAWING, MODE_SOLVING, MODE_CHARGING };
PenSystemState currentSystemMode = MODE_DRAWING;

float globalX = SCREEN_WIDTH / 4; 
float globalY = SCREEN_HEIGHT / 2;

uint32_t lastTimeActive = 0;
uint32_t lastNetworkTxTime = 0;

volatile bool lowBatteryHardwareFlag = false;
volatile bool imuDataReadyHardwareFlag = false;

void IRAM_ATTR onBatteryAlertInterrupt() {
    lowBatteryHardwareFlag = true; 
}

void IRAM_ATTR onImuDataReadyInterrupt() {
    imuDataReadyHardwareFlag = true;
}

//get and display API answer
void OnDataRecv(const esp_now_recv_info *recvInfo, const uint8_t *incomingData, int len) {
    Display.clearDisplay();
    Display.setCursor(0, 10);
    Display.print("Ans: ");
    Display.println((char*)incomingData);
    Display.display();
    
    currentSystemMode = MODE_DRAWING;
    lastTimeActive = millis(); 
}

void setup() {
    Serial.begin(115200);
    //pins
    pinMode(PEN_TIP_PIN, INPUT);
    pinMode(BAT_ALERT_PIN, INPUT);
    pinMode(IMU_INT1_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(BAT_ALERT_PIN), onBatteryAlertInterrupt, FALLING);
    attachInterrupt(digitalPinToInterrupt(IMU_INT1_PIN), onImuDataReadyInterrupt, RISING);
    //I2C
    I2C_Bus1.begin(17, 18, 100000); 
    I2C_Bus2.begin(11, 12, 100000); 
    //OLED
    Display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    Display.clearDisplay();
    Display.setTextSize(1);
    Display.setTextColor(SSD1306_WHITE);
    Display.setCursor(0, 10);
    Display.println("Pen Booting...");
    Display.display();
    //fuel gauge
    FuelGauge.begin(I2C_Bus1);
    FuelGauge.setAlertThreshold(15); 
    FuelGauge.quickStart();
    //IMU 
    IMU.begin();
    IMU.Enable_6AXIS_Sensor_Fusion(); 
    IMU.Enable_X(); 
    IMU.Set_X_ODR(50.0f);
    //ESP-NOW
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    if (esp_now_init() == ESP_OK) {
        esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
        esp_now_peer_info_t peerInfo = {};
        memcpy(peerInfo.peer_addr, baseStationMac, 6);
        peerInfo.channel = 1;
        peerInfo.encrypt = false;
        esp_now_add_peer(&peerInfo);
    }
    //timers
    lastTimeActive = millis();
    lastNetworkTxTime = millis();
}

void loop() {
    float cellVoltage = FuelGauge.getVoltage();
    if (cellVoltage > 4.22f) {
        currentSystemMode = MODE_CHARGING;
    }

    if (lowBatteryHardwareFlag) {
        Display.clearDisplay();
        Display.setCursor(0, 10);
        Display.printf("LOW BAT: %.1f%%", FuelGauge.getSOC());
        Display.display();
        delay(2000); 
        lowBatteryHardwareFlag = false; 
    }

    switch (currentSystemMode) {

        case MODE_DRAWING: {
            if (imuDataReadyHardwareFlag) {
                imuDataReadyHardwareFlag = false;

                bool tipPressed = (digitalRead(PEN_TIP_PIN) == LOW);
                
                int32_t linearAccel = {0, 0, 0};
                IMU.Get_X_Linear_Acceleration(linearAccel); 
                
                int32_t pureHandX = linearAccel[0]; 
                int32_t pureHandY = linearAccel[1]; 

                if (tipPressed) {
                    lastTimeActive = millis(); 
                    globalX += (float)pureHandX * 0.002f;
                    globalY += (float)pureHandY * 0.002f;
                } else {
                    globalX += (float)pureHandX * 0.0004f; 
                    globalY += (float)pureHandY * 0.0004f;
                }

                globalX = constrain(globalX, 0, SCREEN_WIDTH - 1);
                globalY = constrain(globalY, 0, SCREEN_HEIGHT - 1);
            }

            //concurrent data packet transmission every 150ms to base ESP32
            if (millis() - lastNetworkTxTime >= 150) {
                bool tipPressedNow = (digitalRead(PEN_TIP_PIN) == LOW);
                
                SimplePoint dataPacket;
                dataPacket.x_pos = (int16_t)globalX;
                dataPacket.y_pos = (int16_t)globalY;
                dataPacket.is_pressed = tipPressedNow ? 1 : 0;

                //automatic solver after 5 seconds of inactivity
                if (!tipPressedNow && (millis() - lastTimeActive >= 5000)) {
                    currentSystemMode = MODE_SOLVING;
                    
                    Display.clearDisplay();
                    Display.setCursor(0, 10);
                    Display.println("Solving...");
                    Display.display();

                    dataPacket.is_pressed = 255; 
                }

                esp_now_send(baseStationMac, (uint8_t*)&dataPacket, sizeof(SimplePoint));
                lastNetworkTxTime = millis(); 
            }
            break;
        }

        case MODE_SOLVING: {
            if (digitalRead(PEN_TIP_PIN) == LOW) {
                currentSystemMode = MODE_DRAWING;
                lastTimeActive = millis();
                Display.clearDisplay();
            }
            break;
        }

        case MODE_CHARGING: {
            Display.clearDisplay();
            Display.setCursor(0, 0);
            Display.printf("Charging Pen...\nVolts: %.2fV\nBattery: %.1f%%", cellVoltage, FuelGauge.getSOC());
            Display.display();
            
            delay(1000); 
            
            //check if USB charger is unplugged and LiPo battery is full
            if (cellVoltage < 4.15f) { 
                currentSystemMode = MODE_DRAWING;
                lastTimeActive = millis();
                Display.clearDisplay();
            }
            break;
        }
    }
}
