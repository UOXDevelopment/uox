//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef object_types_hpp
#define object_types_hpp

#include <cstdint>
#include <unordered_map>

//=========================================================
using serial_t = std::uint32_t ;
constexpr auto invalid_serial = serial_t(0xFFFFFFFF) ;

/* ***************************************************************
 objecttype_t
 ***************************************************************** */
enum class objecttype_t {base,item,mob,player,spawner,multi};
auto objecttypeForName(const std::string &name) ->objecttype_t ;
auto nameForObjecttype(objecttype_t objecttype) ->const std::string& ;
auto objecttypeNames() ->const std::unordered_map<objecttype_t,std::string>& ;
/* ***************************************************************
 direction_t
 ***************************************************************** */
enum class  direction_t:std::uint8_t {
	north=0,northeast=1,east=2,southeast=3,south=4,southwest=5,west=6,northwest=7,unknown=0xFF
};
auto directionForName(const std::string &name) ->direction_t ;
auto nameForDirection(direction_t direction) ->const std::string& ;
auto directionNames() ->const std::unordered_map<direction_t,std::string>& ;
/* ***************************************************************
 visible_t
 ***************************************************************** */
enum class visible_t {visible,hiding,invisible,permenent,ghost} ;
auto visibleForName(const std::string &name) ->visible_t ;
auto nameForVisible(visible_t visible) ->const std::string& ;
auto visibleNames() ->const std::unordered_map<visible_t,std::string>& ;
/* ***************************************************************
 movable_t
 ***************************************************************** */
enum class movable_t {client,always,never,owner};
auto movableForName(const std::string &name) ->movable_t ;
auto nameForMovable(movable_t movable) ->const std::string& ;
auto movableNames() ->const std::unordered_map<movable_t,std::string>& ;
/* ***************************************************************
 layer_t
 ***************************************************************** */
enum class layer_t {none,righthand,lefthand,footwear,pants,innershirt,helmet,glove,ring,
	talisman,neck,hair,waist,tunic,bracelet,facialhair,outershirt,earring,arms,cloak,pack,robe,
	outerlegging,innerlegging,mount,sellcont,boughtcont,bankbox,unused,securetrade
};
auto layerForName(const std::string &name) ->layer_t ;
auto nameForLayer(layer_t layer) ->const std::string& ;
auto layerNames() ->const std::unordered_map<layer_t,std::string>& ;
/* ***************************************************************
 attrib_t
 ***************************************************************** */
struct attrib_t {
	int strength;
	int intelligence ;
	int dexterity;
	
	attrib_t(int str=0,int dex=0,int intell=0 );
	attrib_t(const std::string &line) ;
	auto value() const ->std::string ;
};
#endif /* object_types_hpp */
