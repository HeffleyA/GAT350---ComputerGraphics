#include "Input.h"
#include <SDL.h>

bool Input::Initialize()
{
	int numKeys;
	const uint8_t* keyboardState = SDL_GetKeyboardState(&numKeys);

	m_keyboardState.resize(numKeys);

	// copy current keyboard state into our keyboard state
	std::copy(keyboardState, keyboardState + numKeys, m_keyboardState.begin());
	m_prevKeyboardState = m_keyboardState;

	return true;
}

void Input::Shutdown()
{
	//
}

void Input::Update()
{
	// keyboard input
	m_prevKeyboardState = m_keyboardState;
	const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
	std::copy(keyboardState, keyboardState + m_keyboardState.size(), m_keyboardState.begin());

	// mouse input
	int x, y;
	uint32_t buttonState = SDL_GetMouseState(&x, &y);

	m_mousePosition.x = (float)x;
	m_mousePosition.y = (float)y;

	SDL_GetRelativeMouseState(&x, &y);
	m_mouseRelative.x = (float)x;
	m_mouseRelative.y = (float)y;

	// 000 <- button state
	// 010 <- button mask
	// 000
	m_prevMouseButtonState = m_mouseButtonState;
}

void Input::SetRelativeMode(bool relative)
{
	SDL_SetRelativeMouseMode(relative ? SDL_TRUE : SDL_FALSE);
}