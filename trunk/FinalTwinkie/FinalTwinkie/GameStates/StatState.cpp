#include "StatState.h"
#include "OptionsState.h"
#include "../Headers/Game.h"
#include "MainMenuState.h"
#include "GamePlayState.h"
#include "../GameObjects/Player.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"
#include "../tinyxml/tinystr.h"
#include "../tinyxml/tinyxml.h"

StatState* StatState::m_pSelf = nullptr;

StatState::StatState(void)
{
	m_pDI = nullptr;
	m_pD3D = nullptr;
	m_pTM = nullptr;
	m_pFont = nullptr;
	m_bStats = true;
}

StatState::~StatState(void)
{
}

StatState* StatState::GetInstance( void )
{
	if(m_pSelf == nullptr)
		m_pSelf = new StatState;
	return m_pSelf;
}

void StatState::DeleteInstance( void )
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}

void StatState::Enter( void )
{
	m_pD3D = CSGD_Direct3D::GetInstance();
	m_pDI = CSGD_DirectInput::GetInstance();
	m_pTM = CSGD_TextureManager::GetInstance();
	m_pFont = CBitmapFont::GetInstance();
	m_pPlayer = CPlayer::GetInstance();
	m_nBGImageID = m_pTM->LoadTexture(_T("resource/graphics/bg_loadMenu_&_sprites.png"),D3DCOLOR_XRGB(255,255,255));
	m_nButtonImageID = m_pTM->LoadTexture(_T("resource/graphics/Button.png"));
	m_nCursor = m_pTM->LoadTexture(_T("resource/graphics/cursor.png"),0);

	m_nButton = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("resource/sound/button.wav"));
	m_nClick = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("resource/sound/click.wav"));
	m_nPos=0;
	LoadText();
}

void StatState::Exit( void )
{
	m_pDI	= nullptr;
	m_pD3D	= nullptr;
	m_pTM	= nullptr;
	m_pFont = nullptr;

//	m_pTM->UnloadTexture(m_nBGImageID);
}

bool StatState::Input( void )
{
	if(ARCADE == 0)
	{
		if(m_pDI->KeyPressed(DIK_ESCAPE) || m_pDI->JoystickButtonPressed(1))
		{
			CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
			return true;
		}

		if(m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0))
		{
			Clicked();
		}
	}
	else
	{
		if(m_pDI->JoystickButtonPressed(1) || m_pDI->JoystickButtonPressed(6))
		{
			CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
			return true;
		}

		if(m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0))
		{
			Clicked();
		}
	}

	return true;
}

void StatState::Update( float fDt )
{
	SelectButtons();
}

void StatState::Render( void )
{
	m_pFont->Init(COptionsState::GetInstance()->GetLang());
	RECT rSelf = { };
	SetRect(&rSelf, 0, 0, 800, 600);
	m_pTM->Draw(m_nBGImageID,0,0,1.0f,1.0f,&rSelf,0,0,0);

	if(m_bStats)
		RenderStats();
	else
		RenderAchievements();

	m_pTM->Draw(m_nButtonImageID,0,CGame::GetInstance()->GetHeight()-40,0.75f,0.75f,nullptr,0,0,0,m_dwBack);
	m_pFont->Print("Stats",40,CGame::GetInstance()->GetHeight()-30,0.75f,D3DCOLOR_ARGB(255,255,255,255));
	m_pTM->Draw(m_nButtonImageID,CGame::GetInstance()->GetWidth()-m_pTM->GetTextureWidth(m_nButtonImageID)+85,CGame::GetInstance()->GetHeight()-40,0.75f,0.75f,nullptr,0,0,0,m_dwNext);
	
	m_pFont->Print("Achievements",CGame::GetInstance()->GetWidth()-m_pTM->GetTextureWidth(m_nButtonImageID)+110,CGame::GetInstance()->GetHeight()-30,0.75f,D3DCOLOR_ARGB(255,255,255,255));
	m_pFont->Print("Press esc to exit",(int)(CGame::GetInstance()->GetWidth()/2-100),CGame::GetInstance()->GetHeight()-30,0.75f,D3DCOLOR_ARGB(255,255,255,255));

	/*char buffer[10];
	_itoa_s(m_pDI->MouseGetPosX(),buffer,10);
	m_pFont->Print(buffer,600,25,0.75f,D3DCOLOR_XRGB(255,255,255));
	_itoa_s(m_pDI->MouseGetPosX()-16,buffer,10);
	m_pFont->Print(buffer,600,50,0.75f,D3DCOLOR_XRGB(255,255,255));
	_itoa_s(m_pDI->MouseGetPosY(),buffer,10);
	m_pFont->Print(buffer,700,25,0.75f,D3DCOLOR_XRGB(255,255,255));
	_itoa_s(m_pDI->MouseGetPosY()-16,buffer,10);
	m_pFont->Print(buffer,700,50,0.75f,D3DCOLOR_XRGB(255,255,255));*/

	m_dwNaziBoss = D3DCOLOR_XRGB(140,140,140);	
	m_dwAlienBoss = D3DCOLOR_XRGB(140,140,140);	
	m_dwRobotBoss = D3DCOLOR_XRGB(140,140,140);
	m_dwSparta = D3DCOLOR_XRGB(140,140,140);
	m_dwSapperAbsorb = D3DCOLOR_XRGB(140,140,140);
	m_dwNukem = D3DCOLOR_XRGB(140,140,140);
	m_dwIamBoss = D3DCOLOR_XRGB(140,140,140);
	m_dwAllUpgrades = D3DCOLOR_XRGB(140,140,140);


	if(CPlayer::GetInstance()->GetNaziBoss())
		m_dwNaziBoss = D3DCOLOR_XRGB(255,255,255);
	if(CPlayer::GetInstance()->GetAlienBoss())
		m_dwAlienBoss = D3DCOLOR_XRGB(255,255,255);
	if(CPlayer::GetInstance()->GetRobotBoss())
		m_dwRobotBoss = D3DCOLOR_XRGB(255,255,255);
	if(CPlayer::GetInstance()->GetSparta())
		m_dwSparta = D3DCOLOR_XRGB(255,255,255);
	if(CPlayer::GetInstance()->GetSapperAbsorb())
		m_dwSapperAbsorb = D3DCOLOR_XRGB(255,255,255);
	if(CPlayer::GetInstance()->GetNukem())
		m_dwNukem = D3DCOLOR_XRGB(255,255,255);
	if(CPlayer::GetInstance()->GetIamBoss())
		m_dwIamBoss = D3DCOLOR_XRGB(255,255,255);
	if(CPlayer::GetInstance()->GetAllUpgrades())	
		m_dwAllUpgrades = D3DCOLOR_XRGB(255,255,255);

	m_pTM->Draw(m_nCursor, m_pDI->MouseGetPosX()-16, m_pDI->MouseGetPosY()-16, 1.0f, 1.0f);
}

void StatState::Highlight( DWORD* dwIndex )
{
	m_dwBack		 = D3DCOLOR_ARGB(255,255,255,255);
	m_dwNext		 = D3DCOLOR_ARGB(255,255,255,255);
	
	if( dwIndex != nullptr)
		*dwIndex = D3DCOLOR_XRGB(177,132,0);
}

void StatState::SelectButtons()
{
	int m_nMouseX = m_pDI->MouseGetPosX();
	int m_nMouseY = m_pDI->MouseGetPosY();
	int nButtonWidth = 175;
	int nButtonHeight = 45;
	if(m_nMouseX >= 0 && m_nMouseX <= 0 + nButtonWidth
		&& m_nMouseY >= CGame::GetInstance()->GetHeight()-40 && m_nMouseY <= CGame::GetInstance()->GetHeight()-40 + nButtonHeight)
	{
		// Buy
		if(m_nPos!=1)
			CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nButton,false);
		Highlight(&m_dwBack);
		m_nPos=1;
	}
	else if(m_nMouseX >= CGame::GetInstance()->GetWidth()-m_pTM->GetTextureWidth(m_nButtonImageID)+80 && m_nMouseX <= CGame::GetInstance()->GetWidth()-m_pTM->GetTextureWidth(m_nButtonImageID)+80 + nButtonWidth
		&& m_nMouseY >= CGame::GetInstance()->GetHeight()-40 && m_nMouseY <= CGame::GetInstance()->GetHeight()-40 + nButtonHeight)
	{
		// Continue
		if(m_nPos!=2)
			CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nButton,false);
		Highlight(&m_dwNext);
		m_nPos=2;
	}
	else
	{
		Highlight(nullptr);
		m_nPos=0;
	}
}

void StatState::Clicked()
{
	if(m_dwNext			 ==D3DCOLOR_XRGB(177,132,0))
	{
		CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nClick, false);
		m_bStats = false;
	}
	else if(m_dwBack		 ==D3DCOLOR_XRGB(177,132,0))
	{
		CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nClick, false);
		m_bStats = true;
	}
}

void StatState::RenderStats()
{

	m_pFont->Print(m_sStat.c_str(),(int)(CGame::GetInstance()->GetWidth()/2-(m_pFont->GetCharWidthW()*10/2)),25,(float)2.0f,D3DCOLOR_ARGB(255,255,255,255));

	RECT rSelf = { };
	SetRect(&rSelf, 653, 638, 816, 759);
	m_pTM->Draw(m_nBGImageID,45,95,4.25f,3.5f,&rSelf,0,0,0,D3DCOLOR_ARGB(255,255,255,255));
	

	
	
	m_pFont->Print(m_sScore.c_str()				,65,115,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	m_pFont->Print(m_sShots.c_str()		,65,165,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	m_pFont->Print(m_sNukes.c_str()		,65,215,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	m_pFont->Print(m_sDamage.c_str()		,65,265,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	m_pFont->Print(m_sMonies.c_str()	,65,315,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	m_pFont->Print(m_sEnemies.c_str()	,65,365,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	m_pFont->Print(m_sSappers.c_str()	,65,415,1.2f,D3DCOLOR_ARGB(255,255,255,255));


	{
		char buffer[10];
		_itoa_s(m_pPlayer->GetScore(),buffer,10);
		m_pFont->Print(buffer	,CGame::GetInstance()->GetWidth()-150,115,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	}
	{
		char buffer[10];
		_itoa_s(m_pPlayer->GetShotsFired(),buffer,10);
		m_pFont->Print(buffer	,CGame::GetInstance()->GetWidth()-150,165,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	}
	{
		char buffer[10];
		_itoa_s(m_pPlayer->GetNukesBlasted(),buffer,10);
		m_pFont->Print(buffer	,CGame::GetInstance()->GetWidth()-150,215,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	}
	{
		char buffer[10];
		if(m_pPlayer->GetDamageTaken() > 0)
			_itoa_s(m_pPlayer->GetDamageTaken(),buffer,10);
		else 
			_itoa_s(0,buffer,10);
		m_pFont->Print(buffer	,CGame::GetInstance()->GetWidth()-150,265,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	}
	{
		char buffer[10];
		_itoa_s(m_pPlayer->GetTotalMoneyEarned(),buffer,10);
		m_pFont->Print(buffer	,CGame::GetInstance()->GetWidth()-150,315,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	}
	{
		char buffer[10];
		_itoa_s(m_pPlayer->GetUnitsKilled(),buffer,10);
		m_pFont->Print(buffer	,CGame::GetInstance()->GetWidth()-150,365,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	}
	{
		char buffer[10];
		_itoa_s(m_pPlayer->GetSappersExploded(),buffer,10);
		m_pFont->Print(buffer	,CGame::GetInstance()->GetWidth()-150,415,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	}

	m_pTM->Draw(m_nBGImageID,45,95,4.25f,3.5f,&rSelf,0,0,0,D3DCOLOR_ARGB(100,255,255,255));

	

}

void StatState::RenderAchievements()
{
	m_pFont->Print(m_sAchieve.c_str(),(int)(CGame::GetInstance()->GetWidth()/2-(m_pFont->GetCharWidthW()*10/2)),25,(float)2.0f,D3DCOLOR_ARGB(255,255,255,255));

	RECT rSelf = { };
	SetRect(&rSelf, 653, 638, 816, 759);
	m_pTM->Draw(m_nBGImageID,45,95,4.25f,3.5f,&rSelf,0,0,0,D3DCOLOR_ARGB(255,255,255,255));
	float scale = 0.9f;
	if(m_pPlayer->GetNaziBoss())
		scale = 1.2f;
	else 
		scale = 0.9f;
	m_pFont->Print(m_sNazi.c_str(),65,115,scale,m_dwNaziBoss);	
	if(m_pPlayer->GetAlienBoss())
		scale = 1.2f;
	else 
		scale = 0.9f;
	m_pFont->Print(m_sAlien.c_str()					,65,165,scale,m_dwAlienBoss);
	if(m_pPlayer->GetRobotBoss())
		scale = 1.2f;
	else 
		scale = 0.9f;
	m_pFont->Print(m_sRobot.c_str()						,65,215,scale,m_dwRobotBoss);
	if(m_pPlayer->GetSparta())
		scale = 1.2f;
	else 
		scale = 0.9f;
	m_pFont->Print(m_sSparta.c_str()	,65,265,scale,m_dwSparta);
	if(m_pPlayer->GetSapperAbsorb())
		scale = 1.2f;
	else 
		scale = 0.9f;
	m_pFont->Print(m_sWTF.c_str()					,65,315,scale,m_dwSapperAbsorb);
	if(m_pPlayer->GetNukem())
		scale = 1.2f;
	else 
		scale = 0.9f;
	m_pFont->Print(m_sNukem.c_str()						,65,365,scale,m_dwNukem);
	if(m_pPlayer->GetIamBoss())
		scale = 1.2f;
	else 
		scale = 0.9f;
	m_pFont->Print(m_sPain.c_str()						,65,415,scale,m_dwIamBoss);
	if(m_pPlayer->GetAllUpgrades())
		scale = 1.2f;
	else 
		scale = 0.9f;
	m_pFont->Print(m_sOwnAll.c_str()					,65,465,scale,m_dwAllUpgrades);	
}

void StatState::LoadText(void)
{
	TiXmlDocument doc("resource/files/Text.xml");
	int LangSel=COptionsState::GetInstance()->GetLang();
	if(doc.LoadFile())
	{
		TiXmlNode* pParent = doc.RootElement();
		switch(LangSel)
		{
		case 0:
			{
				TiXmlNode* pLanguage = pParent->FirstChild("English");
				TiXmlNode* pState = pLanguage->FirstChild("StatState");
				TiXmlNode* pButton = pState->FirstChild("Stats");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sStat=pText->Value();
				pButton=pState->FirstChild("Score");
				pText = pButton->FirstChild()->ToText();
				m_sScore=pText->Value();
				pButton=pState->FirstChild("Shots");
				pText = pButton->FirstChild()->ToText();
				m_sShots=pText->Value();
				pButton=pState->FirstChild("Nukes");
				pText = pButton->FirstChild()->ToText();
				m_sNukes = pText->Value();
				pButton=pState->FirstChild("Damage");
				pText = pButton->FirstChild()->ToText();
				m_sDamage=pText->Value();
				pButton = pState->FirstChild("Monies");
				pText = pButton->FirstChild()->ToText();
				m_sMonies=pText->Value();
				pButton=pState->FirstChild("Enemies");
				pText = pButton->FirstChild()->ToText();
				m_sEnemies=pText->Value();
				pButton=pState->FirstChild("Sappers");
				pText = pButton->FirstChild()->ToText();
				m_sSappers=pText->Value();
				pButton=pState->FirstChild("Achievements");
				pText = pButton->FirstChild()->ToText();
				m_sAchieve=pText->Value();
				pButton=pState->FirstChild("NaziBoss");
				pText = pButton->FirstChild()->ToText();
				m_sNazi=pText->Value();
				pButton=pState->FirstChild("AlienBoss");
				pText = pButton->FirstChild()->ToText();
				m_sAlien=pText->Value();
				pButton=pState->FirstChild("RobotBoss");
				pText = pButton->FirstChild()->ToText();
				m_sRobot=pText->Value();
				pButton=pState->FirstChild("Sparta");
				pText = pButton->FirstChild()->ToText();
				m_sSparta=pText->Value();
				pButton=pState->FirstChild("WTFDamage");
				pText = pButton->FirstChild()->ToText();
				m_sWTF=pText->Value();
				pButton=pState->FirstChild("Nukem");
				pText = pButton->FirstChild()->ToText();
				m_sNukem=pText->Value();
				pButton=pState->FirstChild("Pain");
				pText = pButton->FirstChild()->ToText();
				m_sPain=pText->Value();
				pButton=pState->FirstChild("OwnAll");
				pText = pButton->FirstChild()->ToText();
				m_sOwnAll=pText->Value();
			}
			break;
		case 1:
			{
				TiXmlNode* pLanguage = pParent->FirstChild("English");
				TiXmlNode* pState = pLanguage->FirstChild("StatState");
				TiXmlNode* pButton = pState->FirstChild("Stats");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sStat=pText->Value();
				pButton=pState->FirstChild("Score");
				pText = pButton->FirstChild()->ToText();
				m_sScore=pText->Value();
				pButton=pState->FirstChild("Shots");
				pText = pButton->FirstChild()->ToText();
				m_sShots=pText->Value();
				pButton=pState->FirstChild("Nukes");
				pText = pButton->FirstChild()->ToText();
				m_sNukes = pText->Value();
				pButton=pState->FirstChild("Damage");
				pText = pButton->FirstChild()->ToText();
				m_sDamage=pText->Value();
				pButton = pState->FirstChild("Monies");
				pText = pButton->FirstChild()->ToText();
				m_sMonies=pText->Value();
				pButton=pState->FirstChild("Enemies");
				pText = pButton->FirstChild()->ToText();
				m_sEnemies=pText->Value();
				pButton=pState->FirstChild("Sappers");
				pText = pButton->FirstChild()->ToText();
				m_sSappers=pText->Value();
				pButton=pState->FirstChild("Achievements");
				pText = pButton->FirstChild()->ToText();
				m_sAchieve=pText->Value();
				pButton=pState->FirstChild("NaziBoss");
				pText = pButton->FirstChild()->ToText();
				m_sNazi=pText->Value();
				pButton=pState->FirstChild("AlienBoss");
				pText = pButton->FirstChild()->ToText();
				m_sAlien=pText->Value();
				pButton=pState->FirstChild("RobotBoss");
				pText = pButton->FirstChild()->ToText();
				m_sRobot=pText->Value();
				pButton=pState->FirstChild("Sparta");
				pText = pButton->FirstChild()->ToText();
				m_sSparta=pText->Value();
				pButton=pState->FirstChild("WTFDamage");
				pText = pButton->FirstChild()->ToText();
				m_sWTF=pText->Value();
				pButton=pState->FirstChild("Nukem");
				pText = pButton->FirstChild()->ToText();
				m_sNukem=pText->Value();
				pButton=pState->FirstChild("Pain");
				pText = pButton->FirstChild()->ToText();
				m_sPain=pText->Value();
				pButton=pState->FirstChild("OwnAll");
				pText = pButton->FirstChild()->ToText();
				m_sOwnAll=pText->Value();
			}
			break;
		case 2:
			{
				TiXmlNode* pLanguage = pParent->FirstChild("Pirate");
				TiXmlNode* pState = pLanguage->FirstChild("StatState");
				TiXmlNode* pButton = pState->FirstChild("Stats");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sStat=pText->Value();
				pButton=pState->FirstChild("Score");
				pText = pButton->FirstChild()->ToText();
				m_sScore=pText->Value();
				pButton=pState->FirstChild("Shots");
				pText = pButton->FirstChild()->ToText();
				m_sShots=pText->Value();
				pButton=pState->FirstChild("Nukes");
				pText = pButton->FirstChild()->ToText();
				m_sNukes = pText->Value();
				pButton=pState->FirstChild("Damage");
				pText = pButton->FirstChild()->ToText();
				m_sDamage=pText->Value();
				pButton = pState->FirstChild("Monies");
				pText = pButton->FirstChild()->ToText();
				m_sMonies=pText->Value();
				pButton=pState->FirstChild("Enemies");
				pText = pButton->FirstChild()->ToText();
				m_sEnemies=pText->Value();
				pButton=pState->FirstChild("Sappers");
				pText = pButton->FirstChild()->ToText();
				m_sSappers=pText->Value();
				pButton=pState->FirstChild("Achievements");
				pText = pButton->FirstChild()->ToText();
				m_sAchieve=pText->Value();
				pButton=pState->FirstChild("NaziBoss");
				pText = pButton->FirstChild()->ToText();
				m_sNazi=pText->Value();
				pButton=pState->FirstChild("AlienBoss");
				pText = pButton->FirstChild()->ToText();
				m_sAlien=pText->Value();
				pButton=pState->FirstChild("RobotBoss");
				pText = pButton->FirstChild()->ToText();
				m_sRobot=pText->Value();
				pButton=pState->FirstChild("Sparta");
				pText = pButton->FirstChild()->ToText();
				m_sSparta=pText->Value();
				pButton=pState->FirstChild("WTFDamage");
				pText = pButton->FirstChild()->ToText();
				m_sWTF=pText->Value();
				pButton=pState->FirstChild("Nukem");
				pText = pButton->FirstChild()->ToText();
				m_sNukem=pText->Value();
				pButton=pState->FirstChild("Pain");
				pText = pButton->FirstChild()->ToText();
				m_sPain=pText->Value();
				pButton=pState->FirstChild("OwnAll");
				pText = pButton->FirstChild()->ToText();
				m_sOwnAll=pText->Value();
			}
			break;
		case 3:
			{
				TiXmlNode* pLanguage = pParent->FirstChild("German");
				TiXmlNode* pState = pLanguage->FirstChild("StatState");
				TiXmlNode* pButton = pState->FirstChild("Stats");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sStat=pText->Value();
				pButton=pState->FirstChild("Score");
				pText = pButton->FirstChild()->ToText();
				m_sScore=pText->Value();
				pButton=pState->FirstChild("Shots");
				pText = pButton->FirstChild()->ToText();
				m_sShots=pText->Value();
				pButton=pState->FirstChild("Nukes");
				pText = pButton->FirstChild()->ToText();
				m_sNukes = pText->Value();
				pButton=pState->FirstChild("Damage");
				pText = pButton->FirstChild()->ToText();
				m_sDamage=pText->Value();
				pButton = pState->FirstChild("Monies");
				pText = pButton->FirstChild()->ToText();
				m_sMonies=pText->Value();
				pButton=pState->FirstChild("Enemies");
				pText = pButton->FirstChild()->ToText();
				m_sEnemies=pText->Value();
				pButton=pState->FirstChild("Sappers");
				pText = pButton->FirstChild()->ToText();
				m_sSappers=pText->Value();
				pButton=pState->FirstChild("Achievements");
				pText = pButton->FirstChild()->ToText();
				m_sAchieve=pText->Value();
				pButton=pState->FirstChild("NaziBoss");
				pText = pButton->FirstChild()->ToText();
				m_sNazi=pText->Value();
				pButton=pState->FirstChild("AlienBoss");
				pText = pButton->FirstChild()->ToText();
				m_sAlien=pText->Value();
				pButton=pState->FirstChild("RobotBoss");
				pText = pButton->FirstChild()->ToText();
				m_sRobot=pText->Value();
				pButton=pState->FirstChild("Sparta");
				pText = pButton->FirstChild()->ToText();
				m_sSparta=pText->Value();
				pButton=pState->FirstChild("WTFDamage");
				pText = pButton->FirstChild()->ToText();
				m_sWTF=pText->Value();
				pButton=pState->FirstChild("Nukem");
				pText = pButton->FirstChild()->ToText();
				m_sNukem=pText->Value();
				pButton=pState->FirstChild("Pain");
				pText = pButton->FirstChild()->ToText();
				m_sPain=pText->Value();
				pButton=pState->FirstChild("OwnAll");
				pText = pButton->FirstChild()->ToText();
				m_sOwnAll=pText->Value();
			}
			break;
		}
	}
}