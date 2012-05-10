#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Turret.h"
#include "Emitter.h"

class CSpecial;
class CWeapon;

class CPlayer:public CEntity
{
public:
	virtual void Update(float);
	virtual void Render(void);
	virtual RECT GetRect(void);
	virtual bool CheckCollision(IEntity*);
	void Input(void);
	CPlayer(void);
	~CPlayer(void);
private:
	int m_nMoney;
	std::string m_szName;
	CSpecial* m_apSpec;
	std::vector<CWeapon*> m_vWeapon;
	int m_anWeaponAmmo[3];
	int m_anSpecialammo[2];
	CEmitter* m_pTracks;
	CTurret* m_pTurret;
};
#endif

