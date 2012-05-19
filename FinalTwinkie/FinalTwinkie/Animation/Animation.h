#ifndef ANIMATION_H
#define ANIMATION_H
#include <vector>
#include <string>
#include "Frame.h"
class CAnimation
{
	
public:
	CAnimation(void);
	~CAnimation(void);

	void Update(float fDt);
	void Render();

	float	GetScale() const { return m_fScale; }
	void	SetScale(float val) { m_fScale = val; }

	int		GetImageID() const { return m_nImageID; }
	void	SetImageID(int val) { m_nImageID = val; }

	bool	GetIsAnimating() const { return m_bIsAnimating; }
	void	SetIsAnimating(bool val) { m_bIsAnimating = val; }

	bool	GetIsLooping() const { return m_bIsLooping; }
	void	SetIsLooping(bool val) { m_bIsLooping = val; }

	std::string GetFilename() const { return m_sFilename; }
	void		SetFilename(std::string val) { m_sFilename = val; }

	
/*
	std::vector<CFrame*> GetAnimationFrame() const { return m_pAnimation; }
	void SetAnimationFrame(std::vector<CFrame*> val) { m_pAnimation = val; }
*/

private:

	float m_fScale;
	int m_nImageID;
	bool m_bIsAnimating;
	bool m_bIsLooping;

	enum Mode  { LOOPING, IDLE, OSCILLATE, BACKWARD};
	std::string m_sFilename;

	


};
#endif
