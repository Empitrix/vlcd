echo "Downloading SDL2-devel-2.30.5-mingw.tar.gz"
wget "https://github.com/libsdl-org/SDL/releases/download/release-2.30.5/SDL2-devel-2.30.5-mingw.tar.gz" -P ./dist/
echo "Downloading SDL2_image-devel-2.8.2-mingw.tar.gz"
wget "https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-devel-2.8.2-mingw.tar.gz" -P ./dist/
echo "Downloading SDL2_net-devel-2.2.0-mingw.tar.gz"
wget "https://github.com/libsdl-org/SDL_net/releases/download/release-2.2.0/SDL2_net-devel-2.2.0-mingw.tar.gz" -P ./dist/
echo "Downloading SDL2_ttf-devel-2.22.0-mingw.tar.gz"
wget "https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.22.0/SDL2_ttf-devel-2.22.0-mingw.tar.gz" -P ./dist/


echo "Unpack SDL"
mkdir "./dist/sdl" 
tar -xvzf ".\dist\SDL2-devel-2.30.5-mingw.tar.gz" -C "./dist/sdl"

echo "Unpack Image"
mkdir "./dist/img"
tar -xvzf ".\dist\SDL2_image-devel-2.8.2-mingw.tar.gz" -C "./dist/img"

echo "Unpack Net"
mkdir "./dist/net"
tar -xvzf ".\dist\SDL2_net-devel-2.2.0-mingw.tar.gz" -C "./dist/net"

echo "Unpack TFF"
mkdir "./dist/tff"
tar -xvzf ".\dist\SDL2_ttf-devel-2.22.0-mingw.tar.gz" -C "./dist/tff"

mkdir "./sdl"
mkdir "./sdl/lib"
mkdir "./sdl/include"
mkdir "./sdl/include/SDL2"

cp "./dist/sdl/SDL2-2.30.5/i686-w64-mingw32/bin/SDL2.dll" "./SDL2.dll" -Force
cp "./dist/sdl/SDL2-2.30.5/i686-w64-mingw32/include/SDL2/*" "./sdl/include/SDL2/" -Force 
cp "./dist/sdl/SDL2-2.30.5/i686-w64-mingw32/lib/*" "./sdl/lib/" -Force

cp "./dist/net/SDL2_net-2.2.0/i686-w64-mingw32/bin/SDL2_net.dll" "./SDL2_net.dll" -Force
cp "./dist/net/SDL2_net-2.2.0/i686-w64-mingw32/include/SDL2/SDL_net.h" "./sdl/include/SDL2/" -Force
cp "./dist/net/SDL2_net-2.2.0/i686-w64-mingw32/lib/cmake/*" "./sdl/lib/cmake/" -Force
cp "./dist/net/SDL2_net-2.2.0/i686-w64-mingw32/lib/pkgconfig/*" "./sdl/lib/pkgconfig/" -Force
cp "./dist/net/SDL2_net-2.2.0/i686-w64-mingw32/lib/*" "./sdl/lib/" -Force


cp "./dist/img/SDL2_image-2.8.2/i686-w64-mingw32/bin/SDL2_image.dll" "./SDL2_image.dll" -Force
cp "./dist/img/SDL2_image-2.8.2/i686-w64-mingw32/include/SDL2/SDL_image.h" "./sdl/include/SDL2/" -Force
cp "./dist/img/SDL2_image-2.8.2/i686-w64-mingw32/lib/cmake/*" "./sdl/lib/cmake/" -Force
cp "./dist/img/SDL2_image-2.8.2/i686-w64-mingw32/lib/pkgconfig/*" "./sdl/lib/pkgconfig/" -Force
cp "./dist/img/SDL2_image-2.8.2/i686-w64-mingw32/lib/*" "./sdl/lib/" -Force


cp "./dist/tff/SDL2_ttf-2.22.0/i686-w64-mingw32/bin/SDL2_ttf.dll" "./SDL2_ttf.dll" -Force
cp "./dist/tff/SDL2_ttf-2.22.0/i686-w64-mingw32/include/SDL2/SDL_ttf.h" "./sdl/include/SDL2/" -Force
cp "./dist/tff/SDL2_ttf-2.22.0/i686-w64-mingw32/lib/cmake/*" "./sdl/lib/cmake/" -Force
cp "./dist/tff/SDL2_ttf-2.22.0/i686-w64-mingw32/lib/pkgconfig/*" "./sdl/lib/pkgconfig/" -Force
cp "./dist/tff/SDL2_ttf-2.22.0/i686-w64-mingw32/lib/*" "./sdl/lib/" -Force

rm "./dist" -Force

