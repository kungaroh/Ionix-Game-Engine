#include "Input.h"
#include <unordered_map>

//	1.
//	OnUpdate method implementation:
// 		Store a local variable (Name: ionixKey) of type Keycode which uses your conversion method and the scancode from the e argument 
//		https://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlkeysym.html
// 
// 		Create a switch statement which checks the type of the e argument
//		Create a case for SDL_KEYDOWN and SDL_KEYUP (Mouse implementation can be handled similarly, but focus keyboard first)
//
//		If SDL_KEYDOWN : using ionixKey and your unordered map, check to see if they key state IS NOT handled.
//		If it's not, set the key state to pressed. 
// 
// 		If SDL_KEYUP : Using the same method as 3., set the key state to up.

//	2.
// 		Create an insance of Input in the Window class, and initialise it there, too. 
//		Call this update method from the Window::OnUpdate method and use the SDL polling loop to pass in the SDL_Event& argument
//		Probably a good iddea to clear out the SDL key checks from EventSystem->EventSDL.cpp, too
//		We will phase this loop out eventually


//	3.	Conversion method needs a switch statement which checks for SDL Scancodes (SDL_SCANCODE_SPACE etc.) 
//		and returns the corresponding Ionix keycode (enum)



//keyStates[Keycode::Ionix_Space, 0]

void Input::OnUpdate(SDL_Event & e)
{
	Keycode code = IonixKeyCodeConversion(e.key.keysym.scancode);
	Mousecode mCode = IonixMouseConversion(e.button.button);
	switch (e.type)
	{
	case SDL_KEYDOWN:
		code = IonixKeyCodeConversion(e.key.keysym.scancode);
		if (e.key.repeat == 0)
		{
			//std::cout << "update" << std::endl;
			keyStates[code] = 1;
		}
		break;
	
	case SDL_KEYUP:
		code = IonixKeyCodeConversion(e.key.keysym.scancode);
		keyStates[code] = 3; 
		break;


	case SDL_MOUSEBUTTONDOWN:
		mCode = IonixMouseConversion(e.button.button);
		mouseStates[mCode] = 1;
		break;
	case SDL_MOUSEBUTTONUP:
		mCode = IonixMouseConversion(e.button.button);
		mouseStates[mCode] = 3;
		break;
	}
}

void Input::ClearInputs()
{
	for (auto& key : keyStates) 
	{

		if (key.second == KEY_PRESSED) 
		{
			key.second = KEY_HELD;
		}
	}
	for (auto& mKey : mouseStates)
	{
		if (mKey.second == MOUSE_PRESSED)
		{
			mKey.second = MOUSE_HELD;
		}
	}

	// run thorugh keyStates, setting any that are == 1 to 2
}

bool Input::IsKeyDown(Keycode key)
{	
	if (keyStates[key] == 1)
	{
		keyStates[key] = 0;
		return true;
	}
	return false;
 	
	//return keyStates[key] == 1;
}

bool Input::IsKeyHeld(Keycode key)
{
	return keyStates[key] == 2;
}

bool Input::IsKeyUp(Keycode key) {

	if (keyStates[key] == KEY_RELEASED) 
	{
		keyStates[key] = 0;
		return true;
	}
	return false;
	//return keyStates[key] == 0;
}

bool Input::IsMouseDown(Mousecode key)
{
	if (mouseStates[key] == 1)
	{
		mouseStates[key] = 0;
		return true;
	}
	return false;

	//return mouseStates[key] == 1;
}

bool Input::IsMouseHeld(Mousecode key)
{
	return mouseStates[key] == 2;
}

bool Input::IsMouseUp(Mousecode key)
{
	if (mouseStates[key] == MOUSE_RELEASED)
	{
		mouseStates[key] = 0;
		return true;
	}
	return false;
}

float Input::GetMouseX()
{
	SDL_GetMouseState(&x, &y);
	return x;
}

float Input::GetMouseY()
{
	SDL_GetMouseState(&x, &y);
	return y;
}


Mousecode Input::IonixMouseConversion(Uint8 id)
{
	switch (id)
	{
	case SDL_BUTTON_LEFT:
		return Ionix_Mouse0;
	case SDL_BUTTON_RIGHT:
		return Ionix_Mouse1;
	case SDL_BUTTON_MIDDLE:
		return Ionix_Mouse2;
	default:
		return Ionix_MUnknown;
	}
}


Keycode Input::IonixKeyCodeConversion(SDL_Scancode scancode)
{
	switch (scancode)
	{
	case SDL_SCANCODE_SPACE:
		return Ionix_Space;
	case SDL_SCANCODE_A:
		return Ionix_A;
	case SDL_SCANCODE_B:
		return Ionix_B;
	case SDL_SCANCODE_C:
		return Ionix_C;
	case SDL_SCANCODE_D:
		return Ionix_D;
	case SDL_SCANCODE_E:
		return Ionix_E;
	case SDL_SCANCODE_F:
		return Ionix_F;
	case SDL_SCANCODE_G:
		return Ionix_G;
	case SDL_SCANCODE_H:
		return Ionix_H;
	case SDL_SCANCODE_I:
		return Ionix_I;
	case SDL_SCANCODE_J:
		return Ionix_J;
	case SDL_SCANCODE_K:
		return Ionix_K;
	case SDL_SCANCODE_L:
		return Ionix_L;
	case SDL_SCANCODE_M:
		return Ionix_M;
	case SDL_SCANCODE_N:
		return Ionix_N;
	case SDL_SCANCODE_O:
		return Ionix_O;
	case SDL_SCANCODE_P:
		return Ionix_P;
	case SDL_SCANCODE_Q:
		return Ionix_Q;
	case SDL_SCANCODE_R:
		return Ionix_R;
	case SDL_SCANCODE_S:
		return Ionix_S;
	case SDL_SCANCODE_T:
		return Ionix_T;
	case SDL_SCANCODE_U:
		return Ionix_U;
	case SDL_SCANCODE_V:
		return Ionix_V;
	case SDL_SCANCODE_W:
		return Ionix_W;
	case SDL_SCANCODE_X:
		return Ionix_X;
	case SDL_SCANCODE_Y:
		return Ionix_Y;
	case SDL_SCANCODE_Z:
		return Ionix_Z;
	case SDL_SCANCODE_1:
		return Ionix_1;
	case SDL_SCANCODE_2:
		return Ionix_2;
	case SDL_SCANCODE_3:
		return Ionix_3;
	case SDL_SCANCODE_4:
		return Ionix_4;
	case SDL_SCANCODE_5:
		return Ionix_5;
	case SDL_SCANCODE_6:
		return Ionix_6;
	case SDL_SCANCODE_7:
		return Ionix_7;
	case SDL_SCANCODE_8:
		return Ionix_8;
	case SDL_SCANCODE_9:
		return Ionix_9;
	case SDL_SCANCODE_0:
		return Ionix_0;
	case SDL_SCANCODE_RETURN:
		return Ionix_Return;
	case SDL_SCANCODE_ESCAPE:
		return Ionix_Escape;
	case SDL_SCANCODE_TAB:
		return Ionix_Tab;
	case SDL_SCANCODE_BACKSPACE:
		return Ionix_Backspace;
	case SDL_SCANCODE_DELETE:
		return Ionix_Delete;
	case SDL_SCANCODE_UP:
		return Ionix_Up;
	case SDL_SCANCODE_DOWN:
		return Ionix_Down;
	case SDL_SCANCODE_LEFT:
		return Ionix_Left;
	case SDL_SCANCODE_RIGHT:
		return Ionix_Right;
	case SDL_SCANCODE_LSHIFT:
		return Ionix_LeftShift;
	case SDL_SCANCODE_RSHIFT:
		return Ionix_RightShift;
	case SDL_SCANCODE_LCTRL:
		return Ionix_LeftControl;
	case SDL_SCANCODE_RCTRL:
		return Ionix_RightControl;
	case SDL_SCANCODE_LALT:
		return Ionix_LeftAlt;
	case SDL_SCANCODE_RALT:
		return Ionix_RightAlt;
	case SDL_SCANCODE_CAPSLOCK:
		return Ionix_CapsLock;
		// Add more keys as needed...
	default:
		return Ionix_Unknown; // Handle unknown keycodes
	}
}
	
