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


   if (xcontains(strQuery, "resident") || xcontains(strQuery, "bot")  || xcontains(strQuery, "ca2bot"))
   {

      if (xfind(straAdj, strQuery))
      {

         if (xfind(straGreet, strQuery))
         {

            str = _t("Thank you, %name!!");

         }

      }


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


bool xcontains(string str, string strFind)
{

   strsize iFind = 0;

   while((iFind = str.find_ci(strFind, iFind)) >= 0)
   {

      bool bLowerBound1 = iFind == 0;
      bool bLowerBound = bLowerBound1 || !isalpha_dup(strFind[iFind-1]);
      strsize iUpperBound = iFind + strFind.get_length();
      bool bUpperBound1 = iUpperBound == str.get_length();
      bool bUpperBound = bUpperBound1 || !isalpha_dup(strFind[iUpperBound]);

      if(bLowerBound && bUpperBound)
      {
         
         return true;

      }

      iFind++;

   }

   return false;

}

bool xfind(stringa & stra, string str)
{

   for(auto & strFind : stra)
   {

      if(xcontains(str, strFind))
      {

         return true;

      }

   }

   return false;

}
