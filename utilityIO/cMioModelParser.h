#pragma once

#ifndef __M_C_IO_PARSER_H__

#include <fstream>

// File Formats
// STL - https://en.wikipedia.org/wiki/STL_(file_format)
// OBJ - https://en.wikipedia.org/wiki/Wavefront_.obj_file

// Extension. mmod
struct MmodelFileFormat
{
	struct MmodelFileHeader
	{
		char magicNumber[4] = { 'D', 'O', 'M', 'M' };
		short fileVersion = 0;
		char modelName[32] = {0};
		int modelVertex;
	};

	MmodelFileHeader header;
	char* data;
};

struct MVertexData
{
	float x;	// Vertex X
	float y;	// Vertex Y
	float z;	// Vertex Z
	float tx;	// Texture X
	float ty;	// Texture Y
	float nx;	// Normal X
	float ny;	// Normal Y
	float nz;	// Normal Z
};

class MioModelParser
{
public:
	MioModelParser();
	virtual ~MioModelParser();

	void	Cleanup();	
	
	virtual bool	ParseFromFile(wchar_t* fileName) = 0;
	virtual bool	ParseFromBuffer(char* buffer) = 0;

private:
	virtual void OnCleanUp() = 0;

protected:
	std::ifstream*		m_fileReadStream;
	//char*				m_byteBuffer;
	MmodelFileFormat*m_vertexData;
};

#endif
