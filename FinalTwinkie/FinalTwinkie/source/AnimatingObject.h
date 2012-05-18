#pragma once
class CAnimInfo;
class CAnimatingObject
{
public:
	CAnimatingObject(void);
	~CAnimatingObject(void);
	
	void Init();
	void Update();

private:

	CAnimInfo* m_pCurrAnim;

	enum m_eAnimate {DOSTUFF};

};

