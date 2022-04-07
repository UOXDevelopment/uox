//Copyright © 2022 Charles Kerr. All rights reserved.

#include "serversock.hpp"
#include "client.hpp"

#include <iostream>

using namespace std::string_literals ;
//=========================================================
serversock_t::serversock_t(){
	log_incoming = false ;
	log_outgoing = false ;
}
//=========================================================
serversock_t::~serversock_t(){
	// we dont need to do anything?
}
