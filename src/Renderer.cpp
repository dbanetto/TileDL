#include "Renderer.h"
#include <stdexcept>

using namespace tiledl;

Renderer::Renderer()
{
	this->handle = nullptr;
}

Renderer::Renderer(SDL_Window* window, int index, Uint32 flags)
{
	if (!init(window, index, flags)) {
		throw std::runtime_error("Failed to init renderer");
	}
}

Renderer::Renderer(Window window, int index, Uint32 flags)
{
	if (!init(window, index, flags)) {
		throw std::runtime_error("Failed to init renderer");
	}
}

Renderer::~Renderer()
{
	this->destroy();
}

bool Renderer::operator==(const Renderer& other) const
{
	return this->handle == other.handle;
}

bool Renderer::operator==(const SDL_Renderer* other) const
{
	return this->handle == other;
}

bool Renderer::isNull()
{
	return this->handle == nullptr || this->handle == NULL;
}

void Renderer::destroy()
{
	if (!this->isNull()) {
		SDL_DestroyRenderer(this->handle);
		this->handle = nullptr;
	}
}

inline void Renderer::null_check()
{
	if (this->isNull())
		throw std::runtime_error("Cannot operate on a Renderer that is not initalised");
}

void Renderer::present()
{
	null_check();
	SDL_RenderPresent(this->handle);
}


void Renderer::clear()
{
	null_check();
	SDL_RenderClear(this->handle);
}

bool Renderer::init(Window window, int index, Uint32 flags)
{
	return init(window.getHandle(), index, flags);
}

bool Renderer::init(SDL_Window* window, int index, Uint32 flags)
{
	if (SDL_WasInit(SDL_INIT_VIDEO) == SDL_FALSE) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		             "Renderer (%p) : attempted to be created when SDL_INIT_VIDEO is not inited",
		             this
		            );
		return false;
	}

	this->handle = SDL_CreateRenderer(window, index, flags);

	if (this->handle == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		             "Renderer (%p) : Failed to create SDL_Renderer (window: %p index: %d flags: %x) %s",
		             this, window, index, flags, SDL_GetError()
		            );
		return false;
	}

	return true;
}

bool Renderer::initSW(SDL_Surface* surface)
{
	if (SDL_WasInit(SDL_INIT_VIDEO) == SDL_FALSE) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		             "Renderer (%p) : attempted to be created when SDL_INIT_VIDEO is not inited",
		             this
		            );
		return false;
	}

	this->handle = SDL_CreateSoftwareRenderer(surface);

	if (this->handle == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		             "Renderer (%p) : Failed to create a software SDL_Renderer (surface: %p) %s",
		             this, surface, SDL_GetError()
		            );
		return false;
	}

	return true;
}

/* ========= Draw Functions =========*/

void Renderer::drawPoint(int x, int y)
{
	null_check();

	if (SDL_RenderDrawPoint(this->handle, x , y) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		             "Renderer (%p) : Error while drawing point {%i,%i} %s",
		             this, x, y , SDL_GetError()
		            );
	}
}

void Renderer::drawPoint(SDL_Point pt)
{
	drawLine(pt.x, pt.y);
}

void Renderer::drawPoint(const Vector& pt)
{
	drawLine((int)pt.x , (int)pt.y);
}

void Renderer::drawLine(int x1, int y1, int x2, int y2)
{
	null_check();

	if (SDL_RenderDrawLine(this->handle, x1 , y1, x2, y2) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		             "Renderer (%p) : Error while drawing line {%i,%i} to {%i,%i} %s",
		             this, x1, y1, x2, y2, SDL_GetError()
		            );
	}
}

void Renderer::drawLine(SDL_Point pt1, SDL_Point pt2)
{
	drawLine(pt1.x, pt1.y, pt2.x, pt2.y);
}

void Renderer::drawLine(const Vector& pt1, const Vector& pt2)
{
	drawLine((int)pt1.x, (int)pt1.y, (int)pt2.x, (int)pt2.y);
}

void Renderer::drawLines(const SDL_Point* points, int count)
{
	null_check();

	if (SDL_RenderDrawLines(this->handle, points, count) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		             "Renderer (%p) : Error while drawing Lines (count: %d) %s",
		             this, count, SDL_GetError()
		            );
	}
}

void Renderer::drawLines(const std::vector<SDL_Point>& points)
{
	drawLines(&points[0], points.size());
}

void Renderer::drawLines(const Point* points, int count)
{
	drawLines((SDL_Point*)points, count);
}

void Renderer::drawLines(const std::vector<Point>& points)
{
	drawLines((SDL_Point*)(&points[0]), points.size());
}

void Renderer::drawRect(const SDL_Rect* rect)
{
	null_check();

	if (SDL_RenderDrawRect(this->handle, rect) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		             "Renderer (%p) : Error while drawing Rectangle {%i,%i,%i,%i} %s",
		             this, rect->x, rect->y, rect->w, rect->h, SDL_GetError()
		            );
	}
}

void Renderer::drawRect(const Rectangle& rect)
{
	auto r = rect.toSdlRect();
	drawRect(&r);
}

void Renderer::drawRect(int x, int y, int w, int h)
{
	SDL_Rect r = {x, y, w , h};
	drawRect(&r);
}

void Renderer::fillRect(const SDL_Rect* rect)
{
	null_check();

	if (SDL_RenderFillRect(this->handle, rect) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		             "Renderer (%p) : Error while filling Rectangle {%i,%i,%i,%i} %s",
		             this, rect->x, rect->y, rect->w, rect->h, SDL_GetError()
		            );
	}
}

void Renderer::fillRect(const Rectangle& rect)
{
	auto r = rect.toSdlRect();
	fillRect(&r);
}

void Renderer::fillRect(int x, int y, int w, int h)
{
	SDL_Rect r = {x, y, w , h};
	fillRect(&r);
}

/* ========= Getters =========*/

SDL_Renderer* Renderer::getHandle()
{
	return this->handle;
}

void Renderer::setDrawColor(SDL_Color color)
{
	setDrawColor(color.r, color.g, color.b, color.a);
}

void Renderer::setDrawColor(Color color)
{
	setDrawColor(color.r, color.g, color.b, color.a);
}

void Renderer::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	null_check();

	if (SDL_SetRenderDrawColor(handle, r, g , b, a) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		             "Renderer (%p) : Error while setting draw color RGBA:{%X,%X,%X,%X} %s",
		             this, r, g, b, a, SDL_GetError()
		            );
	}
}

