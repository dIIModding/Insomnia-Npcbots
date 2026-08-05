#include "InsPlayerBotAI.h"
#include "InsPlayerBot.h"
#include "InsPlayerBotSocial.h"
#include "Player.h"
#include "MotionMaster.h"
#include "Unit.h"

InsPlayerBotAI::InsPlayerBotAI(Player* player, InsPlayerBot* bot)
    : PlayerAI(player), me(player), _bot(bot)
{
    _social = bot->GetSocial();
}

void InsPlayerBotAI::UpdateAI(uint32 diff)
{
    _checkTimer += diff;

    if (_checkTimer >= 500)
    {
        _checkTimer = 0;

        if (Player* master = me->GetMaster())
        {
            if (_social->ShouldFollow(master))
                DoFollow(master);
        }

        if (Unit* victim = me->GetVictim())
            DoCombat(victim);
    }
}

void InsPlayerBotAI::DoFollow(Player* target)
{
    if (!target)
        return;

    if (me->GetDistance(target) > 5.0f)
        me->GetMotionMaster()->MoveFollow(target, 2.0f, 0.0f);
}

void InsPlayerBotAI::DoStop()
{
    me->GetMotionMaster()->Clear();
}

void InsPlayerBotAI::DoCombat(Unit* target)
{
    if (!target)
        return;

    if (me->IsWithinMeleeRange(target))
        me->Attack(target, true);
    else
        me->GetMotionMaster()->MoveChase(target);
}