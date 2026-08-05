#include "InsomniaInstincts.h"
#include "BotAI.h"
#include "Unit.h"
#include "Player.h"
#include "SpellMgr.h"
#include "MotionMaster.h"

void InsomniaInstincts::UpdateInstincts(BotAI* ai, Unit* target)
{
    if (!ai || !ai->GetBot() || !target)
        return;

    ApplySurvival(ai);
    ApplyProtective(ai);
    ApplyDominance(ai);
    ApplyRevenge(ai);
}

// =========================
//  SURVIVAL INSTINCT
// =========================
void InsomniaInstincts::ApplySurvival(BotAI* ai)
{
    Unit* bot = ai->GetBot();
    if (!bot)
        return;

    float hp = bot->GetHealthPct();

    // Activates when HP < 35%
    if (hp > 35.0f)
        return;

    // Step back / retreat
    if (Unit* victim = bot->GetVictim())
    {
        Position backPos;
        victim->GetNearPosition(backPos, 5.0f, bot->GetAngle(victim) + M_PI);
        bot->GetMotionMaster()->MovePoint(1, backPos);
    }

    // Defensive abilities
    const uint32 defensiveSpells[] =
    {
        871,    // Shield Wall
        498,    // Divine Protection
        22812,  // Barkskin
        19263   // Deterrence
    };

    for (uint32 spellId : defensiveSpells)
    {
        if (bot->HasSpell(spellId) && bot->IsSpellReady(spellId))
        {
            bot->CastSpell(bot, spellId, false);
            break;
        }
    }
}

// =========================
//  PROTECTIVE INSTINCT
// =========================
void InsomniaInstincts::ApplyProtective(BotAI* ai)
{
    Unit* bot = ai->GetBot();
    if (!bot)
        return;

    Player* owner = bot->GetCharmerOrOwnerPlayerOrPlayerItself();
    if (!owner)
        return;

    // Activates when player HP < 40%
    if (owner->GetHealthPct() > 40.0f)
        return;

    // Taunts
    const uint32 taunts[] =
    {
        355,    // Warrior Taunt
        6795,   // Druid Growl
        62124   // Paladin Hand of Reckoning
    };

    for (uint32 spellId : taunts)
    {
        if (bot->HasSpell(spellId) && bot->IsSpellReady(spellId))
        {
            if (Unit* target = owner->GetAttackerForHelper())
            {
                bot->CastSpell(target, spellId, false);
                break;
            }
        }
    }

    // Emergency heals
    const uint32 emergencyHeals[] =
    {
        2061,   // Flash Heal
        19750,  // Flash of Light
        8936    // Regrowth
    };

    for (uint32 spellId : emergencyHeals)
    {
        if (bot->HasSpell(spellId) && bot->IsSpellReady(spellId))
        {
            bot->CastSpell(owner, spellId, false);
            break;
        }
    }
}

// =========================
//  DOMINANCE INSTINCT
// =========================
void InsomniaInstincts::ApplyDominance(BotAI* ai)
{
    Unit* bot = ai->GetBot();
    if (!bot)
        return;

    Unit* target = bot->GetVictim();
    if (!target)
        return;

    // Activates when enemy HP < 40%
    if (target->GetHealthPct() > 40.0f)
        return;

    // Offensive cooldowns
    const uint32 offensiveSpells[] =
    {
        1719,   // Recklessness
        12042,  // Arcane Power
        31884   // Avenging Wrath
    };

    for (uint32 spellId : offensiveSpells)
    {
        if (bot->HasSpell(spellId) && bot->IsSpellReady(spellId))
        {
            bot->CastSpell(bot, spellId, false);
            break;
        }
    }

    bot->GetMotionMaster()->MoveChase(target);
}

// =========================
//  REVENGE INSTINCT
// =========================
void InsomniaInstincts::ApplyRevenge(BotAI* ai)
{
    Unit* bot = ai->GetBot();
    if (!bot)
        return;

    // Activates when bot HP < 20%
    if (bot->GetHealthPct() > 20.0f)
        return;

    Unit* attacker = bot->GetLastDamager();
    if (!attacker)
        return;

    bot->Attack(attacker, true);

    // Burst abilities
    const uint32 burstSpells[] =
    {
        30330,  // Mortal Strike
        23922,  // Shield Slam
        53351   // Kill Shot
    };

    for (uint32 spellId : burstSpells)
    {
        if (bot->HasSpell(spellId) && bot->IsSpellReady(spellId))
        {
            bot->CastSpell(attacker, spellId, false);
            break;
        }
    }
}

