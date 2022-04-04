//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef mobobj_hpp
#define mobobj_hpp

#include <cstdint>
#include <string>

#include "baseobj.hpp"
//=========================================================
struct mobobj_t : public baseobj_t {
	
	mobobj_t() ;
	virtual ~mobobj_t() ;
	
	auto saveContents(std::ostream &output) ->void override;
	auto processWorldKey(const keyvalue_t &keyvalue,factory_t *factory) ->bool override;
	auto secondaryLoad(const keyvalue_t &keyvalue, factory_t *factory)->bool override;
	auto processServerKey(const keyvalue_t &keyvalue, factory_t *factory) ->bool override;
	
};

#endif /* mobob_hpp */
