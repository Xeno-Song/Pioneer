#include "cMioModelParser.h"

MioModelParser::MioModelParser()
{
	m_fileReadStream = nullptr;
}

MioModelParser::MioModelParser(const MioModelParser&)
{
	m_fileReadStream = nullptr;
}

MioModelParser::~MioModelParser()
{
	Cleanup();
}

void MioModelParser::Cleanup()
{
	if (m_fileReadStream != nullptr &&
		m_fileReadStream->is_open() == true)
	{
		m_fileReadStream->close();
		m_fileReadStream->clear();

		delete m_fileReadStream;
		m_fileReadStream = nullptr;
	}
}
