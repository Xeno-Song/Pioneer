#include "cMd3d11Model.h"

#ifdef __DX_VERSION_11__

Md3d11Model::Md3d11Model()
{
	m_vertexBuffer = nullptr;
	m_indexBuffer = nullptr;
	m_vertexCount = 0;
	m_indexCount = 0;
}

Md3d11Model::Md3d11Model(const Md3d11Model&)
{
}

Md3d11Model::~Md3d11Model()
{
	Cleanup();
}

bool Md3d11Model::Initialize(ID3D11Device* device, ModelFileType type, wchar_t* filePath)
{
	if (InitializeBuffers(device) == false) return false;

	return true;
}

bool Md3d11Model::Initialize(ID3D11Device* device, ModelFileType type, const char* modelData)
{
	if (InitializeBuffers(device) == false) return false;

	return true;
}

void Md3d11Model::Cleanup()
{
	CleanupBuffers();
}

void Md3d11Model::Render(ID3D11DeviceContext* deviceContext)
{
	RenderBuffers(deviceContext);
}

int Md3d11Model::GetIndexCount() const
{
	return m_indexCount;
}

bool Md3d11Model::InitializeBuffers(ID3D11Device* device, ModelFileType type, wchar_t* filePath, const char* modelData)
{
	if(modelData != nullptr)
	{
		if (lstrlenA(modelData) == 0)
			return false;
	}
	else if(filePath != nullptr)
	{
		if (lstrlenW(filePath) == 0)
			return false;

		
	}
}

bool Md3d11Model::InitializeBuffers(ID3D11Device* device)
{
	VertexType* verteices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	return true;
}

void Md3d11Model::CleanupBuffers()
{
	SAFE_RELEASE(m_vertexBuffer);
	SAFE_RELEASE(m_indexBuffer);

	m_vertexCount = 0;
	m_indexCount = 0;
}

void Md3d11Model::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
}

#endif