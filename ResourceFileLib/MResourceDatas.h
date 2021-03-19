#pragma once

#define DllExport   __declspec( dllexport )

class DllExport MResourceDatas
{
public:
	MResourceDatas();
	virtual ~MResourceDatas();

public:
	void Initialize();
	void Cleanup();

	void LoadDatas();
	void UnloadDatas();

private:
	cMioXmlSerializer* m_dataSerializer;
};