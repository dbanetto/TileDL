# - Try to find SDL2_IMAGE

find_package(PkgConfig)
pkg_check_modules(SDL2_IMAGE QUIET sdl2_image)
set(SDL2_IMAGE_DEFINITIONS ${SDL2_IMAGE_CFLAGS_OTHER})

find_path(SDL2_IMAGE_INCLUDE_DIR SDL2/SDL_image.h
          HINTS ${SDL2_IMAGE_INCLUDEDIR} ${SDL2_IMAGE_INCLUDE_DIRS}
		  PATH_SUFFIXES SDL2 )

	  find_library(SDL2_IMAGE_LIBRARY NAMES SDL2_image
             HINTS ${SDL2_IMAGE_LIBDIR} ${SDL2_IMAGE_LIBRARY_DIRS} )

set(SDL2_IMAGE_LIBRARIES ${SDL2_IMAGE_LIBRARY} )
set(SDL2_IMAGE_INCLUDE_DIRS ${SDL2_IMAGE_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL_image  DEFAULT_MSG
                                  SDL2_IMAGE_LIBRARY SDL2_IMAGE_INCLUDE_DIR)

mark_as_advanced(SDL2_IMAGE_INCLUDE_DIR SDL2_IMAGE_LIBRARY )
