#pragma once
#include <map>
#include <vector>
#include <fstream>

#ifndef __C_MIO_XML_SERIALIZER_H__
#define __C_MIO_XML_SERIALIZER_H__

#define _MIO_XML_SERIALIZER_MAX_STRING_LEN	256

class cMiolXml_Stream
{
protected:
	std::wstring		m_fileName;

	std::wofstream		m_outStream;
	std::wifstream		m_inStream;

	std::wstring		m_lastRead;
	std::wstring		m_buffer;

public:
	cMiolXml_Stream();
	cMiolXml_Stream(std::wstring	_fileName);
	virtual ~cMiolXml_Stream();

	void	Cleanup();

	void		SetTargetFilePath(std::wstring _fileName);
	std::string	GetTargetFileName();

	bool	WriteStart();
	void	WriteText(const wchar_t* _text, ...);
	void	WriteTabsByDepth(int _depth);
	void	WriteEnd();

	bool				ReadStart();
	const std::wstring	ReadToNextSyntaxOpen(bool _trim = true);
	const std::wstring	GetLastLine(bool _trim = true);
	void				ReadEnd();

private:
	std::wstring	TrimString(std::wstring _data);
};

class cMioXml_Attribute
{
protected:
	std::wstring m_tag;
	std::wstring m_value;

public:
	cMioXml_Attribute();
	virtual ~cMioXml_Attribute();

	void				SetTag(std::wstring _data);
	const std::wstring	GetTag();

	void	SetValue(std::wstring _data);
	void	SetValue(int _data);
	void	SetValue(double _data);

	const std::wstring	GetValueToString();
	int					GetValueToInt();
	double				GetValueToDouble();

	void	WriteXml(cMiolXml_Stream* _stream);
	void	ReadXml(std::wstring _data);
};

class cMioXml_SubElement
{
protected:
	std::wstring	m_tag;
	std::wstring	m_value;
	std::vector<cMioXml_Attribute*>	m_attributeNodes;

	int		m_depth;

public:
	cMioXml_SubElement(int _depth);
	virtual ~cMioXml_SubElement();

	void	Cleanup();

	void				SetTag(std::wstring _tag);
	const std::wstring	GetTag();

	cMioXml_Attribute*	CreateAttributeNode(std::wstring _tag);
	cMioXml_Attribute*	CreateAttributeNode(std::wstring _tag, std::wstring _value);
	cMioXml_Attribute*	CreateAttributeNode(std::wstring _tag, int _value);
	cMioXml_Attribute*	CreateAttributeNode(std::wstring _tag, double _value);
	cMioXml_Attribute*	GetAttributeNode(std::wstring _tag, bool _createIfNotFound = false);

	void	SetValue(std::wstring _value);
	void	SetValue(int _value);
	void	SetValue(double _value);

	const std::wstring	GetValueToString();
	int					GetValueToInt();
	double				GetValueToDouble();

	void	WriteXml(cMiolXml_Stream* _stream);
	void	ReadXml(cMiolXml_Stream* _stream);
};

class cMioXml_Element
{
protected:
	std::wstring	m_tag;

	std::vector<cMioXml_Attribute*>		m_attributeNodes;
	std::vector<cMioXml_Element*>		m_elementNodes;
	std::vector<cMioXml_SubElement*>	m_subElementNodes;

	int		m_depth;

public:
	cMioXml_Element(int _depth);
	virtual ~cMioXml_Element();

	void	Cleanup();

	void				SetTag(std::wstring _tag);
	const std::wstring	GetTag();

	cMioXml_Attribute*	CreateAttributeNode(std::wstring _tag);
	cMioXml_Attribute*	CreateAttributeNode(std::wstring _tag, std::wstring _value);
	cMioXml_Attribute*	CreateAttributeNode(std::wstring _tag, int _value);
	cMioXml_Attribute*	CreateAttributeNode(std::wstring _tag, double _value);
	cMioXml_Attribute*	GetAttributeNode(std::wstring _tag, bool _createIfNotFound = false);

	cMioXml_Element*	CreateElementNode(std::wstring _tag);
	cMioXml_Element*	GetElementNode(std::wstring _tag, bool _createIfNotFound = false);

	cMioXml_SubElement*	CreateSubElementNode(std::wstring _tag);
	cMioXml_SubElement*	CreateSubElementNode(std::wstring _tag, std::wstring _value);
	cMioXml_SubElement*	CreateSubElementNode(std::wstring _tag, int _value);
	cMioXml_SubElement*	CreateSubElementNode(std::wstring _tag, double _value);
	cMioXml_SubElement*	GetSubElementNode(std::wstring _tag, bool _createIfNotFound = false);

	void	WriteXml(cMiolXml_Stream* _stream);
	void	ReadXml(cMiolXml_Stream* _stream);
};

class cMioXmlSerializer
{
protected:
	cMiolXml_Stream*	m_stream;
	cMioXml_Element*	m_root;

public:
	cMioXmlSerializer();
	cMioXmlSerializer(std::wstring _fileName, std::wstring _tag);
	virtual ~cMioXmlSerializer();
	
	void	XmlInitialize(std::wstring _fileName, std::wstring _tag);
	void	XmlCleanup();
	void	XmlSetFilePath(std::wstring _path);

	void	XmlWrite();
	void	XmlRead();

	cMioXml_Element*	XmlGetRootElement();
};

#endif