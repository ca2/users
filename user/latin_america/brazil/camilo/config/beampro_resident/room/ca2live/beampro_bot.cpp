#include "framework.h"
#include "app-core/appseed/resident/resident.h"
#pragma comment (lib,"vericard.lib" )
#pragma comment (lib,"beampro.lib" )
#pragma comment (lib,"app_core_beampro_bot.lib" )
#pragma comment (lib,"app_core_beampro_client.lib" )
#pragma comment (lib,"app_core_beampro_resident.lib" )
#pragma comment (lib,"app_core_resident.lib" )

class this_plugin :
	virtual public ::beampro_resident::plugin
{
	
	public:
	
   
   
	
      this_plugin(::aura::application * papp, object * p) :
		object(papp),
      ::vericard::chat_item(papp),
      ::vericard::plugin(papp,dynamic_cast <::vericard::comm * > (p)),
		::beampro_resident::plugin(papp, dynamic_cast <::vericard::comm * > (p))

		#include "../../../xmpp_resident/room/ca2@livecoding.tv/xmpp_bot_common.cpp"



};



BEG_ONLY_FACT
CREATE_OBJECT_ENTRY("plugin",this_plugin)
END_ONLY_FACT



