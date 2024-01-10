// I2C Addresss
const uint8_t KEYPAD_ADDR = 0x20;
const uint8_t LCD_ADDR = 0x27;

// KEYPAD CONFIG
const byte keypadRows = 4;
const byte keypadCol = 4;

byte colPins[keypadRows] = {0, 1, 2, 3};
byte rowPins[keypadCol] = {4, 5, 6, 7};

char userKeyMap[keypadRows][keypadCol] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};

// LCD CONFIG
const byte lcdRows = 16;
const byte lcdCols = 4;

// RELAY CONFIG
const byte PELTIER1 = 7;
const byte PELTIER2 = 6;
const byte PELTIER3 = 5;
const byte PELTIER4 = 4;

const byte RADIATOR = 3;
const byte PEMANAS = 2;

const byte HIDUP = LOW;
const byte MATI = HIGH;

void setRelayPinMode() {
    pinMode(PELTIER1, OUTPUT);
    pinMode(PELTIER2, OUTPUT);
    pinMode(PELTIER3, OUTPUT);
    pinMode(PELTIER4, OUTPUT);
    pinMode(RADIATOR, OUTPUT);
    pinMode(PEMANAS, OUTPUT);

    digitalWrite(PELTIER1, MATI);
    digitalWrite(PELTIER2, MATI);
    digitalWrite(PELTIER3, MATI);
    digitalWrite(PELTIER4, MATI);
    digitalWrite(RADIATOR, MATI);
    digitalWrite(PEMANAS, MATI);
}

// TERMOCOPEL CONFIG
const byte chipSelectTermoIn = 9;
const byte chipSelectTermoW = 8;

void memanaskan(bool s) {
    digitalWrite(PEMANAS, s ? HIDUP : MATI);
}

void mendinginkan(bool s) {
    digitalWrite(PELTIER1, s ? HIDUP : MATI);
    digitalWrite(PELTIER2, s ? HIDUP : MATI);
    digitalWrite(PELTIER3, s ? HIDUP : MATI);
    digitalWrite(PELTIER4, s ? HIDUP : MATI);
    digitalWrite(RADIATOR, s ? HIDUP : MATI);
}