#include "Player.h"
#include "../Headers/GUI.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/SGD_Math.h"
#include "../Event and Messages/MessageSystem.h"
#include "../Event and Messages/CreateBulletMessage.h"
#include "../Event and Messages/DestroyEnemyMessage.h"
#include "../Headers/Camera.h"
#include "../Headers/Game.h"
#include "../GameStates/ShopState.h"
#include "Enemy.h"
#include "../PickUps and Specials/Special.h"
#include "../ObjectManager and Factory/ObjectManager.h"
#include "../Boss/NaziBoss.h"
#include "../GameObjects/Factory.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"
#include "../GameStates/GamePlayState.h"
#include "../GameStates/SurvivalState.h"
#include "../GameStates/TutorState.h"

CPlayer* CPlayer::m_pInstance=nullptr;
CPlayer* CPlayer::GetInstance(void)
{
	if(m_pInstance==nullptr)
		m_pInstance=new CPlayer;
	return m_pInstance;
}

void CPlayer::DeleteInstance(void)
{
	if(m_pInstance!=nullptr)
		delete m_pInstance;
	m_pInstance=nullptr;
}

void CPlayer::Update(float fDt)
{
	this;
	tVector2D Up={0,-1};

	if(ARCADE == 0)
	{
		if(m_pDI->KeyDown(DIK_W) || m_pDI->KeyDown(DIK_S) || m_pDI->JoystickGetRStickYAmount() < 0 || m_pDI->JoystickGetRStickYAmount() > 0)
		{
			m_bIsMoving = true;
		}
		else m_bIsMoving = false;

		if(!m_pDI->KeyDown(DIK_W) && !m_pDI->KeyDown(DIK_S) && m_pDI->JoystickGetRStickYAmount() == 0)
		{
			SetMoveUp(false);
			SetMoveDown(false);
		}

		if(Camera::GetInstance()->GetPlayerCannotMove() == false)
		{
			if(m_pDI->KeyDown(DIK_W) || m_pDI->JoystickDPadDown(DIR_UP) || m_pDI->JoystickGetRStickYAmount() < 0)
			{
				Up=Vector2DRotate(Up, m_fRotation);
				float DX=(Up.fX*GetVelX()*fDt);
				m_v2OldPos.fX = GetPosX();
				m_v2OldPos.fY = GetPosY();
				SetPosX(GetPosX()+DX);
				SetPosY(GetPosY()+(Up.fY*GetVelY()*fDt));

				SetMoveUp(true);
				SetMoveDown(false);
			}
			else if(m_pDI->KeyDown(DIK_S) || m_pDI->JoystickDPadDown(DIR_DOWN) || m_pDI->JoystickGetRStickYAmount() > 0)
			{
				Up=Vector2DRotate(Up, m_fRotation);
				float DX=(Up.fX*GetVelX()*fDt);
				m_v2OldPos.fX = GetPosX();
				m_v2OldPos.fY = GetPosY();
				SetPosX(GetPosX()-DX);
				SetPosY(GetPosY()-(Up.fY*GetVelY()*fDt));

				SetMoveUp(false);
				SetMoveDown(true);
			}
			else
			{
				SetMoveUp(false);
				SetMoveDown(false);
			}
		}
		if(m_pDI->KeyDown(DIK_D) || m_pDI->JoystickDPadDown(DIR_RIGHT) || m_pDI->JoystickGetRStickXAmount() > 0)
		{
			m_fRotation+=m_fRotationRate*fDt;

			SetMoveRight(true);
			SetMoveLeft(false);
		}
		else if(m_pDI->KeyDown(DIK_A) || m_pDI->JoystickDPadDown(DIR_LEFT) || m_pDI->JoystickGetRStickXAmount() < 0)
		{
			m_fRotation-=m_fRotationRate*fDt;

			SetMoveRight(false);
			SetMoveLeft(true);
		}

		if((m_pDI->MouseButtonDown(0) || m_pDI->JoystickGetLTriggerAmount() > 0) && m_fFireTimer >= m_fTime)
		{
			if((m_pTurret->GetBullet() == BUL_SHELL && GetWeaponAmmoShell()> 0)||(m_pTurret->GetBullet() == BUL_ARTILLERY && GetWeaponAmmoArtillery()> 0)||(m_pTurret->GetBullet() == BUL_ROCKET && GetWeaponAmmoMissile()> 0)||m_bInfAmmo)
			{
				if(m_fNoReloadTimer == 0.0f)
				{			
						CCreateBulletMessage* msg=new CCreateBulletMessage(MSG_CREATEBULLET, m_pTurret->GetBullet(), m_pTurret);
						CMessageSystem::GetInstance()->SndMessage(msg);
						msg = nullptr;
						m_fFireTimer = 0.0f;
						CPlayer::GetInstance()->SetShotsFired(CPlayer::GetInstance()->GetShotsFired()+1);
				}
				else
				{
					CCreateBulletMessage* msg=new CCreateBulletMessage(MSG_CREATEBULLET, m_pTurret->GetBullet(), m_pTurret);
					CMessageSystem::GetInstance()->SndMessage(msg);
					msg = nullptr;
					m_fFireTimer = 0.0f;
					CPlayer::GetInstance()->SetShotsFired(CPlayer::GetInstance()->GetShotsFired()+1);
				}
			}
		}
		else
			m_fFireTimer += fDt;

		if(m_fNoReloadTimer > 0.0)
		{
			m_fNoReloadTimer -= fDt;
			m_fTime = 0.25f;
		}
		else
			m_fTime = 1.0;
		CGamePlayState* g = CGamePlayState::GetInstance();
		CSurvivalState* s = CSurvivalState::GetInstance();
		if(g->GetPaused() || s->GetPaused())
		{
			return;
		}
		if(!g->GetPaused() && !s->GetPaused())
		{
			if(m_pDI->MouseButtonDown(1) || m_pDI->JoystickGetRTriggerAmount() > 0)
			{
				switch(m_nSecondType)
				{
				case MACHINEGUN:
					{
						if(m_fFireRate >= 0.15f&&m_fHeat<100&&!m_bOverheat)
						{
							m_fFireRate = 0.0f;
							CCreateBulletMessage* msg=new CCreateBulletMessage(MSG_CREATEBULLET, BUL_MACHINEGUN, m_pTurret);
							CMessageSystem::GetInstance()->SndMessage(msg);
							msg = nullptr;
							if(m_bInfAmmo == false)
								m_fHeat+=3*m_fHeatModifier;
						}
						else
							m_fFireRate += fDt;
					}
					break;
				case LAZER:
					{
						if(m_fFireRate >= 0.02f&&m_fHeat<100&&!m_bOverheat)
						{
							m_fFireRate = 0.0f;
							CCreateBulletMessage* msg=new CCreateBulletMessage(MSG_CREATEBULLET, BUL_LASER, m_pTurret);
							CMessageSystem::GetInstance()->SndMessage(msg);
							msg = nullptr;
							if(m_bInfAmmo == false)
								m_fHeat+=1.0f*m_fHeatModifier;
						}
						else
						{
							m_fFireRate += fDt;

						}
					}
					break;
				case FLAME:
					{
						if(!m_bOverheat)
						{
							GetTurret()->GetFlamer()->ActivateEmitter();


							m_fHeat+=.4f*m_fHeatModifier;
							if(!SlowFlame)
							{
								CCreateBulletMessage* pMsg=new CCreateBulletMessage(MSG_CREATEBULLET, BUL_FLAME, m_pTurret);
								CMessageSystem::GetInstance()->SndMessage(pMsg);
								pMsg = nullptr;
								SlowFlame=true;
								if(m_bSoundPlaying == false && m_nFireSound != -1)
								{
									CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nFireSound,true);
									m_bSoundPlaying = true;
								}
							}
							else
							{

								SlowFlame=false;
							}
						}
					}
					break;
				}
				if(m_fHeat>100)
				{
					m_bOverheat=true;
					GetTurret()->GetFlamer()->DeactivateEmitter();

					if(CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(m_nFireSound) == true)
						CSGD_XAudio2::GetInstance()->SFXStopSound(m_nFireSound);

					m_bSoundPlaying = false;
				}
				if(m_bOverheat&&m_fOverheatTimer>=1.5f)
				{
					m_bOverheat=false;
					m_fOverheatTimer=0.0f;
				}
				else if(m_bOverheat&&m_fOverheatTimer<1.5f)
				{
					m_fOverheatTimer+=fDt;
				}
			}
			else if(m_pDI->MouseButtonReleased(1)|| m_pDI->JoystickGetRTriggerAmount() == 0)
			{
				if(m_nSecondType==FLAME)
				{
					GetTurret()->GetFlamer()->DeactivateEmitter();

					if(m_bSoundPlaying == true)
					{
						if(CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(m_nFireSound) == true)
							CSGD_XAudio2::GetInstance()->SFXStopSound(m_nFireSound);
					}
					m_bSoundPlaying = false;
				}
			}
			this;
			if(m_pDI->KeyPressed(DIK_1))
			{
				if(m_pSpec1!=nullptr)
				{
					m_pSelectedSpec=m_pSpec1;
					m_pSelectedSpecAmmo=0;
				}
			}
			if(m_pDI->KeyPressed(DIK_2))
			{
				if(m_pSpec2!=nullptr)
				{
					m_pSelectedSpec=m_pSpec2;
					m_pSelectedSpecAmmo=1;
				}
			}
			if((m_pDI->KeyPressed(DIK_SPACE) || m_pDI->JoystickButtonPressed(4)) && m_anSpecialammo[m_pSelectedSpecAmmo]>0)
			{
				if(m_pSelectedSpec!=nullptr)
				{
					if(m_pSelectedSpec->GetType() == NUKE && m_nNukeSound != -1)
						CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nNukeSound, false);

					m_pSelectedSpec->ActivateSpecial();
					m_anSpecialammo[m_pSelectedSpecAmmo]--;
				}
			}
			if(m_pDI->MouseWheelMovement()>0)
			{
				if(m_nGunSel==1&&m_bRocketAccess)
				{
					m_nGunSel=2;
					GetTurret()->SetBullet(BUL_ROCKET);
				}
				else if(m_nGunSel==1&&!m_bRocketAccess&&m_bArtilleryAccess)
				{
					m_nGunSel=3;
					GetTurret()->SetBullet(BUL_ARTILLERY);
				}
				else if(m_nGunSel==2&&m_bArtilleryAccess)
				{
					m_nGunSel=3;
					GetTurret()->SetBullet(BUL_ARTILLERY);
				}
				else if(m_nGunSel==2&&!m_bArtilleryAccess)
				{
					m_nGunSel=1;
					GetTurret()->SetBullet(BUL_SHELL);
				}
				else if(m_nGunSel==3)
				{
					m_nGunSel=1;
					GetTurret()->SetBullet(BUL_SHELL);
				}
				CGUI::GetInstance()->SetGunSelected(m_nGunSel);
			}
			else if(m_pDI->MouseWheelMovement()<0)
			{
				if(m_nGunSel==1&&m_bArtilleryAccess)
				{
					m_nGunSel=3;
					GetTurret()->SetBullet(BUL_ARTILLERY);
				}
				else if(m_nGunSel==1&&m_bRocketAccess&&!m_bArtilleryAccess)
				{
					m_nGunSel=2;
					GetTurret()->SetBullet(BUL_ROCKET);
				}
				else if(m_nGunSel==3&&m_bRocketAccess)
				{
					m_nGunSel=2;
					GetTurret()->SetBullet(BUL_ROCKET);
				}
				else if(m_nGunSel==3&&!m_bRocketAccess)
				{
					m_nGunSel=1;
					GetTurret()->SetBullet(BUL_SHELL);
				}
				else if(m_nGunSel==2)
				{
					m_nGunSel=1;
					GetTurret()->SetBullet(BUL_SHELL);
				}
				CGUI::GetInstance()->SetGunSelected(m_nGunSel);
			}
		}
		else
		{
			if(m_pDI->JoystickGetLStickYAmount() > 0)
			{
				m_bIsMoving = true;
			}
			else m_bIsMoving = false;

			if(m_pDI->JoystickGetLStickYAmount() == 0)
			{
				SetMoveUp(false);
				SetMoveDown(false);
			}

			if(Camera::GetInstance()->GetPlayerCannotMove() == false)
			{
				if(m_pDI->JoystickGetLStickYAmount() < 0)
				{
					Up=Vector2DRotate(Up, m_fRotation);
					float DX=(Up.fX*GetVelX()*fDt);
					m_v2OldPos.fX = GetPosX();
					m_v2OldPos.fY = GetPosY();
					SetPosX(GetPosX()+DX);
					SetPosY(GetPosY()+(Up.fY*GetVelY()*fDt));

					SetMoveUp(true);
					SetMoveDown(false);
				}
				else if(m_pDI->JoystickGetLStickYAmount() > 0)
				{
					Up=Vector2DRotate(Up, m_fRotation);
					float DX=(Up.fX*GetVelX()*fDt);
					m_v2OldPos.fX = GetPosX();
					m_v2OldPos.fY = GetPosY();
					SetPosX(GetPosX()-DX);
					SetPosY(GetPosY()-(Up.fY*GetVelY()*fDt));

					SetMoveUp(false);
					SetMoveDown(true);
				}
				else
				{
					SetMoveUp(false);
					SetMoveDown(false);
				}
			}
			if(m_pDI->JoystickGetLStickXAmount() > 0)
			{
				m_fRotation+=m_fRotationRate*fDt;

				SetMoveRight(true);
				SetMoveLeft(false);
			}
			else if(m_pDI->JoystickGetLStickXAmount() < 0)
			{
				m_fRotation-=m_fRotationRate*fDt;

				SetMoveRight(false);
				SetMoveLeft(true);
			}

			if(m_pDI->JoystickButtonDown(0) && m_fFireTimer >= m_fTime)
			{
				if((m_pTurret->GetBullet() == BUL_SHELL && GetWeaponAmmoShell()> 0)||(m_pTurret->GetBullet() == BUL_ARTILLERY && GetWeaponAmmoArtillery()> 0)||(m_pTurret->GetBullet() == BUL_ROCKET && GetWeaponAmmoMissile()> 0))
				{
					if(m_fNoReloadTimer == 0.0f)
					{			
						CCreateBulletMessage* msg=new CCreateBulletMessage(MSG_CREATEBULLET, m_pTurret->GetBullet(), m_pTurret);
						CMessageSystem::GetInstance()->SndMessage(msg);
						msg = nullptr;
						m_fFireTimer = 0.0f;
						CPlayer::GetInstance()->SetShotsFired(CPlayer::GetInstance()->GetShotsFired()+1);
					}
					else
					{
						CCreateBulletMessage* msg=new CCreateBulletMessage(MSG_CREATEBULLET, m_pTurret->GetBullet(), m_pTurret);
						CMessageSystem::GetInstance()->SndMessage(msg);
						msg = nullptr;
						m_fFireTimer = 0.0f;
						CPlayer::GetInstance()->SetShotsFired(CPlayer::GetInstance()->GetShotsFired()+1);
					}
				}
			}
			else
				m_fFireTimer += fDt;

			if(m_fNoReloadTimer > 0.0)
			{
				m_fNoReloadTimer -= fDt;
				m_fTime = 0.25f;
			}
			else
				m_fTime = 1.0;

			if(m_pDI->JoystickButtonDown(3))
			{
				switch(m_nSecondType)
				{
				case MACHINEGUN:
					{
						if(m_fFireRate >= 0.15f&&m_fHeat<100&&!m_bOverheat)
						{
							m_fFireRate = 0.0f;
							CCreateBulletMessage* msg=new CCreateBulletMessage(MSG_CREATEBULLET, BUL_MACHINEGUN, m_pTurret);
							CMessageSystem::GetInstance()->SndMessage(msg);
							msg = nullptr;
							if(m_bInfAmmo == false)
								m_fHeat+=3*m_fHeatModifier;
						}
						else
							m_fFireRate += fDt;
					}
					break;
				case LAZER:
					{
						if(m_fFireRate >= 0.02f&&m_fHeat<100&&!m_bOverheat)
						{
							m_fFireRate = 0.0f;
							CCreateBulletMessage* msg=new CCreateBulletMessage(MSG_CREATEBULLET, BUL_LASER, m_pTurret);
							CMessageSystem::GetInstance()->SndMessage(msg);
							msg = nullptr;
							if(m_bInfAmmo == false)
								m_fHeat+=1.0f*m_fHeatModifier;
						}
						else
						{
							m_fFireRate += fDt;

						}
					}
					break;
				case FLAME:
					{
						if(!m_bOverheat)
						{
							GetTurret()->GetFlamer()->ActivateEmitter();


							m_fHeat+=.4f*m_fHeatModifier;
							if(!SlowFlame)
							{
								CCreateBulletMessage* pMsg=new CCreateBulletMessage(MSG_CREATEBULLET, BUL_FLAME, m_pTurret);
								CMessageSystem::GetInstance()->SndMessage(pMsg);
								pMsg = nullptr;
								SlowFlame=true;
								if(m_bSoundPlaying == false && m_nFireSound != -1)
								{
									CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nFireSound,true);
									m_bSoundPlaying = true;
								}
							}
							else
							{

								SlowFlame=false;
							}
						}
					}
					break;
				}
				if(m_fHeat>100)
				{
					m_bOverheat=true;
					GetTurret()->GetFlamer()->DeactivateEmitter();

					if(CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(m_nFireSound) == true)
						CSGD_XAudio2::GetInstance()->SFXStopSound(m_nFireSound);

					m_bSoundPlaying = false;
				}
				if(m_bOverheat&&m_fOverheatTimer>=1.5f)
				{
					m_bOverheat=false;
					m_fOverheatTimer=0.0f;
				}
				else if(m_bOverheat&&m_fOverheatTimer<1.5f)
				{
					m_fOverheatTimer+=fDt;
				}
			}
			else if(m_pDI->MouseButtonReleased(1)|| m_pDI->JoystickGetRTriggerAmount() == 0)
			{
				if(m_nSecondType==FLAME)
				{
					GetTurret()->GetFlamer()->DeactivateEmitter();

					if(m_bSoundPlaying == true)
					{
						if(CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(m_nFireSound) == true)
							CSGD_XAudio2::GetInstance()->SFXStopSound(m_nFireSound);
					}
					m_bSoundPlaying = false;
				}
			}
			this;
			if(m_pDI->MouseButtonPressed(0))
			{
				if(m_pSpec1!=nullptr)
				{
					m_pSelectedSpec=m_pSpec1;
					m_pSelectedSpecAmmo=0;
				}
			}
			if(m_pDI->MouseButtonPressed(1))
			{
				if(m_pSpec2!=nullptr)
				{
					m_pSelectedSpec=m_pSpec2;
					m_pSelectedSpecAmmo=1;
				}
			}
			if(m_pDI->JoystickButtonPressed(1) && m_anSpecialammo[m_pSelectedSpecAmmo]>0)
			{
				if(m_pSelectedSpec!=nullptr)
				{
					if(m_pSelectedSpec->GetType() == NUKE && m_nNukeSound != -1)
						CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nNukeSound, false);

					m_pSelectedSpec->ActivateSpecial();
					m_anSpecialammo[m_pSelectedSpecAmmo]--;
				}
			}
			if(m_pDI->JoystickButtonPressed(2))
			{
				if(m_nGunSel==1&&m_bRocketAccess)
				{
					m_nGunSel=2;
					GetTurret()->SetBullet(BUL_ROCKET);
				}
				else if(m_nGunSel==1&&!m_bRocketAccess&&m_bArtilleryAccess)
				{
					m_nGunSel=3;
					GetTurret()->SetBullet(BUL_ARTILLERY);
				}
				else if(m_nGunSel==2&&m_bArtilleryAccess)
				{
					m_nGunSel=3;
					GetTurret()->SetBullet(BUL_ARTILLERY);
				}
				else if(m_nGunSel==2&&!m_bArtilleryAccess)
				{
					m_nGunSel=1;
					GetTurret()->SetBullet(BUL_SHELL);
				}
				else if(m_nGunSel==3)
				{
					m_nGunSel=1;
					GetTurret()->SetBullet(BUL_SHELL);
				}
				CGUI::GetInstance()->SetGunSelected(m_nGunSel);
			}
			else if(m_pDI->JoystickButtonPressed(5))
			{
				if(m_nGunSel==1&&m_bArtilleryAccess)
				{
					m_nGunSel=3;
					GetTurret()->SetBullet(BUL_ARTILLERY);
				}
				else if(m_nGunSel==1&&m_bRocketAccess&&!m_bArtilleryAccess)
				{
					m_nGunSel=2;
					GetTurret()->SetBullet(BUL_ROCKET);
				}
				else if(m_nGunSel==3&&m_bRocketAccess)
				{
					m_nGunSel=2;
					GetTurret()->SetBullet(BUL_ROCKET);
				}
				else if(m_nGunSel==3&&!m_bRocketAccess)
				{
					m_nGunSel=1;
					GetTurret()->SetBullet(BUL_SHELL);
				}
				else if(m_nGunSel==2)
				{
					m_nGunSel=1;
					GetTurret()->SetBullet(BUL_SHELL);
				}
				CGUI::GetInstance()->SetGunSelected(m_nGunSel);
			}
		}
	}

	Camera* C=Camera::GetInstance();
	m_pTurret->SetPosX(GetPosX());
	m_pTurret->SetPosY(GetPosY());
	if(GetPosX()-GetHeight()/2<0)
	{
		m_v2OldPos.fX = GetPosX();
		SetPosX((float)(GetHeight()/2));
	}
	if(GetPosY()-GetHeight()/2<0)
	{
		m_v2OldPos.fY = GetPosY();
		SetPosY((float)(GetHeight()/2));
	}
	CGame* game=CGame::GetInstance();
	if(GetPosX()+GetHeight()/2>game->GetWidth())
	{
		m_v2OldPos.fX = GetPosX();
		SetPosX(float(game->GetWidth()-GetHeight()/2));
	}
	if(GetPosY()+GetHeight()/2>game->GetHeight())
	{
		m_v2OldPos.fY = GetPosY();
		SetPosY(float(game->GetHeight()-GetHeight()/2));
	}

	if(abs(m_fRotation)>=6.28)
		m_fRotation=0;
	if(abs(m_fRotation)>=5.495)
	{
		m_fRotationHeight=128;
		m_fRotationWidth=64;
	}
	else if(abs(m_fRotation)>=3.925)
	{
		m_fRotationHeight=64;
		m_fRotationWidth=128;
	}
	else if(abs(m_fRotation)>=2.335)
	{
		m_fRotationHeight=128;
		m_fRotationWidth=64;
	}
	else if(abs(m_fRotation)>0.785)
	{
		m_fRotationHeight=64;
		m_fRotationWidth=128;
	}
	else if(abs(m_fRotation)<=0.785)
	{
		m_fRotationHeight=128;
		m_fRotationWidth=64;
	}

	if(m_fHeat>0&&!m_bOverheat)
	{
		m_fHeat-=0.1f;
	}
	else if(m_fHeat>0&&m_bOverheat)
	{
		m_fHeat-=.5;
	}
	if(m_fHeat<0)
		m_fHeat=0;

	if(m_bDoubleDamage == true)
		if(m_fDamageTime > 0.0f)
			m_fDamageTime-=fDt;
		else
			m_bDoubleDamage = false;

	if(m_bInfAmmo == true)
		if(m_fInfAmmoTimer > 0.0f)
			m_fInfAmmoTimer-=fDt;
		else
			m_bInfAmmo = false;

	if(GetInvul() == true)
		if(GetInvulTimer() > 0.0f)
		{
			float fTime = GetInvulTimer();
			fTime-=fDt;
			SetInvulTimer(fTime);
		}
		else
			SetInvul(false);
	tVector2D Look={0,-1};
	Look=Vector2DRotate(Look, m_fRotation);

	/*if(Look.fY>=-1&&Look.fY<=0&&Look.fX>=0&&Look.fX<=1)
	{
		m_pTracksLeft->UpdateEmitterPos((GetPosX()+((-45)*Look.fX)+(15*(Look.fY)))-C->GetPosX(), (GetPosY()+((-64)*Look.fY)+(10*(-Look.fX)))-C->GetPosY());
		m_pTracksLeft->UpdateRotation(m_fRotation);
		m_pTracksLeft->ActivateEmitter();

		m_pTracksRight->UpdateEmitterPos((GetPosX()+((-45)*Look.fX)+(30*(-Look.fY)))-C->GetPosX(), (GetPosY()+((-64)*Look.fY)+(30*(Look.fX)))-C->GetPosY());
		m_pTracksRight->UpdateRotation(m_fRotation);
		m_pTracksRight->ActivateEmitter();	
	}
	else
	{
		m_pTracksLeft->UpdateEmitterPos((GetPosX()+((-70)*Look.fX)+(37*(Look.fY)))-C->GetPosX(), (GetPosY()+((-45)*Look.fY)+(37*(-Look.fX)))-C->GetPosY());
		m_pTracksLeft->UpdateRotation(m_fRotation);
		m_pTracksLeft->ActivateEmitter();

		m_pTracksRight->UpdateEmitterPos((GetPosX()+((-70)*Look.fX)+(5*(-Look.fY)))-C->GetPosX(), (GetPosY()+((-45)*Look.fY)+(5*(Look.fX)))-C->GetPosY());
		m_pTracksRight->UpdateRotation(m_fRotation);
		m_pTracksRight->ActivateEmitter();
	}*/
	if(m_bSlowDown == true)
	{
		if(m_fSlowTimer > 0.0f)
			m_fSlowTimer -= fDt;
		else 
		{
			m_fSlowTimer = 0.0f;
			m_bSlowDown = false;
			SetVelX(m_fStartVelX);
			SetVelY(m_fStartVelY);
		}
	}
}

void CPlayer::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)(GetPosX()-GetWidth()/2), (int)(GetPosY()-GetHeight()/2),1.0f,1.0f,0,GetWidth()/2.0f,GetHeight()/2.0f,m_fRotation);
}

RECT CPlayer::GetRect(void)
{
	RECT rect;
	rect.top=(LONG)(GetPosY()-m_fRotationHeight/2);
	rect.left=(LONG)(GetPosX()-m_fRotationWidth/2);
	rect.bottom=(LONG)(GetPosY()+m_fRotationHeight/2);
	rect.right=(LONG)(GetPosX()+m_fRotationWidth/2);
	return rect;
}
RECT CPlayer::GetSpawnRect()
{
	Camera* C=Camera::GetInstance();
	RECT rect;
	rect.top=(LONG)((GetPosY())-GetHeight()/2);
	rect.left=(LONG)((GetPosX())-GetWidth()/2);
	rect.bottom=(LONG)((GetPosY())+GetHeight()/2);
	rect.right=(LONG)((GetPosX())+GetWidth()/2);
	return rect;
}

bool CPlayer::CheckCollision(IEntity* pBase)
{
	if(CEntity::CheckCollision(pBase) == true)
	{
		switch(pBase->GetType())
		{
		case OBJ_BASE:
			break;
		case OBJ_PLAYER:
			{
			}
			break;
		case OBJ_BULLET:
			{				
			}
			break;
		case OBJ_ENEMY:
			{
				/*CEnemy* pEnemy =dynamic_cast<CEnemy*>(pBase);
				CDestroyEnemyMessage* pMse = new CDestroyEnemyMessage(pEnemy);
				CMessageSystem::GetInstance()->SndMessage(pMse);
				pMse = nullptr;*/
			}
			break;
		case OBJ_PICKUP:
			{
			}
			break;
		case OBJ_BUILDING:
			{
				this->SetPosX(this->GetOldPos().fX);
				this->SetPosY(this->GetOldPos().fY);
				Camera *cam = Camera::GetInstance();

				cam->SetPosX(cam->GetOldPos().fX);
				cam->SetPosY(cam->GetOldPos().fY);
			}
			break;
		case OBJ_MINE:
			{
			}
			break;
		case OBJ_TANK:
			{
				if(CGame::GetInstance()->GetCurState()!= CTutorState::GetInstance())
				{
					CEnemy* pEnemy =dynamic_cast<CEnemy*>(pBase);

					pEnemy->SetPosX(pEnemy->GetOldPos().fX);
					pEnemy->SetPosY(pEnemy->GetOldPos().fY);

					this->SetPosX(this->GetOldPos().fX);
					this->SetPosY(this->GetOldPos().fY);
				}
			}
			break;
		case OBJ_TREE:
			{

			}
			break;
		case OBJ_NAZIBOSS:
			{
				CNaziBoss* pEnemy =dynamic_cast<CNaziBoss*>(pBase);

				pEnemy->SetPosX(pEnemy->GetOldPos().fX);
				pEnemy->SetPosY(pEnemy->GetOldPos().fY);

				this->SetPosX(this->GetOldPos().fX);
				this->SetPosY(this->GetOldPos().fY);
				if(pEnemy->GetState()==2)
				{
					if(pEnemy->GetCharging())
					{
						pEnemy->SetCollision();
						this->TakeDamage(50);
						m_nDamageTaken+=50;
					}
				}
			}
			break;
		case OBJ_FACTORY:
			{
				Camera *cam = Camera::GetInstance();
				Factory* pEnemy =dynamic_cast<Factory*>(pBase);

				pEnemy->SetPosX(pEnemy->GetOldPos().fX);
				pEnemy->SetPosY(pEnemy->GetOldPos().fY);
				cam->SetPosX(cam->GetOldPos().fX);
				cam->SetPosY(cam->GetOldPos().fY);

				this->SetPosX(this->GetOldPos().fX);
				this->SetPosY(this->GetOldPos().fY);
			}
			break;
		}
		return true;
	}
	else
		return false;
}

CPlayer::CPlayer(void)
{
	m_pDI=CSGD_DirectInput::GetInstance();
	m_fRotationRate=1.5f;
	m_nType=OBJ_PLAYER;

	m_bIsMoving		= false;
	m_bMoveRight	= false;
	m_bMoveLeft		= false;
	m_bMoveUp		= false;
	m_bMoveDown		= false;
	m_bOverheat		= false;

	m_bSlowDown		= false;
	m_fSlowTimer = 0.0f;

	m_fHeatModifier	= 1;
	m_nHeatLevel	= 1;
	m_fDamageMod	= 1;
	m_nDamageLevel	= 1;
	m_fAmmoMod		= 1;
	m_nAmmoLevel	= 1;
	m_fHealthMod	= 1;
	m_nHealthLevel	= 1;
	m_fArmorMod		= 1;
	m_nArmorLevel	= 1;
	m_fSpeedMod		= 1;
	m_nSpeedLevel	= 1;
	m_nNukeSound = -1;


	m_nFireSound = -1;
	m_bSoundPlaying = false;


	m_fHeatModifier = CShopState::GetInstance()->GetHeat();

	m_fFireRate = 0.0f;
	m_fHeat=0.0f;
	m_fOverheatTimer=0.0f;
	m_fTime=1.0f;
	m_fFireTimer=m_fTime;	
	m_fNoReloadTimer=0.0f;
	m_bDoubleDamage = false;
	m_fDamageTime = 0.0f;
	m_bInfAmmo = false;
	m_fInfAmmoTimer = 0.0f;

	m_bRocketAccess		= false;
	m_bLaserAccess		= false;
	m_bNukeAccess		= false;
	m_bEMPAccess		= false;
	m_bArtilleryAccess	= false;
	m_bFlamerAccess		= false;
	m_bAirStrikeAccess	= false;
	m_bSmokeBombAccess	= false;
	SlowFlame			= false;

	m_pSelectedSpec=m_pSpec1;
	m_pSelectedSpecAmmo=0;
	m_nNukesBlasted		= 0;
	m_nScore			= 0;
	m_nShotsFired		= 0;
	m_nDamageTaken		= 0;
	m_nTotalMoneyEarned	= 0;
	m_nUnitsKilled		= 0;
	m_nSappersExploded	= 0; 
	m_nDamageTaken = 0;
	m_bNaziBoss			= false;	
	m_bAlienBoss		= false;
	m_bRobotBoss		= false;
	m_bSparta			= false;
	m_bSapperAbsorb		= false;
	m_bNukem			= false;
	m_bIamBoss			= false;
	m_bAllUpgrades		= false;

	m_nGunSel=1;
}

CPlayer::~CPlayer(void)
{
}

void CPlayer::SlowVel(float time, float vel)
{
	m_bSlowDown = true;
	m_fSlowTimer = time;
	SetVelX(vel);
	SetVelY(vel);
}
