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


/*unsigned long idleAnimationTmr[8] = { 0,  0,  0,  0,  0,  0,  0, 0 };
long idleAnimationStep[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };

struct AnimationStep {
	AnimationStep(PIN_ADDRESS addr, uint8_t val) : address(addr), value(val) {};
	//AnimationStep(PIN_ADDRESS addr, uint8_t val, uint16_t delay) : address(addr), value(val), delayToNextStep(delay) {};
	PIN_ADDRESS address;
	uint8_t value;
	//uint16_t delayToNextStep;
};


template<int maxSteps, int maxLEDs>
struct Animation {
	static const int maxStep = maxSteps;
	static const int maxLED = maxLEDs;
	long delay;
	AnimationStep LEDs[maxSteps][maxLEDs];
};

const Animation<8, 1> idleAnimation1 = { 100,
{
	{ { PLAYER1_BOOSTER1, 255 } },
	{ { PLAYER1_BOOSTER2, 255 } },
	{ { PLAYER1_BOOSTER3, 255 } },
	{ { PLAYER1_BOOSTER4, 255 } },
	{ { PLAYER1_BOOSTER4, 0 } },
	{ { PLAYER1_BOOSTER3, 0 } },
	{ { PLAYER1_BOOSTER2, 0 } },
	{ { PLAYER1_BOOSTER1, 0 } },
}
};

const Animation<4, 6>  idleAnimation2 = { 150,
{
	{ { PLAYER4_COLOR_R,  0 },{ PLAYER4_COLOR_G, 0 },{ PLAYER4_COLOR_B, 0 },{ PLAYER1_COLOR_R,  255 },{ PLAYER1_COLOR_G, 0 },{ PLAYER1_COLOR_B, 0 } },
	{ { PLAYER1_COLOR_R,  0 },{ PLAYER1_COLOR_G, 0 },{ PLAYER1_COLOR_B, 0 },{ PLAYER2_COLOR_R,  80 },{ PLAYER2_COLOR_G, 0 },{ PLAYER2_COLOR_B, 80 } },
	{ { PLAYER2_COLOR_R,  0 },{ PLAYER2_COLOR_G, 0 },{ PLAYER2_COLOR_B, 0 },{ PLAYER3_COLOR_R,  255 },{ PLAYER3_COLOR_G, 100 },{ PLAYER3_COLOR_B, 0 } },
	{ { PLAYER3_COLOR_R,  0 },{ PLAYER3_COLOR_G, 0 },{ PLAYER3_COLOR_B, 0 },{ PLAYER4_COLOR_R,  0 },{ PLAYER4_COLOR_G, 255 },{ PLAYER4_COLOR_B, 0 } }
}
};

const Animation<8, 1> idleAnimation3 = { 100,
{
	{ { PLAYER2_BOOSTER1, 255 } },
	{ { PLAYER2_BOOSTER2, 255 } },
	{ { PLAYER2_BOOSTER3, 255 } },
	{ { PLAYER2_BOOSTER4, 255 } },
	{ { PLAYER2_BOOSTER4, 0 } },
	{ { PLAYER2_BOOSTER3, 0 } },
	{ { PLAYER2_BOOSTER2, 0 } },
	{ { PLAYER2_BOOSTER1, 0 } }
}
};

const Animation<8, 1> idleAnimation4 = { 100,
{
	{ { PLAYER3_BOOSTER1, 255 } },
	{ { PLAYER3_BOOSTER2, 255 } },
	{ { PLAYER3_BOOSTER3, 255 } },
	{ { PLAYER3_BOOSTER4, 255 } },
	{ { PLAYER3_BOOSTER4, 0 } },
	{ { PLAYER3_BOOSTER3, 0 } },
	{ { PLAYER3_BOOSTER2, 0 } },
	{ { PLAYER3_BOOSTER1, 0 } }
}
};

const Animation<8, 1> idleAnimation5 = { 100,
{
	{ { PLAYER4_BOOSTER1, 255 } },
	{ { PLAYER4_BOOSTER2, 255 } },
	{ { PLAYER4_BOOSTER3, 255 } },
	{ { PLAYER4_BOOSTER4, 255 } },
	{ { PLAYER4_BOOSTER4, 0 } },
	{ { PLAYER4_BOOSTER3, 0 } },
	{ { PLAYER4_BOOSTER2, 0 } },
	{ { PLAYER4_BOOSTER1, 0 } }
}
};

const Animation<2, 8> idleAnimation6 = { 1500,
{
	{ { PLAYER1_UV1, 255 },{ PLAYER1_UV2 , 255 },{ PLAYER2_UV1 , 255 },{ PLAYER2_UV2, 255 },{ PLAYER3_UV1, 255 },{ PLAYER3_UV2 , 255 },{ PLAYER4_UV1 , 255 },{ PLAYER4_UV2, 255 } },
	{ { PLAYER1_UV1, 0 },{ PLAYER1_UV2 , 0 },{ PLAYER2_UV1 , 0 },{ PLAYER2_UV2, 0 },{ PLAYER3_UV1, 0 },{ PLAYER3_UV2 , 0 },{ PLAYER4_UV1 , 0 },{ PLAYER4_UV2, 0 } }
}
};

const Animation<28, 2> middleSquence = { 24,
{
	{ { PIN_PLAYER1_LED1,255 },{ PIN_PLAYER4_LED5, 0 } },
	{ { PIN_PLAYER1_LED2,255 },{ PIN_PLAYER1_LED1, 0 } },
	{ { PIN_PLAYER1_LED3,255 },{ PIN_PLAYER1_LED2, 0 } },
	{ { PIN_PLAYER1_LED4,255 },{ PIN_PLAYER1_LED3, 0 } },
	{ { PIN_PLAYER1_LED5,255 },{ PIN_PLAYER1_LED4, 0 } },
	{ { PLAYER1_UV4, 255 },{ PLAYER2_UV4, 255 } },
	{ { PLAYER3_UV4, 255 },{ PLAYER4_UV4, 255 } },
	{ { PIN_PLAYER2_LED1,255 },{ PIN_PLAYER1_LED5, 0 } },
	{ { PIN_PLAYER2_LED2,255 },{ PIN_PLAYER2_LED1, 0 } },
	{ { PIN_PLAYER2_LED3,255 },{ PIN_PLAYER2_LED2, 0 } },
	{ { PIN_PLAYER2_LED4,255 },{ PIN_PLAYER2_LED3, 0 } },
	{ { PIN_PLAYER2_LED5,255 },{ PIN_PLAYER2_LED4, 0 } },
	{ { PLAYER1_UV3, 255 },{ PLAYER2_UV3, 255 } },
	{ { PLAYER3_UV3, 255 },{ PLAYER4_UV3, 255 } },
	{ { PIN_PLAYER3_LED1,255 },{ PIN_PLAYER2_LED5, 0 } },
	{ { PIN_PLAYER3_LED2,255 },{ PIN_PLAYER3_LED1, 0 } },
	{ { PIN_PLAYER3_LED3,255 },{ PIN_PLAYER3_LED2, 0 } },
	{ { PIN_PLAYER3_LED4,255 },{ PIN_PLAYER3_LED3, 0 } },
	{ { PIN_PLAYER3_LED5,255 },{ PIN_PLAYER3_LED4, 0 } },
	{ { PLAYER1_UV4, 0 },{ PLAYER2_UV4, 0 } },
	{ { PLAYER3_UV4, 0 },{ PLAYER4_UV4, 0 } },
	{ { PIN_PLAYER4_LED1,255 },{ PIN_PLAYER3_LED5, 0 } },
	{ { PIN_PLAYER4_LED2,255 },{ PIN_PLAYER4_LED1, 0 } },
	{ { PIN_PLAYER4_LED3,255 },{ PIN_PLAYER4_LED2, 0 } },
	{ { PIN_PLAYER4_LED4,255 },{ PIN_PLAYER4_LED3, 0 } },
	{ { PIN_PLAYER4_LED5,255 },{ PIN_PLAYER4_LED4, 0 } },
	{ { PLAYER1_UV3, 0 },{ PLAYER2_UV3, 0 } },
	{ { PLAYER3_UV3, 0 },{ PLAYER4_UV3, 0 } }
}
};

const Animation<32, 2> circleSquence = { 21,
{
	{ { PLAYER2_CIRCLE4,255 },{ PLAYER2_CIRCLE3, 0 } },
	{ { PLAYER2_CIRCLE5,255 },{ PLAYER2_CIRCLE4, 0 } },
	{ { PLAYER2_CIRCLE6,255 },{ PLAYER2_CIRCLE5, 0 } },
	{ { PLAYER2_CIRCLE7,255 },{ PLAYER2_CIRCLE6, 0 } },
	{ { PLAYER2_CIRCLE8,255 },{ PLAYER2_CIRCLE7, 0 } },

	{ { PLAYER3_CIRCLE1,255 },{ PLAYER2_CIRCLE8, 0 } },
	{ { PLAYER3_CIRCLE2,255 },{ PLAYER3_CIRCLE1, 0 } },
	{ { PLAYER3_CIRCLE3,255 },{ PLAYER3_CIRCLE2, 0 } },
	{ { PLAYER3_CIRCLE4,255 },{ PLAYER3_CIRCLE3, 0 } },
	{ { PLAYER3_CIRCLE5,255 },{ PLAYER3_CIRCLE4, 0 } },
	{ { PLAYER3_CIRCLE6,255 },{ PLAYER3_CIRCLE5, 0 } },
	{ { PLAYER3_CIRCLE7,255 },{ PLAYER3_CIRCLE6, 0 } },
	{ { PLAYER3_CIRCLE8,255 },{ PLAYER3_CIRCLE7, 0 } },

	{ { PLAYER4_CIRCLE1,255 },{ PLAYER3_CIRCLE8, 0 } },
	{ { PLAYER4_CIRCLE2,255 },{ PLAYER4_CIRCLE1, 0 } },
	{ { PLAYER4_CIRCLE3,255 },{ PLAYER4_CIRCLE2, 0 } },
	{ { PLAYER4_CIRCLE4,255 },{ PLAYER4_CIRCLE3, 0 } },
	{ { PLAYER4_CIRCLE5,255 },{ PLAYER4_CIRCLE4, 0 } },
	{ { PLAYER4_CIRCLE6,255 },{ PLAYER4_CIRCLE5, 0 } },
	{ { PLAYER4_CIRCLE7,255 },{ PLAYER4_CIRCLE6, 0 } },
	{ { PLAYER4_CIRCLE8,255 },{ PLAYER4_CIRCLE7, 0 } },

	{ { PLAYER1_CIRCLE1,255 },{ PLAYER4_CIRCLE8, 0 } },
	{ { PLAYER1_CIRCLE2,255 },{ PLAYER1_CIRCLE1, 0 } },
	{ { PLAYER1_CIRCLE3,255 },{ PLAYER1_CIRCLE2, 0 } },
	{ { PLAYER1_CIRCLE4,255 },{ PLAYER1_CIRCLE3, 0 } },
	{ { PLAYER1_CIRCLE5,255 },{ PLAYER1_CIRCLE4, 0 } },
	{ { PLAYER1_CIRCLE6,255 },{ PLAYER1_CIRCLE5, 0 } },
	{ { PLAYER1_CIRCLE7,255 },{ PLAYER1_CIRCLE6, 0 } },
	{ { PLAYER1_CIRCLE8,255 },{ PLAYER1_CIRCLE7, 0 } },

	{ { PLAYER2_CIRCLE1,255 },{ PLAYER1_CIRCLE8, 0 } },
	{ { PLAYER2_CIRCLE2,255 },{ PLAYER2_CIRCLE1, 0 } },
	{ { PLAYER2_CIRCLE3,255 },{ PLAYER2_CIRCLE2, 0 } }
}
};

const Animation<4, 32> circleSquence2 = { 25,
{
	{ { PLAYER1_CIRCLE1,255 },{ PLAYER1_CIRCLE2,255 },{ PLAYER1_CIRCLE3,255 },{ PLAYER1_CIRCLE4,255 },{ PLAYER1_CIRCLE5,255 },{ PLAYER1_CIRCLE6,255 },{ PLAYER1_CIRCLE7,255 },{ PLAYER1_CIRCLE8,255 },
	{ PLAYER2_CIRCLE1,255 },{ PLAYER2_CIRCLE2,255 },{ PLAYER2_CIRCLE3,255 },{ PLAYER2_CIRCLE4,255 },{ PLAYER2_CIRCLE5,255 },{ PLAYER2_CIRCLE6,255 },{ PLAYER2_CIRCLE7,255 },{ PLAYER2_CIRCLE8,255 },
	{ PLAYER3_CIRCLE1,255 },{ PLAYER3_CIRCLE2,255 },{ PLAYER3_CIRCLE3,255 },{ PLAYER3_CIRCLE4,255 },{ PLAYER3_CIRCLE5,255 },{ PLAYER3_CIRCLE6,255 },{ PLAYER3_CIRCLE7,255 },{ PLAYER3_CIRCLE8,255 },
	{ PLAYER4_CIRCLE1,255 },{ PLAYER4_CIRCLE2,255 },{ PLAYER4_CIRCLE3,255 },{ PLAYER4_CIRCLE4,255 },{ PLAYER4_CIRCLE5,255 },{ PLAYER4_CIRCLE6,255 },{ PLAYER4_CIRCLE7,255 },{ PLAYER4_CIRCLE8,255 } },

	{ { PLAYER1_CIRCLE1,0 },{ PLAYER1_CIRCLE2,0 },{ PLAYER1_CIRCLE3,0 },{ PLAYER1_CIRCLE4,0 },{ PLAYER1_CIRCLE5,0 },{ PLAYER1_CIRCLE6,0 },{ PLAYER1_CIRCLE7,0 },{ PLAYER1_CIRCLE8,0 },
	{ PLAYER2_CIRCLE1,0 },{ PLAYER2_CIRCLE2,0 },{ PLAYER2_CIRCLE3,0 },{ PLAYER2_CIRCLE4,0 },{ PLAYER2_CIRCLE5,0 },{ PLAYER2_CIRCLE6,0 },{ PLAYER2_CIRCLE7,0 },{ PLAYER2_CIRCLE8,0 },
	{ PLAYER3_CIRCLE1,0 },{ PLAYER3_CIRCLE2,0 },{ PLAYER3_CIRCLE3,0 },{ PLAYER3_CIRCLE4,0 },{ PLAYER3_CIRCLE5,0 },{ PLAYER3_CIRCLE6,0 },{ PLAYER3_CIRCLE7,0 },{ PLAYER3_CIRCLE8,0 },
	{ PLAYER4_CIRCLE1,0 },{ PLAYER4_CIRCLE2,0 },{ PLAYER4_CIRCLE3,0 },{ PLAYER4_CIRCLE4,0 },{ PLAYER4_CIRCLE5,0 },{ PLAYER4_CIRCLE6,0 },{ PLAYER4_CIRCLE7,0 },{ PLAYER4_CIRCLE8,0 } },

	{ { PLAYER1_CIRCLE1,0 },{ PLAYER1_CIRCLE2,0 },{ PLAYER1_CIRCLE3,0 },{ PLAYER1_CIRCLE4,0 },{ PLAYER1_CIRCLE5,0 },{ PLAYER1_CIRCLE6,0 },{ PLAYER1_CIRCLE7,0 },{ PLAYER1_CIRCLE8,0 },
	{ PLAYER2_CIRCLE1,0 },{ PLAYER2_CIRCLE2,0 },{ PLAYER2_CIRCLE3,0 },{ PLAYER2_CIRCLE4,0 },{ PLAYER2_CIRCLE5,0 },{ PLAYER2_CIRCLE6,0 },{ PLAYER2_CIRCLE7,0 },{ PLAYER2_CIRCLE8,0 },
	{ PLAYER3_CIRCLE1,0 },{ PLAYER3_CIRCLE2,0 },{ PLAYER3_CIRCLE3,0 },{ PLAYER3_CIRCLE4,0 },{ PLAYER3_CIRCLE5,0 },{ PLAYER3_CIRCLE6,0 },{ PLAYER3_CIRCLE7,0 },{ PLAYER3_CIRCLE8,0 },
	{ PLAYER4_CIRCLE1,0 },{ PLAYER4_CIRCLE2,0 },{ PLAYER4_CIRCLE3,0 },{ PLAYER4_CIRCLE4,0 },{ PLAYER4_CIRCLE5,0 },{ PLAYER4_CIRCLE6,0 },{ PLAYER4_CIRCLE7,0 },{ PLAYER4_CIRCLE8,0 } },

	{ { PLAYER1_CIRCLE1,0 },{ PLAYER1_CIRCLE2,0 },{ PLAYER1_CIRCLE3,0 },{ PLAYER1_CIRCLE4,0 },{ PLAYER1_CIRCLE5,0 },{ PLAYER1_CIRCLE6,0 },{ PLAYER1_CIRCLE7,0 },{ PLAYER1_CIRCLE8,0 },
	{ PLAYER2_CIRCLE1,0 },{ PLAYER2_CIRCLE2,0 },{ PLAYER2_CIRCLE3,0 },{ PLAYER2_CIRCLE4,0 },{ PLAYER2_CIRCLE5,0 },{ PLAYER2_CIRCLE6,0 },{ PLAYER2_CIRCLE7,0 },{ PLAYER2_CIRCLE8,0 },
	{ PLAYER3_CIRCLE1,0 },{ PLAYER3_CIRCLE2,0 },{ PLAYER3_CIRCLE3,0 },{ PLAYER3_CIRCLE4,0 },{ PLAYER3_CIRCLE5,0 },{ PLAYER3_CIRCLE6,0 },{ PLAYER3_CIRCLE7,0 },{ PLAYER3_CIRCLE8,0 },
	{ PLAYER4_CIRCLE1,0 },{ PLAYER4_CIRCLE2,0 },{ PLAYER4_CIRCLE3,0 },{ PLAYER4_CIRCLE4,0 },{ PLAYER4_CIRCLE5,0 },{ PLAYER4_CIRCLE6,0 },{ PLAYER4_CIRCLE7,0 },{ PLAYER4_CIRCLE8,0 } }
}
};

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
}*/

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

boolean isButtonPressed(PIN_ADDRESS pin) {
	if (pin.pin >= 100) {
		return digitalRead(pin) == LOW;
	}
	else {
		return digitalRead(pin) == LOW;
	}
}

boolean checkButtons() {
	return isButtonPressed(BUTTON_INC_SPEED_PLAYER1) || isButtonPressed(BUTTON_DEC_SPEED_PLAYER1)
		|| isButtonPressed(BUTTON_INC_SPEED_PLAYER2) || isButtonPressed(BUTTON_DEC_SPEED_PLAYER2)
		|| isButtonPressed(BUTTON_INC_SPEED_PLAYER3) || isButtonPressed(BUTTON_DEC_SPEED_PLAYER3)
		|| isButtonPressed(BUTTON_INC_SPEED_PLAYER4) || isButtonPressed(BUTTON_DEC_SPEED_PLAYER4)
		|| isButtonPressed(PLAYER1_SPECIAL_BUTTON)
		|| isButtonPressed(PLAYER2_SPECIAL_BUTTON)
		|| isButtonPressed(PLAYER3_SPECIAL_BUTTON)
		|| isButtonPressed(PLAYER4_SPECIAL_BUTTON);
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

void setColor(const uint8_t player, const uint8_t r, const uint8_t g, const uint8_t b) {
	analogWrite(RGB_LEDS[player - 1][0], r);
	analogWrite(RGB_LEDS[player - 1][1], g);
	analogWrite(RGB_LEDS[player - 1][2], b);
}

void setColor(const uint8_t player, const Color color) {
	setColor(player, color.r, color.g, color.b);
}


void testFullOn() {
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

	Log("setup done.");

		testFullOn();
}

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
	}
}

void loop()
{
	Log("wert: " + (String)(analogRead(0)));

	switch (state) {
	case STANDBY:
		//any pressed button awakes from standby
		if (checkButtons()) {
			Log("Wake from Standby Mode");
			standbyTmr = millis(); //reset StandbyTimer
			state = IDLE;
		}
		break;
	case  IDLE:
		//idleAnimations(); // Play Idle Animations
		if (checkButtons()) {
			standbyTmr = millis();
		}
		//check inputs -> reset standby_tmr
		if ((unsigned long)(millis() - standbyTmr) > STANDBY_DELAY) {
			Log("Switch to Standby Mode");
			state = STANDBY;
			//switch all LEDs off
			int l;
			for (int p = 0; p < 4; p++) {
				for (l = 0; l < 4; l++) {
					digitalWrite(BOOSTER_LEDS[p][l], LOW);
					digitalWrite(UVLEDs[p][l], LOW);
				}
				for (l = 0; l < 3; l++) {
					digitalWrite(RGB_LEDS[p][l], LOW);
				}
				for (l = 0; l < 5; l++) {
					digitalWrite(playerMiddleColors[p][l], LOW);
				}
				for (l = 0; l < 8; l++) {
					digitalWrite(playerCircle[p][l], LOW);

				}
				digitalWrite(SpecialButtonLED[p], LOW);
			}
			digitalWrite(PIN_ADDRESS GLOBAL_IR, LOW);
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
