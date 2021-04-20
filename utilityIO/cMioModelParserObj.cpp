#include "cMioModelParserObj.h"
#include <string>
#include <sstream>
#include <iterator>
#include <memory>

MioModelParserObj::MioModelParserObj()
{
}

MioModelParserObj::~MioModelParserObj()
{
}

void MioModelParserObj::OnCleanUp()
{
}

bool MioModelParserObj::Parse(char* byteBuffer)
{
	std::string data(byteBuffer);
}

bool MioModelParserObj::ParseFromFile(wchar_t* fileName)
{
	if(m_fileReadStream != nullptr)
	{
		if(m_fileReadStream->is_open())
		{
			m_fileReadStream->close();
		}
		delete m_fileReadStream;
		m_fileReadStream = nullptr;
	}

	m_fileReadStream = new std::ifstream();
	m_fileReadStream->open(fileName);
	if(m_fileReadStream->good() == false)
	{
		// File not exist
		return false;
	}

	m_fileReadStream->seekg(0, m_fileReadStream->end);
	const size_t length = m_fileReadStream->tellg();
	m_fileReadStream->seekg(0, m_fileReadStream->beg);

	char* byteBuffer = (char*)malloc(length);
	m_fileReadStream->read(byteBuffer, length);

	m_fileReadStream->close();
	delete m_fileReadStream;
	m_fileReadStream->close();
	
	return Parse(byteBuffer);
}

bool MioModelParserObj::ParseFromBuffer(char* buffer)
{
	char* byteBuffer = buffer;
	
	return Parse(byteBuffer);
}

