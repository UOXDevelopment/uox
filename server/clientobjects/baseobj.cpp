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
	output <<"\tlocation = " << location.value()<<"\n";
	output <<"\tattr = " << attr.value() <<"\n";
}
//=========================================================
auto baseobj_t::loadWorldSection(const section_t &section, factory_t *factory) ->bool {
	for (const auto &entry : section.entries()){
		processWorldKey(entry, factory);
	}
	return true ;
}
//=========================================================
auto baseobj_t::processWorldKey(const keyvalue_t &keyvalue,factory_t *factory) ->bool {
	auto rvalue = false ;
	auto key = keyvalue.key();
	
	if (key == "location"){
		rvalue = true ;
		location = location_t(keyvalue.value());
	}
	else if (key=="attr"){
		rvalue  = true ;
		attr = attrib_t(keyvalue.value());
	}
	return rvalue;
}

//=========================================================
auto baseobj_t::secondaryLoad(factory_t *factory) ->void {
	for (auto &entry : secondary){
		secondaryLoad(entry, factory);
	}
}
//=========================================================
auto baseobj_t::secondaryLoad(const keyvalue_t &keyvalue, factory_t *factory)->bool {
	return false ;
}

//=========================================================
auto baseobj_t::loadServerSection(const section_t &section, factory_t *factory) ->bool {
	for (auto &entry : section.entries()){
		processServerKey(entry, factory);
	}
	return true ;
}
//=========================================================
auto baseobj_t::processServerKey(const keyvalue_t &keyvalue, factory_t *factory) ->bool {
	return false ;
}
