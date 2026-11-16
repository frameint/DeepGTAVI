/*
	THIS FILE IS A PART OF GTA VI SCRIPT HOOK SDK
*/

#include "lib/script.h"
#include "Server.h"

void ScriptMain()
{
	Server server(8000);
	while (true) {
		while (!server.clientConnected) {
			server.checkClient();
			scriptWait(1);
		}
		while (server.clientConnected) {
			server.checkRecvMessage();
			server.checkSendMessage();
			server.scenario.run();
		}
	}
}
