//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef serversock_hpp
#define serversock_hpp

#include <cstdint>
#include <string>
#include <filesystem>
#include <memory>

#include "socket.hpp"

class client_t ;

//=========================================================
class serversock_t{
private:
	std::unique_ptr<socket_t> socket ;
	std::filesystem::path logging_location;
	bool log_incoming ;
	bool log_outgoing ;
	
public:
	serversock_t();
	
	auto listen()->void ;
	auto serviceConnection() ->client_t* ;
	auto serviceRead() ->void ;
	auto serviceWrite() ->void ;
};
#endif /* serversock_hpp */
