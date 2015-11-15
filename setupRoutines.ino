void setupMotor() {
	Log("setup Motor");
	pinMode((PIN_ADDRESS MOTOR_SPEED).pin, OUTPUT);
	pinMode((PIN_ADDRESS MOTOR_DIRECTION_A).pin, OUTPUT);
	pinMode((PIN_ADDRESS MOTOR_DIRECTION_B).pin, OUTPUT);

	digitalWrite(PIN_ADDRESS MOTOR_DIRECTION_A, LOW);
	digitalWrite(PIN_ADDRESS MOTOR_DIRECTION_B, LOW);
	analogWrite((PIN_ADDRESS MOTOR_SPEED), 0);
}

void setupColorPins() {
	Log("setup Color Pins");
	pinMode((PIN_ADDRESS PLAYER1_COLOR_R).pin, OUTPUT);
	pinMode((PIN_ADDRESS PLAYER1_COLOR_G).pin, OUTPUT);
	pinMode((PIN_ADDRESS PLAYER1_COLOR_B).pin, OUTPUT);
	setColor(1, Color RED);

	pinMode((PIN_ADDRESS PLAYER2_COLOR_R).pin, OUTPUT);
	pinMode((PIN_ADDRESS PLAYER2_COLOR_G).pin, OUTPUT);
	pinMode((PIN_ADDRESS PLAYER2_COLOR_B).pin, OUTPUT);
	setColor(2, Color PURPLE);

	pinMode((PIN_ADDRESS PLAYER3_COLOR_R).pin, OUTPUT);
	pinMode((PIN_ADDRESS PLAYER3_COLOR_G).pin, OUTPUT);
	pinMode((PIN_ADDRESS PLAYER3_COLOR_B).pin, OUTPUT);
	setColor(3, Color YELLOW);

	pinMode((PIN_ADDRESS PLAYER4_COLOR_R).pin, OUTPUT);
	pinMode((PIN_ADDRESS PLAYER4_COLOR_G).pin, OUTPUT);
	pinMode((PIN_ADDRESS PLAYER4_COLOR_B).pin, OUTPUT);
	setColor(4, Color GREEN);
}

void setupSpecialButtons() {
	Log("setup Special Buttons");
	pinMode((PIN_ADDRESS PLAYER1_SPECIAL_BUTTON).pin, INPUT);
	digitalWrite(PIN_ADDRESS PLAYER1_SPECIAL_BUTTON, HIGH); //enable Pullup-resistor
	pinMode((PIN_ADDRESS PLAYER2_SPECIAL_BUTTON).pin, INPUT);
	digitalWrite(PIN_ADDRESS PLAYER2_SPECIAL_BUTTON, HIGH); //enable Pullup-resistor
	pinMode((PIN_ADDRESS PLAYER3_SPECIAL_BUTTON).pin, INPUT);
	digitalWrite(PIN_ADDRESS PLAYER3_SPECIAL_BUTTON, HIGH); //enable Pullup-resistor
	pinMode((PIN_ADDRESS PLAYER4_SPECIAL_BUTTON).pin, INPUT);
	digitalWrite(PIN_ADDRESS PLAYER4_SPECIAL_BUTTON, HIGH); //enable Pullup-resistor
}

void setupSpecialButtonLEDs() {
	Log("setup Special Button LEDS");
	pinMode((PIN_ADDRESS PLAYER1_SPECIAL_BUTTON_LED).pin, OUTPUT);
	pinMode((PIN_ADDRESS PLAYER2_SPECIAL_BUTTON_LED).pin, OUTPUT);
	pinMode((PIN_ADDRESS PLAYER3_SPECIAL_BUTTON_LED).pin, OUTPUT);
	pinMode((PIN_ADDRESS PLAYER4_SPECIAL_BUTTON_LED).pin, OUTPUT);
}

void setupSpeedButtons() {
	Log("setup Speed Buttons");

	pinMode(A12, INPUT);
	digitalWrite(A12, HIGH); // enable AnalogInput pullup resistor
	pinMode(A13, INPUT);
	digitalWrite(A13, HIGH); // enable AnalogInput pullup resistor
	pinMode(A14, INPUT);
	digitalWrite(A14, HIGH); // enable AnalogInput pullup resistor
	pinMode(A15, INPUT);
	digitalWrite(A15, HIGH); // enable AnalogInput pullup resistor

	pinMode((PIN_ADDRESS BUTTON_INC_SPEED_PLAYER1).pin, INPUT);
	digitalWrite(PIN_ADDRESS BUTTON_INC_SPEED_PLAYER1, HIGH);
	pinMode((PIN_ADDRESS BUTTON_DEC_SPEED_PLAYER1).pin, INPUT);
	digitalWrite(PIN_ADDRESS BUTTON_DEC_SPEED_PLAYER1, HIGH);
	pinMode((PIN_ADDRESS BUTTON_INC_SPEED_PLAYER4).pin, INPUT);
	digitalWrite(PIN_ADDRESS BUTTON_INC_SPEED_PLAYER4, HIGH);
	pinMode((PIN_ADDRESS BUTTON_DEC_SPEED_PLAYER4).pin, INPUT);
	digitalWrite(PIN_ADDRESS BUTTON_DEC_SPEED_PLAYER4, HIGH);
}

void setupLightBarriers() {
	Log("setup Light Barriers");
	pinMode((PIN_ADDRESS GLOBAL_IR).pin, OUTPUT);
	digitalWrite(PIN_ADDRESS GLOBAL_IR, LOW);

	pinMode(A0, INPUT);
	digitalWrite(A0, HIGH);  // disable AnalogInput pullup resistor
	pinMode(A1, INPUT);
	digitalWrite(A1, HIGH);  // disable AnalogInput pullup resistor
	pinMode(A2, INPUT);
	digitalWrite(A2, HIGH);  // disable AnalogInput pullup resistor
	pinMode(A3, INPUT);
	digitalWrite(A3, HIGH);  // disable AnalogInput pullup resistor
	pinMode(A4, INPUT);
	digitalWrite(A4, HIGH);  // disable AnalogInput pullup resistor
	pinMode(A5, INPUT);
	digitalWrite(A5, HIGH);  // disable AnalogInput pullup resistor
	pinMode(A6, INPUT);
	digitalWrite(A6, HIGH);  // disable AnalogInput pullup resistor
	pinMode(A7, INPUT);
	digitalWrite(A7, HIGH);  // disable AnalogInput pullup resistor
	pinMode(A8, INPUT);
	digitalWrite(A8, HIGH);  // disable AnalogInput pullup resistor
	pinMode(A9, INPUT);
	digitalWrite(A9, HIGH);  // disable AnalogInput pullup resistor
	pinMode(A10, INPUT);
	digitalWrite(A10, HIGH);  // disable AnalogInput pullup resistor
	pinMode(A11, INPUT);
	digitalWrite(A11, HIGH);  // disable AnalogInput pullup resistor

	//12-15 are speed buttons
/*	pinMode(A12, INPUT);
	digitalWrite(A12, LOW);
	pinMode(A13, INPUT);
	digitalWrite(A13, LOW);
	pinMode(A14, INPUT);
	digitalWrite(A14, LOW);
	pinMode(A15, INPUT);
	digitalWrite(A15, LOW);*/
}

void setupBoosterLEDs() {
	Log("setup Booster LEDs");
	mcpBoosterLEDs.begin(0); // all address pins on ground.
	mcpBoosterLEDs.pinMode((PIN_ADDRESS PLAYER1_BOOSTER1).pin, OUTPUT);
	mcpBoosterLEDs.pinMode((PIN_ADDRESS PLAYER1_BOOSTER2).pin, OUTPUT);
	mcpBoosterLEDs.pinMode((PIN_ADDRESS PLAYER1_BOOSTER3).pin, OUTPUT);
	mcpBoosterLEDs.pinMode((PIN_ADDRESS PLAYER1_BOOSTER4).pin, OUTPUT);
	updatePlayerBoosterLEDs(1, 0);

	mcpBoosterLEDs.pinMode((PIN_ADDRESS PLAYER2_BOOSTER1).pin, OUTPUT);
	mcpBoosterLEDs.pinMode((PIN_ADDRESS PLAYER2_BOOSTER2).pin, OUTPUT);
	mcpBoosterLEDs.pinMode((PIN_ADDRESS PLAYER2_BOOSTER3).pin, OUTPUT);
	mcpBoosterLEDs.pinMode((PIN_ADDRESS PLAYER2_BOOSTER4).pin, OUTPUT);
	updatePlayerBoosterLEDs(2, 0);

	mcpBoosterLEDs.pinMode((PIN_ADDRESS PLAYER3_BOOSTER1).pin, OUTPUT);
	mcpBoosterLEDs.pinMode((PIN_ADDRESS PLAYER3_BOOSTER2).pin, OUTPUT);
	mcpBoosterLEDs.pinMode((PIN_ADDRESS PLAYER3_BOOSTER3).pin, OUTPUT);
	mcpBoosterLEDs.pinMode((PIN_ADDRESS PLAYER3_BOOSTER4).pin, OUTPUT);
	updatePlayerBoosterLEDs(3, 0);

	mcpBoosterLEDs.pinMode((PIN_ADDRESS PLAYER4_BOOSTER1).pin, OUTPUT);
	mcpBoosterLEDs.pinMode((PIN_ADDRESS PLAYER4_BOOSTER2).pin, OUTPUT);
	mcpBoosterLEDs.pinMode((PIN_ADDRESS PLAYER4_BOOSTER3).pin, OUTPUT);
	mcpBoosterLEDs.pinMode((PIN_ADDRESS PLAYER4_BOOSTER4).pin, OUTPUT);
	updatePlayerBoosterLEDs(4, 0);
}

void setupUVLEDs() {
	Log("setup UV LEDs");
	mcpUVLEDs.begin(1);
	mcpUVLEDs.pinMode((PIN_ADDRESS PLAYER1_UV1).pin, OUTPUT);
	mcpUVLEDs.pinMode((PIN_ADDRESS PLAYER2_UV2).pin, OUTPUT);
	mcpUVLEDs.pinMode((PIN_ADDRESS PLAYER2_UV1).pin, OUTPUT);
	mcpUVLEDs.pinMode((PIN_ADDRESS PLAYER3_UV2).pin, OUTPUT);
	mcpUVLEDs.pinMode((PIN_ADDRESS PLAYER3_UV1).pin, OUTPUT);
	mcpUVLEDs.pinMode((PIN_ADDRESS PLAYER4_UV2).pin, OUTPUT);
	mcpUVLEDs.pinMode((PIN_ADDRESS PLAYER4_UV1).pin, OUTPUT);
	mcpUVLEDs.pinMode((PIN_ADDRESS PLAYER1_UV2).pin, OUTPUT);

	for (int i = 0; i <= 7; i++) {
		mcpUVLEDs.pinMode(i, OUTPUT);
		mcpUVLEDs.digitalWrite(i, LOW);
	}
}

void setupCircleLEDs() {
	Log("setup Circle LEDs");
	mcpCircle1LEDs.begin(3);
	mcpCircle2LEDs.begin(4);

	mcpCircle1LEDs.pinMode((PIN_ADDRESS PLAYER1_CIRCLE1).pin, OUTPUT);
	mcpCircle1LEDs.pinMode((PIN_ADDRESS PLAYER1_CIRCLE2).pin, OUTPUT);
	mcpCircle1LEDs.pinMode((PIN_ADDRESS PLAYER1_CIRCLE3).pin, OUTPUT);
	mcpCircle1LEDs.pinMode((PIN_ADDRESS PLAYER1_CIRCLE4).pin, OUTPUT);
	mcpCircle1LEDs.pinMode((PIN_ADDRESS PLAYER1_CIRCLE5).pin, OUTPUT);
	mcpCircle1LEDs.pinMode((PIN_ADDRESS PLAYER1_CIRCLE6).pin, OUTPUT);
	mcpCircle1LEDs.pinMode((PIN_ADDRESS PLAYER1_CIRCLE7).pin, OUTPUT);
	mcpCircle1LEDs.pinMode((PIN_ADDRESS PLAYER1_CIRCLE8).pin, OUTPUT);
	mcpCircle1LEDs.pinMode((PIN_ADDRESS PLAYER2_CIRCLE1).pin, OUTPUT);
	mcpCircle1LEDs.pinMode((PIN_ADDRESS PLAYER2_CIRCLE2).pin, OUTPUT);
	mcpCircle1LEDs.pinMode((PIN_ADDRESS PLAYER2_CIRCLE3).pin, OUTPUT);
	mcpCircle1LEDs.pinMode((PIN_ADDRESS PLAYER2_CIRCLE4).pin, OUTPUT);
	mcpCircle1LEDs.pinMode((PIN_ADDRESS PLAYER2_CIRCLE5).pin, OUTPUT);
	mcpCircle1LEDs.pinMode((PIN_ADDRESS PLAYER2_CIRCLE6).pin, OUTPUT);
	mcpCircle1LEDs.pinMode((PIN_ADDRESS PLAYER2_CIRCLE7).pin, OUTPUT);
	mcpCircle1LEDs.pinMode((PIN_ADDRESS PLAYER2_CIRCLE8).pin, OUTPUT);

	mcpCircle2LEDs.pinMode((PIN_ADDRESS PLAYER3_CIRCLE1).pin, OUTPUT);
	mcpCircle2LEDs.pinMode((PIN_ADDRESS PLAYER3_CIRCLE2).pin, OUTPUT);
	mcpCircle2LEDs.pinMode((PIN_ADDRESS PLAYER3_CIRCLE3).pin, OUTPUT);
	mcpCircle2LEDs.pinMode((PIN_ADDRESS PLAYER3_CIRCLE4).pin, OUTPUT);
	mcpCircle2LEDs.pinMode((PIN_ADDRESS PLAYER3_CIRCLE5).pin, OUTPUT);
	mcpCircle2LEDs.pinMode((PIN_ADDRESS PLAYER3_CIRCLE6).pin, OUTPUT);
	mcpCircle2LEDs.pinMode((PIN_ADDRESS PLAYER3_CIRCLE7).pin, OUTPUT);
	mcpCircle2LEDs.pinMode((PIN_ADDRESS PLAYER3_CIRCLE8).pin, OUTPUT);
	mcpCircle2LEDs.pinMode((PIN_ADDRESS PLAYER4_CIRCLE1).pin, OUTPUT);
	mcpCircle2LEDs.pinMode((PIN_ADDRESS PLAYER4_CIRCLE2).pin, OUTPUT);
	mcpCircle2LEDs.pinMode((PIN_ADDRESS PLAYER4_CIRCLE3).pin, OUTPUT);
	mcpCircle2LEDs.pinMode((PIN_ADDRESS PLAYER4_CIRCLE4).pin, OUTPUT);
	mcpCircle2LEDs.pinMode((PIN_ADDRESS PLAYER4_CIRCLE5).pin, OUTPUT);
	mcpCircle2LEDs.pinMode((PIN_ADDRESS PLAYER4_CIRCLE6).pin, OUTPUT);
	mcpCircle2LEDs.pinMode((PIN_ADDRESS PLAYER4_CIRCLE7).pin, OUTPUT);
	mcpCircle2LEDs.pinMode((PIN_ADDRESS PLAYER4_CIRCLE8).pin, OUTPUT);
}

void setupMiddleColorLEDS() {
	Log("setup Middle Color LEDs");
	pinMode((PIN_ADDRESS PIN_PLAYER1_LED1).pin, OUTPUT);
	pinMode((PIN_ADDRESS PIN_PLAYER1_LED2).pin, OUTPUT);
	pinMode((PIN_ADDRESS PIN_PLAYER1_LED3).pin, OUTPUT);
	pinMode((PIN_ADDRESS PIN_PLAYER1_LED4).pin, OUTPUT);
	pinMode((PIN_ADDRESS PIN_PLAYER1_LED5).pin, OUTPUT);

	pinMode((PIN_ADDRESS PIN_PLAYER2_LED1).pin, OUTPUT);
	pinMode((PIN_ADDRESS PIN_PLAYER2_LED2).pin, OUTPUT);
	pinMode((PIN_ADDRESS PIN_PLAYER2_LED3).pin, OUTPUT);
	pinMode((PIN_ADDRESS PIN_PLAYER2_LED4).pin, OUTPUT);
	pinMode((PIN_ADDRESS PIN_PLAYER2_LED5).pin, OUTPUT);

	pinMode((PIN_ADDRESS PIN_PLAYER3_LED1).pin, OUTPUT);
	pinMode((PIN_ADDRESS PIN_PLAYER3_LED2).pin, OUTPUT);
	pinMode((PIN_ADDRESS PIN_PLAYER3_LED3).pin, OUTPUT);
	pinMode((PIN_ADDRESS PIN_PLAYER3_LED4).pin, OUTPUT);
	pinMode((PIN_ADDRESS PIN_PLAYER3_LED5).pin, OUTPUT);

	pinMode((PIN_ADDRESS PIN_PLAYER4_LED1).pin, OUTPUT);
	pinMode((PIN_ADDRESS PIN_PLAYER4_LED2).pin, OUTPUT);
	pinMode((PIN_ADDRESS PIN_PLAYER4_LED3).pin, OUTPUT);
	pinMode((PIN_ADDRESS PIN_PLAYER4_LED4).pin, OUTPUT);
	pinMode((PIN_ADDRESS PIN_PLAYER4_LED5).pin, OUTPUT);

	for (int p = 0; p < 4; p++) {
		for (int l = 0; l <= 5; l++) {
			digitalWrite(playerMiddleColors[getPinIndex(p,l, MAX_LEDS_MIDDLE)], HIGH);
		}
	}
}
