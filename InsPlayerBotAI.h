#ifndef INS_PLAYERBOTAI_H
#define INS_PLAYERBOTAI_H

#include "PlayerAI.h"
#include "Player.h"
#include "MotionMaster.h"

class InsPlayerBot;
class InsPlayerBotSocial;

class InsPlayerBotAI : public PlayerAI
{
public:
    explicit InsPlayerBotAI(Player* player, InsPlayerBot* bot);

    void UpdateAI(uint32 diff) override;

    void DoFollow(Player* target);
    void DoStop();
    void DoCombat(Unit* target);

private:
    Player* me;
    InsPlayerBot* _bot;
    InsPlayerBotSocial* _social;

    uint32 _checkTimer = 0;
};

#endif // INS_PLAYERBOTAI_H