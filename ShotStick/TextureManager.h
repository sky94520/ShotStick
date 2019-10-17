#ifndef __TextureManager_H__
#define __TextureManager_H__

#include<iostream>
#include<map>
#include<string>
#include<stdexcept>

#include "SDL.h"
#include "SDL_image.h"
//管理图片的单例类
class TextureManager
{
private:
	static TextureManager*s_pInstance;
	TextureManager();
public:
	  ~TextureManager();
	  static TextureManager* Instance();
	  //绑定render
	  void bind(SDL_Renderer* renderer);
	  //加载图片
	  bool load(std::string fileName, std::string id);
	  //画出某一帧
	  void draw(std::string id, int x, int y, int width, int height,SDL_RendererFlip flip = SDL_FLIP_NONE);
	  void draw(std::string id,int x,int y,float times = 1.0,SDL_RendererFlip flip = SDL_FLIP_NONE);
	  //从id获取tex
	  SDL_Rect getTextureRectFromId(std::string id);
	  void update();
	  //void drawFrame(std::string id, int x, int y, int width, int height, int currentRow,int currentFrame, SDL_RendererFlip flip =SDL_FLIP_NONE);
	  //从map中清除id的Texture
	  void clearFromTextureMap(std::string id);
private:
    //键值保存SDL_Texture
	std::map <std::string, SDL_Texture* >m_textureMap;
	//保存SDL_Renderer
	SDL_Renderer* m_pRenderer;
	
};
typedef TextureManager TheTextureManager;
#endif