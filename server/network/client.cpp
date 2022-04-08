//Copyright © 2022 Charles Kerr. All rights reserved.

#include "client.hpp"

#include <iostream>
#include <algorithm>

#include "ip4addr.hpp"
#include "strutil.hpp"
#include "playerobj.hpp"

using namespace std::string_literals;
//=========================================================
client_t::~client_t() {
	if (player != nullptr){
		player->client = nullptr ;
	}
	player = nullptr ;
	auto attempt = 10 ;
	while ((attempt>0) && socket->valid() && (outgoing.size()>0)){
		
	}
}
//=========================================================
client_t::client_t() {
	received_packet = false;
	log_incoming = false ;
	log_outgoing = false ;
	logoff = false ;
	player = nullptr ;
}
//=========================================================
client_t::client_t(std::unique_ptr<socket_t> &socket) :client_t(){
	set(socket);
}
//=========================================================
auto client_t::set(std::unique_ptr<socket_t> &socket) ->client_t&{
	this->socket = std::move(socket) ;
	return *this ;
}

//=========================================================
auto client_t::name() const ->std::string {
	const auto [addr,port] = socket->peer() ;
	return addr.number() + ":"s + std::to_string(port) ;
}
//==========================================================
auto client_t::valid() const ->bool {
	auto rvalue = false ;
	if (socket != nullptr){
		rvalue = socket->valid();
	}
	return rvalue ;
}
