//Copyright © 2022 Charles Kerr. All rights reserved.

#include "itemobj.hpp"

#include <iostream>

//=========================================================
itemobj_t::itemobj_t() :baseobj_t(){
	type = objecttype_t::item ;
}
//=========================================================
itemobj_t::~itemobj_t() {
	
}

//=========================================================
auto itemobj_t::saveContents(std::ostream &output) ->void {
	baseobj_t::saveContents(output);
	
}
//=========================================================
auto itemobj_t::processWorldKey(const keyvalue_t &keyvalue,factory_t *factory) ->bool {
	auto rvalue = baseobj_t::processWorldKey(keyvalue, factory);
	if (!rvalue){
		
	}
	return rvalue ;
}
//=========================================================
auto itemobj_t::secondaryLoad(const keyvalue_t &keyvalue, factory_t *factory)->bool {
	baseobj_t::secondaryLoad(keyvalue, factory) ;
	return true ;
}
//=========================================================
auto itemobj_t::processServerKey(const keyvalue_t &keyvalue, factory_t *factory) ->bool {
	
	auto rvalue = baseobj_t::processServerKey(keyvalue, factory);
	if (!rvalue) {
		
	}
	return rvalue ;
}
