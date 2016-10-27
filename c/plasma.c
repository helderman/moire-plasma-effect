// plasma.c - main module of Moire Plasma Effect, by Ruud Helderman

#include "SDL.h"
#include "SDL_image.h"

#define TITLE		"Moire Plasma Effect"

#define SPEED		50	/* pixels per second */

#define SCRN_WIDTH	640
#define SCRN_HEIGHT	480
#define SCRN_DEPTH	24

extern char _binary____html5_moire1_png_start;
extern char _binary____html5_moire1_png_size;
extern char _binary____html5_moire2_png_start;
extern char _binary____html5_moire2_png_size;

#define moire1_start   (&_binary____html5_moire1_png_start)
#define moire1_size    ((int)(&_binary____html5_moire1_png_size))
#define moire2_start   (&_binary____html5_moire2_png_start)
#define moire2_size    ((int)(&_binary____html5_moire2_png_size))

#define ADJUST_LEFT(rect, d)    ((rect)->w += (d), (rect)->x -= (d))
#define ADJUST_RIGHT(rect, d)   ((rect)->w += (d))
#define ADJUST_TOP(rect, d)     ((rect)->h += (d), (rect)->y -= (d))
#define ADJUST_BOTTOM(rect, d)  ((rect)->h += (d))

static void clip_left(SDL_Rect *rect1, SDL_Rect *rect2, int d)
{
	if (d < 0) { ADJUST_LEFT(rect1, d); ADJUST_LEFT(rect2, d); }
}

static void clip_right(SDL_Rect *rect1, SDL_Rect *rect2, int d)
{
	if (d < 0) { ADJUST_RIGHT(rect1, d); ADJUST_RIGHT(rect2, d); }
}

static void clip_top(SDL_Rect *rect1, SDL_Rect *rect2, int d)
{
	if (d < 0) { ADJUST_TOP(rect1, d); ADJUST_TOP(rect2, d); }
}

static void clip_bottom(SDL_Rect *rect1, SDL_Rect *rect2, int d)
{
	if (d < 0) { ADJUST_BOTTOM(rect1, d); ADJUST_BOTTOM(rect2, d); }
}

static void blit_tiles(SDL_Surface *screen, SDL_Surface *tile, int xpos, int ypos)
{
	int x, y;
	for (y = -ypos; y < screen->h; y += tile->h)
	{
		for (x = -xpos; x < screen->w; x += tile->w)
		{
			SDL_Rect src = {0, 0, tile->w, tile->h};
			SDL_Rect dest = {x, y, tile->w, tile->h};
			clip_left(&src, &dest, x);
			clip_right(&src, &dest, screen->w - dest.x - dest.w);
			clip_top(&src, &dest, y);
			clip_bottom(&src, &dest, screen->h - dest.y - dest.h);
			SDL_BlitSurface(tile, &src, screen, &dest);
		}
	}
}

static void blit_all(SDL_Surface *screen, SDL_Surface *front, SDL_Surface *back, int position)
{
	int pos1 = position & 511;
	int pos2 = ~position & 511;
	blit_tiles(screen, back, pos2, pos1);
	blit_tiles(screen, front, pos1, pos1);
}

int main(int argc, char *argv[])
{
	int i, done = 0, flip = 0;

	SDL_Init(SDL_INIT_VIDEO);
	atexit(SDL_Quit);

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0)
	{
		fprintf(stderr, "Failed to init PNG support.\n");
		exit(1);
	}

	Uint32 flags = SDL_HWSURFACE;
	for (i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-fullscreen") == 0)
		{
			flags |= SDL_FULLSCREEN;
			SDL_ShowCursor(SDL_DISABLE);
		}
		if (strcmp(argv[i], "-doublebuf") == 0)
		{
			flags |= SDL_DOUBLEBUF;
		}
		if (strcmp(argv[i], "-flip") == 0)
		{
			flip = 1;
		}
	}
	SDL_Surface *screen = SDL_SetVideoMode(SCRN_WIDTH, SCRN_HEIGHT, SCRN_DEPTH, flags);
	if (screen == NULL)
	{
		fprintf(stderr, "Failed to set video mode.\n");
		exit(1);
	}

	SDL_WM_SetCaption(TITLE, *argv);

	SDL_RWops *rw1 = SDL_RWFromMem(moire1_start, moire1_size);
	SDL_RWops *rw2 = SDL_RWFromMem(moire2_start, moire2_size);

	SDL_Surface *surface1 = IMG_LoadTyped_RW(rw1, 1, "png");
	SDL_Surface *surface2 = IMG_LoadTyped_RW(rw2, 1, "png");

	SDL_SetAlpha(surface1, SDL_RLEACCEL | SDL_SRCALPHA, 0);
	SDL_SetAlpha(surface2, SDL_RLEACCEL, 0);

	i = 0;
	while (!done)
	{
		static SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				done = 1;
				break;
			case SDL_KEYDOWN:
				done = event.key.keysym.sym == SDLK_ESCAPE;
				break;
			}
		}
		else
		{
			int ms = SDL_GetTicks();
			blit_all(screen, surface1, surface2, SPEED * ms / 1000);

			SDL_UpdateRect(screen, 0, 0, 0, 0);
			if (flip)
			{
				SDL_Flip(screen);
			}
			SDL_Delay(10);
		}
	}
	return 0;
}
