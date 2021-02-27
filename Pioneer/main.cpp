#include "Engine/MEngine.h"
#include <Windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	MGetSystem()->InitEngine(hInstance);
	//MGetSystem()->StartEngine();
	MGetSystem()->GetWindowManager()->Destroy();
}