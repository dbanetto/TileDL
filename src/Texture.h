#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>

namespace tiledl
{
	class Texture
	{
	public:
		Texture();
		~Texture();
		bool operator== (const Texture& other) const;

		void destroy();
		bool isNull();

		void ref();
		void deref();

		void lock();
		void lock(void** pixels, int* pitch);
		void lock(const SDL_Rect* area, void** pixels, int* pitch);
		void unlock();
		void query(Uint32* format, int* access, int* w, int* h);

		bool updateTexture(const SDL_Rect*, const void* pixels, int pitch);

		// Getters
		int getWidth();
		int getHeight();
		int getRefCount();
		SDL_TextureAccess getAccess();
		Uint32 getFormat();
		Uint8 getAlphaMod();
		Uint8 getBlendMod();
		Uint8 getColorMod();

		SDL_Renderer* getOwner();

		//Setters
		void setAlphaMod(Uint8 mod);
		void setBlendMod(Uint8 mod);
		void setColorMod(Uint8 mod);

	private:
		inline void null_check();
		SDL_Renderer* owner;
		SDL_Texture* texture;

		int refcount;

		int w, h, access;
		Uint32 format;
	};
} // namespace tiledl
#endif // TEXTURE_H
