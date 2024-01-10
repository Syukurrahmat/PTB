# 1 "D:\\Project\\PTB\\PTB.ino"
# 2 "D:\\Project\\PTB\\PTB.ino" 2
# 3 "D:\\Project\\PTB\\PTB.ino" 2
# 4 "D:\\Project\\PTB\\PTB.ino" 2
# 5 "D:\\Project\\PTB\\PTB.ino" 2
# 6 "D:\\Project\\PTB\\PTB.ino" 2

# 8 "D:\\Project\\PTB\\PTB.ino" 2

Keypad_I2C keypad(((char*)userKeyMap), rowPins, colPins, keypadRows, keypadCol, KEYPAD_ADDR);
// Keypad keypad = Keypad(makeKeymap(userKeyMap), rowPins, colPins, keypadRows, keypadCol);
LiquidCrystal_I2C lcd(LCD_ADDR, lcdRows, lcdCols);
MAX6675 thermoW(SCK, chipSelectTermoW, MISO);
MAX6675 thermoIn(SCK, chipSelectTermoIn, MISO);
Timer<2> timer;

// Constant value
const int TEMP_LIMITS[] = {1, 85};
const int DURATION_LIMITS[] = {1, 120};
const int TEMP_TOLERANCE = 1.5;

// Default value
int COOLING_TEMP = 5;
int THAWING_TEMP = 45;
int COOLING_DUR = 20;
int THAWING_DUR = 10;

// Global Variable
int MODE = 
# 28 "D:\\Project\\PTB\\PTB.ino" 3 4
          __null
# 28 "D:\\Project\\PTB\\PTB.ino"
              ;
bool backButtonPressed = false;
int screenIndex = 0;

# 33 "D:\\Project\\PTB\\PTB.ino" 2

void setup() {
    Serial.begin(9600);

    lcd.init();
    lcd.backlight();
    lcd_initCustomChar();

    keypad.begin();
    keypad.addEventListener(keypadEvent);

    setRelayPinMode();
    startupMessage();
}

void loop() {
    lcd_printMode();

    switch (screenIndex) {
        case 0:
            selectMode();
            break;

        case 1: {
            int tempSet = inputSetPoint(
                (reinterpret_cast<const __FlashStringHelper *>(
# 58 "D:\\Project\\PTB\\PTB.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 58 "D:\\Project\\PTB\\PTB.ino"
               "Suhu"
# 58 "D:\\Project\\PTB\\PTB.ino" 3
               ); &__c[0];}))
# 58 "D:\\Project\\PTB\\PTB.ino"
               )), // Name
                (reinterpret_cast<const __FlashStringHelper *>(
# 59 "D:\\Project\\PTB\\PTB.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 59 "D:\\Project\\PTB\\PTB.ino"
               "\xDF\C"
# 59 "D:\\Project\\PTB\\PTB.ino" 3
               ); &__c[0];}))
# 59 "D:\\Project\\PTB\\PTB.ino"
               )), // Unit
                MODE == 1 // Default Value
                    ? COOLING_TEMP
                    : THAWING_TEMP,
                TEMP_LIMITS // min max alowed
            );

            MODE == 1
                ? COOLING_TEMP = tempSet
                : THAWING_TEMP = tempSet;
            break;
        }

        case 2: {
            int durationSet = inputSetPoint(
                (reinterpret_cast<const __FlashStringHelper *>(
# 74 "D:\\Project\\PTB\\PTB.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 74 "D:\\Project\\PTB\\PTB.ino"
               "Durasi"
# 74 "D:\\Project\\PTB\\PTB.ino" 3
               ); &__c[0];}))
# 74 "D:\\Project\\PTB\\PTB.ino"
               )), // Name
                (reinterpret_cast<const __FlashStringHelper *>(
# 75 "D:\\Project\\PTB\\PTB.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 75 "D:\\Project\\PTB\\PTB.ino"
               "Menit"
# 75 "D:\\Project\\PTB\\PTB.ino" 3
               ); &__c[0];}))
# 75 "D:\\Project\\PTB\\PTB.ino"
               )), // Unit
                MODE == 1
                    ? COOLING_DUR
                    : THAWING_DUR, // Default Value
                DURATION_LIMITS // min max alowed
            );

            MODE == 1
                ? COOLING_DUR = durationSet
                : THAWING_DUR = durationSet;
            break;
        }

        case 3:
            confirmToStart();
            break;

        case 4:
            startProcess();
            break;
    }

    backButtonPressed &&screenIndex > 0
        ? screenIndex--
        : screenIndex++;
    screenIndex %= 5;
    backButtonPressed = false;
    lcd.noBlink();
    lcd.clear();
}

void keypadEvent(KeypadEvent key) {
    if (keypad.getState() == PRESSED && key == '*') {
        backButtonPressed = true;
    }
}

// ============= STARTUP MESSAGE =============
void startupMessage() {
    lcd_printAt(1, 0, (reinterpret_cast<const __FlashStringHelper *>(
# 114 "D:\\Project\\PTB\\PTB.ino" 3
                     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 114 "D:\\Project\\PTB\\PTB.ino"
                     "Alat Cooling"
# 114 "D:\\Project\\PTB\\PTB.ino" 3
                     ); &__c[0];}))
# 114 "D:\\Project\\PTB\\PTB.ino"
                     )));
    lcd_printAt(2, 1, (reinterpret_cast<const __FlashStringHelper *>(
# 115 "D:\\Project\\PTB\\PTB.ino" 3
                     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 115 "D:\\Project\\PTB\\PTB.ino"
                     "dan thawing"
# 115 "D:\\Project\\PTB\\PTB.ino" 3
                     ); &__c[0];}))
# 115 "D:\\Project\\PTB\\PTB.ino"
                     )));
    lcd_printAt(0, 2, (reinterpret_cast<const __FlashStringHelper *>(
# 116 "D:\\Project\\PTB\\PTB.ino" 3
                     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 116 "D:\\Project\\PTB\\PTB.ino"
                     "[PTB 23 kel. 1]"
# 116 "D:\\Project\\PTB\\PTB.ino" 3
                     ); &__c[0];}))
# 116 "D:\\Project\\PTB\\PTB.ino"
                     )));
    lcd_setCursor(0, 3);

    delay(100);
    for (byte i = 0; i < 16; i++) {
        lcd.write(0);
        delay(100);
    }
    lcd.clear();
}

// ============= SELECT MODE =============
void selectMode() {
    lcd_printAt(0, 0, (reinterpret_cast<const __FlashStringHelper *>(
# 129 "D:\\Project\\PTB\\PTB.ino" 3
                     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 129 "D:\\Project\\PTB\\PTB.ino"
                     "Pilih Mode :    "
# 129 "D:\\Project\\PTB\\PTB.ino" 3
                     ); &__c[0];}))
# 129 "D:\\Project\\PTB\\PTB.ino"
                     )));
    lcd_printAt(0, 1, (reinterpret_cast<const __FlashStringHelper *>(
# 130 "D:\\Project\\PTB\\PTB.ino" 3
                     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 130 "D:\\Project\\PTB\\PTB.ino"
                     "> Cooling (A)   "
# 130 "D:\\Project\\PTB\\PTB.ino" 3
                     ); &__c[0];}))
# 130 "D:\\Project\\PTB\\PTB.ino"
                     )));
    lcd_printAt(0, 2, (reinterpret_cast<const __FlashStringHelper *>(
# 131 "D:\\Project\\PTB\\PTB.ino" 3
                     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 131 "D:\\Project\\PTB\\PTB.ino"
                     "> Thawing (B)   "
# 131 "D:\\Project\\PTB\\PTB.ino" 3
                     ); &__c[0];}))
# 131 "D:\\Project\\PTB\\PTB.ino"
                     )));

    while (!backButtonPressed) {
        char key = keypad.getKey();
        if (key == 'A') {
            MODE = 1;
            return;
        }
        if (key == 'B') {
            MODE = 2;
            return;
        }
    }
}

// ============= INPUT TEMP AND DURATION =============
int inputSetPoint(String question, String unit, int defaultValue, const int limits[]) {
    String value = String(defaultValue);

    lcd_printAt(0, 1, question + " :");
    lcd_printAt(0, 2, ">     " + unit);
    lcd_printAt(2, 2, value);

    while (!backButtonPressed) {
        char key = keypad.getKey();
        if (key == 'C' || key == '#') {
            // Edit value
            if (key == 'C') {
                value = editValue(limits);
                if (backButtonPressed) {
                    backButtonPressed = false;
                    value = String(defaultValue);
                    lcd_printAt(2, 2, value);
                    continue;
                }
            }

            showToast("Oke");
            return value.toInt();
        }
    }
    return defaultValue;
}

String editValue(const int limits[]) {
    String userInput;

    lcd_printAt(2, 2, "  ");
    lcd_setCursor(2, 2);
    lcd.blink();

    while (!backButtonPressed) {
        char key = keypad.getKey();

        // ADD DIGIT
        if (isdigit(key) && userInput.length() < 2) {
            userInput += key;
            lcd.print(key);
            continue;
        }

        // REMOVE LAST DIGIT
        if (key == 'C') {
            userInput.remove(userInput.length() - 1);
            lcd_setCursor(userInput.length() + 2, 2);
            lcd.print(" ");
            lcd_setCursor(userInput.length() + 2, 2);
        }

        // SUBMIT DIGIT
        if (key == '#') {
            lcd.noBlink();

            int minVal = limits[0];
            int maxVal = limits[1];
            int enteredVal = userInput.toInt();

            if (enteredVal > maxVal || enteredVal < minVal) {
                showToast("Invalid");
                return editValue(limits);
            }

            return userInput;
        }
    }
    lcd.noBlink();
    return "";
}

// ============= CONFIRM MESSAGE =============
void confirmToStart() {
    String tempSet = String(MODE == 1 ? COOLING_TEMP : THAWING_TEMP);
    String durationSet = String(MODE == 1 ? COOLING_DUR : THAWING_DUR);

    lcd_printAt(0, 1, "Suhu   : " + tempSet + " \xDF\C");
    lcd_printAt(0, 2, "Durasi : " + durationSet + " m");
    lcd_printAt(0, 3, "Mulai Sekarang ?");

    while (!backButtonPressed) {
        char key = keypad.getKey();
        if (key == '#') return;
    }
}

// ============= PROCESSS =============
int countdown = 0;
bool screenConfirmToStop = false;
bool processStarted = false;

void startProcess() {
    countdown = 0;
    processStarted = false;

    displayTemplate();
    animationTemplate();

    // BEGIN

    timer.every(250, processAnimation);
    timer.every(2000, readSensor);

    while (!timer.empty()) {
        timer.tick();
        forceStopHandle();
    }

    // END

    lcd_clearRow(1);
    lcd_clearRow(2);
    lcd_clearRow(3);

    lcd_setCursor(0, 2);
    lcd.write(3);
    lcd.print(" PROSES SELESAI");

    for (byte i = 0; i < 4; i++) {
        delay(750);
        lcd.setBacklight(0x0);
        delay(750);
        lcd.setBacklight(0x1);
    }

    if (MODE == 1) {
        lcd_printAt(0, 3, "Lanjut Thawing ?");

        while (true) {
            char key = keypad.getKey();
            if (key == '*') break;
            if (key == '#') {
                MODE = 2;
                screenIndex += 1;

                return;
            }
        }
    } else {
        keypad.waitForKey();
    }

    lcd.clear();
    startupMessage();
    return;
}

bool readSensor(void *opaque) {
    int tempSet = MODE == 1 ? COOLING_TEMP : THAWING_TEMP;

    float currentTempW = thermoW.readCelsius();
    float currentTempin = thermoIn.readCelsius();

    if (!screenConfirmToStop) {
        lcd_printAt(9, 1, formatedTemp(currentTempW));
        lcd_printAt(9, 2, formatedTemp(currentTempin));
    }

    bool tempIsLower = currentTempin < (tempSet - TEMP_TOLERANCE);
    bool tempIsHigher = currentTempin > (tempSet + TEMP_TOLERANCE);
    bool tempInSetpoint = !tempIsHigher && !tempIsLower;

    if (tempIsHigher) {
        mendinginkan(true);
        memanaskan(false);
    }
    if (tempIsLower) {
        mendinginkan(false);
        memanaskan(true);
    }

    if (tempInSetpoint) {
        mendinginkan(false);
        memanaskan(false);

        if (!processStarted) {
            processStarted = true;
            countdown = (MODE == 1 ? COOLING_DUR : THAWING_DUR) * 60;
            animationTemplate();
            // digitalWrite(RADIATORHIDUP);
        }
    }

    return true;
}

bool processAnimation(void *opaque) {
    static int index = 0;

    if (!processStarted) {
        index == 0
            ? lcd_printAt(10 + index, 3, "   ")
            : lcd_printAt(9 + index, 3, ".");
    } else if (!index) {
        lcd_printAt(6, 3, formatedTime(countdown));
        if (countdown <= 0) timer.cancel();
        countdown--;
    }

    index = (index + 1) % 4;
    return true;
}

void displayTemplate() {
    lcd_printAt(0, 1, "Suhu W :      \xDF\C");
    lcd_printAt(0, 2, "Suhu in:      \xDF\C");
}

void animationTemplate() {
    if (!processStarted) {
        lcd_printAt(0, 3, "  [Memulai   ]  ");
    } else {
        lcd_printAt(0, 3, "   [  " + formatedTime(countdown) + " ]   ");
        lcd_setCursor(4, 3);
        lcd.write(2);
    }
}

void forceStopHandle() { // work in loop
    char key = keypad.getKey();

    if (key == '*') {
        if (!screenConfirmToStop) {
            lcd_printAt(0, 1, "Hentikan Proses ");
            lcd_printAt(0, 2, "   Sekarang ?   ");
        } else {
            displayTemplate();
        }
        screenConfirmToStop = !screenConfirmToStop;
        backButtonPressed = false;
    }

    if (key == '#' && screenConfirmToStop) {
        timer.cancel();
        screenConfirmToStop = false;

        lcd_clearRow(3);
        showToast("Oke");

        lcd_clearRow(1);
        lcd_printAt(0, 2, "PROSES TERHENTI");
        delay(2000);
    }
}
