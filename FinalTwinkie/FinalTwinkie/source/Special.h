#ifndef CSPECIAL_H_
#define CSPECIAL_H_

enum SpecialType{SMOKE,EMP,NUKE,REINFORCEAIRSTRIKE  };

class CSpecial
{
public:
	CSpecial(void);
	~CSpecial(void);

	void Update(float fDt);
	void Render(void);
	void ActivateSpecial(void);

private:
	int m_nType;
	int m_nAmmo;
	float m_fDuration;
};


#endif

