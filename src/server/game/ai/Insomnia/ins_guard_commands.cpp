bool HandleAddGuardAgentCommand(ChatHandler* handler, const char* args)
{
    if (!*args)
        return false;

    uint32 entry = atoi(args);
    if (!entry)
        return false;

    // превръщаме entry → клас
    uint8 cls = InsGuardClassFromEntry(entry);
    if (!cls)
    {
        handler->PSendSysMessage("Invalid guard entry: %u", entry);
        return true;
    }

    // създаваме Guard-Agent
    InsPlayerBot* bot = InsPlayerBotMgr::CreateBot(cls, 80, ObjectGuid::Empty);
    if (!bot)
    {
        handler->PSendSysMessage("Failed to create Guard-Agent.");
        return true;
    }

    handler->PSendSysMessage("Guard-Agent %u created.", entry);
    return true;
    bool HandleAddGuardAgentCommand(ChatHandler* handler, const char* args)
{
    ...
}
{ "g-", SEC_ADMIN, false, &HandleAddGuardAgentCommand, "" },

}
