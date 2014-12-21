#include "Game.h"
#include "Timer.h"
#include <stdexcept>

using namespace tiledl;

Game::Game()
{
	inited = false;
	inited_on = 0;
	updateThread = nullptr;

	background.r = background.g = background.b = background.a = 0;
}

Game::~Game()
{
	if (inited) {
		quit = true;
		inited = false;

		if (updateThread != nullptr) {
			SDL_WaitThread(updateThread, NULL);
		}

		SDL_GL_DeleteContext(glcontex);
		renderer.destroy();
		window.destroy();
	}
}
/**
 * @note Compares the renderer and the window pointers
 * which both are unique to each Game
 */
bool Game::operator== (const Game& other) const
{
	return (other.renderer == this->renderer && other.window == this->window);
}

int Game::init(const char* title, int width, int height, Uint32 windowFlags, int deviceIndex, Uint32 rendererFlags)
{
	if (this->inited == true) {
		//warning
	}

	this->window   = Window();
	this->renderer = Renderer();

	if (SDL_WasInit(SDL_INIT_VIDEO) == SDL_FALSE) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot init a Game Window when SDL is not initialised");
		SDL_ClearError();
		return -1;
	}

	// Window
	if (!window.init(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, windowFlags)) {
		SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Game (%p): Failed to create a window. Flags %x. %s",
		                this, windowFlags, SDL_GetError());
		SDL_ClearError();
		return 1;
	}

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Game (%p): Created SDL_Window flags: %x",
	            this, windowFlags);

	// Renderer

	if (!renderer.init(window.getHandle(), deviceIndex, rendererFlags)) {
		window.destroy();
		SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Game (%p): Failed to create a renderer. Flags %x. %s",
		                this, rendererFlags, SDL_GetError());
		SDL_ClearError();
		return 2;
	}

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Game (%p): Created SDL_Renderer flags: %x",
	            this, rendererFlags);

	// OpenGL Context
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	glcontex = SDL_GL_CreateContext(window.getHandle());

	if (glcontex == NULL) {
		window.destroy();
		renderer.destroy();
		SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Game (%p): Failed to create a GL Context. %s",
		                this, SDL_GetError());
		SDL_ClearError();
		return 3;
	} else {
		SDL_GL_MakeCurrent(window.getHandle(), glcontex);
	}

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Game (%p): Created GL Context", this);

	windowSettings.width = width;
	windowSettings.height = height;

	inited_on = SDL_ThreadID();
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Game (%p): initialised on thread ID : %u",
	            this, inited_on);

	inited = true;
	return 0;
}

/**
 * @note Requires the Game to be init'd
 */
void Game::start()
{
	if (!inited) {
		SDL_Log("Game (%p): Cannot start a Game Window when it is not initialised", this);
		return;
	}

	renderSettings.vsync = SDL_FALSE;
	renderSettings.antialias = SDL_TRUE;
	renderSettings.samples = 8;

	applySettings();
	quit = false;

	// Create a Update Thread
	updateThread = SDL_CreateThread((SDL_ThreadFunction)([](void * ptr) -> int {
		((Game*)(ptr))->updateLoop();
		return 0;
	}), "Update Thread", this);

	SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Game (%p): Created Update thread with ID : %x",
	             this, SDL_GetThreadID(updateThread));

	// Start render loop
	renderLoop();
}

void Game::updateLoop()
{
	Timer updatetimer;
	SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Game (%p): Started update loop on thread : %x"
	             , this
	             , SDL_ThreadID());

	while (!quit) {
		updatetimer.start();

		// Event Handling
		SDL_PumpEvents();
		SDL_Event event;

		while (SDL_PollEvent(&event) && !quit) {
			this->event(event);
		}

		// General updates
		{
			update();
		}

		const char* error = SDL_GetError();

		if (*error != '\0') {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", error);
			SDL_ClearError();
		}

		SDL_Delay(1); // HACK: temporary Update thread limiter, should have "Update per second" cap and boolean (like V-Sync)
		updatetimer.stop();

#ifdef DEBUG
		SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, "Game (%p): Update Time %g"
		               , this
		               , updatetimer.getDeltas());
#endif
	}
}

void Game::renderLoop()
{
	Timer frametimer, rendertimer;

	frametimer.start();

	while (!quit) {

		//Rendering

		rendertimer.start();
		{
			//SDL_GL_MakeCurrent(window, glcontex); Makes rendered output flip and distort
			renderer.setDrawColor(background);
			renderer.clear();
			render();
		}
		rendertimer.stop(); // TODO: Should rendertimer include V-Sync times?
		renderer.present();

#ifdef DEBUG
		frametimer.stop();
		SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, "Game (%p): : Frame Time : %g Render Time : %g",
		               this, frametimer.getDeltas(), rendertimer.getDeltas());
#endif
		frametimer.start();
	}
}

void Game::render()
{
	throw std::runtime_error("Game::render is called");
}

void Game::update()
{
	throw std::runtime_error("Game::update is called");
}
/**
 * General handler for SDL events
 */
void Game::event(SDL_Event& event)
{
	throw std::runtime_error("Game::event is called");
}

void Game::setWindowSettings(WindowSettings& settings)
{
	this->windowSettings = settings;
}

void Game::setRenderSettings(RenderSettings& settings)
{
	this->renderSettings = settings;
}

/**
 * Apply Window and Renderer settings
 */
void Game::applySettings()
{
	applyWindowSettings();
	applyRenderSettings();
}

/**
 * Apply Window settings
 */
void Game::applyWindowSettings()
{
	if (!inited) {
		return;
	}

	window.setBordered(windowSettings.bordered);

	if (!window.setFullscreen(windowSettings.fullscreen)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		             "Game (%p): Failed to apply Fullscreen. %s",
		             this, SDL_GetError());
		SDL_ClearError();
	}

	//FIXME: Should resizable window only be changed on restart?
	/*if (!(SDL_GetWindowFlags(window) & SDL_WINDOW_RESIZABLE) && windowSettings.resizable) {
		// Re-create Window with SDL_WINDOW_RESIZABLE flag to mirror the setting
		SDL_Log("Should probably add the SDL_WINDOW_RESIZABLE flag");
	} else if ((SDL_GetWindowFlags(window) & SDL_WINDOW_RESIZABLE) && !windowSettings.resizable) {
		// Re-create Window with SDL_WINDOW_RESIZABLE flag to mirror the setting
		SDL_Log("Should probably remove the SDL_WINDOW_RESIZABLE flag");
	}*/

	window.setSize(windowSettings.width, windowSettings.height);
}
/**
 * Apply Renderer and OpenGL settings
 * @note to be run on the same thread as inited_on
 */
void Game::applyRenderSettings()
{
	//FIXME: This should be only be run on the render(inited_on) thread
	if (SDL_ThreadID() != inited_on) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		             "Game (%p): Calling applyRenderSettings on wrong thread, expected %p got %p",
		             this, inited_on, SDL_ThreadID());
		return;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, renderSettings.doublebuffer);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, renderSettings.antialias);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, renderSettings.samples);

	if (SDL_GL_SetSwapInterval(renderSettings.vsync) != 0) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Game (%p): Failed to apply V-Sync setting: %i. %s",
		            this, renderSettings.vsync, SDL_GetError());
		SDL_ClearError();
	}

	if (glcontex == nullptr || glcontex == NULL) {
		glcontex = SDL_GL_CreateContext(window.getHandle());
	}
}
