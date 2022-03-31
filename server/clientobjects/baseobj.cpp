//Copyright © 2022 Charles Kerr. All rights reserved.

#include "baseobj.hpp"

#include <iostream>

#include "strutil.hpp"

using namespace std::string_literals ;
//=========================================================
baseobj_t::baseobj_t() {
	type = objecttype_t::base ;
	serial = invalid_serial ;
}

//=========================================================
auto baseobj_t::save(std::ostream &output) ->void {
	auto type_name = nameForObjecttype(type);
	output <<"["<<strutil::ntos(serial,strutil::radix_t::hex,true,8)<<":"<<type_name<<"]\n{\n";
	saveContents(output);
	output<<"}\n\n";
}
//=========================================================
auto baseobj_t::saveContents(std::ostream &output) ->void {
	
}
//=========================================================
auto baseobj_t::loadWorldSection(section_t &section, factory_t *factory) ->bool {
	for (auto &entry : section.entries()){
		processWorldKey(entry, factory);
	}
	return true ;
}
//=========================================================
auto baseobj_t::processWorldKey(keyvalue_t &keyvalue,factory_t *factory) ->bool {
	auto rvalue = false ;
	
	return rvalue;
}

//=========================================================
auto baseobj_t::secondaryLoad(factory_t *factory) ->void {
	for (auto &entry : secondary){
		secondaryLoad(entry, factory);
	}
}
//=========================================================
auto baseobj_t::secondaryLoad(keyvalue_t &keyvalue, factory_t *factory)->bool {
	return false ;
}

//=========================================================
auto baseobj_t::loadServerSection(section_t &section, factory_t *factory) ->bool {
	for (auto &entry : section.entries()){
		processServerKey(entry, factory);
	}
	return true ;
}
//=========================================================
auto baseobj_t::processServerKey(keyvalue_t &keyvalue, factory_t *factory) ->bool {
	return false ;
}
