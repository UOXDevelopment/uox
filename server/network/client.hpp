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
	
	client_t();
	~client_t() ;
	
	auto name() const ->std::string ;
};
#endif /* client_hpp */
