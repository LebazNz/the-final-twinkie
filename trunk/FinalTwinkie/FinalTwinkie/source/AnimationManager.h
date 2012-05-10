#ifndef ANIMANG_H
#define ANIMANG_H
#include <string>
#include "Animation.h"
class CAnimationManager
{
public:
	CAnimationManager(void);
	~CAnimationManager(void);

	void Update(float fDt);
	void Load(std::string szFile);
	void Unload();
	void Render();
	void StartAnimation(int nID);
	void StopAnimation(int nID);
	void PauseAnimation(int nID);
	int AddAnimation(CAnimation* pAnimation);
};

#endif