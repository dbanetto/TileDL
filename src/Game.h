#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#pragma once

#include <SDL2/SDL.h>
#include "Renderer.h"
#include "Window.h"

namespace tiledl
{

	/**
	 *  @note Breaks down SDL_Color into a RGBA comma separated list
	 */
#define SDL_COLOR_RGBA(x) x.r, x.g, x.b, x.a // FIXME: move this to a more appropriate file

	/**
	 * A struct of Window Settings
	 */
	struct WindowSettings {
		bool bordered = true;
		/** 0 - Windowed
		* 1 - Fullscreen
		* 2 - Fullscreen desktop
		*/
		FullscreenMode fullscreen = WINDOWED;
		bool screensaver = true;
		bool resizable = false;

		int width = 800, height = 600;
	};

	/**
	 * A struct of Renderer settings
	 */
	struct RenderSettings {
		int vsync = 1;
		bool doublebuffer = true;
		bool antialias = false;
		int samples = 0; // FIXME: Better name for Anti-Alias samples
	};

	class Game
	{
	public:
		Game();
		~Game();
		bool operator== (const Game& other) const;

		int init(const char* title, int width, int height, Uint32 windowFlags, int deviceIndex, Uint32 rendererFlags);
		void start();

		virtual void render();
		virtual void update();
		virtual void event(SDL_Event& event);

		void setWindowSettings(WindowSettings& settings);
		void setRenderSettings(RenderSettings& settings);

		void applyWindowSettings();
		void applyRenderSettings();
		void applySettings();

		void renderLoop();
		void updateLoop();

	protected:
		Renderer renderer;
		Window window;
		SDL_GLContext glcontex;

		bool inited, quit;
		SDL_Color background;

		WindowSettings windowSettings;
		RenderSettings renderSettings;

		SDL_threadID inited_on; // FIXME : Correct name
	private:
		SDL_Thread* updateThread;

	};
} // namespace tiledl
#endif // GAMEWINDOW_H
