

string on_new_host(const string & strHost, int iViewers)
{

   string strMessage;

   if (iViewers <= 0)
   {

      strMessage = "Thank you for hosting, " + strHost + "!!";

   }
   else
   {

      strMessage =  "Thank you " + strHost + " for hosting with" + ::str::from(iViewers) + " viewers!!";

   }

   /*

   auto puser = get_user(strHost);

   string strLang = Application.lang(puser->get_user_data("lang").get_string().lower());

   if(strLang.is_empty())
   {

      string strCountry = puser->get_user_data("country_code").get_string().lower();

      if(strCountry.is_empty())
      {

         strCountry = puser->get_user_info("country_code").get_string().lower();

         puser->set_user_data("country_code",strCountry);

      }

      strLang = Application.initial_country_lang(strCountry);

      puser->set_user_data("lang",strLang);

   }

   if(strLastLang.is_empty())
   {

      strLastLang = strLang;

   }

   */

   spa(::vericard::user) usera;

//   for (auto strUser : straNew)
   {

      auto puser = get_user(strHost);

      usera.add(puser);

   }

   Application.veripack().add_announce(strMessage, usera, 15000);

   //ws(strHost, false, true);

   hostsbell();

   m_pcomm->msg(strMessage);

   lspeak("","en",strMessage, true);


   return "";

}










