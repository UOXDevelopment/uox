//Copyright © 2022 Charles Kerr. All rights reserved.

#include "object_types.hpp"

#include <iostream>

using namespace std::string_literals;
//=========================================================
/* ***************************************************************
 objecttype_t
 ***************************************************************** */
//=========================================================
const std::unordered_map<objecttype_t, std::string> objecttype_names{
	{objecttype_t::base,"base"s}, 	{objecttype_t::item,"item"s}, 		{objecttype_t::mob,"mob"s},
	{objecttype_t::player,"player"s}, 	{objecttype_t::spawner, "spawner"s}, 	{objecttype_t::multi,"multi"s}
};
//=========================================================
auto objecttypeForName(const std::string &name) ->objecttype_t {
	auto iter = std::find_if(objecttype_names.begin(),objecttype_names.end(),[&name](const std::pair<objecttype_t,std::string> &entry){
		return entry.second == name ;
	});
	if (iter != objecttype_names.end()){
		return iter->first ;
	}
	throw std::out_of_range(name +" is not a valid objecttype_t type"s);
}
//=========================================================
auto nameForObjecttype(objecttype_t objecttype) ->const std::string& {
	return objecttype_names.at(objecttype);
}
//=========================================================
auto objecttypeNames() ->const std::unordered_map<objecttype_t,std::string>& {
	return objecttype_names;
}
