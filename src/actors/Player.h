#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "../drawing/Sprite.h"

#include "Actor.h"

class Player : public IActor
{
public:

    Player(Sprite* pSprite, float x, float y);

    virtual ~Player();

    void doAction (ActorActions action);
    void update   (size_t dt);
    void draw     (Camera& cam) const;

    const RECT& getBounds() const;

private:
    Sprite*     m_pSprite;
    float       m_XPos;
    float       m_YPos;
    float       m_WalkSpeed;
    RECT        m_Rect;

    ActorActions m_CurrAction;

    // util functions
    void updateRect();
};

#endif // _PLAYER_H_
