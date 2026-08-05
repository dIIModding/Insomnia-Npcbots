#ifndef INS_PLAYERBOT_H
#define INS_PLAYERBOT_H

#include "Player.h"
#include <unordered_map>

class InsPlayerBotAI;
class InsPlayerBotSocial;

class InsPlayerBot
{
public:
    explicit InsPlayerBot(Player* player);
    ~InsPlayerBot();

    Player* GetPlayer() const { return _player; }

    InsPlayerBotAI* GetAI() const { return _ai; }
    InsPlayerBotSocial* GetSocial() const { return _social; }

    void Update(uint32 diff);

    // Affinity system
    int32 GetAffinity(ObjectGuid playerGuid) const;
    void AddAffinity(ObjectGuid playerGuid, int32 amount);
    void SetAffinity(ObjectGuid playerGuid, int32 value);

    void LoadAffinityFromDB();
    void SaveAffinityToDB();

private:
    Player* _player;
    InsPlayerBotAI* _ai;
    InsPlayerBotSocial* _social;

    std::unordered_map<ObjectGuid, int32, ObjectGuid::Hash> _affinity;
};

#endif // INS_PLAYERBOT_H