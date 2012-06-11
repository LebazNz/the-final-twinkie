#pragma once

#include "Entity.h"

class CEMPBlast : public CEntity
{
public:
	CEMPBlast(void);
	virtual ~CEMPBlast(void);
	virtual void Update(float);
	virtual void Render(void);

private:
	int m_nEMPImageID;
	float m_fTimer;
	float m_fScale;
	int m_nOffsetX;
	int m_nOffsetY;
};

