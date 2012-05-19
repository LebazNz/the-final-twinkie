#include <windows.h>
#include "AnimationVault.h"
#include "AnimationManager.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include <iterator>
#include "Frame.h"
#include "../tinyxml/tinyxml.h"
#include <sstream>
#include <string>
#include <iostream>
#include "../Headers/Camera.h"
CAnimationManager::CAnimationManager(void)
{
	m_pAV	= new CAnimationVault();
	animframe = 0;
}
	
CAnimationManager::~CAnimationManager(void)
{
	for(unsigned int i=0; i<m_vpFrame.size(); i++)
	{
		delete(m_vpFrame[i]);
	}
	delete m_pAV;
}
	
void CAnimationManager::Update( float fDt )
{
	static DWORD g = GetTickCount() + 10;
	if(g < GetTickCount())
	{
		if(animframe < 2)
			animframe++;
		else 
			animframe = 0;
		g = GetTickCount() + 10;
	}
}

void CAnimationManager::Load( const char* szFile )
{
	//tchar buffer[20];
	//mbstowcs_s(nullptr,buffer,20,szFile,_TRUNCATE);
	
	CAnimation* pA = new CAnimation();
	AddAnimation(pA);
	


	// Create a TinyXML Document
	TiXmlDocument document;
	// Attempt to load the document from the file
	
	if(document.LoadFile(szFile) == false)
	{
		return;
	}

	// Access the root node (Frame_List) in the document
	TiXmlElement* pRoot = document.RootElement();
	if(pRoot == nullptr)
		return;

	// Clear out any frames
	m_vpFrame.clear();

	// Iterate through the root's children nodes (Frame_Info)
	TiXmlElement* pFrame = pRoot->FirstChildElement("Frame_Info");

	while(pFrame != nullptr)
	{
		CFrame info;

		// Read the frame data 
		// Fill the node with vector info
		
		RECT tempR;
		// Left
		int tempRL;
		pFrame->Attribute("FrameRectLeft",&tempRL);
		tempR.left = tempRL;

		// Top
		int tempRT;
		pFrame->Attribute("FrameRectTop",&tempRT);
		tempR.top = tempRT;

		// Right
		int tempRR;
		pFrame->Attribute("FrameRectRight",&tempRR);
		tempR.right = tempRR;

		// Bottom
		int tempRB;
		pFrame->Attribute("FrameRectBottom",&tempRB);
		tempR.bottom = tempRB;

		// Anchor Y
		int tempAY;
		pFrame->Attribute("FrameAnchorY",&tempAY);
		info.SetAnchorY(tempAY);

		// Anchor X
		int tempAX;
		pFrame->Attribute("FrameAnchorX",&tempAX);
		info.SetAnchorX(tempAX);

		// Frame Time
		double tempT;
		pFrame->Attribute("FrameTime",&tempT);
		info.SetFrameTime((float)tempT);
	
		info.SetFrame(tempR);
		AddFrame(info.GetFrame().left,info.GetFrame().top,info.GetFrame().right,
			info.GetFrame().bottom,info.GetAnchorX(),info.GetAnchorY(),
			info.GetFrameTime());

			pFrame = pFrame->NextSiblingElement("Frame_Info");
	}

	
	
	

		//X:	0
		//Y:	0
		//height:	180
		//width:	150
		//AP:	
		//
		//
		//X:	160
		//Y:	0
		//height:	180
		//width:	140
		//AP:	230	330
		//
		//
		//X:	310
		//Y:	0
		//height:	180
		//width:	150
		//AP:	360	330



}	
	
void CAnimationManager::Unload()
{	

}	
	
void CAnimationManager::Render()
{

	static DWORD g = GetTickCount() + 100;
	if(g < GetTickCount())
	{
		if(animframe < 2)
			animframe++;
		else 
			animframe = 0;
		g = GetTickCount() + 100;
	}

	int xOffSet =m_vpFrame[animframe]->GetAnchorX() - (m_vpFrame[animframe]->GetFrame().left  );
	int yOffSet =m_vpFrame[animframe]->GetAnchorY() - (m_vpFrame[animframe]->GetFrame().top   );

	int x = m_vpFrame[animframe]->GetAnchorX();
	/*CSGD_TextureManager::GetInstance()->Draw(m_pAV->m_vAnimationList[0]->GetImageID(),
		(int)(100 - xOffSet + Camera::GetInstance()->GetPosX()),(int)(190 - yOffSet+ Camera::GetInstance()->GetPosY()),1.0f,1.0f,&m_vpFrame[animframe]->GetFrame(),
		0.0f,0.0f,0.0f);*/
	
	
}

void CAnimationManager::StartAnimation( int nID )
{

}

void CAnimationManager::StopAnimation( int nID )
{

}

void CAnimationManager::PauseAnimation( int nID )
{

}

void CAnimationManager::AddAnimation( CAnimation* pAnimation )
{
	temp = CSGD_TextureManager::GetInstance()->LoadTexture(_T("resource/graphics/test.png"),D3DCOLOR_XRGB(255,255,255));
		
	pAnimation->SetImageID(temp);

	m_pAV->m_vAnimationList.push_back(pAnimation);
	
}

void CAnimationManager::AddFrame(int nX, int nY, int nWidth, int nHeight, int nAnchorX, int nAnchorY, float fFrameTime)
{
	CFrame* pFrame = new CFrame();
	//pFrame->SetPosX(nX);
	//pFrame->SetPosY(nY);
	//pFrame->SetHeight(nHeight);
	//pFrame->SetWidth(nWidth);

	
	RECT rBanana;
	rBanana.left = nX;
	rBanana.top = nY;
	rBanana.right =  /*rBanana.left +*/ nWidth;
	rBanana.bottom = /*rBanana.top +*/ nHeight;
	pFrame->SetFrame(rBanana);
	pFrame->SetFrameTime(fFrameTime);

	pFrame->SetAnchorX(nAnchorX);
	pFrame->SetAnchorY(nAnchorY);

	m_vpFrame.push_back(pFrame);
}


CAnimationManager* CAnimationManager::GetInstance()
{
	static CAnimationManager s_Instance;
	return &s_Instance;
}

void CAnimationManager::Save(const char* szFile)
{
	CAnimation* pA = new CAnimation();
	AddAnimation(pA);

	AddFrame(0,	  0, 150, 180, 79,  76, 0);
	AddFrame(150, 0, 300, 180, 227, 76, 0);
	AddFrame(300, 0, 450, 180, 388, 76, 0);

	// Create a tiny XML doc
	TiXmlDocument document;

	// Create a TinyXML Declaration (version info)
	TiXmlDeclaration* pDec = new TiXmlDeclaration("1.0","utf-8","");

	// Add the declaration to the document

	document.LinkEndChild(pDec);

	// Create a root node for the document (Frame_List)
	TiXmlElement* pRoot = new TiXmlElement("Frame_List");

	// Add the root node to the document
	document.LinkEndChild(pRoot);

	// Iterate through the vector to save each frame
	std::vector<CFrame*>::iterator iter;
	for(iter = m_vpFrame.begin(); iter != m_vpFrame.end(); ++iter)
	{
		// Create a node for this Frame
		TiXmlElement* pFrame = new TiXmlElement("Frame_Info");

		// Fill the node with vector info
		// Left
		pFrame->SetAttribute("FrameRectLeft",(*iter)->GetFrame().left);
		// Top
		pFrame->SetAttribute("FrameRectTop",(*iter)->GetFrame().top);
		// Right
		pFrame->SetAttribute("FrameRectRight",(*iter)->GetFrame().right);
		// Bottom
		pFrame->SetAttribute("FrameRectBottom",(*iter)->GetFrame().bottom);
		// Anchor Y
		pFrame->SetAttribute("FrameAnchorY",(*iter)->GetAnchorY());
		// Anchor X
		pFrame->SetAttribute("FrameAnchorX",(*iter)->GetAnchorX());
		// Frame Time
		pFrame->SetDoubleAttribute("FrameTime",(double)(*iter)->GetFrameTime());


		// Create a Text node for the frame's name
		// to store it between the XML tags

		/*TiXmlText* pText = new TiXmlText("HELICOPTER)");
		pFrame->LinkEndChild(pText);*/

		// Add the frame node to the Frame_List
		pRoot->LinkEndChild(pFrame);
	}
	document.SaveFile(szFile);
}
