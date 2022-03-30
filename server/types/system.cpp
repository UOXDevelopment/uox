//Copyright © 2022 Charles Kerr. All rights reserved.

#include "system.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>
#include <stdexcept>

using namespace std::string_literals;
//=========================================================
/* ******************************************************
 servmod_t
 *******************************************************/
//=========================================================
const std::map<servmod_t,std::string> servmod_names{
	{servmod_t::data,"data"s},{servmod_t::user,"user"s}
};
//=========================================================
auto nameForServMod(servmod_t modifier) -> const std::string& {
	return servmod_names.at(modifier);
}
//=========================================================
auto servmodForName(const std::string &name) ->servmod_t {
	auto iter = std::find_if(servmod_names.begin(),servmod_names.end(),[&name](const std::pair<servmod_t,std::string> &entry){
		return entry.second == name ;
	});
	if (iter != servmod_names.end()){
		return iter->first ;
	}
	throw std::out_of_range(name +" is not a valid servmod_t type"s);
}
//=========================================================
auto servmodNames() ->const std::map<servmod_t,std::string>& {
	return servmod_names;
}

//=========================================================
/* ******************************************************
 serverloc_t
 *******************************************************/
//=========================================================
const std::map<serverloc_t,std::string> serverloc_names{
	{serverloc_t::configuration,"configuration"s},{serverloc_t::language,"language"s},
	{serverloc_t::language,"language"s},{serverloc_t::script,"script"s},
};
//=========================================================
auto nameForServerLoc(serverloc_t modifier) -> const std::string& {
	return serverloc_names.at(modifier);
}
//=========================================================
auto serverlocForName(const std::string &name) ->serverloc_t {
	auto iter = std::find_if(serverloc_names.begin(),serverloc_names.end(),[&name](const std::pair<serverloc_t,std::string> &entry){
		return entry.second == name ;
	});
	if (iter != serverloc_names.end()){
		return iter->first ;
	}
	throw std::out_of_range(name +" is not a valid serverloc_t type"s);
}
//=========================================================
auto serverlocNames() ->const std::map<serverloc_t,std::string>& {
	return serverloc_names;
}
