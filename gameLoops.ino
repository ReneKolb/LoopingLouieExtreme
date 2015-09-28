void initGame() {
	state = GAME;
	digitalWrite(PIN_ADDRESS GLOBAL_IR, HIGH);

	if (analogRead((PIN_ADDRESS PIN_PLAYER1_IR1).pin-100) < 500) {
		Log("player 1 1");
	}else{
		Log("no");
	}
}

void gameLoop() {

}

void endGame() {
	digitalWrite(PIN_ADDRESS GLOBAL_IR, LOW);
}
