#ifndef __SCORE_H_
#define __SCORE_H_

#include "Text.h"


class Score
{
public:
	Score();
	virtual ~Score();

	void create(unsigned int);
	void draw();
	void updateScore();
	

public:
	inline void setScore(int score) {
		this->score += score;
	}

	inline int getScore() {
		return score;
	}


private:
	Resource* fontRes = nullptr;
	Text* textS = nullptr;
	Text* textC = nullptr;
	Text* textO = nullptr;
	Text* textR = nullptr;
	Text* textE = nullptr;
	Text* textDotDot = nullptr;

	Text* digit1 = nullptr;
	Text* digit2 = nullptr;

	int score = 0;
};

#endif /* SCORE_H_ */
