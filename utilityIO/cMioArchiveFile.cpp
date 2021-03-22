#include "cMioArchiveFile.h"
#include "pch.h"
#include <cctype>
#include <cstdarg>

cMioArchieFile_Stream::cMioArchieFile_Stream()
{
	m_fileName.clear();
	m_out.clear();
	m_in.clear();
	m_buffer.clear();
}

cMioArchieFile_Stream::cMioArchieFile_Stream(std::wstring _path)
{
	m_fileName.clear();
	m_out.clear();
	m_in.clear();
	m_buffer.clear();

	m_fileName.assign(_path);
}

cMioArchieFile_Stream::~cMioArchieFile_Stream()
{
	Cleanup();
}

void cMioArchieFile_Stream::Cleanup()
{
	if (m_out.is_open() == true)
		m_out.close();
	if (m_in.is_open() == true)
		m_in.clear();

	m_fileName.clear();
	m_out.clear();
	m_in.clear();
	m_buffer.clear();
}

void cMioArchieFile_Stream::SetFilePath(std::wstring _path)
{
	m_fileName.clear();
	m_fileName.assign(_path);
}

std::wstring cMioArchieFile_Stream::GetFilePath()
{
	return m_fileName;
}

bool cMioArchieFile_Stream::WriteStart()
{
	std::string	path;
	path.clear();
	path.assign(m_fileName.begin(), m_fileName.end());

	if (m_fileName.size() == 0)
	{
		return false;
	}

	m_out.open(m_fileName);
	m_buffer.clear();

	if (m_out.is_open() == false)
		return false;

	return true;
}

void cMioArchieFile_Stream::WriteText(const char * _data, ...)
{
	if (m_out.is_open() == false)
		return;

	int length = 0;
	char* buffer = nullptr;
	va_list argList;

	va_start(argList, _data);
	length = vsprintf_s(nullptr, NULL, _data, argList);

	buffer = (char*)malloc(sizeof(char) * length + 1);
	memset(buffer, 0, length + 1);

	vsprintf_s(buffer, length + 1, _data, argList);
	va_end(argList);

	//Encoding
	for (int i = 0; i < length; i++)
		buffer[i] ^= 0x5E;

	m_buffer.append(buffer);
}

void cMioArchieFile_Stream::WriteEnd()
{
	m_out.write(m_buffer.data(), m_buffer.length());

	m_out.close();
	m_out.clear();
}

bool cMioArchieFile_Stream::ReadStart()
{
	if (m_fileName.size() == 0)
	{
		return false;
	}

	char*	buffer = nullptr;
	std::string	path;
	path.clear();
	path.assign(m_fileName.begin(), m_fileName.end());

	m_in.open(path);
	m_in.seekg(0, m_in.end);
	size_t	textLength = m_in.tellg();
	m_in.seekg(0, m_in.beg);

	buffer = (char*)malloc(sizeof(char) * textLength + 1);
	memset(buffer, 0, textLength);

	m_in.read(buffer, textLength);
	m_buffer.assign(buffer);

	//Decoding
	for (auto i : m_buffer)
		i ^= 0x5E;

	m_in.close();
	m_in.clear();

	return true;
}

const std::string cMioArchieFile_Stream::ReadByte(unsigned int _length)
{
	std::string value;
	value.clear();
	value.assign(m_buffer.substr(0, _length));

	m_buffer = m_buffer.substr(_length + 1);

	return value;
}

void cMioArchieFile_Stream::ReadEnd()
{
	m_buffer.clear();
}

cMioArchiveFile_Header::cMioArchiveFile_Header()
{
	m_fileName.clear();
	m_startPont = 0;
	m_size = 0;
}

cMioArchiveFile_Header::~cMioArchiveFile_Header()
{
	m_fileName.clear();
	m_startPont = 0;
	m_size = 0;
}

void cMioArchiveFile_Header::SetFileName(std::wstring _fileName)
{
	m_fileName.assign(_fileName);
}

void cMioArchiveFile_Header::SetStartPoint(unsigned int _point)
{
	m_startPont = _point;
}

void cMioArchiveFile_Header::SetSize(unsigned int _size)
{
	m_size = _size;
}

std::wstring cMioArchiveFile_Header::GetFileName()
{
	return m_fileName;
}

unsigned int cMioArchiveFile_Header::GetStartPoint()
{
	return m_startPont;
}

unsigned int cMioArchiveFile_Header::GetSize()
{
	return m_size;
}

void cMioArchiveFile_Header::WriteFile(cMioArchieFile_Stream* _stream)
{
	int	fileNameLength;
	char buffer[8] = { 0 };

	fileNameLength = (int)m_fileName.length();
	memcpy(buffer, &fileNameLength, sizeof(unsigned int));
	_stream->WriteText(buffer);

	std::string fileName;
	fileName.clear();
	fileName.assign(m_fileName.begin(), m_fileName.end());
	_stream->WriteText(fileName.data());

	memset(buffer, 0, sizeof(buffer));
	memcpy(buffer, &m_startPont, sizeof(unsigned int));
	_stream->WriteText(buffer);

	memset(buffer, 0, sizeof(buffer));
	memcpy(buffer, &m_size, sizeof(unsigned int));
	_stream->WriteText(buffer);
}

void cMioArchiveFile_Header::ReadFile(cMioArchieFile_Stream* _stream)
{
	int fileNameLength;
	std::string buffer;
	buffer.clear();

	buffer = _stream->ReadByte(4);
	memcpy(&fileNameLength, buffer.data(), sizeof(unsigned int));
	
	buffer = _stream->ReadByte(fileNameLength);
	m_fileName.assign(buffer.begin(), buffer.end());

	buffer = _stream->ReadByte(4);
	memcpy(&m_startPont, buffer.data(), sizeof(unsigned int));

	buffer = _stream->ReadByte(4);
	memcpy(&m_size, buffer.data(), sizeof(unsigned int));
}

void cMioArchiveFile_FileData::WriteFile(cMioArchieFile_Stream* _stream, int _length)
{
}

void cMioArchiveFile_FileData::ReadFile()
{
}
