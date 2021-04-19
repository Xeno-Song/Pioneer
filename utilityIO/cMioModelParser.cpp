#include "cMioModelParser.h"
#include "Mdefines.h"

MioModelParser::MioModelParser()
{
	m_fileReadStream = nullptr;
	m_byteBuffer = nullptr;
	m_vertexData = nullptr;
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

	if(m_vertexData != nullptr)
	{
		if(m_vertexData->data != nullptr)
		{
			delete[] m_vertexData->data;
			m_vertexData->data = nullptr;
		}

		delete m_vertexData;
		m_vertexData = nullptr;
	}
	SAFE_DELETE_ARR(m_byteBuffer);
}
