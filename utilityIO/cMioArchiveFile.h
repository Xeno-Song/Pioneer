#pragma once

#ifndef __M_IO_ARCHIVE_FILE_H__
#define __M_IO_ARCHIVE_FILE_H__

#include "DllExport.h"
#include <vector>
#include <fstream>

class MIO_API cMioArchieFile_Stream
{
protected:
	std::wstring	m_fileName;

	std::ofstream	m_out;
	std::ifstream	m_in;

	std::string		m_buffer;

public:
	cMioArchieFile_Stream();
	cMioArchieFile_Stream(std::wstring _path);
	virtual ~cMioArchieFile_Stream();

	void	Cleanup();

	void			SetFilePath(std::wstring _path);
	std::wstring	GetFilePath();

	bool	WriteStart();
	void	WriteText(const char* _data, ...);
	void	WriteEnd();

	bool				ReadStart();
	const std::string	ReadByte(unsigned int _length);
	void				ReadEnd();
};

class cMioArchiveFile_Header
{
private:
	std::wstring	m_fileName;
	unsigned int	m_startPont;
	unsigned int	m_size;
	
public:
	cMioArchiveFile_Header();
	virtual ~cMioArchiveFile_Header();

	void	SetFileName(std::wstring _fileName);
	void	SetStartPoint(unsigned int _point);
	void	SetSize(unsigned int _size);

	std::wstring	GetFileName();
	unsigned int	GetStartPoint();
	unsigned int	GetSize();

	void	WriteFile(cMioArchieFile_Stream* _stream);
	void	ReadFile(cMioArchieFile_Stream* _stream);
};

class cMioArchiveFile_FileData
{
private:
	char*	m_data;

public:


	void	WriteFile(cMioArchieFile_Stream* _stream, int _length);
	void	ReadFile();
};

class cMioArchiveFile
{

public:

};

#endif