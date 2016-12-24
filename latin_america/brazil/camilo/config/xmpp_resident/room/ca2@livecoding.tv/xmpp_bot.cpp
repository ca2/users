#include "resident.h"
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


#include "app-core/appseed/vericard/vericard_animation.h"

#include "vericard_animation_disco.cpp"


#define __XMPP




class this_plugin:
   virtual public ::xmpp_resident::plugin
{
public:  


























   




























   




  


      
   this_plugin(::aura::application * papp, object * p) :
      object(papp),
      ::vericard::chat_item(papp),
      ::vericard::plugin(papp, dynamic_cast <::vericard::comm *> (p)),
      ::xmpp_resident::plugin(papp, dynamic_cast <::vericard::comm *> (p))

#include "xmpp_bot_common.cpp"




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








      










