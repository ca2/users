


bool is_exclamation(string str)
{

   if (plugin::is_exclamation(str))
      return true;

   if (::str::find_ci("wtf", str) >= 0)
      return true;

   if (::str::find_ci("fuck", str) >= 0)
      return true;

   if (::str::find_ci("fck", str) >= 0)
      return true;

   if (::str::find_ci("**", str) >= 1)
      return true;

   return false;

}




bool is_vowel(string str)
{

   str = ::str::to_lower(str);

   if (str == "å")
      return true;
   if (str == "a")
      return true;
   if (str == "á")
      return true;
   if (str == "à")
      return true;
   if (str == "â")
      return true;
   if (str == "ã")
      return true;
   if (str == "ä")
      return true;
   if (str == "e")
      return true;
   if (str == "é")
      return true;
   if (str == "è")
      return true;
   if (str == "ë")
      return true;
   if (str == "ê")
      return true;
   if (str == "i")
      return true;
   if (str == "ì")
      return true;
   if (str == "í")
      return true;
   if (str == "o")
      return true;
   if (str == "õ")
      return true;
   if (str == "ó")
      return true;
   if (str == "ò")
      return true;
   if (str == "u")
      return true;
   if (str == "ę")
      return true;
   if (str == "ę")
      return true;
   if (str == "ą")
      return true;
   if (str == "y")
      return true;
   return false;

}

bool is_consonant(string str)
{

   if (str == "ç")
   {
      return true;
   }
   if (str == "ń")
   {
      return true;
   }

   if (str.get_length() != 1)
   {

      return false;

   }

   if (!isalpha(str[0]))
   {
      return false;
   }

   if (is_vowel(str[0]))
   {
      return false;
   }

   return true;

}


bool consider_speakable_text(string strText)
{

   string str;
   string str1;
   string str2;
   string str3;
   string str4;
   string str5;
   string str6;
   string str7;
   string str8;

   int iMax4Vowel = 3;
   int iMax5pVowel = 1;
   int iMax8Consonant = 1;
   int iv5p = 0;
   int iv4 = 0;
   int ic8 = 0;

   {

      stringa stra;
      stra.add("vagina");
      stra.add("penis");
      stra.add("bitch");
      int iFind;
      for (auto str : stra)
      {
         iFind = strText.find_ci(str);
         if (iFind >= 0)
         {
            return false;
         }
      }
   }

   {

      stringa stra;

      stra.add("shit");
      stra.add("cock");
      stra.add("dick");
      stra.add("cum");
      stra.add("anal");
      stra.add("cum");
      stra.add("fuck");
      int iFind;
      for (auto str : stra)
      {
         iFind = 0;
         if (str.CompareNoCase(strText.trimmed()) == 0)
         {
            return false;
         }
         while (true)
         {
            iFind = strText.find_ci(str, iFind);
            if (iFind < 0)
            {
               break;
            }
            if (iFind == 0)
            {
               if (!isalpha(strText[iFind + str.get_length()]))
               {
                  return false;
               }
            }
            else if (iFind == strText.get_length() - str.get_length())
            {
               if (!isalpha(strText[iFind - 1]))
               {
                  return false;
               }
            }
            else if (!isalpha(strText[iFind - 1]) && !isalpha(strText[iFind + str.get_length()]))
            {

               return false;
            }
            iFind += str.get_length();
         }
      }
   }

   if (strText.get_length() < 12)
   {
      return true;
   }


   int i = 0;
   const char * psz = strText;
   while (true)
   {

      str = ::str::get_utf8_char(psz);
      if (str.is_empty())
         break;
      psz += str.get_length();

      if (i == 0)
      {
         str1 = str;
      }
      else if (i == 1)
      {
         str2 = str;
      }
      else if (i == 2)
      {
         str3 = str;
      }
      else if (i == 3)
      {
         str4 = str;
      }
      else if (i == 4)
      {
         str5 = str;
      }
      else if (i == 5)
      {
         str6 = str;
      }
      else if (i == 6)
      {
         str7 = str;
      }
      else if (i == 7)
      {
         str8 = str;
      }
      else
      {

         if (is_vowel(str1) && is_vowel(str2) && is_vowel(str3) && is_vowel(str4) && is_vowel(str5))
         {
            iv5p++;
            if (iv5p >= iMax5pVowel)
            {
               return false;
            }
         }
         else if (is_vowel(str1) && is_vowel(str2) && is_vowel(str3) && is_vowel(str4))
         {
            iv4++;
            if (iv4 >= iMax4Vowel)
            {
               return false;
            }
         }
         else if (is_consonant(str1) && is_consonant(str2) && is_consonant(str3) && is_consonant(str4) && is_consonant(str5) && is_consonant(str6) && is_consonant(str7) && is_consonant(str8))
         {
            ic8++;
            if (ic8 >= iMax8Consonant)
            {
               return false;
            }
         }


         str1 = str2;
         str2 = str3;
         str3 = str4;
         str4 = str5;
         str5 = str6;
         str6 = str;
      }
      i++;
   }

   return true;
}


void audio_announce(string strParam)
{

#ifdef WINDOWS
call_async("C:\\core\\time\\Win32\\basis\\app_veriwell_waven.exe", strParam +  " : dont_add_to_playlist", "C:\\core\\time\\Win32\\basis\\", SW_SHOW, false);

#elif defined(MACOS)

//string strPath = file_as_string_dup(::file::path(“HOME”) / “.ca2/mypath/app-core/Waven”);

::system("/Applications/Waven.app/Contents/MacOS/Waven \""+strParam+"\" : dont_add_to_playlist");

#else
call_async("/xcore/stage/x86/app", strParam + " :  app=app-veriwell/waven build_number=basis locale=_std schema=_std dont_add_to_playlist", "/xcore/stage/x86", SW_SHOW, false);
#endif

}

::file::path bergedge()
{

#ifdef WINDOWS
   return "C:\\bergedge";
#else
   return "/bergedge";
#endif

}

::file::path hi5()
{
   return bergedge() / "hi5";
}

::file::path hi5_user(string strUser)
{
   if (strUser == "xmetrix")
   {
      return hi5() / "user/northamerica/us/xmetrix";
   }
   else
   {
      return "";
   }
}




double user_time_zone(string strUser)
{

   var time_zone_text = get_user_data(strUser, "time_zone_text");

   if (time_zone_text.has_char())
   {

      return time_zone(time_zone_text);

   }
   else
   {

      return get_user_time_zone(strUser);

   }

}



bool set_user_timer(string strName, string strTitle, string strSpec, string strLang)
{
#ifdef WINDOWS
   call_async("C:\\core\\time\\x64\\basis\\app_core_timer.exe", "\"timer://device/"+strSpec+"?user="+System.url().url_encode(strName)+"&title="+System.url().url_encode(strTitle)+"&lang="+System.url().url_encode(strLang)+"&autoclose=1\"", "C:\\core\\time\\x64\\basis\\", SW_SHOW, false);
#else
   call_async("/xcore/stage/x86/app", "\"timer://device/"+strSpec+"?user="+System.url().url_encode(strName)+"&title="+System.url().url_encode(strTitle)+"&lang="+System.url().url_encode(strLang)+"&autoclose=1\" : app=app-core/timer build_number=basis locale=_std schema=_std", "/xcore/stage/x86", SW_SHOW, false);
#endif
   return true;
}




void olink(string strUser, string strUrl)
{
   if (spam(strUser))
   {
   }
   else
   {
      open_link(strUrl);
   }
}



string str_signed(double d)
{

   if (d > 0.0)
   {

      return "+" + ::str::from(d);

   }
   else if (d < 0.0)
   {

      return ::str::from(d);

   }
   else
   {

      return "0.0";

   }

}

string str_signed_int(int i)
{

   if (i > 0)
   {

      return "+" + ::str::from(i);

   }
   else if (i < 0)
   {

      return ::str::from(i);

   }
   else
   {

      return "0";

   }

}


bool utc_offset_invalid(double dUTCOffset)
{

   return dUTCOffset < -12.0 || dUTCOffset > 14.0;  // don't know (is invalid?)

}





void auto_translate(string strUser, string strDst, string strText)
{
   olink(strUser, "https://translate.google.com.br/?hl=&ie=UTF-8&sl=en&tl=sv#auto/" + strDst + "/" + url_encode(strText));
}


void translate(string strUser, string strDst, string strSrc, string strText)
{

   olink(strUser, "https://translate.google.com.br/?hl=&ie=UTF-8&sl=en&tl=sv#" + strSrc + "/" + strDst + "/" + url_encode(strText));

}

void lctv_profile(string strUser, string strProfile)
{
   olink(strUser, "https://www.livecoding.tv/" + strProfile + "/");
}




string lotext(string strText)
{
   
   return strText.lower();

}


string lotext()
{

   return lotext(m_strText);

}



bool third_info(string strQuery, bool bPrefix = true)
{

   string strText = m_strText;

   string strQuery1 = "!" + strQuery;

   string strQuery2 = "!" + strQuery;

   if (strText.CompareNoCase(strQuery1) == 0 || ::str::begins_eat_ci(strText, strQuery1 + " ")
      || strText.CompareNoCase(strQuery2) == 0 || ::str::begins_eat_ci(strText, strQuery2 + " ")
      || (!bPrefix && (strText.CompareNoCase(strQuery) == 0 || ::str::begins_eat_ci(strText, strQuery + " "))))
   {

      if (strText.CompareNoCase(strQuery1) == 0
         || strText.CompareNoCase(strQuery2) == 0
         || (!bPrefix && strText.CompareNoCase(strQuery) == 0))
      {

         strText.Empty();

      }

      m_strExtra = strText;

      if (strText == m_strUser || m_strUser == m_strOther || (m_strOther.is_empty() && strText.is_empty()))
      {

         m_epersonVocative = ::vericard::person_user;

         //m_strTopicUser = m_strUser;

      }
      else
      {



         if (strText.has_char())
         {

            //m_strTopicUser = strText;

            m_strOtherName = strText;

         }
         else if (m_strOther.has_char())
         {

            m_strOtherLang = get_user_lang(m_strOther);

            m_strOtherName = username(m_strOther, m_strOtherLang);

            //   m_strTopicUser = m_strOther;

         }

         //param1_topic_username();

      }

      return true;

   }
   else
   {

      return false;

   }

}




