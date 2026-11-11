#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <LSM6DSV16XSensor.h>

#define IMU_I2C_ADDRESS 0x6A
#define FLASH_CS 10
#define SAMPLE_RATE 10
#define MAX_SAMPLE 150
#define QVAR_TOUCH_THRESHOLD 50.0f

LSM6DSV16XSensor IMU(&Wire, IMU_I2C_ADDRESS);

// IMU sample structure
struct IMUSample {
    int32_t ax, ay, az;
    int32_t gx, gy, gz;
};

IMUSample strokeBuffer[MAX_SAMPLE];
int sampleCount = 0;
bool writing = false;
uint32_t flashWriteAddress = 0x000000;
unsigned long lastSampleTime = 0;

// check Flash memory
void checkFlash() {
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    digitalWrite(FLASH_CS, LOW);
    SPI.transfer(0x9F);
    uint8_t brandID = SPI.transfer(0x00);
    uint8_t memoryTypeID = SPI.transfer(0x00);
    uint8_t capacityID = SPI.transfer(0x00);
    digitalWrite(FLASH_CS, HIGH);
    SPI.endTransaction();

    Serial.print("Brand: 0x");
    Serial.print(brandID, HEX);
    Serial.print(", Memory Type: 0x");
    Serial.print(memoryTypeID, HEX);
    Serial.print(", Capacity: 0x");
    Serial.println(capacityID, HEX);

    if (brandID == 0x00 || brandID == 0xFF) {
        Serial.println("Flash memory chip error");
    } else {
        Serial.println("Flash memory chip works");
    }
}

//save character in Flash memory
void saveFlash(char character) {
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    digitalWrite(FLASH_CS, LOW);
    SPI.transfer(0x06);
    digitalWrite(FLASH_CS, HIGH);
    delayMicroseconds(5);
    digitalWrite(FLASH_CS, LOW);
    SPI.transfer(0x02);
    SPI.transfer((flashWriteAddress >> 16) & 0xFF);
    SPI.transfer((flashWriteAddress >> 8) & 0xFF);
    SPI.transfer(flashWriteAddress & 0xFF);
    SPI.transfer((uint8_t)character);
    digitalWrite(FLASH_CS, HIGH);
    SPI.endTransaction();
    delay(5);
    Serial.print("Character '");
    Serial.print(character);
    Serial.print("' saved at 0x");
    Serial.println(flashWriteAddress, HEX);
    flashWriteAddress++;
}

// conversion
char conversion(IMUSample* buffer, int length) {
    Serial.print("Converting ");
    Serial.print(length);
    Serial.print(" stroke samples");

    // example logic
    long sumX = 0, sumY = 0;
    for (int i = 0; i < length; i++) {
        sumX += abs(buffer[i].ax);
        sumY += abs(buffer[i].ay);
    }

    if (length < 15) return '.';
    if (sumX > sumY) return 'A';
    return 'B';

}

// bluetooth transfer
void bluetoothTransfer() {
    Serial.println("Bluetooth Transfer");
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    digitalWrite(FLASH_CS, LOW);
    SPI.transfer(0x03);
    SPI.transfer(0x00);
    SPI.transfer(0x00);
    SPI.transfer(0x00);

    String notes = "";
    for (uint32_t i = 0; i < flashWriteAddress; i++) {
        char c = (char)SPI.transfer(0x00);
        notes += c;
    }
    digitalWrite(FLASH_CS, HIGH);
    SPI.endTransaction();

    // Serial for now
    Serial.print("Notes: ");
    Serial.println(notes);
}

// handwriting
void handwriting() {
    int32_t acceleration[3];
    int32_t gyroscope[3];
    static float qvar = 0.0f;
    uint8_t qvarStatus = 0;
    if (IMU.QVAR_GetStatus(&qvarStatus) == 0 && qvarStatus) {
        IMU.QVAR_GetData(&qvar);
    }
    bool penDown = (abs(qvar) > QVAR_TOUCH_THRESHOLD);

    if (penDown) {
        if (!writing) {
            writing = true;
            sampleCount = 0;
            Serial.println("Pen Down");
        }
        if (sampleCount < MAX_SAMPLE) {
            if (IMU.Get_X_Axes(acceleration) == 0 && IMU.Get_G_Axes(gyroscope) == 0) {
                strokeBuffer[sampleCount] = {acceleration[0], acceleration[1], acceleration[2], gyroscope[0], gyroscope[1], gyroscope[2]};
                sampleCount++;
            }
        }
    } else if (writing) {
        writing = false;
        Serial.println("Pen Up");
        if (sampleCount > 5) {
            char convertedChar = conversion(strokeBuffer, sampleCount);
            saveFlash(convertedChar);
        }
    }
}

void setup() {
    Serial.begin(115200);
    while (!Serial) {delay(10);}
    Serial.println("uPen v2 Testing");
    Wire.begin();
    pinMode(FLASH_CS, OUTPUT);
    digitalWrite(FLASH_CS, HIGH);
    SPI.begin();

    if (IMU.begin() == 0) {
        Serial.println("IMU works");
        IMU.Enable_X();
        IMU.Enable_G();
        IMU.Set_X_ODR(120.0f);
        IMU.Set_G_ODR(120.0f);
        IMU.QVAR_Enable();
    } else {
        Serial.println("IMU error");
    }

    checkFlash();
    Serial.println("Set up finished. Start writing or send 't' via Serial to test Bluetooth");
}

void loop() {
    if (millis() - lastSampleTime >= SAMPLE_RATE) {
        lastSampleTime = millis();
        handwriting();
    }
    if (Serial.available()) {
        char cmd = Serial.read();
        if (cmd == 't' || cmd == 'T') {
            bluetoothTransfer();
        }
    }
}