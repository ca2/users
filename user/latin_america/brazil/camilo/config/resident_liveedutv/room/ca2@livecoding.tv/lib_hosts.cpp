

string on_new_host(const string & strHost, int iViewers)
{

   string strMessage;

   string strSpeakText;

   auto puser = get_user(strHost, true);

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

   param(1, username(strHost, strLang));

   param(2, ::str::from(iViewers));

   if (iViewers <= 0)
   {

      strMessage = _t("Thank you for hosting, %param1!!");

   }
   else
   {

      strMessage = _t("Thank you %param1 for hosting with %param2 viewers!!");

   }

   spa(::vericard::user) usera;

   usera.add(puser);

   Application.veripack().add_announce(strMessage, usera, 15000);

   hostsbell();

   m_pcomm->msg(strMessage);

   lspeak(strHost,strLang,strSpeakText, true);

   Sleep(15000);

   return "";

}










