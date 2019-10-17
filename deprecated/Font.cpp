#include "Font.h"

Font*Font::s_pInstance = NULL;

Font::Font()
{
	if (!TTF_WasInit())
	    TTF_Init();
}
Font::~Font()
{
	TTF_Quit();
}
Font*Font::Instance()
{
	if (s_pInstance == NULL)
	   s_pInstance = new Font();
	return s_pInstance;
}
SDL_Texture*Font::RenderText(SDL_Renderer*ren,std::string message,std::string fontFile,SDL_Color color,int fontSize)
{
	TTF_Font*font = NULL;
	font = TTF_OpenFont(fontFile.c_str(),fontSize);
	
	if (font == NULL)
	   throw std::runtime_error(TTF_GetError());
	SDL_Surface*sur = TTF_RenderText_Blended(font,message.c_str(),color);
	SDL_Texture*tex = SDL_CreateTextureFromSurface(ren,sur);
	
	SDL_FreeSurface(sur);
	TTF_CloseFont(font);
	return tex;
}