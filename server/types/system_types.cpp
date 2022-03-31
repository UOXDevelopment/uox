//Copyright © 2022 Charles Kerr. All rights reserved.

#include "system_types.hpp"

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
	{servmod_t::data,"data"s},{servmod_t::user,"user"s},{servmod_t::ultima,"ultima"s}
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
	{serverloc_t::configuration,"configuration"s},{serverloc_t::definition,"definition"s},
	{serverloc_t::language,"language"s},{serverloc_t::script,"script"s}
};
//=========================================================
auto nameForServerLoc(serverloc_t type) -> const std::string& {
	return serverloc_names.at(type);
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

//=========================================================
/* ******************************************************
 userloc_t
 *******************************************************/
//=========================================================
const std::map<userloc_t,std::string> userloc_names{
	{userloc_t::configuration,"configuration"s},{userloc_t::definition,"definition"s},
	{userloc_t::language,"language"s},{userloc_t::script,"script"s},
	{userloc_t::log,"log"s},{userloc_t::msgboard,"msgboard"s},
	{userloc_t::world,"world"s},{userloc_t::book,"book"s},
	{userloc_t::access,"access"s},{userloc_t::scriptdata,"scriptdata"s}
};
//=========================================================
auto nameForUserLoc(userloc_t type) -> const std::string& {
	return userloc_names.at(type) ;
}
//=========================================================
auto userlocForName(const std::string &name) ->userloc_t {
	auto iter = std::find_if(userloc_names.begin(),userloc_names.end(),[&name](const std::pair<userloc_t,std::string> &entry){
		return entry.second == name ;
	});
	if (iter != userloc_names.end()){
		return iter->first ;
	}
	throw std::out_of_range(name +" is not a valid userloc_t type"s);
}
//=========================================================
auto userlocNames() ->const std::map<userloc_t,std::string>& {
	return userloc_names;
}
