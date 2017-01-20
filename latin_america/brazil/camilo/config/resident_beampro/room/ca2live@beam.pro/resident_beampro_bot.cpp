#include "framework.h"
#pragma comment (lib,"announcecom.lib" )
#pragma comment (lib,"vericard.lib" )
#pragma comment (lib,"app_core_resident.lib" )
#pragma comment (lib,"user32.lib" )


#define __BEAM

class this_plugin :
	virtual public ::vericard::plugin
{
	
	public:
	


   
   



	
      this_plugin(::aura::application * papp, object * p) :
		object(papp),
      ::vericard::chat_item(papp),
      ::vericard::plugin(papp,dynamic_cast <::vericard::comm * > (p))

		#include "../../../resident_liveedutv/room/ca2@livecoding.tv/bot_common.cpp"



};



BEG_ONLY_FACT
CREATE_OBJECT_ENTRY("plugin",this_plugin)
END_ONLY_FACT



