#ifndef ANIMANG_H
#define ANIMANG_H
#include <string>
#include "Animation.h"
class CAnimationVault;
class CFrame;
class CAnimationManager
{
public:

	static CAnimationManager* GetInstance();
	int temp;
	int animframe;
	void Update(float fDt);
	void Load(const char* szFile);
	void Unload();
	void Render();
	void StartAnimation(int nID);
	void StopAnimation(int nID);
	void PauseAnimation(int nID);
	void AddAnimation(CAnimation* pAnimation);
	void AddFrame(int nX, int nY, int nWidth, int nHeight, int nAnchorX, int nAnchorY, float fFrameTime);
	//void AddCollisionRect(int nX, int nY, int nWidth, int nHeight);
	void Save(const char* szFile);
private:

	CAnimationVault* m_pAV;
	std::vector<CFrame*> m_vpFrame;

	CAnimationManager(void);
	~CAnimationManager(void);
	CAnimationManager(const CAnimationManager&);
	CAnimationManager& operator =(const CAnimationManager&);
};

#endif