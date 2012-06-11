#include "Pickup.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../Headers/Camera.h"
#include "../Event and Messages/MessageSystem.h"
#include "../Event and Messages/DestroyPickupMessage.h"
#include "../Event and Messages/CreateFlyTextMessage.h"



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
				CPlayer* pPlayer = dynamic_cast<CPlayer*>(pBase);

				switch(m_nPickUpType)
				{
				case PU_HEALTH:
					{
						float fHealth = pPlayer->GetHealth();
						float fMaxHealth = pPlayer->GetMaxHealth();
						fHealth += (float)m_nGiven;
						if(fHealth >= fMaxHealth)
							fHealth = fMaxHealth;
						pPlayer->SetHealth(fHealth);
					}
					break;
				case PU_AMMO:
					{
						int nAmmo[3] = {};
						nAmmo[0] = pPlayer->GetWeaponAmmoShell();
						nAmmo[1] = pPlayer->GetWeaponAmmoArtillery();
						nAmmo[2] = pPlayer->GetWeaponAmmoMissile();
						int nMaxAmmo[3] = {};
						nMaxAmmo[0] = pPlayer->GetMaxWeaponAmmoShell();
						nMaxAmmo[1] = pPlayer->GetMaxWeaponAmmoArtillery();
						nMaxAmmo[2] = pPlayer->GetMaxWeaponAmmoMissile();
						for(int i = 0; i < 3; ++i)
						{
							if(nAmmo[i] != -1)
								nAmmo[i] += (int)nMaxAmmo[i]*0.25f;
								if(nAmmo[i] > nMaxAmmo[i])
									nAmmo[i] = nMaxAmmo[i];
						}
						pPlayer->SetWeaponAmmo(nAmmo[0],nAmmo[1],nAmmo[2]);
					}
					break;
				case PU_ARMOR:
					{
						float fArmor = pPlayer->GetArmor();
						float fMaxArmor = pPlayer->GetMaxArmor();
						fArmor += (float)m_nGiven;
						if(fArmor >= fMaxArmor)
							fArmor = fMaxArmor;
						pPlayer->SetArmor(fArmor);
					}
					break;
				case PU_DD:
					{
						pPlayer->SetDamageTimer(15.0f);
						pPlayer->SetDoubleDamage(true);
					}
					break;
				case PU_NORELOAD:
					{
						pPlayer->SetNoReloadTimer(15.0f);
					}
					break;
				case PU_INVU:
					{
						pPlayer->SetInvul(true);
						pPlayer->SetInvulTimer(15.0f);
					}
					break;
				case PU_INFAMMO:
					{
						pPlayer->SetInfAmmo(true);
						pPlayer->SetInfoAmmoTimer(15.0f);
					}
					break;
				case PU_MONEY:
					{
						int nMoney = pPlayer->GetMoney();
						nMoney+=m_nGiven;
						pPlayer->SetMoney(nMoney);
						CPlayer::GetInstance()->SetTotalMoneyEarned(CPlayer::GetInstance()->GetTotalMoneyEarned()+nMoney);
					}
					break;
				}
				CCreateFlyTextMessage* pMsge = new CCreateFlyTextMessage(MSG_CREATEFLYTEXT,m_nPickUpType,this);
				CMessageSystem::GetInstance()->SndMessage(pMsge);
				pMsge = nullptr;
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