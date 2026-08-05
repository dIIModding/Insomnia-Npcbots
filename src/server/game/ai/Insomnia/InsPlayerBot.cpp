#include "InsPlayerBot.h"
#include "InsPlayerBotAI.h"
#include "InsPlayerBotSocial.h"
#include "Player.h"
#include "ObjectMgr.h"
#include "Log.h"

InsPlayerBot::InsPlayerBot(Player* player)
    : _player(player)
{
    if (!_player)
        return;

    // Guard-Agent флаг
    _isGuardAgent = true;

    // AI слой
    _ai = new InsPlayerBotAI(_player, this);

    // Social слой
    _social = new InsPlayerBotSocial(_player, this);

    // Зареждане на affinity
    LoadAffinityFromDB();
}

InsPlayerBot::~InsPlayerBot()
{
    SaveAffinityToDB();

    delete _ai;
    delete _social;
}

void InsPlayerBot::Update(uint32 diff)
{
    if (!_player)
        return;

    // AI tick
    if (_ai)
        _ai->UpdateAI(diff);

    // Social tick
    if (_social)
        _social->Update(diff);
}

/* -------------------------
 *  AFFINITY SYSTEM
 * ------------------------- */

int32 InsPlayerBot::GetAffinity(ObjectGuid guid) const
{
    auto it = _affinity.find(guid);
    if (it != _affinity.end())
        return it->second;

    return 0;
}

void InsPlayerBot::AddAffinity(ObjectGuid guid, int32 amount)
{
    _affinity[guid] += amount;
}

void InsPlayerBot::SetAffinity(ObjectGuid guid, int32 value)
{
    _affinity[guid] = value;
}

void InsPlayerBot::LoadAffinityFromDB()
{
    QueryResult result = CharacterDatabase.Query(
        "SELECT target_guid, affinity FROM ins_playerbot_affinity WHERE bot_guid = {}", 
        _player->GetGUID().GetCounter()
    );

    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        ObjectGuid target = ObjectGuid::Create<HighGuid::Player>(fields[0].Get<uint32>());
        int32 affinity = fields[1].Get<int32>();

        _affinity[target] = affinity;

    } while (result->NextRow());
}

void InsPlayerBot::SaveAffinityToDB()
{
    CharacterDatabase.Execute(
        "DELETE FROM ins_playerbot_affinity WHERE bot_guid = {}",
        _player->GetGUID().GetCounter()
    );

    for (auto const& [guid, affinity] : _affinity)
    {
        CharacterDatabase.Execute(
            "INSERT INTO ins_playerbot_affinity (bot_guid, target_guid, affinity) "
            "VALUES ({}, {}, {})",
            _player->GetGUID().GetCounter(),
            guid.GetCounter(),
            affinity
        );
    }
}
