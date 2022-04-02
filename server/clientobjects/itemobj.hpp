//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef itemobj_hpp
#define itemobj_hpp

#include <cstdint>
#include <string>

#include "baseobj.hpp"
//=========================================================
struct itemobj_t : public baseobj_t {
	
	itemobj_t() ;
	virtual ~itemobj_t() ;
	
	auto saveContents(std::ostream &output) ->void override;
	auto processWorldKey(const keyvalue_t &keyvalue,factory_t *factory) ->bool override;
	auto secondaryLoad(const keyvalue_t &keyvalue, factory_t *factory)->bool override;
	auto processServerKey(const keyvalue_t &keyvalue, factory_t *factory) ->bool override;

};
#endif /* itemobj_hpp */
