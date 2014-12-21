#ifndef RENDERER_H
#define RENDERER_H
#pragma once

#include <SDL2/SDL.h>
#include "Window.h"
#include "Vector.h"
#include "Point.h"
#include "Rectangle.h"
#include "Color.h"
#include <vector>

namespace tiledl
{
	class Renderer
	{
	public:
		Renderer();
		Renderer(SDL_Window* window, int index, Uint32 flags);
		Renderer(Window window, int index, Uint32 flags);

		~Renderer();

		bool init(SDL_Window* window, int index, Uint32 flags);
		bool init(Window window, int index, Uint32 flags);
		bool initSW(SDL_Surface* surface); // Software Renderer

		bool isNull();
		void destroy();
		bool operator==(const Renderer& other) const;
		bool operator==(const SDL_Renderer* other) const;

		void present();
		void clear();

		// Draw Functions
		void drawPoint(int x, int y);
		void drawPoint(SDL_Point pt);
		void drawPoint(const Vector& pt);

		void drawLine(int x1, int y1, int x2, int y2);
		void drawLine(SDL_Point pt1, SDL_Point pt2);
		void drawLine(const Vector& pt1, const Vector& pt2);

		void drawLines(const std::vector<SDL_Point>& points);
		void drawLines(const std::vector<Point>& points);
		void drawLines(const SDL_Point* points, int count);
		void drawLines(const Point* points, int count);

		void drawRect(const SDL_Rect* rect);
		void drawRect(const Rectangle& rect);
		void drawRect(int x, int y, int w, int h);

		void fillRect(const SDL_Rect* rect);
		void fillRect(const Rectangle& rect);
		void fillRect(int x, int y, int w, int h);

		// Getters
		SDL_Renderer* getHandle();


		//Setters
		void setDrawColor(SDL_Color color);
		void setDrawColor(Color color);
		void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	private:
		inline void null_check();
		SDL_Renderer* handle;
	};
} // namespace frame2d
#endif // RENDERER_H
