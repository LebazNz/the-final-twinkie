#define _USE_MATH_DEFINES
#include "Emitter.h"
#include "../Headers/Game.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../tinyxml/tinystr.h"
#include "../tinyxml/tinyxml.h"
#include <math.h>
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
					float life=(float)(rand()/4294967294);
					life=(life*(m_fMaxLife-m_fMinLife))+m_fMinLife;
					CParticle* newPart=new CParticle();
					newPart->CreateParticle(life,velocityX*m_fMaxSpeedX,velocityY*m_fMaxSpeedY,m_fMaxScale,m_fStartPosX,m_fStartPosY, m_dwStartColor, m_nParticleImage);
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
					float life=(float)(rand()/4294967294);
					life=(life*(m_fMaxLife-m_fMinLife))+m_fMinLife;
					CParticle* newPart=new CParticle();
					newPart->CreateParticle(life,velocityX*m_fMaxSpeedX,velocityY*m_fMaxSpeedY,m_fMaxScale,m_fStartPosX,m_fStartPosY, m_dwStartColor, m_nParticleImage);
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
				posX+=m_fStartPosX;
				posY+=m_fStartPosY;
				float life=float(rand()/4294967294);
				life=(life*(m_fMaxLife-m_fMinLife))+m_fMinLife;
				CParticle* newPart=new CParticle();
				newPart->CreateParticle(life,0,0,m_fMaxScale,posX,posY, m_dwStartColor, m_nParticleImage);
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
				posX+=m_fStartPosX;
				posY+=m_fStartPosY;
				float life=(float)(rand()/4294967294);
				life=(life*(m_fMaxLife-m_fMinLife))+m_fMinLife;
				CParticle* newPart=new CParticle();
				newPart->CreateParticle(life,0,0,m_fMaxScale,posX,posY, m_dwStartColor, m_nParticleImage);
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
		if(m_nType==ANGLE)
		{
			if(m_bExplosion)
			{
				for(;;)
				{
					float velocityX;
					float velocityY;
					tVector2D vel;
					do
					{
						velocityX=(float)(((rand()%361)/180.0)-1.0);
						velocityY=(float)(((rand()%361)/180.0)-1.0);
						vel.fX=velocityX;
						vel.fY=velocityY;
					}while(abs(AngleBetweenVectors(m_vDirection, vel))>abs(AngleBetweenVectors(m_vDirection, Vector2DRotate(m_vDirection, m_fAngle))));
					float life=(float)(rand()/4294967294);
					life=(life*(m_fMaxLife-m_fMinLife))+m_fMinLife;
					CParticle* newPart=new CParticle();
					newPart->CreateParticle(life,velocityX*m_fMaxSpeedX,velocityY*m_fMaxSpeedY,m_fMaxScale,m_fStartPosX,m_fStartPosY, m_dwStartColor, m_nParticleImage);
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
					float velocityX;
					float velocityY;
					tVector2D vel;
					do
					{
						velocityX=(float)(((rand()%361)/180.0)-1.0);
						velocityY=(float)(((rand()%361)/180.0)-1.0);
						vel.fX=velocityX;
						vel.fY=velocityY;
					}while(abs(AngleBetweenVectors(m_vDirection, vel))>abs(AngleBetweenVectors(m_vDirection, Vector2DRotate(m_vDirection, m_fAngle))));
					float life=(float)(rand()/4294967294);
					life=(life*(m_fMaxLife-m_fMinLife))+m_fMinLife;
					CParticle* newPart=new CParticle();
					newPart->CreateParticle(life,velocityX*m_fMaxSpeedX,velocityY*m_fMaxSpeedY,m_fMaxScale,m_fStartPosX,m_fStartPosY, m_dwStartColor, m_nParticleImage);
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
	}
}

void CEmitter::InitEmmitter(string szFile)
{
	TiXmlDocument doc(szFile.c_str());
	doc.LoadFile();
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
		pChild->ToElement()->FirstAttribute()->IntValue()==1 ?m_bLooping=true :m_bLooping=false;
		pChild=pChild->NextSibling();
		pChild->ToElement()->FirstAttribute()->IntValue()==1 ?m_bExplosion=true :m_bExplosion=false;
		pChild=pChild->NextSibling();
		pSecond=pChild->FirstChild();
		m_fMaxLife=(float)pSecond->ToElement()->FirstAttribute()->DoubleValue();
		pSecond=pSecond->NextSibling();
		m_fMinLife=(float)pSecond->ToElement()->FirstAttribute()->DoubleValue();
		pChild=pChild->NextSibling();
		m_fSpawnTimer=(float)pChild->ToElement()->FirstAttribute()->DoubleValue();
		pChild=pChild->NextSibling();
		m_nType=(Type)(pChild->ToElement()->FirstAttribute()->IntValue());
		pChild=pChild->NextSibling();
		m_fRadius=(float)pChild->ToElement()->FirstAttribute()->DoubleValue();
		pChild=pChild->NextSibling();
		m_fAngle=(float)pChild->ToElement()->FirstAttribute()->DoubleValue();
		m_fAngle=(float)(m_fAngle*(M_PI/180));		
		pChild=pChild->NextSibling();
		m_nSource=(D3DBLEND)pChild->ToElement()->FirstAttribute()->IntValue();
		pChild=pChild->NextSibling();
		m_nDest=(D3DBLEND)pChild->ToElement()->FirstAttribute()->IntValue();
		pChild=pChild->NextSibling();
		pSecond=pChild->FirstChild();
		m_fMinSpeedX=(float)pSecond->ToElement()->FirstAttribute()->DoubleValue();
		pSecond=pSecond->NextSibling();
		m_fMaxSpeedX=(float)pSecond->ToElement()->FirstAttribute()->DoubleValue();
		pChild=pChild->NextSibling();
		pSecond=pChild->FirstChild();
		m_fMinSpeedY=(float)pSecond->ToElement()->FirstAttribute()->DoubleValue();
		pSecond=pSecond->NextSibling();
		m_fMaxSpeedY=(float)pSecond->ToElement()->FirstAttribute()->DoubleValue();
		pChild=pChild->NextSibling();
		pSecond=pChild->FirstChild();
		m_fMinScale=(float)pSecond->ToElement()->FirstAttribute()->DoubleValue();
		pSecond=pSecond->NextSibling();
		m_fMaxScale=(float)pSecond->ToElement()->FirstAttribute()->DoubleValue();
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
			m_vParticles[i]->SetScale(m_vParticles[i]->GetScale()-((m_fMaxScale-m_fMinScale)/m_vParticles[i]->GetTotalLife())*fDt);
		}

		if(m_vParticles[i]->GetColor()!=m_dwEndColor)
		{
			D3DXCOLOR ParticleColor=m_vParticles[i]->GetColor();
			ParticleColor.a-=((m_dwStartColor.a-m_dwEndColor.a)/m_vParticles[i]->GetTotalLife())*fDt;
			ParticleColor.r-=((m_dwStartColor.r-m_dwEndColor.r)/m_vParticles[i]->GetTotalLife())*fDt;
			ParticleColor.g-=((m_dwStartColor.g-m_dwEndColor.g)/m_vParticles[i]->GetTotalLife())*fDt;
			ParticleColor.b-=((m_dwStartColor.b-m_dwEndColor.b)/m_vParticles[i]->GetTotalLife())*fDt;
			m_vParticles[i]->SetColor(ParticleColor);
		}

		if(m_vParticles[i]->GetVelocityX()>0)
		{
			m_vParticles[i]->SetVelocityX(m_vParticles[i]->GetVelocityX()-((m_fMaxSpeedX-m_fMinSpeedX)/m_vParticles[i]->GetTotalLife())*fDt);
		}
		if(m_vParticles[i]->GetVelocityX()<0)
		{
			m_vParticles[i]->SetVelocityX(m_vParticles[i]->GetVelocityX()+((m_fMaxSpeedX-m_fMinSpeedX)/m_vParticles[i]->GetTotalLife())*fDt);
		}

		if(m_vParticles[i]->GetVelocityY()>0)
		{
			m_vParticles[i]->SetVelocityY(m_vParticles[i]->GetVelocityY()-((m_fMaxSpeedY-m_fMinSpeedY)/m_vParticles[i]->GetTotalLife())*fDt);
		}
		if(m_vParticles[i]->GetVelocityY()<0)
		{
			m_vParticles[i]->SetVelocityY(m_vParticles[i]->GetVelocityY()+((m_fMaxSpeedY-m_fMinSpeedY)/m_vParticles[i]->GetTotalLife())*fDt);
		}

		m_vParticles[i]->SetPosX((m_vParticles[i]->GetPosX()+m_vParticles[i]->GetVelocityX()));
		m_vParticles[i]->SetPosY((m_vParticles[i]->GetPosY()+m_vParticles[i]->GetVelocityY()));
	}
	if(m_bActive)
		CreateParticle(fDt);
}

void CEmitter::RenderParticles(void)
{
	DWORD nOrigSrc;
	DWORD nOrigDest;

	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->GetRenderState(D3DRS_SRCBLEND, &nOrigSrc);
	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->GetRenderState(D3DRS_DESTBLEND, &nOrigDest);

	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();

	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->SetRenderState(D3DRS_SRCBLEND, m_nSource);
	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->SetRenderState(D3DRS_DESTBLEND, m_nDest);
	for(unsigned int i=0; i<m_vParticles.size(); i++)
	{	
		m_vParticles[i]->Render();
	}

	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();

	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->SetRenderState(D3DRS_SRCBLEND, nOrigSrc);
	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->SetRenderState(D3DRS_DESTBLEND, nOrigDest);
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
	m_fStartPosX=fPosX;
	m_fStartPosY=fPosY;
}

void  CEmitter::UpdateEmitterDirecton(tVector2D vDir)
{
	m_vDirection=vDir;
}