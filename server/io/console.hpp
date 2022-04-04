//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef console_hpp
#define console_hpp

#include <cstdint>
#include <string>
//=========================================================
auto initConsole() ->bool ;
auto resetConsole() ->bool ;
auto getLine() ->std::string ;
//============================================================================
// Set the title of the window
//===========================================================================
auto setConsoleTitle(const std::string &title)->void ;

#endif /* console_hpp */
