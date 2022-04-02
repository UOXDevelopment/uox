//Copyright © 2022 Charles Kerr. All rights reserved.

#include "object_types.hpp"

#include <iostream>

#include "strutil.hpp"

using namespace std::string_literals;
//=========================================================
/* ***************************************************************
 objecttype_t
 ***************************************************************** */
//=========================================================
const std::unordered_map<objecttype_t, std::string> objecttype_names{
	{objecttype_t::base,"base"s},		{objecttype_t::item,"item"s},
	{objecttype_t::mob,"mob"s},		{objecttype_t::player,"player"s},
	{objecttype_t::spawner,"spawner"s},	{objecttype_t::multi,"multi"s}
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
/* ***************************************************************
 direction_t
 ***************************************************************** */
//=========================================================
const std::unordered_map<direction_t, std::string> direction_names{
	{direction_t::north,"north"s},	{direction_t::northeast,"northeast"s},
	{direction_t::east,"east"s},		{direction_t::southeast,"southeast"s},
	{direction_t::south,"south"s},	{direction_t::southwest,"southwest"s},
	{direction_t::west,"west"s},		{direction_t::northwest,"northwest"s},
	{direction_t::unknown,"unknown"}
};
//=========================================================
auto directionForName(const std::string &name) ->direction_t {
	auto iter = std::find_if(direction_names.begin(),direction_names.end(),[&name](const std::pair<direction_t,std::string> &entry){
		return entry.second == name ;
	});
	if (iter != direction_names.end()){
		return iter->first ;
	}
	throw std::out_of_range(name +" is not a valid direction_t type"s);
}
//=========================================================
auto nameForDirection(direction_t direction) ->const std::string& {
	return direction_names.at(direction);
}
//=========================================================
auto directionNames() ->const std::unordered_map<direction_t,std::string>& {
	return direction_names;
}
/* ***************************************************************
 visible_t
 ***************************************************************** */
//=========================================================
const std::unordered_map<visible_t, std::string> visible_names{
	{visible_t::visible,"visible"s},		{visible_t::hiding,"hiding"s},
	{visible_t::invisible,"invisible"s},	{visible_t::permenent,"permenent"s},
	{visible_t::ghost,"ghost"s}
};
//=========================================================
auto visibleForName(const std::string &name) ->visible_t {
	auto iter = std::find_if(visible_names.begin(),visible_names.end(),[&name](const std::pair<visible_t,std::string> &entry){
		return entry.second == name ;
	});
	if (iter != visible_names.end()){
		return iter->first ;
	}
	throw std::out_of_range(name +" is not a valid visible_t type"s);
}
//=========================================================
auto nameForVisible(visible_t visible) ->const std::string& {
	return visible_names.at(visible);
}
//=========================================================
auto visibleNames() ->const std::unordered_map<visible_t,std::string>& {
	return visible_names;
}
/* ***************************************************************
 movable_t
 ***************************************************************** */
//=========================================================
const std::unordered_map<movable_t, std::string> movable_names{
	{movable_t::client,"client"s},	{movable_t::always,"always"s},
	{movable_t::never,"never"s},		{movable_t::owner,"owner"s},
};
//=========================================================
auto movableForName(const std::string &name) ->movable_t {
	auto iter = std::find_if(movable_names.begin(),movable_names.end(),[&name](const std::pair<movable_t,std::string> &entry){
		return entry.second == name ;
	});
	if (iter != movable_names.end()){
		return iter->first ;
	}
	throw std::out_of_range(name +" is not a valid movable_t type"s);
}
//=========================================================
auto nameForMovable(movable_t movable) ->const std::string& {
	return movable_names.at(movable);
}
//=========================================================
auto movableNames() ->const std::unordered_map<movable_t,std::string>& {
	return movable_names;
}
/* ***************************************************************
 layer_t
 ***************************************************************** */
//=========================================================
const std::unordered_map<layer_t, std::string> layer_names{
	{layer_t::none,"none"s},			{layer_t::righthand,"righthand"s},
	{layer_t::lefthand,"lefthand"s},		{layer_t::footwear,"footwear"s},
	{layer_t::pants,"pants"s},			{layer_t::innershirt,"innershirt"s},
	{layer_t::helmet,"helmet"s},			{layer_t::glove,"glove"s},
	{layer_t::ring,"ring"s},			{layer_t::talisman,"talisman"s},
	{layer_t::neck,"neck"s},			{layer_t::hair,"hair"s},
	{layer_t::waist,"waist"s},			{layer_t::tunic,"tunic"s},
	{layer_t::bracelet,"bracelet"s},		{layer_t::facialhair,"facialhair"s},
	{layer_t::outershirt,"outershirt"s},	{layer_t::earring,"earring"s},
	{layer_t::arms,"arms"s},			{layer_t::cloak,"cloak"s},
	{layer_t::pack,"pack"s},			{layer_t::robe,"robe"s},
	{layer_t::outerlegging,"outerlegging"s},	{layer_t::innerlegging,"innerlegging"s},
	{layer_t::mount,"mount"s},			{layer_t::sellcont,"sellcont"s},
	{layer_t::boughtcont,"boughtcont"s},	{layer_t::bankbox,"bankbox"s},
	{layer_t::unused,"unused"s},			{layer_t::securetrade,"securetrade"s}
};
//=========================================================
auto layerForName(const std::string &name) ->layer_t {
	auto iter = std::find_if(layer_names.begin(),layer_names.end(),[&name](const std::pair<layer_t,std::string> &entry){
		return entry.second == name ;
	});
	if (iter != layer_names.end()){
		return iter->first ;
	}
	throw std::out_of_range(name +" is not a valid layer_t type"s);
}
//=========================================================
auto nameForLayer(layer_t layer) ->const std::string& {
	return layer_names.at(layer) ;
}
//=========================================================
auto layerNames() ->const std::unordered_map<layer_t,std::string>& {
	return layer_names ;
}
/* ***************************************************************
 attrib_t
 ***************************************************************** */
//=========================================================
attrib_t::attrib_t(int str,int dex,int intell ){
	strength = str ;
	dexterity = dex ;
	intelligence = intell ;
}
//=========================================================
attrib_t::attrib_t(const std::string &line):attrib_t(){
	auto values = strutil::parse(line,",");
	switch(values.size()){
		default:
		case 3:
			intelligence=std::stoi(values[2]);
			[[fallthrough]];
		case 2:
			dexterity = std::stoi(values[1]);
			[[fallthrough]];
		case 1:
			strength = std::stoi(values[0]);
			[[fallthrough]];
		case 0:
			break;
	}
}
//=========================================================
auto attrib_t::value() const ->std::string {
	return std::to_string(strength)+","s+std::to_string(dexterity) + ","s + std::to_string(intelligence);
}
