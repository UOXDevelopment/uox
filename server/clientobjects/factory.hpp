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
