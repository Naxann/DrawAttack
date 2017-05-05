#include <iostream>
#include <cpp3ds/Graphics.hpp>
#include "DrawAttack.hpp"


bool isCIAVersion() {
	u64 id;
    APT_GetProgramID(&id);
	return (id == 0x0004000000771800);
}

int main(int argc, char** argv) {
//	Console::enable(TopScreen, cpp3ds::Color::Black); // Console for reading stdout
//	Console::enableBasic(TopScreen); // Console for reading stdout
	/*
	if (!Service::enable(Network))
		std::cout << "SERVICE FAILURE!" << std::endl;
	if (!Service::enable(Microphone))
		std::cout << "NO MIC!" << std::endl;
	*/

	cpp3ds::Service::enable(cpp3ds::Audio);
	cpp3ds::Service::enable(cpp3ds::Config);
	cpp3ds::Service::enable(cpp3ds::Network);
	cpp3ds::Service::enable(cpp3ds::SSL);
	cpp3ds::Service::enable(cpp3ds::Httpc);
	cpp3ds::Service::enable(cpp3ds::AM);

	if (isCIAVersion()) {
		cpp3ds::Service::enable(cpp3ds::Microphone);
	}



	srand(time(NULL));
	auto game = new DrawAttack::DrawAttack();
	DrawAttack::DrawAttack::isCIA = isCIAVersion();
	game->run();

	delete game;
	nimsExit();
	return 0;
}
