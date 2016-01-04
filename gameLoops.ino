enum GameState {
	COUNTDOWN,
	RUNNING,
	OUTRO
};



#define SPECIAL_COOLDOWN 5000
#define TURBO_DURATION 300
#define SLOW_DURATION 1000 // 500

#define PHASE1_DURATION 13000
#define PHASE2_DURATION 18000

//Game Settings
//boolean enableSpecialItems = true;
//boolean enableEvents = true;

unsigned long gameStartCountdown;
int countdownAnimation;
GameState gameState;
boolean enabledPlayer[4];
uint8_t playerCount;

//uint16_t animationDelay;
unsigned long animationTmr;
uint8_t animationStep;

unsigned long eventDelayTmr;
uint16_t eventDelay;
unsigned long eventTmr;
#define EVENT_DURATION 1500

unsigned long eventAnnounceTmr;
int eventAnnouncePhase;

unsigned long playerSpecialCooldownTmr[4];
uint8_t playerSpecialItemAmount[4];
//SpecialItemType playerSpecialItemType[4];

unsigned long turboTmr;
unsigned long slowTmr;

unsigned long recheckTmr[4];

uint8_t chipCount[4];

uint8_t currentChefIndex;
unsigned long chefChangeTmr;

uint8_t currentMotorSpeed;
boolean currentMotorDirection; //true = forward
unsigned long motorSpeedChangeTmr;
uint16_t motorSpeedChangeDelay;

unsigned long animationSwitchTmr;
unsigned long animationSwitchDelay;

unsigned long colorFlashTmr; //used for short light flashes (e.g. loose a chip, display item usage)
Color colorFlashPlayer[4];
uint8_t colorFlashDuration;
uint8_t colorFlashCount;
boolean colorFlashIsOff;

unsigned long startTime;
uint8_t gamePhase;

//uint8_t loser;
//uint8_t winner;
uint8_t score[4]; // 0 -> 1st (winner player), 1 -> 2nd, 2 -> 3rd player, 3 -> 4th player (loser)
uint8_t currentScore;

void enablePlayer(uint8_t player) {
	setColor(player, PlayerColor[player - 1]);
	for (int l = 0; l < 4; l++) {
		digitalWrite(UVLEDs[getPinIndex(player-1,l, MAX_LEDS_UV)],255);
	}
	for (int l = 0; l < 5; l++) {
		digitalWrite(playerMiddleColors[getPinIndex(player-1,l, MAX_LEDS_MIDDLE)], 255);
	}
	if (!enabledPlayer[player - 1]) {
		playerCount++;
	}
	enabledPlayer[player - 1] = true;
	chipCount[player - 1] = 3;

	if (gameSettings.enableItems) {
		updatePlayerBoosterLEDs(player, 4);
		digitalWrite(SpecialButtonLED[player-1], 255);
	}
	else {
		updatePlayerBoosterLEDs(player, 0);
		digitalWrite(SpecialButtonLED[player - 1], 0);
	}
}

void handleTurbo() {
	turboTmr = millis();
	setMotorSpeed(currentMotorDirection, MAX_MOTOR_SPEED);
}

void handleSlow() {
	slowTmr = millis();
	setMotorSpeed(true, 0);
}

void handleDirectionChange() {
	currentMotorDirection = !currentMotorDirection; 
	if (!currentMotorDirection && currentMotorSpeed > 100) {
		currentMotorSpeed = 100; //limit backward speed to 100
	}
	setMotorSpeed(currentMotorDirection, currentMotorSpeed);
}

void handleSpecialButton(uint8_t player) {
	if (playerSpecialCooldownTmr[player - 1] == 0) {
		//no Cooldown
		if (playerSpecialItemAmount[player - 1] >= 1) {
			playerSpecialItemAmount[player - 1]--;
			playerSpecialCooldownTmr[player - 1] = millis();
			updatePlayerBoosterLEDs(player, playerSpecialItemAmount[player - 1],false);
			digitalWrite(SpecialButtonLED[player - 1], 0);

			colorFlashTmr = millis();
			colorFlashDuration = 150;
			colorFlashCount = 2;
			colorFlashIsOff = false;
			setColor(player, colorFlashPlayer[player-1] = BLUE);
			for (int i = 0; i < 4; i++) {
				if (i != player - 1) {
					colorFlashPlayer[i] = BLACK;
				}
			}

			
			switch (gameSettings.itemType[player - 1]) {
			case TURBO:
				handleTurbo();
				break;
			case SLOW:
				handleSlow();
				break;
			case CHANGE_DIR:
				handleDirectionChange();
				break;
			}
		}
	}
}

uint16_t calcAnimationDelay(uint8_t motorSpeed) {
	uint16_t newDelay = map(motorSpeed, MIN_MOTOR_SPEED, MAX_MOTOR_SPEED-50, 87, 20);
	Log("new Animation Delay: "+(String) newDelay);
	return newDelay;
}

void inline setRandomPhase1Animation() {
	switch (random(6)) {
	case 0:
		setAnimation(0, 10, 46); // Circle 
		setAnimation(1, -1);
		setAnimation(2, 15, 64); // Middle Start
		setAnimation(3, -1);  // Middle with offset
		setAnimation(4, 5, 750); // UVLED OUTER BLINK
		setAnimation(5, 6, 320); // UVLED INNER BLINK
		setAnimation(6, 7, 184); //COLOR

		setAnimation(7, -1);
		setAnimation(8, -1);
		break;
	case 1:
		setAnimation(0, 9, 46); // Circle 
		setAnimation(1, -1);
		setAnimation(2, 16, 64); // Middle Start
		setAnimation(3, -1);  // Middle with offset
		setAnimation(4, 5, 750); // UVLED OUTER BLINK
		setAnimation(5, 6, 320); //UVLED INNET BLINK
		setAnimation(6, 8, 184); //COLOR

		setAnimation(7, -1);
		setAnimation(8, -1);
		break;
	case 2:
	case 3:
		setColor(1, Color BLACK);
		setColor(2, Color BLACK);
		setColor(3, Color BLACK);
		setColor(4, Color BLACK);
		digitalWrites(playerMiddleColors, 0, 19, 0);

		setAnimation(0, 21, 600);
		setAnimation(1, 22, 600, 0);

		//TODO: add middle & UV
		setAnimation(2, 28, 600);
		setAnimation(3, 29, 600, 0);
		setAnimation(4, 5, 600);
		setAnimation(5, 6, 400);
		setAnimation(6, -1);
		setAnimation(7, -1);
		setAnimation(8, -1);

		break;
	case 4:
	case 5:
		setColor(1, Color BLACK);
		setColor(2, Color BLACK);
		setColor(3, Color BLACK);
		setColor(4, Color BLACK);
		digitalWrites(playerMiddleColors, 0, 19, 0);

		setAnimation(0, 24);

		//TODO: add middle & UV
		setAnimation(1, -1);
		setAnimation(2, 30);
		setAnimation(3, -1);
		setAnimation(4, 5, 600);
		setAnimation(5, 6, 400);
		setAnimation(6, 7);
		setAnimation(7, -1);
		setAnimation(8, -1);
		break;
	}
}

void inline setRandomPhase2Animation() {
	switch (random(6)) {
	case 0:
		setAnimation(0, 10); // Circle 
		setAnimation(1, 10, -1, 15); // Circle with offset  
		setAnimation(2, 15); // Middle Start
		setAnimation(3, 15, -1, 9);  // Middle with offset
		setAnimation(4, 5, 750); // UVLED OUTER BLINK
		setAnimation(5, 6, 320); // UVLED INNER BLINK
		setAnimation(6, 7, 184); //COLOR

		setAnimation(7, -1);
		setAnimation(8, -1);
		break;
	case 1:
		setAnimation(0, 9); // Circle 
		setAnimation(1, 9, -1, 15); // Circle with offset  
		setAnimation(2, 16); // Middle Start
		setAnimation(3, 16, -1, 9);  // Middle with offset
		setAnimation(4, 5, 750); // UVLED OUTER BLINK
		setAnimation(5, 6, 320); //UVLED INNET BLINK
		setAnimation(6, 8, 184); //COLOR

		setAnimation(7, -1);
		setAnimation(8, -1);
		break;
	case 2:
	case 3:
		setColor(1, Color BLACK);
		setColor(2, Color BLACK);
		setColor(3, Color BLACK);
		setColor(4, Color BLACK);
		digitalWrites(playerMiddleColors, 0, 19, 0);

		setAnimation(0, 21, 300);
		setAnimation(1, 22, 300, 0);

		//TODO: add middle & UV
		setAnimation(2, 28, 300);
		setAnimation(3, 29, 300, 0);
		setAnimation(4, 5, 300);
		setAnimation(5, 6, 200);
		setAnimation(6, 8, 184);
		setAnimation(7, -1);
		setAnimation(8, -1);
		break;
	case 4:
	case 5:
		setColor(1, Color BLACK);
		setColor(2, Color BLACK);
		setColor(3, Color BLACK);
		setColor(4, Color BLACK);
		digitalWrites(playerMiddleColors, 0, 19, 0);

		setAnimation(0, 24, 18);

		//TODO: add middle & UV
		setAnimation(1, -1);
		setAnimation(2, 30, 25);
		setAnimation(3, -1);
		setAnimation(4, 5, 300);
		setAnimation(5, 6, 200);
		setAnimation(6, 7, 184);
		setAnimation(7, -1);
		setAnimation(8, -1);
		break;
	}
}

void inline setRandomPhase3Animation() {
	switch (random(6)) {
	case 0:
		setAnimation(0, 10); // Circle 
		setAnimation(1, 10, -1, 15); // Circle with offset  
		setAnimation(2, 15); // Middle Start
		setAnimation(3, 15, -1, 9);  // Middle with offset
		setAnimation(4, 5, 750); // UVLED OUTER BLINK
		setAnimation(5, 6, 320); // UVLED INNER BLINK
		setAnimation(6, 7, 184); //COLOR
		setAnimation(7, 10, -1, 7); // Circle with offset
		setAnimation(8, 10, -1, 23);  // Circle with offset  
		break;
	case 1:
		setAnimation(0, 9); // Circle 
		setAnimation(1, 9, -1, 15); // Circle with offset  
		setAnimation(2, 16); // Middle Start
		setAnimation(3, 16, -1, 9);  // Middle with offset
		setAnimation(4, 5, 750); // UVLED OUTER BLINK
		setAnimation(5, 6, 320); //UVLED INNET BLINK
		setAnimation(6, 8, 184); //COLOR
		setAnimation(7, 9, -1, 7); // Circle with offset
		setAnimation(8, 9, -1, 23);  // Circle with offset  
		break;
	case 2:
	case 3:
		setColor(1, Color BLACK);
		setColor(2, Color BLACK);
		setColor(3, Color BLACK);
		setColor(4, Color BLACK);
		digitalWrites(playerMiddleColors, 0,19,0);

		setAnimation(0, 21, 150);
		setAnimation(1, 22, 150, 0);

		//TODO: add middle & UV
		setAnimation(2, 28, 110);
		setAnimation(3, 29, 110, 0);
		setAnimation(4, 5, 150);
		setAnimation(5, 6, 100);
		setAnimation(6, 31);
		setAnimation(7, -1);
		setAnimation(8, -1);
		break;
	case 4:
	case 5:
		setColor(1, BLACK);
		setColor(2, BLACK);
		setColor(3, BLACK);
		setColor(4, BLACK);
		digitalWrites(playerMiddleColors, 0, 19, 0);

		setAnimation(0, 24, 12);

		//TODO: add middle & UV
		setAnimation(1, -1);
		setAnimation(2, 30, 17);
		setAnimation(3, -1);
		setAnimation(4, 5, 150);
		setAnimation(5, 6, 100);
		setAnimation(6, 31);
		setAnimation(7, -1);
		setAnimation(8, -1);
		break;
	}
}

void setRandomGameAnim() {
	Serial.println("GamePhase: "+(String)gamePhase);
	switch (gamePhase) {
	case 0:
		//chill phase
		setRandomPhase1Animation();
		break;
	case 1:
		//normal phase
		setRandomPhase2Animation();
		break;
	case 2:
		//escalation phase ----> PARTY!!!
		setRandomPhase3Animation();
		break;
	}
}

void initGame() {
	Log("Init Game");
	fullOff();
	gamePhase = 0;
	setNoAnimation();
	state = GAME;
	gameState = COUNTDOWN;
	gameStartCountdown = millis();
	countdownAnimation = -1;
	motorSpeedChangeTmr = millis();
	motorSpeedChangeDelay = 4000 + random(4000);
	currentMotorSpeed = gameSettings.startSpeed;
	currentMotorDirection = true;
	//animationDelay = calcAnimationDelay(currentMotorSpeed);
	animationStep = -1;
	animationTmr = millis();

	colorFlashTmr = 0;

	enabledPlayer[0] = false;
	enabledPlayer[1] = false;
	enabledPlayer[2] = false;
	enabledPlayer[3] = false;
	recheckTmr[0] = 0;
	recheckTmr[1] = 0;
	recheckTmr[2] = 0;
	recheckTmr[3] = 0;
	chipCount[0] = 0;
	chipCount[1] = 0;
	chipCount[2] = 0;
	chipCount[3] = 0;
	playerSpecialCooldownTmr[0] = 0;
	playerSpecialCooldownTmr[1] = 0;
	playerSpecialCooldownTmr[2] = 0;
	playerSpecialCooldownTmr[3] = 0;
	playerSpecialItemAmount[0] = 4;
	playerSpecialItemAmount[1] = 4;
	playerSpecialItemAmount[2] = 4;
	playerSpecialItemAmount[3] = 4;

	score[0] = 255;
	score[1] = 255;
	score[2] = 255;
	score[3] = 255;
	currentScore = 0;

	/*playerSpecialItemType[0] = TURBO;
	playerSpecialItemType[1] = SLOW;
	playerSpecialItemType[2] = TURBO;
	playerSpecialItemType[3] = SLOW;*/

	turboTmr = 0;
	slowTmr = 0;

	eventDelayTmr = 0;
	eventDelay = 12000 + random(5000);
	eventTmr = 0;

	eventAnnouncePhase = -1;
	eventAnnounceTmr = 0;

	//loser = 255;
	//winner = 255;

	digitalWrite(PIN_ADDRESS GLOBAL_IR, HIGH);

	delay(200);

	playerCount = 0;
	if (getPlayerChipAmount(1) == 3) {
		Log("Player 1: OK");
		enablePlayer(1);
	}
	else {
		Log("Player 1: -");
		enabledPlayer[0] = false;
	}

	if (getPlayerChipAmount(2) == 3) {
		Log("Player 2: OK");
		enablePlayer(2);
	}
	else {
		Log("Player 2: -");
		enabledPlayer[1] = false;
	}

	if (getPlayerChipAmount(3) == 3) {
		Log("Player 3: OK");
		enablePlayer(3);
	}
	else {
		Log("Player 3: -");
		enabledPlayer[2] = false;
	}

	if (getPlayerChipAmount(4) == 3) {
		Log("Player 4: OK");
		enablePlayer(4);
	}
	else {
		Log("Player 4: -");
		enabledPlayer[3] = false;
	}

	if (playerCount <= 1) {
		Log("Cannot start. Too few Players available (" +(String)playerCount+")");
		Serial1.print("b"+(String)playerCount+".");
		state = IDLE;
		setIdleAnimations();
		return;
		//gameState = COUNTDOWN;
	}
	else {
		Serial1.print("c.");
	}

	if (gameSettings.chefMode) {
		//determine 1st chef
		//TODO: vllt könnte man hier ein minigame draus machen
		do {
			currentChefIndex = random(4);
		} while (!enabledPlayer[currentChefIndex]);
		//display chef
		Log("new Chef: " + (String)(currentChefIndex + 1));
	}

	Log("Game Settings:");
	Log("Start  Speed:  " + (String)gameSettings.startSpeed);
	Log("Random Speed:  " + (String)gameSettings.randomSpeed);
	Log("Min Speed Del: " + (String)gameSettings.speedMinDelay);
	Log("Max Speed Del: " + (String)gameSettings.speedMaxDelay);
	Log("Min Speed Ste: " + (String)gameSettings.speedMinStepSize);
	Log("Max Speed Ste: " + (String)gameSettings.speedMaxStepSize);
	Log("Enable Revers: " + (String)gameSettings.enableReverse);
	Log("Chef Mode:     " + (String)gameSettings.chefMode);
	Log("Chef Roulette: " + (String)gameSettings.chefRoulette);
	Log("Chef Delay:    " + (String)gameSettings.chefChangeDelay);
	Log("Chef Cooldown: " + (String)gameSettings.chefHasShorterCooldown);
	Log("Enable Items:  " + (String)gameSettings.enableItems);
}

void gameLoop() {
	switch (gameState) {
	case COUNTDOWN:
		if ((unsigned long)(millis() - gameStartCountdown) > 500/*cntdwn animation delay*/) {
			countdownAnimation++;
			if (countdownAnimation >= 8) {
				gameState = RUNNING;
				setMotorSpeed(currentMotorDirection, currentMotorSpeed);
				// reset/start Timers
				motorSpeedChangeTmr = millis();
				eventDelayTmr = millis(); 
				chefChangeTmr = millis();
				animationSwitchTmr = millis();
				animationSwitchDelay = 5000 + random(10001);
				startTime = millis();

				setRandomGameAnim();
				
				Log("Countdown done -> start");
			}
			else {
				gameStartCountdown = millis();
				//DoAnimationStep()
			}
		}
		break;
	case RUNNING:
		//if(doAnimations)
		if (eventTmr == 0) {
			//TODO: Bedingung allgemeiner! aber zum Testen hier speziell
			handleAnimations();
		}

		if (eventAnnouncePhase == -1 && eventTmr == 0 && (unsigned long)(millis() - animationSwitchTmr) > animationSwitchDelay) {
			animationSwitchDelay = 2000 + random(3001);
			animationSwitchTmr = millis();
			setRandomGameAnim();
		}

		if ((unsigned long)(millis() - startTime) > PHASE1_DURATION) {
			if ((unsigned long)(millis() - startTime) > (PHASE1_DURATION + PHASE2_DURATION)) {
				gamePhase = 2;
			}
			else {
				gamePhase = 1;
			}
		}

		if (turboTmr != 0) {
			if ((unsigned long)(millis() - turboTmr) > TURBO_DURATION) {
				turboTmr = 0;
				setMotorSpeed(currentMotorDirection, currentMotorSpeed);
			}
		}

		if (slowTmr != 0) {
			if ((unsigned long)(millis() - slowTmr) > SLOW_DURATION) {
				slowTmr = 0;
				setMotorSpeed(currentMotorDirection, currentMotorSpeed);
			}
		}

		if (colorFlashTmr != 0) {
			if ((unsigned long)(millis() - colorFlashTmr) > colorFlashDuration) {
				if (!colorFlashIsOff) {
					colorFlashCount--;
					if (colorFlashCount == 0) {
						colorFlashTmr = 0;
					}
					else {
						colorFlashTmr = millis();
					}

					if (!equalColors(colorFlashPlayer[0],Color BLACK))
						setColor(1, BLACK);
					if (!equalColors(colorFlashPlayer[1],Color BLACK))
						setColor(2, BLACK);
					if (!equalColors(colorFlashPlayer[2],Color BLACK))
						setColor(3, BLACK);
					if (!equalColors(colorFlashPlayer[3],Color BLACK))
						setColor(4, BLACK);

					colorFlashIsOff = true;
				}else{
					colorFlashTmr = millis();

					if (!equalColors(colorFlashPlayer[0], Color BLACK))
						setColor(1, colorFlashPlayer[0]);
					if (!equalColors(colorFlashPlayer[1], Color BLACK))
						setColor(2, colorFlashPlayer[1]);
					if (!equalColors(colorFlashPlayer[2], Color BLACK))
						setColor(3, colorFlashPlayer[2]);
					if (!equalColors(colorFlashPlayer[3], Color BLACK))
						setColor(4, colorFlashPlayer[3]);

					colorFlashIsOff = false;
				}
			
			}
		}

		if (eventAnnouncePhase != -1) {
			if ((unsigned long)(millis() - eventAnnounceTmr) > 1500) {
				eventAnnouncePhase++;
				if (eventAnnouncePhase >= 3) {
					eventAnnouncePhase = -1;
					eventAnnounceTmr = 0;
					//Start event
					eventDelayTmr = millis();
					eventDelay = EVENT_DURATION + 9000 + random(11000);
					eventTmr = millis();

					//signalize that an event has started
					fullOff(false, false);
				}
				else {
					eventAnnounceTmr = millis();
					setAnimation(6,25+eventAnnouncePhase);
				}
			}
		}

		for (int i = 0; i < 4; i++) {
			if (enabledPlayer[i]) {
				//player Loop
				if (recheckTmr[i] == 0) {
					if (getPlayerChipAmount(i + 1) != chipCount[i]) {
						recheckTmr[i] = millis();
						//Log("player " + (String)(i + 1) + " recheck!");
					}
				}else{
					if ((unsigned long)(millis() - recheckTmr[i]) > 500) {
						recheckTmr[i] = 0;
						uint8_t cnt = getPlayerChipAmount(i + 1);
						if (cnt != chipCount[i]) { // chip amount is still different -> has really changed
							//update Chip Count
							if (cnt < chipCount[i] && eventAnnouncePhase == -1 && eventTmr == 0) {
								//only flash lights when no event is announcing 
								colorFlashTmr = millis();
								colorFlashDuration = 100;
								colorFlashCount = 2;
								colorFlashIsOff = false;

								if (enabledPlayer[0]) {
									setColor(1, colorFlashPlayer[0] = PlayerColor[i]);
								}
								if (enabledPlayer[1]) {
									setColor(2, colorFlashPlayer[1] = PlayerColor[i]);
								}
								if (enabledPlayer[2]) {
									setColor(3, colorFlashPlayer[2] = PlayerColor[i]);
								}
								if (enabledPlayer[3]) {
									setColor(4, colorFlashPlayer[3] = PlayerColor[i]);
								}
							}
							chipCount[i] = cnt;
							//Log("player " + (String)(i + 1) + ": "+(String) cnt+" chips left");
							if (cnt == 0) {
								enabledPlayer[i] = false;
								score[currentScore] = i;
								Log("Player OUT: "+(String)i+" platz: "+(String)currentScore);
								currentScore++;
								//if (loser == 255) {
//									loser = i;
								//}
								//TEST: disable Player LEDs
								for (int l = 0; l < 5; l++) {
									digitalWrite(playerMiddleColors[getPinIndex(i,l, MAX_LEDS_MIDDLE)],0);
								}
								setColor(i + 1, Color BLACK);
								updatePlayerBoosterLEDs(i+1,0);
								//digitalWrite(SpecialButtonLED[i],0);

								playerCount--;
								//TODO: play "player lose" effect
								//Log((String)playerCount+" players left");
								if (playerCount <= 1) {
									//Only 1 player left -> game is finished!
									for (int i = 0; i < 4;i++) {
										if (enabledPlayer[i]) {
											score[currentScore] = i;
											//winner = i + 1;
											break;
										}
									}

									//Log("Stop: playerCount <= 1");
									endGame();
									return;
								}
							}
						}
					}
				}


				//handle Special Item Cooldown
				if (playerSpecialCooldownTmr[i] != 0 && (unsigned long) (millis()-playerSpecialCooldownTmr[i]) >= ((gameSettings.chefMode&&currentChefIndex==i&&gameSettings.chefHasShorterCooldown)?(SPECIAL_COOLDOWN/3):SPECIAL_COOLDOWN) ) {
					playerSpecialCooldownTmr[i] = 0;
					if (playerSpecialItemAmount[i] > 0) {
						//nur rote LED anschalten, wenn noch Items übrig sind
						digitalWrite(SpecialButtonLED[i], 255);
					}
				}

				//handle Special Items
				if (gameSettings.enableItems && eventTmr == 0) {
					//only when no event is in progress, a player can use special items
					if (isButtonPressed(SpecialButton[i])) {
						handleSpecialButton(i + 1);
					}

					//to prevent spamming + - speed buttons: start special cooldown
					/*if (isButtonPressed(SpeedButton[i][0]) || isButtonPressed(SpeedButton[i][1])) {
						playerSpecialCooldownTmr[i] = millis();
						digitalWrite(SpecialButtonLED[i], 0);
					}*/
				}

				//handle chef mode!!
				if (gameSettings.chefMode && currentChefIndex == i) {
					if (isButtonPressed(SpeedButton[i][0])) {
						//Inc speed Button
						if ((unsigned long)(millis() - motorSpeedChangeTmr) > 50) {
							motorSpeedChangeTmr = millis();
							currentMotorSpeed += 1;
							if (currentMotorSpeed < MIN_MOTOR_SPEED) {
								currentMotorSpeed = MIN_MOTOR_SPEED;
							}
							if (currentMotorSpeed > MAX_MOTOR_SPEED - 30) {
								currentMotorSpeed = MAX_MOTOR_SPEED - 30;
							}
							setMotorSpeed(currentMotorDirection, currentMotorSpeed);
						}
					}
					else if (isButtonPressed(SpeedButton[i][1])) {
						//Dec speed Button
						if ((unsigned long)(millis() - motorSpeedChangeTmr) > 50) {
							motorSpeedChangeTmr = millis();
							currentMotorSpeed -= 1;
							if (currentMotorSpeed < MIN_MOTOR_SPEED + 20) {
								currentMotorSpeed = MIN_MOTOR_SPEED + 20;
							}
							if (currentMotorSpeed > MAX_MOTOR_SPEED - 50) {
								currentMotorSpeed = MAX_MOTOR_SPEED - 50;
							}
							setMotorSpeed(currentMotorDirection, currentMotorSpeed);
						}
					}
				}
		
			} // end if(enabledPlayer)
		} // end iterating players

		  // ********** handle events **********
		if (gameSettings.enableEvents) {
			if (eventDelayTmr != 0 && (unsigned long)(millis() - eventDelayTmr) > eventDelay) {
				//Announce Event
				eventAnnouncePhase = 0;
				eventAnnounceTmr = millis();

				setNoAnimation();
				setAnimation(6, 25);
				eventDelayTmr = 0;

				digitalWrites(UVLEDs_OUTER,0,7,255);
				
			/*	eventDelayTmr = millis();
				eventDelay = EVENT_DURATION + 4500 + random(7000);
				eventTmr = millis();

				//signalize that an event has started
				fullOff(false, false);*/
			}

			if (eventTmr != 0) {
				if ((unsigned long)(millis() - eventTmr) > EVENT_DURATION) {
					eventTmr = 0; //cancel event
					setRandomGameAnim();
					//TEST
				/*	for (int i = 0; i < 4; i++) {
						if (enabledPlayer[i]) {
							for (int l = 0; l < 5; l++) {
								digitalWrite(playerMiddleColors[getPinIndex(i,l, MAX_LEDS_MIDDLE)], 255);
								if (l < 4) {
									digitalWrite(UVLEDs[getPinIndex(i, l, MAX_LEDS_UV)], 255);
								}
							}
							setColor(i + 1, PlayerColor[i]);
						}
					}*/
				}
				else {
					for (int i = 1; i <= 4; i++) {
						if (enabledPlayer[i - 1] && checkButtons(i)) {
							//end event -> an enabled! player has pressed a button
							eventTmr = 0;
							playerSpecialItemAmount[i - 1]++;
							//play Effect
							if (playerSpecialItemAmount[i - 1] > 4) {
								playerSpecialItemAmount[i - 1] = 4;
							}
							else {
								updatePlayerBoosterLEDs(i, playerSpecialItemAmount[i - 1]);
							}

							colorFlashTmr = millis();
							colorFlashDuration = 100;
							colorFlashCount = 3;
							colorFlashIsOff = false;
							setColor(1, (colorFlashPlayer[0] = PlayerColor[i-1]));
							setColor(2, (colorFlashPlayer[1] = PlayerColor[i - 1]));
							setColor(3, (colorFlashPlayer[2] = PlayerColor[i - 1]));
							setColor(4, (colorFlashPlayer[3] = PlayerColor[i - 1]));

							setRandomGameAnim();

						/*	for (int p = 0; p < 4; p++) {
								if (enabledPlayer[p]) {
									for (int l = 0; l < 5; l++) {
										digitalWrite(playerMiddleColors[getPinIndex(p, l, MAX_LEDS_MIDDLE)], 255);
										if (l < 4) {
											digitalWrite(UVLEDs[getPinIndex(p, l, MAX_LEDS_UV)], 255);
										}
									}
									setColor(p + 1, PlayerColor[p]);
								}
							}*/

							break;
						}
					}
				}
			}
		}

		// ********** handle random Speed **********
		//chef mode disables random Speed!!
		if (gameSettings.randomSpeed && !gameSettings.chefMode) {
			if ((unsigned long)(millis() - motorSpeedChangeTmr)>motorSpeedChangeDelay) {
				motorSpeedChangeTmr = millis();
				motorSpeedChangeDelay = gameSettings.speedMinDelay + random(gameSettings.speedMaxDelay-gameSettings.speedMinDelay+1);

				if (gameSettings.enableReverse) {
					if (!currentMotorDirection) {
						currentMotorDirection = true; //change from backward to forward
					}
					else {
						if (random(4) == 0) {
							//25% chance of turing backward
							currentMotorDirection = false;
							if (currentMotorSpeed > 100) {
								currentMotorSpeed = 100; //limit initial backward speed to 100
							}
						}
					}
				}

				//50:50 chance of increase or decrease the speed
				currentMotorSpeed += (random(2) == 0) ? (gameSettings.speedMinStepSize + random(gameSettings.speedMaxStepSize - gameSettings.speedMinStepSize + 1)) : -(gameSettings.speedMinStepSize + random(gameSettings.speedMaxStepSize - gameSettings.speedMinStepSize + 1));
				if (currentMotorSpeed < MIN_MOTOR_SPEED+20+gamePhase*10) {
					currentMotorSpeed = MIN_MOTOR_SPEED+20+gamePhase*10;
				}
				if (currentMotorSpeed > MAX_MOTOR_SPEED - 50) {
					currentMotorSpeed = MAX_MOTOR_SPEED - 50;
				}

			//	setAnimationDelay(0,calcAnimationDelay(currentMotorSpeed));
				//animationDelay = calcAnimationDelay(currentMotorSpeed);
				setMotorSpeed(currentMotorDirection, currentMotorSpeed);
			}
		}//end random speed

		if (gameSettings.chefMode && gameSettings.chefRoulette) {
			if ((unsigned long)(millis() - chefChangeTmr) > gameSettings.chefChangeDelay) {
				chefChangeTmr = millis();
				uint8_t oldChefIndex = currentChefIndex;
				do {
					currentChefIndex = random(4);
				} while (!enabledPlayer[currentChefIndex] || oldChefIndex == currentChefIndex );

				//display new Chef
				Log("new Chef: "+(String)(currentChefIndex+1));
			}
		}
	
		break;
	case OUTRO:
		//play final effects
		if ((unsigned long)(millis() - gameStartCountdown) > 100) {
			countdownAnimation++;
			gameStartCountdown = millis();

			//setColor(winner, (countdownAnimation%2==0)?(Color BLACK):(PlayerColor[winner-1]));
			for (int i = 1; i <= 4; i++) {
				setColor(i, (countdownAnimation % 2 == 0) ? (Color BLACK) : (PlayerColor[score[currentScore]]));
			}

			if (countdownAnimation > 21) {
				state = IDLE;
				standbyTmr = millis(); // reset standby timer
				fullOff(); 

				for (int i = 1; i <= 4; i++) {
					setColor(i, PlayerColor[i - 1]);
				}
				setIdleAnimations();
				return;
			}
		}
		break;
	}
}

void endGame() {
	Log("End Game");
	//state = IDLE;
	gameState = OUTRO;
	fullOff();
	gameStartCountdown = millis();
	countdownAnimation = 0;
	//play end/win effect
	digitalWrite(PIN_ADDRESS GLOBAL_IR, LOW);
	setMotorSpeed(true,0);
	Serial1.print("a"+(String)score[3]+":" + (String)score[2] + ":" + (String)score[1] + ":" + (String)score[0] +".");
}
