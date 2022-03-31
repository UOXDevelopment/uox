//Copyright © 2022 Charles Kerr. All rights reserved.

#include "ultima_types.hpp"

#include <iostream>

using namespace std::string_literals ;
//=========================================================
const std::unordered_map<tiletype_t, std::string> tiletype_names{
	{tiletype_t::invalid,"invalid"s}, {tiletype_t::terrain,"terrain"s}, {tiletype_t::art,"art"s}
};
//=========================================================
auto nameForTiletype(tiletype_t type) -> const std::string& {
	return tiletype_names.at(type) ;
}
//=========================================================
auto tiletypeForName(const std::string &name) ->tiletype_t {
	auto iter = std::find_if(tiletype_names.begin(),tiletype_names.end(),[&name](const std::pair<tiletype_t,std::string> &entry){
		return entry.second == name ;
	});
	if (iter != tiletype_names.end()){
		return iter->first ;
	}
	throw std::out_of_range(name +" is not a valid tiletype_t type"s);
}
//=========================================================
auto tiletypeNames() ->const std::unordered_map<tiletype_t,std::string>& {
	return tiletype_names;
}

