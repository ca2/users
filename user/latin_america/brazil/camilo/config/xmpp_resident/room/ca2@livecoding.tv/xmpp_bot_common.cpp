{
   m_straSpecialCommand.add("exclamation");
   m_straSpecialCommand.add("exclamation mark");
}

stringa m_straSpecialCommand;

#define _t(strText) get_text(strSpeakText, strLang, strText, strName, strTopic, t_straParam)

string_map < string_to_string > m_text;

string_map < file_time > m_ftime;

bool _load_text(string strLang)
{

   auto & m = m_text[strLang];

   //::file::path path = "C:\\ca2\\config\\xmpp_resident\\room\\"+ m_pcomm->get_room_id()+"\\xmpp_resident_po\\" + strLang + ".po";
#ifdef WINDOWS
   	::file::path path = "C:\\ca2\\config\\xmpp_resident\\room\\ca2@livecoding.tv\\xmpp_resident_po\\" + strLang + ".po";
#else
	::file::path path = "/home/camilo/.ca2/config/xmpp_resident/room/ca2@livecoding.tv/xmpp_resident_po/" + strLang + ".po";
#endif

   ::file_time ft = get_file_time(path);

   if (m_ftime[strLang] == ft)
   {

      return true;

   }

   m_ftime[strLang] = ft;

   string strPo = Application.file().as_string(path);

   stringa stra;

   stra.add_lines(strPo);
   int iState = -1;
   string strMsgId;
   string strText;

   for (index i = 0; i < stra.get_count();  i++)
   {
      string strLine = stra[i];

      const char * psz = strLine;
      const char * pszEnd = psz + strLine.get_length();

      ::str::consume_spaces(psz, 0, pszEnd);
      try
      {
         if (iState == -1)
         {
            strMsgId = ::str::consume_nc_name(psz);
            if (strMsgId == "msgid")
            {
               iState = 0;
               ::str::consume_spaces(psz, 1, pszEnd);
               strMsgId = ::str::consume_quoted_value_ex(psz, pszEnd);
            }
         }
         else if (iState == 0)
         {
            strText = ::str::consume_nc_name(psz);
            if (strText == "msgtext")
            {
               iState = -1;
               ::str::consume_spaces(psz, 1, pszEnd);
               strText = ::str::consume_quoted_value_ex(psz, pszEnd);
               m[strMsgId] = strText;
            }


         }
      }
      catch (...)
      {


      }
   }


   return true;

}


string_map < string_to_string > m_country;

string_map < file_time > m_ftimeCountry;




string get_country(string strLang, string strCountry)
{

   strLang.make_upper();

   strCountry.make_upper();
#ifdef WINDOWS
   ::file::path path = "C:\\ca2\\config\\xmpp_resident\\room\\ca2@livecoding.tv\\xmpp_resident_country\\" + strLang + ".json";
#else
	::file::path path = "/home/camilo/.ca2/config/xmpp_resident/room/ca2@livecoding.tv/xmpp_resident_country/" + strLang + ".json";
#endif

   ::file_time ft = get_file_time(path);

   if (m_ftimeCountry[strLang] == ft)
   {

      return m_country[strLang][strCountry];

   }

   m_ftimeCountry[strLang] = ft;

   string strJson = Application.file().as_string(path);

   try
   {

      const char * psz = strJson;

      var v;

      v.parse_json(psz);

      for (auto & item : v.vara())
      {
         
         m_country[strLang][item["code"].get_string().upper()] = item["name"];

      }

   }
   catch (...)
   {


   }

   return m_country[strLang][strCountry];

}


string _get_text(string strLang, string strId)
{

   _load_text(strLang);

   auto p = m_text.PLookup(strLang);

   if (p == NULL)
   {

//         _load_text(strLang);

      //       p = m_text.PLookup(strLang);

      //     if (p == NULL)
      //   {

      //    return strId;

      //}

      return strId;

   }

   if(p->m_element2[strId].is_empty())
      return strId;
   else
      return p->m_element2[strId];

}

string get_text(string & strSpeakText, string strLang, string strId, string strName, string strTopic, stringa straParam)
{

   string strText = _get_text(strLang, strId);

   strSpeakText = strText;

   strSpeakText.replace("($name)", "");
   strSpeakText.replace("$name", "");
   strSpeakText = process_text(strSpeakText, strName, strTopic, straParam);

   if (strLang == "en" || strLang == "pt" || strLang == "de" || strLang == "nl")
   {
      strSpeakText.replace(":)", "");
      strSpeakText.replace(":(", "");
   }



   strText.replace("($name)", "(%name)");
   strText.replace("$name", "%name");
   return process_text(strText, strName, strTopic, straParam);

}

string process_text(string strText, string strName, string strTopic, stringa straParam)
{
   int iFind = 0;
   while (true)
   {
      iFind = strText.find_ci("%name", iFind);

      if (iFind < 0)
         break;

      if (iFind == 0)
      {
         strText = strName + strText.Mid(5);
      }
      // lazy check, it is not correct way of checking, it may result errors (triple %)
      else if(strText[iFind - 1] != '%')
      {
         strText = strText.Left(iFind) + strName + strText.Mid(iFind + 5);
      }
      iFind += 5;
   }
   iFind = 0;
   while (true)
   {
      iFind = strText.find_ci("%topic", iFind);

      if (iFind < 0)
         break;

      if (iFind == 0)
      {
         strText = strName + strText.Mid(6);
      }
      // lazy check, it is not correct way of checking, it may result errors (triple %)
      else if (strText[iFind - 1] != '%')
      {
         strText = strText.Left(iFind) + strTopic + strText.Mid(iFind + 6);
      }
      iFind += 6;
   }
   string strParamName;
   for (index i = 0; i < straParam.get_size(); i++)
   {
      iFind = 0;
      strParamName = "%param" + ::str::from(i + 1);
      while (true)
      {
         iFind = strText.find_ci(strParamName, iFind);

         if (iFind < 0)
            break;

         if (iFind == 0)
         {
            strText = strName + strText.Mid(strParamName.get_length());
         }
         // lazy check, it is not correct way of checking, it may result errors (triple %)
         else if (strText[iFind - 1] != '%')
         {
            strText = strText.Left(iFind) + strTopic + strText.Mid(strParamName.get_length());
         }
         iFind += 6;
      }
   }
   return strText;
}

string warn(string strUser)
{
   return "This operation is not permitted to you, " + strUser + "! Contact moderator if you think its wrong.";
}
bool enable_tts(string strLang)
{

#ifdef LINUX
   return false;
#endif
   if (strLang == "en")
   {
      return true;
   }
   else if (strLang == "fr")
   {
      return true;
   }
   else if (strLang == "de")
   {
      return true;
   }
   else if (strLang == "pl")
   {
      return true;
   }
   else if (strLang == "zh")
   {
      return true;
   }
   else if (strLang == "cn")
   {
      return true;
   }
   else if (strLang == "tw")
   {
      return true;
   }
   else if (strLang == "pt")
   {
      return true;
   }
   else if (strLang == "br")
   {
      return true;
   }
   else if (strLang == "es")
   {
      return true;
   }
   else if (strLang == "it")
   {
      return true;
   }
   else if (strLang == "kr")
   {
      return true;
   }
   else if (strLang == "ru")
   {
      return true;
   }
   else if (strLang == "jp")
   {
      return true;
   }
   else if (strLang == "pl")
   {
      return true;
   }
   else if (strLang.is_empty())
   {
      return true;
   }
   else
   {
      return false;
   }

}

bool isbot(string strUser)
{

   if (::str::find_ci(strUser, "l3vl69") >= 0)
   {
      return true;
   }
   else if(::str::find_ci(strUser,"iamfree") >= 0)
   {
      return true;
   }
   else if(::str::find_ci(strUser,"iwanttodie") >= 0)
   {
      return true;
   }
   else if(::str::begins_ci(strUser,"bot"))
   {
      return true;
   }
   else if(::str::ends_ci(strUser,"bot"))
   {
      return true;
   }
   else
   {
      return false;
   }
}
void olink(string strUser,string strUrl)
{
   if(spam(strUser))
   {
   }
   else
   {
      open_link(strUrl);
   }
}
bool spam(string strUser)
{
   if(::str::begins_ci(strUser,"spam"))
   {
      return true;
   }
   else if(::str::ends_ci(strUser,"spam"))
   {
      return true;
   }
   else if(strUser.CompareNoCase("coldzer0") == 0)
   {
      return true;
   }
   else if (strUser.CompareNoCase("bamberino") == 0 || strUser.CompareNoCase("bamb3rino") == 0)
   {
      return true;
   }
   else if (strUser.CompareNoCase("daratho") == 0)
   {
      return true;
   }
   else
   {
      return false;
   }
}
bool lspeak(string strUser,string strLang,string strText)
{

   if (!consider_speakable_text(strText))
   {

      return false;

   }

   strText = " " + strText + " ";
   int iFind = 0;
   while (true)
   {
      iFind = strText.find_ci("ca2", iFind);
      if (iFind < 0)
         break;
      if (!isalnum(strText[iFind - 1]) && !isalnum(strText[iFind + 3]))
      {
         strText = strText.Left(iFind) + " c a 2 " + strText.Mid(iFind + 3);
      }
      iFind += 3;
   }
   if(spam(strUser))
   {
      return false;
   }
   else if (!enable_tts(strLang))
   {
      trans_speak(trans_lang(strLang), strText);
   }
   else
   {
      lang_speak(tts_lang(strLang),strText);
   }
   return true;
}
string  lang(string strLang)
{
   if(strLang == "br")
   {
      return "pt";
   }
   else if(strLang == "do")
   {
      return "es";
   }
   else if(strLang == "co")
   {
      return "es";
   }
   else if(strLang == "pe")
   {
      return "es";
   }
   else if(strLang == "ec")
   {
      return "es";
   }
   else if(strLang == "mx")
   {
      return "es";
   }
   else if(strLang == "pa")
   {
      return "es";
   }
   else if(strLang == "py")
   {
      return "es";
   }
   else if(strLang == "uy")
   {
      return "es";
   }
   else if(strLang == "ar")
   {
      return "es";
   }
   else if(strLang == "cl")
   {
      return "es";
   }
   else if(strLang == "us")
   {
      return "en";
   }
   else if (strLang == "ja")
   {
      return "jp";
   }
   else if(strLang == "uk")
   {
      return "en-uk";
   }
   else if(strLang == "en-uk")
   {
      return "en-uk";
   }
   else if (strLang == "zh-tw")
   {
      return "tw";
   }
   else if (strLang == "zh-cn")
   {
      return "cn";
   }
   else
   {
      stringa stra;
      stra.explode("-",strLang);
      if(stra.get_count() == 2)
      {
         return lang(stra[0]);
      }
      else
      {
         return strLang;
      }
   }
}

string  tts_lang(string strLang)
{

   if (strLang == "en")
   {
      return "en";
   }
   else if (strLang == "es")
   {
      return "es";
   }
   else if (strLang == "pt")
   {
      return "pt";
   }
   else if (strLang == "ru")
   {
      return "ru";
   }
   else if (strLang == "fr")
   {
      return "fr";
   }
   else if (strLang == "it")
   {
      return "it";
   }
   else if (strLang == "de")
   {
      return "de";
   }
   else if (strLang == "jp")
   {
      return "jp";
   }
   else if (strLang == "ja")
   {
      return "jp";
   }
   else if (strLang == "pl")
   {
      return "pl";
   }
   else if (strLang == "tw")
   {
      return "tw";
   }
   else if (strLang == "cn")
   {
      return "cn";
   }
   else if (strLang == "kr")
   {
      return "kr";
   }
   else
   {
      return "en";
   }


}

string  trans_lang(string strLang)
{

   if (strLang == "en")
   {
      return "en";
   }
   else if (strLang == "es")
   {
      return "es";
   }
   else if (strLang == "pt")
   {
      return "pt";
   }
   else if (strLang == "ru")
   {
      return "ru";
   }
   else if (strLang == "fr")
   {
      return "fr";
   }
   else if (strLang == "it")
   {
      return "it";
   }
   else if (strLang == "de")
   {
      return "de";
   }
   else if (strLang == "nl")
   {
      return "nl";
   }
   else if (strLang == "ca") // catalan - (catalunha)
   {
      return "ca";
   }
   else if (strLang == "hy") // modern armenian
   {
      return "hy";
   }
   else if (strLang == "cn")
   {
      return "zh-cn";
   }
   else if (strLang == "tw")
   {
      return "zh-tw";
   }
   else if (strLang == "jp" || strLang == "ja")
   {
      return "ja";
   }
   else if (strLang == "se" || strLang == "sv")
   {
      return "sv";
   }
   else
   {
      return "en";
   }


}

string  initial_country_lang(string strCountry)
{

   if (strCountry == "br")
   {

      return "pt";

   }
   else if (strCountry == "do")
   {

      return "es";

   }
   else if (strCountry == "co")
   {

      return "es";

   }
   else if (strCountry == "pe")
   {

      return "es";

   }
   else if (strCountry == "ec")
   {

      return "es";

   }
   else if (strCountry == "mx")
   {

      return "es";

   }
   else if (strCountry == "pa")
   {

      return "es";

   }
   else if (strCountry == "py")
   {

      return "es";

   }
   else if (strCountry == "uy")
   {

      return "es";

   }
   else if (strCountry == "ar")
   {

      return "es";

   }
   else if (strCountry == "cl")
   {

      return "es";

   }
   else if (strCountry == "us")
   {

      return "en";

   }
   else if (strCountry == "ja" || strCountry == "jp")
   {

      return "jp";

   }
   else if (strCountry == "uk")
   {

      return "en";

   }
   else if (strCountry == "nl")
   {

      return "nl";

   }
   else if (strCountry == "de")
   {

      return "de";

   }
   else if (strCountry == "cn")
   {

      return "cn";

   }
   else if (strCountry == "tw")
   {

      return "tw";

   }
   else
   {

      stringa stra;

      stra.explode("-", strCountry);

      if (stra.get_count() == 2)
      {

         return stra[0];

      }
      else
      {

         return "en";

      }

   }

}
double  time_zone(string str)
{
   str.make_lower();
   //Московское время (UTC+3)
   if(str == "msk")
   {
      return 3.0;

   }
   else if(str == "brt")
   {

      return -3.0;

   }
   else if(str == "cet")
   {
      return 1.0;
   }

   else
   {
      return 1000.0; // earth?
   }
}
string glang(string strLang)
{
   if(strLang == "en")
   {
      return "en";
   }
   else if(strLang == "jp")
   {
      return "ja";
   }
   else
   {
      return lang(strLang);
   }
}
string l_and(string strLang)
{
   if (strLang == "de")
   {
      return "und";
   }
   if (strLang == "pt")
   {
      return "e";
   }
   if (strLang == "fr")
   {
      return "et";
   }
   if (strLang == "ru")
   {
      return "и";
   }
   return "and";
}
string username(string strUser, string strLang)
{
   var strName = get_user_data(strUser, "name." + strLang);
   if (strName.is_empty())
   {
      strName = get_user_data(strUser, "name");
      if (strName.is_empty())
      {
         strName = strUser;
      }
   }
   return strName;
}

void ws(string strUser) // welcome sound
{
   strUser.make_lower();
   ::file::path path = m_pcomm->get_base_path() / "audio/hidden/welcome" / strUser + ".wav";
   if (Application.file().exists(path))
   {
      Application.play_audio(path);
   }
   else
   {
      Application.play_audio(m_pcomm->get_base_path() / "audio/hidden/welcome.wav");
   }
}
void doorbell() // welcome sound
{
   Application.play_audio(m_pcomm->get_base_path() / "audio/hidden/doorbell.wav");
}
void bye() // welcome sound
{
   Application.play_audio(m_pcomm->get_base_path() / "audio/hidden/youlater.wav");
}
void auto_translate(string strUser, string strDst, string strText)
{
   olink(strUser, "https://translate.google.com.br/?hl=&ie=UTF-8&sl=en&tl=sv#auto/" + strDst + "/" + url_encode(strText));
}


void translate(string strUser, string strDst, string strSrc, string strText)
{

   olink(strUser, "https://translate.google.com.br/?hl=&ie=UTF-8&sl=en&tl=sv#" + strSrc + "/" + strDst + "/" + url_encode(strText));

}


string bot_x(string strNameParam, string strUserParam, string strText, string strCountry, string strLangParam, string strOther, string strOtherName)
{

   stringa t_straParam;

   string strSpeakText;

   string strSpeakLang = strLangParam;
   
   string strTopic;
   
   string str;
   
   string strUser = strUserParam;
   
   string strName = strNameParam;

   string strLang = strLangParam;

   string strOtherCountry;

   string strOtherLang;
   
   if (strOther.has_char() && strOther != strUser)
   {

      strOtherCountry = get_user_data(strOther, "country").get_string().lower();
      if (strOtherCountry.is_empty())
      {
         strOtherCountry = get_lctv_info(strOther, "country_code").get_string().lower();
         set_user_data(strOther, "country", strOtherCountry);
      }
      strOtherLang = lang(get_user_data(strOther, "lang").get_string().lower());
      if (strOther.is_empty())
      {
         strOtherLang = initial_country_lang(strOther);
         set_user_data(strOther, "lang", strOtherLang);
      }


      if (strOtherName.has_char())
      {

         strName = strOtherName;

      }
      else
      {

         strName = strOther;

      }

      strUser = strOther;

      strLang = strOtherLang;

      strCountry = strOtherCountry;

   }

   if (strText == "!" || strText == "exclamation" || strText == "exclamation mark")
   {
      str = _t("%name, Some supported commands !help, !about and !want the bot");
   }
   else if (strText.CompareNoCase("!cc") == 0)
   {

      strTopic = get_lctv_info(strUser, "country_code").get_string().lower();

      str = _t("The country code of %name is \"%topic\"");

   }
   else if (strText.CompareNoCase("!ws") == 0 || ::str::begins_eat_ci(strText, "!ws "))
   {
      if (strUserParam == "ca2")
      {
         ws(strOther);
      }
   }
   else if (strText.CompareNoCase("!land") == 0 || ::str::begins_eat_ci(strText, "!land "))
   {

      string strCountry;

      strName = strNameParam;

      //strLang = strLangParam;

      //strSpeakLang = strLangParam;

      if (strOtherName.has_char())
      {

         strName = strOtherName;

         strSpeakLang = strOtherLang;

      }

      if (strText.CompareNoCase("!land") == 0 || strText.CompareNoCase("!land ") == 0)
      {

         strCountry = get_lctv_info(strUser, "country").get_string().upper();

      }
      else
      {

         strName = strText;

         strCountry = get_lctv_info(strText, "country").get_string().upper();

      }

      strTopic = get_country(strLang, strCountry);

      if (strTopic.is_empty())
      {

         strTopic = get_country("en", strCountry);

      }


      if (strTopic.is_empty())
      {

         str = _t("The country of %name is unknown");

      }
      else
      {

         str = _t("The country of %name is \"%topic\"");

      }

      strUser = strUserParam;

      strName = strNameParam;

      if (strOther.has_char())
      {

         if (strOtherName.has_char())
         {

            strName = strOtherName;

         }
         else
         {

            strName = strOther;

         }

         strUser = strOther;

      }

   }
   else if (::str::begins_eat_ci(strText, "!subj "))
   {

      if (strUser == "ca2")
      {
#ifdef __XMPP
         ::xmpp::comm * pcomm = dynamic_cast <::xmpp::comm *>(m_pcomm);

         pcomm->defer_set_subject(strText);
#endif
      }

   }
   else if (strText == "!pres")
   {

#ifdef __XMPP
      ::xmpp::comm * pcomm = dynamic_cast <::xmpp::comm *>(m_pcomm);

      pcomm->defer_request_roster();
      ::fork(get_app(), [=]()
      {
         string strSpeakText;
         string str;
         pcomm->m_evRoster.wait(seconds(15));

         stringa straFiltered;

         stringa straBot;

         stringa stra;

         stra.explode("@", pcomm->m_strRoomJid);

         string strRoom;

         if (stra.get_count() > 0)
         {

            strRoom = stra[0];

         }

         stra.explode("@", pcomm->m_strJid);

         string strBot;

         ::count cGuest = 0;

         if (stra.get_count() > 0)
         {

            strBot = stra[0];

         }

         int iAddUp = 0;

         int iAddUpBot = 0;

         for (index i = 0; i < pcomm->m_straPresenceName.get_count(); i++)
         {

            string strName = pcomm->m_straPresenceName[i];

            string strJid = pcomm->m_straPresenceJid[i];

            if (strRoom.has_char() && ::str::ends_ci(strJid, "/" + strRoom))
            {
               string str1 = _t("\"myself\"");
               straFiltered.add_unique(str1);

            }
            else if (strBot.has_char() && ::str::ends_ci(strJid, "/" + strBot))
            {

               straBot.add_unique(strBot);

            }
            else
            {

               if (::str::begins_ci(strName, "guest_"))
               {

                  cGuest++;

               }
               else
               {

                  if (isbot(strName))
                  {

                     straBot.add_unique(strName);

                  }
                  else
                  {

                     straFiltered.add_unique(strName);

                  }

               }

            }

         }

         string strTopic = ::str::from(straFiltered.get_count() + cGuest);

         str = _t("%name, There are %topic online people at chat");

         straFiltered.quick_sort(NULL, NULL, true);

         if (straFiltered.get_count() <= 0)
         {

         }
         else if (cGuest > 0)
         {

            str += ":\n" + straFiltered.implode(",\n");

         }
         else if (straFiltered.get_count() == 1)
         {

            str += ":\n" + straFiltered[0] + ".";

         }
         else if (straFiltered.get_count() == 2)
         {

            str += ":\n" + straFiltered[0] + "\n"+l_and(strLang)+"\n" + straFiltered[1];

         }
         else
         {

            str += ":\n" + straFiltered.implode(",\n", 0, straFiltered.get_upper_bound()) + "\n" + l_and(strLang) + "\n" + straFiltered[straFiltered.get_upper_bound()];

         }

         if (cGuest > 0)
         {

            if (straFiltered.get_count() > 0)
            {

               str += "\n";

            }

            if (cGuest == 1)
            {

               str += _t("and one guest.");

            }
            else
            {

               strTopic = ::str::from(cGuest);

               str += _t("and %topic guests.");

            }

         }

         if (straBot.get_count() > 0)
         {

            strTopic = ::str::from(straBot.get_count());

            if (straBot.get_count() <= 0)
            {

               str += "\n" + _t("and no detected bots.");

            }
            else if (straBot.get_count() == 1)
            {

               str += "\n" + _t("and 1 detected bot");

            }
            else
            {

               str += "\n" + _t("and %topic detected bots");

            }

            if (straBot.get_count() <= 0)
            {

            }
            else if (straBot.get_count() == 1)
            {

               str += " :\n" + straBot[0] + ".";

            }
            else if (straBot.get_count() == 2)
            {

               str += " :\n" + straBot[0] + "\n" + l_and(strLang) + "\n" + straBot[1];

            }
            else
            {

               str += " :\n" + straBot.implode(",\n", 0, straBot.get_upper_bound()) + "\n" + l_and(strLang) + "\n" + straBot[straBot.get_upper_bound()];

            }

         }

         lspeak(strUser, strLang, str);
         pcomm->msg(str);
      });

#endif
   }
   else if (strText == "!live")
   {
#ifdef __XMPP

      var v;
      Application.lctv_api_get("/api/livestreams/onair/", v, "bot");

      stringa stra;

      for (auto & i : v["results"].vara())
      {
         if ((bool)i["is_live"])
         {
            stra.add(i["user__slug"]);
         }
      }
      stra.quick_sort(NULL, NULL, true);
      for (auto & user : stra)
      {
         str += user + "\n";
      }
#endif
   }
   else if(strText == "!reset!")
   {
      set_user_data(strUser,"country","");
      set_user_data(strUser,"lang","");
      set_user_data(strUser,"visit_count","");
      set_user_data(strUser,"last_visit","");
      set_user_data(strUser,"last_visit_time","");
   }
   else if(strText == "!rickroll" || strText == "!rr" || strText == "!rick") // xmetrix commanded !rickroll (me: probably he is referring to Rick Astley hit...)
   {
      if(spam(strUser))
      {
         return warn(strUser);
      }
      else
      {
         str = rr(strName, strLang);
      }
   }
   else if(strText == "!song")
   {

      strTopic = song("");

      if(strTopic.is_empty())
      {

         str = _t("%name, song not playing or not in record.");

      }
      else
      {

         str = _t("%name, currently playing song is: \"%topic\".");

      }
   }
   else if(strText == "!help")
   {

      str = _t("%name, help information is grouped in:\n!help util\n!help info\n!help config\n and\n!help media");

   }
   else if(::str::begins(strText,"!help "))
   {
      string strGroup(strText);
      var strC;
      strC = "";
      ::str::begins_eat(strGroup,"!help ");
      if(strGroup == "config")
      {

         strGroup = _t(" settings commands are:");
         str = _t("!setname \"name\"\n!setlang \"country code\"\n!cc\n!land\n!getlang\nand\n!setzone \"time zone\"");

      }
      else if(strGroup == "media")
      {

         strGroup = _t(" multimedia commands are:");
         str = _t("!rr\n!rickroll\n!say \"text\"\n!playlist\n and\n!play \"sound\"");

      }
      else if(strGroup == "util")
      {
         strGroup = _t(" some utility commands:");
         str = _t("!urbd \"urban dictionary query\"\n!at \"google auto translate\"\n and\n!t \"lang\" \"text to translate from lang\"");
      }
      else if(strGroup == "rr" || strGroup == "rickroll")
      {

         strC = _t("%name, !rr or !rickroll plays 80s hit Never Gonna Give You Up performed by Rick Astley with ASCII animation.");

      }
      else if(strGroup == "cmdtips")
      {

         strC = _t("%name, Use this command to get special tips");

      }
      else if(strGroup == "say")
      {

         strC = _t("%name, say uses Windows Narrator to speak the supplied text.");

      }
      else if(strGroup == "ide")
      {

         strC = _t("%name, ide \"platform\" display information about tools used for development of ca2 framework and apps at the specified platform. \"platform\" may be: windows (Desktop), linux, macos, ios, android and winrt.");

      }
      else if(strGroup == "setlang")
      {

         strC = _t("%name, setlang \"language code and/or two-letter country code\" sets user preferred language. The bot speaks to you in selected language, as much as possible.");

      }
      else if(strGroup == "setname")
      {

         strC = _t("%name, use setname command to set better user name, matching nick or name, with desired capitalization and spacing. It can make it better the name pronunciantion by Text-To-Speech.");

      }
      else
      {

         strGroup = _t(" information retrieval commands are:");
         str = _t("!ide \"platform\"\n!help \"command\"\n!cmdtips\n!about\n!want the bot\nand\n!credits");

      }

      if(strC.is_empty())
      {
         if(strLang == "pt")
         {
            str = strName + ", " + strGroup + "\n" + str;
         }
         else
         {
            str = strName + ", " + strGroup + "\n" + str;
         }
      }
      else
      {
         str = strC;
      }
   }
   else if(strText.CompareNoCase("!ide windows") == 0)
   {

      str = _t("%name, For Windows Desktop Software Development, ca2 uses Visual Studio 2015 Community Edition, SmartSVN, TortoiseSVN and WinMerge.");

   }
   else if(strText.CompareNoCase("!ide linux") == 0)
   {

      strTopic = "15.10";

      str = _t("%name, For Linux Software Development, ca2 uses Ubuntu %topic, Code::Blocks and SmartSVN.");

   }
   else if(strText.CompareNoCase("!ide macos") == 0)
   {

      strTopic = "El Capitan";

      str = _t("%name, At MacOS, ca2 uses Mac OS %topic, XCode and SmartSVN.");

   }
   else if(strText.CompareNoCase("!ide ios") == 0)
   {

      str = _t("%name, for iOS development, ca2 uses Mac OS X El Capitan, XCode, SmartSVN, XCode iOS simulator and trying to convince co-founder to borrow iOS device.");

   }
   else if(strText.CompareNoCase("!ide android") == 0)
   {

      str = _t("%name, for Android development, ca2 uses Windows with Hyper-V, Visual Studio 2015 Community Edition, SmartSVN, TortoiseSVN, WinMerge, Visual Studio Emulator for Android and Galaxy Tab 3 (Door Prize for co-founder, gift for me, help for ca2 developers and users).");

   }
   else if(strText.CompareNoCase("!ide winrt") == 0)
   {

      str = _t("%name, for Windows Store App development, ca2 uses Windows, Visual Studio 2015 Community Edition, SmartSVN, TortoiseSVN and WinMerge.");

   }
   else if(strText.CompareNoCase("!cmdtips") == 0)
   {

      str = _t("%name, For the exclamation mark, if an existing command is not found, an audio clip is played from !playlist. If a corresponding audio clip is not found, the text is played like in !say <text>");

   }
   else if(strText.CompareNoCase("!about") == 0)
   {

      str = _t("%name, ca2 is an all-purpose multi-platform framework and set of libraries written in C++ language to help developers create great apps for users.");

   }
   else if (strText == "!repos")
   {

      str = _t("%name, you can gain access to ca2 repos https://repos.ca2.cc basically by informally talking at chat at http://livecoding.tv/ca2 and showing interest in C++/ca2. Working e-mail address is needed. Pre-register at https://fontopus.com . Type !fontopus for details on registration.");

   }
   else if (strText == "!fontopus")
   {

      str = _t("%name, type e-mail and password at https://fontopus.com . If not registered or wrong credentials, the screen will be prompted again. Furthermore, if not registered, you will receive e-mail which should be confirmed.");

   }
   else if(strText == "!credits")
   {
      str = _t("%name presence and interest.\nxmetrix xmxstudio API.\nLivecoding.TV API and web site.\nVapaamies Russian translation.\nr00tkiller French translation.\nCatherina Cortega Dutch translation.\nfuel and andremommert German translation.\nPawel Kulesza Polish translation.\nha10word Traditional Chinese translation.");
   }
   else if(strText.get_length() > 6 && ::str::begins_eat(strText,"!urbd "))
   {
      olink(strUser,"http://www.urbandictionary.com/define.php?term=" + url_encode(strText));
   }
   else if(strText.get_length() > 4 && ::str::begins(strText,"!at "))
   {
      auto_translate(strUser,glang(strLang),strText.substr(4));
   }
   else if(strText.get_length() > 3 && ::str::begins(strText,"!t ") && strText.substr(5,1) == " ")
   {
      translate(strUser,glang(strText.substr(3,2)),glang(strLang),strText.substr(6));
   }
   else if(strText == "!getlang")
   {

      string strTopic = ::str::from(get_user_data(strUser, "lang"));

      str = _t("%name, your language is set to %topic");

   }
   else if(strText.get_length() == 11 && ::str::begins_eat(strText,"!setlang "))
   {
      strLang = lang(strText);
      set_user_data(strUser,"lang",strLang);
      strLang = get_user_data(strUser,"lang");
      strSpeakLang = strLang;
      strTopic = strLang;
      strName = username(strUser, strSpeakLang);
      str = _t("%name, your language was set to \"%topic\"");
   }
   else if (strText == "!time" || ::str::begins_eat(strText, "!time "))
   {

      ::datetime::time now = ::datetime::time::get_current_time();

      string strZoneUser = strUser;

      if (strText.has_char() && strText != "!time")
      {
         
         strZoneUser = strText;

      }

      int iZone = get_user_data(strUser, "time_zone");

      string strZone = get_user_data(strUser, "time_zone_text");

      if (strZone.is_empty())
      {

         strZone = "UTC";

         if (iZone > 0)
         {

            strZone += "+";

         }
         else
         {

            strZone += "-";

         }

         strZone += ::str::from(abs(iZone));

      }

      now += ::datetime::time_span(0, iZone, 0, 0);

      strTopic = System.datetime().international().get_gmt_date_time(now);

      if (strZoneUser != strUser)
      {

         t_straParam.add(username(strZoneUser, strLang));

         str = _t("%name, it is \"%topic\" for %param1.");

      }
      else
      {

         str = _t("%name, it is \"%topic\"");

      }

   }
   else if(::str::begins_eat(strText,"!setzone "))
   {
      var v = strText;
      if(v.is_double())
      {
         set_user_data(strUser,"time_zone",v.get_double());
         set_user_data(strUser,"time_zone_text","");

         strTopic = ::str::from(get_user_data(strUser, "time_zone"));

         str = _t("%name, your time zone was set to UTC %topic");

      }
      else
      {
         double d = time_zone(strText);
         set_user_data(strUser,"time_zone_text",strText);
         set_user_data(strUser,"time_zone",d);

         strTopic = get_user_data(strUser,"time_zone_text");

         str  = _t("%name, your time zone was set to \"%topic\".");

         if(time_zone(get_user_data(strUser,"time_zone_text")) > 900.0)
         {

            str += _t(" Actually, it is currently \"Unknown Time Zone\". Yell ca2 on this (or not).");

         }

      }

   }
   else if(strText == "!getzone")
   {
      if(get_user_data(strUser,"time_zone_text").has_char())
      {
         strTopic = "\"" + get_user_data(strUser, "time_zone_text") + "\" : UTC " + ::str::from(user_time_zone(strUser));

         str = _t("%name, your time zone is set to %topic");

      }
      else
      {
         strTopic = ::str::from(user_time_zone(strUser));

         str = _t("%name, your time zone is set to UTC %topic");
      }
   }
   else if(strText.get_length() == 14 && ::str::begins_eat(strText,"!setlang ") && strText.substr(2,1) == "-")
   {
      strLang = lang(strText);
      set_user_data(strUser,"lang",strLang);
      strLang = get_user_data(strUser,"lang");
      strSpeakLang = strLang;
      set_user_data(strUser,"lang",strLang);
      set_user_data(strUser,"country",strText.substr(3,2));

      strTopic = strLang;
      strName = username(strUser, strSpeakLang);

      str = _t("%name, your language was set to %topic");

      strTopic = ::str::from(get_user_data(strUser, "country"));

      str += _t(" and your country was set to %topic");

   }
   else if(strText == "!resetlang")
   {
      set_user_data(strUser,"lang","");
   }
   else if(strText == "!want the bot") // question by julienb16 //2015-10-09 sexta-feira 23:23
   {

      str = _t("%name, you will need Visual Studio 2015 (at least Community Edition), a SVN (Subversion) client and repository access (working e-mail address needed). Talk to Camilo for details.");

   }
   else if(strText == "!playlist")
   {
      stringa a = ls_names(m_pcomm->get_base_path() / "audio/element");
      if(a.get_count() > 0)
      {
         str = "Type !play ";
         for(int i = 0; i < a.get_upper_bound(); i++)
         {
            if(i > 0)
            {
               str += ", ";
            }
            str += a[i].make_lower();
         }
         if(a.get_count() > 1)
         {
            str += " or " + a.last().make_lower();
         }
         else if(a.get_count() == 1)
         {
            str += a[0].lower();
         }
         str += ".";
      }
      else
      {
         if(strLang == "ru")
         {

            str = "В списке воспроизведения нет файлов";

         }
         else
         {

            str = "No files in the playlist";

         }
      }
      return str;
   }
   else
   {
      stringa a = ls_names(m_pcomm->get_base_path() / "audio/element");
      str = strText.substr(1);
      bool found = false;
      int i = 0;
      for(; i < a.get_count() && !found; i++)
      {
         if(a[i].lower() == str.lower())
         {
            found = 1;
         }
      }
      if(found == 1)
      {
         play_sound(m_pcomm->get_base_path() / "audio/element" / str + ".wav");
         return "";
      }
      else
      {
         str = strText;
         if (!consider_speakable_text(strText))
         {
            str = _t("I am not going to say that phrase");
         }
         if (!lspeak(strUser, strSpeakLang, strSpeakText))
         {
            return str;
         }
         return "";
      }
   }
   if(str.is_empty())
   {
      return "";
   }
   if (!consider_speakable_text(strText))
   {
      str = _t("I am not going to say that phrase.");
   }
   if(!lspeak(strUser, strSpeakLang, strSpeakText))
   {
   }
   return str;
}

string on_bot(string strUser,string strText)
{
   string strOther;
   string strOtherName;
   string strTopic;
   stringa t_straParam;
   string strSpeakText;
   if(!strText.begins_ci("!") && !m_straSpecialCommand.contains_ci(strText))
      return "";
   string strCountry = get_user_data(strUser,"country").get_string().lower();
   if(strCountry.is_empty())
   {
      strCountry = get_lctv_info(strUser,"country_code").get_string().lower();
      set_user_data(strUser,"country",strCountry);
   }
   string strLang = lang(get_user_data(strUser,"lang").get_string().lower());
   if(strLang.is_empty())
   {
      strLang = initial_country_lang(strCountry);
      set_user_data(strUser,"lang",strLang);
   }
   string strName = username(strUser, strLang);
   if(strText.get_length() > 9 && ::str::begins(strText,"!setname "))
   {
      var str = strText.substr(9);
      if (consider_speakable_text(str))
      {
         set_user_data(strUser, "name", str);
         set_user_data(strUser, "name." + strLang, str);
      }
      else
      {
         str = _t("It is not considered reasonably speakable text.");
      }

      lspeak(strUser,strLang,str);
      return str;
   }
   else if(strText.get_length() > 5 && ::str::begins(strText,"!say "))
   {
      var str = strText.substr(5);
      if (!consider_speakable_text(strText))
      {
         str = _t("I am not going to say that phrase");
      }
      if (!lspeak(strUser, strLang, str))
      {
         return str;
      }
      return "";
   }
   else if(strText.get_length() > 6 && ::str::begins(strText,"!play "))
   {
      stringa a = ls_names(m_pcomm->get_base_path() / "audio/element");
      string str = strText.substr(6);
      str = str.trimmed();
      
      if (::str::begins_ci(str, "spotify:track:"))
      {

#ifdef WINDOWS

         call_async("Z:\\core\\time\\Win32\\basis\\app_veriwell_waven.exe", str, "X:\\core\\time\\Win32\\basis\\", SW_SHOW, false);

#else

         call_async("/xcore/stage/x86/app", "\"" + str + "\" : app=app-veriwell/waven build_number=basis version=basis locale=_std schema=_std ", "/xcore/stage/x86/", SW_SHOW, false);

#endif

      }
      else
      {

         bool found = false;
         int i = 0;
         for (; i < a.get_count() && !found; i++)
         {
            if (a[i].lower() == str.lower())
            {
               found = true;
            }
         }
         if (found)
         {
            play_sound(m_pcomm->get_base_path() / "audio/element"/ str + ".wav");
            return "";
         }
         else
         {
            if (strLang == "ru")
            {

               return "Звук \"" + str + "\" не найден. Используйте команду !playlist для получения списка доступных звуков";

            }
            else
            {

               return "\"" + str + "\" not found. Please, use !playlist command to list existing sounds.";

            }

         }
      }
   }
   stringa tokens;
   tokens.explode(" ",strText);
   if(tokens.get_count() == 1)
   {
      if(::str::begins(tokens.last(),"!@"))
      {
         strUser = tokens[0].substr(2);
         strText = "!";
      }
   }
   else
   {
      if(::str::begins(tokens.last(),"@"))
      {
         
         strOther = tokens.last().substr(1);
         
         strOtherName = username(strOther, strLang);

         string str = "";
         int i = 0;
         for(; i < tokens.get_upper_bound(); i++)
         {
            if(i > 0)
            {
               str += " ";
            }
            str += tokens[i];
         }
         strText = str;
      }
   }
   return bot_x(strName,strUser,strText,strCountry,strLang, strOther, strOtherName);
}
string on_pres(string strUser,string strType)
{
   stringa t_straParam;
   string strSpeakText;
   string strTopic;
   string strCountry = get_user_data(strUser,"country").get_string().lower();
   if(strCountry.is_empty())
   {
      strCountry = get_lctv_info(strUser,"country_code").get_string().lower();
      if (strUser == "ca2")
      {
         //strCountry = "be";
      }
      set_user_data(strUser,"country",strCountry);
   }
   string strLang = lang(get_user_data(strUser,"lang").get_string().lower());
   if(strLang.is_empty())
   {
      strLang = initial_country_lang(strCountry);
      set_user_data(strUser,"lang",strLang);
   }
   var strName = username(strUser, strLang);
   var strText;
   if(strType == "unavailable")
   {

      if(spam(strUser))
      {

         strText = _t("%name gone, uff...");

      }
      else if (isbot(strUser))
      {

         strText = _t("%name was unplugged!");

      }
      else
      {
         if(get_user_data(strUser,"visit_count") <= 4)
         {

            bye();
            strText = _t("Bye %name! :(");

         }
         else
         {


            ::datetime::time last_back;

            last_back.m_time = get_user_data(strUser, "last_back").int64();

            ::datetime::time now = ::datetime::time::get_current_time();

            set_user_data(strUser, "last_see_you", now.m_time);

            if (get_user_data(strUser, "back") == 1)
            {

               strText = _t("See you %name! :(");

               if (now.m_time - last_back.m_time > 8 * 60)  // 1 hour
               {
               
                  bye();

                  set_user_data(strUser, "back", 0);

               }
               else
               {

                  set_user_data(strUser, "back", 1);

                  return "";

               }

            }
            else
            {

               return "";

            }

         }
      }
      lspeak(strUser,strLang, strSpeakText);
      return strText;
   }
   else
   {
      if(spam(strUser))
      {
         strText = strUser + " entered!! (Subset of commands enabled).";
         return strText;
      }
      else if(isbot(strUser))
      {
         strText = strName + " you are connected!";
      }
      else
      {
         if(get_user_data(strUser,"visit_count") <= 4)
         {
            doorbell();
            strText = _t("Welcome %name! :) You can type exclamation mark and then press enter to get some help.");
            if(strCountry == "be")
            {
               strText += "\nYou can choose between \"Nederlands\", \"Deutsch\" and \"Français\" using \"!setlang nl\", \"!setlang de\" or \"!setlang fr\"";
            }
            else if(strCountry == "ch")
            {
               strText += "\nYou can choose between \"Deutsch\", \"Français\" and \"Italiano\" using \"!setlang de\", \"!setlang fr\" or \"!setlang it\"";
            }
            else if (strCountry == "ca")
            {
               strText += "\nYou can choose between \"Français\" and \"English\" using \"!setlang fr\" or \"!setlang en\"";
            }
         }
         else if(get_user_data(strUser,"last_visit") > 60 * 60 * 18 || get_user_data(strUser,"today_visit_count") <= 1)
         {
            doorbell();

            strText = _t("Hi %name! Welcome! What brings you here today?");

         }
         else
         {

            ::datetime::time last_see_you;

            last_see_you.m_time = get_user_data(strUser, "last_see_you").int64();

            ::datetime::time now = ::datetime::time::get_current_time();

            set_user_data(strUser, "last_back", now.m_time);

            if (get_user_data(strUser, "back") == 0)
            {

               strText = _t("%name is back! :)");

               if (now.m_time - last_see_you.m_time > 8 * 60)  // 1 hour
               {

                  ws(strUser);

                  set_user_data(strUser, "back", 1);

               }
               else
               {

                  set_user_data(strUser, "back", 0);

                  return "";

               }

            }
            else
            {

               return "";

            }

         }

      }

      lspeak(strUser,strLang, strSpeakText);

      return strText;

   }

}


string on_new_followers(stringa & straNew)
{

   string str;

   stringa straLang;

   string strLastLang;

   bool bSameLang = true;

   for(auto strUser : straNew)
   {

      string strLang = lang(get_user_data(strUser,"lang").get_string().lower());
      if(strLang.is_empty())
      {
         string strCountry = get_user_data(strUser,"country").get_string().lower();
         if(strCountry.is_empty())
         {
            strCountry = get_lctv_info(strUser,"country_code").get_string().lower();
            set_user_data(strUser,"country",strCountry);
         }
         strLang = initial_country_lang(strCountry);
         set_user_data(strUser,"lang",strLang);
      }

      if(strLastLang.is_empty())
      {

         strLastLang = strLang;

      }

      if(strLang.get_length() < 2 || strLastLang.get_length() < 2 || strLang.Left(2) != strLastLang.Left(2))
      {

         bSameLang = false;

      }

      if(strLang == "pt")
      {

         str += "Te dou Boas Vindas, " + strUser + "! Obrigado por seguir!";

      }
      else
      {

         str += "You're welcome, " + strUser + "! Thank you for following!";

      }

      strLastLang = strLang;

   }

   bool bMsg = true;

   if(bSameLang)
   {

      if(strLastLang == "pt")
      {
         if(straNew.get_size() > 1)
         {

            str += "\nAbrindo o Rick Roll para todos vocês novos seguidores!!\n";

         }
         else
         {

            str += "\nAbrindo o Rick Roll para você!\n";

         }
      }
      else
      {
         bMsg = false;
      }
   }
   else
   {

      bMsg = false;

   }

   if(!bMsg)
   {
      if(straNew.get_size() > 1)
      {

         str += "\nOpening Rick Roll for you all new followers!!\n";

      }
      else
      {

         str += "\nOpening Rick Roll for you!!\n";

      }

      str += rr("en");

      lspeak("","en",str);

   }
   else
   {

      str += rr(strLastLang);

      lspeak("",strLastLang,str);

   }

   return str;

}


string rr(string strName, string strLang)
{

   ::datetime::time last_rr;

   ::datetime::time now = ::datetime::time::get_current_time();

   last_rr.m_time = get_user_data("global", "last_rr");

   if (now.m_time - last_rr.m_time < 5 * 60)
   {
      
      return "";

   }

   stringa t_straParam;
   string strSpeakText;

   string strTopic;

   string str;

   str = _t("%name, Opening Rick Astley - Never Gonna Give You Up!");
#ifdef WINDOWS
   call_async("Z:\\core\\time\\Win32\\basis\\app_veriwell_waven.exe", "Y:\\bergedge\\hi5\\user\\northamerica\\us\\xmetrix\\never_gonna_give_you_up.asciimedia : dont_add_to_playlist", "X:\\core\\time\\Win32\\basis\\", SW_SHOW, false);
#else
   call_async("/xcore/stage/x86/app", "/mnt/bergedge/bergedge/hi5/user/northamerica/us/xmetrix/never_gonna_give_you_up.asciimedia : dont_add_to_playlist", "/xcore/stage/x86", SW_SHOW, false);
#endif

   set_user_data("global", "last_rr", now.m_time);

   return str;

}


string rr(string strLang)
{

   ::datetime::time last_rr;

   ::datetime::time now = ::datetime::time::get_current_time();

   last_rr.m_time = get_user_data("global", "last_rr");

   if (now.m_time - last_rr.m_time < 3 * 60)
   {

      return "";

   }
   
   stringa t_straParam;
string strSpeakText;

string strName;

string strTopic;

string str;

str = _t("Opening Rick Astley - Never Gonna Give You Up!");

#ifdef WINDOWS
   call_async("Z:\\core\\time\\Win32\\basis\\app_veriwell_waven.exe", "Y:\\bergedge\\hi5\\user\\northamerica\\us\\xmetrix\\never_gonna_give_you_up.asciimedia : dont_add_to_playlist", "X:\\core\\time\\Win32\\basis\\", SW_SHOW, false);
#else
   call_async("/xcore/stage/x86/app", "/mnt/bergedge/bergedge/hi5/user/northamerica/us/xmetrix/never_gonna_give_you_up.asciimedia : dont_add_to_playlist", "/xcore/stage/x86", SW_SHOW, false);
#endif

   set_user_data("global", "last_rr", now.m_time);

      return str;

}


#include "lib1.cpp"