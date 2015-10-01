enum GameState {
	COUNTDOWN,
	RUNNING,
	OUTRO
};

#define SPECIAL_COOLDOWN 5000
#define TURBO_DURATION 300

unsigned long gameStartCountdown;
int countdownAnimation;
GameState gameState;
boolean enabledPlayer[4];
uint8_t playerCount;

unsigned long playerSpecialCooldownTmr[4];
uint8_t playerSpecialItemAmount[4];

unsigned long turboTmr;

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

	updatePlayerBoosterLEDs(player, 3);
}

void handleTurbo() {
	turboTmr = millis();
	setMotorSpeed(true, MAX_MOTOR_SPEED);
}

void handleSpecialButton(uint8_t player) {
	if (playerSpecialCooldownTmr[player - 1] == 0) {
		//no Cooldown
		if (playerSpecialItemAmount[player - 1] >= 1) {
			playerSpecialItemAmount[player - 1]--;
			playerSpecialCooldownTmr[player - 1] = millis();
			updatePlayerBoosterLEDs(player, playerSpecialItemAmount[player - 1]);
			digitalWrite(SpecialButtonLED[player - 1], 0);

			handleTurbo();
		}
	}
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
	currentMotorSpeed = 63;

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

	turboTmr = 0;

	winner = 255;

	digitalWrite(PIN_ADDRESS GLOBAL_IR, HIGH);

	delay(200);

	Log("0: " + (String)(analogRead(0)) + "\t3: " + (String)(analogRead(3)) + "\t6: " + (String)(analogRead(6)) + "\t9: " + (String)(analogRead(9)));
	Log("1: " + (String)(analogRead(1)) + "\t4: " + (String)(analogRead(4)) + "\t7: " + (String)(analogRead(7)) + "\t10: " + (String)(analogRead(10)));
	Log("2: " + (String)(analogRead(2)) + "\t5: " + (String)(analogRead(5)) + "\t8: " + (String)(analogRead(8)) + "\t11: " + (String)(analogRead(11)));

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

	for (int i = 0; i < 4; i++) {
		if (enabledPlayer[i]) {
			updatePlayerBoosterLEDs(i + 1, 4);
			digitalWrite(SpecialButtonLED[i], 255);
		}
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
						if (cnt != chipCount[i]) { // still 0: player really has 0 chips 
							//update Chip Count
							chipCount[i] = cnt;
							//updatePlayerBoosterLEDs(i+1, cnt);
							//Log("player " + (String)(i + 1) + ": "+(String) cnt+" chips left");
							if (cnt == 0) {
								enabledPlayer[i] = false;
								playerCount--;
								//play "player lose" effect
								//Log((String)playerCount+" players left");
								if (playerCount <= 1) {
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
					digitalWrite(SpecialButtonLED[i], 255);
				}

				if (isButtonPressed(SpecialButton[i])) {
					handleSpecialButton(i+1);
				}
			} // end if(enabledPlayer)
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

			setMotorSpeed(true, currentMotorSpeed);
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
