struct PIN_ADDRESS {
	uint8_t board; //0= Arduino, 1= MCP1,  2= MCP2 ...
	uint8_t pin;
};

const PIN_ADDRESS NONE = { 255, 255 };

// ********** Define Pins: Motor ********** 
#define MOTOR_SPEED						{ 0, 2 }
#define MOTOR_DIRECTION_A				{ 0, 22 }
#define MOTOR_DIRECTION_B				{ 0, 24 }

// ********** Define Motor Speed Range ********** 
#define NORMAL_SPEED					64
#define MIN_MOTOR_SPEED					49
#define MAX_MOTOR_SPEED					170

// ********** Define Pins: Booster Counter LEDs ********** 
#define PLAYER1_BOOSTER1				{ 1, 4 }
#define PLAYER1_BOOSTER2				{ 1, 5 }
#define PLAYER1_BOOSTER3				{ 1, 6 }
#define PLAYER1_BOOSTER4				{ 1, 7 }

#define PLAYER2_BOOSTER1				{ 1, 8 }
#define PLAYER2_BOOSTER2				{ 1, 9 }
#define PLAYER2_BOOSTER3				{ 1, 10 }
#define PLAYER2_BOOSTER4				{ 1, 11 }

#define PLAYER3_BOOSTER1				{ 1, 12 }
#define PLAYER3_BOOSTER2				{ 1, 13 }
#define PLAYER3_BOOSTER3				{ 1, 14 }
#define PLAYER3_BOOSTER4				{ 1, 15 }

#define PLAYER4_BOOSTER1				{ 1, 0 }
#define PLAYER4_BOOSTER2				{ 1, 1 }
#define PLAYER4_BOOSTER3				{ 1, 2 }
#define PLAYER4_BOOSTER4				{ 1, 3 }

//                       [Player][LED] 
const PIN_ADDRESS BOOSTER_LEDS[4][4] = {
	{ PLAYER1_BOOSTER1,  PLAYER1_BOOSTER2,  PLAYER1_BOOSTER3,  PLAYER1_BOOSTER4 },
	{ PLAYER2_BOOSTER1,  PLAYER2_BOOSTER2,  PLAYER2_BOOSTER3,  PLAYER2_BOOSTER4 },
	{ PLAYER3_BOOSTER1,  PLAYER3_BOOSTER2,  PLAYER3_BOOSTER3,  PLAYER3_BOOSTER4 },
	{ PLAYER4_BOOSTER1,  PLAYER4_BOOSTER2,  PLAYER4_BOOSTER3,  PLAYER4_BOOSTER4 }
};

// ********** Define Pins: RGB-Color-Strips ********** 
#define PLAYER4_COLOR_R					{ 0, 3 }
#define PLAYER4_COLOR_G					{ 0, 4 }
#define PLAYER4_COLOR_B					{ 0, 5 }

#define PLAYER1_COLOR_R					{ 0, 6 }
#define PLAYER1_COLOR_G					{ 0, 7 }
#define PLAYER1_COLOR_B					{ 0, 8 }

#define PLAYER2_COLOR_R					{ 0, 9 }
#define PLAYER2_COLOR_G					{ 0, 10 }
#define PLAYER2_COLOR_B					{ 0, 11 }

#define PLAYER3_COLOR_R					{ 0, 12 }
#define PLAYER3_COLOR_G					{ 0, 13 }
#define PLAYER3_COLOR_B					{ 0, 44 }//4  //??? gibts nicht alle eins verschieben? 

//                   [Player][Color]
const PIN_ADDRESS RGB_LEDS[4][3] = {
	{ PLAYER1_COLOR_R,  PLAYER1_COLOR_G,  PLAYER1_COLOR_B },
	{ PLAYER2_COLOR_R,  PLAYER2_COLOR_G,  PLAYER2_COLOR_B },
	{ PLAYER3_COLOR_R,  PLAYER3_COLOR_G,  PLAYER3_COLOR_B },
	{ PLAYER4_COLOR_R,  PLAYER4_COLOR_G,  PLAYER4_COLOR_B }
};

// ********** Define Colors ********** 
struct Color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

#define RED								{ 255, 0, 0}
#define GREEN							{ 0, 255, 0 }
#define BLUE							{ 0, 0, 255 }
#define YELLOW							{ 255, 100, 0 }
#define PURPLE							{ 80, 0, 80 } //80 0 80
#define AQUA							{ 0, 255, 255 }
#define WHITE							{ 255, 255, 255 }
#define BLACK							{ 0, 0, 0 }
const struct Color COLOR[]	=			{ RED, GREEN, BLUE, YELLOW, PURPLE, AQUA, WHITE, BLACK };

const struct Color PlayerColor[4]	=		{ RED,PURPLE, YELLOW,GREEN };

// ********** Define Pins: Special-Button ********** 
#define PLAYER1_SPECIAL_BUTTON		{0,28}//28
#define PLAYER2_SPECIAL_BUTTON		{0,30}//30
#define PLAYER3_SPECIAL_BUTTON		{0,32}//32
#define PLAYER4_SPECIAL_BUTTON		{0,26}//26
const PIN_ADDRESS SpecialButton[] = { PLAYER1_SPECIAL_BUTTON, PLAYER2_SPECIAL_BUTTON, PLAYER3_SPECIAL_BUTTON, PLAYER4_SPECIAL_BUTTON };

// ********** Define Pins: Special-Button-LEDs ********** 
#define PLAYER1_SPECIAL_BUTTON_LED		{ 0, 36 }
#define PLAYER2_SPECIAL_BUTTON_LED		{ 0, 38 }
#define PLAYER3_SPECIAL_BUTTON_LED		{ 0, 40 }
#define PLAYER4_SPECIAL_BUTTON_LED		{ 0, 34 }
const PIN_ADDRESS SpecialButtonLED[4] = { PLAYER1_SPECIAL_BUTTON_LED, PLAYER2_SPECIAL_BUTTON_LED, PLAYER3_SPECIAL_BUTTON_LED, PLAYER4_SPECIAL_BUTTON_LED };

// ********** Define Pins: IR Light-Barriers ********** 
#define GLOBAL_IR						{ 0, 42 }

#define PIN_PLAYER1_IR1					{0,103} //Werte �ber 100 sind analoge Eing�nge: 103 = analog input 3
#define PIN_PLAYER1_IR2					{0,104}
#define PIN_PLAYER1_IR3					{0,105}

#define PIN_PLAYER2_IR1					{0,106}
#define PIN_PLAYER2_IR2					{0,107}
#define PIN_PLAYER2_IR3					{0,108}

#define PIN_PLAYER3_IR1					{0,109}
#define PIN_PLAYER3_IR2					{0,110}
#define PIN_PLAYER3_IR3					{0,111}

#define PIN_PLAYER4_IR1					{0,100}
#define PIN_PLAYER4_IR2					{0,101}
#define PIN_PLAYER4_IR3					{0,102}

const PIN_ADDRESS PlayerIRPins[4][3]= { { PIN_PLAYER1_IR1 ,PIN_PLAYER1_IR2 ,PIN_PLAYER1_IR3 },
										{ PIN_PLAYER2_IR1 ,PIN_PLAYER2_IR2 ,PIN_PLAYER2_IR3 },
										{ PIN_PLAYER3_IR1 ,PIN_PLAYER3_IR2 ,PIN_PLAYER3_IR3 },
										{ PIN_PLAYER4_IR1 ,PIN_PLAYER4_IR2 ,PIN_PLAYER4_IR3 } };

#define IR_THRESHOLD 800

// ********** Define Pins: UV-LEDs ********** 
#define PLAYER1_UV1						{ 2, 13 } //Einzelne LED am H�uschen
#define PLAYER1_UV2						{ 2, 10 } //3 LEDs am Nachbar H�uschen
#define PLAYER1_UV3						{ 2, 7 }  // untere 3 LEDS im Kranz
#define PLAYER1_UV4						{ 2, 0 }  // einzelne LED im Farbkranz

#define PLAYER2_UV1						{ 2, 11 }
#define PLAYER2_UV2						{ 2, 8 }
#define PLAYER2_UV3						{ 2, 4 }
#define PLAYER2_UV4						{ 2, 1 }

#define PLAYER3_UV1						{ 2, 9 }
#define PLAYER3_UV2						{ 2, 14 }
#define PLAYER3_UV3						{ 2, 5 }
#define PLAYER3_UV4						{ 2, 2 }

#define PLAYER4_UV1						{ 2, 15 }
#define PLAYER4_UV2						{ 2, 12 }
#define PLAYER4_UV3						{ 2, 6 }
#define PLAYER4_UV4						{ 2, 3 }

const PIN_ADDRESS UVLEDs[4][4] = {
	{ PLAYER1_UV1, PLAYER1_UV2, PLAYER1_UV3, PLAYER1_UV4 },
	{ PLAYER2_UV1, PLAYER2_UV2, PLAYER2_UV3, PLAYER2_UV4 },
	{ PLAYER3_UV1, PLAYER3_UV2, PLAYER3_UV3, PLAYER3_UV4 },
	{ PLAYER4_UV1, PLAYER4_UV2, PLAYER4_UV3, PLAYER4_UV4 }
};

// ********** Define Pins: Middle LEDs ********** 
//RED
#define PIN_PLAYER1_LED1				{ 0, 52	}
#define PIN_PLAYER1_LED2				{ 0, 50	}
#define PIN_PLAYER1_LED3				{ 0, 48	}
#define PIN_PLAYER1_LED4				{ 0, 46	}
#define PIN_PLAYER1_LED5				{ 0, 23 }

//PURPLE
#define PIN_PLAYER2_LED1				{ 0, 43	}
#define PIN_PLAYER2_LED2				{ 0, 41	}
#define PIN_PLAYER2_LED3				{ 0, 39	}
#define PIN_PLAYER2_LED4				{ 0, 37	}
#define PIN_PLAYER2_LED5				{ 0, 35 }

//YELLOW
#define PIN_PLAYER3_LED1				{ 0, 45	}
#define PIN_PLAYER3_LED2				{ 0, 47	}
#define PIN_PLAYER3_LED3				{ 0, 49	}
#define PIN_PLAYER3_LED4				{ 0, 51	}
#define PIN_PLAYER3_LED5				{ 0, 53 }

//GREEN
#define PIN_PLAYER4_LED1				{ 0, 33	}
#define PIN_PLAYER4_LED2				{ 0, 31	}
#define PIN_PLAYER4_LED3				{ 0, 29	}
#define PIN_PLAYER4_LED4				{ 0, 27	}
#define PIN_PLAYER4_LED5				{ 0, 25 }

const PIN_ADDRESS playerMiddleColors[4][5] = {
	{ PIN_PLAYER1_LED1, PIN_PLAYER1_LED2, PIN_PLAYER1_LED3, PIN_PLAYER1_LED4, PIN_PLAYER1_LED5 },
	{ PIN_PLAYER2_LED1, PIN_PLAYER2_LED2, PIN_PLAYER2_LED3, PIN_PLAYER2_LED4, PIN_PLAYER2_LED5 },
	{ PIN_PLAYER3_LED1, PIN_PLAYER3_LED2, PIN_PLAYER3_LED3, PIN_PLAYER3_LED4, PIN_PLAYER3_LED5 },
	{ PIN_PLAYER4_LED1, PIN_PLAYER4_LED2, PIN_PLAYER4_LED3, PIN_PLAYER4_LED4, PIN_PLAYER4_LED5 }
};

// ********** Define Pins: Circle LEDs ********** 
//RED
#define PLAYER1_CIRCLE1					{4,8}
#define PLAYER1_CIRCLE2					{4,9}
#define PLAYER1_CIRCLE3					{4,10}
#define PLAYER1_CIRCLE4					{4,11}
#define PLAYER1_CIRCLE5					{4,12}
#define PLAYER1_CIRCLE6					{4,13}
#define PLAYER1_CIRCLE7					{4,14}
#define PLAYER1_CIRCLE8					{4,15}

//PURPLE
#define PLAYER2_CIRCLE1					{3,0}
#define PLAYER2_CIRCLE2					{3,1}
#define PLAYER2_CIRCLE3					{3,2}
#define PLAYER2_CIRCLE4					{3,3}
#define PLAYER2_CIRCLE5					{3,4}
#define PLAYER2_CIRCLE6					{3,5}
#define PLAYER2_CIRCLE7					{3,6}
#define PLAYER2_CIRCLE8					{3,7}

//YELLOW
#define PLAYER3_CIRCLE1					{3,8}
#define PLAYER3_CIRCLE2					{3,9}
#define PLAYER3_CIRCLE3					{3,10}
#define PLAYER3_CIRCLE4					{3,11}
#define PLAYER3_CIRCLE5					{3,12}
#define PLAYER3_CIRCLE6					{3,13}
#define PLAYER3_CIRCLE7					{3,14}
#define PLAYER3_CIRCLE8					{3,15}

//GREEN
#define PLAYER4_CIRCLE1					{4,0}
#define PLAYER4_CIRCLE2					{4,1}
#define PLAYER4_CIRCLE3					{4,2}
#define PLAYER4_CIRCLE4					{4,3}
#define PLAYER4_CIRCLE5					{4,4}
#define PLAYER4_CIRCLE6					{4,5}
#define PLAYER4_CIRCLE7					{4,6}
#define PLAYER4_CIRCLE8					{4,7}

const PIN_ADDRESS playerCircle[4][8] = {
	{ PLAYER1_CIRCLE1, PLAYER1_CIRCLE2, PLAYER1_CIRCLE3, PLAYER1_CIRCLE4, PLAYER1_CIRCLE5,PLAYER1_CIRCLE6,PLAYER1_CIRCLE7,PLAYER1_CIRCLE8 },
	{ PLAYER2_CIRCLE1, PLAYER2_CIRCLE2, PLAYER2_CIRCLE3, PLAYER2_CIRCLE4, PLAYER2_CIRCLE5,PLAYER2_CIRCLE6,PLAYER2_CIRCLE7,PLAYER2_CIRCLE8 },
	{ PLAYER3_CIRCLE1, PLAYER3_CIRCLE2, PLAYER3_CIRCLE3, PLAYER3_CIRCLE4, PLAYER3_CIRCLE5,PLAYER3_CIRCLE6,PLAYER3_CIRCLE7,PLAYER3_CIRCLE8 },
	{ PLAYER4_CIRCLE1, PLAYER4_CIRCLE2, PLAYER4_CIRCLE3, PLAYER4_CIRCLE4, PLAYER4_CIRCLE5,PLAYER4_CIRCLE6,PLAYER4_CIRCLE7,PLAYER4_CIRCLE8 }
};

// ********** Define Pins: Speed manipulation Buttons ********** 
#define BUTTON_INC_SPEED_PLAYER2		{0,113} 
#define BUTTON_DEC_SPEED_PLAYER2		{0,112} 
#define BUTTON_DEC_SPEED_PLAYER1		{0,14}
#define BUTTON_INC_SPEED_PLAYER1		{0,15}
#define BUTTON_INC_SPEED_PLAYER4		{0,16}
#define BUTTON_DEC_SPEED_PLAYER4		{0,17}
#define BUTTON_INC_SPEED_PLAYER3		{0,114}
#define BUTTON_DEC_SPEED_PLAYER3		{0,115}


/*
struct GameSettings{
SpeedSettings:
boolean randomSpeed
uint8_t startSpeed
int randomization //delay-variation between speedSteps & Stepsize?
boolean reverse

WinRestiction: OneLastStanding, FirstLooser, Time
long maxPlayTime //default: INF

boolean ChefMode
boolean chefRoulett //automatischer Wechsel des Chefs
uint16_t chefWechselDelay
boolean enableItems
boolean enableBoosterRegainEvents
ChefMode & boosterRegainEvent schlie�en sich gegenseitig aus? da selbe Buttons ben�tigt

int itemRegainDelay //Zeit bis Booster automatisch um 1 aufgef�llt wird: default INF?
int itemCooldownDelay
boolean itemBLAAAMode //booster erst cooldown wenn alle einen booster benutzt haben

boolean enabledPlayers[4] //Spieler die momentan mitspielen (3 Chips eingesteckt haben)

//eher player settings:
uint8_t playerItemType[4]  //enum: Turbo, Stop, InverseDir,
uint8_t playerItemAmount[4] //0..4
uint8_t currentChef; // 0=niemand, 1=Spieler1 ...

uint8_t currentSpeed //0..255
boolean currentDirection // true=foreward; false=backward

};
*/

