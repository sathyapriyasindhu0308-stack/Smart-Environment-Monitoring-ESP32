#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// ================= PIN CONFIGURATION =================

#define DHT_PIN 4
#define DHT_TYPE DHT11

#define LDR_PIN 34

#define GREEN_LED 25
#define YELLOW_LED 26
#define RED_LED 27

#define BUZZER 18

#define OLED_SDA 21
#define OLED_SCL 22

// ================= OLED =================

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

// ================= DHT =================

DHT dht(DHT_PIN, DHT_TYPE);

// ================= THRESHOLDS =================

const float WARNING_TEMP = 30.0;
const float CRITICAL_TEMP = 35.0;

const float WARNING_HUMIDITY = 70.0;
const float CRITICAL_HUMIDITY = 80.0;

// ================= TIMING =================

unsigned long lastSensorRead = 0;
const unsigned long SENSOR_INTERVAL = 2000;

// ================= SENSOR VALUES =================

float temperature = 0;
float humidity = 0;
int lightLevel = 0;

// ================= SYSTEM STATUS =================

enum SystemStatus {
  NORMAL,
  WARNING,
  CRITICAL,
  SENSOR_ERROR
};

SystemStatus status = SENSOR_ERROR;

// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(115200);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  pinMode(LDR_PIN, INPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);

  noTone(BUZZER);

  Wire.begin(OLED_SDA, OLED_SCL);

  // Start OLED

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {

    Serial.println("OLED ERROR");

    while (true) {

      digitalWrite(RED_LED, HIGH);
      delay(300);

      digitalWrite(RED_LED, LOW);
      delay(300);
    }
  }

  // Startup display

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  display.setCursor(10, 5);
  display.println("SMART ENVIRONMENT");

  display.setCursor(20, 20);
  display.println("MONITORING SYSTEM");

  display.setCursor(35, 45);
  display.println("Initializing...");

  display.display();

  delay(2000);

  // Start DHT

  dht.begin();

  // Ready display

  display.clearDisplay();

  display.setTextSize(2);

  display.setCursor(25, 15);
  display.println("SYSTEM");

  display.setCursor(30, 38);
  display.println("READY");

  display.display();

  delay(1500);
}

// =====================================================
// MAIN LOOP
// =====================================================

void loop() {

  if (millis() - lastSensorRead >= SENSOR_INTERVAL) {

    lastSensorRead = millis();

    readSensors();

    determineStatus();

    updateLEDs();

    updateDisplay();

    printSerial();
  }

  handleBuzzer();
}

// =====================================================
// READ SENSORS
// =====================================================

void readSensors() {

  temperature = dht.readTemperature();

  humidity = dht.readHumidity();

  lightLevel = analogRead(LDR_PIN);
}

// =====================================================
// DETERMINE STATUS
// =====================================================

void determineStatus() {

  if (isnan(temperature) || isnan(humidity)) {

    status = SENSOR_ERROR;

    return;
  }

  if (
    temperature >= CRITICAL_TEMP ||
    humidity >= CRITICAL_HUMIDITY
  ) {

    status = CRITICAL;

    return;
  }

  if (
    temperature >= WARNING_TEMP ||
    humidity >= WARNING_HUMIDITY
  ) {

    status = WARNING;

    return;
  }

  status = NORMAL;
}

// =====================================================
// LED CONTROL
// =====================================================

void updateLEDs() {

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);

  if (status == NORMAL) {

    digitalWrite(GREEN_LED, HIGH);
  }

  else if (status == WARNING) {

    digitalWrite(YELLOW_LED, HIGH);
  }

  else if (status == CRITICAL) {

    digitalWrite(RED_LED, HIGH);
  }

  else if (status == SENSOR_ERROR) {

    digitalWrite(RED_LED, (millis() / 500) % 2);
  }
}

// =====================================================
// BUZZER
// =====================================================

void handleBuzzer() {

  if (status != CRITICAL) {

    noTone(BUZZER);

    return;
  }

  static unsigned long buzzerTimer = 0;
  static bool buzzerOn = false;

  unsigned long currentTime = millis();

  if (!buzzerOn && currentTime - buzzerTimer >= 4000) {

    tone(BUZZER, 2000);

    buzzerOn = true;

    buzzerTimer = currentTime;
  }

  if (buzzerOn && currentTime - buzzerTimer >= 1000) {

    noTone(BUZZER);

    buzzerOn = false;

    buzzerTimer = currentTime;
  }
}

// =====================================================
// OLED DISPLAY
// =====================================================

void updateDisplay() {

  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  display.setCursor(0, 0);

  display.print("Temp : ");
  display.print(temperature, 1);
  display.println(" C");

  display.setCursor(0, 12);

  display.print("Hum  : ");
  display.print(humidity, 1);
  display.println(" %");

  display.setCursor(0, 24);

  display.print("Light: ");
  display.println(lightLevel);

  display.setCursor(0, 38);

  display.print("Status: ");

  if (status == NORMAL) {

    display.println("NORMAL");
  }

  else if (status == WARNING) {

    display.println("WARNING");
  }

  else if (status == CRITICAL) {

    display.println("CRITICAL");
  }

  else {

    display.println("SENSOR ERR");
  }

  display.setCursor(0, 52);

  if (status == CRITICAL) {

    display.println("Check Room!");
  }

  else if (status == SENSOR_ERROR) {

    display.println("Check DHT11!");
  }

  else {

    display.println("System Monitoring");
  }

  display.display();
}

// =====================================================
// SERIAL MONITOR
// =====================================================

void printSerial() {

  Serial.println("----------------------------");

  Serial.print("Temperature : ");
  Serial.print(temperature, 1);
  Serial.println(" C");

  Serial.print("Humidity    : ");
  Serial.print(humidity, 1);
  Serial.println(" %");

  Serial.print("Light Level : ");
  Serial.println(lightLevel);

  Serial.print("Status      : ");

  if (status == NORMAL) {

    Serial.println("NORMAL");
  }

  else if (status == WARNING) {

    Serial.println("WARNING");
  }

  else if (status == CRITICAL) {

    Serial.println("CRITICAL");
  }

  else {

    Serial.println("SENSOR ERROR");
  }
}