cmake_minimum_required(VERSION 3.23)
project(Secret-Agent C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

########## SDL2
set(SDL2_PATH "C:/C_Libraries/SDL2-2.28.5/x86_64-w64-mingw32")

########## SDL2_TTF
set(SDL_TTF_LIBRARY "C:/C_Libraries/SDL2_ttf-2.20.2/x86_64-w64-mingw32/lib/libSDL2_ttf.dll.a")
set(SDL_TTF_INCLUDE_DIR "C:/C_Libraries/SDL2_ttf-2.20.2/x86_64-w64-mingw32/include")

########## SDL2_MIXER
set(SDL2_MIXER_LIBRARY "C:/C_Libraries/SDL2_mixer-2.6.3/x86_64-w64-mingw32/lib/libSDL2_mixer.dll.a")
set(SDL2_MIXER_INCLUDE_DIR "C:/C_Libraries/SDL2_mixer-2.6.3/x86_64-w64-mingw32/include")

########## SDL2_IMAGE
set(SDL2_IMAGE_LIBRARY "C:/C_Libraries/SDL2_image-2.8.2/x86_64-w64-mingw32/lib/libSDL2_image.dll.a")
set(SDL2_IMAGE_INCLUDE_DIR "C:/C_Libraries/SDL2_image-2.8.2/x86_64-w64-mingw32/include")

########## CURL
# set(CURL_INCLUDE_DIR "C:/C_Libraries/curl-8.4.0/include")
# set(CURL_LIBRARY "C:/C_Libraries/curl-8.4.0/lib")

########## FIND PACKAGE
find_package(SDL2 REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
# find_package(CURL REQUIRED)


########## INCLUDE DIR
include_directories(${SDL2_INCLUDE_DIR} ${SDL_TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})
# include_directories(${CURL_INCLUDE_DIR})


########## EXECUTABLE
add_executable(Secret-Agent main.c src/c_files/global_functions.c src/c_files/interface.c src/c_files/musics.c src/includes/musics.h src/includes/audioData.h src/c_files/menu.c src/c_files/player.c src/c_files/building.c src/c_files/interactivesParts.c)

########## TARGET_LINK_LIB
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL_TTF_LIBRARY} ${SDL2_MIXER_LIBRARY} ${SDL2_IMAGE_LIBRARY})

# target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} CURL::libcurl)
