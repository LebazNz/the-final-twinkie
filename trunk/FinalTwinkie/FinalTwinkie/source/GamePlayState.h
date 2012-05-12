#ifndef CGAMEPLAYSTATE_H_
#define CGAMEPLAYSTATE_H_

#include "IGameState.h"
#include "ObjectFactory.h"

#include <string>

class CParticleManager;
class CObjectManager;
//class CObjectFactory;
class CEntity;
class CEmitter;
class CTileManager;
class CAnimationManager;
class CMessageSystem;

typedef CObjectFactory< std::string , CEntity> CFactory;

class CGamePlayState : public IGameState
{
public:
	static CGamePlayState* GetInstance(void);
	static void DeleteInstance(void);
	virtual void Enter(void);
	virtual void Exit(void);
	virtual bool Input(void);
	virtual void Update(float fDt);
	virtual void Render(void);
	

private:
	CGamePlayState(void);
	CGamePlayState(const CGamePlayState&);
	CGamePlayState& operator=(const CGamePlayState&);
	virtual ~CGamePlayState(void);

	CSGD_Direct3D*			m_pD3D;
	CSGD_DirectInput*		m_pDI;
	CSGD_TextureManager*	m_pTM;
	CBitmapFont*			m_pFont;
	CObjectManager*			m_pOM;
	CFactory*				m_pOF;
	CParticleManager*		m_PM;
	CMessageSystem*			m_pMS;
	CTileManager*			m_pTile;
	CAnimationManager*		m_AM;
	
	
	static CGamePlayState*	m_pSelf;

	vector<CEmitter*>		m_pEmitters;
	CEntity*				m_pPlayer;
	CEntity*				m_pEnemys[16];
	int m_anBulletImageIDs[4];
	int m_anEnemyIDs[16];
};

#endif
