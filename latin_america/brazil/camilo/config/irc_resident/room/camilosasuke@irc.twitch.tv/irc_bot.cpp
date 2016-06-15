#include "framework.h"
#include "app-core/appseed/irc_resident/irc_resident.h"
#pragma comment (lib,"vericard.lib" )
#pragma comment (lib,"irc.lib" )
#pragma comment (lib,"app_core_irc_bot.lib" )
#pragma comment (lib,"app_core_irc_client.lib" )
#pragma comment (lib,"app_core_irc_resident.lib" )


class this_plugin :
	virtual public ::irc_resident::plugin
{
	
	public:
	
	
      this_plugin(::aura::application * papp, object * p) :
		object(papp),
      ::vericard::chat_item(papp),
      ::vericard::plugin(papp,dynamic_cast <::vericard::comm * > (p)),
		::irc_resident::plugin(papp, dynamic_cast <::vericard::comm * > (p))


		#include "C:\Users\camilo\AppData\Roaming\ca2\system\config\xmpp_resident\room\ca2@livecoding.tv\xmpp_bot_common.cpp"


};


BEG_ONLY_FACT
CREATE_OBJECT_ENTRY("plugin",this_plugin)
END_ONLY_FACT



