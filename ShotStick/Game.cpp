#include "Game.h"
#include "TextureManager.h"
#include "ShotStick.h"
#include "Player.h"

Game*Game::s_pInstance = NULL;

Game::Game()
	:m_pWindow(nullptr)
	,m_pRenderer(nullptr)
	,m_bRunning(true)
	,m_gameWidth(0)
	,m_gameHeight(0)
	,m_pPlayer(nullptr)
	,m_pShotStick(nullptr)
{
}

Game* Game::getInstance()
{
	if (s_pInstance == NULL)
		s_pInstance = new Game();

	return s_pInstance;
}

bool Game::init(const char *title, int xpos, int ypos, int width, int height, int flags)
{
    m_bRunning = false;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		/// if succeeded create our window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != NULL)
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
		if (m_pRenderer != NULL)
			SDL_SetRenderDrawColor(m_pRenderer,210,250,255,255);
		else
			return false;
	}
	else
		return false;

	m_bRunning = true;
	std::string platform = SDL_GetPlatform();
	// init
	if (platform == "Android") {
		SDL_GetWindowSize(m_pWindow,&m_gameWidth,&m_gameHeight);
	}
	else {
		m_gameWidth = width;
		m_gameHeight = height;
	}
	SDL_Log("width=%d, height=%d\n", m_gameWidth, m_gameHeight);

	//结合SDL_Renderer
	TheTextureManager::Instance()->bind(m_pRenderer);
	/*加载图片资源*/
	try
	{
	    TheTextureManager::Instance()->load("Resources/icon.png","player");
	    TheTextureManager::Instance()->load("Resources/shotStick1.png","shotStick1");
	    TheTextureManager::Instance()->load("Resources/shotStick.png","shotStick2");
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}

	m_pPlayer = new Player();
	m_pPlayer->init("player");

	m_pShotStick = new ShotStick();
	m_pShotStick->init("shotStick1", "shotStick2");
	return true;
}

void Game::render()
{
	SDL_SetRenderDrawColor(m_pRenderer,210,250,255,255);
	///clear the renderer to the draw color
	SDL_RenderClear(m_pRenderer);
	///draw
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	SDL_Rect rect = { 0, 0, 200, 200 };
	SDL_RenderDrawRect(m_pRenderer, &rect);
	m_pPlayer->draw(m_pRenderer);
	m_pShotStick->draw(m_pRenderer);
	///draw to the screen
	SDL_RenderPresent(m_pRenderer);
}

void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		}
		m_pShotStick->handleEvents(&event);
	}
	auto velocity = m_pShotStick->getVelocity();
	m_pPlayer->setVelocity(velocity);
}

void Game::clean()
{
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void Game::update()
{
   m_pPlayer->update();
}
