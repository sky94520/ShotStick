#include "Player.h"
#include "ShotStick.h"
#include "TextureManager.h"

Player::Player()
{
}

Player::~Player()
{
}

bool Player::init(const string& spriteID)
{
	m_spriteID = spriteID;
	return true;
}

void Player::setVelocity(const Vector2D& velocity)
{
	m_velocity = velocity;
}

void Player::draw(SDL_Renderer*ren)
{
    TheTextureManager::Instance()->draw(m_spriteID,(int)m_position.getX(),(int)m_position.getY());
}

void Player::update()
{
	m_velocity *= 2;
	m_position += m_velocity;
	//m_velocity += m_acceleration;
}

void Player::clean()
{
}