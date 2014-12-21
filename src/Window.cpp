#include "Window.h"
#include <stdexcept>

using namespace tiledl;

Window::Window()
{
	this->handle = nullptr;
}

Window::Window(const char* title, int width, int height, Uint32 flags)
{
	if (!this->init(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags)) {
		throw std::runtime_error("Failed to initalise Window");
	}
}


Window::Window(const char* title, int x, int y, int width, int height, Uint32 flags)
{
	if (!this->init(title, x, y, width, height, flags)) {
		throw std::runtime_error("Failed to initalise Window");
	}
}

Window::~Window()
{
	this->destroy();
}

bool Window::init(const char* title, int x, int y, int width, int height, Uint32 flags)
{
	if (SDL_WasInit(SDL_INIT_VIDEO) == SDL_FALSE) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		             "Window (%p) : Window attempted to be created when SDL_INIT_VIDEO is not is not inited",
		             this
		            );
		return false;
	}

	this->handle = SDL_CreateWindow(title, x, y, width, height, flags);

	if (this->handle == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		             "Window (%p) : Window failed to create %s",
		             this, SDL_GetError()
		            );
		return false;
	}

	return true;
}

bool Window::isNull()
{
	return (this->handle == nullptr || this->handle == NULL);
}

inline void Window::null_check()
{
	if (this->isNull())
		throw std::runtime_error("Cannot operate on a Window that is not initalised");
}
void Window::destroy()
{
	if (!this->isNull()) {
		SDL_DestroyWindow(this->handle);
		this->handle = nullptr;
	}
}

bool Window::operator==(const Window& other) const
{
	return this->handle == other.handle;
}

void Window::show()
{
	null_check();
	SDL_ShowWindow(this->handle);
}

void Window::hide()
{
	null_check();
	SDL_HideWindow(this->handle);
}

void Window::maximize()
{
	null_check();
	SDL_MaximizeWindow(this->handle);
}

void Window::minimize()
{
	null_check();
	SDL_MinimizeWindow(this->handle);
}

void Window::raise()
{
	null_check();
	SDL_RaiseWindow(this->handle);
}

void Window::restore()
{
	null_check();
	SDL_RestoreWindow(this->handle);
}

/* ========= Getters =========*/

SDL_Point Window::getPosition()
{
	null_check();
	SDL_Point pt;
	SDL_GetWindowPosition(this->handle, &pt.x, &pt.y);
	return pt;
}

void Window::getPosition(int* x, int* y)
{
	null_check();
	SDL_GetWindowPosition(this->handle, x, y);
}

SDL_Rect Window::getSize()
{
	null_check();
	SDL_Rect rect;
	rect.x = rect.y = 0;
	SDL_GetWindowMaximumSize(this->handle, &rect.w, &rect.h);
	return rect;
}

void Window::getSize(int* w, int* h)
{
	null_check();
	SDL_GetWindowSize(this->handle, w, h);
}


SDL_Rect Window::getMaximumSize()
{
	null_check();
	SDL_Rect rect;
	rect.x = rect.y = 0;
	SDL_GetWindowSize(this->handle, &rect.w, &rect.h);
	return rect;
}

void Window::getMaximumSize(int* w, int* h)
{
	null_check();
	SDL_GetWindowMaximumSize(this->handle, w, h);
}

SDL_Rect Window::getMinimumSize()
{
	null_check();
	SDL_Rect rect;
	rect.x = rect.y = 0;
	SDL_GetWindowMinimumSize(this->handle, &rect.w, &rect.h);
	return rect;
}

void Window::getMinimumSize(int* w, int* h)
{
	null_check();
	SDL_GetWindowMinimumSize(this->handle, w, h);
}


SDL_Surface* Window::getWindowSurface()
{
	null_check();
	return SDL_GetWindowSurface(this->handle);
}

const char* Window::getTitle()
{
	null_check();
	return SDL_GetWindowTitle(this->handle);
}

SDL_Window* Window::getHandle()
{
	return this->handle;
}

Uint32 Window::getFlags()
{
	null_check();
	return SDL_GetWindowFlags(this->handle);
}

Uint32 Window::getWindowID()
{
	null_check();
	return SDL_GetWindowID(this->handle);
}

Uint32 Window::getPixelFormat()
{
	null_check();
	return SDL_GetWindowPixelFormat(this->handle);
}

SDL_DisplayMode Window::getDislayMode()
{
	null_check();
	SDL_DisplayMode dm;

	if (SDL_GetWindowDisplayMode(this->handle, &dm) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		             "Window (%p) : Failed to get Window Display Mode %s",
		             this, SDL_GetError()
		            );
		throw std::runtime_error("Failed to get Window Display Mode");
	}

	return dm;
}

/* ========= Setters =========*/

bool Window::setDisplayMode(const SDL_DisplayMode dm)
{
	null_check();
	return (SDL_SetWindowDisplayMode(this->handle, &dm) == 0);
}

bool Window::setFullscreen(FullscreenMode mode)
{
	null_check();
	return (SDL_SetWindowFullscreen(this->handle, (Uint32)mode) == 0);
}

void Window::setWindowGrab(bool grabbed)
{
	null_check();
	SDL_SetWindowGrab(this->handle, (grabbed ? SDL_TRUE : SDL_FALSE));
}

void Window::setIcon(SDL_Surface* icon)
{
	null_check();
	SDL_SetWindowIcon(this->handle, icon);
}

void Window::setMaximumSize(int w, int h)
{
	null_check();
	SDL_SetWindowMaximumSize(this->handle, w, h);
}

void Window::setMinimumSize(int w, int h)
{
	null_check();
	SDL_SetWindowMinimumSize(this->handle, w, h);
}

void Window::setPosition(int x, int y)
{
	null_check();
	SDL_SetWindowPosition(this->handle, x, y);
}

void Window::setSize(int w, int h)
{
	null_check();
	SDL_SetWindowSize(this->handle, w, h);
}

void Window::setTitle(const char* title)
{
	null_check();
	SDL_SetWindowTitle(this->handle, title);
}

void Window::setBordered(bool bordered)
{
	null_check();
	SDL_SetWindowBordered(this->handle, (bordered ? SDL_TRUE : SDL_FALSE));
}
