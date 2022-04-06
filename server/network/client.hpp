//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef client_hpp
#define client_hpp

#include <cstdint>
#include "socket.hpp"
//=========================================================
struct client_t : public socket_t{
	client_t(descriptor_t descriptor = invalid_socket);
};
#endif /* client_hpp */
