#ifndef FANTASYFIGHT_GAME_H
#define FANTASYFIGHT_GAME_H


//forward declaration
class Team;
class Arbiter;

class Game
{

public:
	enum TeamEnum
	{
		LEFT = 0,
		RIGHT,
		COUNT_TEAMS,
	};

private:
	//members
	Team*		m_teams[TeamEnum::COUNT_TEAMS];
	Arbiter*	m_arbiter;

	//singleton
	static Game* m_gameInstance;
	//ctors, dtor and = are private: you MUST use getInstance()
	Game();
	Game(const Game& otherGame);
	~Game();
	Game& operator=(const Game& otherGame);

	Team*		createTeam(bool autoCreate);
	Arbiter*	createArbiter();

public:
	//singleton accessors
	static Game* getInstance();

	Team* getTeam(TeamEnum teamNum) const;
	Team* getEnemyTeam(TeamEnum teamNum) const;

	void startGame();
};

#endif