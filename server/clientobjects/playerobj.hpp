//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef playerobj_hpp
#define playerobj_hpp

#include <cstdint>

#include "mobobj.hpp"
//=========================================================
struct playerobj_t : public mobobj_t {
	playerobj_t() ;
	virtual ~playerobj_t() ;

};
#endif /* playerobj_hpp */
