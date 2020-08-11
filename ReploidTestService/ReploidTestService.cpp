// ReploidTestService.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "rest_controller/controller.hpp"
#include "user_interrupt_handler.h"

int main(int argc, const char* argv[]) {
	reploid::InterruptHandler::hookSIGINT();

	reploid::Controller server;
    server.setEndpoint(_XPLATSTR("http://host_auto_ip4:6502/kaiser/api"));

    try {
        // wait for server initialization...
        server.accept().wait();
        std::cout << "Modern C++ Microservice now listening for requests at: " << utility::conversions::to_utf8string(server.endpoint()) << '\n';

        reploid::InterruptHandler::waitForUserInterrupt();

        server.shutdown().wait();
    }
    catch (std::exception& e) {
        std::cerr << "something wrong happen! :(" << '\n';
        std::cerr << e.what() << '\n';
    }
    catch (...) {
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
