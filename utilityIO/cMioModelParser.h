#pragma once

#ifndef __M_C_IO_PARSER_H__

#include <fstream>

// File Formats
// STL - https://en.wikipedia.org/wiki/STL_(file_format)
// OBJ - https://en.wikipedia.org/wiki/Wavefront_.obj_file

struct IndexData
{
	struct IndeciedVertexData
	{
		int position;
		int normal;
		int texture;
	};
};



//class MIO_API MioModelParser
//{
//public:
//	MioModelParser();
//	MioModelParser(const MioModelParser&);
//	virtual ~MioModelParser();
//
//	void	Cleanup();
//	
//	virtual bool	ParseFromFile(wchar_t* fileName) = 0;
//	virtual bool	ParseFromBuffer(char* buffer) = 0;
//
//private:
//	std::ifstream*	m_fileReadStream;
//	D3DXVECTOR3*	m_vertexDatas;
//};

#endif
