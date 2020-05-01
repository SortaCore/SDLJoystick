// ============================================================================
//
// This file are where the Conditions/Actions/Expressions are defined.
//
// ============================================================================

// Common Include
#include "common.h"
#include "SDL.h"


//Variables

bool initialize = false;

// Quick memo: content of the eventInformations arrays
// ---------------------------------------------------
// Menu ID
// String ID
// Code
// Flags
// Number_of_parameters
// Parameter_type [Number_of_parameters]
// Parameter_TitleString [Number_of_parameters]

// Definitions of parameters for each condition
short conditionsInfos[]=
		{
		IDMN_ISCONNECTED, M_ISCONNECTED, CND_ISCONNECTED, EVFLAGS_ALWAYS + EVFLAGS_NOTABLE, 1, PARAM_EXPRESSION, M_CND_JOY,
		IDMN_BUTTONPRESSED, M_BUTTONPRESSED, CND_BUTTONPRESSED, EVFLAGS_ALWAYS + EVFLAGS_NOTABLE, 2, PARAM_EXPRESSION, PARAM_EXPRESSION, M_CND_JOY, M_CND_BUTTON,
		IDMN_BUTTONHELDDOWN, M_BUTTONHELDDOWN, CND_BUTTONHELDDOWN, EVFLAGS_ALWAYS + EVFLAGS_NOTABLE, 2, PARAM_EXPRESSION, PARAM_EXPRESSION, M_CND_JOY, M_CND_BUTTON,
		IDMN_BUTTONRELEASED, M_BUTTONRELEASED, CND_BUTTONRELEASED, EVFLAGS_ALWAYS + EVFLAGS_NOTABLE, 2, PARAM_EXPRESSION, PARAM_EXPRESSION, M_CND_JOY, M_CND_BUTTON,
		IDMN_ANYBUTTONPRESSED, M_ANYBUTTONPRESSED, CND_ANYBUTTONPRESSED, EVFLAGS_ALWAYS + EVFLAGS_NOTABLE, 1, PARAM_EXPRESSION, M_CND_JOY,
		IDMN_ANYBUTTONHELDDOWN, M_ANYBUTTONHELDDOWN, CND_ANYBUTTONHELDDOWN, EVFLAGS_ALWAYS + EVFLAGS_NOTABLE, 1, PARAM_EXPRESSION, M_CND_JOY,
		IDMN_ANYBUTTONRELEASED, M_ANYBUTTONRELEASED, CND_ANYBUTTONRELEASED, EVFLAGS_ALWAYS + EVFLAGS_NOTABLE, 1, PARAM_EXPRESSION, M_CND_JOY,
		};

// Definitions of parameters for each action
short actionsInfos[] =
		{ 0 };

// Definitions of parameters for each expression
short expressionsInfos[]=
		{
		IDMN_NUMJOYS, M_NUMJOYS, EXP_NUMJOYS, 0, 0,
		IDMN_GETAXIS, M_GETAXIS, EXP_GETAXIS, 0, 2, EXPPARAM_LONG, EXPPARAM_LONG, 0, 0,
		IDMN_GETBUTTON, M_GETBUTTON, EXP_GETBUTTON, 0, 2, EXPPARAM_LONG, EXPPARAM_LONG, 0, 0,
		IDMN_GETHAT, M_GETHAT, EXP_GETHAT, 0, 2, EXPPARAM_LONG, EXPPARAM_LONG, 0, 0,
		IDMN_GETBALLX, M_GETBALLX, EXP_GETBALLX, 0, 2, EXPPARAM_LONG, EXPPARAM_LONG, 0, 0,
		IDMN_GETBALLY, M_GETBALLY, EXP_GETBALLY, 0, 2, EXPPARAM_LONG, EXPPARAM_LONG, 0, 0,
		IDMN_NUMAXES, M_NUMAXES, EXP_NUMAXES, 0, 1, EXPPARAM_LONG, 0,
		IDMN_NUMBUTTONS, M_NUMBUTTONS, EXP_NUMBUTTONS, 0, 1, EXPPARAM_LONG, 0,
		IDMN_NUMHATS, M_NUMHATS, EXP_NUMHATS, 0, 1, EXPPARAM_LONG, 0,
		IDMN_NUMBALLS, M_NUMBALLS, EXP_NUMBALLS, 0, 1, EXPPARAM_LONG, 0,
		IDMN_DEVICENAME, M_DEVICENAME, EXP_DEVICENAME, EXPFLAG_STRING, 1, EXPPARAM_LONG, 0,
		IDMN_DEVICEGUID, M_DEVICEGUID, EXP_DEVICEGUID, EXPFLAG_STRING, 1, EXPPARAM_LONG, 0,
		IDMN_GETBUTTONSHELD, M_GETBUTTONSHELD, EXP_GETBUTTONSHELD, EXPFLAG_STRING, 1, EXPPARAM_LONG, 0,
		IDMN_HELDBUTTON, M_HELDBUTTON, EXP_HELDBUTTON, 0, 2, EXPPARAM_LONG, EXPPARAM_LONG, 0, 0,
		IDMN_LASTPRESSED, M_LASTPRESSED, EXP_LASTPRESSED, 0, 1, EXPPARAM_LONG, 0,
		IDMN_LASTRELEASED, M_LASTRELEASED, EXP_LASTRELEASED, 0, 1, EXPPARAM_LONG, 0,
		};

// ============================================================================
//
// CONDITION ROUTINES
// 
// ============================================================================

long WINAPI DLLExport IsConnected(LPRDATA rdPtr, long param1, long param2)
{
	return rdPtr->SDL_Data[param1].connected;
}

long WINAPI DLLExport ButtonPressed(LPRDATA rdPtr, long param1, long param2)
{
	if (rdPtr->SDL_Data[param1].held_buttons[param2] && !rdPtr->SDL_Data[param1].held_buttons_last[param2]) return 1;
	else return 0;
}

long WINAPI DLLExport ButtonHeldDown(LPRDATA rdPtr, long param1, long param2)
{
	if (rdPtr->SDL_Data[param1].held_buttons[param2]) return 1;
	else return 0;
}

long WINAPI DLLExport ButtonReleased(LPRDATA rdPtr, long param1, long param2)
{
	if (!rdPtr->SDL_Data[param1].held_buttons[param2] && rdPtr->SDL_Data[param1].held_buttons_last[param2]) return 1;
	else return 0;
}

long WINAPI DLLExport AnyButtonPressed(LPRDATA rdPtr, long param1, long param2)
{
	for (int i = 0; i < 32; i++)
	{
		if (rdPtr->SDL_Data[param1].held_buttons[i] && !rdPtr->SDL_Data[param1].held_buttons_last[i]) return 1;
	}
	return 0;
}

long WINAPI DLLExport AnyButtonHeldDown(LPRDATA rdPtr, long param1, long param2)
{
	for (int i = 0; i < 32; i++)
	{
		if (rdPtr->SDL_Data[param1].held_buttons[i]) return 1;
	}
	return 0;
}

long WINAPI DLLExport AnyButtonReleased(LPRDATA rdPtr, long param1, long param2)
{
	for (int i = 0; i < 32; i++)
	{
		if (!rdPtr->SDL_Data[param1].held_buttons[i] && rdPtr->SDL_Data[param1].held_buttons_last[i]) return 1;
	}
	return 0;
}
// ============================================================================
//
// ACTIONS ROUTINES
// 
// ============================================================================

// ============================================================================
//
// EXPRESSIONS ROUTINES
// 
// ============================================================================

long WINAPI DLLExport GetAxis(LPRDATA rdPtr, long param1)
{
	long joy = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);
	long axis = CNC_GetNextExpressionParameter(rdPtr, param1, TYPE_INT);
	return (long)(rdPtr->SDL_Data[joy].axis[axis]);
}

long WINAPI DLLExport GetButton(LPRDATA rdPtr, long param1)
{
	long joy = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);
	long button = CNC_GetNextExpressionParameter(rdPtr, param1, TYPE_INT);
	return (long)(rdPtr->SDL_Data[joy].held_buttons[button]);
}

long WINAPI DLLExport GetHat(LPRDATA rdPtr, long param1)
{
	long joy = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);
	long hat = CNC_GetNextExpressionParameter(rdPtr, param1, TYPE_INT);
	return (long)(rdPtr->SDL_Data[joy].hat[hat]);
}

long WINAPI DLLExport GetBallX(LPRDATA rdPtr, long param1)
{
	long joy = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);
	long ball = CNC_GetNextExpressionParameter(rdPtr, param1, TYPE_INT);
	return (long)(rdPtr->SDL_Data[joy].ball_x[ball]);
}

long WINAPI DLLExport GetBallY(LPRDATA rdPtr, long param1)
{
	long joy = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);
	long ball = CNC_GetNextExpressionParameter(rdPtr, param1, TYPE_INT);
	return (long)(rdPtr->SDL_Data[joy].ball_y[ball]);
}

long WINAPI DLLExport NumAxes(LPRDATA rdPtr,long param1)
{
	long joy = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);
	return (long)(rdPtr->SDL_Data[joy].num_axes);
}

long WINAPI DLLExport NumButtons(LPRDATA rdPtr,long param1)
{
	long joy = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);
	return (long)(rdPtr->SDL_Data[joy].num_buttons);
}

long WINAPI DLLExport NumHats(LPRDATA rdPtr, long param1)
{
	long joy = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);
	return (long)(rdPtr->SDL_Data[joy].num_hats);
}

long WINAPI DLLExport NumBalls(LPRDATA rdPtr, long param1)
{
	long joy = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);
	return (long)(rdPtr->SDL_Data[joy].num_balls);
}

long WINAPI DLLExport NumJoysticks(LPRDATA rdPtr,long param1)
{
	short numjoys = 0;
 
	for (int joy = 0; joy < 16; joy++)
	{
		if (rdPtr->SDL_Data[joy].connected) numjoys++;
	}
	
	return numjoys;
}

long WINAPI DLLExport GetDeviceGUID(LPRDATA rdPtr, long param1)
{
	SDL_JoystickGUID guid;
	LPTSTR pszName = ("");
	long joy = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_LONG);
	if (rdPtr->SDL != nullptr && rdPtr->SDL_Data[joy].connected)
	{
		pszName = (LPTSTR)callRunTimeFunction(rdPtr, RFUNCTION_GETSTRINGSPACE_EX, 0, 33 * sizeof(TCHAR));
		if (pszName != NULL)
		{
			guid = SDL_JoystickGetGUID(rdPtr->SDL_Data[joy].joystick);
			SDL_JoystickGetGUIDString(guid, pszName, 33);
		}
	}
	rdPtr->rHo.hoFlags |= HOF_STRING;
	return (long)pszName;
}

long WINAPI DLLExport GetDeviceName(LPRDATA rdPtr, long param1)
{
	LPTSTR pszName = ("");
	long joy = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_LONG);
	if (rdPtr->SDL != nullptr && rdPtr->SDL_Data[joy].connected)
	{
		pszName = (LPTSTR)callRunTimeFunction(rdPtr, RFUNCTION_GETSTRINGSPACE_EX, 0, 512 * sizeof(TCHAR));
		if (pszName != NULL)
		{
			sprintf(pszName, "%s", SDL_JoystickName(rdPtr->SDL_Data[joy].joystick));
		}
	}
	rdPtr->rHo.hoFlags |= HOF_STRING;
	return (long)pszName;
}

long WINAPI DLLExport GetButtonsHeld(LPRDATA rdPtr, long param1)
{
	LPTSTR pszName = ("");
	pszName = (LPTSTR)callRunTimeFunction(rdPtr, RFUNCTION_GETSTRINGSPACE_EX, 0, 16 * sizeof(TCHAR));
	int buttons = 0;
	long joy = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);
	if (pszName != NULL)
	{
		for (int i = 0; i < 32; i++)
		{
			if (rdPtr->SDL_Data[joy].held_buttons[i]) buttons |= (1 << i);
		}
		sprintf(pszName, "%08X", buttons);
	}
	rdPtr->rHo.hoFlags |= HOF_STRING;
	return (long)pszName;
}

long WINAPI DLLExport HeldButton(LPRDATA rdPtr, long param1)
{
	long joy = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);
	long index = CNC_GetNextExpressionParameter(rdPtr, param1, TYPE_INT);
	return rdPtr->SDL_Data[joy].currentheld[index];
}

long WINAPI DLLExport LastButtonPressed(LPRDATA rdPtr, long param1)
{
	long joy = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_LONG);
	return rdPtr->SDL_Data[joy].lastpressed;
}

long WINAPI DLLExport LastButtonReleased(LPRDATA rdPtr, long param1)
{
	long joy = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_LONG);
	return rdPtr->SDL_Data[joy].lastreleased;
}

// ----------------------------------------------------------
// Condition / Action / Expression jump table
// ----------------------------------------------------------
// Contains the address inside the extension of the different
// routines that handle the action, conditions and expressions.
// Located at the end of the source for convinience
// Must finish with a 0
//
long (WINAPI * ConditionJumps[])(LPRDATA rdPtr, long param1, long param2) = 
			{ 
			IsConnected,
			ButtonPressed,
			ButtonHeldDown,
			ButtonReleased,
			AnyButtonPressed,
			AnyButtonHeldDown,
			AnyButtonReleased,
			0
			};
	
short (WINAPI * ActionJumps[])(LPRDATA rdPtr, long param1, long param2) =
			{
			0
			};

long (WINAPI * ExpressionJumps[])(LPRDATA rdPtr, long param) = 
			{     
			NumJoysticks,
			GetAxis,
			GetButton,
			GetHat,
			GetBallX,
			GetBallY,
			NumAxes,
			NumButtons,
			NumHats,
			NumBalls,
			GetDeviceName,
			GetDeviceGUID,
			GetButtonsHeld,
			HeldButton,
			LastButtonPressed,
			LastButtonReleased,
			0
			};