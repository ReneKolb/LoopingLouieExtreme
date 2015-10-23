AnimationTmr animationTimers[10] = { { 0,-1 },{ 0,-1 } ,{ 0,-1 } ,{ 0,-1 } ,{ 0,-1 } ,{ 0,-1 } ,{ 0,-1 } ,{ 0,-1 } ,{ 0,-1 } ,{ 0,-1 } }; //max 10 animations at a time
CurrentAnimationSettings currentAnimations[10]; //indices of the Animation corresponding to AnimationDB.

void setIdleAnimations() {

	for (int i = 0; i < 10; i++) {
		animationTimers[i] = { 0,-1 };
	}
	currentAnimations[0] = { 0,-1 };
	currentAnimations[1] = { 1,-1 };
	currentAnimations[2] = { 2,-1 };
	currentAnimations[3] = { 3,-1 };
	currentAnimations[4] = { 4,-1 };
	currentAnimations[5] = { 5,-1 };
	currentAnimations[6] = { 6,-1 };
	currentAnimations[7] = { -1,-1 };
	currentAnimations[8] = { -1,-1 };
	currentAnimations[9] = { -1,-1 };
}

void setNoAnimation() {
	for (int i = 0; i < 10; i++) {
		animationTimers[i] = { 0,-1 };
		currentAnimations[i] = { -1,-1 };
	}
}

void setNoAnimation(int animationSlot) {
	animationTimers[animationSlot] = {0,-1};
	currentAnimations[animationSlot] = { -1,-1 };
}

void setAnimation(int animationSlot, int animationDBIndex, int overrideDelay = -1) {
	animationTimers[animationSlot] = { 0,-1 };
	currentAnimations[animationSlot] = { animationDBIndex, overrideDelay };
}

void setAnimationDelay(int animationSlot, int overrideDelay) {
	currentAnimations[animationSlot].delay = overrideDelay;
}


void handleAnimationStep(NewAnimation &anim, AnimationTmr &animTmr) {
	int oldIndex;
	int newIndex;

	switch (anim.animType) {
	case BLINK:
		oldIndex = -1;
		newIndex = -1;
		if (++animTmr.currentIndex >= 1) {
			animTmr.currentIndex = -1;
			for (int j = anim.startIndex; j <= anim.endIndex; j++) {
				digitalWrite(anim.pPinList[j], 255);
			}
		}
		else {
			for (int j = anim.startIndex; j <= anim.endIndex; j++) {
				digitalWrite(anim.pPinList[j], 0);
			}
		}
		break;
	case FORWARD:
		oldIndex = animTmr.currentIndex++;
		if (animTmr.currentIndex > (anim.endIndex - anim.startIndex)) {
			animTmr.currentIndex = 0; // depending on animType
		}
		newIndex = animTmr.currentIndex;
		break;
	case BACKWARD:
		oldIndex = animTmr.currentIndex--;
		if (animTmr.currentIndex < 0) {
			animTmr.currentIndex = anim.endIndex - anim.startIndex; // depending on animType
		}
		newIndex = animTmr.currentIndex;
		break;
	case FORBACKWARD:
		animTmr.currentIndex++;
		if (animTmr.currentIndex >(anim.endIndex - anim.startIndex)) {
			oldIndex = 2 * (anim.endIndex - anim.startIndex) - animTmr.currentIndex + 1;
			newIndex = 2 * (anim.endIndex - anim.startIndex) - animTmr.currentIndex;
			if (animTmr.currentIndex > 2 * (anim.endIndex - anim.startIndex)) {
				animTmr.currentIndex = -1; // depending on animType
			}
		}
		else {
			oldIndex = animTmr.currentIndex - 1;
			newIndex = animTmr.currentIndex;
		}
		break;
	case FILLFORWARD:
		oldIndex = -1;
		animTmr.currentIndex++;
		if (animTmr.currentIndex >(anim.endIndex - anim.startIndex)) {
			animTmr.currentIndex = 0; // depending on animType
			for (int j = anim.startIndex; j <= anim.endIndex; j++) {
				digitalWrite(anim.pPinList[j], 0);
			}
		}
		newIndex = animTmr.currentIndex;
		break;
	case FILLBACKWARD:
		oldIndex = -1;
		animTmr.currentIndex--;
		if (animTmr.currentIndex < 0) {
			animTmr.currentIndex = anim.endIndex - anim.startIndex; // depending on animType
			for (int j = anim.startIndex; j <= anim.endIndex; j++) {
				digitalWrite(anim.pPinList[j], 0);
			}
		}
		newIndex = animTmr.currentIndex;
		break;
	case FILLFORBACKWARD:
		//oldIndex =
		animTmr.currentIndex++;
		//newIndex = animationTimers[i].currentIndex;

		if (animTmr.currentIndex >(anim.endIndex - anim.startIndex)) {
			oldIndex = 2 * (anim.endIndex - anim.startIndex) - animTmr.currentIndex + 1;
			newIndex = -1;
			if (animTmr.currentIndex > 2 * (anim.endIndex - anim.startIndex)) {
				animTmr.currentIndex = -1; // depending on animType
			}
		}
		else {
			oldIndex = -1;
			newIndex = animTmr.currentIndex;
		}
		break;
	default:
		Log("Unimplemented Animation Type");
	}

	//do step:
	if (oldIndex > -1) {
		digitalWrite(anim.pPinList[anim.startIndex + oldIndex], 0);
	}
	if (newIndex > -1) {
		digitalWrite(anim.pPinList[anim.startIndex + newIndex], 255);
	}
}

int getAnimationDelay(int animationSlot) {
	if (currentAnimations[animationSlot].animationDBIndex == -1) {
		//DEAD CODE??
		return -1;
	}

	if (currentAnimations[animationSlot].delay != -1) {
		return currentAnimations[animationSlot].delay;
	}

	return AnimationDB[currentAnimations[animationSlot].animationDBIndex].defaultDelay;
}

void handleAnimations() {
	for (int i = 0; i < 10; i++) {
		if (currentAnimations[i].animationDBIndex != -1) {
			if ((unsigned long)(millis() - animationTimers[i].tmr)>getAnimationDelay(i)) {
				animationTimers[i].tmr = millis();
				handleAnimationStep(AnimationDB[currentAnimations[i].animationDBIndex], animationTimers[i]);
			}
		}
	}
}