#include "MEngine.h"
#include "cMioXmlSerializer.h"
#include <Windows.h>


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	cMioXmlSerializer* xmlSerializer = new cMioXmlSerializer(L"D:\\test.xml", L"root");

	//cMGeneralXml_Element* element = xmlSerializer->GetRootElement()->CreateElementNode(L"test");
	//cMGeneralXml_Attribute* attribute = element->CreateElementNode(L"TestElement")->CreateAttributeNode(L"attribute");
	//attribute->SetAttribute(10);

	//element->CreateSubElementNode(L"SubElement", L"Apple");

	xmlSerializer->ReadXml();
	xmlSerializer->SetFilePath(L"D:\\test1.xml");
	xmlSerializer->WriteXml();
}