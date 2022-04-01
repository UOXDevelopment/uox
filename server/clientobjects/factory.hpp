//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef factory_hpp
#define factory_hpp

#include <cstdint>
#include <memory>
#include <unordered_map>

#include "serial_generator.hpp"
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
 
 So, why doesnt Factory use std::unique_ptr ?  Well, it has to do with storage.
 I want to save all item types (including their subclasses ) in a single map.
 I can do this if I save the base pointer, but if a unique_ptr, it is a different type.
 It quickly exceeds my my limited knowledge in std::unique_ptr manipulation.
 however, since Factory is the only "ownership", we just need to ensure that
 we delete when we erase, in ONE spot.  Should be doable (and cleanup in the destructor).
 ************************************************************************ */


//=========================================================
struct factory_t {
	
	serial_generator generator ;
	tileinfo *info ;
	uomulti *multicollection ;
	secgroup_t *definitions;
	secgroup_t *configuration ;
	langmsg *languages ;
	
	
	factory_t(const factory_t&) = delete ;
	auto operator=(const factory_t&) ->factory_t& = delete ;
	factory_t()  ;
	auto set(tileinfo *info,uomulti *multi,secgroup_t *definitions, secgroup_t *configuration, langmsg *languages)->void ;
};
#endif /* factory_hpp */
