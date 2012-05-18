#pragma once
#include <vector>
class CAnimation;
class CAnimationVault
{
	
	
public:
	std::vector<CAnimation*> m_vAnimationList;
	CAnimationVault(void);
	~CAnimationVault(void);
};

