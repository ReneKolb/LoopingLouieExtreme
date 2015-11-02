int actionByte;
char buffer[6];
size_t readSize;

// ******************************************
// * A command must be terminated by an '.' *
// ******************************************

void inline cmd_randomSpeed() {
	if (readSize == 1) {
		gameSettings.randomSpeed = atoi(buffer)!=0;
		Log("New Random Speed: "+(String)gameSettings.randomSpeed);
	}else{
		Log("Error: Wrong data size");
	}
}

void inline cmd_startSpeed() {
	int n = atoi(buffer);
	if (n < MIN_MOTOR_SPEED) {
		Log("start Speed is smaller than "+(String)MIN_MOTOR_SPEED+". It is fitted!");
		n = MIN_MOTOR_SPEED;
	} else if (n>MAX_MOTOR_SPEED) {
		Log("start Speed is larger than "+(String)MAX_MOTOR_SPEED+". It is fitted!");
		n = MAX_MOTOR_SPEED;
	}
	gameSettings.startSpeed = n;
	Log("new Start Speed: " + (String)gameSettings.startSpeed);
}

void inline cmd_speedMinDelay() {
	int n = atoi(buffer);
	if (n < 0) {
		Log("Speed Min Delay is smaller than 0. It is fitted!");
		n = 0;
	}
	else if (n>60000) {
		Log("Speed Min Delay is larger than 60000. It is fitted!");
		n = 60000;
	}
	gameSettings.speedMinDelay = n;
	Log("new Speed Min Delay: " + (String)gameSettings.speedMinDelay);
}

void inline cmd_speedMaxDelay() {
	int n = atoi(buffer);
	if (n < 0) {
		Log("Speed Max Delay is smaller than 0. It is fitted!");
		n = 0;
	}
	else if (n>60000) {
		Log("Speed Max Delay is larger than 60000. It is fitted!");
		n = 60000;
	}
	if (n < gameSettings.speedMinDelay) {
		Log("Speed Max Delay is smaller than Speed Min Delay("+(String)gameSettings.speedMinDelay+"). It is fitted!");
		n = gameSettings.speedMinDelay;
	}
	gameSettings.speedMaxDelay = n;
	Log("new Speed Max Delay: " + (String)gameSettings.speedMaxDelay);
}

void inline cmd_speedMinStepSize() {
	int n = atoi(buffer);
	if (n < 0) {
		Log("Speed Min Step Size is smaller than 0. It is fitted!");
		n = 0;
	}
	else if (n>170) {
		Log("Speed Min Step Size is larger than 170. It is fitted!");
		n = 170;
	}
	gameSettings.speedMinStepSize = n;
	Log("new Speed Min Step Size: " + (String)gameSettings.speedMinStepSize);
}

void inline cmd_speedMaxStepSize() {
	int n = atoi(buffer);
	if (n < 0) {
		Log("Speed Max Step Size is smaller than 0. It is fitted!");
		n = 0;
	}
	else if (n>170) {
		Log("Speed Max Step Size is larger than 170. It is fitted!");
		n = 170;
	}
	if (n < gameSettings.speedMinStepSize) {
		Log("Speed Max Step Size is smaller than Speed Min Step Size(" + (String)gameSettings.speedMinStepSize + "). It is fitted!");
		n = gameSettings.speedMinStepSize;
	}
	gameSettings.speedMaxStepSize = n;
	Log("new Speed Max Step Size: " + (String)gameSettings.speedMaxStepSize);
}

void inline cmd_enableReverse() {
	if (readSize == 1) {
		gameSettings.enableReverse = atoi(buffer) != 0;
		Log("New Enable Reverse: " + (String)gameSettings.enableReverse);
	}
	else {
		Log("Error: Wrong data size");
	}
}

void inline cmd_chefMode() {
	if (readSize == 1) {
		gameSettings.chefMode = atoi(buffer) != 0;
		Log("New Chef Mode: " + (String)gameSettings.chefMode);
	}
	else {
		Log("Error: Wrong data size");
	}
}

void inline cmd_chefRoulette() {
	if (readSize == 1) {
		gameSettings.chefRoulette = atoi(buffer) != 0;
		Log("New Chef Roulette: " + (String)gameSettings.chefRoulette);
	}
	else {
		Log("Error: Wrong data size");
	}
}

void inline cmd_chefChangeDelay() {
	int n = atoi(buffer);
	if (n < 0) {
		Log("Chef Change Delay is smaller than 0. It is fitted!");
		n = 0;
	}
	else if (n>60000) {
		Log("Chef Change Delay is larger than 60000. It is fitted!");
		n = 60000;
	}
	
	gameSettings.chefChangeDelay = n;
	Log("new Chef Change Delay: " + (String)gameSettings.chefChangeDelay);
}

void inline cmd_chefShorterCD() {
	if (readSize == 1) {
		gameSettings.chefHasShorterCooldown = atoi(buffer) != 0;
		Log("New Chef Shorter CD: " + (String)gameSettings.chefHasShorterCooldown);
	}
	else {
		Log("Error: Wrong data size");
	}
}

void inline cmd_enableItems() {
	if (readSize == 1) {
		gameSettings.enableItems = atoi(buffer) != 0;
		Log("New Enable Items: " + (String)gameSettings.enableItems);
	}
	else {
		Log("Error: Wrong data size");
	}
}

SpecialItemType itemTypeFromChar(const char c) {
	if (c == '0') {
		return TURBO;
	}else if (c == '1'){
		return SLOW;
	}
	else {
		return CHANGE_DIR;
	}
}

void inline cmd_itemTypes() {
	if (readSize == 4) {
		gameSettings.itemType[0] = itemTypeFromChar(buffer[0]);
		gameSettings.itemType[1] = itemTypeFromChar(buffer[1]);
		gameSettings.itemType[2] = itemTypeFromChar(buffer[2]);
		gameSettings.itemType[3] = itemTypeFromChar(buffer[3]);
		Log("Item Types updated");
	} else {
		Log("Error: Wrong data size");
	}
}

void inline cmd_enableEvents() {
	if (readSize == 1) {
		gameSettings.enableEvents = atoi(buffer) != 0;
		Log("New Enable Events: " + (String)gameSettings.enableEvents);
	}
	else {
		Log("Error: Wrong data size");
	}
}

void inline cmd_itemAutoRefillDelay() {
	int n = atoi(buffer);
	if (n < 0) {
		Log("Item Auto Refill Delay is smaller than 0. It is fitted!");
		n = 0;
	}
	else if (n>60000) {
		Log("Item Auto Refill Delay is larger than 60000. It is fitted!");
		n = 60000;
	}

	gameSettings.itemAutoRefillDelay = n;
	Log("new Item Auto Refill Delay: " + (String)gameSettings.itemAutoRefillDelay);
}

void inline cmd_itemCDDelay() {
	int n = atoi(buffer);
	if (n < 0) {
		Log("Item CD Delay is smaller than 0. It is fitted!");
		n = 0;
	}
	else if (n>60000) {
		Log("Item CD Delay is larger than 60000. It is fitted!");
		n = 60000;
	}

	gameSettings.itemCooldownDelay = n;
	Log("new Item CD Delay: " + (String)gameSettings.itemCooldownDelay);
}

void inline cmd_alternateCD() {
	if (readSize == 1) {
		gameSettings.alternateCooldownMode = atoi(buffer) != 0;
		Log("New Alternate CD: " + (String)gameSettings.alternateCooldownMode);
	}
	else {
		Log("Error: Wrong data size");
	}

}

void fillBuffer(boolean usb) {
	if (usb) {
		readSize = Serial.readBytesUntil('.', buffer, 6);
	}
	else {
		readSize = Serial1.readBytesUntil('.', buffer, 6);
	}
}

//DEBUG
int pIndex = 0;
int lIndex = -1;

boolean usbAvailable;
boolean btAvailable;

void handleSerialInput() {
	usbAvailable = Serial.available();
	btAvailable = Serial1.available();
	if (usbAvailable||btAvailable) {
		//first char is action type
		if (usbAvailable) {
			actionByte = Serial.read();
		}
		else {
			actionByte = Serial1.read();
		}

		switch (actionByte) {
		case 'a':
			fillBuffer(usbAvailable);
			cmd_randomSpeed();
			break;
		case 'b':
			fillBuffer(usbAvailable);
			cmd_startSpeed();
			break;
		case 'c':
			fillBuffer(usbAvailable);
			cmd_speedMinDelay();
			break;
		case 'd':
			fillBuffer(usbAvailable);
			cmd_speedMaxDelay();
			break;
		case 'e':
			fillBuffer(usbAvailable);
			cmd_speedMinStepSize();
			break;
		case 'f':
			fillBuffer(usbAvailable);
			cmd_speedMaxStepSize();
			break;
		case 'g':
			fillBuffer(usbAvailable);
			cmd_enableReverse();
			break;
		case 'h':
			fillBuffer(usbAvailable);
			cmd_chefMode();
			break;
		case 'i':
			fillBuffer(usbAvailable);
			cmd_chefRoulette();
			break;
		case 'j':
			fillBuffer(usbAvailable);
			cmd_chefChangeDelay();
			break;
		case 'k':
			fillBuffer(usbAvailable);
			cmd_chefShorterCD();
			break;
		case 'l':
			fillBuffer(usbAvailable);
			cmd_enableItems();
			break;
		case 'm':
			fillBuffer(usbAvailable);
			cmd_itemTypes();
			break;
		case 'n':
			fillBuffer(usbAvailable);
			cmd_enableEvents();
			break;
		case 'o':
			fillBuffer(usbAvailable);
			cmd_itemAutoRefillDelay();
			break;
		case 'p':
			fillBuffer(usbAvailable);
			cmd_itemCDDelay();
			break;
		case 'q':
			fillBuffer(usbAvailable);
			cmd_alternateCD();
			break;
		/*case 'r':
			break;*/
		case 's':
			//start the game
			initGame();
			break;
		case '.':
			//'.' is the command end symbol. So a actionByte with '.' is no command. --> Ignore
			break;
		default:
			Log("Unkown Action Byte: "+(String)actionByte);
		}
	}
}


void handleBTSerialInput() {
	//if (Serial1.available()) {
//		Log("read: "+ Serial1.readString());
//	}
}