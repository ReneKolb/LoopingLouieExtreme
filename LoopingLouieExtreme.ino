#define DEBUG true

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

void digitalWrite(const PIN_ADDRESS pinAddress, const uint8_t value) {
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


void updatePlayerBoosterLEDs(const uint8_t player, const uint8_t amount) {
	for (int i = 0; i < 4; i++) {
		if (amount > i) {
			digitalWrite(BOOSTER_LEDS[player - 1][i], HIGH);
		}
		else {
			digitalWrite(BOOSTER_LEDS[player - 1][i], LOW);
		}
	}
}

boolean playerChip(uint8_t player, uint8_t chip) {
	return analogRead(PlayerIRPins[player-1][chip-1].pin-100) < IR_THRESHOLD;
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
	analogWrite(RGB_LEDS[player - 1][0], r);
	analogWrite(RGB_LEDS[player - 1][1], g);
	analogWrite(RGB_LEDS[player - 1][2], b);
}

void setColor(const uint8_t player, const Color color) {
	setColor(player, color.r, color.g, color.b);
}

void DoAnimationStep(const AnimationStep leds[], int amount) {
	for (int i = 0; i < amount; i++) {
		if (leds[i].address.board != NONE.board && leds[i].address.pin != NONE.pin) {
			if (leds[i].value == 0) {
				digitalWrite(leds[i].address, 0);
			}
			else if (leds[i].value == 255) {
				digitalWrite(leds[i].address, HIGH);
			}
			else {
				analogWrite(leds[i].address, leds[i].value); //custom analogWrite
			}
		}
	}
}


void fullOn() {
	for (int p = 0; p < 4; p++) {
		for (int l = 0; l < 4; l++) {
			digitalWrite(BOOSTER_LEDS[p][l], 255);
			digitalWrite(UVLEDs[p][l], 255);
		}
		for (int l = 0; l < 3; l++) {
			digitalWrite(RGB_LEDS[p][l], 255);
		}
		for (int l = 0; l < 5; l++) {
			digitalWrite(playerMiddleColors[p][l], 255);
		}
		for (int l = 0; l < 8; l++) {
			digitalWrite(playerCircle[p][l], 255);
		}
		digitalWrite(SpecialButtonLED[p], 255);
	}
	digitalWrite(PIN_ADDRESS GLOBAL_IR, 255);
}

void fullOff(boolean includeBoosterLEDs, boolean includeIR) {
	for (int p = 0; p < 4; p++) {
		for (int l = 0; l < 4; l++) {
			if (includeBoosterLEDs) {
				digitalWrite(BOOSTER_LEDS[p][l], 0);
			}
			digitalWrite(UVLEDs[p][l], 0);
		}
		for (int l = 0; l < 3; l++) {
			digitalWrite(RGB_LEDS[p][l], 0);
		}
		for (int l = 0; l < 5; l++) {
			digitalWrite(playerMiddleColors[p][l], 0);
		}
		for (int l = 0; l < 8; l++) {
			digitalWrite(playerCircle[p][l], 0);
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

void idleAnimations() {
	if ((unsigned long)(millis() - idleAnimationTmr[0]) > idleAnimation1.delay) {
		idleAnimationTmr[0] = millis();
		idleAnimationStep[0]++;
		if (idleAnimationStep[0] >= idleAnimation1.maxStep) {
			idleAnimationStep[0] = 0;
		}
		DoAnimationStep(idleAnimation1.LEDs[idleAnimationStep[0]], idleAnimation1.maxLED);
	}

	if ((unsigned long)(millis() - idleAnimationTmr[1]) > idleAnimation2.delay) {
		idleAnimationTmr[1] = millis();
		idleAnimationStep[1]++;
		if (idleAnimationStep[1] >= idleAnimation2.maxStep) {
			idleAnimationStep[1] = 0;
		}
		DoAnimationStep(idleAnimation2.LEDs[idleAnimationStep[1]], idleAnimation2.maxLED);
	}

	if ((unsigned long)(millis() - idleAnimationTmr[2]) > idleAnimation3.delay) {
		idleAnimationTmr[2] = millis();
		idleAnimationStep[2]++;
		if (idleAnimationStep[2] >= idleAnimation3.maxStep) {
			idleAnimationStep[2] = 0;
		}
		DoAnimationStep(idleAnimation3.LEDs[idleAnimationStep[2]], idleAnimation3.maxLED);
	}

	if ((unsigned long)(millis() - idleAnimationTmr[3]) > idleAnimation4.delay) {
		idleAnimationTmr[3] = millis();
		idleAnimationStep[3]++;
		if (idleAnimationStep[3] >= idleAnimation4.maxStep) {
			idleAnimationStep[3] = 0;
		}
		DoAnimationStep(idleAnimation4.LEDs[idleAnimationStep[3]], idleAnimation4.maxLED);
	}

	if ((unsigned long)(millis() - idleAnimationTmr[4]) > idleAnimation5.delay) {
		idleAnimationTmr[4] = millis();
		idleAnimationStep[4]++;
		if (idleAnimationStep[4] >= idleAnimation5.maxStep) {
			idleAnimationStep[4] = 0;
		}
		DoAnimationStep(idleAnimation5.LEDs[idleAnimationStep[4]], idleAnimation5.maxLED);
	}

	if ((unsigned long)(millis() - idleAnimationTmr[5]) > idleAnimation6.delay) {
		idleAnimationTmr[5] = millis();
		idleAnimationStep[5]++;
		if (idleAnimationStep[5] >= idleAnimation6.maxStep) {
			idleAnimationStep[5] = 0;
		}
		DoAnimationStep(idleAnimation6.LEDs[idleAnimationStep[5]], idleAnimation6.maxLED);
	}

	if ((unsigned long)(millis() - idleAnimationTmr[6]) > middleSquence.delay) {
		idleAnimationTmr[6] = millis();
		idleAnimationStep[6]++;
		if (idleAnimationStep[6] >= middleSquence.maxStep) {
			idleAnimationStep[6] = 0;
		}
		DoAnimationStep(middleSquence.LEDs[idleAnimationStep[6]], middleSquence.maxLED);
	}

	if ((unsigned long)(millis() - idleAnimationTmr[7]) > circleSquence.delay) {
		idleAnimationTmr[7] = millis();
		idleAnimationStep[7]++;
		if (idleAnimationStep[7] >= circleSquence.maxStep) {
			idleAnimationStep[7] = 0;
		}
		DoAnimationStep(circleSquence.LEDs[idleAnimationStep[7]], circleSquence.maxLED);
	}

	/*if ((unsigned long)(millis() - idleAnimationTmr[7]) > nochntest.delay) {
		idleAnimationTmr[7] = millis();
		idleAnimationStep[7]++;
		if (idleAnimationStep[7] >= nochntest.maxStep) {
			idleAnimationStep[7] = 0;
		}
		DoAnimationStep(nochntest.LEDs[idleAnimationStep[7]], nochntest.maxLED);
	}*/
}

void loadDefaultGameSettings() {
	//Speed Settings
	gameSettings.randomSpeed = false;
	gameSettings.startSpeed = NORMAL_MOTOR_SPEED;
	gameSettings.speedMinDelay = 5000; //0 means: delay between speed steps is always the same
	gameSettings.speedMaxDelay = 12000;
	gameSettings.speedMinStepSize = 7;
	gameSettings.speedMaxStepSize = 30;
	gameSettings.enableReverse = true;

	//Chef Mode
	gameSettings.chefMode = true;
	gameSettings.chefRoulette = true;     //könnte man zusammenfassen
	gameSettings.chefChangeDelay = 7000; // indem man chefDelay auf 0 setzt und != 0
	gameSettings.chefHasShorterCooldown = true;

	gameSettings.enableItems = true;
	gameSettings.enableEvents= true;

	gameSettings.itemType[0] = TURBO;
	gameSettings.itemType[1] = SLOW;
	gameSettings.itemType[2] = CHANGE_DIR;
	gameSettings.itemType[3] = SLOW;

	gameSettings.itemAutoRefillDelay = 0; // 0: no refill
	gameSettings.itemCooldownDelay = 5000; //individuell für jeden ItemTyp ?
	gameSettings.alternateCooldownMode = false; //true: erst wenn alle spieler ein item eingesetzt haben, können die anderen wieder ein item einsetzen
}

void setup()
{
	if (DEBUG) {
		Serial.begin(9600);
		Serial.setTimeout(50); //reduce delay from Serial.parseInt();//default is 1000ms
	}

	Log("setup");

	//init bluetooth
	//if (BLUETOOTH) {
//		Log("init bluetooth");
		//Serial1.begin(9600); //TX1 & RX1 pins
	//}

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

	Log("setup done.");

	fullOn();
//	digitalWrite(PIN_ADDRESS GLOBAL_IR, LOW);
}

/*
int received;
long received_LONG;
int data;

void handleSerialInput() {
	//Handle DEBUG Serial Commands
	if (Serial.available()) {
		//first char is action type
		data = Serial.read();

		Log("Received Action-Byte: " + (String)data);
		//Rest is Data
		if (data == 'm') {
			//MANUAL MOTOR CONTROL
			received_LONG = Serial.parseInt(); //only for testing (delay reduced by setTimeout() )
			if (received_LONG > 170) {
				received_LONG = 170;
			}
			else if (received_LONG < -170) {
				received_LONG = -170;
			}

			if (received_LONG > 0) {
				setMotorSpeed(true, received_LONG);
			}
			else {
				setMotorSpeed(false, -received_LONG);
			}
		}
		else if (data == 'p') {
			int value;
			value = Serial.parseInt();
			Log("Value: " + (String)value);
			digitalWrite(PIN_ADDRESS{ 2,value }, HIGH);
		}
		else if (data == 's') {
			initGame();
		}
		else if (data == 'i') {
			digitalWrite(PIN_ADDRESS GLOBAL_IR, HIGH);
			Log("Global IR on");
		}
		else if (data == 'o') {
			digitalWrite(PIN_ADDRESS GLOBAL_IR, LOW);
			Log("Global IR off");
		}
		else if (data == 'r') {
			Log("IR status:");
			Log(" 4 \t| 1 \t| 2 \t| 3");
			Log("0: " + (String)(analogRead(0)) + "\t|3: " + (String)(analogRead(3)) + "\t|6: " + (String)(analogRead(6)) + "\t|9: " + (String)(analogRead(9)));
			Log("1: " + (String)(analogRead(1)) + "\t|4: " + (String)(analogRead(4)) + "\t|7: " + (String)(analogRead(7)) + "\t|10: " + (String)(analogRead(10)));
			Log("2: " + (String)(analogRead(2)) + "\t|5: " + (String)(analogRead(5)) + "\t|8: " + (String)(analogRead(8)) + "\t|11: " + (String)(analogRead(11)));
			Log("  "+(String)getPlayerChipAmount(4)+"\t|  "+(String)getPlayerChipAmount(1) + "\t|  " + (String)getPlayerChipAmount(2) + "\t|  " + (String)getPlayerChipAmount(3));
		}
		else if (data == 'q') {
			int value = Serial.parseInt();
			//value = player [1..4]
			Log("0: "+(String)analogRead(PlayerIRPins[value - 1][0].pin - 100));
			Log("1: " + (String)analogRead(PlayerIRPins[value - 1][1].pin - 100));
			Log("2: " + (String)analogRead(PlayerIRPins[value - 1][2].pin - 100));
		}
	}
}*/

void loop()
{
	switch (state) {
	case STANDBY:
		//any pressed button awakes from standby
		if (checkButtons()) {
			Log("Wake from Standby Mode");
			standbyTmr = millis(); //reset StandbyTimer
			state = IDLE;
			fullOn();
		}
		break;
	case  IDLE:
		idleAnimations(); // Play Idle Animations
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
				initGame();
			}
		}else{
			pressStartTmr = 0;
		}
		
		break;
	case GAME:
		//gameLoop();
		gameLoop();

		//global IR -> HIGH!!
		//after game -> LOW
		//actual game
		break;
	default: Log("Unkown state");
	}

	
	if (DEBUG) {
		handleSerialInput();
	}
}
