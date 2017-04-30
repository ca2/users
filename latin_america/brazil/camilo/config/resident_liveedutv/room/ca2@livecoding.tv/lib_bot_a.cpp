string bot_a()
{
   string strText = m_strText;

   string strSpeakText;

   string & strTopic = m_strTopic;

   string & strTopicUser = m_strTopicUserId;
   
   string str;

   string & strUserParam = m_strUserId;

   string & strNameParam = m_strName;

   string & strCountry = m_strCountry;

   string & strLangParam = m_strLang;

   string & strTimeZone = m_strTimeZone;
   
   string & strOther = m_strOtherUserId;

   string & strOtherName = m_strOtherName;

   string & strOtherCountry = m_strOtherCountry;

   string & strOtherLang = m_strOtherLang;
   
   string & strOtherTimerZone = m_strOtherTimeZone;

   string & strUser = m_strUserId;
   
   string & strName = m_strName;

   string & strLang = m_strLang;

   string strLoText = lotext();

   string strQuery = strText;

   bool bPlay = false;

#ifdef __XMPP

   bool bAdmin = strUser == "ca2" || strUser == "ca2live" || strUser == "ca2bot" || strUser == "resident";

#else

   bool bAdmin = strUser == "ca2" || strUser == "ca2live" || strUser == "ca2bot";

#endif

   stringa straAdj;

   straAdj.add("nice");

   stringa straGreet;
   straGreet.add("welcome");
   straGreet.add("wb");

   if (::str::x_contains(strQuery, "resident") || ::str::x_contains(strQuery, "bot")  || ::str::x_contains(strQuery, "ca2bot"))
   {

      if (::str::x_find(straAdj, strQuery))
      {

         if (::str::x_find(straGreet, strQuery))
         {

            str = _t("Thank you, %name!!");

         }

      }


   }

   if (::str::x_contains(strQuery, "cya") || ::str::x_contains(strQuery, "see you") || ::str::x_contains(strQuery, "bye"))
   {

      str = _t("See you, %name!!");

   }

   if (::str::x_contains(strQuery, "hi") || ::str::x_contains(strQuery, "hello") || ::str::x_contains(strQuery, "hey"))
   {

      str = _t("Hi, %name!!");

   }

   if (::str::x_contains(strQuery, "yay") || ::str::x_contains(strQuery, "yey") || ::str::x_contains(strQuery, "wow"))
   {

      str = _t("Victory!!");

   }

   if(str.is_empty())
   {

      // this is the default behaviour of bot_a

      m_pcomm->add_chat(this);

      return "";

   }
   
   bool bSpeakable = true;

   if (!consider_speakable_text(strText))
   {
      
      str = _t("I am not going to say that phrase.");

      bSpeakable = false;

   }

   if (!str.has_char() && strSpeakText.has_char())
   {

      m_bSpeak = true;

   }

   m_strResponse = str;

   m_pcomm->add_chat(this);

   if (str.has_char())
   {

      string strMessage = m_pcomm->prepare_message(str);

      Application.veripack().schedule_speech(strUser, m_strLang, strMessage, strSpeakText, this);

      m_pcomm->post_message(strMessage, true);

   }
   else if(strSpeakText.has_char())
   {
      
      if (!lspeak(strUser, m_strLang, strSpeakText, true))
      {

      }

   }

   return "";

}


