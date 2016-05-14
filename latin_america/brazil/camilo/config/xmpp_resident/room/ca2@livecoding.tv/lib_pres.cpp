
string on_pres(string strUser,string strType)
{
   m_strUser = strUser;
   int iThreshold = 16;

   string strTopic;
   m_strCountry = get_user_country_code(strUser, true);
   m_strLang = get_user_lang(strUser);
   string strTimeZone = get_user_data(strUser, "time_zone");
   if (strTimeZone.is_empty())
   {
      strTimeZone = initial_locality_time_zone(m_strCountry, get_lctv_info(strUser, "city"));
      set_user_data(strUser, "time_zone_text", strTimeZone);
      set_user_data(strUser, "time_zone", time_zone(strTimeZone));
   }
   var strName = username(strUser, m_strLang);
   
   if(strType == "unavailable")
   {


      ::datetime::time last_back;

      last_back.m_time = get_user_data(strUser, "last_presence").int64();

      ::datetime::time now = ::datetime::time::get_current_time();

      set_user_data(strUser, "last_see_you", now.m_time);

      set_user_data(strUser, "back", 0);

      ::fork(get_app(), [=]()
      {

         Sleep(iThreshold * 1000);

         if (get_user_data(strUser, "back") == 0)
         {
   
            string strSpeakText;
            string strText;

            if(get_user_data(strUser, "official_back") == 1)
            {

               set_user_data(strUser, "official_back", 0);

               if (spam(strUser))
               {

                  strText = _t("%name gone, uff...");

               }
               else if (isbot(strUser))
               {

                  strText = _t("%name was unplugged!");

               }
               else
               {

                  if (get_user_data(strUser, "visit_count") <= 4)
                  {

                     bye();

                     strText = _t("Bye %name! :(");

                  }
                  else
                  {

                     if (now.m_time - last_back.m_time > 8 * 60)  // 1 hour
                     {

                        strText = _t("See you %name! :(");

                        bye();

                     }
                     else
                     {

                        strText = _t("See you %name! :(");

                        strText.replace(":(", "");

                        bye();

                     }

                  }

                  lspeak(strUser, m_strLang, strSpeakText);

               }

            }
            else if (now.m_time - last_back.m_time < iThreshold)
            {

               strText = _t("%name passed by here...");

            }
            
#ifdef __XMPP
            ::xmpp::comm * pcomm = dynamic_cast <::xmpp::comm *>(m_pcomm);
            pcomm->msg(strText);
#endif

         }

      });
      return "";

   }
   else
   {

      ::datetime::time last_see_you;

      last_see_you.m_time = get_user_data(strUser, "last_see_you").int64();

      ::datetime::time now = ::datetime::time::get_current_time();

      set_user_data(strUser, "last_presence", now.m_time);

      set_user_data(strUser, "back", 1);

//      if (now.m_time - last_see_you.m_time > 8)
      {

         ::fork(get_app(), [=]()
         {

            Sleep(iThreshold * 1000);

            if (get_user_data(strUser, "back") == 1 && get_user_data(strUser, "official_back") == 0)
            {

               set_user_data(strUser, "official_back", 1);

               string strText;
               string strSpeakText;

               if (spam(strUser))
               {
                  strText = strUser + " entered!! (Subset of commands enabled).";
               }
               else if (isbot(strUser))
               {
                  strText = strName + " you are connected!";
               }
               else
               {

                  if (get_user_data(strUser, "visit_count") <= 4)
                  {
                     
                     ws(strUser, true);

                     param1(_trans1(welcome_time));

                     set_user_data(strUser, "last_welcome_time", _trans1(welcome_time));

                     strText = _t("Welcome %name! :) %param1 You can type exclamation mark and then press enter to get some help.");

                     if (m_strCountry == "be")
                     {
                        strText += "\nYou can choose between \"Nederlands\", \"Deutsch\" and \"Français\" using \"!setlang nl\", \"!setlang de\" or \"!setlang fr\"";
                     }
                     else if (m_strCountry == "ch")
                     {
                        strText += "\nYou can choose between \"Deutsch\", \"Français\" and \"Italiano\" using \"!setlang de\", \"!setlang fr\" or \"!setlang it\"";
                     }
                     else if (m_strCountry == "ca")
                     {
                        strText += "\nYou can choose between \"Français\" and \"English\" using \"!setlang fr\" or \"!setlang en\"";
                     }
                  }
                  else if (get_user_data(strUser, "last_visit") > 60 * 60 * 18 || get_user_data(strUser, "today_visit_count") <= 1)
                  {

                     ws(strUser, true);

                     param1(_trans1(welcome_time));

                     set_user_data(strUser, "last_welcome_time", _trans1(welcome_time));

                     strText = _t("Hi %name! Welcome! %param1 What brings you here today?");

                  }
                  else if (get_user_data(strUser, "last_visit") > 60 * 60 * 3 || get_user_data(strUser, "last_welcome_time") != _trans1(welcome_time))
                  {

                     ws(strUser, true);

                     param1(_trans1(name_welcome_time));

                     set_user_data(strUser, "last_welcome_time", _trans1(welcome_time));

                     strText = _t("%param1! :)");

                  }
                  else
                  {


                     strText = _t("%name is back! :)");

                     if (now.m_time - last_see_you.m_time > 8 * 60)  // 8 (infinite standing up) minutes
                     {

                        ws(strUser, true);

                     }
                     else
                     {

                        doorbell();

                     }

                  }

                  lspeak(strUser, m_strLang, strSpeakText);

               }

#ifdef __XMPP
               ::xmpp::comm * pcomm = dynamic_cast <::xmpp::comm *>(m_pcomm);
               pcomm->msg(strText);
#endif
            }

         });

      }

      return "";

   }

}




