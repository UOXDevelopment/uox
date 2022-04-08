//Copyright © 2022 Charles Kerr. All rights reserved.

#include "serversock.hpp"
#include "strutil.hpp"

#include <iostream>
#include <utility>

using namespace std::string_literals ;
//=========================================================
serversock_t::serversock_t(bool log_incoming ,bool log_outgoing){
	this->log_incoming = log_incoming ;
	this->log_outgoing = log_outgoing ;
	socket = nullptr ;

}
//=========================================================
serversock_t::~serversock_t(){
	// we dont need to do anything?
}
//=========================================================
auto serversock_t::listen(const std::string &ipaddress, const std::string & port)->bool {
	socket = socket_t::listen(ipaddress,port,false) ;
	return socket != nullptr ;
}
//=========================================================
auto serversock_t::serviceConnection() ->void {
	if (socket){
		auto sock = socket->accept(false) ;
		if (sock){
			auto client = client_t(sock) ;
			clients.push_back(std::move(client));
		}
	}
}
