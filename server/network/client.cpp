//Copyright © 2022 Charles Kerr. All rights reserved.

#include "client.hpp"

#include <iostream>

#include "ip4addr.hpp"
#include "strutil.hpp"

using namespace std::string_literals;
//=========================================================
client_t::client_t() {
	received_packet = false;
	log_incoming = false ;
	log_outgoing = false ;
}
//=========================================================
client_t::~client_t() {
	auto attempt = 10 ;
	while ((attempt>0) && socket->valid() && (outgoing.size()>0)){
		
	}
}
//=========================================================
auto client_t::name() const ->std::string {
	const auto [addr,port] = socket->peer() ;
	return addr.number() + ":"s + std::to_string(port) ;
}
