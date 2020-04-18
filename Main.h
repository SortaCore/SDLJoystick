// Object identifier "SDLJ"
#define IDENTIFIER	0x53444C4A
#include "SDL.h"

// ------------------------------
// DEFINITION OF CONDITIONS CODES
// ------------------------------
#define	CND_ISCONNECTED				0
#define	CND_BUTTONPRESSED			1
#define	CND_BUTTONHELDDOWN			2
#define	CND_BUTTONRELEASED			3
#define	CND_ANYBUTTONPRESSED		4
#define	CND_ANYBUTTONHELDDOWN		5
#define	CND_ANYBUTTONRELEASED		6
#define	CND_LAST					7

// ---------------------------
// DEFINITION OF ACTIONS CODES
// ---------------------------
#define	ACT_LAST                    0

// -------------------------------
// DEFINITION OF EXPRESSIONS CODES
// -------------------------------
#define	EXP_NUMJOYS                 0
#define	EXP_GETAXIS                 1
#define	EXP_GETBUTTON               2
#define	EXP_GETHAT                  3
#define	EXP_GETBALLX                4
#define	EXP_GETBALLY                5
#define	EXP_NUMAXES                 6
#define	EXP_NUMBUTTONS              7
#define	EXP_NUMHATS                 8
#define	EXP_NUMBALLS                9
#define EXP_DEVICENAME 				10
#define EXP_DEVICEGUID 				11
#define	EXP_GETBUTTONSHELD	        12
#define	EXP_HELDBUTTON	            13
#define	EXP_LASTPRESSED	            14
#define	EXP_LASTRELEASED	        15
#define	EXP_LAST                    16

// --------------------------------
// EDITION OF OBJECT DATA STRUCTURE
// --------------------------------
typedef struct tagEDATA_V0
{
	extHeader		eHeader;
	short			sx;
	short			sy;
	short			swidth;
	short			sheight;

} EDITDATA;
typedef EDITDATA _far *			LPEDATA;

// Object versions
#define	KCX_CURRENT_VERSION			0

// --------------------------------
// RUNNING OBJECT DATA STRUCTURE
// --------------------------------

struct SDL_JoystickData
{
	SDL_Joystick* joystick;
	SDL_Haptic* haptic;
	bool connected;
	int joy_id;
	Sint16 axis[8];
	Uint8 held_buttons[32];
	Uint8 held_buttons_last[32];
	Uint8 hat[4];
	int ball_x[4];
	int ball_y[4];
	Sint8 currentheld[32];
	Sint8 lastpressed;
	Sint8 lastreleased;
	char num_buttons;
	char num_axes;
	char num_hats;
	char num_balls;
};

typedef struct tagRDATA
{
	headerObject	rHo;					// Header
	HINSTANCE SDL;
	SDL_JoystickData SDL_Data[16];
} RUNDATA;
typedef	RUNDATA	_far *			LPRDATA;

// Size when editing the object under level editor
// -----------------------------------------------
#define	MAX_EDITSIZE			sizeof(EDITDATA)


// Default flags
// -------------
#define	OEFLAGS      			(OEFLAG_NEVERSLEEP | OEFLAG_DISPLAYINFRONT | OEFLAG_WINDOWPROC)
#define	OEPREFS      			0

// If to handle message, specify the priority of the handling procedure
// 0= low, 255= very high. You should use 100 as normal.                                                
// --------------------------------------------------------------------
#define	WINDOWPROC_PRIORITY		100
