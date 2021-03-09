#include "MObject.h"
#include "../../MEngine.h"

MObject::MObject()
{
	Initialize(ResourceNumber::IMG_NONE, MVector3(0, 0, 0), true);
}

MObject::MObject(ResourceNumber::ImageResourceNumber imageNumber, MVector3 position, bool visible)
{
	Initialize(imageNumber, position, visible);
}

MObject::~MObject()
{
}

void MObject::SetPosition(MVector3 size)
{
	m_position = size;
}

MVector3 MObject::GetPosition()
{
	return MVector3();
}

MVector3 MObject::GetImageSize()
{
	return MVector3();
}

MVector3 MObject::GetCenterOffset()
{
	return MVector3();
}

void MObject::SetCollisionCheckStatus(bool enable)
{
}

bool MObject::GetCollisionCheckStatus()
{
	return false;
}

void MObject::SetCollisionArea(MRect size)
{
}

MRect MObject::GetCollisionArea()
{
	return MRect();
}

double MObject::GetCollSphereDistance()
{
	return 0.0;
}

void MObject::PreUpdate()
{
}

void MObject::Update()
{
}

void MObject::PostUpdate()
{
}

void MObject::Render()
{
}

void MObject::Initialize(ResourceNumber::ImageResourceNumber imageNumber, MVector3 position, bool visible)
{
	m_uid = MObjGetManager()->CreateNewUID();
	MObjGetManager()->RegisterNewObject(this, m_uid);

	m_imageNumber = imageNumber;
	m_position = position;
	m_visible = visible;
}
