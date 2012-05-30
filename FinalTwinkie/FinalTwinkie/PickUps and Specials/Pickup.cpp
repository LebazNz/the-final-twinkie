#include "Pickup.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../Headers/Camera.h"
#include "../Event and Messages/MessageSystem.h"
#include "../Event and Messages/DestroyPickupMessage.h"



CPickup::CPickup(void)
{
	m_nType = OBJ_PICKUP;
	m_fAliveTime = 0.0f;
	m_nGiven = 0;
	m_nPickUpType = -1;
	m_fEndTime = 0.0f;
	m_pPlayer = CPlayer::GetInstance();
}

CPickup::~CPickup(void)
{
}

void CPickup::Update(float fDt)
{
	CEntity::Update(fDt);
	m_fEndTime += fDt;
	if(m_fEndTime >= m_fAliveTime)
	{
		CDestroyPickupMessage* pMsg = new CDestroyPickupMessage(this);
		CMessageSystem::GetInstance()->SndMessage(pMsg);
		pMsg = nullptr;
	}
}

void CPickup::Render(void)
{
	Camera* C=Camera::GetInstance();
	if(GetImageID() != -1)
	{
		CSGD_TextureManager::GetInstance()->Draw(GetImageID(), int(GetPosX()-(GetWidth()/2)+C->GetPosX()), int(GetPosY()-(GetHeight()/2)+C->GetPosY()), 1.0f, 1.0f, nullptr, float(GetWidth()/2), float(GetHeight()/2), 0.0f, GetColor()); 
		//CSGD_Direct3D::GetInstance()->DrawRect(GetRect(), 255,0,0);
	}
}

bool CPickup::CheckCollision(IEntity* pBase)
{
	if(CEntity::CheckCollision(pBase) == true)
	{
		switch(pBase->GetType())
		{
		case OBJ_BASE:
			break;
		case OBJ_PLAYER:
			{
				switch(m_nPickUpType)
				{
				case PU_HEALTH:
					{
						float fHealth = m_pPlayer->GetHealth();
						float fMaxHealth = m_pPlayer->GetMaxHealth();
						fHealth += (float)m_nGiven;
						if(fHealth >= fMaxHealth)
							fHealth = fMaxHealth;
						m_pPlayer->SetHealth(fHealth);
					}
					break;
				case PU_AMMO:
					{
						int nAmmo[3];
						nAmmo[0] = m_pPlayer->GetWeaponAmmoOne();
						nAmmo[1] = m_pPlayer->GetWeaponAmmoTwo();
						nAmmo[2] = m_pPlayer->GetWeaponAmmoThree();
						int nMaxAmmo[3];
						nMaxAmmo[0] = m_pPlayer->GetMaxWeaponAmmoOne();
						nMaxAmmo[1] = m_pPlayer->GetMaxWeaponAmmoTwo();
						nMaxAmmo[2] = m_pPlayer->GetMaxWeaponAmmoThree();
						for(int i = 0; i < 3; ++i)
						{
							if(nAmmo[i] != -1)
								nAmmo[i] = nMaxAmmo[i];
						}
					}
					break;
				case PU_ARMOR:
					{
						float fArmor = m_pPlayer->GetArmor();
						float fMaxArmor = m_pPlayer->GetMaxArmor();
						fArmor += (float)m_nGiven;
						if(fArmor >= fMaxArmor)
							fArmor = fMaxArmor;
						m_pPlayer->SetArmor(fArmor);
					}
					break;
				case PU_DD:
					break;
				case PU_NORELOAD:
					break;
				case PU_INVU:
					break;
				case PU_INFAMMO:
					break;
				case PU_MONEY:
					{
						int nMoney = m_pPlayer->GetMoney();
						nMoney+=m_nGiven;
						m_pPlayer->SetMoney(nMoney);
					}
					break;
				}
				CDestroyPickupMessage* pMsg = new CDestroyPickupMessage(this);
				CMessageSystem::GetInstance()->SndMessage(pMsg);
				pMsg = nullptr;
			}
			break;
		case OBJ_BULLET:
			break;
		case OBJ_ENEMY:
			break;
		};
		return true;
	}
	else
		return false;
}