#ifndef SURFACE_H_
#define SURFACE_H_
#pragma once

#include <SDL2/SDL.h>
#include "Rectangle.h"
#include "Color.h"

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define rmask 0xff000000
#define gmask 0x00ff0000
#define bmask 0x0000ff00
#define amask 0x000000ff
#else
#define rmask 0x000000ff
#define gmask 0x0000ff00
#define bmask 0x00ff0000
#define amask 0xff000000
#endif

namespace tiledl
{

	class Surface
	{
		public:
			Surface();
			Surface(int width, int height);
			Surface(SDL_Surface* handle);
			Surface(SDL_RWops* src, bool freesrc);
			Surface(SDL_RWops* src, bool freesrc, char* type);
			Surface(const char* file);

			virtual ~Surface();

			bool operator== (const Surface& other) const;
			bool operator== (const SDL_Surface* other) const;

			// Operations
			void ref();
			void deref();
			void destroy();

			bool isNull();
			void lock();
			void unlock();
			bool mustLock();

			void resize(const Rectangle& newSize);

			bool SaveBMP(const char* file);
			bool SaveBMP(SDL_RWops* dst, bool freedst);
			bool SavePNG(const char* file);
			bool SavePNG(SDL_RWops* dst, bool freedst);

			// Setters
			void setRLE(bool enable);
			void setAlphaMod(Uint8 alpha);
			void setBlendMode(SDL_BlendMode blend);
			void setColorMod(Color color);

			// Getters
			SDL_Surface* getHandle();
			SDL_PixelFormat* getFormat();
			int getWidth();
			int getHeight();
			int getPitch();
			void* getUserData();
			Rectangle getClipRect();
			int getRefCount();
			Uint8 getAlphaMod();
			SDL_BlendMode getBlendMode();
			Color getColorMod();

		private:
			inline void null_check();
			int refcount;
			SDL_Surface* handle;
	};
	SDL_Surface* CreateSurface(int width, int height);
} // tiledl

#endif // SURFACE_H_
