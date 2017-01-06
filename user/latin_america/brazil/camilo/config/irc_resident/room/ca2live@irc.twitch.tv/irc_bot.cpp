#include "framework.h"
#pragma comment (lib,"announcecom.lib" )
#pragma comment (lib,"vericard.lib" )
#pragma comment (lib,"xmpp.lib" )
#pragma comment (lib,"app_core_xmpp_bot.lib" )
#pragma comment (lib,"app_core_xmpp_client.lib" )
#pragma comment (lib,"app_core_xmpp_resident.lib" )
#pragma comment (lib,"app_core_resident.lib" )
#pragma comment (lib,"irc.lib" )
#pragma comment (lib,"app_core_irc_bot.lib" )
#pragma comment (lib,"app_core_irc_client.lib" )
#pragma comment (lib,"app_core_irc_resident.lib" )
#pragma comment (lib,"beampro.lib" )
#pragma comment (lib,"app_core_beampro_bot.lib" )
#pragma comment (lib,"app_core_beampro_client.lib" )
#pragma comment (lib,"app_core_beampro_resident.lib" )
#pragma comment (lib,"user32.lib" )

#define __IRC


class this_plugin :
	virtual public ::irc_resident::plugin
{


	public:
	
	



	




      

      this_plugin(::aura::application * papp, object * p) :
		object(papp),
      ::vericard::chat_item(papp),
      ::vericard::plugin(papp,dynamic_cast <::vericard::comm * > (p)),
		::irc_resident::plugin(papp, dynamic_cast <::vericard::comm * > (p))


		#include "../../../xmpp_resident/room/ca2@livecoding.tv/xmpp_bot_common.cpp"


};


BEG_ONLY_FACT
CREATE_OBJECT_ENTRY("plugin",this_plugin)
END_ONLY_FACT



