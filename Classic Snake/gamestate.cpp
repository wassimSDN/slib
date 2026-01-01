#include <ctime>

#include "gamestate.h"

namespace SnakeGame
{
	GameState::GameState()
	{
		Events e;
		e.setTicks(10);
		window.createWindow("Snake Game", windowSize, windowSize, WindowFlags::centered, WindowFlags::centered, WindowFlags::resizable);

		if(!init())
			return;
		
		Snake player;

		while (true)
		{
			e.updateEvents();
			if (e.shouldQuit())
				break;
			while (e.ticking())
			{
				player.fixedUpdate();
				e.reduceAccumulatedTime();
			}

			if (e.isResized())
			{
				int w, h;
				window.getSize(&w, &h);

				float windowRatio = (float)w / (float)h;
				float textureRatio = (float)windowSize / (float)windowSize;
				

				if (windowRatio > textureRatio)
				{
					posTarget.setDimensions(h * textureRatio, h);
					float windowMiddleX = w / 2;
					float x = windowMiddleX - posTarget.get().w / 2;
					posTarget.setX(x);
					posTarget.setY(0);
				}
				else if(windowRatio < textureRatio)
				{
					posTarget.setDimensions(w, w / textureRatio);
					float windowMiddleY = h / 2;
					float y = windowMiddleY - posTarget.get().h / 2;
					posTarget.setX(0);
					posTarget.setY(y);
				}
				else if (false)
				{
					posTarget.setDimensions(w, h);
					posTarget.setPos(0, 0);
				}
			}
			
			player.update();
			
			window.setClearColor(BLACK);
			window.clear();
			window.setRenderTarget(txtTarget);
			window.setClearColor(CORN);
			window.clear();
		   
			for (int i = 0; i < nbrCells && isKeyDown(Keys::space); i++)
				for (int j = 0; j < nbrCells && isKeyDown(Keys::space); j++)
					cells[i][j].draw();

			player.draw(cells);

			window.resetRenderTarget();
			txtTarget.drawReal(nullptr, posTarget);
			window.flip();

			SDL_Delay(1);
		}
	}

	bool GameState::init()
	{
		srand(time(nullptr));

		txtTarget.createTextureAsTarget(500, 500);
		if (!txtTarget.isCreated())
			return false;

		for (int i = 0; i < nbrCells; i++)
		{
			for (int j = 0; j < nbrCells; j++)
			{
				cells[i][j].setDimensions(sizeCells, sizeCells);
				cells[i][j].setPos(i * sizeCells, j * sizeCells);
			}
		}

		return true;
	}

	Snake::Snake()
	{
		txt.loadTexture("snake.png");
		if (!txt.isCreated())
			return;

		FILE* scoreFile;
		fopen_s(&scoreFile, "scoreFile", "rb");
		if (scoreFile)
		{
			fread(&highScore, sizeof(int), 1, scoreFile);
			fclose(scoreFile);
		}

		score.createText("", 100);
		highScoreText.createText("", 30);

		init();
		jazz.play();
		jazz.pause();
	}

	Snake::~Snake()
	{
		FILE* scoreFile;
		fopen_s(&scoreFile, "scoreFile", "wb");
		if (scoreFile)
		{
			fwrite(&highScore, sizeof(int), 1, scoreFile);
			fclose(scoreFile);
		}
	}

	void Snake::init()
	{
		body.clear();

		body.push_back(std::pair<int, int>(nbrCells / 2, nbrCells / 2));
		
		setTicks((body.size() - 1) / 4 + 10);
		highScoreText.setText("high score: " + std::to_string(highScore));
		highScoreText.changeColor({ 0, 50, 200, 128 });
		score.setText("0");
		score.changeColor({ 0, 50, 200, 128 });

		angle = 0;
		changedDirection = false;
		direction = DIRECTION_NONE;

		std::pair <int, int> randomFoodPos;
		do
		{
			randomFoodPos = { rand() % (MAX - MIN + 1) + MIN , rand() % (MAX - MIN + 1) + MIN };
		} 
		while (std::find(body.begin(), body.end(), randomFoodPos) != body.end());

		foodPos = randomFoodPos;
	}

	void Snake::update()
	{
		if (isKeyJustDown(Keys::m))
			jazz.toggle();
		if(!changedDirection)
		{
			if (isKeyJustDown(Keys::left) || isKeyJustDown(Keys::a))
			{
				if (direction != DIRECTION_RIGHT)
				{
					angle = direction = DIRECTION_LEFT;
					changedDirection = true;
				}
			}
			else if (isKeyJustDown(Keys::up) || isKeyJustDown(Keys::w))
			{
				if (direction != DIRECTION_DOWN)
				{
					angle = direction = DIRECTION_UP;
					changedDirection = true;
				}
			}
			else if (isKeyJustDown(Keys::right) || isKeyJustDown(Keys::d))
			{
				if (direction != DIRECTION_LEFT)
				{
					angle = direction = DIRECTION_RIGHT;
					changedDirection = true;
				}
			}
			else if (isKeyJustDown(Keys::down) || isKeyJustDown(Keys::s))
			{
				if (direction != DIRECTION_UP)
				{
					angle = direction = DIRECTION_DOWN;
					changedDirection = true;
				}
			}
		}

		if (isKeyJustDown(Keys::escape))
		{	
			lost = false;	
			direction = DIRECTION_NONE;
		}

		if (body[0] == foodPos)
		{
			body.push_back({ -1, -1 });
			setTicks((body.size() - 1) / 4 + 10);
			scoreSound.play();

			std::pair <int, int> randomFoodPos;
			do
			{
				randomFoodPos = { rand() % (MAX - MIN + 1) + MIN , rand() % (MAX - MIN + 1) + MIN };
			} 
			while (std::find(body.begin(), body.end(), randomFoodPos) != body.end());

			foodPos = randomFoodPos;
			score.setText(std::to_string(body.size() - 1 - startSize));
		}
	}

	void Snake::fixedUpdate()
	{
		changedDirection = false;
		if (direction != DIRECTION_NONE)
			for (int i = body.size() - 1; i > 0; i--)
				body[i] = body[i - 1];
			
		switch (direction)
		{
		case DIRECTION_LEFT:
				body[0].first--;
			break;

		case DIRECTION_RIGHT:
				body[0].first++;
			break;

		case DIRECTION_UP:
				body[0].second--;
			break;

		case DIRECTION_DOWN:
				body[0].second++;
			break;

		case DIRECTION_NONE:
			break;
		}
		
		bool touchedSelf = std::find(body.begin() + 1, body.end(), body[0]) != body.end();
		if (body[0].second < 0 || body[0].second > nbrCells - 1 || body[0].first< 0 || body[0].first > nbrCells - 1 || touchedSelf)
		{
			if (body.size() - 1 > highScore)
				highScore = body.size() - 1 - startSize;

			losingSound.play();
			init();
		}
	}

	void Snake::draw(RectangleReal cells[nbrCells][nbrCells])
	{
		const Rectangle headSrc = { 0, 0, 32, 32 };
		const Rectangle bodySrc = { 32, 0, 32, 32 };
		const Rectangle foodSrc = { 32, 32, 32, 32 };
		
		const Vector2 textPos = { (float)windowSize / 2.0f - (float)score.getW() / 2.0f, (float)windowSize / 2.0f - (float)score.getH() / 2.0f };
		score.draw(textPos);
		
		for (auto &it : body)
			txt.drawReal(bodySrc, cells[it.first][it.second]);

		txt.drawAngleCenterReal(headSrc, cells[body[0].first][body[0].second], angle);
		txt.drawReal(foodSrc, cells[foodPos.first][foodPos.second]);
		highScoreText.draw({ 20, 20 });
	}
}