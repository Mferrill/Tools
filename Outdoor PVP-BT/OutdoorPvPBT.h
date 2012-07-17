/*
		.__      .___.                
		[__)  .    |   _ ._ _ ._ _   .
		[__)\_|    |  (_)[ | )[ | )\_|
			._|                    ._|

			Was for Omni-WoW
			Now: Released - 5/4/2012
*/
#ifndef OUTDOOR_PVP_BT_
#define OUTDOOR_PVP_BT_
#include "OutdoorPvP.h"
#include "OutdoorPvPMgr.h"
#include "Chat.h"
using namespace std;

#define POINTS_LOSE_ON_NPC_KILL 5
#define WIN_BUFFS 4
#define LOSE_BUFFS 2
const uint32 WinBuffs[WIN_BUFFS] = { 39233, 23948, 53899, 62213 }; // Whoever wins, gets these buffs
const uint32 LoseBuffs[LOSE_BUFFS] = { 23948, 40079}; // Whoever loses, gets this buff.
const uint32 BT_RESOURCES_A = 450;
const uint32 BT_RESOURCES_H = 450;

enum Sounds
{
	BT_SOUND_ALLIANCE_GOOD                  = 8173,
    BT_SOUND_HORDE_GOOD                     = 8213,
};

enum AllianceNpcs
{
	VALIANCE_KEEP_CANNONEER = 25306,
	VALIANCE_KEEP_DEFENDER = 29617,
	VALIANCE_KEEP_FISHERMAN = 27393,
	VALIANCE_KEEP_FOOTMAN = 25313,
	VALIANCE_KEEP_FOOTMAN_2 = 25253,
	VALIANCE_KEEP_OFFICER = 25759,
	VALIANCE_KEEP_RIFLEMAN = 25311,
	VALIANCE_KEEP_WORKER = 25271,
	DURDAN_THUNDERBEAK = 35131
};

enum HordeNpcs
{
	WARSONG_BATTLEGUARD = 51890,
	WARSONG_BATTLEGUARD_2 = 25242,
	WARSONG_CAPTAIN = 25446,
	WARSONG_CARAVAN_GUARD = 25338,
	WARSONG_HONOR_GUARD = 25243,
	WARSONG_MARKSMAN = 25244,
	WARSONG_RECRUITMENT_OFFICER = 25273,
	WARSONG_SCOUT = 25439,
	WARSONG_WIND_RIDER = 25286
};

class OutdoorPvPBT : public OutdoorPvP
{
   public:
	   /* OutdoorPvPBT Related */
	   OutdoorPvPBT();
	   bool SetupOutdoorPvP();

	   /* Handle Player Action */
	   void HandlePlayerEnterZone(Player * player, uint32 zone);
	   void HandlePlayerLeaveZone(Player * player, uint32 zone);

	   /* Handle Killer Kill */
	   void HandleKill(Player * player, Unit * killed);

	   /* Handle Randomizer */
	   void Randomizer(Player * player);

	   /* Buffs */
	   void HandleBuffs(Player * player, bool loser);

	   /* Chat */
	   void HandleWinMessage(const char * msg);

	   /* Reset */
	   void HandleReset();

	   /* Rewards */
	   void HandleRewards(Player * player, uint32 honororarenapoints, bool honor, bool arena, bool both);

	   /* Updates */
	   bool Update(uint32 diff);
	   
	   /* Sounds */
	   void PlaySounds(bool side);

    private:
		uint32 m_ally_gathered;
		uint32 m_horde_gathered;
		uint32 m_LastWin;
		bool IS_ABLE_TO_SHOW_MESSAGE;
		bool IS_RESOURCE_MESSAGE_A;
		bool IS_RESOURCE_MESSAGE_H;
		bool m_FirstLoad;
		int limit_A;
		int limit_H;
		int limit_resources_message_A;
		int limit_resources_message_H;
};
#endif
