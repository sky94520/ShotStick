#pragma once

#include<string>
#include<stdexcept>

#include "SDL.h"
#include "SDL_ttf.h"
  /* 唯一单例类 */
  class Font 
  {
private:
  Font();
  ~Font();
  static Font *s_pInstance;
public:
  static Font *Instance();
  /* 输出字体 */
  SDL_Texture *RenderText(SDL_Renderer * ren, std::string message,
                          std::string fontFile, SDL_Color color, int fontSize);
};
typedef Font TheFont;