    /*
                    .__      .___.                
                    [__)  .    |   _ ._ _ ._ _   .
                    [__)\_|    |  (_)[ | )[ | )\_|
                            ._|                    ._|
     
                            Was for Omni-WoW
                            Now: Released - 5/4/2012
    */
    #include "OutdoorPvPBT.h"
     
    OutdoorPvPBT::OutdoorPvPBT()
    {
            m_TypeId = OUTDOOR_PVP_BT;
            m_ally_gathered = BT_RESOURCES_A;
            m_horde_gathered = BT_RESOURCES_H;
            IS_ABLE_TO_SHOW_MESSAGE = false;
            IS_RESOURCE_MESSAGE_A = false;
            IS_RESOURCE_MESSAGE_H = false;
            m_FirstLoad = false;
            limit_A = 0;
            limit_H = 0;
            m_LastWin = 0;
            limit_resources_message_A = 0;
            limit_resources_message_H = 0;
    }
     
    bool OutdoorPvPBT::SetupOutdoorPvP()
    {
        RegisterZone(3537);
        return true;
    }
     
    void OutdoorPvPBT::HandlePlayerEnterZone(Player * player, uint32 zone)
    {      
            char message[250];
            if(player->GetTeam() == ALLIANCE)
                    snprintf(message, 250, "[Borean Tundra Defense]: Alliance has %u resources!", m_ally_gathered);
            else
                    snprintf(message, 250, "[Borean Tundra Defense]: Horde has %u resources!", m_horde_gathered);
     
            player->MonsterTextEmote(message, player->GetGUID());
            OutdoorPvP::HandlePlayerEnterZone(player, zone);
    }
     
    void OutdoorPvPBT::HandlePlayerLeaveZone(Player * player, uint32 zone)
    {
            player->MonsterTextEmote("You're leaving while the zone PvP is active!", player->GetGUID());
            OutdoorPvP::HandlePlayerLeaveZone(player, zone);
    }
     
    void OutdoorPvPBT::HandleWinMessage(const char * message)
    {
            sWorld->SendZoneText(3537, message);
    }
     
    void OutdoorPvPBT::PlaySounds(bool side)
    {
            SessionMap m_sessions = sWorld->GetAllSessions();
            for(SessionMap::iterator itr = m_sessions.begin(); itr != m_sessions.end(); ++itr)
            {
                    if(!itr->second || !itr->second->GetPlayer() || !itr->second->GetPlayer()->IsInWorld() ||
                            itr->second->GetPlayer()->GetZoneId() != 3537)
                            continue;
     
                    if(itr->second->GetPlayer()->GetZoneId() == 3537)
                    {
                            if(itr->second->GetPlayer()->GetTeam() == ALLIANCE && side == true)
                                    itr->second->GetPlayer()->PlayDirectSound(BT_SOUND_ALLIANCE_GOOD, itr->second->GetPlayer());
                            else
                                    itr->second->GetPlayer()->PlayDirectSound(BT_SOUND_HORDE_GOOD, itr->second->GetPlayer());
                    }
            }
    }
     
    void OutdoorPvPBT::HandleReset()
    {
            m_ally_gathered = BT_RESOURCES_A;
            m_horde_gathered = BT_RESOURCES_H;
            IS_ABLE_TO_SHOW_MESSAGE = false;
            IS_RESOURCE_MESSAGE_A = false;
            IS_RESOURCE_MESSAGE_H = false;
            m_FirstLoad = false;
            limit_A = 0;
            limit_H = 0;
            limit_resources_message_A = 0;
            limit_resources_message_H = 0;
            sLog->outString("[OutdoorPvPBT]: Borean Tundra : HandleReset()");
    }
     
    void OutdoorPvPBT::HandleBuffs(Player * player, bool loser)
    {
            if(loser)
            {
                    for(int i = 0; i < LOSE_BUFFS; i++)
                            player->CastSpell(player, LoseBuffs[i], true);
            }
            else
            {
                    for(int i = 0; i < WIN_BUFFS; i++)
                            player->CastSpell(player, WinBuffs[i], true);
            }
    }
     
    void OutdoorPvPBT::HandleRewards(Player * player, uint32 honorpointsorarena, bool honor, bool arena, bool both)
    {
            char msg[250];
            uint32 m_GetHonorPoints = player->GetHonorPoints();
            uint32 m_GetArenaPoints = player->GetArenaPoints();
            if(honor)
            {
                    player->SetHonorPoints(m_GetHonorPoints + honorpointsorarena);
                    snprintf(msg, 250, "You received %u extra honor points!", honorpointsorarena);
            }
            else if(arena)
            {
                    player->SetArenaPoints(m_GetArenaPoints + honorpointsorarena);
                    snprintf(msg, 250, "You received %u extra arena points!", honorpointsorarena);
            }
            else if(both)
            {
                player->SetHonorPoints(m_GetHonorPoints + honorpointsorarena);
                    player->SetArenaPoints(m_GetArenaPoints + honorpointsorarena);
                    snprintf(msg, 250, "You received %u extra honor and arena points!", honorpointsorarena);
            }
            HandleWinMessage(msg);
    }
     
    bool OutdoorPvPBT::Update(uint32 diff)
    {
            OutdoorPvP::Update(diff);
            if(m_FirstLoad == false)
            {
                    if(m_LastWin == ALLIANCE)
                       sLog->outString("[OutdoorPvPBT]: Borean Tundra has started! Last Winner: Alliance(%u)", ALLIANCE);
                    else if(m_LastWin == HORDE)
                       sLog->outString("[OutdoorPvPBT]: Borean Tundra has started! Last Winner: Horde(%u)", HORDE);
                    else if(m_LastWin == 0)
                       sLog->outString("[OutdoorPvPBT]: Borean Tundra has started! Last Winner: Neutral(0)");
                    m_FirstLoad = true;
            }
     
            if(m_ally_gathered <= 50 && limit_A == 0)
            {
               IS_ABLE_TO_SHOW_MESSAGE = true; // We allow the message to pass
               IS_RESOURCE_MESSAGE_A = true; // We allow the message to be shown
               limit_A = 1; // We set this to one to stop the spamming
               PlaySounds(false);
            }
            else if(m_horde_gathered <= 50 && limit_H == 0)
            {
                    IS_ABLE_TO_SHOW_MESSAGE = true; // We allow the message to pass
                    IS_RESOURCE_MESSAGE_H = true; // We allow the message to be shown
                    limit_H = 1; // Same as above
                    PlaySounds(true);
            }
            else if(m_ally_gathered <= 0 && limit_A == 1)
            {
                    IS_ABLE_TO_SHOW_MESSAGE = true; // We allow the message to pass
                    IS_RESOURCE_MESSAGE_A = true; // We allow the message to be shown
                    limit_A = 2;
                    PlaySounds(false);
            }
            else if(m_horde_gathered <= 0 && limit_H == 1)
            {
                    IS_ABLE_TO_SHOW_MESSAGE = true; // We allow the message to pass
                    IS_RESOURCE_MESSAGE_H = true; // We allow the message to be shown
                    limit_H = 2;
                    PlaySounds(true);
            }
            else if(m_ally_gathered <= 300 && limit_resources_message_A == 0)
            {
                    IS_ABLE_TO_SHOW_MESSAGE = true;
                    limit_resources_message_A = 1;
                    PlaySounds(false);
            }
            else if(m_horde_gathered <= 300 && limit_resources_message_H == 0)
            {
                    IS_ABLE_TO_SHOW_MESSAGE = true;
                    limit_resources_message_H = 1;
                    PlaySounds(true);
            }
            else if(m_ally_gathered <= 200 && limit_resources_message_A == 1)
            {
                    IS_ABLE_TO_SHOW_MESSAGE = true;
                    limit_resources_message_A = 2;
                    PlaySounds(false);
            }
            else if(m_horde_gathered <= 200 && limit_resources_message_H == 1)
            {
                    IS_ABLE_TO_SHOW_MESSAGE = true;
                    limit_resources_message_H = 2;
                    PlaySounds(true);
            }
            else if(m_ally_gathered <= 100 && limit_resources_message_A == 2)
            {
                    IS_ABLE_TO_SHOW_MESSAGE = true;
                    limit_resources_message_A = 3;
                    PlaySounds(false);
            }
            else if(m_horde_gathered <= 100 && limit_resources_message_H == 2)
            {
                    IS_ABLE_TO_SHOW_MESSAGE = true;
                    limit_resources_message_H = 3;
                    PlaySounds(true);
            }
     
            if(IS_ABLE_TO_SHOW_MESSAGE == true) // This will limit the spam
            {
                    SessionMap m_sessions = sWorld->GetAllSessions();
                    for(SessionMap::iterator itr = m_sessions.begin(); itr != m_sessions.end(); ++itr) // We're searching for all the sessions(Players)
                    {
                            if(!itr->second || !itr->second->GetPlayer() || !itr->second->GetPlayer()->IsInWorld() ||
                                    itr->second->GetPlayer()->GetZoneId() != 3537)
                                    continue;
     
                            if(itr->second->GetPlayer()->GetZoneId() == 3537)
                            {
                                    char msg[250];
                                    if(limit_resources_message_A == 1 || limit_resources_message_A == 2 || limit_resources_message_A == 3)
                                    {
                                            snprintf(msg, 1024, "[Borean Tundra Defense]: Alliance has %u resources remaining!", m_ally_gathered);
                                            itr->second->GetPlayer()->MonsterTextEmote(msg, itr->second->GetPlayer()->GetGUID());
                                    }
                                    else if(limit_resources_message_H == 1 || limit_resources_message_H == 2 || limit_resources_message_H == 3)
                                    {
                                            snprintf(msg, 1024, "[Borean Tundra Defense]: Horde has %u resources remaining!", m_horde_gathered);
                                            itr->second->GetPlayer()->MonsterTextEmote(msg, itr->second->GetPlayer()->GetGUID());
                                    }
     
                                    if(IS_RESOURCE_MESSAGE_A == true)
                                    {
                                            if(limit_A == 1)
                                            {
                                                    snprintf(msg, 1024, "[Borean Tundra Defense]: Alliance has %u resources remaining!", m_ally_gathered);
                                                    itr->second->GetPlayer()->MonsterTextEmote(msg, itr->second->GetPlayer()->GetGUID());
                                                    IS_RESOURCE_MESSAGE_A = false; // Reset
                                            }
                                            else if(limit_A == 2)
                                            {
                                                    itr->second->GetPlayer()->MonsterTextEmote("[Borean Tundra Defense]: Alliance has 0 resources! Horde wins!",
                                                    itr->second->GetPlayer()->GetGUID());
                                                    HandleWinMessage("Horde Wins!");
                                                    HandleRewards(itr->second->GetPlayer(), 1500, true, false, false);
                                                    switch(itr->second->GetPlayer()->GetTeam())
                                                    {
                                                       case ALLIANCE:
                                                           HandleBuffs(itr->second->GetPlayer(), true);
                                                       break;
     
                                                       case HORDE:
                                                               HandleBuffs(itr->second->GetPlayer(), false);
                                                       break;
                                                    }
                                                    m_LastWin = HORDE;
                                                    IS_RESOURCE_MESSAGE_A = false; // Reset
                                            }
                                    }
                                    else if(IS_RESOURCE_MESSAGE_H == true)
                                    {
                                            if(limit_H == 1)
                                            {
                                                    snprintf(msg, 1024, "[Borean Tundra Defense]: Horde has %u resources remaining!", m_horde_gathered);
                                                    itr->second->GetPlayer()->MonsterTextEmote(msg, itr->second->GetPlayer()->GetGUID());
                                                    IS_RESOURCE_MESSAGE_H = false; // Reset
                                            }
                                            else if(limit_H == 2)
                                            {
                                                    itr->second->GetPlayer()->MonsterTextEmote("[Borean Tundra Defense]: Horde has 0 resources! Alliance wins!",
                                                    itr->second->GetPlayer()->GetGUID());
                                                    HandleWinMessage("Alliance Wins!");
                                                    HandleRewards(itr->second->GetPlayer(), 1500, true, false, false);
                                                    switch(itr->second->GetPlayer()->GetTeam())
                                                    {
                                                       case ALLIANCE:
                                                           HandleBuffs(itr->second->GetPlayer(), false);
                                                       break;
     
                                                       case HORDE:
                                                               HandleBuffs(itr->second->GetPlayer(), true);
                                                       break;
                                                    }
                                                    m_LastWin = ALLIANCE;
                                                    IS_RESOURCE_MESSAGE_H = false; // Reset
                                            }
                                    }
                            }
                            else
                            {
                                    // Don't send anything
                            }
                    }
            }
            IS_ABLE_TO_SHOW_MESSAGE = false; // Reset
            return false;
    }
     
    void OutdoorPvPBT::Randomizer(Player * player)
    {
            switch(urand(0, 4))
            {
                    case 0:
                            HandleRewards(player, 17, true, false, false);
                    break;
     
                    case 1:
                            HandleRewards(player, 11, true, false, false);
                    break;
     
                    case 2:
                            HandleRewards(player, 19, true, false, false);
                    break;
     
                    case 3:
                            HandleRewards(player, 22, true, false, false);
                    break;
            }
    }
     
    void OutdoorPvPBT::HandleKill(Player * player, Unit * killed)
    {
            uint32 take = POINTS_LOSE_ON_NPC_KILL;
            if(killed->GetTypeId() == TYPEID_PLAYER) // Killing players will take their resources away. It also gives extra honor.
            {
                    if(player->GetGUID() != killed->GetGUID())
                            return;
     
                    switch(killed->ToPlayer()->GetTeam())
                    {
                       case ALLIANCE:
                               m_ally_gathered -= take;
                               Randomizer(player);
                       break;
     
                       case HORDE:
                               m_horde_gathered -= take;
                               Randomizer(player);
                       break;
                    }
            }
            else // If is something besides a player
            {
                    if(player->GetTeam() == ALLIANCE)
                    {
                            switch(killed->GetEntry()) // Alliance killing horde guards
                            {
                                case WARSONG_BATTLEGUARD:
                                            m_horde_gathered -= take;
                                            Randomizer(player); // Randomizes the honor reward
                                    break;
     
                                case WARSONG_BATTLEGUARD_2: // 2?
                                            m_horde_gathered -= take;
                                            Randomizer(player); // Randomizes the honor reward
                                    break;
     
                                case WARSONG_CAPTAIN:
                                            m_horde_gathered -= take;
                                            Randomizer(player); // Randomizes the honor reward
                                    break;
     
                                case WARSONG_CARAVAN_GUARD:
                                            m_horde_gathered -= take;
                                            Randomizer(player); // Randomizes the honor reward
                                    break;
     
                                case WARSONG_HONOR_GUARD:
                                            m_horde_gathered -= take;
                                            Randomizer(player); // Randomizes the honor reward
                                    break;
     
                                case WARSONG_MARKSMAN:
                                            m_horde_gathered -= take;
                                            Randomizer(player); // Randomizes the honor reward
                                    break;
     
                                case WARSONG_RECRUITMENT_OFFICER:
                                            m_horde_gathered -= take;
                                            Randomizer(player); // Randomizes the honor reward
                                    break;
     
                                case WARSONG_SCOUT:
                                            m_horde_gathered -= take;
                                            Randomizer(player); // Randomizes the honor reward
                                    break;
     
                                case WARSONG_WIND_RIDER:
                                            m_horde_gathered -= take;
                                            Randomizer(player); // Randomizes the honor reward
                                    break;
                            }
                    }
                    else // Horde
                    {
                            switch(killed->GetEntry()) // Horde killing alliance guards
                            {
                                case VALIANCE_KEEP_CANNONEER:
                                            m_ally_gathered -= take;
                                            Randomizer(player); // Randomizes the honor reward
                                break;
     
                                case VALIANCE_KEEP_DEFENDER:
                                            m_ally_gathered -= take;
                                            Randomizer(player); // Randomizes the honor reward
                                break;
     
                                case VALIANCE_KEEP_FISHERMAN:
                                            m_ally_gathered -= take;
                                            Randomizer(player); // Randomizes the honor reward
                                break;
     
                                case VALIANCE_KEEP_FOOTMAN: // Wrong?
                                            m_ally_gathered -= take;
                                            Randomizer(player); // Randomizes the honor reward
                                break;
     
                                case VALIANCE_KEEP_FOOTMAN_2: // 2?
                                            m_ally_gathered -= take;
                                            Randomizer(player); // Randomizes the honor reward
                                break;
     
                                case VALIANCE_KEEP_OFFICER:
                                            m_ally_gathered -= take;
                                            Randomizer(player); // Randomizes the honor reward
                                break;
     
                                case VALIANCE_KEEP_RIFLEMAN:
                                            m_ally_gathered -= take;
                                            Randomizer(player); // Randomizes the honor reward
                                break;
     
                                case VALIANCE_KEEP_WORKER:
                                            m_ally_gathered -= take;
                                            Randomizer(player); // Randomizes the honor reward
                                break;
     
                                case DURDAN_THUNDERBEAK:
                                            m_ally_gathered -= take;
                                            Randomizer(player); // Randomizes the honor reward
                                break;
                            }
                    }
            }
    }
     
    class pvp_borean_tundra : public OutdoorPvPScript
    {
        public:
     
            pvp_borean_tundra()
                : OutdoorPvPScript("pvp_borean_tundra")
            {
            }
     
            OutdoorPvP* GetOutdoorPvP() const
            {
                return new OutdoorPvPBT();
            }
    };
     
    void AddSC_pvp_bt()
    {
            new pvp_borean_tundra;
    }