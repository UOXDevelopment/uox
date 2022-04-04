//Copyright © 2022 Charles Kerr. All rights reserved.

#include "mobobj.hpp"


//=========================================================
mobobj_t::mobobj_t() :baseobj_t(){
	type = objecttype_t::mob ;
}
//=========================================================
mobobj_t::~mobobj_t() {
	
}

//=========================================================
auto mobobj_t::saveContents(std::ostream &output) ->void {
	baseobj_t::saveContents(output);
	
}
//=========================================================
auto mobobj_t::processWorldKey(const keyvalue_t &keyvalue,factory_t *factory) ->bool {
	auto rvalue = baseobj_t::processWorldKey(keyvalue, factory);
	if (!rvalue){
		
	}
	return rvalue ;
}
//=========================================================
auto mobobj_t::secondaryLoad(const keyvalue_t &keyvalue, factory_t *factory)->bool {
	baseobj_t::secondaryLoad(keyvalue, factory) ;
	return true ;
}
//=========================================================
auto mobobj_t::processServerKey(const keyvalue_t &keyvalue, factory_t *factory) ->bool {
	
	auto rvalue = baseobj_t::processServerKey(keyvalue, factory);
	if (!rvalue) {
		
	}
	return rvalue ;
}
