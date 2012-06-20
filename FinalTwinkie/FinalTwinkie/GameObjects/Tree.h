#ifndef CTREE_H_
#define CTREE_H_

#include "entity.h"
class CTree : public CEntity
{
private:
	bool m_bHit;
	int hitImageID;
	int m_nSound;
public:

	virtual bool CheckCollision(IEntity* pObject);
	virtual void Render(void);

	CTree(void);
	~CTree(void);

	void SetHit(bool h) { m_bHit = h;}
	bool GetHit(void) { return m_bHit;}
	void SetDestroyedImage(int h) { hitImageID = h;}
	void SetSound(int s) { m_nSound = s; }
	
};

#endif