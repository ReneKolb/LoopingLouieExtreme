#define DEBUG true
#define BLUETOOTH true

#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include "defines.h"
#include "timer.h"

enum State
{
	GAME,
	IDLE,
	STANDBY
};

State state;

Adafruit_MCP23017 mcpBoosterLEDs; // IO-Expander for Booster-LEDs
Adafruit_MCP23017 mcpUVLEDs;      // IO-Expander for UV-LEDs

Adafruit_MCP23017 mcpCircle1LEDs; // IO-Expander for Circle-LEDs
Adafruit_MCP23017 mcpCircle2LEDs; // IO-Expander for Circle-LEDs

GameSettings gameSettings;

void Log(String msg) {
	if (DEBUG) {
		Serial.println(msg);
	}
}

boolean equalColors(const Color col1, const Color col2) {
	return col1.r == col2.r && col1.g == col2.g && col1.b == col2.b;

}

void digitalWrite(const PIN_ADDRESS pinAddress, const uint8_t value) {
	if (pinAddress.pin >= 54 && pinAddress.pin <= 69) {
		Log("Trying to write analog-Input pin");
		return;
	}

	switch (pinAddress.board) {
	case 0:
		digitalWrite(pinAddress.pin, value);
		break;
	case 1:
		mcpBoosterLEDs.digitalWrite(pinAddress.pin, value);
		break;
	case 2:
		mcpUVLEDs.digitalWrite(pinAddress.pin, value);
		break;
	case 3:
		mcpCircle1LEDs.digitalWrite(pinAddress.pin, value);
		break;
	case 4:
		mcpCircle2LEDs.digitalWrite(pinAddress.pin, value);
		break;
	default:
		Log("Unkown pinAddress.board: " + (String)pinAddress.board);
	}
}

void digitalWrites(const PIN_ADDRESS *pPinList, int startIndex, int endIndex, const uint8_t value) {
	for (int i = startIndex; i <= endIndex; i++) {
		digitalWrite(pPinList[i], value);
	}
}

uint8_t digitalRead(const PIN_ADDRESS pinAddress) {
	switch (pinAddress.board) {
	case 0:
		if (pinAddress.pin >= 100) {
			if (analogRead(pinAddress.pin - 100) <= 511) {
				return LOW;
			}
			else {
				return HIGH;
			}
		}
		else {
			return digitalRead(pinAddress.pin);
		}
		break;
	default:
		Log("digital Read only supported for the arduino Board (for now).");
		return 0x02; //weder LOW noch HIGH!!
	}
}

void analogWrite(const PIN_ADDRESS pinAddress, const uint8_t value) {
	if (pinAddress.board != 0) {
		Log("analogWrite only supported on the Arduino board (not I/O-Expander)");
		return;
	}
	analogWrite(pinAddress.pin, value);
}

void setMotorSpeed(const int speed) {
	if (speed >= 0) {
		setMotorSpeed(true, speed);
	}
	else {
		setMotorSpeed(false, -speed);
	}
}

void setMotorSpeed(const boolean forward, uint8_t speed) {
	if (forward) {
		digitalWrite(PIN_ADDRESS MOTOR_DIRECTION_A, HIGH);
		digitalWrite(PIN_ADDRESS MOTOR_DIRECTION_B, LOW);
	}
	else {
		digitalWrite(PIN_ADDRESS MOTOR_DIRECTION_A, LOW);
		digitalWrite(PIN_ADDRESS MOTOR_DIRECTION_B, HIGH);
	}

	if (speed <= 0) {
		speed = 0;
	}
	else {
		if (speed > MAX_MOTOR_SPEED)
			speed = MAX_MOTOR_SPEED;
		else if (speed < MIN_MOTOR_SPEED)
			speed = MIN_MOTOR_SPEED;
	}
	analogWrite(PIN_ADDRESS MOTOR_SPEED, speed);

	Log("Motor Speed: " + (String)speed);
}

boolean isButtonPressed(const PIN_ADDRESS pin) {
	if (pin.pin >= 100) {
		return digitalRead(pin) == LOW;
	}
	else {
		return digitalRead(pin) == LOW;
	}
}

boolean checkButtons(uint8_t player) {
	return isButtonPressed(SpeedButton[player - 1][0])|| isButtonPressed(SpeedButton[player - 1][1]) || isButtonPressed(SpecialButton[player - 1]);
}

boolean checkButtons() {
	return checkButtons(1) || checkButtons(2)|| checkButtons(3) || checkButtons(4);
	/*
	return isButtonPressed(PIN_ADDRESS BUTTON_INC_SPEED_PLAYER1) || isButtonPressed(PIN_ADDRESS BUTTON_DEC_SPEED_PLAYER1)
		|| isButtonPressed(PIN_ADDRESS BUTTON_INC_SPEED_PLAYER2) || isButtonPressed(PIN_ADDRESS BUTTON_DEC_SPEED_PLAYER2)
		|| isButtonPressed(PIN_ADDRESS BUTTON_INC_SPEED_PLAYER3) || isButtonPressed(PIN_ADDRESS BUTTON_DEC_SPEED_PLAYER3)
		|| isButtonPressed(PIN_ADDRESS BUTTON_INC_SPEED_PLAYER4) || isButtonPressed(PIN_ADDRESS BUTTON_DEC_SPEED_PLAYER4)
		|| isButtonPressed(PIN_ADDRESS PLAYER1_SPECIAL_BUTTON)
		|| isButtonPressed(PIN_ADDRESS PLAYER2_SPECIAL_BUTTON)
		|| isButtonPressed(PIN_ADDRESS PLAYER3_SPECIAL_BUTTON)
		|| isButtonPressed(PIN_ADDRESS PLAYER4_SPECIAL_BUTTON);
		*/
}


void updatePlayerBoosterLEDs(const uint8_t player, const uint8_t amount, const boolean updateButtonLED=false) {
	for (int i = 0; i < 4; i++) {
		if (amount > i) {
			//digitalWrite(BOOSTER_LEDS[player - 1][i], HIGH);
			digitalWrite(BOOSTER_LEDS[getPinIndex(player-1,i,MAX_LEDS_BOOSTER)], HIGH);
		}
		else {
			//digitalWrite(BOOSTER_LEDS[player - 1][i], LOW);
			digitalWrite(BOOSTER_LEDS[getPinIndex(player - 1, i, MAX_LEDS_BOOSTER)], LOW);
		}
	}
	if (updateButtonLED) {
		digitalWrite(SpecialButtonLED[player-1],amount>0);
	}
}

boolean playerChip(uint8_t player, uint8_t chip) {
	return analogRead(PlayerIRPins[player - 1][chip - 1].pin - 100) < IR_THRESHOLD;
}

uint8_t getPlayerChipAmount(uint8_t player) {
	uint8_t amount=0;
	if (playerChip(player, 1)) {
		amount++;
	}
	if (playerChip(player, 2)) {
		amount++;
	}
	if (playerChip(player, 3)) {
		amount++;
	}
	return amount;
}

void setColor(const uint8_t player, const uint8_t r, const uint8_t g, const uint8_t b) {
	analogWrite(RGB_LEDS[getPinIndex(player - 1, 0, MAX_LEDS_RGB)], r);
	analogWrite(RGB_LEDS[getPinIndex(player - 1, 1, MAX_LEDS_RGB)], g);
	analogWrite(RGB_LEDS[getPinIndex(player - 1, 2, MAX_LEDS_RGB)], b);
}

void setColor(const uint8_t player, const Color color) {
	setColor(player, color.r, color.g, color.b);
}

void fullOn(boolean includeIR ) {
	for (int p = 0; p < 4; p++) {
		for (int l = 0; l < 4; l++) {
			//digitalWrite(BOOSTER_LEDS[p][l], 255);
			digitalWrite(BOOSTER_LEDS[getPinIndex(p, l, MAX_LEDS_BOOSTER)], 255);
			digitalWrite(UVLEDs[getPinIndex(p,l, MAX_LEDS_UV)], 255);
		}
		for (int l = 0; l < 3; l++) {
			digitalWrite(RGB_LEDS[getPinIndex(p,l, MAX_LEDS_RGB)], 255);
		}
		for (int l = 0; l < 5; l++) {
			digitalWrite(playerMiddleColors[getPinIndex(p,l, MAX_LEDS_MIDDLE)], 255);
		}
		for (int l = 0; l < 8; l++) {
			digitalWrite(playerCircle[getPinIndex(p,l, MAX_LEDS_CIRCLE)], 255);
		}
		digitalWrite(SpecialButtonLED[p], 255);
	}
	if (includeIR) {
		digitalWrite(PIN_ADDRESS GLOBAL_IR, 255);
	}
}

void fullOff(boolean includeBoosterLEDs, boolean includeIR) {
	for (int p = 0; p < 4; p++) {
		for (int l = 0; l < 4; l++) {
			if (includeBoosterLEDs) {
				//digitalWrite(BOOSTER_LEDS[p][l], 0);
				digitalWrite(BOOSTER_LEDS[getPinIndex(p, l, MAX_LEDS_BOOSTER)],0);
			}
			digitalWrite(UVLEDs[getPinIndex(p,l, MAX_LEDS_UV)], 0);
		}
		for (int l = 0; l < 3; l++) {
			digitalWrite(RGB_LEDS[getPinIndex(p,l, MAX_LEDS_RGB)], 0);
		}
		for (int l = 0; l < 5; l++) {
			digitalWrite(playerMiddleColors[getPinIndex(p,l, MAX_LEDS_MIDDLE)], 0);
		}
		for (int l = 0; l < 8; l++) {
			digitalWrite(playerCircle[getPinIndex(p,l, MAX_LEDS_CIRCLE)], 0);
		}
		if (includeBoosterLEDs) {
			digitalWrite(SpecialButtonLED[p], 0);
		}
	}
	if (includeIR) {
		digitalWrite(PIN_ADDRESS GLOBAL_IR, 0);
	}
}

void fullOff() {
	fullOff(true,true);
}

void loadDefaultGameSettings() {
	//Speed Settings
	gameSettings.randomSpeed = true;
	gameSettings.startSpeed = NORMAL_MOTOR_SPEED;
	gameSettings.minSpeed = 49;
	gameSettings.maxSpeed = 120;
	gameSettings.speedMinDelay = 5000; //0 means: delay between speed steps is always the same
	gameSettings.speedMaxDelay = 12000;
	gameSettings.speedMinStepSize = 7;
	gameSettings.speedMaxStepSize = 30;
	gameSettings.enableReverse = true;

	//Chef Mode
	gameSettings.chefMode = false;
	gameSettings.chefRoulette = true;     //könnte man zusammenfassen
	gameSettings.chefChangeDelay = 7000; // indem man chefDelay auf 0 setzt und != 0
	gameSettings.chefHasShorterCooldown = true;

	gameSettings.enableItems = true;
	gameSettings.enableEvents= true;

	gameSettings.itemType[0] = TURBO;
	gameSettings.itemType[1] = SLOW;
	gameSettings.itemType[2] = CHANGE_DIR;
	gameSettings.itemType[3] = BLACKOUT;

	gameSettings.itemAutoRefillDelay = 0; // 0: no refill
	gameSettings.itemCooldownDelay = 5000; //individuell für jeden ItemTyp ?
	gameSettings.alternateCooldownMode = false; //true: erst wenn alle spieler ein item eingesetzt haben, können die anderen wieder ein item einsetzen

	gameSettings.enabledPlayers[0] = true;
	gameSettings.enabledPlayers[1] = true;
	gameSettings.enabledPlayers[2] = true;
	gameSettings.enabledPlayers[3] = true;
}

void inline BTprint(String message) {
	Serial1.print(message);
}

void setup()
{
	if (DEBUG) {
		Serial.begin(9600);
		Serial.setTimeout(50); //reduce delay from Serial.parseInt();//default is 1000ms
	}

	Log("setup");
	//init bluetooth
	if (BLUETOOTH) {
		Log("init bluetooth");
		Serial1.begin(9600); //TX1 & RX1 pins
	}

	// ********** Motor pins Setup **********
	setupMotor();

	// ********** PWM-COLOR pins Setup **********
	setupColorPins();

	// ********** Special Button Setup **********
	setupSpecialButtons();

	// ********** Special Button-LED Setup **********
	setupSpecialButtonLEDs();

	// ********** Speed Buttons Setup **********
	setupSpeedButtons();

	// ********** IR Setup **********
	setupLightBarriers();

	// ********** I/O-Expander 1 Setup **********
	setupBoosterLEDs();

	// ********** I/O-Expander 2 Setup **********
	setupUVLEDs();

	// ********** I/O-Expander 3 & 4 Setup **********
	setupCircleLEDs();

	// ********** middle circle setup **********
	setupMiddleColorLEDS();

	state = IDLE;
	standbyTmr = millis();
	randomSeed(analogRead(1)*micros());

	loadDefaultGameSettings();
	setIdleAnimations();

	Log("setup done.");
}

//unsigned long startDebugTime;

void loop()
{
	//startDebugTime = millis();

	switch (state) {
	case STANDBY:
		//any pressed button awakes from standby
		if (checkButtons()) {
			Log("Wake from Standby Mode");
			standbyTmr = millis(); //reset StandbyTimer
			state = IDLE;
			fullOn(false);
			for (int i = 1; i <= 4; i++) {
				setColor(i, PlayerColor[i - 1]);
			}
		}
		break;
	case IDLE:
		handleAnimations();
		if (checkButtons()) {
			standbyTmr = millis();
		}
		//check inputs -> reset standby_tmr
		if ((unsigned long)(millis() - standbyTmr) > STANDBY_DELAY) {
			Log("Switch to Standby Mode");
			state = STANDBY;
			//switch all LEDs off
			fullOff();
		}

		if (isButtonPressed(SpecialButton[0]) || isButtonPressed(SpecialButton[1]) || isButtonPressed(SpecialButton[2]) || isButtonPressed(SpecialButton[3])) {
			if (pressStartTmr == 0) {
				pressStartTmr = millis();
			}
			else if ((unsigned long)(millis() - pressStartTmr)>PRESS_START_DELAY) {
				pressStartTmr = 0;
				gameSettings.enabledPlayers[0] = true;
				gameSettings.enabledPlayers[1] = true;
				gameSettings.enabledPlayers[2] = true;
				gameSettings.enabledPlayers[3] = true;

				initGame();
			}
		}else{
			pressStartTmr = 0;
		}
		
		break;
	case GAME:
		gameLoop();
		break;
	default: Log("Unkown state");
	}

	
	if (DEBUG) {
		handleSerialInput();
	}

	if (BLUETOOTH) {
		//handleBTSerialInput();
	}

	/*unsigned long cycleTime = (millis() - startDebugTime);
	if (cycleTime > 10) {
		Log("Cycle Time: " + (String)cycleTime);
	}*/
}
