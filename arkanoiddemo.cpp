#include <SDL.h>
#include <EGL/egl.h>
#include<vector>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <sstream>
#include <GLES/gl.h>
#include<string>
#include <SDL2/SDL.h>

/*         Copyright (c) <2017> <arkanoid>.
All rights reserved.

Redistribution and use in source and binary forms are permitted
provided that the above copyright notice and this paragraph are
duplicated in all such forms and that any documentation,
advertising materials, and other materials related to such
distribution and use acknowledge that the software was developed
by the notepadpl. The name of the
notepadpl may not be used to endorse or promote products derived
from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
         BSD_licenses                           */
                                    
   /*     global varible int ff[][] is map game        */
int ff[12][11] = {

	1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1,

	1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0,

	0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0,

	1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0,

	1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0,

	0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1,

	1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0,

	1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0,

	0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0,

	1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0,

	1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0,

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

};
/*struct bouncingBall*/
struct kulka
{
	int a;
	int b;
	int r;
} ball =
{
100, 300, 20}, wall =

{
1, 1}, speed =

{
3, 4}, quad;

SDL_Rect enemy;
SDL_Window *win = NULL;

SDL_Renderer *renderer = NULL;

SDL_Texture *bitmapTex = NULL;

SDL_Surface *surface;
SDL_Surface *kursor = NULL;
SDL_Surface *przycisk = NULL;	/* area exit */
SDL_Rect przyciskDane;
SDL_Rect przyciskCel;			/* arena start */
SDL_Rect startButonW;
SDL_Rect startButonH;			/* rect of player and ball */

SDL_Rect rect, darea;
SDL_Rect hit;
SDL_Rect shot;					/* mouse postion */
SDL_Rect kursorDane;			/* suirface */
SDL_Surface *bitmapSurface = NULL;
SDL_Event event;

/* exit */

void triangle(SDL_Renderer * renderer)
{
	int a;

	przyciskDane.w = 150;
	przyciskDane.h = 50;
	przyciskCel.x = 0;
	przyciskCel.y = 0;

	SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);	/* E */
	SDL_RenderDrawLine(renderer, 0, 0, 50, 0);
	SDL_RenderDrawLine(renderer, 0, 25, 25, 25);

	SDL_RenderDrawLine(renderer, 0, 50, 50, 50);

	SDL_RenderDrawLine(renderer, 0, 0, 0, 50);	/* X */

	SDL_RenderDrawLine(renderer, 50, 0, 100, 50);

	SDL_RenderDrawLine(renderer, 100, 0, 50, 50);	/* I */
	SDL_RenderDrawLine(renderer, 100, 0, 100, 50);	/* T */
	SDL_RenderDrawLine(renderer, 100, 0, 150, 0);

	SDL_RenderDrawLine(renderer, 125, 0, 125, 50);

}

/* COLISION ALGORYTM */


/* colision rectangle and vector rectangle */
bool CheckCollision(SDL_Rect A, std::vector < SDL_Rect > B)
{
	int cX, cY;
	for (int Bbox = 0; Bbox < B.size(); Bbox++)
		if (A.x > B[Bbox].x + B[Bbox].w)
		{
			return false;
		}
		else if (A.y > B[Bbox].y + B[Bbox].h)
		{
			return false;
		}
		else if (A.x + A.w < B[Bbox].x)
		{
			return false;
		}
		else if (A.y + A.h < B[Bbox].y)
		{
			return false;
		}

		else
		{
			return speed.b = -3;

		}
}

/* colision rerctangle and rectangle (ball and player) */
bool CheckCollision(SDL_Rect r1, SDL_Rect r2)
{
	if (r1.x > r2.x + r2.w)
	{
		return false;
	}
	else if (r1.y > r2.y + r2.h)
	{
		return false;
	}
	else if (r1.x + r1.w < r2.x)
	{
		return false;
	}
	else if (r1.y + r1.h < r2.y)
	{
		return false;
	}

	else
	{
		return speed.b = -3;
	}
}



/* colision rerctangle and rectangle (ball and player) */
bool CheckCollision(SDL_Rect r1, SDL_Rect * r2)
{
	if (r2->x > r1.x + r1.w)
	{
		return false;
	}
	else if (r2->y > r1.y + r1.h)
	{
		return false;
	}
	else if (r2->x + r2->w < r1.x)
	{
		return false;
	}
	else if (r2->y + r2->h < r1.y)
	{
		return false;
	}

	else
	{
		return speed.b = 3;
	}
}

/* End of colision algoritm */

void start(SDL_Renderer * renderer)
{
	/*START*/ int a;
	startButonW.w = 225;
	startButonW.h = 150;
	startButonH.x = 0;
	startButonH.y = 100;

	SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);	/* S */
	SDL_RenderDrawLine(renderer, 0, 100, 50, 100);

	SDL_RenderDrawLine(renderer, 0, 100, 0, 125);
	SDL_RenderDrawLine(renderer, 0, 125, 50, 125);

	SDL_RenderDrawLine(renderer, 0, 150, 50, 150);

	SDL_RenderDrawLine(renderer, 50, 125, 50, 150);	/* T */
	SDL_RenderDrawLine(renderer, 50, 100, 100, 100);

	SDL_RenderDrawLine(renderer, 75, 100, 75, 150);	/* A */

	SDL_RenderDrawLine(renderer, 100, 150, 125, 100);

	SDL_RenderDrawLine(renderer, 125, 100, 150, 150);	/* R */
	SDL_RenderDrawLine(renderer, 150, 150, 150, 100);

	SDL_RenderDrawLine(renderer, 150, 100, 175, 100);
	SDL_RenderDrawLine(renderer, 175, 100, 175, 125);

	SDL_RenderDrawLine(renderer, 175, 125, 150, 125);

	SDL_RenderDrawLine(renderer, 150, 125, 175, 150);	/* T */
	SDL_RenderDrawLine(renderer, 175, 100, 225, 100);

	SDL_RenderDrawLine(renderer, 200, 100, 200, 150);

}

void line(SDL_Renderer * renderer)
{								/* draw kursor mouse */

	SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, kursorDane.x, kursorDane.y, kursorDane.x + 100,
					   kursorDane.y + 100);

}

void bal(SDL_Renderer * renderer)
{
	/* this func rycle rectangle BALL in postion shot.x shot.y and width higth */

	/* Get the Size of drawing surface */

	SDL_RenderGetViewport(renderer, &darea);
	/* color */
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF);

	shot.w = 10;

	shot.h = 10;
	/* ball = shot rectangle */
	shot.x = ball.a;

	shot.y = ball.b;
	/* colsion ball with wall */

	if (ball.a > 200)
	{
		--speed.a;
	}
	if (ball.b > 400)
	{
		--speed.b;
	}
	if (ball.b < 0)
	{
		speed.b++;
	}
	if (ball.a < 0)
	{
		speed.a++;
	}

	/* draw ball */
	SDL_RenderFillRect(renderer, &shot);

}

void player(SDL_Renderer * renderer)
{
	/* this func draw rectangle of PLAYER in post hit.x hit.y and width 50 height 10 */

	/* Get the Size of drawing surface */ SDL_RenderGetViewport(renderer, &darea);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF);

	hit.w = 50;

	hit.h = 10;

	hit.x = kursorDane.x;

	hit.y = 300;
	

	SDL_RenderFillRect(renderer, &hit);
	/* check collision with ball and player */
	CheckCollision(shot, hit);

}

void drawEnemy(SDL_Renderer * render)
{
	int i, j, lx = 0, ly = 0, ch;
	SDL_RenderGetViewport(renderer, &darea);
	SDL_Rect egl;
	/* i need two rect one statistic in postion 0 0 and sec. rect to draw enemy */
	SDL_Rect enemy;
/*rect egl is  LEVER  to draw enemy*/
	egl.x = 0;
	egl.y = 0;
	egl.w = 5;
	egl.h = 5;
/*rect enemy */
	enemy.x = lx;
	enemy.y = ly;
	enemy.w = lx + 16;
	enemy.h = ly + 9;
	/* form the word BRICKS */
	SDL_RenderFillRect(renderer, &enemy);
	/*draw chessboard*/
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 11; j++)
		{
/*if ff =1 then draw rect enemy*/
			if (ff[i][j] == 1)
			{
				enemy.x = egl.x + j * 20 + 1;
				enemy.y = egl.y + i * 12 + 1;

				SDL_RenderFillRect(renderer, &enemy);
			}
/*if colision don't draw enemy rect */
			if (CheckCollision(shot, &enemy))
			{
				/*maping from global int ff, DELETE this*/
				ff[i][j] = 0;
			}


		}
	}
}

int main(int argc, char *argv[])
{
	/*menu "system" event tzn. if weed is draw engine game if not draw menu*/
	bool trafka = false;
	/*postion player x*/
kursorDane.x=100;
	SDL_Init(SDL_INIT_EVERYTHING);
	/*varible for window*/
	int posX = 100, posY = 100, width = 320, height = 240;

	SDL_RenderFillRect(renderer, &rect);

	// SDL_Init(SDL_INIT_VIDEO);

	win = SDL_CreateWindow("Hello World", posX, posY, width, height, SDL_WINDOW_OPENGL);

	surface = SDL_GetWindowSurface(win);

	renderer = SDL_CreateSoftwareRenderer(surface);

	SDL_RenderGetViewport(renderer, &darea);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF);
	bitmapSurface = SDL_LoadBMP("src/moon-220.bmp");

	bitmapTex = SDL_CreateTextureFromSurface(renderer, bitmapSurface);

	SDL_FreeSurface(bitmapSurface);

	while (1)
	{
		SDL_ShowCursor(SDL_DISABLE);
		SDL_Event e;
		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_RIGHT:
				ball.a += 1;
				break;
			case SDLK_LEFT:
				ball.a -= 1;
				break;
			}
		}

		if (e.type == SDL_MOUSEMOTION)
		{
			kursorDane.x = e.motion.x;
			kursorDane.y = e.motion.y;

		}						// If a key was released 
		else if (e.type == SDL_KEYUP)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_RIGHT:
				ball.a += 10;
				break;
			case SDLK_LEFT:
				ball.a -= 10;
				break;
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (e.button.button == SDL_BUTTON_LEFT
				&& (kursorDane.x >= przyciskCel.x
					&& kursorDane.x <= przyciskCel.x + przyciskDane.w)
				&& (kursorDane.y >= przyciskCel.y
					&& kursorDane.y <= przyciskCel.y + przyciskDane.h))
			{
				e.type == SDL_QUIT;
				break;
			}
			if (e.button.button == SDL_BUTTON_LEFT
				&& (kursorDane.x >= startButonH.x && kursorDane.x <= startButonH.x + startButonW.w)
				&& (kursorDane.y >= startButonH.y
					&& kursorDane.y <= startButonH.y + startButonW.h))
			{
				/* turn on Animate */
				trafka = true;


			}
		}
		if (SDL_PollEvent(&e))
		{

			if (e.type == SDL_QUIT)
			{
				break;
			}
		}
		bal(renderer);
		start(renderer);
		triangle(renderer);

		if (trafka)
		{
			ball.b += speed.b;
			ball.a += speed.a;
			line(renderer);
			player(renderer);
			glFlush();
			drawEnemy(renderer);
			/*end while 1*/
		}


		/* Got everything on rendering surface,

		   now Update the drawing image on window screen */

		SDL_UpdateWindowSurface(win);

		SDL_RenderFillRect(renderer, &rect);

		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, bitmapTex, NULL, NULL);


		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	
	}

	SDL_DestroyTexture(bitmapTex);

	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(win);

	SDL_Quit();

	return 0;
}