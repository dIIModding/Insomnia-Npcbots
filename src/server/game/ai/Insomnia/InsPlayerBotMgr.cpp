#include "InsPlayerBotMgr.h"
#include "InsPlayerBot.h"
#include "Player.h"
#include "ObjectMgr.h"
#include "Log.h"

// глобална карта с всички активни ботове
std::unordered_map<ObjectGuid, InsPlayerBot*, ObjectGuid::Hash> InsPlayerBotMgr::_bots;

/* -------------------------------------------------------
 *  INITIALIZE
 * ------------------------------------------------------- */
void InsPlayerBotMgr::Initialize()
{
    LoadBotsFromDB();
    LOG_INFO("server", "InsPlayerBotMgr: initialized with {} bots.", _bots.size());
}

/* -------------------------------------------------------
 *  UPDATE TICK
 * ------------------------------------------------------- */
void InsPlayerBotMgr::Update(uint32 diff)
{
    for (auto& [guid, bot] : _bots)
    {
        if (bot)
            bot->Update(diff);
    }
}

/* -------------------------------------------------------
 *  GET BOT BY PLAYER*
 * ------------------------------------------------------- */
InsPlayerBot* InsPlayerBotMgr::GetBot(Player* player)
{
    if (!player)
        return nullptr;

    auto it = _bots.find(player->GetGUID());
    if (it != _bots.end())
        return it->second;

    return nullptr;
}

/* -------------------------------------------------------
 *  CREATE BOT (GUARD-AGENT)
 * ------------------------------------------------------- */
InsPlayerBot* InsPlayerBotMgr::CreateBot(uint8 cls, uint8 level, ObjectGuid owner)
{
    // 1) Създаваме NPC Player (Guard-Agent)
    Player* npc = sObjectMgr->CreateGuardAgent(cls, level);
    if (!npc)
    {
        LOG_ERROR("server", "InsPlayerBotMgr: failed to spawn Guard-Agent.");
        return nullptr;
    }

    // 2) Създаваме InsPlayerBot обект
    InsPlayerBot* bot = new InsPlayerBot(npc);

    // 3) Запазваме го в мениджъра
    _bots[npc->GetGUID()] = bot;

    // 4) Записваме го в DB
    CharacterDatabase.Execute(
        "INSERT INTO ins_playerbots (guid, class, level) VALUES ({}, {}, {})",
        npc->GetGUID().GetCounter(), cls, level
    );

    LOG_INFO("server", "InsPlayerBotMgr: Guard-Agent {} created (class {}, level {}).",
        npc->GetGUID().GetCounter(), cls, level);

    return bot;
}

/* -------------------------------------------------------
 *  REMOVE BOT
 * ------------------------------------------------------- */
void InsPlayerBotMgr::RemoveBot(ObjectGuid botGuid)
{
    auto it = _bots.find(botGuid);
    if (it == _bots.end())
        return;

    InsPlayerBot* bot = it->second;

    // премахваме NPC от света
    if (Player* npc = bot->GetPlayer())
        npc->DeleteFromDB();

    // премахваме от DB
    CharacterDatabase.Execute(
        "DELETE FROM ins_playerbots WHERE guid = {}",
        botGuid.GetCounter()
    );

    delete bot;
    _bots.erase(it);

    LOG_INFO("server", "InsPlayerBotMgr: Guard-Agent {} removed.", botGuid.GetCounter());
}

/* -------------------------------------------------------
 *  LOAD FROM DB
 * ------------------------------------------------------- */
void InsPlayerBotMgr::LoadBotsFromDB()
{
    QueryResult result = CharacterDatabase.Query("SELECT guid, class, level FROM ins_playerbots");
    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();

        uint32 guid = fields[0].Get<uint32>();
        uint8 cls   = fields[1].Get<uint8>();
        uint8 level = fields[2].Get<uint8>();

        // създаваме NPC от DB
        Player* npc = sObjectMgr->LoadGuardAgentFromDB(guid, cls, level);
        if (!npc)
            continue;

        // създаваме InsPlayerBot
        InsPlayerBot* bot = new InsPlayerBot(npc);
        _bots[npc->GetGUID()] = bot;

    } while (result->NextRow());

    LOG_INFO("server", "InsPlayerBotMgr: loaded {} bots from DB.", _bots.size());
}

/* -------------------------------------------------------
 *  SAVE ALL TO DB
 * ------------------------------------------------------- */
void InsPlayerBotMgr::SaveBotsToDB()
{
    for (auto const& [guid, bot] : _bots)
    {
        if (!bot || !bot->GetPlayer())
            continue;

        CharacterDatabase.Execute(
            "UPDATE ins_playerbots SET class = {}, level = {} WHERE guid = {}",
            bot->GetGuardClass(),
            bot->GetPlayer()->GetLevel(),
            guid.GetCounter()
        );
    }
}
