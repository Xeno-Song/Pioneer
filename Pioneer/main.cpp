#include "MEngine.h"
#include "cMd3dDatas.h"
#include <Windows.h>


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	cMd3dDatas*	d3dDatas = nullptr;
	d3dDatas = new cMd3dDatas();

	d3dDatas->SaveAll();
}