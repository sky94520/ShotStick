#include "InputHandler.h"
#include "Game.h"

InputHandler*InputHandler::s_pInstance = NULL;

InputHandler*InputHandler::Instance()
{
    if(s_pInstance == NULL)
    {
        s_pInstance = new InputHandler();
    }
    return s_pInstance;
}
///构造函数
InputHandler::InputHandler()
	:m_keystates(SDL_GetKeyboardState(0))
{
    for(int i = 0;i < 3;i++)
    {
        m_mouseButtonStates.push_back(false);
    }
    ///分配内存
    m_mousePosition = new Vector2D();
}
InputHandler::~InputHandler()
{
    delete m_mousePosition;
}
void InputHandler::update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        /**更新按键*/
        switch(event.type)
        {
            ///exit
            case SDL_QUIT:
            TheGame::Instance()->quit();
            break;
            ///Mouse motion
            case SDL_MOUSEMOTION:
            onMouseMove(event);
            break;
            ///Mouse Button
            case SDL_MOUSEBUTTONDOWN:
            onMouseButtonDown(event);
            break;
            case SDL_MOUSEBUTTONUP:
            onMouseButtonUp(event);
            break;
            ///Keyboard
            case SDL_KEYDOWN:
            onKeyDown();
            break;
            case SDL_KEYUP:
            onKeyUp();
            break;
            default:
            break;
        }
    }
}
void InputHandler::clean()
{
}
Vector2D*InputHandler::getMousePosition()
{
    return m_mousePosition;
}
bool InputHandler::isKeyDown(SDL_Scancode key)
{
    if(m_keystates != NULL)
    {
        if(m_keystates[key] == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}
///private
void InputHandler::onKeyUp()
{
    m_keystates = SDL_GetKeyboardState(0);
}
void InputHandler::onKeyDown()
{
    m_keystates = SDL_GetKeyboardState(0);
}
void InputHandler::onMouseButtonDown(SDL_Event&event)
{
    if(event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtonStates[LEFT] = true;
    }
    if(event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtonStates[MIDDLE] = true;
    }
    if(event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtonStates[RIGHT] = true;
    }
}
void InputHandler::onMouseButtonUp(SDL_Event&event)
{
    if(event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtonStates[LEFT] = false;
    }
    if(event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtonStates[MIDDLE] = false;
    }
    if(event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtonStates[RIGHT] = false;
    }
}
void InputHandler::onMouseMove(SDL_Event&event)
{
    m_mousePosition->setX(event.motion.x);
    m_mousePosition->setY(event.motion.y);
}
bool InputHandler::getMouseButtonState(int buttonNumber)
{
    return m_mouseButtonStates[buttonNumber];
}
void InputHandler::reset()
{
    for(int i = 0;i < m_mouseButtonStates.size();i++)
    {
        m_mouseButtonStates[i] = false;
    }
}
