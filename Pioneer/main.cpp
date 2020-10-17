#include "SystemResource.h"

using namespace pioEngine;

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
	cSystemResource* systemResource = new cSystemResource();
	systemResource->Initialize();
	Sleep(5000);
	systemResource->Shutdown();
	return 0;
}