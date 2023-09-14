#include <iostream>
#include "screen.hpp"
#include "screen.cpp"

int main(){
	//Init window instance
	screen window;

	//Window loop
	while (window.running()){
		window.rungame();
	}

	//End of application
	return 0;
}