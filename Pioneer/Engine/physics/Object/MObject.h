#pragma once

#ifndef __M_OBJECT_H__
#define __M_OBJECT_H__

#include "../../util/math/Mmath.h"
#include "../../ResourceList.h"
#include "../../Mtypes.h"

class MObject
{
// Constructor
public:
	MObject();
	MObject(ResourceNumber::ImageResourceNumber imageNumber, MVector3 position, bool visible = true);
	virtual ~MObject();

public:	
	void SetPosition(MVector3 size);
	MVector3 GetPosition();
	MVector3 GetImageSize();
	MVector3 GetCenterOffset();

	void SetCollisionCheckStatus(bool enable);
	bool GetCollisionCheckStatus();
	// Left top is (0, 0)
	void SetCollisionArea(MRect size);
	MRect GetCollisionArea();
	MRect GetCollisionAreaRelativeCenter();
	double GetCollisionCircleRadius();


public:
	void PreUpdate();
	void Update();
	void PostUpdate();

	void Render();

protected:
	virtual void OnPreUpdate() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnPostUpdate() = 0;
	
private:
	void Initialize(ResourceNumber::ImageResourceNumber imageNumber, MVector3 position, bool visible);

private:
	UID			m_uid;

	ResourceNumber::ImageResourceNumber	m_imageNumber;
	bool		m_visible;

	MVector3	m_position;
	MVector3	m_centerOffset;
	MVector3	m_size;

	bool		m_collisionCheckEnable;
	MRect		m_collisionArea;
	double		m_collisionCircleRadius;
};

#endif