#pragma once

class BotAI;
class Unit;

class InsomniaInstincts
{
public:
    // Main entry point – called from BotAI::UpdateAI()
    static void UpdateInstincts(BotAI* ai, Unit* target);

private:
    // Instinct layers
    static void ApplySurvival(BotAI* ai);
    static void ApplyProtective(BotAI* ai);
    static void ApplyDominance(BotAI* ai);
    static void ApplyRevenge(BotAI* ai);
};

