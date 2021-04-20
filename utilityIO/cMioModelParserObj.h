#pragma once

#ifndef __C_M_IO_MODEL_PARSER_OBJ_H__
#define __C_M_IO_MODEL_PARSER_OBJ_H__

#include "DllExport.h"
#include "cMioModelParser.h"
#include <vector>

struct ObjFileVertex
{
	float x, y, z;
};

struct ObjFileTexture
{
	float tx, ty;
};

struct ObjFileNormal
{
	float nx, ny, nz;
};

struct ObjFileIndex
{
	bool isSquare = false;
	int _1, _2, _3, _4;
};

class MIO_API MioModelParserObj : public MioModelParser
{
public:
	MioModelParserObj();
	virtual ~MioModelParserObj();

	bool	ParseFromFile(wchar_t* fileName) override;
	bool	ParseFromBuffer(char* buffer) override;

private:
	void	OnCleanUp() override;
	bool	Parse(char* byteBuffer);
	
private:
	std::vector<ObjFileVertex>	m_vertexList;
	std::vector<ObjFileTexture>	m_textureList;
	std::vector<ObjFileNormal>	m_normalList;
	std::vector<ObjFileIndex>	m_indexList;
};

#endif