#include <vector>
#include <algorithm>

#include <slib.h>
using namespace slib;




int WinMain()
{
	Events e;
	e.setTicks(100);
	
	Window wind("Chess Idea", 172, 172, 500, 500, hidden | resizable);
	Window wind2("Chesss Idea", 172, 172, 700, 500, resizable);
	Texture board = "Simple_Chess_by_skyel/Board/spr_board_with_border_02.png";
	Texture piece;
	RectangleReal piecePos;
	Text t;

	{
		Surface sur = "Simple_Chess_by_skyel/Black Pieces/spr_bishop_black.png";
		piece.createTexture(sur);
		int w;
		int h;
		sur.getDimensions(w, h);
		piecePos = { 50, 50, (float) w, (float) h};
		t.setText(std::to_string(w) + ' ' + std::to_string(h) + " YES");
	}

	Texture target;
	target.createTextureAsTarget(172, 172);
	
	
	Rectangle targetPos = { 0, 0, 172, 172 };



	wind.show();
	while (!e.shouldQuit())
	{
		e.updateEvents();
		while (e.ticking())
		{

			e.reduceAccumulatedTime();
		}
		
		if (e.isResized())
		{
			int w;
			int h;
			wind.getSize(&w, &h);


		
		}
		

		wind.setRenderTarget(target);
		wind.clear();

		board.draw();
		piece.drawReal(nullptr, piecePos);
		t.draw({ 50, 50 });
		
		wind.resetRenderTarget();
		target.draw();// (nullptr, targetPos);
		wind.flip();


		SDL_Delay(1);
	}

	return 0;
}

