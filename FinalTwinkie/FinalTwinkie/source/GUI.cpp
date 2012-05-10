#include "GUI.h"

CGUI* CGUI::m_pSelf = nullptr;

CGUI* CGUI::GetInstance(void)
{
	if(m_pSelf == nullptr)
		m_pSelf = new CGUI();
	return m_pSelf;
}
void CGUI::DeleteInstance(void)
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}


CGUI::CGUI(void)
{
}


CGUI::~CGUI(void)
{
}
