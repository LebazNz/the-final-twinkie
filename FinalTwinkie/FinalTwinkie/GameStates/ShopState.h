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

	void RenderPrices(int y2);
	void DetermineSelection();
	void SelectButtons();
	void ColorSelected();
	void Purchase();
	void SelectThis(bool * bRhs);
	void Clicked();
	void RenderStats();
	void RenderAchievements();
	float	GetHeat() const { return m_nHeat; }
	void	SetHeat(float val) { m_nHeat = val; }
	void	Highlight(DWORD* dwIndex);

	float	GetHeatUp() const { return m_fHeatUp; }
	void	SetHeatUp(float val) { m_fHeatUp = val; }
	float	GetDamUp() const { return m_fDamUp; }
	void	SetDamUp(float val) { m_fDamUp = val; }
	float	GetAmmoUp() const { return m_fAmmoUp; }
	void	SetAmmoUp(float val) { m_fAmmoUp = val; }
	float	GetHealthUp() const { return m_fHealthUp; }
	void	SetHealthUp(float val) { m_fHealthUp = val; }
	float	GetArmorUp() const { return m_fArmorUp; }
	void	SetArmorUp(float val) { m_fArmorUp = val; }
	float	GetSpeedUp() const { return m_fSpeedUp; }
	void	SetSpeedUp(float val) { m_fSpeedUp = val; }




private:
	CShopState(void);
	CShopState(const CShopState&);
	CShopState& operator=(const CShopState&);
	virtual ~CShopState(void);

	//Pointers
	CSGD_Direct3D*			m_pD3D;
	CSGD_DirectInput*		m_pDI;
	CSGD_TextureManager*	m_pTM;
	CBitmapFont*			m_pFont;
	CPlayer*				m_pPlayer;

	static CShopState*			m_pSelf;

	//Variables
	int m_nRocketPrice;
	int m_nLaserPrice;
	int m_nNukePrice;
	int m_nEMPPrice;
	int m_nArtilleryPrice;
	int m_nFlamerPrice;
	int m_nAirStrikePrice;
	int m_SmokeBombPrice;

	int m_nHeatPrice;
	int m_nAmmoPrice;
	int m_nDamagePrice;
	int m_nHealthPrice;
	int m_nArmorPrice;
	int m_nSpeedPrice;
	float m_fPriceIncrease;

	// Blah
	// Heat modifier
	float m_nHeat;
	
	// IDs
	int	m_nBGImageID;
	int m_nButtonImageID;
	int m_nCursor;
	// Positions
	int m_nMouseX;
	int m_nMouseY;

	int m_nIndex;

	int m_nItemCost;
	int m_nSelectedCost;
	// Button Colors
	DWORD m_dwRocket;
	DWORD m_dwLaser;
	DWORD m_dwNuke;
	DWORD m_dwEMP;
	DWORD m_dwArillery;
	DWORD m_dwFlamer;
	DWORD m_dwAirStrike;
	DWORD m_dwSmokeBomb;

	DWORD m_dwBuy;
	DWORD m_dwBack;

	// Grey Button Colors
	DWORD m_dwHeat;
	DWORD m_dwDamage;
	DWORD m_dwAmmo;
	DWORD m_dwHealth;
	DWORD m_dwArmor;
	DWORD m_dwSpeed;

	bool m_bRocket;
	bool m_bLaser;
	bool m_bNuke;
	bool m_bEMP;
	bool m_bArillery;
	bool m_bFlamer;
	bool m_bAirStrike;
	bool m_bSmokeBomb;
	bool m_bHeat;
	bool m_bDamage;
	bool m_bAmmo;
	bool m_bHealth;
	bool m_bArmor;
	bool m_bSpeed;

	bool m_bPurchase;
	float m_fHeatUp;
	float m_fDamUp;
	float m_fAmmoUp;
	float m_fHealthUp;
	float m_fArmorUp;
	float m_fSpeedUp;

	
};

#endif

