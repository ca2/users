#include "framework.h"
#include "resident.h"
#pragma comment (lib,"announcecom.lib" )
#pragma comment (lib,"vericard.lib" )
#pragma comment (lib,"app_core_resident.lib" )
#pragma comment (lib,"user32.lib" )


#include "app-core/appseed/vericard/vericard_animation.h"

#include "vericard_animation_disco.cpp"


#define __XMPP




class this_plugin:
   virtual public ::vericard::plugin
{
public:  

























   




























   




  


      
   this_plugin(::aura::application * papp, object * p) :
      object(papp),
      ::vericard::chat_item(papp),
      ::vericard::plugin(papp, dynamic_cast <::vericard::comm *> (p))
   {

      construct_this_plugin();

   }

#include "bot_common.cpp"




      ::vericard::animation * create_animation(string strAnimation)
   {

      if (strAnimation == "disco")
      {

         return new ::vericard::animation_disco(&Application.veripack());

      }

      return NULL;

   }

};












   BEG_ONLY_FACT
   CREATE_OBJECT_ENTRY("plugin",this_plugin)
   END_ONLY_FACT








      










