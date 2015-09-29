void initGame() {
	state = GAME;
	digitalWrite(PIN_ADDRESS GLOBAL_IR, HIGH);

	Log("0: " + (String)(analogRead(0)) + "\t3: " + (String)(analogRead(3)) + "\t6: " + (String)(analogRead(6)) + "\t9: " + (String)(analogRead(9)));
	Log("1: " + (String)(analogRead(1)) + "\t4: " + (String)(analogRead(4)) + "\t7: " + (String)(analogRead(7)) + "\t10: " + (String)(analogRead(10)));
	Log("2: " + (String)(analogRead(2)) + "\t5: " + (String)(analogRead(5)) + "\t8: " + (String)(analogRead(8)) + "\t11: " + (String)(analogRead(11)));
/*	Log("Dec 3: " + (String)isButtonPressed(BUTTON_DEC_SPEED_PLAYER3) + "Inc 3: " + (String)isButtonPressed(BUTTON_INC_SPEED_PLAYER3));
	Log("Dec 2: " + (String)isButtonPressed(BUTTON_DEC_SPEED_PLAYER2) + "Inc 2: " + (String)isButtonPressed(BUTTON_INC_SPEED_PLAYER2));
*/

	if (getPlayerChipAmount(1) == 3) {
		Log("Player 1: OK");
	}
	else {
		Log("Player 1: -");
	}

	if (getPlayerChipAmount(2) == 3) {
		Log("Player 2: OK");
	}
	else {
		Log("Player 2: -");
	}

	if (getPlayerChipAmount(3) == 3) {
		Log("Player 3: OK");
	}
	else {
		Log("Player 3: -");
	}

	if (getPlayerChipAmount(4) == 3) {
		Log("Player 4: OK");
	}
	else {
		Log("Player 4: -");
	}
}

void gameLoop() {

}

void endGame() {
	digitalWrite(PIN_ADDRESS GLOBAL_IR, LOW);
}
