#ifndef INS_PLAYERBOTMGR_H
#define INS_PLAYERBOTMGR_H

#include "Player.h"
#include "ObjectGuid.h"
#include <unordered_map>

class InsPlayerBot;

class InsPlayerBotMgr
{
public:
    static void Initialize();
    static void Update(uint32 diff);

    static InsPlayerBot* GetBot(Player* player);
    static InsPlayerBot* CreateBot(uint8 cls, uint8 level, ObjectGuid owner);
    static void RemoveBot(ObjectGuid botGuid);

    static void LoadBotsFromDB();
    static void SaveBotsToDB();

private:
    static std::unordered_map<ObjectGuid, InsPlayerBot*, ObjectGuid::Hash> _bots;
   InsPlayerBot* InsPlayerBotMgr::CreateBot(uint8 cls, uint8 level, ObjectGuid owner)
{
    // 1) Spawn NPC (Player*)
    Player* npc = sObjectMgr->CreateGuardAgent(cls, level);
    if (!npc)
        return nullptr;

    // 2) Създаваме InsPlayerBot обект
    InsPlayerBot* bot = new InsPlayerBot(npc);

    // 3) ЗАПАЗВАМЕ го в мениджъра
    _bots[npc->GetGUID()] = bot;

    return bot;
}
 
};

#endif // INS_PLAYERBOTMGR_H