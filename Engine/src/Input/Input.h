#pragma once
#include <SDL.h>
#include <unordered_map>
#include <iostream>

//	1.
//	enum which defines Ionix Keycodes
//	Add a None/Default/Unknown entry
//	Ionix_Space .. and so on. Add two entries for testing, such as Ionix_Space and Ionix_A   X

enum Keycode {
    Ionix_A,
    Ionix_B,
    Ionix_C,
    Ionix_D,
    Ionix_E,
    Ionix_F,
    Ionix_G,
    Ionix_H,
    Ionix_I,
    Ionix_J,
    Ionix_K,
    Ionix_L,
    Ionix_M,
    Ionix_N,
    Ionix_O,
    Ionix_P,
    Ionix_Q,
    Ionix_R,
    Ionix_S,
    Ionix_T,
    Ionix_U,
    Ionix_V,
    Ionix_W,
    Ionix_X,
    Ionix_Y,
    Ionix_Z,
    Ionix_0,
    Ionix_1,
    Ionix_2,
    Ionix_3,
    Ionix_4,
    Ionix_5,
    Ionix_6,
    Ionix_7,
    Ionix_8,
    Ionix_9,
    Ionix_Space,
    Ionix_Return,
    Ionix_Escape,
    Ionix_Tab,
    Ionix_Backspace,
    Ionix_Delete,
    Ionix_Up,
    Ionix_Down,
    Ionix_Left,
    Ionix_Right,
    Ionix_LeftShift,
    Ionix_RightShift,
    Ionix_LeftControl,
    Ionix_RightControl,
    Ionix_LeftAlt,
    Ionix_RightAlt,
    Ionix_CapsLock,
    Ionix_Unknown
    // For handling unknown keycodes
    // Add more keys as needed...
};

enum Mousecode
{
    Ionix_Mouse0, //Left
    Ionix_Mouse2, //Middle
    Ionix_Mouse1, //Right
    Ionix_MUnknown
};


enum Keystate {
    KEY_NOT_PRESSED = 0,
    KEY_PRESSED = 1,
    KEY_HELD = 2,
    KEY_RELEASED = 3
	
//	0=not interracted
//  1= pressed
//  2= held
//  3= released

};

enum Mousestate {
    MOUSE_NOT_PRESSED = 0,
    MOUSE_PRESSED = 1,
    MOUSE_HELD = 2,
    MOUSE_RELEASED = 3
};




//	2.
//  enum which defines Keystates
//	Probably a good idea to have None/Default/Unknown, Pressed, Handled, Held, Up   x/


//	3.
// These enums will be used with a map so that we can track the current state of keys in Ionix (Default, Pressed, Handled, Held, or Up)
// The general idea is to query this map to check input state and return true/false based off this

class Input
{
public:

	//	4.
	//	OnUpdate method which takes a reference to SDL_Event and returns nothing

	void OnUpdate(SDL_Event& e);
	void ClearInputs();
	bool IsKeyDown(Keycode key);

	bool IsKeyHeld(Keycode key);
	bool IsKeyUp(Keycode key);
    bool IsMouseDown(Mousecode key);
    bool IsMouseUp(Mousecode key);
    bool IsMouseHeld(Mousecode key);
    float GetMouseX();
    float GetMouseY();
	//	5.
	//	Getter method which returns a key's keystate. Keystate return type with a single paramater of type Keycode.
	//	Put the implementation in the .h

	//	6.
	//	Setter which sets the key state of a Keycode in the keyStates map

private:
    std::unordered_map<Keycode, int> keyStates;
    std::unordered_map<Mousecode, int> mouseStates;
    Keycode IonixKeyCodeConversion(SDL_Scancode scancode);
    Mousecode IonixMouseConversion(Uint8 id);
    int x;
    int y;
	//	7.
	// unordered map - Types: Keycode, Keystate : A suitable name for this would be keyStates or something similar    X

	// 8.
	// A conversion method which takes in a single argument of type SDL_Scancode and returns a value from our Keycode enum  X
};

//




