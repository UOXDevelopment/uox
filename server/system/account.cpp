//Copyright © 2022 Charles Kerr. All rights reserved.

#include "account.hpp"

#include <iostream>
#include <algorithm>
#include <fstream>

#include "secgroup.hpp"
#include "strutil.hpp"
#include "playerobj.hpp"
#include "factory.hpp"
#include "section.hpp"
#include "secgroup.hpp"
#include "secparser.hpp"

using namespace std::string_literals;
/* *************************************************************************
 actentry_t
 ************************************************************************ */
//=========================================================
actentry_t::actentry_t(){
	player = nullptr ;
	created_on = std::chrono::system_clock::now();
	logged_off = std::chrono::system_clock::now();
	this->privilege = priv_t::player ;
}

//=========================================================
actentry_t::actentry_t(const std::string &line,factory_t *factory):actentry_t() {
	auto values = strutil::parse(line) ;
	switch (values.size()) {
		default:
		case 4:
			logged_off = strutil::stringToSysTime(values[3]) ;
			[[fallthrough]] ;
		case 3:
			created_on = strutil::stringToSysTime(values[2]) ;
			[[fallthrough]] ;
		case 2:
			privilege = privForName(values[1]) ;;
			[[fallthrough]] ;
		case 1:
		{
			//auto serial = strutil::ston<serial_t>(values[0]) ;
			// Get the player pointer from the factory here
			
			[[fallthrough]] ;
		}
		case 0:
			break;
	}
}
//=========================================================
auto actentry_t::value() const ->std::string {
	auto rvalue = strutil::ntos(invalid_serial) ;
	if (player){
		rvalue = strutil::ntos(player->serial);
		rvalue +=","s + nameForPriv(privilege);
		rvalue += ","s + strutil::sysTimeToString(created_on) + ","s + strutil::sysTimeToString(logged_off) ;
	}
	return rvalue ;
}

/* *************************************************************************
 account_t
 ************************************************************************ */
account_t::account_t(factory_t *factory){
	number = invalid_account ;
	this->factory = factory ;
	created_on = std::chrono::system_clock::now();
	
}
//=========================================================
auto account_t::save(std::ostream &output) const ->void {
	output <<"["<<number<<"account]\n{\n";
	output <<"\tusername = "<<username <<"\n";
	output <<"\tpassword = "<<password<<"\n";
	output <<"\tprivilege = " << nameForPriv(privilege) <<"\n";
	output <<"\tcreated_on = "<<strutil::sysTimeToString(created_on)<<"\n";
	for (auto i=0 ; i<max_characters;++i) {
		output <<"\tcharacter = " << i<<","s<<characters[i].value()<<"\n";
	}
}
//=========================================================
account_t::account_t(const section_t &section,factory_t *factory) :account_t(factory){
	number = strutil::ston<actnum_t>(section.header().identifier());
	load(section) ;
}
//=========================================================
auto account_t::load(const section_t &section) ->void {
	for (auto entry : section.entries()){
		if (entry.key()=="username"){
			username = entry.value();
		}
		else if (entry.key() == "password"){
			password = entry.value() ;
		}
		else if (entry.key() == "privilege"){
			privilege = privForName(entry.value());
		}
		else if (entry.key() == "created_on") {
			created_on = strutil::stringToSysTime(entry.value());
		}
		else if (entry.key() == "character") {
			auto [num,line] = strutil::split(entry.value(),",") ;
			characters[strutil::ston<actnum_t>(num)] = actentry_t(line,factory) ;
		}
	}
}

/* *************************************************************************
 actholder_t
 ************************************************************************ */
//=========================================================
actholder_t::~actholder_t() {
	if (!accountfile.empty()){
		auto output = std::ofstream(accountfile);
		for (const auto &account : accounts){
			account.second.save(output);
		}
	}
}
//=========================================================
actholder_t::actholder_t(bool create_account, factory_t * factory):secparser_t() {
	this->factory = factory;
	this->create_account = create_account ;
	nextnumber = 0 ;
}
//=========================================================
auto actholder_t::set(const std::string &filepath) ->bool {
	accountfile = filepath ;
	auto rvalue = true ;
	auto group = secgroup_t(filepath,true,".act") ;
	auto sections = group.type("account") ;
	if (sections != nullptr){
		for (const auto &section:*sections){
			auto account = account_t(section.second,factory);
			accounts.try_emplace(account.username, std::move(account));
		}
	}
	// Now we need to get the next account number ;
	int tempnumber = -1 ;
	for (const auto &account : accounts){
		tempnumber = std::max(tempnumber,account.second.number);
	}
	nextnumber = tempnumber + 1 ;
	return rvalue ;
}
//=========================================================
auto actholder_t::size() const ->size_t {
	return accounts.size();
}
//=========================================================
auto actholder_t::account(const std::string &name) -> account_t * {
	account_t *rvalue = nullptr ;
	try {
		rvalue = &accounts.at(name);
	}
	catch(...) {
		// wasnt found
	}
	return rvalue ;
}

//============================================================
auto actholder_t::createAccount(const std::string &username, const std::string &password, priv_t privilege)->account_t* {
	account_t *rvalue = nullptr ;
	
	// First, make sure the account doesn't exist
	rvalue = account(username) ;
	if (rvalue != nullptr) {
		// this account exists
		std::cerr <<"Account " << rvalue->username<< " all ready exists, created on: "<< strutil::sysTimeToString(rvalue->created_on)<<std::endl;
		rvalue = nullptr ;
	}
	else {
		// Ok, it doesnt exists, which is good, now we can create it
		auto account = account_t(factory) ;
		account.number = ++nextnumber ;
		account.username = username ;
		account.privilege = privilege ;
		account.password = password ;
		auto status = accounts.try_emplace(username, std::move(account));
		rvalue =  &((status.first)->second);
	}
	return rvalue ;
}
//============================================================
auto actholder_t::processSection(section_t &section) ->void {
	if (section.header().identifier()=="account"){
		auto username = section.last("username") ;
		if (username != nullptr){
			auto account = this->account(username->value());
			if (account == nullptr){
				auto password = std::string() ;
				auto passkey = section.last("password") ;
				if (passkey){
					password = passkey->value();
				}
				auto privilege = priv_t::player ;
				auto priv = section.last("privilege") ;
				if (priv){
					privilege = privForName(priv->value());
				}
				account = this->createAccount(username->value(), password, privilege);
			}

		}
	}
}
