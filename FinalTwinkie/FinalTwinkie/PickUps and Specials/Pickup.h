#ifndef PICKUP_H
#define PICKUP_H
#include "../GameObjects/Entity.h"
#include "../GameObjects/Player.h"

enum PICKUPTYPE { PU_HEALTH, PU_AMMO, PU_ARMOR, PU_DD, PU_NORELOAD, PU_INVU, PU_INFAMMO, PU_MONEY };

class CPickup: public CEntity
{
public:
	virtual void Update(float);
	virtual void Render(void);
	virtual bool CheckCollision(IEntity* pBase);
	virtual int GetType(void) { return m_nType; }
	CPickup(void);
	~CPickup(void);

	void SetAliveTime(float fTimer) { m_fAliveTime = fTimer; }
	void SetGiven(int nGiven) {m_nGiven = nGiven;}
	void SetPickUpType(int nPickUpType) { m_nPickUpType = nPickUpType; }
	int GetPickUpType(void) {return m_nPickUpType;}

private:
	float m_fAliveTime;
	float m_fEndTime;
	int m_nGiven;
	int m_nPickUpType;
	
	CPlayer* m_pPlayer;
};
#endif