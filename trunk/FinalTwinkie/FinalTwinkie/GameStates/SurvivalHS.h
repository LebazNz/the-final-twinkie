#pragma once
#include "IGameState.h"

#include "../ObjectManager and Factory/ObjectFactory.h"
#include "../Event and Messages/Message.h"
#include "../GameObjects/Player.h"
#include "../tinyxml/tinyxml.h"
#include "../source/PlayerScores.h"
class CSurvivalHS :
	public IGameState
{
public:
	static CSurvivalHS* GetInstance();
	static void DeleteInstance(void);
	virtual void Enter(void);		
	virtual void Exit(void);		

	virtual bool Input(void);
	virtual void Update(float fElapsedTime);
	virtual void Render(void);
	virtual void Transition();

	void GeneratePlayers();
	void SwapPlayers();
	bool LoadPlayers(const char* szFileName);
	void SavePlayers(const char* szFileName);

	vector<PlayerScores> m_vScore;
	
	int		m_nBackgroundID;
	static CSurvivalHS*	m_pSelf;
	// Singleton
	CSurvivalHS(void);
	// Copy
	CSurvivalHS(const CSurvivalHS&);
	// Assignment
	CSurvivalHS* operator=(const CSurvivalHS&);
	// Destructor
	virtual ~CSurvivalHS(void);

	// SGD Wrappers
	CSGD_Direct3D*			m_pD3D;
	CSGD_DirectInput*		m_pDI;
	CSGD_TextureManager*	m_pTM;

	CBitmapFont*			m_pFM;
};

