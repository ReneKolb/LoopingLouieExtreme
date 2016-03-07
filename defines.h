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
#define NORMAL_MOTOR_SPEED				64
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

//converts old 2d array indices to 1d index
/*int getPinIndex(uint8_t playerIndex, uint8_t pinIndex, uint8_t maxLeds) {
	//playerIndex: 0..3
	return (playerIndex * maxLeds) + pinIndex;
}*/
#define getPinIndex(playerIndex, pinIndex, maxLeds) (((playerIndex) * maxLeds) + (pinIndex))

//                       [Player][LED] 
/*const PIN_ADDRESS BOOSTER_LEDS[4][4] = {
	{ PLAYER1_BOOSTER1,  PLAYER1_BOOSTER2,  PLAYER1_BOOSTER3,  PLAYER1_BOOSTER4 },
	{ PLAYER2_BOOSTER1,  PLAYER2_BOOSTER2,  PLAYER2_BOOSTER3,  PLAYER2_BOOSTER4 },
	{ PLAYER3_BOOSTER1,  PLAYER3_BOOSTER2,  PLAYER3_BOOSTER3,  PLAYER3_BOOSTER4 },
	{ PLAYER4_BOOSTER1,  PLAYER4_BOOSTER2,  PLAYER4_BOOSTER3,  PLAYER4_BOOSTER4 }
};*/
#define MAX_LEDS_BOOSTER 4
static const PIN_ADDRESS BOOSTER_LEDS[16] = {
	 PLAYER1_BOOSTER1,  PLAYER1_BOOSTER2,  PLAYER1_BOOSTER3,  PLAYER1_BOOSTER4,
	 PLAYER2_BOOSTER1,  PLAYER2_BOOSTER2,  PLAYER2_BOOSTER3,  PLAYER2_BOOSTER4,
	 PLAYER3_BOOSTER1,  PLAYER3_BOOSTER2,  PLAYER3_BOOSTER3,  PLAYER3_BOOSTER4,
	 PLAYER4_BOOSTER1,  PLAYER4_BOOSTER2,  PLAYER4_BOOSTER3,  PLAYER4_BOOSTER4 
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
#define MAX_LEDS_RGB 3
static const PIN_ADDRESS RGB_LEDS[12] = {
	 PLAYER1_COLOR_R,  PLAYER1_COLOR_G,  PLAYER1_COLOR_B,
	 PLAYER2_COLOR_R,  PLAYER2_COLOR_G,  PLAYER2_COLOR_B,
	 PLAYER3_COLOR_R,  PLAYER3_COLOR_G,  PLAYER3_COLOR_B,
	 PLAYER4_COLOR_R,  PLAYER4_COLOR_G,  PLAYER4_COLOR_B
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

static const struct Color PlayerColor[4]	=		{ RED,PURPLE, YELLOW,GREEN };

// ********** Define Pins: Special-Button ********** 
#define PLAYER1_SPECIAL_BUTTON		{0,28}//28
#define PLAYER2_SPECIAL_BUTTON		{0,30}//30
#define PLAYER3_SPECIAL_BUTTON		{0,32}//32
#define PLAYER4_SPECIAL_BUTTON		{0,26}//26
const PIN_ADDRESS SpecialButton[4] = { PLAYER1_SPECIAL_BUTTON, PLAYER2_SPECIAL_BUTTON, PLAYER3_SPECIAL_BUTTON, PLAYER4_SPECIAL_BUTTON };

// ********** Define Pins: Special-Button-LEDs ********** 
#define PLAYER1_SPECIAL_BUTTON_LED		{ 0, 36 }
#define PLAYER2_SPECIAL_BUTTON_LED		{ 0, 38 }
#define PLAYER3_SPECIAL_BUTTON_LED		{ 0, 40 }
#define PLAYER4_SPECIAL_BUTTON_LED		{ 0, 34 }
const PIN_ADDRESS SpecialButtonLED[4] = { PLAYER1_SPECIAL_BUTTON_LED, PLAYER2_SPECIAL_BUTTON_LED, PLAYER3_SPECIAL_BUTTON_LED, PLAYER4_SPECIAL_BUTTON_LED };

// ********** Define Pins: IR Light-Barriers ********** 
#define GLOBAL_IR						{ 0, 42 }

#define PIN_PLAYER1_IR1					{0,103} //Werte über 100 sind analoge Eingänge: 103 = analog input 3
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

const PIN_ADDRESS PlayerIRPins[4][3] =	{ { PIN_PLAYER1_IR1 ,PIN_PLAYER1_IR2 ,PIN_PLAYER1_IR3 },
										  { PIN_PLAYER2_IR1 ,PIN_PLAYER2_IR2 ,PIN_PLAYER2_IR3 },
										  { PIN_PLAYER3_IR1 ,PIN_PLAYER3_IR2 ,PIN_PLAYER3_IR3 },
										  { PIN_PLAYER4_IR1 ,PIN_PLAYER4_IR2 ,PIN_PLAYER4_IR3 } };

#define IR_THRESHOLD 800

// ********** Define Pins: UV-LEDs ********** 
#define PLAYER1_UV1						{ 2, 13 } //Einzelne LED am Häuschen
#define PLAYER1_UV2						{ 2, 10 } //3 LEDs am Nachbar Häuschen
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

#define MAX_LEDS_UV 4
static const PIN_ADDRESS UVLEDs[16] = {
	 PLAYER1_UV1, PLAYER1_UV2, PLAYER1_UV3, PLAYER1_UV4,
	 PLAYER2_UV1, PLAYER2_UV2, PLAYER2_UV3, PLAYER2_UV4,
	 PLAYER3_UV1, PLAYER3_UV2, PLAYER3_UV3, PLAYER3_UV4,
	 PLAYER4_UV1, PLAYER4_UV2, PLAYER4_UV3, PLAYER4_UV4
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

#define MAX_LEDS_MIDDLE 5
static const PIN_ADDRESS playerMiddleColors[20] = {
	 PIN_PLAYER1_LED1, PIN_PLAYER1_LED2, PIN_PLAYER1_LED3, PIN_PLAYER1_LED4, PIN_PLAYER1_LED5,
	 PIN_PLAYER2_LED1, PIN_PLAYER2_LED2, PIN_PLAYER2_LED3, PIN_PLAYER2_LED4, PIN_PLAYER2_LED5,
	 PIN_PLAYER3_LED1, PIN_PLAYER3_LED2, PIN_PLAYER3_LED3, PIN_PLAYER3_LED4, PIN_PLAYER3_LED5,
	 PIN_PLAYER4_LED1, PIN_PLAYER4_LED2, PIN_PLAYER4_LED3, PIN_PLAYER4_LED4, PIN_PLAYER4_LED5
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

#define MAX_LEDS_CIRCLE 8
static const PIN_ADDRESS playerCircle[32] = {
	 PLAYER1_CIRCLE1, PLAYER1_CIRCLE2, PLAYER1_CIRCLE3, PLAYER1_CIRCLE4, PLAYER1_CIRCLE5, PLAYER1_CIRCLE6, PLAYER1_CIRCLE7, PLAYER1_CIRCLE8,
	 PLAYER2_CIRCLE1, PLAYER2_CIRCLE2, PLAYER2_CIRCLE3, PLAYER2_CIRCLE4, PLAYER2_CIRCLE5, PLAYER2_CIRCLE6, PLAYER2_CIRCLE7, PLAYER2_CIRCLE8,
	 PLAYER3_CIRCLE1, PLAYER3_CIRCLE2, PLAYER3_CIRCLE3, PLAYER3_CIRCLE4, PLAYER3_CIRCLE5, PLAYER3_CIRCLE6, PLAYER3_CIRCLE7, PLAYER3_CIRCLE8,
	 PLAYER4_CIRCLE1, PLAYER4_CIRCLE2, PLAYER4_CIRCLE3, PLAYER4_CIRCLE4, PLAYER4_CIRCLE5, PLAYER4_CIRCLE6, PLAYER4_CIRCLE7, PLAYER4_CIRCLE8
};
/*
static const PIN_ADDRESS playerCircleEven[16] = {
	PLAYER1_CIRCLE2, PLAYER1_CIRCLE4, PLAYER1_CIRCLE6, PLAYER1_CIRCLE8,
	PLAYER2_CIRCLE2, PLAYER2_CIRCLE4, PLAYER2_CIRCLE6, PLAYER2_CIRCLE8,
	PLAYER3_CIRCLE2, PLAYER3_CIRCLE4, PLAYER3_CIRCLE6, PLAYER3_CIRCLE8,
	PLAYER4_CIRCLE2, PLAYER4_CIRCLE4, PLAYER4_CIRCLE6, PLAYER4_CIRCLE8
};

static const PIN_ADDRESS playerCircleOdd[16] = {
	PLAYER1_CIRCLE1, PLAYER1_CIRCLE3, PLAYER1_CIRCLE5, PLAYER1_CIRCLE7,
	PLAYER2_CIRCLE1, PLAYER2_CIRCLE3, PLAYER2_CIRCLE5, PLAYER2_CIRCLE7,
	PLAYER3_CIRCLE1, PLAYER3_CIRCLE3, PLAYER3_CIRCLE5, PLAYER3_CIRCLE7,
	PLAYER4_CIRCLE1, PLAYER4_CIRCLE3, PLAYER4_CIRCLE5, PLAYER4_CIRCLE7
};
*/
// ********** Define Pins: Speed manipulation Buttons ********** 
#define BUTTON_INC_SPEED_PLAYER2		{0,113} 
#define BUTTON_DEC_SPEED_PLAYER2		{0,112} 
#define BUTTON_DEC_SPEED_PLAYER1		{0,14}
#define BUTTON_INC_SPEED_PLAYER1		{0,15}
#define BUTTON_INC_SPEED_PLAYER4		{0,16}
#define BUTTON_DEC_SPEED_PLAYER4		{0,17}
#define BUTTON_INC_SPEED_PLAYER3		{0,114}
#define BUTTON_DEC_SPEED_PLAYER3		{0,115}

const PIN_ADDRESS SpeedButton[4][2] = {
	{ BUTTON_INC_SPEED_PLAYER1 ,BUTTON_DEC_SPEED_PLAYER1 },
	{ BUTTON_INC_SPEED_PLAYER2 ,BUTTON_DEC_SPEED_PLAYER2 },
	{ BUTTON_INC_SPEED_PLAYER3 ,BUTTON_DEC_SPEED_PLAYER3 },
	{ BUTTON_INC_SPEED_PLAYER4 ,BUTTON_DEC_SPEED_PLAYER4 }
};


enum SpecialItemType {
	TURBO,
	SLOW,
	CHANGE_DIR,
	BLACKOUT
};

struct GameSettings{
	//Speed Settings
	bool randomSpeed;
	uint8_t startSpeed;
	int speedMinDelay; //0 means: delay between speed steps is always the same
	int speedMaxDelay;
	int speedMinStepSize;
	int speedMaxStepSize; 
	bool enableReverse;

	//Chef Mode
	bool chefMode;
	bool chefRoulette;     //könnte man zusammenfassen
	uint16_t chefChangeDelay; // indem man chefDelay auf 0 setzt und != 0
	bool chefHasShorterCooldown;

	bool enableItems;
	SpecialItemType itemType[4];
	bool enableEvents;

	uint16_t itemAutoRefillDelay; // 0: no refill
	uint16_t itemCooldownDelay; //individuell für jeden ItemTyp ?
	bool alternateCooldownMode; //true: erst wenn alle spieler ein item eingesetzt haben, können die anderen wieder ein item einsetzen

	bool enabledPlayers[4];
};




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
ChefMode & boosterRegainEvent schließen sich gegenseitig aus? da selbe Buttons benötigt

int itemRegainDelay //Zeit bis Booster automatisch um 1 aufgefüllt wird: default INF?
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

static const PIN_ADDRESS UVLEDs_OUTER[8] = {
	PLAYER1_UV1, PLAYER1_UV2,
	PLAYER2_UV1, PLAYER2_UV2,
	PLAYER3_UV1, PLAYER3_UV2,
	PLAYER4_UV1, PLAYER4_UV2
};

static const PIN_ADDRESS UVLEDs_INNER[8] = {
	PLAYER1_UV3, PLAYER1_UV4,
	PLAYER2_UV3, PLAYER2_UV4,
	PLAYER3_UV3, PLAYER3_UV4,
	PLAYER4_UV3, PLAYER4_UV4
};

static const Color COLOR_LIST[4] = {
	RED, PURPLE, YELLOW, GREEN
};

static const Color COLOR_LIST_EVENT_1[4] = {
	BLACK,BLUE,BLUE,BLUE
};

static const Color COLOR_LIST_EVENT_2[4] = {
	BLACK,BLUE,BLACK,BLUE
};

static const Color COLOR_LIST_EVENT_3[4] = {
	BLACK,BLACK,BLUE,BLACK
};

static const Color COLOR_BLINK_LIST[] = {
	RED, BLACK, GREEN, BLACK, BLUE, BLACK, YELLOW, BLACK, PURPLE, BLACK, AQUA, BLACK
};

enum AnimationType
{
	DEFAULT_ANIM,

	BLINK, FORWARD, BACKWARD, FORBACKWARD, FILLFORWARD, FILLBACKWARD, FILLFORBACKWARD,
	RANDOM_FILLS,
	
	COLOR_FORWARD, COLOR_BACKWARD, COLOR_ROTATE, COLOR_ROTATE_BACKWARDS, COLOR_BLINK, COLOR_BLINK_ALL
};


//tests for new animations
struct NewAnimation
{
	const PIN_ADDRESS *pPinList;
	const Color *pColorList;
	int startIndex;
	int endIndex;
	AnimationType animType;
	int defaultDelay;
	int extra;

	NewAnimation(const PIN_ADDRESS *pPinLst, int startIdx, int endIdx, AnimationType animTyp,int defaultDel, int animExtra = 1) : pPinList(pPinLst),startIndex(startIdx),endIndex(endIdx),animType(animTyp),defaultDelay(defaultDel),extra(animExtra){}
	NewAnimation(const Color *pColorLst, int startIdx, int endIdx, AnimationType animTyp, int defaultDel, int animExtra = 1) : pColorList(pColorLst), startIndex(startIdx), endIndex(endIdx), animType(animTyp), defaultDelay(defaultDel), extra(animExtra){}
};

struct AnimationTmr {
	unsigned long tmr;
	int currentIndex;
};

NewAnimation AnimationDB[] = {
	//Booster Display Animation
/*0*/ 	{ BOOSTER_LEDS,			0,  3,  FILLFORWARD,		100 }, 
/*1*/ 	{ BOOSTER_LEDS,			4,  7,  FILLBACKWARD,		100 },
/*2*/ 	{ BOOSTER_LEDS,			8,  11, FILLFORBACKWARD,	100 },
/*3*/ 	{ BOOSTER_LEDS,			12, 15, FORBACKWARD,		100 },
/*4*/ 	{ UVLEDs,				0,  15, BLINK,				1500},
/*5*/ 	{ UVLEDs_OUTER,			0,  7,  BLINK,				1500},
/*6*/ 	{ UVLEDs_INNER,			0,  7,  BLINK,				640},
/*7*/ 	{ COLOR_LIST,			0,  3,  COLOR_FORWARD,		160},
/*8*/	{ COLOR_LIST,			0,  3,  COLOR_BACKWARD,		160 },

/*9*/	{ playerCircle,			0,  31, FORWARD,			23 },
/*10*/	{ playerCircle,			0,  31, BACKWARD,			23 },
/*11*/	{ playerCircle,			0,  31, FILLFORWARD,		23 },
/*12*/	{ playerCircle,			0,  31, FILLBACKWARD,		23 },
/*13*/	{ playerCircle,			0,  31, FILLFORBACKWARD,	23 },
/*14*/	{ playerCircle,			0,	31, FORBACKWARD,		23 },

/*15*/	{ playerMiddleColors,	0,  19, FORWARD,			32 },
/*16*/	{ playerMiddleColors,	0,  19, BACKWARD,			32 },
/*17*/	{ playerMiddleColors,	0,  19, FILLFORWARD,		32 },
/*18*/	{ playerMiddleColors,	0,  19, FILLBACKWARD,       32 },
/*19*/	{ playerMiddleColors,	0,  19, FILLFORBACKWARD,    32 },
/*20*/	{ playerMiddleColors,	0,	19, FORBACKWARD,		32 },

/*21*/	{ playerCircle,			0,  31, BLINK,				800,	2},
/*22*/	{ playerCircle,			1,  31, BLINK,				800,	2},

/*23*/	{ playerCircle,			0,	31, FORWARD,			23,		4},

/*24*/	{ playerCircle,			0,	31,	RANDOM_FILLS,		23},

/*25*/	{ COLOR_LIST_EVENT_1,	0,	3,	COLOR_ROTATE,		250},
/*26*/	{ COLOR_LIST_EVENT_2,	0,	3,	COLOR_ROTATE_BACKWARDS,		170},
/*27*/	{ COLOR_LIST_EVENT_3,	0,	3,	COLOR_ROTATE,		100},

/*28*/	{ playerMiddleColors,	0,	19,	BLINK,		800, 2 },
/*29*/	{ playerMiddleColors,	1,	19,	BLINK,		800, 2 },

/*30*/	{ playerMiddleColors,	0,	19,	RANDOM_FILLS,		32},
/*31*/	{ COLOR_LIST,			0,	3,	COLOR_BLINK,		50},
/*32*/	{ COLOR,				0,	5,	COLOR_BLINK_ALL,	100},
/*33*/	{COLOR_BLINK_LIST,		0,	11,	COLOR_BLINK_ALL,	100},
};

struct CurrentAnimationSettings {
	int animationDBIndex;
	int delay;
	AnimationType animType;
};

// TODO: COLOR!!!
/*
AnimationTmr animationTimers[10] = { {0,-1},{ 0,-1 } ,{ 0,-1 } ,{ 0,-1 } ,{ 0,-1 } ,{ 0,-1 } ,{ 0,-1 } ,{ 0,-1 } ,{ 0,-1 } ,{ 0,-1 } }; //max 10 animations at a time
int currentAnimations[10] = {0, 1, 2, 3, 4 , 5 , 6 ,-1 ,-1 ,-1 }; //indices of the Animation corresponding to AnimationDB.
*/


