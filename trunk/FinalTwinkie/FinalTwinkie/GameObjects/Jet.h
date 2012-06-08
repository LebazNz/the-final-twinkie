#pragma once

#include "Entity.h"
#include "../Particle/Emitter.h"

class CJet : public CEntity
{
public:
	CJet(void);
	virtual ~CJet(void);
	virtual void Update(float);
	virtual void Render(void);
	virtual int GetType(void) { return m_nType; }
	void SetTargetRect(RECT rTarget){m_rTarget = rTarget; }
	void SetTargetPos(tVector2D vPos);
	void DropBomb(void);

	void SetEmitter(CEmitter* Fire){m_pEmitter=Fire;}
	CEmitter* GetEmitter(void){return m_pEmitter;}

private:
	int m_nJetID;
	tVector2D m_vPos;
	RECT m_rTarget;
	bool m_bDropper;
	CEmitter* m_pEmitter;
};

