//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef playerobj_hpp
#define playerobj_hpp

#include <cstdint>

#include "mobobj.hpp"

class client_t ;
//=========================================================
struct playerobj_t : public mobobj_t {

	client_t *client ;


	playerobj_t() ;
	~playerobj_t() ;

};
#endif /* playerobj_hpp */
