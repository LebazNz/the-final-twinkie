#include "SurvivalHS.h"
#include "MainMenuState.h"
#include "../Headers/Game.h"
CSurvivalHS* CSurvivalHS::m_pSelf = nullptr;
CSurvivalHS::CSurvivalHS(void)
{
}


CSurvivalHS::~CSurvivalHS(void)
{
	m_pD3D	= nullptr;
	m_pDI	= nullptr;
	m_pTM	= nullptr;
	m_pFM = nullptr;
}

CSurvivalHS* CSurvivalHS::GetInstance()
{
	if(m_pSelf == nullptr)
		m_pSelf = new CSurvivalHS;
	return m_pSelf;
}

void CSurvivalHS::DeleteInstance( void )
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}

void CSurvivalHS::Enter( void )
{
	m_pD3D	= CSGD_Direct3D::GetInstance();
	m_pDI	= CSGD_DirectInput::GetInstance();
	m_pTM	= CSGD_TextureManager::GetInstance();
	m_pFM	= CBitmapFont::GetInstance();
	if(!LoadPlayers("HighScores.xml"))
		GeneratePlayers();
	CSurvivalHS::SwapPlayers();
	m_nBackgroundID = m_pTM->LoadTexture(_T("resource/graphics/bg_loadMenu_&_sprites.png"),D3DCOLOR_XRGB(255,255,255));
}

void CSurvivalHS::Exit( void )
{
	SavePlayers("HighScores.xml");

	m_pD3D = nullptr;
	m_pDI  = nullptr;
	m_pTM  = nullptr;
	
}

bool CSurvivalHS::Input( void )
{
	if(m_pDI->KeyPressed(DIK_ESCAPE))
	{
		CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
		return true;
	}
	return true;
}

void CSurvivalHS::Update( float fElapsedTime )
{

}

void CSurvivalHS::Render( void )
{
	RECT rSelf = { };
	SetRect(&rSelf, 0, 0, 800, 600);
	m_pTM->Draw(m_nBackgroundID,0,0,1.0f,1.0f,&rSelf,0,0,0);
	vector<PlayerScores>::iterator iter;
	int i = 0;
	for(iter = m_vScore.begin();iter != m_vScore.end(); ++iter)
	{
		++i;
		// THANKS FOR THE HELP!! http://www.cplusplus.com/forum/beginner/7777/
		int tempNum = iter->GetScore();
		std::string temp="";
		std::string convertvalue="";
		while (tempNum>0)
		{
			temp+=tempNum%10+48;
			tempNum/=10;
		}
		for (unsigned int i=0;i<temp.length();i++)
			convertvalue+=temp[temp.length()-i-1];

		m_pFM->Print(iter->GetName().c_str(),75,50*i,1,D3DCOLOR_ARGB(255,255,255,255));
		m_pFM->Print(convertvalue.c_str(),500,50*i,1,D3DCOLOR_ARGB(255,255,255,255));
	}
}

void CSurvivalHS::Transition()
{

}

void CSurvivalHS::GeneratePlayers()
{
	PlayerScores player1;
	player1.SetName("Caboosh");
	player1.SetScore(8999);
	PlayerScores player2;
	player2.SetName("Frank");
	player2.SetScore(4976);
	PlayerScores player3;
	player3.SetName("Steve");
	player3.SetScore(3197);
	PlayerScores player4;
	player4.SetName("Max");
	player4.SetScore(2198);
	PlayerScores player5;
	player5.SetName("Anthony");
	player5.SetScore(1);

	
	m_vScore.push_back(player1);
	m_vScore.push_back(player2);
	m_vScore.push_back(player3);
	m_vScore.push_back(player4);
	m_vScore.push_back(player5);
}

bool CSurvivalHS::LoadPlayers( const char* szFileName )
{
	int score = CPlayer::GetInstance()->GetScore();
	string name = CPlayer::GetInstance()->GetUserName();
	// Create a TinyXML Document
	TiXmlDocument doc;
	// Attempt to load the document from the file
	if(doc.LoadFile(szFileName) == false)
		return false;

	// Access the root node (player_list) in the document

	TiXmlElement* pRoot = doc.RootElement();
	if(pRoot == nullptr)
		return false;

	// Clear out any existing player data
	m_vScore.clear();

	// Iterate through the root's children nodes (player_info)
	TiXmlElement* pPlayer = pRoot->FirstChildElement("player_info");

	while(pPlayer != nullptr)
	{
		// Read the player's info out of the node
		PlayerScores info;

		// Read the name (which is a Text node between the XML tags)
		const char* pText = pPlayer->GetText();
		if(pText != nullptr)
		{
			info.SetName(pText);
		}
		int temp;
		// Read the attributes (within the XML tag)
		if(pPlayer->Attribute("score",&temp) == nullptr)
			info.SetScore(0);
		else
			info.SetScore(temp);


		// Save the player to our vector
		m_vScore.push_back(info);

		// Move to the next node in the player_list
		pPlayer = pPlayer->NextSiblingElement("player_info");
	}

	return true;
}

void CSurvivalHS::SavePlayers( const char* szFileName )
{
	// Create a tinyXML document
	TiXmlDocument doc;

	// Create a TinyXML Declaration (version info)
	TiXmlDeclaration*	pDec = new TiXmlDeclaration("1.0","utf-8","");

	// Add the declaration to the document
	doc.LinkEndChild(pDec);


	// Create a root node for the document (player_list)
	TiXmlElement*	pRoot = new TiXmlElement("player_list");

	// Add the root node to the document
	doc.LinkEndChild(pRoot);


	// Iterate through the vector to save individual players
	vector<PlayerScores>::iterator iter;
	for(iter = m_vScore.begin();iter != m_vScore.end(); ++iter)
	{
		// Create a node for this player
		TiXmlElement* pPlayer = new TiXmlElement("player_info");

		// Fill the node with player info7
		pPlayer->SetAttribute("score",iter->GetScore());	// int

		// Create a Text node for the player's name
		// to store it between the XML tags

		TiXmlText*	pText = new TiXmlText(iter->GetName().c_str());
		pPlayer->LinkEndChild(pText);

		// Add the player node to the "player_list"
		pRoot->LinkEndChild(pPlayer);

	}

	// Save the XML document to the file
	doc.SaveFile(szFileName);
}

void CSurvivalHS::SwapPlayers()
{
	vector<PlayerScores>::iterator iter;

	for(iter = m_vScore.begin(); iter != m_vScore.end(); ++iter)
	{
		if(CPlayer::GetInstance()->GetScore() > iter->GetScore())
		{
			PlayerScores* temp = new PlayerScores;
			temp->SetName(CPlayer::GetInstance()->GetUserName());
			temp->SetScore(CPlayer::GetInstance()->GetScore());
			m_vScore.insert(iter,*temp);	
			break;
		}
	}
}
