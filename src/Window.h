#ifndef WINDOW_H
#define WINDOW_H
#pragma once

#include <SDL2/SDL.h>

namespace tiledl
{
	enum FullscreenMode : Uint32 {
	    FULLSCREEN = SDL_WINDOW_FULLSCREEN,
	    FULLSCREEN_DESKTOP = SDL_WINDOW_FULLSCREEN_DESKTOP,
	    WINDOWED = 0
	};

	class Window
	{
	public:
		Window();
		Window(const char* title, int width, int height, Uint32 flags);
		Window(const char* title, int x, int y, int width, int height, Uint32 flags);
		~Window();

		bool init(const char* title, int x, int y, int width, int height, Uint32 flags);
		bool isNull();
		void destroy();
		bool operator==(const Window& other) const;

		void show();
		void hide();
		void raise();
		void restore();
		void maximize();
		void minimize();

		// Getters

		SDL_Point getPosition();
		SDL_Rect  getSize();
		SDL_Rect  getMinimumSize();
		SDL_Rect  getMaximumSize();
		void getPosition(int* x, int* y);
		void getSize(int* w, int* h);
		void getMaximumSize(int* w, int* h);
		void getMinimumSize(int* w, int* h);

		SDL_Surface* getWindowSurface();
		const char* getTitle();

		Uint32 getFlags();
		Uint32 getWindowID();
		Uint32 getPixelFormat();
		SDL_DisplayMode getDislayMode();
		SDL_Window* getHandle();

		// Setters
		bool setDisplayMode(const SDL_DisplayMode dm);
		bool setFullscreen(FullscreenMode mode);
		void setWindowGrab(bool grabbed);
		void setIcon(SDL_Surface* icon);
		void setMaximumSize(int w, int h);
		void setMinimumSize(int w, int h);
		void setPosition(int x, int y);
		void setSize(int w, int h);
		void setTitle(const char* title);
		void setBordered(bool bordered);

	private:
		SDL_Window* handle;
		inline void null_check();
	};
}
#endif // WINDOW_H
