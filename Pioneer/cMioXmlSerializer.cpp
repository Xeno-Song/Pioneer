#include "cMioXmlSerializer.h"
#include "Mdefines.h"
#include <algorithm>
#include <cctype>
#include <cstdarg>

cMioXmlSerializer::cMioXmlSerializer(std::wstring _fileName, std::wstring _tag)
{
	m_stream = new cMiolXml_Stream(_fileName);
	m_root = new cMioXml_Element(0);
	m_root->SetTag(_tag);
}

cMioXmlSerializer::~cMioXmlSerializer()
{
	Cleanup();
}

void cMioXmlSerializer::Cleanup()
{
	delete m_root;
	m_root = nullptr;
}

void cMioXmlSerializer::SetFilePath(std::wstring _path)
{
	m_stream->SetTargetFilePath(_path);
}

void cMioXmlSerializer::WriteXml()
{
	if (m_stream->WriteStart() == false)
	{
		return;
	}

	m_stream->WriteText(L"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	m_root->WriteXml(m_stream);
	m_stream->WriteEnd();
}

void cMioXmlSerializer::ReadXml()
{
	m_stream->ReadStart();
	m_stream->ReadToNextSyntaxOpen();
	m_stream->ReadToNextSyntaxOpen();

	m_root->ReadXml(m_stream);
	m_stream->ReadEnd();
}

cMioXml_Element * cMioXmlSerializer::GetRootElement()
{
	return m_root;
}



cMioXml_Attribute::cMioXml_Attribute()
{
	m_tag.clear();
	m_value.clear();
}

cMioXml_Attribute::~cMioXml_Attribute()
{
	m_tag.clear();
	m_value.clear();
}

void cMioXml_Attribute::SetTag(std::wstring _data)
{
	m_tag.assign(_data);
}

const std::wstring cMioXml_Attribute::GetTag()
{
	return m_tag;
}

void cMioXml_Attribute::SetValue(std::wstring _data)
{
	m_value = _data;
}

void cMioXml_Attribute::SetValue(int _data)
{
	wchar_t buffer[_MIO_XML_SERIALIZER_MAX_STRING_LEN] = { 0 };
	swprintf_s(buffer,
		_MIO_XML_SERIALIZER_MAX_STRING_LEN,
		L"%d",
		_data);

	m_value.clear();
	m_value.assign(buffer);
}

void cMioXml_Attribute::SetValue(double _data)
{
	wchar_t buffer[_MIO_XML_SERIALIZER_MAX_STRING_LEN] = { 0 };
	swprintf_s(buffer,
		_MIO_XML_SERIALIZER_MAX_STRING_LEN,
		L"%g",
		_data);

	m_value.clear();
	m_value.assign(buffer);
}

const std::wstring cMioXml_Attribute::GetValueToString()
{
	return m_value;
}

int cMioXml_Attribute::GetValueToInt()
{
	long attribute = 0;
	attribute = wcstol(m_value.data(), NULL, 10);

	return (int)attribute;
}

double cMioXml_Attribute::GetValueToDouble()
{
	double attribute = 0.0;
	attribute = wcstod(m_value.data(), NULL);

	return attribute;
}

void cMioXml_Attribute::WriteXml(cMiolXml_Stream * _stream)
{
	_stream->WriteText(L" %s=\"%s\"", m_tag.data(), m_value.data());
}

void cMioXml_Attribute::ReadXml(std::wstring _data)
{
	size_t	firstQuotationMarkPos = 0;
	size_t	secondQuotationMarkPos = 0;
	size_t	equalMarkPos = 0;

	equalMarkPos = _data.find_first_of(L'=');
	m_tag.assign(_data.substr(0, equalMarkPos));
	_data = _data.substr(equalMarkPos + 1);

	firstQuotationMarkPos = _data.find_first_of(L'\"');
	secondQuotationMarkPos = _data.find_last_of(L'\"');

	m_value.assign(_data.substr(firstQuotationMarkPos + 1, secondQuotationMarkPos - 1));
}





cMioXml_SubElement::cMioXml_SubElement(int _depth)
{
	m_depth = _depth;

	m_tag.clear();
	m_value.clear();
}

cMioXml_SubElement::~cMioXml_SubElement()
{
	Cleanup();
}

void cMioXml_SubElement::Cleanup()
{
	m_depth = 0;

	m_tag.clear();
	m_value.clear();
}

void cMioXml_SubElement::SetTag(std::wstring _tag)
{
	m_tag.clear();
	m_tag = _tag;
}

const std::wstring cMioXml_SubElement::GetTag()
{
	return m_tag;
}

cMioXml_Attribute * cMioXml_SubElement::CreateAttributeNode(std::wstring _tag)
{
	cMioXml_Attribute*	attribute = nullptr;

	attribute = GetAttributeNode(_tag);
	if (attribute != nullptr)
	{
		return attribute;
	}

	attribute = new cMioXml_Attribute();
	attribute->SetTag(_tag);

	m_attributeNodes.push_back(attribute);

	return attribute;
}

cMioXml_Attribute * cMioXml_SubElement::CreateAttributeNode(std::wstring _tag, std::wstring _value)
{
	cMioXml_Attribute*	attribute = nullptr;

	attribute = CreateAttributeNode(_tag);
	attribute->SetValue(_value);

	return attribute;
}

cMioXml_Attribute * cMioXml_SubElement::CreateAttributeNode(std::wstring _tag, int _value)
{
	cMioXml_Attribute*	attribute = nullptr;

	attribute = CreateAttributeNode(_tag);
	attribute->SetValue(_value);

	return attribute;
}

cMioXml_Attribute * cMioXml_SubElement::CreateAttributeNode(std::wstring _tag, double _value)
{
	cMioXml_Attribute*	attribute = nullptr;

	attribute = CreateAttributeNode(_tag);
	attribute->SetValue(_value);

	return attribute;
}

cMioXml_Attribute * cMioXml_SubElement::GetAttributeNode(std::wstring _tag, bool _createIfNotFound)
{
	cMioXml_Attribute*	findAttribute = nullptr;

	for (auto attribute : m_attributeNodes)
	{
		if (attribute->GetTag().compare(_tag.data()) == 0)
		{
			findAttribute = attribute;
			break;
		}
	}

	if (_createIfNotFound == true)
	{
		if (findAttribute == nullptr)
		{
			findAttribute = CreateAttributeNode(_tag);
		}
	}

	return findAttribute;
}

void cMioXml_SubElement::SetValue(std::wstring _value)
{
	m_value.clear();
	m_value.assign(_value);
}

void cMioXml_SubElement::SetValue(int _value)
{
	wchar_t buffer[_MIO_XML_SERIALIZER_MAX_STRING_LEN] = { 0 };
	swprintf_s(buffer,
		_MIO_XML_SERIALIZER_MAX_STRING_LEN,
		L"%d",
		_value);

	m_value.clear();
	m_value.assign(buffer);
}

void cMioXml_SubElement::SetValue(double _value)
{
	wchar_t buffer[_MIO_XML_SERIALIZER_MAX_STRING_LEN] = { 0 };
	swprintf_s(buffer,
		_MIO_XML_SERIALIZER_MAX_STRING_LEN,
		L"%g",
		_value);

	m_value.clear();
	m_value.assign(buffer);
}

const std::wstring cMioXml_SubElement::GetValueToString()
{
	return m_value;
}

int cMioXml_SubElement::GetValueToInt()
{
	long attribute = 0;
	attribute = wcstol(m_value.data(), NULL, 10);

	return (int)attribute;
}

double cMioXml_SubElement::GetValueToDouble()
{
	double attribute = 0.0;
	attribute = wcstod(m_value.data(), NULL);

	return attribute;
}

void cMioXml_SubElement::WriteXml(cMiolXml_Stream * _stream)
{
	_stream->WriteTabsByDepth(m_depth);
	_stream->WriteText(
		L"<%s>%s</%s>\n",
		m_tag.data(),
		m_value.data(),
		m_tag.data()
	);
}

void cMioXml_SubElement::ReadXml(cMiolXml_Stream * _stream)
{
	std::wstring	dataLine;
	std::wstring	dataTag;
	dataLine.clear();
	dataTag.clear();

	dataLine.assign(_stream->GetLastLine(false));

	size_t	syntaxStartPos = 0;
	size_t	syntaxEndPos = 0;
	syntaxStartPos = dataLine.find_first_of('<');
	syntaxEndPos = dataLine.find_first_of('>');

	dataTag.assign(dataLine.substr(syntaxStartPos + 1, syntaxEndPos - 1));
	m_value.assign(dataLine.substr(syntaxEndPos + 1));

	size_t	spaceCnt = 0;

	spaceCnt = std::count(dataLine.begin(), dataLine.end(), L' ');
	if (spaceCnt != 0)
	{
		cMioXml_Attribute*	attribute = nullptr;
		std::wstring attributeString;
		size_t	spacePos = 0;

		attributeString.assign(dataLine);
		spacePos = attributeString.find_first_of(L' ');
		m_tag.assign(attributeString.substr(0, spacePos));
		attributeString = attributeString.substr(spacePos);

		while (true)
		{
			spacePos = attributeString.find_first_of(L' ');
			if (spacePos == attributeString.npos)
			{
				spacePos = attributeString.find_last_of(L'\"');
				attribute = new cMioXml_Attribute();
				attribute->ReadXml(attributeString.substr(0, spacePos));
				m_attributeNodes.push_back(attribute);

				break;
			}
			else
			{
				attribute = new cMioXml_Attribute();
				attribute->ReadXml(attributeString.substr(0, spacePos));
				m_attributeNodes.push_back(attribute);

				attributeString = attributeString.substr(spacePos + 1);
			}
		}
	}
	else
	{
		size_t	syntaxClosePos = 0;
		syntaxClosePos = dataLine.find_first_of(L'>');
		m_tag.assign(dataLine.substr(0, syntaxClosePos));
	}

	dataLine.clear();
	dataTag.clear();

	dataTag.append(L"<");
	dataTag.append(m_tag);
	dataTag.append(L"/>");
}




cMioXml_Element::cMioXml_Element(int _depth)
{
	m_depth = _depth;

	m_tag.clear();
	m_attributeNodes.clear();
	m_elementNodes.clear();
}

cMioXml_Element::~cMioXml_Element()
{
	Cleanup();
}

void cMioXml_Element::Cleanup()
{
	m_tag.clear();
	SAFE_DELETE_VECTOR(m_attributeNodes);
	SAFE_DELETE_VECTOR(m_elementNodes);
}

void cMioXml_Element::SetTag(std::wstring _tag)
{
	//remove space in string
	_tag.erase(std::remove_if(_tag.begin(), _tag.end(), std::isspace), _tag.end());

	m_tag = _tag;
}

const std::wstring cMioXml_Element::GetTag()
{
	return m_tag;
}

cMioXml_Element * cMioXml_Element::CreateElementNode(std::wstring _tag)
{
	cMioXml_Element*	element = nullptr;
	
	element = GetElementNode(_tag);
	if (element != nullptr)
	{
		return element;
	}
	
	element = new cMioXml_Element(m_depth + 1);
	element->SetTag(_tag);

	m_elementNodes.push_back(element);

	return element;
}

cMioXml_Element * cMioXml_Element::GetElementNode(std::wstring _tag, bool _createIfNotFound)
{
	cMioXml_Element*	findElement = nullptr;

	for (auto element : m_elementNodes)
	{
		if (element->GetTag().compare(_tag.data()) == 0)
		{
			findElement = element;
			break;
		}
	}

	if (_createIfNotFound == true)
	{
		if (findElement == nullptr)
		{
			findElement = CreateElementNode(_tag);
		}
	}

	return findElement;
}

cMioXml_SubElement * cMioXml_Element::CreateSubElementNode(std::wstring _tag)
{
	cMioXml_SubElement*	subElement = nullptr;

	subElement = GetSubElementNode(_tag);
	if (subElement != nullptr)
	{
		return subElement;
	}

	subElement = new cMioXml_SubElement(m_depth + 1);
	subElement->SetTag(_tag);
	m_subElementNodes.push_back(subElement);

	return subElement;
}

cMioXml_SubElement * cMioXml_Element::CreateSubElementNode(std::wstring _tag, std::wstring _value)
{
	cMioXml_SubElement*	subElement = nullptr;

	subElement = CreateSubElementNode(_tag);
	subElement->SetValue(_value);

	return subElement;
}

cMioXml_SubElement * cMioXml_Element::CreateSubElementNode(std::wstring _tag, int _value)
{
	cMioXml_SubElement*	subElement = nullptr;

	subElement = CreateSubElementNode(_tag);
	subElement->SetValue(_value);

	return subElement;
}

cMioXml_SubElement * cMioXml_Element::CreateSubElementNode(std::wstring _tag, double _value)
{
	cMioXml_SubElement*	subElement = nullptr;

	subElement = CreateSubElementNode(_tag);
	subElement->SetValue(_value);

	return subElement;
}

cMioXml_SubElement * cMioXml_Element::GetSubElementNode(std::wstring _tag, bool _createIfNotFound)
{
	cMioXml_SubElement*	findSubElement = nullptr;

	for (auto subElement : m_subElementNodes)
	{
		if (subElement->GetTag().compare(_tag.data()) == 0)
		{
			findSubElement = subElement;
			break;
		}
	}

	if (_createIfNotFound == true)
	{
		if (findSubElement == nullptr)
		{
			findSubElement = CreateSubElementNode(_tag);
		}
	}

	return findSubElement;
}

cMioXml_Attribute * cMioXml_Element::CreateAttributeNode(std::wstring _tag)
{
	cMioXml_Attribute*	attribute = nullptr;

	attribute = GetAttributeNode(_tag);
	if (attribute != nullptr)
	{
		return attribute;
	}

	attribute = new cMioXml_Attribute();
	attribute->SetTag(_tag);

	m_attributeNodes.push_back(attribute);

	return attribute;
}

cMioXml_Attribute * cMioXml_Element::CreateAttributeNode(std::wstring _tag, std::wstring _value)
{
	cMioXml_Attribute*	attribute = nullptr;
	
	attribute = CreateAttributeNode(_tag);
	attribute->SetValue(_value);

	return attribute;
}

cMioXml_Attribute * cMioXml_Element::CreateAttributeNode(std::wstring _tag, int _value)
{
	cMioXml_Attribute*	attribute = nullptr;

	attribute = CreateAttributeNode(_tag);
	attribute->SetValue(_value);

	return attribute;
}

cMioXml_Attribute * cMioXml_Element::CreateAttributeNode(std::wstring _tag, double _value)
{
	cMioXml_Attribute*	attribute = nullptr;

	attribute = CreateAttributeNode(_tag);
	attribute->SetValue(_value);

	return attribute;
}

cMioXml_Attribute * cMioXml_Element::GetAttributeNode(std::wstring _tag, bool _createIfNotFound)
{
	cMioXml_Attribute*	findAttribute = nullptr;

	for (auto attribute : m_attributeNodes)
	{
		if (attribute->GetTag().compare(_tag.data()) == 0)
		{
			findAttribute = attribute;
			break;
		}
	}

	if (_createIfNotFound == true)
	{
		if (findAttribute == nullptr)
		{
			findAttribute = CreateAttributeNode(_tag);
		}
	}

	return findAttribute;
}

void cMioXml_Element::WriteXml(cMiolXml_Stream* _stream)
{
	_stream->WriteTabsByDepth(m_depth);
	_stream->WriteText(L"<%s", m_tag.data());

	if (m_attributeNodes.size() != 0)
	{
		for (auto node : m_attributeNodes)
		{
			node->WriteXml(_stream);
		}
	}
	_stream->WriteText(L">\n");

	if(m_elementNodes.size() != 0)
	{
		for (auto node : m_elementNodes)
		{
			node->WriteXml(_stream);
		}
	}

	if (m_subElementNodes.size() != 0)
	{
		for (auto node : m_subElementNodes)
		{
			node->WriteXml(_stream);
		}
	}

	_stream->WriteTabsByDepth(m_depth);
	_stream->WriteText(L"</%s>\n", m_tag.data());
}

void cMioXml_Element::ReadXml(cMiolXml_Stream* _stream)
{
	std::wstring dataLine;
	dataLine.clear();

	dataLine.assign(_stream->GetLastLine());
	dataLine = dataLine.substr(1);

	size_t	spaceCnt = 0;

	spaceCnt = std::count(dataLine.begin(), dataLine.end(), L' ');
	if (spaceCnt != 0)
	{
		cMioXml_Attribute*	attribute = nullptr;
		std::wstring attributeString;
		size_t	spacePos = 0;

		attributeString.assign(dataLine);
		spacePos = attributeString.find_first_of(L' ');
		m_tag.assign(attributeString.substr(0, spacePos));
		attributeString = attributeString.substr(spacePos + 1);

		while (true)
		{
			spacePos = attributeString.find_first_of(L' ');
			if (spacePos == attributeString.npos)
			{
				spacePos = attributeString.find_last_of(L'\"');
				attribute = new cMioXml_Attribute();
				attribute->ReadXml(attributeString.substr(0, spacePos + 1));
				m_attributeNodes.push_back(attribute);

				break;
			}
			else
			{
				attribute = new cMioXml_Attribute();
				attribute->ReadXml(attributeString.substr(0, spacePos));
				m_attributeNodes.push_back(attribute);

				attributeString = attributeString.substr(spacePos + 1);
			}
		}
	}
	else
	{
		size_t	syntaxClosePos = 0;
		syntaxClosePos = dataLine.find_first_of(L'>');
		m_tag.assign(dataLine.substr(0, syntaxClosePos));
	}
	
	size_t	syntaxClosePos = 0;
	size_t	syntaxEndPos = 0;

	while (true)
	{
		dataLine.clear();
		dataLine.assign(_stream->ReadToNextSyntaxOpen());
		syntaxClosePos = dataLine.find_first_of(L'>');
		syntaxEndPos = dataLine.find_first_of(L'/');

		if (syntaxEndPos != dataLine.npos)
		{
			break;
		}

		if (syntaxClosePos != dataLine.length())
		{
			cMioXml_Element*	element = nullptr;
			element = new cMioXml_Element(m_depth + 1);
			element->ReadXml(_stream);
			m_elementNodes.push_back(element);
		}
		else
		{
			cMioXml_SubElement*	subElement = nullptr;
			subElement = new cMioXml_SubElement(m_depth + 1);
			subElement->ReadXml(_stream);
			m_subElementNodes.push_back(subElement);
		}
	}

	//size_t	leftTrimPos = 0;
	//std::wstring lastLine = { 0 };
	//lastLine.assign(_stream->GetLastLine());
	//leftTrimPos = lastLine.find_first_not_of(L'\t');

	//if (leftTrimPos == lastLine.npos)
	//{
	//	//TODO. exception process like error return
	//}
	//lastLine = lastLine.substr(leftTrimPos);

	//size_t	spaceCnt = 0;

	//spaceCnt = std::count(lastLine.begin(), lastLine.end(), L' ');
	//if (spaceCnt != 0)
	//{
	//	cMGeneralXml_Attribute*	attribute = nullptr;
	//	std::wstring attributeString;
	//	size_t	spacePos = 0;

	//	attributeString.assign(lastLine);
	//	spacePos = attributeString.find_first_of(L' ');
	//	attributeString = attributeString.substr(spacePos);

	//	while (true)
	//	{
	//		spacePos = attributeString.find_first_of(L' ');
	//		if (spacePos == attributeString.npos)
	//		{
	//			spacePos = attributeString.find_last_of(L'\"');
	//			attribute = new cMGeneralXml_Attribute();
	//			attribute->ReadXml(attributeString.substr(0, spacePos));
	//			m_attributeNodes.push_back(attribute);

	//			break;
	//		}
	//		else
	//		{
	//			attribute = new cMGeneralXml_Attribute();
	//			attribute->ReadXml(attributeString.substr(0, spacePos));
	//			m_attributeNodes.push_back(attribute);

	//			attributeString = attributeString.substr(spacePos + 1);
	//		}
	//	}
	//}

	//lastLine.assign(_stream->ReadLine());

	//size_t	closeSyntaxCnt = 0;
	//size_t	endSyntaxCnt = 0;
	//closeSyntaxCnt = std::count(lastLine.begin(), lastLine.end(), L'>');
	//endSyntaxCnt = std::count(lastLine.begin(), lastLine.end(), L'/');

	//if (closeSyntaxCnt == 1 && endSyntaxCnt == 1)
	//{

	//}
	//else if(endSyntaxCnt == 1)
}

cMiolXml_Stream::cMiolXml_Stream()
{
	m_fileName.clear();
	m_outStream.clear();
	m_inStream.clear();
}

cMiolXml_Stream::cMiolXml_Stream(std::wstring _fileName)
{
	m_fileName.clear();
	m_outStream.clear();
	m_inStream.clear();

	m_fileName.assign(_fileName);
}

cMiolXml_Stream::~cMiolXml_Stream()
{
	Cleanup();
}

void cMiolXml_Stream::Cleanup()
{
	m_fileName.clear();
	m_outStream.clear();
	m_inStream.clear();
}

void cMiolXml_Stream::SetTargetFilePath(std::wstring _fileName)
{
	m_fileName = _fileName;
}

std::string cMiolXml_Stream::GetTargetFileName()
{
	return std::string();
}

bool cMiolXml_Stream::WriteStart()
{
	if (m_fileName.size() == 0)
	{
		return false;
	}

	m_outStream.open(m_fileName);
	m_buffer.clear();

	return true;
}

void cMiolXml_Stream::WriteText(const wchar_t * _format, ...)
{
	wchar_t buffer[_MIO_XML_SERIALIZER_MAX_STRING_LEN];
	if (m_outStream.is_open() == false)	return;

	va_list argList;
	va_start(argList, _format);
	vswprintf_s(buffer,
		_MIO_XML_SERIALIZER_MAX_STRING_LEN,
		_format,
		argList);
	va_end(argList);

	size_t length = wcslen(buffer);
	m_buffer.append(buffer);
}

void cMiolXml_Stream::WriteTabsByDepth(int _depth)
{
	if (_depth == 0)	return;

	wchar_t* buffer = nullptr;
	buffer = (wchar_t*)malloc(sizeof(wchar_t) * (_depth + 1));
	wmemset(buffer, L'\t', _depth);
	buffer[_depth] = L'\0';

	WriteText(buffer);
	delete[] buffer;
}

void cMiolXml_Stream::WriteEnd()
{
	if (m_outStream.is_open() == true)
	{
		m_outStream.write(m_buffer.data(), m_buffer.length());
		m_outStream.close();
	}

	m_outStream.clear();
}

bool cMiolXml_Stream::ReadStart()
{
	if (m_fileName.size() == 0)
	{
		return false;
	}

	wchar_t*	buffer = nullptr;

	m_inStream.open(m_fileName);
	m_inStream.seekg(0, m_inStream.end);
	size_t	textLength = m_inStream.tellg();
	m_inStream.seekg(0, m_inStream.beg);

	buffer = (wchar_t*)malloc(sizeof(wchar_t) * textLength);
	wmemset(buffer, 0, textLength);

	m_inStream.read(buffer, textLength);
	m_buffer.assign(buffer);

	m_inStream.close();
	m_inStream.clear();

	return true;
}

const std::wstring cMiolXml_Stream::ReadToNextSyntaxOpen(bool _trim)
{
	if (m_buffer.size() == 0)	return std::wstring();

	size_t	nextOpenSyntaxPos = 0;
	nextOpenSyntaxPos = m_buffer.substr(1).find_first_of('<');

	m_lastRead.clear();
	if (nextOpenSyntaxPos == m_buffer.npos)
	{
		m_lastRead.assign(m_buffer);
		m_buffer.clear();
	}
	else
	{
		m_lastRead.assign(m_buffer.substr(0, nextOpenSyntaxPos + 1));
		m_buffer = m_buffer.substr(nextOpenSyntaxPos + 1);
	}

	if (_trim == true)
	{
		return TrimString(m_lastRead);
	}

	return m_lastRead;
}

const std::wstring cMiolXml_Stream::GetLastLine(bool _trim)
{
	if (_trim == true)
	{
		return TrimString(m_lastRead);
	}

	return m_lastRead;
}

void cMiolXml_Stream::ReadEnd()
{
	m_buffer.clear();
}

std::wstring cMiolXml_Stream::TrimString(std::wstring _data)
{
	std::wstring	temp;
	size_t			trimPos = 0;
	temp.clear();
	temp.assign(_data);

	trimPos = temp.find_first_not_of(L'\t');
	if (trimPos != temp.npos)
	{
		temp = temp.substr(trimPos);
	}

	trimPos = temp.find_first_of(L'\t');
	if (trimPos != temp.npos)
	{
		temp = temp.substr(0, trimPos);
	}

	trimPos = temp.find_first_of(L'\n');
	if (trimPos != temp.npos)
	{
		temp = temp.substr(0, trimPos);
	}

	return temp;
}
