


string bot_x()
{

   string & strText = m_strText;

   string strSpeakText;

   string & strTopic = m_strTopic;

   string & strTopicUser = m_strTopicUser;
   
   string str;

   string & strUserParam = m_strUser;

   string & strNameParam = m_strName;

   string & strCountry = m_strCountry;

   string & strLangParam = m_strLang;

   string & strTimeZone = m_strTimeZone;
   
   string & strOther = m_strOther;

   string & strOtherName = m_strOtherName;

   string & strOtherCountry = m_strOtherCountry;

   string & strOtherLang = m_strOtherLang;
   
   string & strOtherTimerZone = m_strOtherTimeZone;

   string & strUser = m_strUser;
   
   string & strName = m_strName;

   string & strLang = m_strLang;

   string strLoText = lotext();

   if (
      target_info("!", false)
      || target_info("exclamation mark", false)
      || target_info("exclamation", false)
      || target_info("?", false)
      || target_info("interrogation mark", false)
      || target_info("interrogation", false)
      || target_info("enter", false)
      || target_info("question mark", false)
      || target_info("question", false))
   {
      
      defer_extra_to_vocative();
      str = _t("%name, Some supported commands !help, !about and !want the bot");

   }
   else if (about_user("cc"))
   {

      strTopic = get_user_country_code(strTopicUser);

      if (is_about_self())
      {

         str = _t("%name, your country code is set to \"%topic\"");

      }
      else
      {

         str = _t("%name, country code of %param1 is \"%topic\"");

      }

   }
   else if (about_user("ws"))
   {

      ws(strTopicUser, false);

   }
   else if (about_user("land"))
   {

      string strCountryCode = get_user_country_code(strTopicUser, true);

      strCountryCode.make_upper();

      strTopic = get_country(strCountryCode);

      if (strTopic.is_empty())
      {

         strTopic = get_country("en", strCountryCode);

      }

      if (strTopic.is_empty())
      {

         strTopic = strCountryCode;

      }

      if (is_about_self())
      {

         if (strTopic.is_empty())
         {

            str = _t("%name, your country is unknown");

         }
         else
         {

            str = _t("%name, your country is set to \"%topic\"");

         }

      }
      else
      {

         if (strTopic.is_empty())
         {

            str = _t("%name, country of %param1 is unknown");

         }
         else
         {

            str = _t("%name, country of %param1 is \"%topic\"");

         }

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

                     strName = username(strName, strLang);

                     straFiltered.add_unique(strName);

                  }

               }

            }

         }

         string & strTopic = m_strTopic;

         strTopic = ::str::from(straFiltered.get_count() + cGuest);

         str = _t("%name, There are %topic online people at chat");

         straFiltered.quick_sort(NULL, NULL, true);

         str += straFiltered._008IfImplode(" : ", ", ", " " + l_and(strLang) + " ", cGuest > 0);

         if (cGuest > 0)
         {

            if (straFiltered.get_count() > 0)
            {

               //str += "\n";
               str += " ";

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

               str += " " + _t("and no detected bots.");

            }
            else if (straBot.get_count() == 1)
            {

               str += " " + _t("and 1 detected bot");

            }
            else
            {

               str += " " + _t("and %topic detected bots");

            }

            str += straBot._008IfImplode(" : ", ", ", " " + l_and(strLang) + " ");
         }

         if (str.has_char())
         {

            Application.veripack().schedule_speech(strUser, strLang, strSpeakText, this);

         }
         else
         {

            if (!lspeak(strUser, strLang, str))
            {

            }

         }

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

      strTopic = ::str::from(stra.get_count());

      str = _t("%name, There are %topic live streams");

      if (stra.get_count() > 0)
      {

         str += " ";

         str += stra._008Implode(", ", " " + l_and(strLang) + " ");

      }

#endif
   }
   else if(strText == "!reset!")
   {
      set_user_data(strUser,"country_code","");
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
         str = rr(strName, strLang, strUser == "ca2");
      }
   }
   else if(target_info("song"))
   {

      defer_extra_to_vocative();

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
   else if(target_info("help") || target_info("hlp") || target_info("hlep"))
   {
      
      string strGroup;

      stringa stra;

      stra.add_tokens(m_strExtra, " ", false);

      if (stra.get_count() >= 1)
      {

         strGroup = stra[0];

      }
      
      strGroup.make_lower();
      
      var strC;
      
      strC = "";
      
      string strSpeakGroup;

      string strSpeakC;

      int iParamCount = 1;

      if(strGroup == "config")
      {

         defer_vocative(stra, iParamCount);
         strGroup = _t(" settings commands are:");
         strSpeakGroup = strGroup;
         str = _t("!setname \"name\"\n!setlang \"country code\"\n!cc\n!land\n!getlang\nand\n!setzone \"time zone\"");

      }
      else if(strGroup == "media")
      {

         defer_vocative(stra, iParamCount);
         strGroup = _t(" multimedia commands are:");
         strSpeakGroup = strSpeakText;
         str = _t("!rr\n!rickroll\n!say \"text\"\n!playlist\n and\n!play \"sound\"");

      }
      else if(strGroup == "util")
      {
         defer_vocative(stra, iParamCount);
         strGroup = _t(" some utility commands:");
         strSpeakGroup = strSpeakText;
         str = _t("!urbd \"urban dictionary query\"\n!at \"google auto translate\"\n and\n!t \"lang\" \"text to translate from lang\"");
      }
      else if(strGroup == "rr" || strGroup == "rickroll")
      {

         defer_vocative(stra, iParamCount);
         strC = _t("%name, !rr or !rickroll plays 80s hit Never Gonna Give You Up performed by Rick Astley with ASCII animation.");
         strSpeakC = strSpeakText;

      }
      else if(strGroup == "cmdtips")
      {

         defer_vocative(stra, iParamCount);
         strC = _t("%name, Use this command to get special tips");
         strSpeakC = strSpeakText;

      }
      else if(strGroup == "say")
      {

         defer_vocative(stra, iParamCount);
         strC = _t("%name, say uses Windows Narrator to speak the supplied text.");
         strSpeakC = strSpeakText;

      }
      else if(strGroup == "ide")
      {

         defer_vocative(stra, iParamCount);
         strC = _t("%name, ide \"platform\" display information about tools used for development of ca2 framework and apps at the specified platform. \"platform\" may be: windows (Desktop), linux, macos, ios, android and winrt.");
         strSpeakC = strSpeakText;

      }
      else if(strGroup == "setlang")
      {

         defer_vocative(stra, iParamCount);
         strC = _t("%name, setlang \"language code and/or two-letter country code\" sets user preferred language. The bot speaks to you in selected language, as much as possible.");
         strSpeakC = strSpeakText;

      }
      else if(strGroup == "setname")
      {

         defer_vocative(stra, iParamCount);
         strC = _t("%name, use setname command to set better user name, matching nick or name, with desired capitalization and spacing. It can make it better the name pronunciantion by Text-To-Speech.");
         strSpeakC = strSpeakText;

      }
      else if(strGroup == "info")
      {

         defer_vocative(stra, iParamCount);
         strGroup = _t(" information retrieval commands are:");
         strSpeakGroup = strSpeakText;
         str = _t("!ide \"platform\"\n!help \"command\"\n!cmdtips\n!about\n!want the bot\nand\n!credits");

      }
      else
      {

         defer_extra_to_vocative();
         strC = _t("%name, help information is grouped in:\n!help util\n!help info\n!help config\n and\n!help media");
         strSpeakC = strSpeakText;

      }


      if(strC.is_empty())
      {
      
         str = name() + ", " + strGroup + "\n" + str;

         strSpeakText = name() + ", " + strSpeakGroup + "\n" + strSpeakText;

      }
      else
      {

         str = strC;

         strSpeakText = strSpeakC;

      }

   }
   else if(target_info("ide"))
   {
      
      string strGroup;
      
      stringa stra;
      
      stra.add_tokens(m_strExtra, " ", false);
      
      if (stra.get_count() >= 1)
      {
         
         strGroup = stra[0];
         
      }
      
      strGroup.make_lower();
      
      int iParamCount = 1;
      
      if(strGroup == "windows")
      {
         
         defer_vocative(stra, iParamCount);
         
         str = _t("%name, For Windows Desktop Software Development, ca2 uses Visual Studio 2015 Community Edition, SmartSVN, TortoiseSVN and WinMerge.");
         
      }
      else if(strGroup == "linux")
      {

         strTopic = "16.04";
         
         defer_vocative(stra, iParamCount);

         str = _t("%name, For Linux Software Development, ca2 uses Ubuntu %topic, Code::Blocks and SmartSVN.");

      }
      else if(strGroup == "macos")
      {

         strTopic = "El Capitan";

         defer_vocative(stra, iParamCount);
      
         str = _t("%name, At MacOS, ca2 uses Mac OS %topic, XCode and SmartSVN.");

      }
      else if(strGroup == "ios")
      {

         defer_vocative(stra, iParamCount);
         
         str = _t("%name, for iOS development, ca2 uses Mac OS X El Capitan, XCode, SmartSVN, XCode iOS simulator and trying to convince co-founder to borrow iOS device.");

      }
      else if(strGroup == "android")
      {
         
         defer_vocative(stra, iParamCount);
         
         str = _t("%name, for Android development, ca2 uses Windows with Hyper-V, Visual Studio 2015 Community Edition, SmartSVN, TortoiseSVN, WinMerge, Visual Studio Emulator for Android and Galaxy Tab 3 (Door Prize for co-founder, gift for me, help for ca2 developers and users).");

      }
      else if(strGroup == "winrt")
      {

         defer_vocative(stra, iParamCount);
      
         str = _t("%name, for Windows Store App development, ca2 uses Windows, Visual Studio 2015 Community Edition, SmartSVN, TortoiseSVN and WinMerge.");
         
      }
      else
      {
         
         defer_extra_to_vocative();
         
         str = _t("%name, ide \"platform\" display information about tools used for development of ca2 framework and apps at the specified platform. \"platform\" may be: windows (Desktop), linux, macos, ios, android and winrt.");
         
      }

   }
   else if(target_info("cmdtips"))
   {
      
      defer_extra_to_vocative();

      str = _t("%name, For the exclamation mark, if an existing command is not found, an audio clip is played from !playlist. If a corresponding audio clip is not found, the text is played like in !say <text>");

   }
   else if(target_info("about"))
   {
       
      defer_extra_to_vocative();

      str = _t("%name, ca2 is an all-purpose multi-platform framework and set of libraries written in C++ language to help developers create great apps for users.");

   }
   else if (strText == "!repos")
   {

      str = _t("%name, you can gain access to ca2 repos https://repos.ca2.cc basically by informally talking at chat at http://livecoding.tv/ca2 and showing interest in C++/ca2. Working e-mail address is needed. Pre-register at https://account.ca2.cc . Type !account for details on registration.");

   }
   else if (strText == "!account")
   {

      str = _t("%name, type e-mail and password at https://account.ca2.cc . If not registered or wrong credentials, the screen will be prompted again. Furthermore, if not registered, you will receive e-mail which should be confirmed.");

   }
   else if(strText == "!credits")
   {
      str = _t("%name presence and interest.\nxmetrix xmxstudio API.\nLivecoding.TV API and web site.\nVapaamies Russian translation.\nr00tkiller French translation.\nCatherina Cortega Dutch translation.\nfuel and andremommert German translation.\nPawel Kulesza Polish translation.\nha10word Traditional Chinese translation.");
   }
   else if(strText.get_length() > 6 && ::str::begins_eat(strText,"!urbd "))
   {
      olink(strUser,"http://www.urbandictionary.com/define.php?term=" + url_encode(strText));
   }
   else if (strText.get_length() > 7 && ::str::begins_eat(strText, "!urban "))
   {
      olink(strUser, "http://www.urbandictionary.com/define.php?term=" + url_encode(strText));
   }
   else if(strText.get_length() > 4 && ::str::begins(strText,"!at "))
   {
      auto_translate(strUser,glang(strLang),strText.substr(4));
   }
   else if(strText.get_length() > 3 && ::str::begins(strText,"!t ") && strText.substr(5,1) == " ")
   {
      translate(strUser,glang(strText.substr(3,2)),glang(strLang),strText.substr(6));
   }
   else if (strText.CompareNoCase("!lctv") == 0)
   {
      lctv_profile(strUserParam, strUser);
   }
   else if (::str::begins_eat_ci(strText, "!lctv "))
   {
      lctv_profile(strUserParam, strText);
   }
   else if(about_user("getlang"))
   {

      strTopic = get_user_lang(strTopicUser);

      if (is_about_self())
      {

         str = _t("%name, your language is set to %topic");

      }
      else
      {

         str = _t("%name, language of %param1 is set to %topic");

      }

   }
   else if(strText.get_length() == 11 && ::str::begins_eat(strText,"!setlang "))
   {
      strLang = lang(strText);
      set_user_data(strUser,"lang",strLang);
      strLang = get_user_lang(strUser);
      strTopic = strLang;
      strName = username(strUser, m_strLang);
      str = _t("%name, your language was set to \"%topic\"");
   }
   else if (::str::begins_eat(strText, "!timer "))
   {
      stringa stra;
      stra.explode(":", strText);
      if (stra.get_size() < 2)
         stra.insert_at(0, "timer");
      set_user_timer(strName, stra[0], stra[1], strLang);
   }
   else if (::str::begins_eat(strText, "!weather"))
   {
#ifdef WINDOWS
#include "C:\\sensitive\\sensitive\\seed\\openweather.txt"
      property_set set;
      set["raw_http"] = true;
      str = Application.http().get("http://api.openweathermap.org/data/2.5/weather?q=Curitiba,br&APPID=" + string(pszId), set);
#endif
   }
   else if (about_user("time"))
   {

      strTopic = user_time_text(strTopicUser, m_strLang);

      if (is_about_self())
      {

         str = _t("%name, it is \"%topic\"");

      }
      else
      {

         str = _t("%name, it is \"%topic\" for %param1.");

      }

   }
   else if(::str::begins_eat(strText,"!setzone "))
   {
      
      var v = strText;

      double dUTCOffset;

      if(v.is_double())
      {

         dUTCOffset = v.get_double();

         set_user_data(strUser,"time_zone", dUTCOffset);

         set_user_data(strUser,"time_zone_text","");

         strTopic = ::str::from(get_user_data(strUser, "time_zone"));

         str = _t("%name, your time zone was set to UTC %topic");

      }
      else
      {
         
         dUTCOffset = time_zone(strText);

         set_user_data(strUser, "time_zone", dUTCOffset);

         set_user_data(strUser, "time_zone_text", strText);

         strTopic = get_user_data(strUser, "time_zone_text");

         strTopic.make_upper();

         str = _t("%name, your time zone was set to %topic.");

         if (dUTCOffset == 1000000.0)
         {

            str += _t(" It is unknown time zone. Warn streamer about this.");

         }

      }

   }
   else if(about_user("getzone"))
   {

      double dUTCOffset = user_time_zone(strTopicUser);

      strTopic = utc_offset_string(dUTCOffset);

      if(get_user_data(strUser,"time_zone_text").has_char() && get_user_data(strTopicUser, "time_zone_text").get_string().upper().CompareNoCase(strTopic) != 0)
      {

         strTopic = get_user_data(strTopicUser, "time_zone_text").get_string().upper() + " " + strTopic;

      }

      if (is_about_self())
      {

         str = _t("%name, your time zone is set to %topic");

      }
      else
      {

         str = _t("%name, %param1 time zone is set to %topic");

      }

      if (dUTCOffset == 1000000.0)
      {

         str += _t(" It is unknown time zone. Warn streamer about this.");

      }

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
      string strServer = System.url().get_server(str);
      strsize iFind1 = -1;
      if ((iFind1 = strServer.find_ci("spotify.")) == 0
         || (iFind1 = strServer.find_ci(".spotify.")) > 0)
      {

         strsize iFind = str.find_ci("/track/", iFind1);
         if (iFind > 0)
         {
            string strId = str.Mid(iFind + strlen("/track/"));
            str = "spotify:track:" + strId;
         }

      }
      if (::str::begins_ci(str, "spotify:track:"))
      {

#ifdef WINDOWS

         call_async("C:\\core\\time\\Win32\\basis\\app_veriwell_waven.exe", str, "C:\\core\\time\\Win32\\basis\\", SW_SHOW, false);

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
            if (!lspeak(strUser, m_strLang, strSpeakText))
            {
               return str;
            }
            return "";
         }
      }
   }
   if(str.is_empty())
   {
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

      Application.veripack().schedule_speech(strUser, m_strLang, strSpeakText, this);

      m_pcomm->msg(str);

   }
   else if(strSpeakText.has_char())
   {
      
      if (!lspeak(strUser, m_strLang, strSpeakText))
      {

      }

   }

   return "";

}



