#pragma once
#include <string>
class PlayerScores
{
public:
	PlayerScores(void);
	~PlayerScores(void);
	std::string GetName() const { return m_nName; }
	void		SetName(std::string val) { m_nName = val; }
	int			GetScore() const { return m_nScore; }
	void		SetScore(int val) { m_nScore = val; }
private:
	int m_nScore;
	std::string m_nName;
};

