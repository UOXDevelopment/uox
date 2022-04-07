//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef client_hpp
#define client_hpp

#include <cstdint>
#include <mutex>
#include <queue>
#include <memory>
#include <string>

#include "packet.hpp"
#include "socket.hpp"

struct playerobj_t ;
//=========================================================
class client_t  {
private:
	bool received_packet ;
	std::mutex incoming_mutex ;
	std::mutex outgoing_mutex;
	std::queue<std::unique_ptr<packet_t>> incoming ;
	std::queue<std::unique_ptr<packet_t>> outgoing ;
	std::unique_ptr<socket_t> socket ;

public:
	bool log_incoming ;
	bool log_outgoing ;
	bool logoff ;
	playerobj_t *player ;
	
	~client_t() ;
	client_t();
	client_t(std::unique_ptr<socket_t> &socket);
	auto set(std::unique_ptr<socket_t> &socket)->client_t&;
	auto name() const ->std::string ;
	auto read() ->void ;
	auto write() ->void ;
	auto size() const ->size_t ;
	auto valid() const ->bool ;
	auto packet() ->std::unique_ptr<packet_t> ;
	
};
#endif /* client_hpp */
