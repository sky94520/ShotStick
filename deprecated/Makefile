SDL2_flags := -lSDL2_image -lSDL2_net -ltiff -ljpeg -lpng -lz -lSDL2_ttf -lfreetype -lSDL2_mixer -lSDL2_test -lsmpeg2 -lvorbisfile -lvorbis -logg -lstdc++ -lSDL2 -lEGL -lGLESv1_CM -lGLESv2 -landroid
#CPP_FILES := $(wildcard *.cpp)
CPP_FILES := main.cpp Game.cpp ShotStick.cpp Player.cpp Font.cpp TextureManager.cpp Fps.cpp Timer.cpp
OBJ_FILES := $(subst .cpp,.o,$(CPP_FILES))

cpp_flags := -std=c++11
#是不是必须用all
.PHONY : all
all : main

main : $(OBJ_FILES)
	 $(CXX) $(SDL2_flags) $^ -o $@

$(OBJ_FILES):%.o: %.cpp
	 $(CXX) $(cpp_flags) -c $<
.PHONY : clean
clean :
	 rm -f *.o
	 rm -f main