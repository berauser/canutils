
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define VCAN0 "/sys/class/net/vcan0"

inline bool exists (const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

int main(int argc, char** argv) {
	// The following line must be executed to initialize Google Mock
	// (and Google Test) before running the tests.
	::testing::InitGoogleMock(&argc, argv);
	
	// check if vcan0 is up.
	// if vcan0 is not up, the tests will fail.
	if( ! exists( VCAN0 ) )
	{
		std::cout << std::endl;
		std::cout << "VCAN0 is not up!" << std::endl;
		std::cout << "Please enable VCAN0 for testing" << std::endl;
		std::cout << std::endl;
		std::cout << "  sudo ./scripts/vcan.sh start vcan0" << std::endl;
		std::cout << "  sudo ./scripts/vcan.sh up vcan0" << std::endl;
		std::cout << std::endl;
		return 1;
	}
	
	return RUN_ALL_TESTS();
}
