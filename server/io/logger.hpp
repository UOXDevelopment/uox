//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef logger_hpp
#define logger_hpp

#include <cstdint>
#include <chrono>
#include <string>
#include <queue>
#include <mutex>

//=========================================================
struct log_entry {
	std::chrono::system_clock::time_point logged_time ;
	std::string message ;
	log_entry(const std::string &msg);
	auto description() const ->std::string ;
};

//=========================================================
class logger {
private:
	logger() ;
	std::queue<log_entry> _console ;
	std::queue<log_entry> _logfile ;
	std::mutex msg_mutex ;
	
public:
	enum class logtype_t {console,logfile,both};
	
	logger(const logger&) = delete ;
	auto operator=(const logger&) ->logger& = delete ;
	static auto shared() ->logger& ;
	
	auto log(const std::string &msg, logtype_t type = logtype_t::console)->void;
	
	auto retreive(logtype_t type)->std::queue<log_entry> ;
};
#endif /* Logger_hpp */
