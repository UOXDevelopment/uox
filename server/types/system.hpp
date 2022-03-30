//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef system_hpp
#define system_hpp

#include <cstdint>
#include <string>
#include <map>

//=========================================================
/* ******************************************************
 servmod_t
 *******************************************************/
enum class servmod_t {
	server,user
};
auto nameForServMod(servmod_t modifier) -> const std::string& ;
auto servmodForName(const std::string &name) ->servmod_t ;
auto servmodNames() ->const std::map<servmod_t,std::string>& ;
#endif /* system_hpp */