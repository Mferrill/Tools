/*******************************************************************************************
*						 __                           __ _   							   *
*					  /\ \ \___  _ __ ___  ___  ___  / _| |_ 							   *
*					 /  \/ / _ \| '_ ` _ \/ __|/ _ \| |_| __|							   *
*					/ /\  / (_) | | | | | \__ \ (_) |  _| |_ 							   *
*					\_\ \/ \___/|_| |_| |_|___/\___/|_|  \__|	- www.Nomsoftware.com -	   *
*                               The policy of Nomsoftware states: Releasing our software   *
*                               or any other files are protected. You cannot re-release    *
*                               anywhere unless you were given permission.                 *
*                           (C) Nomsoftware 'Nomsoft' 2011-2012. All rights reserved.      *
********************************************************************************************/
/**********************************************************
**********************************************************
 *                      Title:                          *
  *             	Bounty Hunter 					   *
   *        Scripted for the Nomsoft Server           *
	*           					                 *
	 *            Scripted by: Tommy                *
	  *     (C)Nomsoftware 'Nomsoft' 2012          *
	   *-----------------------------------------*/
#include "ScriptPCH.h"
#include <map>

using namespace std;

#define MSG_PLACE_BOUNTY "I would like to place a bounty. [10g]"

/* Bounty Misc */
void DoSendMessageToWorld(int msg, string name, string playerName)
{
	ostringstream ss;
	if (msg == 1)
	{
		ss << "|cffFF0000A Bounty has been placed on "
			<< name.c_str()
			<< "'s head!|r";
	}
	else if (msg == 2)
	{
		ss << "|cffFFA500Increased the price on "
			<< name.c_str()
			<< "'s head!|r";
	}
	else if (msg == 3)
	{
		ss << "|cffFF0000 "
			<< playerName.c_str()
			<< " has killed "
			<< name.c_str()
			<< ", a bounty target!";
	}
	sWorld->SendGlobalText(ss.str().c_str(), NULL);
}

/* Bounty Enumeration */
enum eGold
{
	BOUNTY_AMOUNT_GOLD = 100000
};

/* Bounty Map */
struct BountyInfo
{
	string name;
	string bounty;
	uint64 hunted;
	uint64 hunter;
	uint32 gold;
};

map<uint64, BountyInfo> Bounty;

class npc_b_hunter : public CreatureScript
{
    public:
		npc_b_hunter() : CreatureScript("npc_bounty_hunter") { }

		bool OnGossipHello(Player * player, Creature * creature)
		{
			player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_BATTLE, MSG_PLACE_BOUNTY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1, "", 0, true);
			if(!Bounty.empty())
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Show Bounty List", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Nevermind..", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			return true;
		}

		bool OnGossipSelect(Player * player, Creature * creature, uint32 sender, uint32 actions)
		{
			player->PlayerTalkClass->ClearMenus();
			if(sender != GOSSIP_SENDER_MAIN)
				return false;

			switch(actions)
			{
			   case GOSSIP_ACTION_INFO_DEF+2:
				   for(map<uint64, BountyInfo>::const_iterator i = Bounty.begin(); i != Bounty.end(); ++i)
					   ChatHandler(player).PSendSysMessage("Current Bounties: \n Name: %s, Money: %u, Bounty: %s", i->second.name.c_str(), i->second.gold, i->second.bounty.c_str());
				   player->PlayerTalkClass->SendCloseGossip();
				   break;

			   case GOSSIP_ACTION_INFO_DEF+4:
				   player->PlayerTalkClass->SendCloseGossip();
				   break;
			}
			return true;
		}

		bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, const char* code)
		{
			player->PlayerTalkClass->ClearMenus();
			if(sender != GOSSIP_SENDER_MAIN)
				return false;

			string name = code;
			Player * hunted = NULL;

			switch(action)
			{
			   case GOSSIP_ACTION_INFO_DEF+1:
				   for(map<uint64, BountyInfo>::const_iterator i = Bounty.begin(); i != Bounty.end(); ++i)
				   {
					   if(i->second.bounty == player->GetName())
					   {
						   ChatHandler(player).SendSysMessage("You have already placed a bounty!");
						   player->PlayerTalkClass->SendCloseGossip();
						   return false;
					   }

					   if(i->second.hunted == player->GetGUID())
					   {
						   ChatHandler(player).SendSysMessage("You cannot place a bounty if you're being hunted!");
						   player->PlayerTalkClass->SendCloseGossip();
						   return false;
					   }

					   if(i->second.hunted == hunted->GetGUID())
					   {
						   Bounty[i->second.hunter].gold += BOUNTY_AMOUNT_GOLD;
						   ChatHandler(player).PSendSysMessage("A hunter already made his mark on %s! So, the price for this bounty went up!", i->second.name.c_str());
						   DoSendMessageToWorld(2, i->second.name, "");
						   player->PlayerTalkClass->SendCloseGossip();
						   return false;
					   }
				   }

				   if(player->GetMoney() >= BOUNTY_AMOUNT_GOLD)
				   {
					   player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_BATTLE, MSG_PLACE_BOUNTY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1, "", 0, true);
					   player->ModifyMoney(-BOUNTY_AMOUNT_GOLD);
				   }
				   else
				   {
					   ChatHandler(player).SendSysMessage("You don't have enough gold!");
					   player->PlayerTalkClass->SendCloseGossip();
					   return false;
				   }
				   if(!name.empty())
					   hunted = sObjectAccessor->FindPlayerByName(name.c_str());

				   if(name == player->GetName())
				   {
					   ChatHandler(player).SendSysMessage("You cannot place a bounty on yourself!");
					   player->PlayerTalkClass->SendCloseGossip();
					   return false;
				   }

				   if(!hunted)
				   {
					   ChatHandler(player).PSendSysMessage("Player %s is not online.", name.c_str());
					   player->PlayerTalkClass->SendCloseGossip();
					   return false;
				   }
				   Bounty[hunted->GetGUID()].hunted = hunted->GetGUID();
				   Bounty[hunted->GetGUID()].hunter = player->GetGUID();
				   Bounty[hunted->GetGUID()].gold = BOUNTY_AMOUNT_GOLD;
				   Bounty[hunted->GetGUID()].name = name.c_str();
				   Bounty[hunted->GetGUID()].bounty = player->GetName();
				   ChatHandler(player).PSendSysMessage("|cffFF0000Bounty was placed on %s!|r", name.c_str());
				   player->Whisper("I placed a Bounty on you!", LANG_UNIVERSAL, hunted->GetGUID());
				   DoSendMessageToWorld(1, name.c_str(), "");
				   player->PlayerTalkClass->SendCloseGossip();
				   break;
			}
			hunted = NULL;
			name = "";
			return false;
		}
};

class bounty_kills : public PlayerScript
{
   public:
	   bounty_kills() : PlayerScript("bounty_kills") { }

	   void OnPVPKill(Player * killer, Player * victim)
	   {
		   if(killer->GetGUID() == victim->GetGUID() || Bounty.empty())
			   return;

		   for(map<uint64, BountyInfo>::const_iterator i = Bounty.begin(); i != Bounty.end(); ++i)
		   {
			   if(i->second.hunted == victim->GetGUID())
			   {
				   killer->ModifyMoney(Bounty[victim->GetGUID()].gold);
				   ChatHandler(killer).PSendSysMessage("Added %u gold for your kill!", Bounty[victim->GetGUID()].gold);
				   Bounty.erase(victim->GetGUID());
				   DoSendMessageToWorld(3, victim->GetName(), killer->GetName());
			   }
		   }
	   }
};

void AddSC_bounties_hunters()
{
	new npc_b_hunter;
	new bounty_kills;
}