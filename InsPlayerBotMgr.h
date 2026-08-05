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
};

#endif // INS_PLAYERBOTMGR_H