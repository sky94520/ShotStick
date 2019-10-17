#ifndef __InputHandler_H__
#define __InputHandler_H__

#include "SDL.h"
#include "Vector2D.h"
#include<vector>

enum mouse_buttons
{
  LEFT = 0,
  MIDDLE = 1,
  RIGHT = 2
};

class InputHandler
{
private:
    InputHandler();
    ~InputHandler();

    static InputHandler* s_pInstance;

    std::vector<bool> m_mouseButtonStates;

    Vector2D *m_mousePosition;
    ///按键 keyboard specific
    const Uint8*m_keystates;
private:
    ///按键处理 keyboard events
    void onKeyDown();
    void onKeyUp();
    ///handle mouse events
    void onMouseMove(SDL_Event&event);
    void onMouseButtonDown(SDL_Event&event);
    void onMouseButtonUp(SDL_Event&event);
public:
    static InputHandler* Instance();

    void update();
    void clean();
    ///判断某一案件是否按下
    bool isKeyDown(SDL_Scancode key);
    Vector2D*getMousePosition();
    bool getMouseButtonState(int buttonNumber);
    //reset the mouse button states to false
    void reset();
};
typedef InputHandler TheInputHandler;

#endif
