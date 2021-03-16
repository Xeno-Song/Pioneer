#include "MObject.h"
#include "../../MEngine.h"
#include <math.h>

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
	m_collisionCheckEnable = enable;
}

bool MObject::GetCollisionCheckStatus()
{
	return m_collisionCheckEnable;
}

void MObject::SetCollisionArea(MRect size)
{
	MVector3 center = GetCenterOffset();

	m_collisionArea.left = size.left - center.x;
	m_collisionArea.right = center.x - size.right;
	m_collisionArea.top = size.top - center.y;
	m_collisionArea.bottom = center.y - size.bottom;

	// TODO. find the solution to optimize below codes.
	// This code need to calculate abs twice.
	int farX = (std::abs(m_collisionArea.left) > std::abs(m_collisionArea.right)) ? std::abs(m_collisionArea.left) : std::abs(m_collisionArea.right);
	int farY = (std::abs(m_collisionArea.top) > std::abs(m_collisionArea.bottom)) ? std::abs(m_collisionArea.top) : std::abs(m_collisionArea.bottom);

	m_collisionCircleRadius = sqrt(pow(farX, 2) + pow(farY, 2));
}

MRect MObject::GetCollisionArea()
{
	MVector3 center = GetCenterOffset();
	MRect rect = m_collisionArea;

	rect.left += center.x;
	rect.right += center.x;
	rect.top += center.y;
	rect.bottom += center.y;

	return rect;
}

MRect MObject::GetCollisionAreaRelativeCenter()
{
	return m_collisionArea;
}

double MObject::GetCollisionCircleRadius()
{
	return m_collisionCircleRadius;
}

void MObject::PreUpdate()
{
	OnPreUpdate();
}

void MObject::Update()
{
	OnUpdate();
}

void MObject::PostUpdate()
{
	OnPostUpdate();
}

void MObject::Render()
{
	
}

void MObject::Initialize(ResourceNumber::ImageResourceNumber imageNumber, MVector3 position, bool visible)
{
	m_uid = MGetObjectManager()->CreateNewUID();
	MGetObjectManager()->RegisterNewObject(this, m_uid);

	m_imageNumber = imageNumber;
	m_position = position;
	m_visible = visible;

	// TODO. Add image center calculation code
}
