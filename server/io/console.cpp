//Copyright © 2022 Charles Kerr. All rights reserved.

#include "console.hpp"

#include <iostream>
#if defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

#else
#include <cstdio>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#endif

using namespace std::string_literals;
//=========================================================
// State variables for console resetting ;
#if defined(_WIN32)
unsigned long _initial_input_state;
unsigned long _initial_output_state;
void* _hdStdin;
void* _hdStdout;
#else
struct termios _initial_state ;

#endif


// values for sequences
//static constexpr char ESC = 27;
static constexpr char BELL = 7;

//=========================================================
auto initConsole() ->bool {
	auto rvalue = false ;
#if defined(_WIN32)
	_hdStdin = GetStdHandle(STD_INPUT_HANDLE);
	_hdStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleMode(_hdStdin, &_initial_input_state); // Save the old state
	GetConsoleMode(_hdStdout, &_initial_output_state);
	auto mode = _initial_output_state | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(_hdStdout, mode);
	mode = (((_initial_input_state & ~ENABLE_MOUSE_INPUT)) | (ENABLE_LINE_INPUT)) | ENABLE_EXTENDED_FLAGS | ENABLE_VIRTUAL_TERMINAL_INPUT;
	SetConsoleMode(_hdStdin, mode);
	rvalue = true;
#else
	if (tcgetattr(fileno(stdin),&_initial_state) == 0) {
		auto temp = _initial_state ;
		temp.c_lflag = temp.c_lflag & (~ICANON); // Disable canonical (line) mode
		temp.c_cc[VMIN] = 0;  		// in non canonical mode we non blocking read
		temp.c_cc[VTIME] = 0; // in non canonical mode we non blocking read
		if (tcsetattr(fileno(stdin), TCSANOW, &temp) ==0) {
			rvalue = true ;
		}
	}
	
#endif
	return rvalue ;
}
//=========================================================
auto resetConsole() ->bool {
	auto rvalue = false ;
#if defined(_WIN32)
	SetConsoleMode(_hdStdin, _initial_input_state);
	SetConsoleMode(_hdStdout, _initial_output_state);
	rvalue = true ;
#else
	if (tcsetattr(1, TCSAFLUSH, &_initial_state)==0){
		rvalue = true ;
	}
#endif
	return rvalue ;
}

//==========================================================
static std::string console_line;
auto getLine() ->std::string {
	auto rvalue = std::string();
	auto keep_reading = true;

#if defined(_WIN32)
	DWORD numread;
	INPUT_RECORD input;
	while (keep_reading) {
		GetNumberOfConsoleInputEvents(_hdStdin, &numread);
		if (numread > 0) {
			if (ReadConsoleInput(_hdStdin, &input, 1, &numread)) {
				if (numread > 0) {
					switch (input.EventType) {
					case KEY_EVENT:
					{
						if (!input.Event.KeyEvent.bKeyDown) {
							auto repeat = input.Event.KeyEvent.wRepeatCount;
							auto key = input.Event.KeyEvent.uChar.AsciiChar;
							auto keyinput = std::string(repeat, key);
							if (keyinput.size() > 0) {
								if (keyinput[0] == '\r') {
									keep_reading = false;
									rvalue = console_line;
									console_line = ""s;
									keyinput = "\n"s;
								}
								else {
									console_line += keyinput;
								}
								WriteConsole(_hdStdout, keyinput.c_str(), static_cast<DWORD>(keyinput.size()), nullptr, nullptr);
							}
						}
						break;
					}
					case MOUSE_EVENT:
					case WINDOW_BUFFER_SIZE_EVENT:
					case FOCUS_EVENT:
					case MENU_EVENT:
					default:

						break;
					}

				}
			}

		}
		else {
			keep_reading = false;

		}
	}

#else
	char key;
	while (keep_reading) {
		auto size = read(1, &key, 1);
		if (size != 0) {
			if (key == '\n') {
				rvalue = console_line;
				console_line = ""s;
				keep_reading = false;
			}
			else {
				
				console_line += std::string(1, key);
			}
		}
		else {
			keep_reading = false;
		}
	}

#endif
	return rvalue;
}

//============================================================================
// Set the title of the window
//===========================================================================
auto setConsoleTitle(const std::string &title)->void {
	std::cout <<"\x1b]2;";
	std::copy(title.begin(),title.end(),std::ostreambuf_iterator<char>(std::cout));
	std::cout << BELL ;
	
}
