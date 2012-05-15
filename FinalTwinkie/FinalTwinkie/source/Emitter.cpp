#include "Emitter.h"
#include "Game.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../tinyxml/tinystr.h"
#include "../tinyxml/tinyxml.h"
#include <sstream>
void CEmitter::CreateParticle(float fDt=0)
{
	if(m_nNumberParticles<=m_nMaxParticles)
	{
#pragma region Point_Emitter
		if(m_nType==Point)
		{
			if(m_bExplosion)
			{
				for(;;)
				{
					float velocityX=(float)(((rand()%361)/180.0)-1.0);
					float velocityY=(float)(((rand()%361)/180.0)-1.0);
					int speedX=m_fMaxSpeedX;
					int speedY=m_fMaxSpeedY;
					CParticle* newPart=new CParticle();
					newPart->CreateParticle(m_fMaxLife,velocityX*speedX,velocityY*speedY,m_fMaxScale,(float)m_nStartPosX,(float) m_nStartPosY, m_dwStartColor, m_nParticleImage);
					m_vParticles.push_back(newPart);
					m_nNumberParticles++;
					if(m_nNumberParticles>=m_nMaxParticles)
					{
						break;
					}
				}
			}
			else
			{
				if(m_fTimer>m_fSpawnTimer)
				{
					float velocityX=(float)(((rand()%361)/180.0)-1.0);
					float velocityY=(float)(((rand()%361)/180.0)-1.0);
					int speedX=m_fMaxSpeedX;
					int speedY=m_fMaxSpeedY;
					CParticle* newPart=new CParticle();
					newPart->CreateParticle(m_fMaxLife,velocityX*speedX,velocityY*speedY,m_fMaxScale,(float)m_nStartPosX,(float) m_nStartPosY, m_dwStartColor, m_nParticleImage);
					m_vParticles.push_back(newPart);
					m_nNumberParticles++;
					m_fTimer=0;
				}
				else
				{
					m_fTimer+=fDt;
				}
			}
		}
#pragma endregion
#pragma region Circle_Emitter
		else if(m_nType==CIRCLE)
		{
			if(m_fTimer>=m_fSpawnTimer)
			{
				float posX=0, posY=0;
				do
				{
					posX=rand()%(int)(m_fRadius*2)-m_fRadius;
					posY=rand()%(int)(m_fRadius*2)-m_fRadius;
				}while(abs(posX)+abs(posY)>m_fRadius);
				posX+=m_nStartPosX;
				posY+=m_nStartPosY;
				CParticle* newPart=new CParticle();
				newPart->CreateParticle(m_fMaxLife,0,0,m_fMaxScale,posX,posY, m_dwStartColor, m_nParticleImage);
				m_vParticles.push_back(newPart);
				m_nNumberParticles++;
				m_fTimer=0;
			}
			else
			{
				m_fTimer+=fDt;
			}
		}
#pragma endregion
#pragma region Square_Emitter
		else if(m_nType==SQUARE)
		{
			if(m_fTimer>m_fSpawnTimer)
			{
				float posX=rand()%(int)(m_fRadius*2)-m_fRadius;
				float posY=rand()%(int)(m_fRadius*2)-m_fRadius;
				posX+=m_nStartPosX;
				posY+=m_nStartPosY;
				CParticle* newPart=new CParticle();
				newPart->CreateParticle(m_fMaxLife,0,0,m_fMaxScale,posX,posY, m_dwStartColor, m_nParticleImage);
				m_vParticles.push_back(newPart);
				m_nNumberParticles++;
				m_fTimer=0;
			}
			else
			{
				m_fTimer+=fDt;
			}
		}
#pragma endregion
#pragma region Angle_Emitter
#pragma endregion
	}
}

void CEmitter::InitEmmitter(string szFile)
{
	TiXmlDocument doc(szFile.c_str());
	if(doc.LoadFile())
	{
		TiXmlNode* pParent=doc.RootElement();
		TiXmlNode* pChild=pParent->FirstChild()->FirstChild();
		TiXmlNode* pSecond;
		TiXmlNode* pThird;
		TiXmlText* pText=pChild->FirstChild()->ToText();
		string picture="resource/graphics/";
		picture+=pText->Value();
		TCHAR buffer[100];
		mbstowcs_s(nullptr,buffer, 100, picture.c_str(), _TRUNCATE);
		m_nParticleImage=CSGD_TextureManager::GetInstance()->LoadTexture(buffer);
		pChild=pChild->NextSibling();
		m_nMaxParticles=pChild->ToElement()->FirstAttribute()->IntValue();
		pChild=pChild->NextSibling();
		m_bLooping=pChild->ToElement()->FirstAttribute()->IntValue();
		pChild=pChild->NextSibling();
		m_bExplosion=pChild->ToElement()->FirstAttribute()->IntValue();
		pChild=pChild->NextSibling();
		m_fMaxLife=pChild->ToElement()->FirstAttribute()->IntValue();
		pChild=pChild->NextSibling();
		m_fSpawnTimer=pChild->ToElement()->FirstAttribute()->DoubleValue();
		pChild=pChild->NextSibling();
		m_nType=(Type)(pChild->ToElement()->FirstAttribute()->IntValue());
		pChild=pChild->NextSibling();
		m_fRadius=pChild->ToElement()->FirstAttribute()->DoubleValue();
		pChild=pChild->NextSibling();
		m_fAngle=pChild->ToElement()->FirstAttribute()->DoubleValue();
		pChild=pChild->NextSibling();
		pSecond=pChild->FirstChild();
		m_fMinSpeedX=pSecond->ToElement()->FirstAttribute()->DoubleValue();
		pSecond=pSecond->NextSibling();
		m_fMaxSpeedX=pSecond->ToElement()->FirstAttribute()->DoubleValue();
		pChild=pChild->NextSibling();
		pSecond=pChild->FirstChild();
		m_fMinSpeedY=pSecond->ToElement()->FirstAttribute()->DoubleValue();
		pSecond=pSecond->NextSibling();
		m_fMaxSpeedY=pSecond->ToElement()->FirstAttribute()->DoubleValue();
		pChild=pChild->NextSibling();
		pSecond=pChild->FirstChild();
		m_fMinScale=pSecond->ToElement()->FirstAttribute()->DoubleValue();
		pSecond=pSecond->NextSibling();
		m_fMaxScale=pSecond->ToElement()->FirstAttribute()->DoubleValue();
		pChild=pChild->NextSibling();
		pSecond=pChild->FirstChild();
		pThird=pSecond->FirstChild();
		int alpha=pThird->ToElement()->FirstAttribute()->IntValue();
		pThird=pThird->NextSibling();
		int red=pThird->ToElement()->FirstAttribute()->IntValue();
		pThird=pThird->NextSibling();
		int green=pThird->ToElement()->FirstAttribute()->IntValue();
		pThird=pThird->NextSibling();
		int blue=pThird->ToElement()->FirstAttribute()->IntValue();
		m_dwStartColor=D3DCOLOR_ARGB(alpha, red, green, blue);
		pSecond=pSecond->NextSibling();
		pThird=pSecond->FirstChild();
		alpha=pThird->ToElement()->FirstAttribute()->IntValue();
		pThird=pThird->NextSibling();
		red=pThird->ToElement()->FirstAttribute()->IntValue();
		pThird=pThird->NextSibling();
		green=pThird->ToElement()->FirstAttribute()->IntValue();
		pThird=pThird->NextSibling();
		blue=pThird->ToElement()->FirstAttribute()->IntValue();
		m_dwEndColor=D3DCOLOR_ARGB(alpha, red, green, blue);
	}
	//m_nStartPosX=400;
	//m_nStartPosY=300;
	m_fTimer=0;
	m_nNumberParticles=0;
	m_bActive=false;
}	

void CEmitter::UpdateParticles(float fDt)
{
	for(unsigned int i=0; i<m_vParticles.size(); i++)
	{
		if(m_vParticles[i]->GetLife()>0)
		{
			m_vParticles[i]->SetLife(m_vParticles[i]->GetLife()-fDt);
		}
		else
		{
			delete m_vParticles[i];
			m_vParticles.erase(m_vParticles.begin()+i);
			i--;
			if(m_bLooping)
				m_nNumberParticles--;
			continue;
		}

		if(m_vParticles[i]->GetScale()>m_fMinScale)
		{
			m_vParticles[i]->SetScale(m_vParticles[i]->GetScale()-((m_fMaxScale-m_fMinScale)/m_fMaxLife)*fDt);
		}

		if(m_vParticles[i]->GetColor()!=m_dwEndColor)
		{
			D3DXCOLOR ParticleColor=m_vParticles[i]->GetColor();
			ParticleColor.a-=((m_dwStartColor.a-m_dwEndColor.a)/m_fMaxLife)*fDt;
			ParticleColor.r-=((m_dwStartColor.r-m_dwEndColor.r)/m_fMaxLife)*fDt;
			ParticleColor.g-=((m_dwStartColor.g-m_dwEndColor.g)/m_fMaxLife)*fDt;
			ParticleColor.b-=((m_dwStartColor.b-m_dwEndColor.b)/m_fMaxLife)*fDt;
			m_vParticles[i]->SetColor(ParticleColor);
		}

		if(m_vParticles[i]->GetVelocityX()>0)
		{
			m_vParticles[i]->SetVelocityX(m_vParticles[i]->GetVelocityX()-((m_fMaxSpeedX-m_fMinSpeedX)/m_fMaxLife)*fDt);
		}
		if(m_vParticles[i]->GetVelocityX()<0)
		{
			m_vParticles[i]->SetVelocityX(m_vParticles[i]->GetVelocityX()+((m_fMaxSpeedX-m_fMinSpeedX)/m_fMaxLife)*fDt);
		}

		if(m_vParticles[i]->GetVelocityY()>0)
		{
			m_vParticles[i]->SetVelocityY(m_vParticles[i]->GetVelocityY()-((m_fMaxSpeedY-m_fMinSpeedY)/m_fMaxLife)*fDt);
		}
		if(m_vParticles[i]->GetVelocityY()<0)
		{
			m_vParticles[i]->SetVelocityY(m_vParticles[i]->GetVelocityY()+((m_fMaxSpeedY-m_fMinSpeedY)/m_fMaxLife)*fDt);
		}

		m_vParticles[i]->SetPosX((m_vParticles[i]->GetPosX()+m_vParticles[i]->GetVelocityX()));
		this->m_nStartPosX;
		this->m_nStartPosY;
		m_vParticles[i]->SetPosY((m_vParticles[i]->GetPosY()+m_vParticles[i]->GetVelocityY()));
	}
	if(m_bActive)
		CreateParticle(fDt);
}

void CEmitter::RenderParticles(void)
{
	
	for(unsigned int i=0; i<m_vParticles.size(); i++)
	{	
		m_vParticles[i]->Render();
	}
}

CEmitter::~CEmitter(void)
{
	for(unsigned int i=0; i<m_vParticles.size(); i++)
	{
		delete m_vParticles[i];
		m_vParticles.erase(m_vParticles.begin()+i);
		i--;
	}
}

void CEmitter::UpdateEmitterPos(float fPosX, float fPosY)
{
	m_nStartPosX=fPosX;
	m_nStartPosY=fPosY;
}