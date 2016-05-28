string  lang(string strLang)
{
   if (strLang == "br")
   {
      return "pt";
   }
   else if (strLang == "do")
   {
      return "es";
   }
   else if (strLang == "co")
   {
      return "es";
   }
   else if (strLang == "pe")
   {
      return "es";
   }
   else if (strLang == "ec")
   {
      return "es";
   }
   else if (strLang == "mx")
   {
      return "es";
   }
   else if (strLang == "pa")
   {
      return "es";
   }
   else if (strLang == "py")
   {
      return "es";
   }
   else if (strLang == "uy")
   {
      return "es";
   }
   else if (strLang == "ar")
   {
      return "es";
   }
   else if (strLang == "cl")
   {
      return "es";
   }
   else if (strLang == "us")
   {
      return "en";
   }
   else if (strLang == "ja")
   {
      return "jp";
   }
   else if (strLang == "uk")
   {
      return "en-uk";
   }
   else if (strLang == "en-uk")
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
   else if (strLang == "si" || strLang == "sl")
   {
      return "sl";
   }
   else
   {
      stringa stra;
      stra.explode("-", strLang);
      if (stra.get_count() == 2)
      {
         return lang(stra[0]);
      }
      else
      {
         return strLang;
      }
   }
}



bool _load_text(string strLang)
{

   auto & m = m_text[strLang];

   ::file::path path = ::dir::system() / "config/xmpp_resident/room/ca2@livecoding.tv/xmpp_resident_po" / strLang + ".po";

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

   for (index i = 0; i < stra.get_count(); i++)
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
   else if (strLang == "dk" || strLang == "da")
   {
      return "da";
   }
   else if (strLang == "si" || strLang == "sl")
   {
      return "sl";
   }
   else if (strLang == "sk")
   {
      return "sk";
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
   else if (strCountry == "ru")
   {

      return "ru";

   }
   else if (strCountry == "pl")
   {

      return "pl";

   }
   else if (strCountry == "am")
   {

      return "hy";

   }
   else if (strCountry == "dk")
   {

      return "dk";

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



bool enable_tts(string strLang)
{

#if defined(LINUX) || defined(MACOS)
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


string glang(string strLang)
{
   if (strLang == "en")
   {
      return "en";
   }
   else if (strLang == "jp")
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


string welcome_time(string & strSpeakText)
{

   string & strTopic = m_strTopic;
   stringa & straParam = m_straParam;
   string strUser = m_epersonVocative == ::vericard::person_user ? m_strUser : m_strUser;
   string strLang = m_epersonVocative == ::vericard::person_user ? m_strLang : m_strOtherLang;
   string strName = m_epersonVocative == ::vericard::person_user ? m_strName : m_strOtherName;



   ::datetime::time now = user_time(strUser);
      
   if (now.GetGmtHour() >= 6 && now.GetGmtHour() < 12)
   {

      return _t("Good Morning!");

   }
   else if (now.GetGmtHour() >= 12 && now.GetGmtHour() < 18)
   {

      return _t("Good Afternoon!");

   }
   else
   {

      return _t("Good Evening!");

   }





}

string name_welcome_time( string & strSpeakText)
{


   string & strTopic = m_strTopic;
   stringa & straParam = m_straParam;
   string strUser = m_epersonVocative == ::vericard::person_user ? m_strUser : m_strUser;
   string strLang = m_epersonVocative == ::vericard::person_user ? m_strLang : m_strOtherLang;
   string strName = m_epersonVocative == ::vericard::person_user ? m_strName : m_strOtherName;


   ::datetime::time now = ::datetime::time::get_current_time();

   string strZoneUser = strUser;

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



   if (now.GetGmtHour() >= 6 && now.GetGmtHour() < 12)
   {

      return _t("%name, Good Morning!");

   }
   else if (now.GetGmtHour() >= 12 && now.GetGmtHour() < 18)
   {

      return _t("%name, Good Afternoon!");

   }
   else
   {

      return _t("%name, Good Evening!");

   }


}

string get_country(string strLang, string strCountry)
{

   strLang.make_upper();

   strCountry.make_upper();

   ::file::path path = ::dir::system() / "config/xmpp_resident/room/ca2@livecoding.tv/xmpp_resident_country" / strLang + ".json";

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

   if (p->m_element2[strId].is_empty())
      return strId;
   else
      return p->m_element2[strId];

}

string get_text(string & strSpeakText, string strId)
{

   stringa straParam = m_straParam;
   string strTopic = m_strTopic;
   string strLang = m_epersonVocative == ::vericard::person_user ? m_strLang : m_strOtherLang;
   string strName = m_epersonVocative == ::vericard::person_user ? m_strName : m_strOtherName;

   string strText = _get_text(strLang, strId);

   string strNewSpeakText;

   strNewSpeakText = strText;

   strNewSpeakText.replace("($name)", "");
   strNewSpeakText.replace("$name", "");
   strNewSpeakText = process_text(strNewSpeakText, strName, strTopic, straParam);

   if (strLang == "en" || strLang == "pt" || strLang == "de" || strLang == "nl")
   {
      strNewSpeakText.replace(":)", "");
      strNewSpeakText.replace(":(", "");
   }

   strSpeakText = strNewSpeakText;

   strText.replace("($name)", "(%name)");
   strText.replace("$name", "%name");
   return process_text(strText, strName, strTopic, straParam);

}

string process_text(string strText, string strName, string strTopic, stringa straParam)
{
   int iFind = 0;
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
            strText = straParam[i] + strText.Mid(strParamName.get_length());
         }
         // lazy check, it is not correct way of checking, it may result errors (triple %)
         else if (strText[iFind - 1] != '%')
         {
            strText = strText.Left(iFind) + straParam[i] + strText.Mid(iFind + strParamName.get_length());
         }
         iFind += straParam[i].get_length();
      }
   }
   iFind = 0;
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
      else if (strText[iFind - 1] != '%')
      {
         strText = strText.Left(iFind) + strName + strText.Mid(iFind + 5);
      }
      iFind += strName.get_length();
   }
   iFind = 0;
   while (true)
   {
      iFind = strText.find_ci("%topic", iFind);

      if (iFind < 0)
         break;

      if (iFind == 0)
      {
         strText = strTopic + strText.Mid(6);
      }
      // lazy check, it is not correct way of checking, it may result errors (triple %)
      else if (strText[iFind - 1] != '%')
      {
         strText = strText.Left(iFind) + strTopic + strText.Mid(iFind + 6);
      }
      iFind += strTopic.get_length();
   }
   return strText;
}




bool lspeak(string strUser, string strLang, string strText)
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
   if (spam(strUser))
   {
      return false;
   }
   else if (m_epersonVocative == ::vericard::person_user)
   {

      if (!enable_tts(strLang))
      {
         m_strLang = trans_lang(strLang);
         m_strSpeak = strText;
         Application.trans_speak(this);
      }
      else
      {
         m_strLang = tts_lang(strLang);
         m_strSpeak = strText;
         Application.lang_speak(this);
      }
   }
   else
   {
      if (!enable_tts(m_strOtherLang))
      {
         m_strOtherLang = trans_lang(m_strOtherLang);
         m_strSpeak = strText;
         Application.trans_speak(this);
      }
      else
      {
         m_strOtherLang = tts_lang(m_strOtherLang);
         m_strSpeak = strText;
         Application.lang_speak(this);
      }
   }
   return true;
}


string get_country(string strCountryCode)
{

   return get_country(m_epersonVocative == ::vericard::person_user ? m_strLang : m_strOtherLang, strCountryCode);

}