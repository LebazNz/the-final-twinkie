#pragma once
#include <string>

class CAnimation;
class CAnimatingObject;

class CAnimInfo
{
	

public:
	CAnimInfo(void);
	~CAnimInfo(void);

	void	RegisterObject(CAnimatingObject* AO);
	void	RegisterAnimation(std::string filename);

	void	Play(int enu);


	int		GetCurrFrame() const { return m_nCurrFrame; }
	void	SetCurrFrame(int val) { m_nCurrFrame = val; }
	float	GetAnimationSpeed() const { return m_fAnimationSpeed; }
	void	SetAnimationSpeed(float val) { m_fAnimationSpeed = val; }
	
private:
	int m_nCurrFrame;
	CAnimation* m_pCurrAnimation;
	float m_fAnimationSpeed;
	
};

