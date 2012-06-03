#ifndef CSPECIAL_H_
#define CSPECIAL_H_

enum SpecialType{SPECIAL,SMOKE,EMP,NUKE,REINFORCE,AIRSTRIKE };

class CSpecial
{
public:
	CSpecial(void);
	~CSpecial(void);

	virtual void Update(float fDt);
	virtual void Render(void);
	virtual void ActivateSpecial(void);

	int GetType(void){return m_nType;}
	void SetType(int Type){m_nType=Type;}

protected:
	int		m_nAmmo;
	float	m_fDuration;
	int		m_nType;
};


#endif

