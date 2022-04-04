//Copyright © 2022 Charles Kerr. All rights reserved.

#include "logger.hpp"

#include <algorithm>

#include "strutil.hpp"

using namespace std::string_literals ;
//=========================================================
log_entry::log_entry(const std::string &msg){
	logged_time = std::chrono::system_clock::now() ;
	message = msg ;
}
//=========================================================
auto log_entry::description() const ->std::string {
	return strutil::sysTimeToString(logged_time)+" - "s + message ;
}
//=========================================================
logger::logger() {
	
}
//=========================================================
auto logger::shared() ->logger& {
	static logger instance ;
	return instance ;
}

//=========================================================
auto logger::log(const std::string &msg, logtype_t type )->void {
	auto entry = log_entry(msg) ;
	std::lock_guard lock(msg_mutex) ;
	if ((type == logtype_t::console) || (type == logtype_t::both)){
		_console.push(entry);
	}
	else if ((type == logtype_t::logfile) || (type == logtype_t::both)){
		_logfile.push(entry) ;
	}
}

//=========================================================
auto logger::retreive(logtype_t type)->std::queue<log_entry> {
	std::queue<log_entry> blank ;
	std::lock_guard lock(msg_mutex) ;
	if (type == logtype_t::console){
		std::swap(blank,_console);
	}
	else if (type == logtype_t::logfile){
		std::swap(blank,_logfile);
	}
	return blank ;
}
