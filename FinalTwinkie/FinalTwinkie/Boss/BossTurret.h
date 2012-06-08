#pragma once
#include "../GameObjects/Entity.h"
#include "../GameObjects/Player.h"
enum TurretType{CANNON, MG1, MG2, RKT1, RKT2};
class CBossTurret :public CEntity
{
public:
	CBossTurret(void);
	virtual ~CBossTurret(void);
	virtual void Update(float fDt);
	virtual void Render(void);
	virtual int GetType(void) { return m_nType; }
	void UpdatePos(float PosX, float PosY);
	void UpdatePlatePos(float PosX, float PosY);
	void UpdateCannonRotation(float Rot) {m_fBossRot=Rot;}
	
	void SetTarget(CPlayer* p) {m_pTarget=p;}
	void SetTurretType(int nType){m_nTurretType=nType;}
	float GetRotation(void) {return m_fRotation;}
	float GetBossRotation(void) {return m_fBossRot;}
	float GetTotalRotation(void) {return m_fRotation+m_fBossRot;}
	void SetState(int State) {m_nState=State;}
	void SetFireRate(float fRate) {m_fFireRate=fRate;}
	

private:
	CPlayer* m_pTarget;
	float m_fRotation;
	int m_nTurretType;
	float m_fBossRot;
	int m_nState;
	float m_fFireRate;

	float PlatePosX;
	float PlatePosY;
};

