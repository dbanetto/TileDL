#include "Surface.h"
#include <stdexcept>
#include <limits>
#include <SDL2/SDL_image.h>

using namespace tiledl;

SDL_Surface* tiledl::CreateSurface(int width, int height)
{
	auto surf = SDL_CreateRGBSurface(0, width, height, 32,
	                                 rmask, gmask, bmask, amask);

	if (surf != NULL) {
		return surf;
	}

	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
	             "Failed to create a surface with {w:%i,h:%i} : %s",
	             width, height, SDL_GetError()
	            );
	return nullptr;
}

/**
 * @brief Create an uninitialised Surface with no SDL_Surface
 *
 */
Surface::Surface()
{
	this->handle = nullptr;
	this->refcount = 0;
}

Surface::Surface(int width, int height)
{
	this->handle = CreateSurface(width, height);
	this->refcount = 0;

	null_check();
}

/**
 * @brief Creates Surface object with the SDL_Surface handle
 *
 * @param handle A SDL_Surface created outside of the class
 * @note increments refcount
 */
Surface::Surface(SDL_Surface* handle)
{
	this->handle = handle;
	this->refcount = 0;

	null_check();
	handle->refcount++;
}


/**
 * @brief Load surface from RWops
 *
 * @param src Source to read image from
 * @param freesrc if true, free the SDL_RWops after loading
 */
Surface::Surface(SDL_RWops* src, bool freesrc)
{
	this->handle = IMG_Load_RW(src, freesrc);
	this->refcount = 0;

	if (this->handle == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		             "Surface (%p): Failed to initialise from RWops (src:%p) : %s",
		             this, src, SDL_GetError()
		            );
	}
}

/**
 * @brief Load surface via src and treat it like the type file type
 *
 * @param src a SDL_RWops to load from
 * @param freesrc if true, frees SDL_RWops after loading
 * @param type A string that indicates which format type to interpret the image as.
 *             Here is a list of the currently recognized strings (case is not important)
 *
 * @note see http://www.libsdl.org/projects/SDL_image/docs/SDL_image.html#SEC13 for more info
 */
Surface::Surface(SDL_RWops* src, bool freesrc, char* type)
{
	this->handle = IMG_LoadTyped_RW(src, freesrc, type);
	this->refcount = 0;

	if (this->handle == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		             "Surface (%p): Failed to initialise from RWops (src:%p) type:%s : %s",
		             this, src, type, SDL_GetError()
		            );
	}
}

/**
 * @brief Load surface from file
 *
 * @param file path to file
 */
Surface::Surface(const char* file)
{
	this->handle = IMG_Load(file);
	this->refcount = 0;

	if (this->handle == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		             "Surface (%p): Failed to load image, path:%s : %s",
		             this, file, SDL_GetError()
		            );
	}
}


Surface::~Surface()
{
	this->destroy();
}

/**
 * @brief Checks if handle is null
 *
 * @return true if handle is not null, otherwise false
 */
bool Surface::isNull()
{
	return (this->handle == nullptr || this->handle == NULL);
}

void Surface::null_check()
{
	if (this->isNull()) {
		throw std::runtime_error("Cannot operate on a surface that has not been initialised");
	}
}

bool Surface::operator==(const Surface& other) const
{
	return this->handle == other.handle;
}

bool Surface::operator==(const SDL_Surface* other) const
{
	return this->handle == other;
}

/* Operations */

void Surface::lock()
{
	null_check();

	if (SDL_LockSurface(this->handle) != 0) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
		            "Surface (%p) : Failed to lock surface : %s",
		            this, SDL_GetError()
		           );
		return;
	}

	this->locked = true;
}

void Surface::unlock()
{
	null_check();

	SDL_UnlockSurface(this->handle);
}

/**
 * @brief Checks if the surface must be locked for access
 *
 * @return true if the surface must be locked for access
 */
bool Surface::mustLock()
{
	null_check();

	return (SDL_MUSTLOCK(this->handle) != 0);
}

bool Surface::isLocked()
{
	return this->locked;
}

void Surface::ref()
{
	null_check();

	if (this->refcount == std::numeric_limits<int>::max()) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
		            "Surface (%p) : reference count overflow. Has more than %i references",
		            this, std::numeric_limits<int>::max()
		           );
		return;
	}

	this->refcount++;
}

void Surface::deref()
{
	null_check();

	if (this->handle->refcount <= 0) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
		            "Texture (%p) : dereferenced when refcount is %i.",
		            this, this->refcount
		           );
		return;
	}

	this->refcount--;
}

/**
 * @brief Frees the SDL_Surface handle, IF and ONLY IF the refcount for the handle is less or equal to zero
 * In any case, the Surface will no longer point to the SDL_Surface handle.
 *
 * @return void
 */
void Surface::destroy()
{
	if (!this->isNull()) {
		this->handle->refcount--;

		if (this->refcount > 0) {
			SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
			            "Surface (%p) : Is being destroyed while refcount is greater than zero (%i).",
			            this, this->refcount
			           );
		}

		if (this->handle->refcount > 0) {
			SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
			            "Surface (%p) : Is being destroyed while the handle's refcount is greater than zero (%i).",
			            this, this->handle->refcount
			           );
		}

		if (this->handle->refcount <= 0) {
			SDL_FreeSurface(this->handle);
		} else {
			SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
			            "SDL_Surface (%p) : Has not been freed as refcount is greater than zero (%i.",
			            this->handle, this->handle->refcount
			           );
		}

		this->handle = nullptr;
	}
}

/**
 * @brief Resizes the surface by copying to a different size surface.
 * This is an expensive function. Surface must be unlocked
 *
 * @param newWidth  the new width of the surface
 * @param newHeight the new height of the surface
 * @note This re-created the surface with a different SDL_Surface handle,
 * and if the refcount is non-zero a warning is issued.
 *
 */
void Surface::resize(int newWidth, int newHeight)
{
	null_check();
	if (this->locked) {
		// During a surface is locked you cannot blit a surface
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		             "Surface (%p): Failed during resize, can not operate on a locked surface : %s",
		             this
		            );
		return;
	}
	auto newHandle = CreateSurface(newWidth, newHeight);

	if (this->handle == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		             "Surface (%p): Failed during resize, could not create new surface {w:%i,h:%i} : %s",
		             this, newWidth, newHeight, SDL_GetError()
		            );
		return;
	}

	if (SDL_BlitScaled(this->handle, NULL, newHandle, NULL) != 0) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
		            "Surface (%p): Failed during resize, BlitScale did not return 0 : %s",
		            this, SDL_GetError()
		           );
		SDL_FreeSurface(newHandle);
		return;
	}

	if (this->handle->refcount != 0) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
		            "Surface (%p): Resizing surface and handle's refcount is non-zero %i",
		            this, this->handle->refcount
		           );
	}

	// So there is no moment when this->handle is not a valid SDL_Surface
	auto oldHandle = this->handle;
	this->handle = newHandle;
	SDL_FreeSurface(oldHandle);
}

/**
 * @brief Resizes the surface by copying to a different size surface.
 * This is an expensive function. Surface must be unlocked
 *
 * @param newSize The new size of the Surface, only w and h are used
 * @note This re-created the surface with a different SDL_Surface handle,
 * and if the refcount is non-zero a warning is issued.
 *
 */
void Surface::resize(const Rectangle& newSize)
{
	this->resize(newSize.w, newSize.h);
}

bool Surface::SaveBMP(const char* file)
{
	null_check();

	if (SDL_SaveBMP(this->handle, file) != 0) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
		            "Surface (%p): Failed to save to bmp at %s : %s",
		            this, file, SDL_GetError()
		           );
		return false;
	}

	return true;
}

bool Surface::SaveBMP(SDL_RWops* dst, bool freedst)
{
	null_check();

	if (SDL_SaveBMP_RW(this->handle, dst, freedst) != 0) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
		            "Surface (%p): Failed to save to bmp using RWops %p, freedst:%u : %s",
		            this, dst, freedst, SDL_GetError()
		           );
		return false;
	}

	return true;
}

bool Surface::SavePNG(const char* file)
{
	null_check();

	if (IMG_SavePNG(this->handle, file) != 0) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
		            "Surface (%p): Failed to save to png at %s : %s",
		            this, file, SDL_GetError()
		           );
		return false;
	}

	return true;
}

bool Surface::SavePNG(SDL_RWops* dst, bool freedst)
{
	null_check();

	if (IMG_SavePNG_RW(this->handle, dst, freedst) != 0) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
		            "Surface (%p): Failed to save to png using RWops %p, freedst:%u : %s",
		            this, dst, freedst, SDL_GetError()
		           );
		return false;
	}

	return true;
}

/* Setters */

void Surface::setRLE(bool enable)
{
	null_check();

	if (SDL_SetSurfaceRLE(this->handle, enable) != 0) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
		            "Surface (%p): Failed to set RLE flag to %u : %s",
		            this, enable, SDL_GetError()
		           );
	}
}

void Surface::setAlphaMod(Uint8 alpha)
{
	null_check();

	if (SDL_SetSurfaceAlphaMod(this->handle, alpha) != 0) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
		            "Surface (%p): Failed to set alpha mod to %i : %s",
		            this, alpha, SDL_GetError()
		           );
	}
}

void Surface::setBlendMode(SDL_BlendMode blend)
{
	null_check();

	if (SDL_SetSurfaceBlendMode(this->handle, blend) != 0) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
		            "Surface (%p): Failed to set blend mode to %X : %s",
		            this, blend, SDL_GetError()
		           );
	}
}

void Surface::setColorMod(Color color)
{
	null_check();

	if (SDL_SetSurfaceColorMod(this->handle, color.r, color.g, color.b) != 0) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
		            "Surface (%p): Failed to set color mod to {%i,%i,%i} : %s",
		            this, color.r, color.b, color.g, SDL_GetError()
		           );
	}
}

/* Getters */

SDL_Surface* Surface::getHandle()
{
	return this->handle;
}


Rectangle Surface::getClipRect()
{
	null_check();

	return this->handle->clip_rect;
}



SDL_PixelFormat* Surface::getFormat()
{
	null_check();

	return this->handle->format;
}


int Surface::getWidth()
{
	null_check();

	return this->handle->w;
}

int Surface::getHeight()
{
	null_check();

	return this->handle->h;
}

int Surface::getPitch()
{
	null_check();

	return this->handle->pitch;
}

void* Surface::getUserData()
{
	null_check();

	return this->handle->userdata;
}

void* Surface::getPixels()
{
	null_check();

	return this->handle->pixels;
}

/**
 * @brief Get the Surface refcount
 *
 * @return int
 * @note this is not the handle's refcount. This can be incremented/decremented via ref/deref.
 */
int Surface::getRefCount()
{
	null_check();

	return this->refcount;
}

SDL_BlendMode Surface::getBlendMode()
{
	null_check();

	SDL_BlendMode out;

	if (SDL_GetSurfaceBlendMode(this->handle, &(out)) != 0) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
		            "Surface (%p): Failed to get blend mode : %s",
		            this, SDL_GetError()
		           );
	}

	return out;
}

Uint8 Surface::getAlphaMod()
{
	null_check();

	Uint8 out = 255;

	if (SDL_GetSurfaceAlphaMod(this->handle, &(out)) != 0) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
		            "Surface (%p): Failed to get alpha mod : %s",
		            this, SDL_GetError()
		           );
	}

	return out;
}

Color Surface::getColorMod()
{
	null_check();

	Color out(255, 255, 255);

	if (SDL_GetSurfaceColorMod(this->handle, &(out.r), &(out.g), &(out.b)) != 0) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
		            "Surface (%p): Failed to get color mod : %s",
		            this, SDL_GetError()
		           );
	}

	return out;
}
