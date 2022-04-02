//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef factory_hpp
#define factory_hpp

#include <cstdint>
#include <memory>
#include <unordered_map>

#include "object_types.hpp"
#include "serial_generator.hpp"
#include "baseobj.hpp"
#include "itemobj.hpp"

class tileinfo ;
class uomulti ;
class secgroup_t ;
class langmsg;

/* ************************************************************************
 Comment on pointers.
 	When dealing with pointers, there is a difference between ownership and use.
 Modern C++ indicates that raw pointes are fine, when dealing with use.  One
 can pass raw pointers at will, if one isn't transfer or converying ownership
 responsiblity to that method/function. Ownership fyi, is the responibiity
 of deleting the pointer, or ensuring the pointer memory is maintained.
 
 Now, in our use, the only "ownership" of our object pointers is the factory.
 So we can have it provide raw pointers to the rest of the system for use.
 
 
 ************************************************************************ */


//=========================================================
struct factory_t {
	std::unordered_map<serial_t, std::unique_ptr<itemobj_t>> items ;

	
	serial_generator generator ;
	tileinfo *info ;
	uomulti *multicollection ;
	secgroup_t *definitions;
	secgroup_t *configuration ;
	langmsg *languages ;
	
	
	factory_t(const factory_t&) = delete ;
	auto operator=(const factory_t&) ->factory_t& = delete ;
	factory_t()  ;
	~factory_t();
	auto set(tileinfo *info,uomulti *multi,secgroup_t *definitions, secgroup_t *configuration, langmsg *languages)->void ;
	auto create(objecttype_t type) ->baseobj_t* ;
	auto create(objecttype_t type, serial_t serial) ->baseobj_t* ;
	auto erase(serial_t serial) ->void ;
};
#endif /* factory_hpp */
