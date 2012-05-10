#ifndef FLYTEXT_H
#define FLYTEXT_H
#include "Entity.h"
#include <string>
class CFlyText:public CEntity
{
public:
	virtual void Update(float);
	virtual void Render(void);
	virtual int GetType(void) { return m_nType; }
	CFlyText(void);
	~CFlyText(void);

private:
	std::string m_szType;
	float m_fTimer;
	DWORD m_DWColor;
};
#endif