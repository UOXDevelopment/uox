//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef system_types_hpp
#define system_types_hpp

#include <cstdint>
#include <string>
#include <map>

//=========================================================
/* ******************************************************
 servermod_t
 *******************************************************/
//=========================================================
enum class servmod_t {
	data,user,ultima
};
//=========================================================
auto nameForServMod(servmod_t modifier) -> const std::string& ;
//=========================================================
//=========================================================
auto servmodForName(const std::string &name) ->servmod_t ;
auto servmodNames() ->const std::map<servmod_t,std::string>& ;

//=========================================================
/* ******************************************************
 serverloc_t
 *******************************************************/
//=========================================================
enum class serverloc_t {
	configuration,definition,language,script
};
//=========================================================
auto nameForServerLoc(serverloc_t type) -> const std::string& ;
//=========================================================
auto serverlocForName(const std::string &name) ->serverloc_t ;
//=========================================================
auto serverlocNames() ->const std::map<serverloc_t,std::string>& ;

//=========================================================
/* ******************************************************
 userloc_t
 *******************************************************/
//=========================================================
enum class userloc_t {
	configuration,definition,language,script,log,msgboard,world,book,access,scriptdata
};
//=========================================================
auto nameForUserLoc(userloc_t type) -> const std::string& ;
//=========================================================
auto userlocForName(const std::string &name) ->userloc_t ;
//=========================================================
auto userlocNames() ->const std::map<userloc_t,std::string>& ;


#endif /* system_types_hpp */
