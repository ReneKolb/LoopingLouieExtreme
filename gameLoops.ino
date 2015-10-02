enum GameState {
	COUNTDOWN,
	RUNNING,
	OUTRO
};

enum SpecialItemType {
	TURBO,
	SLOW
};

#define SPECIAL_COOLDOWN 5000
#define TURBO_DURATION 300
#define SLOW_DURATION 1000 // 500

//Game Settings
boolean enableSpecialItems = true;
boolean enableEvents = true;

unsigned long gameStartCountdown;
int countdownAnimation;
GameState gameState;
boolean enabledPlayer[4];
uint8_t playerCount;

uint16_t animationDelay;
unsigned long animationTmr;
uint8_t animationStep;

unsigned long eventDelayTmr;
uint16_t eventDelay;
unsigned long eventTmr;
#define EVENT_DURATION 1500

unsigned long playerSpecialCooldownTmr[4];
uint8_t playerSpecialItemAmount[4];
SpecialItemType playerSpecialItemType[4];

unsigned long turboTmr;
unsigned long slowTmr;

unsigned long recheckTmr[4];

uint8_t chipCount[4];

uint8_t currentMotorSpeed;
unsigned long motorSpeedChangeTmr;
uint16_t motorSpeedChangeDelay;

uint8_t winner;

void enablePlayer(uint8_t player) {
	setColor(player, PlayerColor[player - 1]);
	for (int l = 0; l < 4; l++) {
		digitalWrite(UVLEDs[player-1][l],255);
	}
	for (int l = 0; l < 5; l++) {
		digitalWrite(playerMiddleColors[player-1][l], 255);
	}
	if (!enabledPlayer[player - 1]) {
		playerCount++;
	}
	enabledPlayer[player - 1] = true;
	chipCount[player - 1] = 3;

	if (enableSpecialItems) {
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
	setMotorSpeed(true, MAX_MOTOR_SPEED);
}

void handleSlow() {
	slowTmr = millis();
	setMotorSpeed(true, 0);
}

void handleSpecialButton(uint8_t player) {
	if (playerSpecialCooldownTmr[player - 1] == 0) {
		//no Cooldown
		if (playerSpecialItemAmount[player - 1] >= 1) {
			playerSpecialItemAmount[player - 1]--;
			playerSpecialCooldownTmr[player - 1] = millis();
			updatePlayerBoosterLEDs(player, playerSpecialItemAmount[player - 1]);
			digitalWrite(SpecialButtonLED[player - 1], 0);
			
			switch (playerSpecialItemType[player - 1]) {
			case TURBO:
				handleTurbo();
				break;
			case SLOW:
				handleSlow();
				break;
			}
		}
	}
}

uint16_t calcAnimationDelay(uint8_t motorSpeed) {
	uint16_t newDelay = map(motorSpeed, MIN_MOTOR_SPEED, MAX_MOTOR_SPEED-50, 87, 20);
	Log("new Delay: "+(String) newDelay);
	return newDelay;
}

void initGame() {
	Log("Init Game");
	fullOff();
	state = GAME;
	gameState = COUNTDOWN;
	gameStartCountdown = millis();
	countdownAnimation = -1;
	motorSpeedChangeTmr = millis();
	motorSpeedChangeDelay = 4000 + random(4000);
	currentMotorSpeed = NORMAL_MOTOR_SPEED;
	animationDelay = calcAnimationDelay(currentMotorSpeed);
	animationStep = -1;
	animationTmr = millis();

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

	playerSpecialItemType[0] = TURBO;
	playerSpecialItemType[1] = SLOW;
	playerSpecialItemType[2] = TURBO;
	playerSpecialItemType[3] = SLOW;

	turboTmr = 0;
	slowTmr = 0;

	eventDelayTmr = 0;
	eventDelay = 5000 + random(5000);
	eventTmr = 0;

	winner = 255;

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
		state = IDLE;
		return;
		//gameState = COUNTDOWN;
	}
}

void gameLoop() {
	switch (gameState) {
	case COUNTDOWN:
		if ((unsigned long)(millis() - gameStartCountdown) > 500/*cntdwn animation delay*/) {
			countdownAnimation++;
			if (countdownAnimation >= 8) {
				gameState = RUNNING;
				setMotorSpeed(true, currentMotorSpeed);
				// reset/start Timers
				motorSpeedChangeTmr = millis();
				eventDelayTmr = millis(); 
				Log("Countdown done -> start");
			}
			else {
				gameStartCountdown = millis();
				//DoAnimationStep()
			}
		}
		break;
	case RUNNING:

		if (turboTmr != 0) {
			if ((unsigned long)(millis() - turboTmr) > TURBO_DURATION) {
				turboTmr = 0;
				setMotorSpeed(true, currentMotorSpeed);
			}
		}

		if (slowTmr != 0) {
			if ((unsigned long)(millis() - slowTmr) > SLOW_DURATION) {
				slowTmr = 0;
				setMotorSpeed(true, currentMotorSpeed);
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
							chipCount[i] = cnt;
							//Log("player " + (String)(i + 1) + ": "+(String) cnt+" chips left");
							if (cnt == 0) {
								enabledPlayer[i] = false;
								//TEST: disable Player LEDs
								for (int l = 0; l < 5; l++) {
									digitalWrite(playerMiddleColors[i][l],0);
								}
								setColor(i + 1, Color BLACK);
								playerCount--;
								//TODO: play "player lose" effect
								//Log((String)playerCount+" players left");
								if (playerCount <= 1) {
									//Only 1 player left -> game is finished!
									for (int i = 0; i < 4;i++) {
										if (enabledPlayer[i]) {
											winner = i + 1;
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

				if (playerSpecialCooldownTmr[i] != 0 && (unsigned long) (millis()-playerSpecialCooldownTmr[i]) >= SPECIAL_COOLDOWN ) {
					playerSpecialCooldownTmr[i] = 0;
					if (playerSpecialItemAmount[i] > 0) {
						//nur rote LED anschalten, wenn noch Items �brig sind
						digitalWrite(SpecialButtonLED[i], 255);
					}
				}

				if (enableSpecialItems && eventTmr == 0) {
					//only when no event is in progress, a player can use special items
					if (isButtonPressed(SpecialButton[i])) {
						handleSpecialButton(i + 1);
					}
				}

				//to prevent spamming + - speed buttons: start special cooldown
				if (eventTmr==0 && (isButtonPressed(SpeedButton[i][0])||isButtonPressed(SpeedButton[i][1]))) {
					playerSpecialCooldownTmr[i] = millis();
					digitalWrite(SpecialButtonLED[i], 0);
				}
			
			} // end if(enabledPlayer)
		} // end iterating players

		if ((unsigned long)(millis() - eventDelayTmr) > eventDelay) {
			//executeEvent
			eventDelayTmr = millis();
			eventDelay = EVENT_DURATION + 4500 + random(7000);
			eventTmr = millis();

			//signalize that an event has started
			fullOff(false, false);
		}

		if (eventTmr != 0) {
			if ((unsigned long)(millis() - eventTmr) > EVENT_DURATION) {
				eventTmr = 0; //cancel event
				//TEST
				for (int i = 0; i < 4;i++) {
					if (enabledPlayer[i]) {
						for (int l = 0; l < 5;l++) {
							digitalWrite(playerMiddleColors[i][l],255);
						}
						setColor(i+1,PlayerColor[i]);
					}
				}
			}
			else {
				for (int i = 1; i <= 4; i++) {
					if (checkButtons(i)) {
						//end event -> a player has pressed a button
						eventTmr = 0;
						playerSpecialItemAmount[i - 1]++;
						//play Effect
						if (playerSpecialItemAmount[i - 1] > 4) {
							playerSpecialItemAmount[i - 1] = 4;
						}
						else {
							updatePlayerBoosterLEDs(i, playerSpecialItemAmount[i - 1]);
						}

						for (int i = 0; i < 4; i++) {
							if (enabledPlayer[i]) {
								for (int l = 0; l < 5; l++) {
									digitalWrite(playerMiddleColors[i][l], 255);
								}
								setColor(i + 1, PlayerColor[i]);
							}
						}
						break;
					}
				}
			}
		}

		if ((unsigned long)(millis() - motorSpeedChangeTmr)>motorSpeedChangeDelay) {
			motorSpeedChangeTmr = millis();
			motorSpeedChangeDelay = 4000 + random(4000);
			currentMotorSpeed += random(60) - 30; //Speed change (+- 30)
			if (currentMotorSpeed < MIN_MOTOR_SPEED) {
				currentMotorSpeed = MIN_MOTOR_SPEED;
			}
			if (currentMotorSpeed > MAX_MOTOR_SPEED - 50) {
				currentMotorSpeed = MAX_MOTOR_SPEED - 50;
			}

			animationDelay = calcAnimationDelay(currentMotorSpeed);
			setMotorSpeed(true, currentMotorSpeed);
		}

		if (eventTmr == 0) {
			//only handle game animation when no event is in progress
			if ((unsigned long)(millis() - animationTmr) > animationDelay) {
				animationTmr = millis();
				animationStep++;
				if (animationStep >= circleSquenceGame.maxStep) {
					animationStep = 0;
				}
				DoAnimationStep(circleSquenceGame.LEDs[animationStep], circleSquenceGame.maxLED);
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
				setColor(i, (countdownAnimation % 2 == 0) ? (Color BLACK) : (PlayerColor[winner - 1]));
			}

			if (countdownAnimation > 21) {
				state = IDLE;
				standbyTmr = millis(); // reset standby timer
				fullOff(); 
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
}
