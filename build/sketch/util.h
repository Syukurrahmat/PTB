#line 1 "D:\\Project\\PTB\\util.h"
// PER LCD AN

byte squareChar[] = {0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x00, 0x00};
byte toastChar[] = {0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01};
byte clockChar[] = {0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0};
byte checkChar[] = { 0x00, 0x01, 0x03, 0x16, 0x1C, 0x08, 0x00,0x00};


void lcd_initCustomChar() {
    lcd.createChar(0, squareChar);
    lcd.createChar(1, toastChar);
    lcd.createChar(2, clockChar);
    lcd.createChar(3, checkChar);
}

void lcd_setCursor(uint8_t col, uint8_t row) {
    if (row > 1) col -= 4;
    lcd.setCursor(col, row);
}

void lcd_printAt(uint8_t col, uint8_t row, String text) {
    lcd_setCursor(col, row);
    lcd.print(text);
}

void lcd_clearRow(uint8_t row) {
    lcd.setCursor(0, row);
    lcd.print("                ");
    lcd.setCursor(0, row);
}

void lcd_printMode() {
    if (!screenIndex) return;
    String modeName = MODE == 1 ? "COOLING" : "THAWING";
    lcd.home();
    for (byte i = 0; i < 3; i++) lcd.write(0);
    lcd.print(" " + modeName + " ");
    for (byte i = 0; i < 4; i++) lcd.write(0);
}

void showToast(String message) {
    lcd_printAt(16 - message.length() - 1, 3, message);
    lcd.write(1);

    delay(500);
    lcd_clearRow(3);
}

// STRING FORMAT

String formatedTemp(float temp) {
    return String(temp, temp < 10 ? 2 : 1).substring(0, 4);
}

String formatedTime(int totalSeconds) {
    char formattedTime[8];

    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    sprintf(formattedTime, "%02u:%02u", minutes, seconds);
    return String(formattedTime);
}
