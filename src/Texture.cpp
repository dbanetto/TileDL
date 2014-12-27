#include "Texture.h"
#include <stdexcept>
#include <limits>

using namespace tiledl;

Texture::Texture()
{
	this->owner = nullptr;
	this->texture = nullptr;
	this->w = this->h = this->format = 0;
	this->access = (SDL_TextureAccess)(0);
	this->refcount = 0;
}

Texture::~Texture()
{
	if (!this->isNull()) {
		this->destroy();
	}
}

bool Texture::isNull()
{
	return (this->texture == nullptr);
}

void Texture::null_check()
{
	if (this->isNull()) {
		throw std::runtime_error("Cannot operate on a texture that has not been initialised");
	}
}

bool Texture::operator== (const Texture& other) const
{
	return this->texture == other.texture;
}

void Texture::ref()
{
	null_check();

	if (refcount == std::numeric_limits<int>::max()) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
		            "Texture (%p) : reference count overflow. Has more than %i references",
		            this, std::numeric_limits<int>::max()
		           );
		return;
	}

	refcount++;
}

void Texture::deref()
{
	null_check();


	if (refcount <= 0) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
		            "Texture (%p) : dereferenced when references is %i.",
		            this, refcount
		           );
		return;
	}

	refcount--;
	// TODO: destroy texture if refcount is 0?
}

int Texture::getRefCount() {
	return this->refcount;
}

void Texture::destroy()
{
	if (!this->isNull()) {
		if (this->refcount != 0) { // NOTE: Should non-zero ref count stop destroy()?
			SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
			            "Texture (%p) : Is being destroyed while ref count is greater than zero (%i).",
			            this, this->refcount
			           );
		}

		SDL_DestroyTexture(this->texture);
		this->texture = nullptr;
		this->owner = nullptr;
	}
}

/**
 * @brief Query the texture for format, access width and height
 * @remark texture must be initialised
 * @param format pointer to be filled with format, can be NULL or nullptr
 * @param access pointer to be filled with access, can be NULL or nullptr
 * @param w pointer to be filled with width, can be NULL or nullptr
 * @param h pointer to be filled with height, can be NULL or nullptr
 */
void Texture::query(Uint32* format, int* access, int* w, int* h)
{
	null_check();

	if (SDL_QueryTexture(this->texture, &(this->format), &(this->access), &(this->w), &(this->h)) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		             "Texture (%p) : Error while Querying Texture (%p) %s",
		             this, texture, SDL_GetError()
		            );
		return;
	}

	if (format != NULL || format != nullptr) {
		*format = this->format;
	}

	if (access != NULL || access != nullptr) {
		*access = this->access;
	}

	if (w != NULL || w != nullptr) {
		*w = this->w;
	}

	if (h != NULL || h != nullptr) {
		*h = this->h;
	}
}

/* ========= Getters =========*/

/**
 * @brief Get the texture access of the texture
 *
 * @return SDL_TextureAccess
 */
SDL_TextureAccess Texture::getAccess()
{
	null_check();
	return (SDL_TextureAccess)(this->access);
}

Uint8 Texture::getAlphaMod()
{
	null_check();
	Uint8 mod = 0;
	if (SDL_GetTextureAlphaMod(this->texture, &mod) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		             "Texture (%p) : Error while getting Alpha Mod of (%p) %s",
		             this, texture, SDL_GetError()
		            );
	}
	return mod;
}

Uint8 Texture::getBlendMod()
{
	return 0x0; // FIXME: Method stub
}

Uint8 Texture::getColorMod()
{
	return 0x0; // FIXME: Method stub
}

Uint32 Texture::getFormat()
{
	null_check();
	return this->format;
}

int Texture::getWidth()
{
	null_check();
	return this->w;
}

int Texture::getHeight()
{
	null_check();
	return this->h;
}

/* ========= Setters =========*/

void Texture::setAlphaMod(Uint8 mod)
{
	// FIXME: Method stub
}

void Texture::setBlendMod(Uint8 mod)
{
	// FIXME: Method stub
}

void Texture::setColorMod(Uint8 mod)
{
	// FIXME: Method stub
}
