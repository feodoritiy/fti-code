#include <iostream>

#include <cpp_httplib/httplib.h>
using namespace httplib;
#include <json/json.hpp>
using json = nlohmann::json;

#include <HooksPage/HooksPage.h>
HooksPage webhooksPage("/webhooks-page.html", "/webhook-single.html");
//HooksPage webhooksPage;

Server server;
const int SERVER_PORT = 1234;

#include <rotes/root/root.h>
#include <rotes/webhooks/webhooks.h>

// MAIN

int main(int argc, char** argv)
{
	server
		.Post("/", RouteRoot::Handler)
		.Post("/webhooks", webhooksRoteHandler);

	//STARTING SERVER
	std::cout << "Server served on localhost:" << SERVER_PORT << "\n";
	server.listen("localhost", SERVER_PORT);

	return 0;
}
