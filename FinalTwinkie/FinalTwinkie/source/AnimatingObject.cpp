#include "AnimatingObject.h"
#include "AnimInfo.h"

CAnimatingObject::CAnimatingObject(void)
{
}


CAnimatingObject::~CAnimatingObject(void)
{
}

void CAnimatingObject::Init()
{
	m_pCurrAnim->RegisterObject(this);
	m_pCurrAnim->RegisterAnimation("HELLO");
}

void CAnimatingObject::Update()
{
	m_pCurrAnim->Play(DOSTUFF);
}
