#include "Player.h"

Player::Player(Sprite* pSprite, float x, float y) : m_pSprite(pSprite), m_XPos(x), m_YPos(y)
{
    updateRect();

    m_WalkSpeed = 128.0f;
    m_CurrAction = ActorActions::IDLE;
}

Player::~Player() {}

void Player::doAction(ActorActions action)
{
    m_CurrAction = action;
}

void Player::update(size_t dt)
{
    switch(m_CurrAction)
    {
        case ActorActions::IDLE:
            // NOTHING TO DO
            break;

        case ActorActions::MOVE_LEFT:
            m_XPos -= m_WalkSpeed * dt / 1000.0f;
            updateRect();
            break;

        case ActorActions::MOVE_RIGHT:
            m_XPos += m_WalkSpeed * dt / 1000.0f;
            updateRect();
            break;
    }
}

void Player::draw(Camera& cam) const
{
    int offsetX = cam.getDrawRect().x;
    int offsetY = cam.getDrawRect().y;
    m_pSprite->drawFrame(*(cam.getGraphics()), 0, m_XPos - offsetX, m_YPos- offsetY, Anchor::HCENTER | Anchor::BOTTOM);

//    RECT tmp = m_Rect;
//    tmp.x -= offsetX;
//    tmp.y -= offsetY;
//    cam.getGraphics()->drawRect(tmp, 0xFFAAFF80);
}

const RECT& Player::getBounds() const
{
    return m_Rect;
}

void Player::updateRect()
{
    m_Rect.w = m_pSprite->getFrame(0).getWidth();
    m_Rect.h = m_pSprite->getFrame(0).getHeight();
    m_Rect.x = m_XPos - m_Rect.w / 2;
    m_Rect.y = m_YPos - m_Rect.h;
}
