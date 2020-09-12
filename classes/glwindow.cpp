#include "glwindow.h"
#include <stdio.h>
#include <GL/glu.h>
#include <GL/gl.h>

static int getKeyState(SDLMod mode)
{
	int state = 0;

	if((mode & KMOD_LSHIFT) != 0)
		state |= LeftShift;
	if((mode & KMOD_RSHIFT) != 0)
		state |= RightShift;
	if((mode & KMOD_LCTRL) != 0)
		state |= LeftCtrl;
	if((mode & KMOD_RCTRL) != 0)
		state |= RightCtrl;
	if((mode & KMOD_LALT) != 0)
		state |= LeftAlt;
	if((mode & KMOD_RALT) != 0)
		state |= RightAlt;
	if((mode & KMOD_CAPS) != 0)
		state |= CapsLock;
	return state;
}

GLWindowBase::GLWindowBase()
{
	const char * defTitle = "OpenGL Sample";

	putenv((char*)"SDL_VIDEO_WINDOW_POS=center");
	putenv((char*)"SDL_VIDEO_CENTERED=1");
	done = false;
	frameCount = 0;
	bpp = 32;
	fps = 0;
	width = 640;
	height = 480;
	mcapture = 0;
	fullscreen = false;
	resizable = false;
	title = new char[strlen(defTitle) + 1];
	strcpy(title, defTitle);
	frameRate = 60;
	fpsCount = 0;
	mlock = false;
	x = 0;
	y = 0;
}

GLWindowBase::~GLWindowBase()
{
	delete title;
}

void GLWindowBase::resize3DScene()
{
	if (height == 0)									// Prevent A Divide By Zero
		height = 1;
	glMatrixMode( GL_PROJECTION );						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glViewport(0, 0, width, height);					// Set The Current Viewport
	// Calculate The Aspect Ratio Of The Window
	glMatrixMode( GL_MODELVIEW );						// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	gluPerspective(45.0f, (GLfloat)width / height, 0.1f, 100.0f);
}

void GLWindowBase::resize2DScene()
{
	glMatrixMode( GL_PROJECTION );						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glViewport(0, 0, width, height);					// Set The Current Viewport
	// Set up the orthographic projection
	glMatrixMode( GL_MODELVIEW );						// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	glOrtho( 0, width, height, 0, -1, 1 );
	glDisable( GL_DEPTH_TEST );
}

void GLWindowBase::getWindowInfo(int & width, int & height, int & bpp,
								 bool & fullScreen, bool & resizable)
{
	width = 640;
	height = 480;
	bpp = 32;
	fullScreen = false;
	resizable = false;
}

bool GLWindowBase::inFullscreen()
{
	return fullscreen;
}

void GLWindowBase::setTitle(const char * title)
{
	if(!strcmp(title, this->title))
		return;
	delete this->title;
	this->title = new char[strlen(title) + 1];
	strcpy(this->title, title);
	SDL_WM_SetCaption(this->title, NULL);
}

const char * GLWindowBase::getTitle()
{
	return title;
}

void GLWindowBase::showMouse(bool show)
{
	SDL_ShowCursor((show) ? 1 : 0);
}

void GLWindowBase::setMousePos(int x, int y)
{
	SDL_WarpMouse(x, y);
}

void GLWindowBase::lockMouse(bool lock)
{
	this->mlock = lock;
	if(lock)
	{
		SDL_WM_GrabInput(SDL_GRAB_ON);
	}
	else
	{
		SDL_WM_GrabInput(SDL_GRAB_OFF);
	}
}

void GLWindowBase::setMouseCapture()
{
	mcapture++;
}

void GLWindowBase::releaseMouseCapture()
{
	if(mcapture == 0)
		return;
	mcapture--;
}

void GLWindowBase::setFullscreen(bool fullscreen)
{
	Uint32 flags;
	SDL_Surface* _screen;

	if(this->fullscreen == fullscreen)
		return;
	this->fullscreen = fullscreen;
	flags = SDL_SWSURFACE | SDL_OPENGL;
	if(fullscreen)
		flags |= SDL_FULLSCREEN;
	if(resizable && !fullscreen)
		flags |= SDL_RESIZABLE;
	_screen = SDL_SetVideoMode(width, height, bpp, flags);
	if(_screen != NULL)
		screen = _screen;
	onResize(screen->w, screen->h);
	onCreate();
}

inline void GLWindowBase::handleEvents()
{
	SDL_Event event;

	while(SDL_PollEvent( & event))
	{
		switch(event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
		{
			int state;

			state = getKeyState(SDL_GetModState());
			onMouseDown(event.button.x, event.button.y, event.button.button, state);
			break;
		}
		case SDL_MOUSEMOTION:
		{
			int state;

			state = getKeyState(SDL_GetModState());
			onMouseMove(event.button.x, event.button.y);
			break;
		}
		case SDL_VIDEORESIZE:
		{
			width = event.resize.w;
			height = event.resize.h;
			onResize(event.resize.w, event.resize.h);
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			int state;

			state = getKeyState(SDL_GetModState());
			onMouseUp(event.button.x, event.button.y, event.button.button, state);
			break;
		}
		case SDL_KEYDOWN:
		{
			int state;

			state = getKeyState(event.key.keysym.mod);
			onKeyDown(event.key.keysym.sym, state);
			break;
		}
		case SDL_KEYUP:
		{
			int state;

			state = getKeyState(event.key.keysym.mod);
			onKeyUp(event.key.keysym.sym, state);
			break;
		}
		case SDL_QUIT:
			if(onClose())
				close();
			break;
		}
	}
}

int GLWindowBase::start(int argc, char * argv[])
{
	Uint32 flags;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_WM_SetCaption(this->title, NULL);
	startTicks = lastTicks;
	lastTicks = SDL_GetTicks();
	setTitle(title);
	if(!onInit(argc, argv))
	{
		SDL_Quit();
		return -2;
	}
	getWindowInfo(width, height, bpp, fullscreen, resizable);
	flags = SDL_SWSURFACE | SDL_OPENGL;
	if(fullscreen)
		flags |= SDL_FULLSCREEN;
	if(resizable && !fullscreen)
		flags |= SDL_RESIZABLE;
	screen = SDL_SetVideoMode(width, height, bpp, flags);
	// call first resize event
	onResize(width, height);
	onCreate();
	// program main loop
	while(!done)
	{
		// check for events
		handleEvents();
		// OpenGL animation code goes here
		render();
		delay();
	}
	onDestroy();
	SDL_Quit();
	return 0;
}

void GLWindowBase::close()
{
	done = true;
}

int GLWindowBase::getWidth()
{
	return width;
}

int GLWindowBase::getHeight()
{
	return height;
}

bool GLWindowBase::onInit(int argc, char * argv[])
{
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	return true;
}

void GLWindowBase::onCreate() {}
void GLWindowBase::onDestroy() {}

void GLWindowBase::onKeyDown(int key, int state)
{
	switch (key)
	{
	case SDLK_ESCAPE:
		close();
		break;
	case SDLK_F12:
		setFullscreen(!inFullscreen());
		break;
	}
}

void GLWindowBase::onKeyUp(int key, int state) {}
void GLWindowBase::onMouseMove(int x, int y) {}
void GLWindowBase::onMouseDown(int x, int y, int button, int state) {}
void GLWindowBase::onMouseUp(int x, int y, int button, int state) {}
void GLWindowBase::onResize(int newWidth, int newHeight) {}
void GLWindowBase::onMove(int x, int y) {}

bool GLWindowBase::onClose()
{
	return true;
}

void GLWindowBase::render()
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClear( GL_COLOR_BUFFER_BIT );

	glPushMatrix();
	glBegin( GL_TRIANGLES );
	glColor3f( 1.0f, 0.0f, 0.0f );
	glVertex2f( 0.0f, 1.0f );
	glColor3f( 0.0f, 1.0f, 0.0f );
	glVertex2f( 0.87f, -0.5f );
	glColor3f( 0.0f, 0.0f, 1.0f );
	glVertex2f( -0.87f, -0.5f );
	glEnd();
	glPopMatrix();

	swapBuffers();
}

void GLWindowBase::swapBuffers()
{
	SDL_GL_SwapBuffers();
}

float GLWindowBase::getFPS()
{
	return fps;
}

void GLWindowBase::setFrameRate(int fps)
{
	if(fps > 0 && fps <= 120)
	{
		frameRate = fps;
		frameCount = 0;
		lastTicks = SDL_GetTicks();
	}
}

void GLWindowBase::delay()
{
	Uint32 target_ticks;
	Uint32 current_ticks;
	Uint32 delay_ticks;
	float fpsTicks;

	fpsTicks = (float)1000 / frameRate;
	frameCount++;
	fpsCount++;
	target_ticks = lastTicks + (Uint32) ((float) frameCount * fpsTicks);
	current_ticks = SDL_GetTicks();
	if(current_ticks <= target_ticks)
	{
		delay_ticks = target_ticks - current_ticks;
		SDL_Delay(delay_ticks);
	}
	else
	{
		frameCount = 0;
		lastTicks = SDL_GetTicks();
	}
	current_ticks = SDL_GetTicks();
	delay_ticks = current_ticks - startTicks;
	if(delay_ticks >= (Uint32)(fpsTicks * frameRate))
	{
		if(fpsCount > 0)
			fps = delay_ticks / (1000.0 / fpsCount);
		startTicks = current_ticks;
		fpsCount = 0;
	}
}


