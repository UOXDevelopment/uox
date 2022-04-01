//Copyright © 2022 Charles Kerr. All rights reserved.

#include "factory.hpp"

#include <iostream>

#include "secgroup.hpp"
#include "langmsg.hpp"
#include "tileinfo.hpp"
#include "uomulti.hpp"
//=========================================================
factory_t::~factory_t(){
	for (auto &entry : items){
		delete entry.second;
	}
	for (auto &entry : mobiles){
		delete entry.second;
	}
}
//=========================================================
factory_t::factory_t() {
	info =nullptr;
	multicollection =nullptr;
	definitions = nullptr;
	configuration = nullptr ;
	languages = nullptr ;
}
//=========================================================
auto factory_t::set(tileinfo *info,uomulti *multi,secgroup_t *definitions, secgroup_t *configuration, langmsg *languages)->void{
	this->info = info ;
	this->multicollection = multi ;
	this->definitions = definitions;
	this->configuration = configuration ;
	this->languages = languages ;
}
