#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// =====================================================
// OLED
// =====================================================

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_SDA 21
#define OLED_SCL 22

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// =====================================================
// PINS
// =====================================================

const int BUTTON_PIN = 4;
const int LED_PIN = 2;
const int BUZZER_PIN = 5;
const int IR_PIN = 27;

// =====================================================
// WIFI
// =====================================================

const char* apSSID = "ESP32_Target_Game";
const char* apPassword = "ESP32game";

WebServer server(80);

// =====================================================
// GAME STATES
// =====================================================

enum GameState {
  IDLE,
  WAITING,
  TARGET,
  RESULT
};

GameState gameState = IDLE;

// =====================================================
// GAME VARIABLES
// =====================================================

unsigned long waitStart = 0;
unsigned long randomWait = 0;

unsigned long targetTime = 0;
unsigned long reactionTime = 0;
unsigned long bestTime = 0;

bool lastButtonState = HIGH;
bool lastIRState = HIGH;

String webStatus = "READY";

// =====================================================
// BUZZER
// =====================================================

void beep(int duration) {

  digitalWrite(BUZZER_PIN, HIGH);
  delay(duration);
  digitalWrite(BUZZER_PIN, LOW);
}

// =====================================================
// OLED
// =====================================================

void showMessage(
  String line1,
  String line2 = "",
  String line3 = ""
) {

  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(0, 5);
  display.println(line1);

  display.setTextSize(1);

  if (line2 != "") {
    display.setCursor(0, 32);
    display.println(line2);
  }

  if (line3 != "") {
    display.setCursor(0, 48);
    display.println(line3);
  }

  display.display();
}

// =====================================================
// START GAME
// =====================================================

void startGame() {

  gameState = WAITING;

  webStatus = "GET READY";

  digitalWrite(LED_PIN, LOW);

  showMessage(
    "GET READY",
    "Wait for TARGET",
    "Don't move!"
  );

  randomWait = random(2000, 5001);

  waitStart = millis();

  Serial.println("Game started");
}

// =====================================================
// ACTIVATE TARGET
// =====================================================

void activateTarget() {

  gameState = TARGET;

  webStatus = "TARGET!";

  targetTime = millis();

  digitalWrite(LED_PIN, HIGH);

  beep(150);

  showMessage(
    "TARGET!",
    "MOVE HAND NOW!"
  );

  Serial.println("TARGET!");
}

// =====================================================
// SHOW RESULT
// =====================================================

void showResult() {

  digitalWrite(LED_PIN, LOW);

  reactionTime = millis() - targetTime;

  Serial.print("Reaction time: ");
  Serial.print(reactionTime);
  Serial.println(" ms");

  if (bestTime == 0 || reactionTime < bestTime) {
    bestTime = reactionTime;
  }

  float reactionSeconds =
    reactionTime / 1000.0;

  float bestSeconds =
    bestTime / 1000.0;

  webStatus = "RESULT";

  // OLED
  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("REACTION RESULT");

  display.setTextSize(2);
  display.setCursor(0, 18);
  display.print(reactionSeconds, 3);
  display.println(" sec");

  display.setTextSize(1);
  display.setCursor(0, 48);
  display.print("Best: ");
  display.print(bestSeconds, 3);
  display.println(" sec");

  display.display();

  // Result sound
  beep(100);
  delay(100);
  beep(100);

  gameState = RESULT;
}

// =====================================================
// WEBPAGE
// =====================================================

void handleRoot() {

  String page = R"rawliteral(

<!DOCTYPE html>

<html>

<head>

<meta charset="UTF-8">

<meta name="viewport"
content="width=device-width, initial-scale=1.0">

<title>ESP32 Reaction Game</title>

<style>

/* =========================
   PAGE
   ========================= */

* {
  box-sizing: border-box;
}

body {

  margin: 0;

  font-family:
    Arial,
    Helvetica,
    sans-serif;

  min-height: 100vh;

  background:
    linear-gradient(
      135deg,
      #4facfe,
      #6a5acd,
      #d946ef
    );

  display: flex;

  justify-content: center;

  align-items: center;

  padding: 20px;
}

/* =========================
   MAIN CARD
   ========================= */

.container {

  width: 100%;

  max-width: 480px;

  background: rgba(255,255,255,0.96);

  border-radius: 25px;

  padding: 30px 25px;

  text-align: center;

  box-shadow:
    0 20px 50px
    rgba(0,0,0,0.25);
}

/* =========================
   TITLE
   ========================= */

.title {

  font-size: 30px;

  font-weight: 800;

  margin-bottom: 5px;

  background:
    linear-gradient(
      90deg,
      #4f46e5,
      #c026d3
    );

  -webkit-background-clip: text;

  -webkit-text-fill-color:
    transparent;
}

.subtitle {

  color: #666;

  font-size: 14px;

  margin-bottom: 25px;
}

/* =========================
   STATUS
   ========================= */

.statusBox {

  border-radius: 18px;

  padding: 20px;

  margin-bottom: 25px;

  background:
    linear-gradient(
      135deg,
      #eef2ff,
      #f5d0fe
    );
}

.statusLabel {

  font-size: 13px;

  color: #666;

  text-transform: uppercase;

  letter-spacing: 2px;
}

.status {

  font-size: 32px;

  font-weight: 800;

  margin-top: 8px;

  color: #4f46e5;
}

/* =========================
   SCORE CARDS
   ========================= */

.scores {

  display: flex;

  gap: 15px;

  margin-bottom: 25px;
}

.scoreCard {

  flex: 1;

  padding: 18px 10px;

  border-radius: 18px;

  background: #f8fafc;

  box-shadow:
    0 5px 15px
    rgba(0,0,0,0.08);
}

.scoreTitle {

  font-size: 13px;

  color: #666;

  margin-bottom: 8px;
}

.scoreValue {

  font-size: 24px;

  font-weight: 800;

  color: #111827;
}

/* =========================
   BUTTON
   ========================= */

button {

  width: 100%;

  border: none;

  border-radius: 16px;

  padding: 17px;

  font-size: 20px;

  font-weight: 700;

  color: white;

  background:
    linear-gradient(
      90deg,
      #4f46e5,
      #c026d3
    );

  cursor: pointer;

  box-shadow:
    0 8px 20px
    rgba(79,70,229,0.35);

  transition:
    transform 0.15s,
    box-shadow 0.15s;
}

button:active {

  transform: scale(0.97);

  box-shadow:
    0 4px 10px
    rgba(79,70,229,0.25);
}

/* =========================
   FOOTER
   ========================= */

.footer {

  margin-top: 20px;

  font-size: 12px;

  color: #888;
}

.connection {

  display: inline-block;

  margin-top: 8px;

  padding: 6px 12px;

  border-radius: 20px;

  background: #dcfce7;

  color: #15803d;

  font-weight: 600;
}

/* =========================
   MOBILE
   ========================= */

@media(max-width: 400px) {

  .container {
    padding: 25px 18px;
  }

  .title {
    font-size: 25px;
  }

  .status {
    font-size: 27px;
  }

  .scoreValue {
    font-size: 20px;
  }

}

</style>

</head>

<body>

<div class="container">

  <div class="title">
    ESP32 REACTION GAME
  </div>

  <div class="subtitle">
    Wi-Fi enabled embedded IoT system
  </div>

  <div class="statusBox">

    <div class="statusLabel">
      Game Status
    </div>

    <div
      class="status"
      id="status">
      READY
    </div>

  </div>

  <div class="scores">

    <div class="scoreCard">

      <div class="scoreTitle">
        YOUR TIME
      </div>

      <div
        class="scoreValue"
        id="reaction">
        0.000 sec
      </div>

    </div>

    <div class="scoreCard">

      <div class="scoreTitle">
        BEST TIME
      </div>

      <div
        class="scoreValue"
        id="best">
        0.000 sec
      </div>

    </div>

  </div>

  <button onclick="startGame()">
    START GAME
  </button>

  <div class="footer">

    ESP32 Local IoT Dashboard

    <br>

    <span class="connection">
      DEVICE CONNECTED
    </span>

  </div>

</div>

<script>

function startGame() {

  fetch('/start')
    .catch(error => {
      console.log(error);
    });

}

function updateGame() {

  fetch('/status')

  .then(response => response.json())

  .then(data => {

    document.getElementById("status")
      .innerHTML = data.status;

    document.getElementById("reaction")
      .innerHTML = data.reaction + " sec";

    document.getElementById("best")
      .innerHTML = data.best + " sec";

  })

  .catch(error => {

    console.log(error);

  });

}

setInterval(updateGame, 200);

updateGame();

</script>

</body>

</html>

)rawliteral";

  server.send(
    200,
    "text/html",
    page
  );
}

// =====================================================
// WEB START
// =====================================================

void handleStart() {

  if (
    gameState == IDLE ||
    gameState == RESULT
  ) {

    startGame();

    server.send(
      200,
      "text/plain",
      "Game Started"
    );

  } else {

    server.send(
      200,
      "text/plain",
      "Game Already Running"
    );
  }
}

// =====================================================
// WEB STATUS
// =====================================================

void handleStatus() {

  float reactionSeconds =
    reactionTime / 1000.0;

  float bestSeconds =
    bestTime / 1000.0;

  String json = "{";

  json += "\"status\":\"";
  json += webStatus;
  json += "\",";

  json += "\"reaction\":\"";
  json += String(
    reactionSeconds,
    3
  );
  json += "\",";

  json += "\"best\":\"";
  json += String(
    bestSeconds,
    3
  );

  json += "\"}";

  server.send(
    200,
    "application/json",
    json
  );
}

// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(115200);

  // GPIO
  pinMode(
    BUTTON_PIN,
    INPUT_PULLUP
  );

  pinMode(
    LED_PIN,
    OUTPUT
  );

  pinMode(
    BUZZER_PIN,
    OUTPUT
  );

  pinMode(
    IR_PIN,
    INPUT
  );

  digitalWrite(
    LED_PIN,
    LOW
  );

  digitalWrite(
    BUZZER_PIN,
    LOW
  );

  // OLED
  Wire.begin(
    OLED_SDA,
    OLED_SCL
  );

  if (
    !display.begin(
      SSD1306_SWITCHCAPVCC,
      0x3C
    )
  ) {

    Serial.println(
      "OLED not found!"
    );

    while (true) {
      delay(100);
    }
  }

  // Random timing
  randomSeed(
    micros()
  );

  // =================================================
  // WIFI ACCESS POINT
  // =================================================

  WiFi.softAP(
    apSSID,
    apPassword
  );

  Serial.println();
  Serial.println(
    "=============================="
  );

  Serial.println(
    "ESP32 REACTION GAME"
  );

  Serial.println(
    "=============================="
  );

  Serial.print(
    "Wi-Fi Network: "
  );

  Serial.println(
    apSSID
  );

  Serial.print(
    "Password: "
  );

  Serial.println(
    apPassword
  );

  Serial.print(
    "IP Address: "
  );

  Serial.println(
    WiFi.softAPIP()
  );

  // =================================================
  // WEB ROUTES
  // =================================================

  server.on(
    "/",
    handleRoot
  );

  server.on(
    "/start",
    handleStart
  );

  server.on(
    "/status",
    handleStatus
  );

  server.begin();

  Serial.println(
    "Web server started."
  );

  showMessage(
    "TARGET",
    "REACTION GAME",
    "Press button"
  );
}

// =====================================================
// LOOP
// =====================================================

void loop() {

  // Handle webpage requests
  server.handleClient();

  // Read button
  bool buttonState =
    digitalRead(
      BUTTON_PIN
    );

  // Read IR
  bool irState =
    digitalRead(
      IR_PIN
    );

  // Detect button press
  bool buttonPressed =
    (
      lastButtonState == HIGH &&
      buttonState == LOW
    );

  // Detect IR object
  bool irDetected =
    (
      lastIRState == HIGH &&
      irState == LOW
    );

  lastButtonState =
    buttonState;

  lastIRState =
    irState;

  // =================================================
  // IDLE
  // =================================================

  if (
    gameState == IDLE
  ) {

    if (buttonPressed) {

      delay(30);

      startGame();
    }
  }

  // =================================================
  // WAITING
  // =================================================

  else if (
    gameState == WAITING
  ) {

    // Hand detected too early
    if (irDetected) {

      digitalWrite(
        LED_PIN,
        LOW
      );

      webStatus =
        "TOO EARLY!";

      showMessage(
        "TOO EARLY!",
        "Wait for TARGET"
      );

      beep(100);

      gameState =
        RESULT;

      delay(1500);

      webStatus =
        "READY";

      showMessage(
        "TARGET",
        "REACTION GAME",
        "Press button"
      );

      gameState =
        IDLE;
    }

    // Random waiting finished
    else if (
      millis() - waitStart >=
      randomWait
    ) {

      activateTarget();
    }
  }

  // =================================================
  // TARGET
  // =================================================

  else if (
    gameState == TARGET
  ) {

    if (irDetected) {

      showResult();
    }
  }

  // =================================================
  // RESULT
  // =================================================

  else if (
    gameState == RESULT
  ) {

    if (buttonPressed) {

      delay(30);

      startGame();
    }
  }

  delay(5);
}
