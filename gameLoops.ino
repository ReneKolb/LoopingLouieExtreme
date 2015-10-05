enum GameState {
	COUNTDOWN,
	RUNNING,
	OUTRO
};



#define SPECIAL_COOLDOWN 5000
#define TURBO_DURATION 300
#define SLOW_DURATION 1000 // 500

//Game Settings
//boolean enableSpecialItems = true;
//boolean enableEvents = true;

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
			updatePlayerBoosterLEDs(player, playerSpecialItemAmount[player - 1]);
			digitalWrite(SpecialButtonLED[player - 1], 0);
			
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
	currentMotorSpeed = gameSettings.startSpeed;
	currentMotorDirection = true;
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

	/*playerSpecialItemType[0] = TURBO;
	playerSpecialItemType[1] = SLOW;
	playerSpecialItemType[2] = TURBO;
	playerSpecialItemType[3] = SLOW;*/

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

	if (gameSettings.chefMode) {
		//determine 1st chef
		//TODO: vllt k�nnte man hier ein minigame draus machen
		do {
			currentChefIndex = random(4);
		} while (!enabledPlayer[currentChefIndex]);
		//display chef
		Log("new Chef: " + (String)(currentChefIndex + 1));
	}
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
				setMotorSpeed(currentMotorDirection, currentMotorSpeed);
			}
		}

		if (slowTmr != 0) {
			if ((unsigned long)(millis() - slowTmr) > SLOW_DURATION) {
				slowTmr = 0;
				setMotorSpeed(currentMotorDirection, currentMotorSpeed);
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

				if (playerSpecialCooldownTmr[i] != 0 && (unsigned long) (millis()-playerSpecialCooldownTmr[i]) >= ((gameSettings.chefMode&&currentChefIndex==i&&gameSettings.chefHasShorterCooldown)?(SPECIAL_COOLDOWN/3):SPECIAL_COOLDOWN) ) {
					playerSpecialCooldownTmr[i] = 0;
					if (playerSpecialItemAmount[i] > 0) {
						//nur rote LED anschalten, wenn noch Items �brig sind
						digitalWrite(SpecialButtonLED[i], 255);
					}
				}

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
					for (int i = 0; i < 4; i++) {
						if (enabledPlayer[i]) {
							for (int l = 0; l < 5; l++) {
								digitalWrite(playerMiddleColors[i][l], 255);
							}
							setColor(i + 1, PlayerColor[i]);
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
				if (currentMotorSpeed < MIN_MOTOR_SPEED+20) {
					currentMotorSpeed = MIN_MOTOR_SPEED+20;
				}
				if (currentMotorSpeed > MAX_MOTOR_SPEED - 50) {
					currentMotorSpeed = MAX_MOTOR_SPEED - 50;
				}

				animationDelay = calcAnimationDelay(currentMotorSpeed);
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
