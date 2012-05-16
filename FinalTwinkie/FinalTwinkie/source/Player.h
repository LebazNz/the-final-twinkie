#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Turret.h"
#include "Emitter.h"
#include <vector>
#include "../SGD Wrappers/CSGD_DirectInput.h"
class CSpecial;
//class CWeapon;

class CPlayer:public CEntity
{
public:
	virtual void Update(float);
	virtual void Render(void);
	virtual RECT GetRect(void);
	virtual int GetType(void) { return m_nType; }
	virtual bool CheckCollision(IEntity*);
	void Input(void);
	CPlayer(void);
	~CPlayer(void);

	void SetTurret(CTurret* pTurret){m_pTurret=pTurret;}
	void SetRotation(float fRotate) {m_fRotation=fRotate;}
private:
	int m_nMoney;
	std::string m_szName;
	CSpecial* m_apSpec;
	//std::vector<CWeapon*> m_vWeapon;
	int m_anWeaponAmmo[3];
	int m_anSpecialammo[2];
	CEmitter* m_pTracks;
	CTurret* m_pTurret;
	float m_fRotation;
	float m_fRotationRate;

	CSGD_DirectInput* m_pDI;
};
#endif

