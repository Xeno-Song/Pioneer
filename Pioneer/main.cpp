#include "SystemResource.h"

using namespace pioEngine;

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
	cSystemResource* systemResource = new cSystemResource();
	systemResource->Initialize();
	systemResource->Run();
	Sleep(5000);
	systemResource->Cleanup();
	return 0;
}