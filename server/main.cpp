//
// Copyright © 2022 Charles Kerr. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <filesystem>
#include <thread>
#include <algorithm>



using namespace std::string_literals ;
int main(int argc, const char * argv[]) {
	auto config_file  = std::filesystem::path("uox.cfg");
	if (argc > 1){
		config_file = std::filesystem::path(argv[1]) ;
	}
	
	return 0;
}
