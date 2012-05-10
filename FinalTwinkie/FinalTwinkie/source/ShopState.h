#ifndef CSHOPSTATE_H_
#define CSHOPSTATE_H_

#include "IGameState.h"
class CPlayer;

class CShopState : public IGameState
{
public:
	static CShopState* GetInstance(void);
	static void DeleteInstance(void);
	virtual void Enter(void);
	virtual void Exit(void);
	virtual bool Input(void);
	virtual void Update(float fDt);
	virtual void Render(void);
	

private:
	CShopState(void);
	CShopState(const CShopState&);
	CShopState& operator=(const CShopState&);
	virtual ~CShopState(void);

	//Pointers
	CSGD_DirectInput*		m_pDI;
	CSGD_TextureManager*	m_pTM;
	CBitmapFont*			m_pFont;
	CPlayer*				m_pPlayer;

	static CShopState*			m_pSelf;

	//Variables
	int m_anWeaponPrices[3];
	int m_anSpecialPrices[3];
	int m_anUpgradesPrices[4];
	int m_anWeaponImageIDs[3];
	int m_anSpecialImageIDs[3];
	int m_anUpgradeImageIDs[4];
	int m_nUpgradedImageID;
	int m_nNotUpgradedImagedID;
	float m_fPriceIncrease;



};

#endif

