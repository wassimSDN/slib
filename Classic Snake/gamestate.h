#include <vector>

#include <slib.h>

using namespace slib;

#define nbrCells 25
#define windowSize 500
#define sizeCells ((float)windowSize/(float)nbrCells)
#define startSize 0
#define MIN 1
#define MAX (nbrCells - 2)

namespace SnakeGame
{
	class GameState : public Events
	{
	public:
		GameState();
		~GameState();
		Window window;

		Texture txtTarget;
		RectangleReal posTarget = { 0, 0, windowSize, windowSize };

	private:	
		RectangleReal cells[nbrCells][nbrCells];
		bool init();
	};

	enum SnakeDirection
	{
		DIRECTION_NONE = 1,
		DIRECTION_LEFT = -90,
		DIRECTION_RIGHT = 90,
		DIRECTION_UP = 0,
		DIRECTION_DOWN = 180
	};

	class Snake : public Events
	{	
	public:
		Snake();
		~Snake();
		void init();
		void update();
		void fixedUpdate();
		void draw(RectangleReal cells[nbrCells][nbrCells]);
	private:
		Texture txt;
		Text score;
		Text highScoreText;
		std::vector<std::pair<int, int>> body;
		std::pair<int, int> foodPos;
		SnakeDirection direction;
		bool foodEaten = true;
		bool lost = false;
		SoundEffect scoreSound = "soundEffect.wav";
		SoundEffect losingSound = "lost.wav";
		Music jazz = "snakeJazz.mp3";
		int highScore = 0;
		float angle = 0;
		bool changedDirection = false;;
	};
}
