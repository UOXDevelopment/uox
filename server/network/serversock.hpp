//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef serversock_hpp
#define serversock_hpp

#include <cstdint>
#include <string>
#include <filesystem>
#include <memory>
#include <mutex>
#include <vector>

#include "socket.hpp"
#include "client.hpp"

//=========================================================
class serversock_t{
private:
	std::unique_ptr<socket_t> socket ;
	std::vector<std::unique_ptr<client_t>> clients ;
public:
	bool log_incoming ;
	bool log_outgoing ;
	serversock_t(bool log_incoming=false, bool log_outgoing=false);
	~serversock_t();
	auto listen(const std::string &ipaddress, const std::string & port)->bool ;
	auto serviceConnection() ->void ;
	auto serviceRead(std::filesystem::path &loglogaction) ->void ;
	auto serviceWrite() ->void ;
};
#endif /* serversock_hpp */
