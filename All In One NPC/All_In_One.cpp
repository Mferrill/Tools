/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 *
 * Copyright (C) 2009-2012 QuantumCore
 *
 * Copyright (C) 2009-2012 Crispi Custom Scripts Special For TrinityCore
 *
 * Release Data 15.05.2012 (Expecto)
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * GOSSIP_ICON_CHAT                = 0      White chat bubble
 * GOSSIP_ICON_VENDOR              = 1      Brown bag
 * GOSSIP_ICON_TAXI                = 2      Flight
 * GOSSIP_ICON_TRAINER             = 3      Book
 * GOSSIP_ICON_INTERACT_1          = 4      Interaction wheel
 * GOSSIP_ICON_INTERACT_2          = 5      Interaction wheel
 * GOSSIP_ICON_MONEY_BAG           = 6      Brown bag with yellow dot
 * GOSSIP_ICON_TALK                = 7      White chat bubble with black dots
 * GOSSIP_ICON_TABARD              = 8      Tabard
 * GOSSIP_ICON_BATTLE              = 9      Two swords
 * GOSSIP_ICON_DOT                 = 10     Yellow dot
 * GOSSIP_ICON_CHAT_11             = 11,    White chat bubble
 * GOSSIP_ICON_CHAT_12             = 12,    White chat bubble
 * GOSSIP_ICON_CHAT_13             = 13,    White chat bubble
 * GOSSIP_ICON_UNK_14              = 14,    INVALID - DO NOT USE
 * GOSSIP_ICON_UNK_15              = 15,    INVALID - DO NOT USE
 * GOSSIP_ICON_CHAT_16             = 16,    White chat bubble
 * GOSSIP_ICON_CHAT_17             = 17,    White chat bubble
 * GOSSIP_ICON_CHAT_18             = 18,    White chat bubble
 * GOSSIP_ICON_CHAT_19             = 19,    White chat bubble
 * GOSSIP_ICON_CHAT_20             = 20,    White chat bubble
 */

#include "ScriptPCH.h"
#include "Config.h"

#define EMOTE_NO_SICKNESS "You Dont Have Resurrection Sickness Aura!"
#define EMOTE_NO_DESERTER "You Dont Have Deserter Aura!"
#define EMOTE_COOLDOWN "Can Not Do It This Time..."
#define EMOTE_NO_ARENA_POINTS "You Have Enough Arena Points!"
#define EMOTE_TELEPORT_ONLY_HORDE "This Teleportation Is Allowed Only To Alliance!"
#define EMOTE_TELEPORT_ONLY_ALLIANCE "This Teleportation Is Allowed Only To Horde!"
#define EMOTE_NO_ENOUGH_EMBLEMS "You Have Enough Emblems!"
#define EMOTE_NO_MONEY "You Dont Have Enough Money!"
#define EMOTE_FUNCTION_OFF "Function Disable!"

#define MESSAGE_REMOVE_SICKNESS_COMPLETE "Resurrection Sickness Removed and Restore Full Health and Mana."
#define MESSAGE_REMOVE_DESERTER_COMPLETE "Deserter Removed! You Can Again Will Return In The Battleground!"
#define MESSAGE_CHARACTER_SAVE_TO_DB "You Character Has Been Saved!"
#define MESSAGE_RENAME_COMPLETE "Rename Complete. Exit The Game and The Remove Cache Folder From Client."
#define MESSAGE_CUSTOMIZE_COMPLETE "Customize Complete. Exit The Game and The Remove Cache Folder From Client."
#define MESSAGE_CHANGE_FACTION_COMPLETE "Change Faction Complete. Exit The Game and The Remove Cache Folder From Client." 
#define MESSAGE_CHANGE_RACE_COMPLETE "Change Race Complete. Exit The Game and The Remove Cache Folder From Client."
#define MESSAGE_RESET_QUEST_STATUS_COMPLETE "Your Daily and Weeekly Quest Cooldown Has Been Reset!"
#define MESSAGE_MAX_SKILL "You Skills Up To Maximum!"

enum MenuStructure
{
	SICKNESS_MENU  = 1,
	DESERTER_MENU  = 2,
	HEAL_MENU      = 3,
	SAVE_MENU      = 4,
	QUEST_MENU     = 5,
	SKILLS_MENU    = 6,
	TALENT_MENU    = 7,
	TELEPORT_MENU  = 8,
	BUFF_MENU      = 9,
	CUSTOMIZE_MENU = 10,
	EXCHANGE_MENU  = 11,
	MOVIE_MENU     = 12,
	FUNNY_MENU     = 13,
	MAIN_MENU      = 14,
};

enum Consts
{
	CONST_ARENA_RENAME         = 500,
	CONST_ARENA_CUSTOMIZE      = 500,
	CONST_ARENA_CHANGE_FACTION = 1500,
	CONST_ARENA_CHANGE_RACE    = 2000,
	SOUND_CUSTOMIZE            = 13838,

	CONST_FROST_TO_TRIUMPH  = 5,
	CONST_FROST_TO_CONQUEST = 5,
	CONST_FROST_TO_VALOR    = 5,
	CONST_FROST_TO_HEROISM  = 5,
	CONST_FROST_TO_JUSTICE  = 5,

	// Max Count Items For Exchange
	MARK_OF_HONOR_MAX       = 1,
	CHAMPIONS_SEAL_MAX      = 3,
	STONE_KEEPERS_SHARD_MAX = 5,
	COOKING_AWARD_MAX       = 1,
	JEWELCRAFTING_TOKEN_MAX = 1,

	CONST_TRIUMPH_TO_ALTERAC_VALLEY     = 5,
	CONST_TRIUMPH_TO_WARSONG_GULCH      = 5,
	CONST_TRIUMPH_TO_ARATHI_BASSIN      = 5,
	CONST_TRIUMPH_TO_EYE_OF_THE_STORM   = 5,
	CONST_TRIUMPH_TO_STRAND_OF_ANCIENTS = 5,
	CONST_TRIUMPH_TO_ISLE_OF_CONQUEST   = 5,
	CONST_TRIUMPH_TO_WINTERGRASP        = 5,

	CONST_FROST_TO_COOKING_AWARD        = 5,
	CONST_FROST_TO_JEWELCRAFTING_TOKEN  = 5,
	CONST_FROST_TO_CHAMPIONS_SEAL       = 5,
	CONST_FROST_TO_STONE_KEEPERS_SHARD  = 1,

	CONST_FOR_RESET_QUESTS_COOLDOWN = 300000000,
};

enum BuffSpells
{
	SPELL_POWER_WORD_FORTITUDE          = 48162,
	SPELL_PRAYER_OF_SPIRIT              = 48074,
	SPELL_SHADOW_PROTECTION             = 48170,
	SPELL_GREATER_BLESSING_OF_KINGS     = 43223,
	SPELL_GREATER_BLESSING_OF_MIGHT     = 48934,
	SPELL_GREATER_BLESSING_OF_WISDOM    = 48938,
	SPELL_GREATER_BLESSING_OF_SANCTUARY = 25899,
	SPELL_ARCANE_INTELLECT              = 36880,
	SPELL_DAMPEN_MAGIC                  = 43015,
	SPELL_AMPLIFY_MAGIC                 = 43017,
	SPELL_GIFT_OF_THE_WILD              = 69381,
	SPELL_THORNS                        = 467,
	SPELL_BRILLIANCE_INTELLECT          = 69994,
	SPELL_INFINITE_REPLENISHMENT        = 61782,
	SPELL_INNER_FIRE                    = 48168,
	SPELL_WATER_BREATHING               = 40621,
};

enum MiscSpells
{
	SPELL_RESURRECTION_SICKNESS = 15007,
	SPELL_DESERTER              = 26013,
	SPELL_FULL_HEAL             = 25840,
	SPELL_ANTI_HEAL_DEBUFF      = 45523,
};

enum Entries
{
	EMBLEM_OF_FROST    = 49426,
	EMBLEM_OF_TRIUMPH  = 47241,
	EMBLEM_OF_CONQUEST = 45624,
	EMBLEM_OF_VALOR    = 40753,
	EMBLEM_OF_HEROISM  = 40752,
	BADGE_OF_JUSTICE   = 29434,

	ALTERAC_VALLEY_MARK_OF_HONOR         = 20560,
	WARSONG_GULCH_MARK_OF_HONOR          = 20558,
	ARATHI_BASSIN_MARK_OF_HONOR          = 20559,
	EYE_OF_THE_STORM_MARK_OF_HONOR       = 29024,
	STRAND_OF_THE_ANCIENTS_MARK_OF_HONOR = 42425,
	ISLE_OF_CONQUEST_MARK_OF_HONOR       = 47395,
	WINTERGRASP_MARK_OF_HONOR            = 43589,

	DALARAN_COOKING_AWARD       = 43016,
	DALARAN_JEWELCRAFTING_TOKEN = 41596,
	CHAMPIONS_SEAL              = 44990,
	STONE_KEEPERS_SHARD         = 43228,

	MOVIE_WORLD_OF_WARCRAFT     = 2,
	MOVIE_THE_WRATH_GATE        = 14,
	MOVIE_FALL_OF_THE_LICH_KING = 16,
};

enum Actions
{
	// Customize Actions
	ACTION_RENAME                        = 496,
	ACTION_CUSTOMIZE                     = 497,
	ACTION_CHANGE_FACTION                = 498,
	ACTION_CHANGE_RACE                   = 499,
	// Teleport Actions
	ACTION_EASTERN_KINGDOMS              = 500,
	ACTION_KALIMDOR                      = 501,
	ACTION_OUTLAND                       = 502,
	ACTION_NORTHREND                     = 503,
	ACTION_INSTANCES                     = 504,
	ACTION_PVP_TERRITORY                 = 505,
	// Buff Actions
	ACTION_POWER_WORD_FORTITUDE          = 506,
	ACTION_PRAYER_OF_SPIRIT              = 507,
	ACTION_SHADOW_PROTECTION             = 508,
	ACTION_GREATER_BLESSING_OF_KINGS     = 509,
	ACTION_GREATER_BLESSING_OF_MIGHT     = 510,
	ACTION_GREATER_BLESSING_OF_WISDOM    = 511,
	ACTION_GREATER_BLESSING_OF_SANCTUARY = 512,
	ACTION_ARCANE_INTELLECT              = 513,
	ACTION_DAMPEN_MAGIC                  = 514,
	ACTION_AMPLIFY_MAGIC                 = 515,
	ACTION_GIFT_OF_THE_WILD              = 516,
	ACTION_THORNS                        = 517,
	ACTION_BRILLIANCE_INTELLECT          = 518,
	ACTION_INFINITE_REPLENISHMENT        = 519,
	ACTION_INNER_FIRE                    = 520,
	ACTION_WATER_BREATHING               = 521,
	//Exchange Service Actions
	ACTION_EMBLEM_EXCHANGE               = 522,
	ACTION_BG_MARK_EXCHANGE              = 523,
	ACTION_CURRENCY_EXCHANGE             = 524,
	// Emblem Exchange Actions
	ACTION_FROST_TO_TRIUMPH              = 525,
	ACTION_FROST_TO_CONQUEST             = 526,
	ACTION_FROST_TO_VALOR                = 527,
	ACTION_FROST_TO_HEROISM              = 528,
	ACTION_FROST_TO_JUSTICE              = 529,
	// BG Mark Exchange Actions
	ACTION_TRIUMPH_TO_ALTERAC_VALLEY     = 530,
	ACTION_TRIUMPH_TO_WARSONG_GULCH      = 531,
	ACTION_TRIUMPH_TO_ARATHI_BASSIN      = 532,
	ACTION_TRIUMPH_TO_EYE_OF_THE_STORM   = 533,
	ACTION_TRIUMPH_TO_STRAND_OF_ANCIENTS = 534,
	ACTION_TRIUMPH_TO_ISLE_OF_CONQUEST   = 535,
	ACTION_TRIUMPH_TO_WINTERGRASP        = 536,
	// Currency Exchange
	ACTION_FROST_TO_COOKING_AWARD        = 537,
	ACTION_FROST_TO_JEWELCRAFTING_TOKEN  = 538,
	ACTION_FROST_TO_CHAMPIONS_SEAL       = 539,
	ACTION_FROST_TO_STONE_KEEPERS_SHARD  = 540,
	// Movie Actions
	ACTION_MOVIE_WORLD_OF_WARCRAFT       = 541,
	ACTION_MOVIE_THE_WRATH_GATE          = 542,
	ACTION_MOVIE_FALL_OF_THE_LICH_KING   = 543,
	// Funny Actions
	ACTION_STARCRAFT_MURLOC              = 544,
	ACTION_AMBROSE_BOLTSPARK             = 545,
	ACTION_JONATHAN_THE_REVELATOR        = 546,
	ACTION_SHATTERED_SUN_MAGE            = 547,
	ACTION_WORGEN                        = 548,
	ACTION_PANDAREN_MONK                 = 549,
	ACTION_ALGALON                       = 550,
	ACTION_IRON_MENDER                   = 551,
	ACTION_DRUID                         = 552,
	ACTION_PRIEST                        = 553,
	ACTION_PALADIN                       = 554,
	ACTION_ROGUE                         = 555,
	ACTION_DEATH_KNIGHT                  = 556,
	ACTION_WARLOCK                       = 557,
	ACTION_WARRIOR                       = 558,
	ACTION_MAGE                          = 559,
	ACTION_SHAMAN                        = 560,
	ACTION_HUNTER                        = 561,
	ACTION_DRAENEI_GIRL_WHITE            = 562,
	ACTION_DRAENEI_GIRL_BLACK            = 563,
	ACTION_DEMORPH                       = 564,
};

enum Zones
{
	// Eastern Kingdoms
	DATA_ALTERAC_MOUNTAINS     = 100,
	DATA_ARATHI_HIGHLANDS      = 101,
	DATA_BADLANDS              = 102,
	DATA_BLACKROCK_MOUNTAIN    = 103,
	DATA_BLASTED_LANDS         = 104,
	DATA_BURNING_STEPPES       = 105,
	DATA_DEADWIND_PASS         = 106,
	DATA_DUN_MOROGH            = 107,
	DATA_DUSKWOOD              = 108,
	DATA_EASTERN_PLAGUELANDS   = 109,
	DATA_ELWYN_FOREST          = 110,
	DATA_EVERSONG_WOODS        = 111,
	DATA_GHOSTLANDS            = 112,
	DATA_HILLSBRAD_FOOTHILLS   = 113,
	DATA_IRONFORGE             = 114,
	DATA_ISLE_OF_QUEL_DANAS    = 115,
	DATA_LOCH_MODAN            = 116,
	DATA_EBON_HOLD             = 117,
	DATA_REDRIGE_MOUNTAINS     = 118,
	DATA_SEARING_GORGE         = 119,
	DATA_SILVERMOON_CITY       = 120,
	DATA_SILVERPINE_FOREST     = 121,
	DATA_STORMWIND_CITY        = 122,
	DATA_STRANGLETHORN_VALE    = 123,
	DATA_SWAMP_OF_SORROWS      = 124,
	DATA_THE_HINTERLANDS       = 125,
	DATA_TIRISFAL_GLADES       = 126,
	DATA_UNDERCITY             = 127,
	DATA_WESTERN_PLAGUELANDS   = 128,
	DATA_WESTFALL              = 129,
	DATA_WETLANDS              = 130,
	// Kalimdor
	DATA_ASHENVALE             = 131,
	DATA_AZSHARA               = 132,
	DATA_AZUREMYT_ISLE         = 133,
	DATA_BLOODMYST_ISLE        = 134,
	DATA_DARKSHORE             = 135,
	DATA_DARNASSUS             = 136,
	DATA_DESOLACE              = 137,
	DATA_DUROTAR               = 138,
	DATA_DUSTWALLOW_MARSH      = 139,
	DATA_FELWOOD               = 140,
	DATA_FERALAS               = 141,
	DATA_MOONGLADE             = 142,
	DATA_MULGORE               = 143,
	DATA_ORGRIMMAR             = 144,
	DATA_SILITHUS              = 145,
	DATA_STONETALON_MOUNTAINS  = 146,
	DATA_TANARIS               = 147,
	DATA_TELDRASSIL            = 148,
	DATA_THE_BARRENS           = 149,
	DATA_THE_EXODAR            = 150,
	DATA_THE_VEILED_SEA        = 151,
	DATA_THOUSAND_NEEDLES      = 152,
	DATA_THUNDER_BLUFF         = 153,
	DATA_UN_GORO_CRATER        = 154,
	DATA_WINTERSPRING          = 155,
	// Outland
	DATA_BLADES_EDGE_MOUNTAINS = 156,
	DATA_HELLFIRE_PENINSULA    = 157,
	DATA_NAGRAND               = 158,
	DATA_NETHERSTORM           = 159,
	DATA_SHADOWMOON_VALLEY     = 160,
	DATA_SHATTRATH_CITY        = 161,
	DATA_TEROKKAR_FOREST       = 162,
	DATA_ZANGARMARSH           = 163,
	// Northrend
	DATA_BOREAN_TUNDRA         = 164,
	DATA_CRYSTALSONG_FOREST    = 165,
	DATA_DALARAN               = 166,
	DATA_DRAGONBLIGHT          = 167,
	DATA_GRIZZLY_HILLS         = 168,
	DATA_HOWLING_FJORD         = 169,
	DATA_HROTGARS_LANDING      = 170,
	DATA_ICECROWN              = 171,
	DATA_SHOLAZAR_BASIN        = 172,
	DATA_THE_STORM_PEAKS       = 173,
	DATA_WINTERGRASP           = 174,
	DATA_ZUL_DRAK              = 175,
	// Dungeon and Raids
	DATA_ICECROWN_CITADEL      = 176,
	DATA_THE_FROZEN_HALLS      = 177,
	DATA_NAXXRAMAS             = 178,
	DATA_ONYXIA_LAIR           = 179,
	DATA_THE_NEXUS             = 180,
	DATA_CHAMDER_OF_ASPECTS    = 181,
	DATA_CRUSADER_COLISEUM     = 182,
	DATA_ULDUAR                = 183,
	DATA_VAULT_OF_ARCHAVON     = 184,
	DATA_AZJOL_NERUB           = 185,
	DATA_UTGARDE_KEEP          = 186,
	DATA_GUNDRAK               = 187,
	DATA_DRAK_THARON_KEEP      = 188,
	DATA_CULLING_OF_STRATHOLME = 189,
	DATA_THE_BLACK_TEMPLE      = 190,
	DATA_TEMPEST_KEEP          = 191,
	DATA_COILFANG_RESERVOIR    = 192,
	DATA_HELLFIRE_CITADEL      = 193,
	DATA_KARAZHAN              = 194,
	DATA_SUNWELL_PLATEAU       = 195,
	DATA_MAGISTERS_TERRACE     = 196,
	DATA_ZUL_AMAN              = 197,
	DATA_CAVERNS_OF_TIME       = 198,
	DATA_GRUULS_LAIR           = 199,
	DATA_AUCHINDOUN            = 200,
	DATA_BLACKWING_LAIR        = 201,
	DATA_MOLTEN_CORE           = 202,
	DATA_RUINS_OF_AHN_QIRAJ    = 203,
	DATA_TEMPLE_OF_AHN_QIRAJ   = 204,
	DATA_ZUL_GURUB             = 205,
	// PvP Territory
	DATA_GURUBASHI_ARENA       = 206,
	DATA_BOOTY_BAY             = 207,
	DATA_GADGETZAN             = 208,
	DATA_NIGHTHAVEN            = 209,
	DATA_RATCHET               = 210,
	DATA_HALAA                 = 211,
	DATA_AREA_52               = 212,
};

enum DisplayId
{
	DISPLAY_ID_STARCRAFT_MURLOC       = 29348,
	DISPLAY_ID_AMBROSE_BOLTSPARK      = 28586,
	DISPLAY_ID_JONATHAN_THE_REVELATOR = 15867,
	DISPLAY_ID_SHATTERED_SUN_MAGE     = 22959,
	DISPLAY_ID_WORGEN                 = 657,
	DISPLAY_ID_PANDAREN_MONK          = 30414,
	DISPLAY_ID_ALGALON                = 28641,
	DISPLAY_ID_IRON_MENDER            = 26239,
	DISPLAY_ID_DRUID                  = 30481,
	DISPLAY_ID_PRIEST                 = 21419,
	DISPLAY_ID_PALADIN                = 29774,
	DISPLAY_ID_ROGUE                  = 30485,
	DISPLAY_ID_DEATH_KNIGHT           = 27153,
	DISPLAY_ID_WARLOCK                = 30487,
	DISPLAY_ID_WARRIOR                = 14732,
	DISPLAY_ID_MAGE                   = 30477,
	DISPLAY_ID_SHAMAN                 = 23188,
	DISPLAY_ID_HUNTER                 = 21379,
	DISPLAY_ID_DRAENEI_GIRL_WHITE     = 30634,
	DISPLAY_ID_DRAENEI_GIRL_BLACK     = 30771,
};

class npc_server_helper : public CreatureScript
{
public:
    npc_server_helper() : CreatureScript("npc_server_helper") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{
		player->PlayerTalkClass->ClearMenus();

		if (ConfigMgr::GetBoolDefault("Server.Helper.Enable", true))
		{
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Remove Resurrection Sickness", GOSSIP_SENDER_MAIN, SICKNESS_MENU);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Remove Deserter", GOSSIP_SENDER_MAIN, DESERTER_MENU);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Heal Me Please", GOSSIP_SENDER_MAIN, HEAL_MENU);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Save Me Please", GOSSIP_SENDER_MAIN, SAVE_MENU);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Reset My Talents", GOSSIP_SENDER_MAIN, TALENT_MENU);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Reset Quest Cooldown [30.000 Gold]", GOSSIP_SENDER_MAIN, QUEST_MENU);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Update My Skills To Maximum", GOSSIP_SENDER_MAIN, SKILLS_MENU);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Teleport Menu ->", GOSSIP_SENDER_MAIN, TELEPORT_MENU);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buff Menu ->", GOSSIP_SENDER_MAIN, BUFF_MENU);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Customize Menu ->", GOSSIP_SENDER_MAIN, CUSTOMIZE_MENU);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Exchange Menu ->", GOSSIP_SENDER_MAIN, EXCHANGE_MENU);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "Movie Menu ->", GOSSIP_SENDER_MAIN, MOVIE_MENU);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "Funny Menu ->", GOSSIP_SENDER_MAIN, FUNNY_MENU);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			return true;
		}
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();

		switch (action)
		{
		case SICKNESS_MENU:
			if (!player->HasAura(SPELL_RESURRECTION_SICKNESS))
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_NO_SICKNESS, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->RemoveAurasDueToSpell(SPELL_RESURRECTION_SICKNESS);
				player->ResetAllPowers();
				creature->MonsterWhisper(MESSAGE_REMOVE_SICKNESS_COMPLETE, player->GetGUID());
			}
			break;
		case DESERTER_MENU:
			if (!player->HasAura(SPELL_DESERTER))
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_NO_DESERTER, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->RemoveAurasDueToSpell(SPELL_DESERTER);
				creature->MonsterWhisper(MESSAGE_REMOVE_DESERTER_COMPLETE, player->GetGUID());
			}
			break;
		case HEAL_MENU:
			if (player->HasAura(SPELL_ANTI_HEAL_DEBUFF))
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_COOLDOWN, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->CastSpell(player, SPELL_FULL_HEAL, true);
				player->CastSpell(player, SPELL_ANTI_HEAL_DEBUFF, true);
			}
			break;
		case SAVE_MENU:
			player->CLOSE_GOSSIP_MENU();
			player->SaveToDB();
			creature->MonsterWhisper(MESSAGE_CHARACTER_SAVE_TO_DB, player->GetGUID());
			break;
		case TALENT_MENU:
			player->CLOSE_GOSSIP_MENU();
			player->SendTalentWipeConfirm(creature->GetGUID());
			break;
		case QUEST_MENU:
			if (!player->HasEnoughMoney(CONST_FOR_RESET_QUESTS_COOLDOWN))
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_NO_MONEY, 0, true);
			}
			else
			{
				player->ModifyMoney(-CONST_FOR_RESET_QUESTS_COOLDOWN);
				player->ResetDailyQuestStatus();
				player->ResetWeeklyQuestStatus();
				creature->MonsterWhisper(MESSAGE_RESET_QUEST_STATUS_COMPLETE, player->GetGUID());
			}
			break;
		case SKILLS_MENU:
			player->CLOSE_GOSSIP_MENU();
			player->UpdateSkillsToMaxSkillsForLevel();
			creature->MonsterWhisper(MESSAGE_MAX_SKILL, player->GetGUID());
			break;
		case TELEPORT_MENU:
			if (ConfigMgr::GetBoolDefault("Server.Helper.Teleport.Menu.Enable", true))
			{
				player->PlayerTalkClass->ClearMenus();
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Eastern Kingdoms", GOSSIP_SENDER_MAIN, ACTION_EASTERN_KINGDOMS);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Kalimdor", GOSSIP_SENDER_MAIN, ACTION_KALIMDOR);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Outland", GOSSIP_SENDER_MAIN, ACTION_OUTLAND);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Northrend", GOSSIP_SENDER_MAIN, ACTION_NORTHREND);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Dungeons and Raids", GOSSIP_SENDER_MAIN, ACTION_INSTANCES);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[PVP] Territory", GOSSIP_SENDER_MAIN, ACTION_PVP_TERRITORY);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "<- [Main Menu]", GOSSIP_SENDER_MAIN, MAIN_MENU);
				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_FUNCTION_OFF, 0, true);
			}
			break;
		case ACTION_EASTERN_KINGDOMS:
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Alterac Mountains", GOSSIP_SENDER_MAIN, DATA_ALTERAC_MOUNTAINS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Arathi Highlands", GOSSIP_SENDER_MAIN, DATA_ARATHI_HIGHLANDS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Badlands", GOSSIP_SENDER_MAIN, DATA_BADLANDS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Blackrock Mountain", GOSSIP_SENDER_MAIN, DATA_BLACKROCK_MOUNTAIN);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Blasted Lands", GOSSIP_SENDER_MAIN, DATA_BLASTED_LANDS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Burning Steppes", GOSSIP_SENDER_MAIN, DATA_BURNING_STEPPES);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Deadwind Pass", GOSSIP_SENDER_MAIN, DATA_DEADWIND_PASS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Dun Morogh", GOSSIP_SENDER_MAIN, DATA_DUN_MOROGH);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Duskwood", GOSSIP_SENDER_MAIN, DATA_DUSKWOOD);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Eastern Plaguelands", GOSSIP_SENDER_MAIN, DATA_EASTERN_PLAGUELANDS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Elwynn Forest", GOSSIP_SENDER_MAIN, DATA_ELWYN_FOREST);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Eversong Woods", GOSSIP_SENDER_MAIN, DATA_EVERSONG_WOODS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Ghostlands", GOSSIP_SENDER_MAIN, DATA_GHOSTLANDS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Hillsbrad Foothills", GOSSIP_SENDER_MAIN, DATA_HILLSBRAD_FOOTHILLS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Ironforge", GOSSIP_SENDER_MAIN, DATA_IRONFORGE);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Isle of Quel Danas", GOSSIP_SENDER_MAIN, DATA_ISLE_OF_QUEL_DANAS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Loch Modan", GOSSIP_SENDER_MAIN, DATA_LOCH_MODAN);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "The Scarlet Enclave [Ebon Hold]", GOSSIP_SENDER_MAIN, DATA_EBON_HOLD);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Redridge Mountains", GOSSIP_SENDER_MAIN, DATA_REDRIGE_MOUNTAINS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Searing Gorge", GOSSIP_SENDER_MAIN, DATA_SEARING_GORGE);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Silvermoon City", GOSSIP_SENDER_MAIN, DATA_SILVERMOON_CITY);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Silverpine Forest", GOSSIP_SENDER_MAIN, DATA_SILVERPINE_FOREST);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Stormwind City", GOSSIP_SENDER_MAIN, DATA_STORMWIND_CITY);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Stranglethorn Vale", GOSSIP_SENDER_MAIN, DATA_STRANGLETHORN_VALE);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Swamp of Sorrows", GOSSIP_SENDER_MAIN, DATA_SWAMP_OF_SORROWS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "The Hinterlands", GOSSIP_SENDER_MAIN, DATA_THE_HINTERLANDS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Tirisfal Glades", GOSSIP_SENDER_MAIN, DATA_TIRISFAL_GLADES);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Undercity", GOSSIP_SENDER_MAIN, DATA_UNDERCITY);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Western Plaguelands", GOSSIP_SENDER_MAIN, DATA_WESTERN_PLAGUELANDS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Westfall", GOSSIP_SENDER_MAIN, DATA_WESTFALL);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Wetlands", GOSSIP_SENDER_MAIN, DATA_WETLANDS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "<- [Back]", GOSSIP_SENDER_MAIN, TELEPORT_MENU);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case DATA_ALTERAC_MOUNTAINS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 370.763f, -491.355f, 175.361f, 5.37858f);
			break;
		case DATA_ARATHI_HIGHLANDS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -1508.51f, -2732.06f, 32.4986f, 3.35708f);
			break;
		case DATA_BADLANDS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -6779.2f, -3423.64f, 241.667f, 0.647481f);
			break;
		case DATA_BLACKROCK_MOUNTAIN:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -7494.94f, -1123.49f, 265.547f, 3.3092f);
			break;
		case DATA_BLASTED_LANDS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -11182.5f, -3016.67f, 7.42235f, 4.0004f);
			break;
		case DATA_BURNING_STEPPES:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -8118.54f, -1633.83f, 132.996f, 0.089067f);
			break;
		case DATA_DEADWIND_PASS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -10438.8f, -1932.75f, 104.617f, 4.77402f);
			break;
		case DATA_DUN_MOROGH:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -5451.55f, -656.992f, 392.675f, 0.66789f);
			break;
		case DATA_DUSKWOOD:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -10898.3f, -364.784f, 39.2681f, 3.04614f);
			break;
		case DATA_EASTERN_PLAGUELANDS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 2300.97f, -4613.36f, 73.6231f, 0.367722f);
			break;
		case DATA_ELWYN_FOREST:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -9617.06f, -288.949f, 57.3053f, 4.72687f);
			break;
		case DATA_EVERSONG_WOODS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 9079.92f, -7193.23f, 55.6013f, 5.94597f);
			break;
		case DATA_GHOSTLANDS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 7360.86f, -6803.3f, 44.2942f, 5.83679f);
			break;
		case DATA_HILLSBRAD_FOOTHILLS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -436.657f, -581.254f, 53.5944f, 1.25917f);
			break;
		case DATA_IRONFORGE:
			if (player->GetTeam() == HORDE)
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_TELEPORT_ONLY_ALLIANCE, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->TeleportTo(0, -4918.88f, -940.406f, 501.564f, 5.42347f);
			}
			break;
		case DATA_ISLE_OF_QUEL_DANAS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 12947.4f, -6893.31f, 5.68398f, 3.09154f);
			break;
		case DATA_LOCH_MODAN:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -2846.52f, -2846.52f, 335.867f, 3.53304f);
			break;
		case DATA_EBON_HOLD:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 2359.69f, -5661.45f, 382.262f, 3.711f);
			break;
		case DATA_REDRIGE_MOUNTAINS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -9551.81f, -2204.73f, 93.473f, 5.47141f);
			break;
		case DATA_SEARING_GORGE:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -7012.47f, -1065.13f, 241.786f, 5.63162f);
			break;
		case DATA_SILVERMOON_CITY:
			if (player->GetTeam() == ALLIANCE)
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_TELEPORT_ONLY_HORDE, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->TeleportTo(530, 9487.69f, -7279.2f, 14.2866f, 6.16478f);
			}
			break;
		case DATA_SILVERPINE_FOREST:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 878.74f, 1359.33f, 50.355f, 5.89929f);
			break;
		case DATA_STORMWIND_CITY:
			if (player->GetTeam() == HORDE)
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_TELEPORT_ONLY_ALLIANCE, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->TeleportTo(0, -8833.38f, 628.628f, 94.0066f, 1.06535f);
			}
			break;
		case DATA_STRANGLETHORN_VALE:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -12644.3f, -377.411f, 10.1021f, 6.09978f);
			break;
		case DATA_SWAMP_OF_SORROWS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -10345.4f, -2773.42f, 21.99f, 5.08426f);
			break;
		case DATA_THE_HINTERLANDS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 119.387f, -3190.37f, 117.331f, 2.34064f);
			break;
		case DATA_TIRISFAL_GLADES:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 2036.02f, 161.331f, 33.8674f, 0.143896f);
			break;
		case DATA_UNDERCITY:
			if (player->GetTeam() == ALLIANCE)
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_TELEPORT_ONLY_HORDE, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->TeleportTo(0, 1584.07f, 241.987f, -52.1534f, 0.049647f);
			}
			break;
		case DATA_WESTERN_PLAGUELANDS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, 1728.65f, -1602.25f, 63.429f, 1.6558f);
			break;
		case DATA_WESTFALL:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -9823.5f, 859.1f, 25.7484f, 2.18454f);
			break;
		case DATA_WETLANDS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -3242.81f, -2469.04f, 15.9226f, 6.03924f);
			break;
		case ACTION_KALIMDOR:
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Ashenvale", GOSSIP_SENDER_MAIN, DATA_ASHENVALE);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Azshara", GOSSIP_SENDER_MAIN, DATA_AZSHARA);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Azuremyst Isle", GOSSIP_SENDER_MAIN, DATA_AZUREMYT_ISLE);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Bloodmyst Isle", GOSSIP_SENDER_MAIN, DATA_BLOODMYST_ISLE);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Darkshore", GOSSIP_SENDER_MAIN, DATA_DARKSHORE);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Darnassus", GOSSIP_SENDER_MAIN, DATA_DARNASSUS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Desolace", GOSSIP_SENDER_MAIN, DATA_DESOLACE);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Durotar", GOSSIP_SENDER_MAIN, DATA_DUROTAR);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Dustwallow Marsh", GOSSIP_SENDER_MAIN, DATA_DUSTWALLOW_MARSH);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Felwood", GOSSIP_SENDER_MAIN, DATA_FELWOOD);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Feralas", GOSSIP_SENDER_MAIN, DATA_FERALAS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Moonglade", GOSSIP_SENDER_MAIN, DATA_MOONGLADE);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Mulgore", GOSSIP_SENDER_MAIN, DATA_MULGORE);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Orgrimmar", GOSSIP_SENDER_MAIN, DATA_ORGRIMMAR);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Silithus", GOSSIP_SENDER_MAIN, DATA_SILITHUS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Stonetalon Mountains", GOSSIP_SENDER_MAIN, DATA_STONETALON_MOUNTAINS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Tanaris", GOSSIP_SENDER_MAIN, DATA_TANARIS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Teldrassil", GOSSIP_SENDER_MAIN, DATA_TELDRASSIL);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "The Barrens", GOSSIP_SENDER_MAIN, DATA_THE_BARRENS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "The Exodar", GOSSIP_SENDER_MAIN, DATA_THE_EXODAR);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "The Veiled Sea", GOSSIP_SENDER_MAIN, DATA_THE_VEILED_SEA);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Thousand Needles", GOSSIP_SENDER_MAIN, DATA_THOUSAND_NEEDLES);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Thunder Bluff", GOSSIP_SENDER_MAIN, DATA_THUNDER_BLUFF);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Un Goro Crater", GOSSIP_SENDER_MAIN, DATA_UN_GORO_CRATER);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Winterspring", GOSSIP_SENDER_MAIN, DATA_WINTERSPRING);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "<- [Back]", GOSSIP_SENDER_MAIN, TELEPORT_MENU);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case DATA_ASHENVALE:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 1928.34f, -2165.95f, 93.7896f, 0.205731f);
			break;
		case DATA_AZSHARA:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 3341.36f, -4603.79f, 92.5027f, 5.28142f);
			break;
		case DATA_AZUREMYT_ISLE:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -4204.32f, -12595.5f, 34.3839f, 1.41562f);
			break;
		case DATA_BLOODMYST_ISLE:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -1993.62f, -11475.8f, 63.9657f, 5.29437f);
			break;
		case DATA_DARKSHORE:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 5756.25f, 298.505f, 20.6049f, 5.96504f);
			break;
		case DATA_DARNASSUS:
			if (player->GetTeam() == HORDE)
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_TELEPORT_ONLY_ALLIANCE, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->TeleportTo(1, 9949.56f, 2284.21f, 1341.4f, 1.59587f);
			}
			break;
		case DATA_DESOLACE:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -606.395f, 2211.75f, 92.9818f, 0.809746f);
			break;
		case DATA_DUROTAR:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 1007.78f, -4446.22f, 11.2022f, 0.20797f);
			break;
		case DATA_DUSTWALLOW_MARSH:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -4043.65f, -2991.32f, 36.3984f, 3.37443f);
			break;
		case DATA_FELWOOD:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 4102.25f, -1006.79f, 272.717f, 0.790048f);
			break;
		case DATA_FERALAS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -4841.19f, 1309.44f, 81.3937f, 1.48501f);
			break;
		case DATA_MOONGLADE:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 7654.3f, -2232.87f, 462.107f, 5.96786f);
			break;
		case DATA_MULGORE:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -2192.62f, -736.317f, -13.3274f, 0.487569f);
			break;
		case DATA_ORGRIMMAR:
			if (player->GetTeam() == ALLIANCE)
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_TELEPORT_ONLY_HORDE, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->TeleportTo(1, 1629.63f, -4373.58f, 31.5523f, 3.44375f);
			}
			break;
		case DATA_SILITHUS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -7426.87f, 1005.31f, 1.13359f, 2.96086f);
			break;
		case DATA_STONETALON_MOUNTAINS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 1570.92f, 1031.52f, 137.959f, 3.33006f);
			break;
		case DATA_TANARIS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -7931.2f, -3414.28f, 80.7365f, 0.66522f);
			break;
		case DATA_TELDRASSIL:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 10111.3f, 1557.73f, 1324.33f, 4.04239f);
			break;
		case DATA_THE_BARRENS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 884.54f, -3548.45f, 91.8532f, 2.95957f);

			break;
		case DATA_THE_EXODAR:
			if (player->GetTeam() == HORDE)
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_TELEPORT_ONLY_ALLIANCE, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->TeleportTo(530, -3965.7f, -11653.6f, -138.844f, 0.852154f);
			}
			break;
		case DATA_THE_VEILED_SEA:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -4263.27f, -11338.0f, 5.59938f, 1.67446f);
			break;
		case DATA_THOUSAND_NEEDLES:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -4969.02f, -1726.89f, -62.1269f, 3.7933f);
			break;
		case DATA_THUNDER_BLUFF:
			if (player->GetTeam() == ALLIANCE)
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_TELEPORT_ONLY_HORDE, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->TeleportTo(1, -1277.37f, 124.804f, 131.287f, 5.22274f);
			}
			break;
		case DATA_UN_GORO_CRATER:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -7943.22f, -2119.09f, -218.343f, 6.0727f);
			break;
		case DATA_WINTERSPRING:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 6759.18f, -4419.63f, 763.214f, 4.43476f);
			break;
		case ACTION_OUTLAND:
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Blades Edge Mountains", GOSSIP_SENDER_MAIN, DATA_BLADES_EDGE_MOUNTAINS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Hellfire Peninsula", GOSSIP_SENDER_MAIN, DATA_HELLFIRE_PENINSULA);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Nagrand", GOSSIP_SENDER_MAIN, DATA_NAGRAND);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Netherstorm", GOSSIP_SENDER_MAIN, DATA_NETHERSTORM);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Shadowmoon Valley", GOSSIP_SENDER_MAIN, DATA_SHADOWMOON_VALLEY);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Shattrath City", GOSSIP_SENDER_MAIN, DATA_SHATTRATH_CITY);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Terokkar Forest", GOSSIP_SENDER_MAIN, DATA_TEROKKAR_FOREST);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Zangarmarsh", GOSSIP_SENDER_MAIN, DATA_ZANGARMARSH);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "<- [Back]", GOSSIP_SENDER_MAIN, TELEPORT_MENU);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case DATA_BLADES_EDGE_MOUNTAINS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 3037.67f, 5962.86f, 130.774f, 1.27253f);
			break;
		case DATA_HELLFIRE_PENINSULA:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -211.237f, 4278.54f, 86.5678f, 4.59776f);
			break;
		case DATA_NAGRAND:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -1145.95f, 8182.35f, 3.60249f, 6.13478f);
			break;
		case DATA_NETHERSTORM:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 3830.23f, 3426.5f, 88.6145f, 5.16677f);
			break;
		case DATA_SHADOWMOON_VALLEY:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -2998.66f, 2568.9f, 76.6306f, 0.551303f);
			break;
		case DATA_SHATTRATH_CITY:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -1838.16f, 5301.79f, -12.428f, 5.9517f);
			break;
		case DATA_TEROKKAR_FOREST:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -2000.47f, 4451.54f, 8.37917f, 4.40447f);
			break;
		case DATA_ZANGARMARSH:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -54.8621f, 5813.44f, 20.9764f, 0.081722f);
			break;
		case ACTION_NORTHREND:
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Borean Tundra", GOSSIP_SENDER_MAIN, DATA_BOREAN_TUNDRA);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Crystalsong Forest", GOSSIP_SENDER_MAIN, DATA_CRYSTALSONG_FOREST);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Dalaran", GOSSIP_SENDER_MAIN, DATA_DALARAN);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Dragonblight", GOSSIP_SENDER_MAIN, DATA_DRAGONBLIGHT);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Grizzly Hills", GOSSIP_SENDER_MAIN, DATA_GRIZZLY_HILLS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Howling Fjord", GOSSIP_SENDER_MAIN, DATA_HOWLING_FJORD);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Hrothgars Landing", GOSSIP_SENDER_MAIN, DATA_HROTGARS_LANDING);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Icecrown", GOSSIP_SENDER_MAIN, DATA_ICECROWN);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Sholazar Basin", GOSSIP_SENDER_MAIN, DATA_SHOLAZAR_BASIN);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "The Storm Peaks", GOSSIP_SENDER_MAIN, DATA_THE_STORM_PEAKS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Wintergrasp", GOSSIP_SENDER_MAIN, DATA_WINTERGRASP);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Zul Drak", GOSSIP_SENDER_MAIN, DATA_ZUL_DRAK);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "<- [Back]", GOSSIP_SENDER_MAIN, TELEPORT_MENU);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case DATA_BOREAN_TUNDRA:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 3256.57f, 5278.23f, 40.8046f, 0.246367f);
			break;
		case DATA_CRYSTALSONG_FOREST:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 5496.46f, 42.38f, 150.0f, 0.75f);
			break;
		case DATA_DALARAN:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 5804.15f, 624.771f, 647.767f, 1.64f);
			break;
		case DATA_DRAGONBLIGHT:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 4103.36f, 264.478f, 50.5019f, 3.09349f);
			break;
		case DATA_GRIZZLY_HILLS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 4391.73f, -3587.92f, 238.531f, 3.57526f);
			break;
		case DATA_HOWLING_FJORD:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 1902.15f, -4883.91f, 171.363f, 3.11537f);
			break;
		case DATA_HROTGARS_LANDING:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 10254.2f, 679.759f, 68.6468f, 3.11773f);
			break;
		case DATA_ICECROWN:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 7253.64f, 1644.78f, 433.68f, 4.83412f);
			break;
		case DATA_SHOLAZAR_BASIN:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 5563.16f, 5510.62f, -96.0489f, 1.59178f);
			break;
		case DATA_THE_STORM_PEAKS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 7527.14f, -1260.89f, 919.049f, 2.0696f);
			break;
		case DATA_WINTERGRASP:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 4561.58f, 2835.33f, 389.79f, 0.34f);
			break;
		case DATA_ZUL_DRAK:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 5560.23f, -3211.66f, 371.709f, 5.55055f);
			break;
		case ACTION_INSTANCES:
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Icecrown Citadel", GOSSIP_SENDER_MAIN, DATA_ICECROWN_CITADEL);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "The Frozen Halls", GOSSIP_SENDER_MAIN, DATA_THE_FROZEN_HALLS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Naxxramas", GOSSIP_SENDER_MAIN, DATA_NAXXRAMAS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Onyxia Lairs", GOSSIP_SENDER_MAIN, DATA_ONYXIA_LAIR);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "The Nexus", GOSSIP_SENDER_MAIN, DATA_THE_NEXUS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Chamber of Aspects", GOSSIP_SENDER_MAIN, DATA_CHAMDER_OF_ASPECTS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Crusaders Coliseum", GOSSIP_SENDER_MAIN, DATA_CRUSADER_COLISEUM);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Ulduar", GOSSIP_SENDER_MAIN, DATA_ULDUAR);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vault of Archavon", GOSSIP_SENDER_MAIN, DATA_VAULT_OF_ARCHAVON);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Azjol Nerub", GOSSIP_SENDER_MAIN, DATA_AZJOL_NERUB);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Utgarde Keep", GOSSIP_SENDER_MAIN, DATA_UTGARDE_KEEP);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Gundrak", GOSSIP_SENDER_MAIN, DATA_GUNDRAK);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Drak Tharon Keep", GOSSIP_SENDER_MAIN, DATA_DRAK_THARON_KEEP);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "The Culling of Stratholme", GOSSIP_SENDER_MAIN, DATA_CULLING_OF_STRATHOLME);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "The Black Temple", GOSSIP_SENDER_MAIN, DATA_THE_BLACK_TEMPLE);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Tempest Keep", GOSSIP_SENDER_MAIN, DATA_TEMPEST_KEEP);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Coilfang Reservoir", GOSSIP_SENDER_MAIN, DATA_COILFANG_RESERVOIR);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Hellfire Citadel", GOSSIP_SENDER_MAIN, DATA_HELLFIRE_CITADEL);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Karazhan", GOSSIP_SENDER_MAIN, DATA_KARAZHAN);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Sunwell Plateau", GOSSIP_SENDER_MAIN, DATA_SUNWELL_PLATEAU);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Magisters Terrace", GOSSIP_SENDER_MAIN, DATA_MAGISTERS_TERRACE);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Zul Aman", GOSSIP_SENDER_MAIN, DATA_ZUL_AMAN);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Caverns of Time", GOSSIP_SENDER_MAIN, DATA_CAVERNS_OF_TIME);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Gruuls Lair", GOSSIP_SENDER_MAIN, DATA_GRUULS_LAIR);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Auchindoun", GOSSIP_SENDER_MAIN, DATA_AUCHINDOUN);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Blackwing Lair", GOSSIP_SENDER_MAIN, DATA_BLACKWING_LAIR);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Molten Core", GOSSIP_SENDER_MAIN, DATA_MOLTEN_CORE);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Ruins of Ahn Qiraj", GOSSIP_SENDER_MAIN, DATA_RUINS_OF_AHN_QIRAJ);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Temple of Ahn Qiraj", GOSSIP_SENDER_MAIN, DATA_TEMPLE_OF_AHN_QIRAJ);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Zul Gurub", GOSSIP_SENDER_MAIN, DATA_ZUL_GURUB);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "<- [Back]", GOSSIP_SENDER_MAIN, TELEPORT_MENU);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case DATA_ICECROWN_CITADEL:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 5873.82f, 2110.98f, 636.011f, 3.5523f);
			break;
		case DATA_THE_FROZEN_HALLS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 5690.97f, 2141.07f, 798.054f, 4.4344f);
			break;
		case DATA_NAXXRAMAS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 3667.99f, -1268.26f, 243.505f, 2.30427f);
			break;
		case DATA_ONYXIA_LAIR:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -4708.27f, -3727.64f, 54.5589f, 3.72786f);
			break;
		case DATA_THE_NEXUS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 3897.42f, 6985.33f, 69.487f, 0.012698f);
			break;
		case DATA_CHAMDER_OF_ASPECTS:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 3641.45f, 282.75f, -120.145f, 3.325f);
			break;
		case DATA_CRUSADER_COLISEUM:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 8515.89f, 629.25f, 547.396f, 1.5747f);
			break;
		case DATA_ULDUAR:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 9239.35f, -1112.53f, 1216.12f, 0.0361938f);
			break;
		case DATA_VAULT_OF_ARCHAVON:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 5482.38f, 2839.47f, 418.839f, 0);
			break;
		case DATA_AZJOL_NERUB:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 3707.86f, 2150.23f, 36.76f, 3.22f);
			break;
		case DATA_UTGARDE_KEEP:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 1228.09f, -4862.45f, 41.248f, 0.314811f);
			break;
		case DATA_GUNDRAK:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 6898.72f, -4584.94f, 451.12f, 2.34455f);
			break;
		case DATA_DRAK_THARON_KEEP:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(571, 4774.47f, -2028.04f, 229.373f, 1.54661f);
			break;
		case DATA_CULLING_OF_STRATHOLME:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -8204.88f, -4495.25f, 9.0091f, 4.72574f);
			break;
		case DATA_THE_BLACK_TEMPLE:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -3649.92f, 317.469f, 35.2827f, 2.94285f);
			break;
		case DATA_TEMPEST_KEEP:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 3099.36f, 1518.73f, 190.3f, 4.72592f);
			break;
		case DATA_COILFANG_RESERVOIR:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 735.066f, 6883.45f, -66.2913f, 5.89172f);
			break;
		case DATA_HELLFIRE_CITADEL:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -390.863f, 3130.64f, 4.51327f, 0.218692f);
			break;
		case DATA_KARAZHAN:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -11118.9f, -2010.33f, 47.0819f, 0.649895f);
			break;
		case DATA_SUNWELL_PLATEAU:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 12574.1f, -6774.81f, 15.0904f, 3.13788f);
			break;
		case DATA_MAGISTERS_TERRACE:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 12884.6f, -7317.69f, 65.5023f, 4.799f);
			break;
		case DATA_ZUL_AMAN:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 6851.78f, -7972.57f, 179.242f, 4.64691f);
			break;
		case DATA_CAVERNS_OF_TIME:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -8204.88f, -4495.25f, 9.0091f, 4.72574f);
			break;
		case DATA_GRUULS_LAIR:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 3530.06f, 5104.08f, 3.50861f, 5.51117f);
			break;
		case DATA_AUCHINDOUN:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -3324.49f, 4943.45f, -101.239f, 4.63901f);
			break;
		case DATA_BLACKWING_LAIR:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(229, 164.789f, -475.305f, 116.842f, 0.022714f);
			break;
		case DATA_MOLTEN_CORE:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(230, 1126.64f, -459.94f, -102.535f, 3.46095f);
			break;
		case DATA_RUINS_OF_AHN_QIRAJ:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -8409.82f, 1499.06f, 27.7179f, 2.51868f);
			break;
		case DATA_TEMPLE_OF_AHN_QIRAJ:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -8240.09f, 1991.32f, 129.072f, 0.941603f);
			break;
		case DATA_ZUL_GURUB:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -11916.7f, -1215.72f, 92.289f, 4.72454f);
			break;
		case ACTION_PVP_TERRITORY:
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Gurubashi Arena", GOSSIP_SENDER_MAIN, DATA_GURUBASHI_ARENA);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Booty Bay", GOSSIP_SENDER_MAIN, DATA_BOOTY_BAY);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Gadgetzan", GOSSIP_SENDER_MAIN, DATA_GADGETZAN);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Nighthaven", GOSSIP_SENDER_MAIN, DATA_NIGHTHAVEN);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Ratchet", GOSSIP_SENDER_MAIN, DATA_RATCHET);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Halaa", GOSSIP_SENDER_MAIN, DATA_HALAA);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Area 52", GOSSIP_SENDER_MAIN, DATA_AREA_52);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "<- [Back]", GOSSIP_SENDER_MAIN, TELEPORT_MENU);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case DATA_GURUBASHI_ARENA:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -13277.4f, 127.372f, 26.1418f, 1.11878f);
			break;
		case DATA_BOOTY_BAY:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -14297.2f, 530.993f, 8.77916f, 3.98863f);
			break;
		case DATA_GADGETZAN:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -7177.15f, -3785.34f, 8.36981f, 6.10237f);
			break;
		case DATA_NIGHTHAVEN:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, 7966.85f, -2491.04f, 487.734f, 3.20562f);
			break;
		case DATA_RATCHET:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(1, -956.664f, -3754.71f, 5.33239f, 0.996637f);
			break;
		case DATA_HALAA:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, -1563.05f, 7945.67f, -22.5568f, 1.13572f);
			break;
		case DATA_AREA_52:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(530, 3043.33f, 3681.33f, 143.065f, 5.07464f);
			break;
		case BUFF_MENU:
			if (ConfigMgr::GetBoolDefault("Server.Helper.Buff.Menu.Enable", true))
			{
				player->PlayerTalkClass->ClearMenus();
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Power Word Fortitude", GOSSIP_SENDER_MAIN, ACTION_POWER_WORD_FORTITUDE);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Prayer of Spirit", GOSSIP_SENDER_MAIN, ACTION_PRAYER_OF_SPIRIT);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Shadow Protection", GOSSIP_SENDER_MAIN, ACTION_SHADOW_PROTECTION);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Greater Blessing of Kings", GOSSIP_SENDER_MAIN, ACTION_GREATER_BLESSING_OF_KINGS);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Greater Bleesing of Might", GOSSIP_SENDER_MAIN, ACTION_GREATER_BLESSING_OF_MIGHT);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Greater Blessing of Wisdom", GOSSIP_SENDER_MAIN, ACTION_GREATER_BLESSING_OF_WISDOM);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Greater Blessing of Sanctuary", GOSSIP_SENDER_MAIN, ACTION_GREATER_BLESSING_OF_SANCTUARY);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Arane Intellect", GOSSIP_SENDER_MAIN, ACTION_ARCANE_INTELLECT);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Dampen Magic", GOSSIP_SENDER_MAIN, ACTION_DAMPEN_MAGIC);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Amplify Magic", GOSSIP_SENDER_MAIN, ACTION_AMPLIFY_MAGIC);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Gift of the Wild", GOSSIP_SENDER_MAIN, ACTION_GIFT_OF_THE_WILD);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Thorns", GOSSIP_SENDER_MAIN, ACTION_THORNS);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Brilliance Intellect", GOSSIP_SENDER_MAIN, ACTION_BRILLIANCE_INTELLECT);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Infinite Replenishment", GOSSIP_SENDER_MAIN, ACTION_INFINITE_REPLENISHMENT);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Inner Fire", GOSSIP_SENDER_MAIN, ACTION_INNER_FIRE);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Water Breathing", GOSSIP_SENDER_MAIN, ACTION_WATER_BREATHING);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "<- [Main Menu]", GOSSIP_SENDER_MAIN, MAIN_MENU);
				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_FUNCTION_OFF, 0, true);
			}
			break;
		case ACTION_POWER_WORD_FORTITUDE:
			player->CLOSE_GOSSIP_MENU();
			player->CastSpell(player, SPELL_POWER_WORD_FORTITUDE, true);
			break;
		case ACTION_PRAYER_OF_SPIRIT:
			player->CLOSE_GOSSIP_MENU();
			player->CastSpell(player, SPELL_PRAYER_OF_SPIRIT, true);
			break;
		case ACTION_SHADOW_PROTECTION:
			player->CLOSE_GOSSIP_MENU();
			player->CastSpell(player, SPELL_SHADOW_PROTECTION, true);
			break;
		case ACTION_GREATER_BLESSING_OF_KINGS:
			player->CLOSE_GOSSIP_MENU();
			player->CastSpell(player, SPELL_GREATER_BLESSING_OF_KINGS, true);
			break;
		case ACTION_GREATER_BLESSING_OF_MIGHT:
			player->CLOSE_GOSSIP_MENU();
			player->CastSpell(player, SPELL_GREATER_BLESSING_OF_MIGHT, true);
			break;
		case ACTION_GREATER_BLESSING_OF_WISDOM:
			player->CLOSE_GOSSIP_MENU();
			player->CastSpell(player, SPELL_GREATER_BLESSING_OF_WISDOM, true);
			break;
		case ACTION_GREATER_BLESSING_OF_SANCTUARY:
			player->CLOSE_GOSSIP_MENU();
			player->CastSpell(player, SPELL_GREATER_BLESSING_OF_SANCTUARY, true);
			break;
		case ACTION_ARCANE_INTELLECT:
			player->CLOSE_GOSSIP_MENU();
			player->CastSpell(player, SPELL_ARCANE_INTELLECT, true);
			break;
		case ACTION_DAMPEN_MAGIC:
			player->CLOSE_GOSSIP_MENU();
			player->CastSpell(player, SPELL_DAMPEN_MAGIC, true);
			break;
		case ACTION_AMPLIFY_MAGIC:
			player->CLOSE_GOSSIP_MENU();
			player->CastSpell(player, SPELL_AMPLIFY_MAGIC, true);
			break;
		case ACTION_GIFT_OF_THE_WILD:
			player->CLOSE_GOSSIP_MENU();
			player->CastSpell(player, SPELL_GIFT_OF_THE_WILD, true);
			break;
		case ACTION_THORNS:
			player->CLOSE_GOSSIP_MENU();
			player->CastSpell(player, SPELL_THORNS, true);
			break;
		case ACTION_BRILLIANCE_INTELLECT:
			player->CLOSE_GOSSIP_MENU();
			player->CastSpell(player, SPELL_BRILLIANCE_INTELLECT, true);
			break;
		case ACTION_INFINITE_REPLENISHMENT:
			player->CLOSE_GOSSIP_MENU();
			player->CastSpell(player, SPELL_INFINITE_REPLENISHMENT, true);
			break;
		case ACTION_INNER_FIRE:
			player->CLOSE_GOSSIP_MENU();
			player->CastSpell(player, SPELL_INNER_FIRE, true);
			break;
		case ACTION_WATER_BREATHING:
			player->CLOSE_GOSSIP_MENU();
			player->CastSpell(player, SPELL_WATER_BREATHING, true);
			break;
		case CUSTOMIZE_MENU:
			if (ConfigMgr::GetBoolDefault("Server.Helper.Customize.Menu.Enable", true))
			{
				player->PlayerTalkClass->ClearMenus();
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Rename [500 Arena Points]", GOSSIP_SENDER_MAIN, ACTION_RENAME);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Customize [500 Arena Points]", GOSSIP_SENDER_MAIN, ACTION_CUSTOMIZE);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Change Faction [1500 Arena Points]", GOSSIP_SENDER_MAIN, ACTION_CHANGE_FACTION);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Change Race [2000 Arena Points]", GOSSIP_SENDER_MAIN, ACTION_CHANGE_RACE);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "<- [Main Menu]", GOSSIP_SENDER_MAIN, MAIN_MENU);
				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_FUNCTION_OFF, 0, true);
			}
			break;
		case ACTION_RENAME:
			if (player->GetArenaPoints() < CONST_ARENA_RENAME)
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_NO_ARENA_POINTS, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->SetAtLoginFlag(AT_LOGIN_RENAME);
				player->ModifyArenaPoints(-CONST_ARENA_RENAME);
				player->PlayDirectSound(SOUND_CUSTOMIZE);
				creature->MonsterWhisper(MESSAGE_RENAME_COMPLETE, player->GetGUID());
			}
			break;
		case ACTION_CUSTOMIZE:
			if (player->GetArenaPoints() < CONST_ARENA_CUSTOMIZE)
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_NO_ARENA_POINTS, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
				player->ModifyArenaPoints(-CONST_ARENA_CUSTOMIZE);
				player->PlayDirectSound(SOUND_CUSTOMIZE);
				creature->MonsterWhisper(MESSAGE_CUSTOMIZE_COMPLETE, player->GetGUID());
			}
			break;
		case ACTION_CHANGE_FACTION:
			if (player->GetArenaPoints() < CONST_ARENA_CHANGE_FACTION)
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_NO_ARENA_POINTS, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
				player->ModifyArenaPoints(-CONST_ARENA_CHANGE_FACTION);
				player->PlayDirectSound(SOUND_CUSTOMIZE);
				creature->MonsterWhisper(MESSAGE_CHANGE_FACTION_COMPLETE, player->GetGUID());
			}
			break;
		case ACTION_CHANGE_RACE:
			if (player->GetArenaPoints() < CONST_ARENA_CHANGE_RACE)
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_NO_ARENA_POINTS, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
				player->ModifyArenaPoints(-CONST_ARENA_CHANGE_RACE);
				player->PlayDirectSound(SOUND_CUSTOMIZE);
				creature->MonsterWhisper(MESSAGE_CHANGE_RACE_COMPLETE, player->GetGUID());
			}
			break;
		case EXCHANGE_MENU:
			if (ConfigMgr::GetBoolDefault("Server.Helper.Exchange.Menu.Enable", true))
			{
				player->PlayerTalkClass->ClearMenus();
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Emblem Exchange Menu", GOSSIP_SENDER_MAIN, ACTION_EMBLEM_EXCHANGE);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "BG Mark Exchange Menu", GOSSIP_SENDER_MAIN, ACTION_BG_MARK_EXCHANGE);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Currency Exchange Menu", GOSSIP_SENDER_MAIN, ACTION_CURRENCY_EXCHANGE);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "<- [Main Menu]", GOSSIP_SENDER_MAIN, MAIN_MENU);
				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
				return true;
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_FUNCTION_OFF, 0, true);
			}
			break;
		case ACTION_EMBLEM_EXCHANGE:
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "5 Emblem of Frost -> 5 Emblem of Triumph", GOSSIP_SENDER_MAIN, ACTION_FROST_TO_TRIUMPH);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "5 Emblem of Frost -> 5 Emblem of Conquest", GOSSIP_SENDER_MAIN, ACTION_FROST_TO_CONQUEST);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "5 Emblem of Frost -> 5 Emblem of Valor", GOSSIP_SENDER_MAIN, ACTION_FROST_TO_VALOR);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "5 Emblem of Frost -> 5 Emblem of Heroism", GOSSIP_SENDER_MAIN, ACTION_FROST_TO_HEROISM);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "5 Emblem of Frost -> 5 Badge of Justice", GOSSIP_SENDER_MAIN, ACTION_FROST_TO_JUSTICE);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "<- [Back]", GOSSIP_SENDER_MAIN, EXCHANGE_MENU);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case ACTION_FROST_TO_TRIUMPH:
			if (!player->HasItemCount(EMBLEM_OF_FROST, CONST_FROST_TO_TRIUMPH))
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_NO_ENOUGH_EMBLEMS, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->DestroyItemCount(EMBLEM_OF_FROST, CONST_FROST_TO_TRIUMPH, true);
				player->AddItem(EMBLEM_OF_TRIUMPH, CONST_FROST_TO_TRIUMPH);
			}
			break;
		case ACTION_FROST_TO_CONQUEST:
			if (!player->HasItemCount(EMBLEM_OF_FROST, CONST_FROST_TO_CONQUEST))
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_NO_ENOUGH_EMBLEMS, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->DestroyItemCount(EMBLEM_OF_FROST, CONST_FROST_TO_CONQUEST, true);
				player->AddItem(EMBLEM_OF_CONQUEST, CONST_FROST_TO_CONQUEST);
			}
			break;
		case ACTION_FROST_TO_VALOR:
			if (!player->HasItemCount(EMBLEM_OF_FROST, CONST_FROST_TO_VALOR))
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_NO_ENOUGH_EMBLEMS, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->DestroyItemCount(EMBLEM_OF_FROST, CONST_FROST_TO_VALOR, true);
				player->AddItem(EMBLEM_OF_VALOR, CONST_FROST_TO_VALOR);
			}
			break;
		case ACTION_FROST_TO_HEROISM:
			if (!player->HasItemCount(EMBLEM_OF_FROST, CONST_FROST_TO_HEROISM))
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_NO_ENOUGH_EMBLEMS, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->DestroyItemCount(EMBLEM_OF_FROST, CONST_FROST_TO_HEROISM, true);
				player->AddItem(EMBLEM_OF_HEROISM, CONST_FROST_TO_HEROISM);
			}
			break;
		case ACTION_FROST_TO_JUSTICE:
			if (!player->HasItemCount(EMBLEM_OF_FROST, CONST_FROST_TO_JUSTICE))
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_NO_ENOUGH_EMBLEMS, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->DestroyItemCount(EMBLEM_OF_FROST, CONST_FROST_TO_JUSTICE, true);
				player->AddItem(BADGE_OF_JUSTICE, CONST_FROST_TO_JUSTICE);
			}
			break;
		case ACTION_BG_MARK_EXCHANGE:
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "5 Triumph -> 1 Mark Alterac Valley", GOSSIP_SENDER_MAIN, ACTION_TRIUMPH_TO_ALTERAC_VALLEY);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "5 Triumph -> 1 Mark Warsong Gulch", GOSSIP_SENDER_MAIN, ACTION_TRIUMPH_TO_WARSONG_GULCH);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "5 Triumph -> 1 Mark Arathi Bassin", GOSSIP_SENDER_MAIN, ACTION_TRIUMPH_TO_ARATHI_BASSIN);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "5 Triumph -> 1 Mark Eye of The Srorm", GOSSIP_SENDER_MAIN, ACTION_TRIUMPH_TO_EYE_OF_THE_STORM);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "5 Triumph -> 1 Mark Strand of The Ancients", GOSSIP_SENDER_MAIN, ACTION_TRIUMPH_TO_STRAND_OF_ANCIENTS);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "5 Triumph -> 1 Mark Isle of Conquest", GOSSIP_SENDER_MAIN, ACTION_TRIUMPH_TO_ISLE_OF_CONQUEST);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "5 Triumph -> 1 Mark Wintergrasp", GOSSIP_SENDER_MAIN, ACTION_TRIUMPH_TO_WINTERGRASP);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "<- [Back]", GOSSIP_SENDER_MAIN, EXCHANGE_MENU);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case ACTION_TRIUMPH_TO_ALTERAC_VALLEY:
			if (!player->HasItemCount(EMBLEM_OF_TRIUMPH, CONST_TRIUMPH_TO_ALTERAC_VALLEY))
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_NO_ENOUGH_EMBLEMS, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->DestroyItemCount(EMBLEM_OF_TRIUMPH, CONST_TRIUMPH_TO_ALTERAC_VALLEY, true);
				player->AddItem(ALTERAC_VALLEY_MARK_OF_HONOR, MARK_OF_HONOR_MAX);
			}
			break;
		case ACTION_TRIUMPH_TO_WARSONG_GULCH:
			if (!player->HasItemCount(EMBLEM_OF_TRIUMPH, CONST_TRIUMPH_TO_WARSONG_GULCH))
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_NO_ENOUGH_EMBLEMS, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->DestroyItemCount(EMBLEM_OF_TRIUMPH, CONST_TRIUMPH_TO_WARSONG_GULCH, true);
				player->AddItem(WARSONG_GULCH_MARK_OF_HONOR, MARK_OF_HONOR_MAX);
			}
			break;
		case ACTION_TRIUMPH_TO_ARATHI_BASSIN:
			if (!player->HasItemCount(EMBLEM_OF_TRIUMPH, CONST_TRIUMPH_TO_ARATHI_BASSIN))
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_NO_ENOUGH_EMBLEMS, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->DestroyItemCount(EMBLEM_OF_TRIUMPH, CONST_TRIUMPH_TO_ARATHI_BASSIN, true);
				player->AddItem(ARATHI_BASSIN_MARK_OF_HONOR, MARK_OF_HONOR_MAX);
			}
			break;
		case ACTION_TRIUMPH_TO_EYE_OF_THE_STORM:
			if (!player->HasItemCount(EMBLEM_OF_TRIUMPH, CONST_TRIUMPH_TO_EYE_OF_THE_STORM))
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_NO_ENOUGH_EMBLEMS, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->DestroyItemCount(EMBLEM_OF_TRIUMPH, CONST_TRIUMPH_TO_EYE_OF_THE_STORM, true);
				player->AddItem(EYE_OF_THE_STORM_MARK_OF_HONOR, MARK_OF_HONOR_MAX);
			}
			break;
		case ACTION_TRIUMPH_TO_STRAND_OF_ANCIENTS:
			if (!player->HasItemCount(EMBLEM_OF_TRIUMPH, CONST_TRIUMPH_TO_STRAND_OF_ANCIENTS))
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_NO_ENOUGH_EMBLEMS, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->DestroyItemCount(EMBLEM_OF_TRIUMPH, CONST_TRIUMPH_TO_STRAND_OF_ANCIENTS, true);
				player->AddItem(STRAND_OF_THE_ANCIENTS_MARK_OF_HONOR, MARK_OF_HONOR_MAX);
			}
			break;
		case ACTION_TRIUMPH_TO_ISLE_OF_CONQUEST:
			if (!player->HasItemCount(EMBLEM_OF_TRIUMPH, CONST_TRIUMPH_TO_ISLE_OF_CONQUEST))
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_NO_ENOUGH_EMBLEMS, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->DestroyItemCount(EMBLEM_OF_TRIUMPH, CONST_TRIUMPH_TO_ISLE_OF_CONQUEST, true);
				player->AddItem(ISLE_OF_CONQUEST_MARK_OF_HONOR, MARK_OF_HONOR_MAX);
			}
			break;
		case ACTION_TRIUMPH_TO_WINTERGRASP:
			if (!player->HasItemCount(EMBLEM_OF_TRIUMPH, CONST_TRIUMPH_TO_WINTERGRASP))
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_NO_ENOUGH_EMBLEMS, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->DestroyItemCount(EMBLEM_OF_TRIUMPH, CONST_TRIUMPH_TO_WINTERGRASP, true);
				player->AddItem(WINTERGRASP_MARK_OF_HONOR, MARK_OF_HONOR_MAX);
			}
			break;
		case ACTION_CURRENCY_EXCHANGE:
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "5 Emblem of Frost -> 1 Cooking Award", GOSSIP_SENDER_MAIN, ACTION_FROST_TO_COOKING_AWARD);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "5 Emblem of Frost -> 1 Jewelcrafting Token", GOSSIP_SENDER_MAIN, ACTION_FROST_TO_JEWELCRAFTING_TOKEN);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "5 Emblem of Frost -> 3 Champion Seal", GOSSIP_SENDER_MAIN, ACTION_FROST_TO_CHAMPIONS_SEAL);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "1 Emblem of Frost -> 5 Stone Keepers Shard", GOSSIP_SENDER_MAIN, ACTION_FROST_TO_STONE_KEEPERS_SHARD);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "<- [Back]", GOSSIP_SENDER_MAIN, EXCHANGE_MENU);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;
		case ACTION_FROST_TO_COOKING_AWARD:
			if (!player->HasItemCount(EMBLEM_OF_FROST, CONST_FROST_TO_COOKING_AWARD))
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_NO_ENOUGH_EMBLEMS, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->DestroyItemCount(EMBLEM_OF_FROST, CONST_FROST_TO_COOKING_AWARD, true);
				player->AddItem(DALARAN_COOKING_AWARD, COOKING_AWARD_MAX);
			}
			break;
		case ACTION_FROST_TO_JEWELCRAFTING_TOKEN:
			if (!player->HasItemCount(EMBLEM_OF_FROST, CONST_FROST_TO_JEWELCRAFTING_TOKEN))
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_NO_ENOUGH_EMBLEMS, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->DestroyItemCount(EMBLEM_OF_FROST, CONST_FROST_TO_JEWELCRAFTING_TOKEN, true);
				player->AddItem(DALARAN_JEWELCRAFTING_TOKEN, JEWELCRAFTING_TOKEN_MAX);
			}
			break;
		case ACTION_FROST_TO_CHAMPIONS_SEAL:
			if (!player->HasItemCount(EMBLEM_OF_FROST, CONST_FROST_TO_CHAMPIONS_SEAL))
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_NO_ENOUGH_EMBLEMS, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->DestroyItemCount(EMBLEM_OF_FROST, CONST_FROST_TO_CHAMPIONS_SEAL, true);
				player->AddItem(CHAMPIONS_SEAL, CHAMPIONS_SEAL_MAX);
			}
			break;
		case ACTION_FROST_TO_STONE_KEEPERS_SHARD:
			if (!player->HasItemCount(EMBLEM_OF_FROST, CONST_FROST_TO_STONE_KEEPERS_SHARD))
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_NO_ENOUGH_EMBLEMS, 0, true);
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				player->DestroyItemCount(EMBLEM_OF_FROST, CONST_FROST_TO_STONE_KEEPERS_SHARD, true);
				player->AddItem(STONE_KEEPERS_SHARD, STONE_KEEPERS_SHARD_MAX);
			}
			break;
		case MOVIE_MENU:
			if (ConfigMgr::GetBoolDefault("Server.Helper.Movie.Menu.Enable", true))
			{
				player->PlayerTalkClass->ClearMenus();
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "World of Warcraft", GOSSIP_SENDER_MAIN, ACTION_MOVIE_WORLD_OF_WARCRAFT);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "The Wrath Gate", GOSSIP_SENDER_MAIN, ACTION_MOVIE_THE_WRATH_GATE);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Fall of The Lich King", GOSSIP_SENDER_MAIN, ACTION_MOVIE_FALL_OF_THE_LICH_KING);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "<- [Main Menu]", GOSSIP_SENDER_MAIN, MAIN_MENU);
				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
				return true;
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_FUNCTION_OFF, 0, true);
			}
			break;
		case ACTION_MOVIE_WORLD_OF_WARCRAFT:
			player->CLOSE_GOSSIP_MENU();
			player->SendMovieStart(MOVIE_WORLD_OF_WARCRAFT);
			break;
		case ACTION_MOVIE_THE_WRATH_GATE:
			player->CLOSE_GOSSIP_MENU();
			player->SendMovieStart(MOVIE_THE_WRATH_GATE);
			break;
		case ACTION_MOVIE_FALL_OF_THE_LICH_KING:
			player->CLOSE_GOSSIP_MENU();
			player->SendMovieStart(MOVIE_FALL_OF_THE_LICH_KING);
			break;
		case FUNNY_MENU:
			if (ConfigMgr::GetBoolDefault("Server.Helper.Funny.Menu.Enable", true))
			{
				player->PlayerTalkClass->ClearMenus();
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Star Craft Murloc", GOSSIP_SENDER_MAIN, ACTION_STARCRAFT_MURLOC);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Ambrose Boltspark", GOSSIP_SENDER_MAIN, ACTION_AMBROSE_BOLTSPARK);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Jonathan The Revelator", GOSSIP_SENDER_MAIN, ACTION_JONATHAN_THE_REVELATOR);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Shattered Sun Mage", GOSSIP_SENDER_MAIN, ACTION_SHATTERED_SUN_MAGE);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Worgen", GOSSIP_SENDER_MAIN, ACTION_WORGEN);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Pandaren Monk", GOSSIP_SENDER_MAIN, ACTION_PANDAREN_MONK);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Algalon", GOSSIP_SENDER_MAIN, ACTION_ALGALON);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Iron Mender", GOSSIP_SENDER_MAIN, ACTION_IRON_MENDER );
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Druid", GOSSIP_SENDER_MAIN, ACTION_DRUID);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Priest", GOSSIP_SENDER_MAIN, ACTION_PRIEST);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Paladin", GOSSIP_SENDER_MAIN, ACTION_PALADIN);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Rogue", GOSSIP_SENDER_MAIN, ACTION_ROGUE);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Death Knight", GOSSIP_SENDER_MAIN, ACTION_DEATH_KNIGHT);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Warlock", GOSSIP_SENDER_MAIN, ACTION_WARLOCK);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Warrior", GOSSIP_SENDER_MAIN, ACTION_WARRIOR);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Mage", GOSSIP_SENDER_MAIN, ACTION_MAGE);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Shaman", GOSSIP_SENDER_MAIN, ACTION_SHAMAN);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Hunter", GOSSIP_SENDER_MAIN, ACTION_HUNTER);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Draenei Girl White", GOSSIP_SENDER_MAIN, ACTION_DRAENEI_GIRL_WHITE);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Draenei Girl Black", GOSSIP_SENDER_MAIN, ACTION_DRAENEI_GIRL_BLACK);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Demorph]", GOSSIP_SENDER_MAIN, ACTION_DEMORPH);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "<- [Main Menu]", GOSSIP_SENDER_MAIN, MAIN_MENU);
				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
				return true;
			}
			else
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterTextEmote(EMOTE_FUNCTION_OFF, 0, true);
			}
			break;
		case ACTION_STARCRAFT_MURLOC:
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(DISPLAY_ID_STARCRAFT_MURLOC);
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 2);
			break;
		case ACTION_AMBROSE_BOLTSPARK:
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(DISPLAY_ID_AMBROSE_BOLTSPARK);
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
			break;
		case ACTION_JONATHAN_THE_REVELATOR:
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(DISPLAY_ID_JONATHAN_THE_REVELATOR);
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
			break;
		case ACTION_SHATTERED_SUN_MAGE:
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(DISPLAY_ID_SHATTERED_SUN_MAGE);
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
			break;
		case ACTION_WORGEN:
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(DISPLAY_ID_WORGEN);
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
			break;
		case ACTION_PANDAREN_MONK:
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(DISPLAY_ID_PANDAREN_MONK);
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 2);
			break;
		case ACTION_ALGALON:
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(DISPLAY_ID_ALGALON);
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.2f);
			break;
		case ACTION_IRON_MENDER:
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(DISPLAY_ID_IRON_MENDER);
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.5f);
			break;
		case ACTION_DRUID:
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(DISPLAY_ID_DRUID);
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.7f);
			break;
		case ACTION_PRIEST:
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(DISPLAY_ID_PRIEST);
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.6f);
			break;
		case ACTION_PALADIN:
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(DISPLAY_ID_PALADIN);
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.7f);
			break;
		case ACTION_ROGUE:
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(DISPLAY_ID_ROGUE);
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.7f);
			break;
		case ACTION_DEATH_KNIGHT:
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(DISPLAY_ID_DEATH_KNIGHT);
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.7f);
			break;
		case ACTION_WARLOCK:
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(DISPLAY_ID_WARLOCK);
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.7f);
			break;
		case ACTION_WARRIOR:
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(DISPLAY_ID_WARRIOR);
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
			break;
		case ACTION_MAGE:
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(DISPLAY_ID_MAGE);
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.7f);
			break;
		case ACTION_SHAMAN:
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(DISPLAY_ID_SHAMAN);
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.6f);
			break;
		case ACTION_HUNTER:
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(DISPLAY_ID_HUNTER);
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.6f);
			break;
		case ACTION_DRAENEI_GIRL_WHITE:
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(DISPLAY_ID_DRAENEI_GIRL_WHITE);
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
			break;
		case ACTION_DRAENEI_GIRL_BLACK:
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(DISPLAY_ID_DRAENEI_GIRL_BLACK);
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
			break;
		case ACTION_DEMORPH:
			player->CLOSE_GOSSIP_MENU();
			player->DeMorph();
			player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
			break;
		case MAIN_MENU:
			OnGossipHello(player, creature);
			break;
        }
		return true;
    }
};

void AddSC_npc_server_helper()
{
	new npc_server_helper();
}