#ifndef FLYTEXT_H
#define FLYTEXT_H
#include "../GameObjects/Entity.h"
#include "../GameObjects/Player.h"
#include "BitmapFont.h"
#include <string>
class CFlyText:public CEntity
{
public:
	virtual void Update(float);
	virtual void Render(void);
	virtual int GetType(void) { return m_nType; }
	CFlyText(void);
	~CFlyText(void);

	void SetFlyText(int nType, float fTimer, DWORD dColor, float fX, float fY);

private:
	std::string m_szType;
	float		m_fTimer;
	DWORD		m_DWColor;
};
#endif