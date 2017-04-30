string rr(string strName, string strLang, bool bForce = false)
{

   ::datetime::time now;

   if (!bForce)
   {

      ::datetime::time last_rr;

      now = ::datetime::time::get_current_time();

      last_rr.m_time = get_user_data("global", "last_rr").int64();

      if (now.m_time - last_rr.m_time < 1 * 60)
      {

         return "";

      }

   }

   string strSpeakText;

   string & strTopic = m_strTopic;

   strTopic = strName;

   string str;

   str = _t("%topic, Opening Rick Astley - Never Gonna Give You Up!");

   audio_announce(hi5_user("xmetrix") / "Never Gonna Give You Up.asciimedia");

   if (!bForce)
   {

      set_user_data("global", "last_rr", now.m_time);

   }

   return str;

}


string rr(string strLang, bool bForce = false)
{

   ::datetime::time now;

   if (!bForce)
   {

      ::datetime::time last_rr;

      now = ::datetime::time::get_current_time();

      last_rr.m_time = get_user_data("global", "last_rr").int64();

      if (now.m_time - last_rr.m_time < 1 * 60)
      {

         return "";

      }

   }

   string strSpeakText;

   string & strTopic = m_strTopic;

   string str;

   str = _t("Opening Rick Astley - Never Gonna Give You Up!");

   audio_announce(hi5_user("xmetrix") / "Never Gonna Give You Up.asciimedia");

   if (!bForce)
   {

      set_user_data("global", "last_rr", now.m_time);

   }

   return str;

}



stringa wsa(string strUser)
{

   stringa stra;

   ::file::path path;

   index iIndex = 0;

   while (Application.file().exists(path = ::dir::system() / ("audio/hidden/welcome" + ::str::from(iIndex++)) / (strUser + ".wav")))
   {
      stra.add(path);
   }

   return stra;

}

void ws(string strUser, bool bDoorBel, bool bHosts = false) // welcome sound
{

   auto puser = get_user(strUser, true);

   puser->get_user_country_code();

   string strUsername = username(strUser, m_epersonVocative == ::vericard::person_user ? m_strLang : m_strOtherLang);

   spa(::vericard::user) usera;

   usera.add(puser);

   Application.veripack().add_announce("Welcome " + strUsername + "!", usera, 10000);

   strUser.make_lower();

   stringa stra = wsa(strUser);

   if (stra.get_size() > 0)
   {

      index iIndex = atoi(file_as_string_dup(::dir::system() / "audio/hidden/welcome0" / strUser + ".txt"));

      if (iIndex >= stra.get_size())
      {

         iIndex = 0;

      }

      audio_announce(stra[iIndex], strUsername, puser != NULL ? puser->m_strImage : "");

      iIndex++;

      file_put_contents_dup(::dir::system() / "audio/hidden/welcome0" / strUser + ".txt", ::str::from(iIndex));

   }
   else if (bHosts)
   {

      hostsbell();

   }
   else if (bDoorBel)
   {

      doorbell();

   }
   else
   {

      Application.play_audio(::dir::system() / "audio/hidden/welcome.wav");

   }

}


void doorbell() // welcome sound
{

   Application.play_audio(::dir::system() / "audio/hidden/doorbell.mp3");

}

void hostsbell() // welcome sound
{

   Application.play_audio(::dir::system() / "audio/hidden/hostsbell.mp3");

}

void bye() // welcome sound
{
   Application.play_audio(::dir::system() / "audio/hidden/youlater.wav");
}
void sound_for_follower() // welcome sound
{
   ::fork(get_app(), [this]()
   {

      Application.play_audio(::dir::system() / "audio/hidden/follower.wav");

      Sleep(1000);

      Application.play_audio(::dir::system() / "audio/hidden/follower.wav");

      Sleep(1000);

      Application.play_audio(::dir::system() / "audio/hidden/follower.wav");

      
   });

   
}




void audio_announce(string strParam, string strTitle = "", string strAlbumArt = "", bool bIgnorePlaybackNotification = true)
{

   if (bIgnorePlaybackNotification)
   {

      ::file::path pathOrigin(strParam);

      Application.veripack().m_pathaIgnorePlaybackNotification.add(pathOrigin);

   }

   if (strTitle.has_char())
   {

      strTitle = " call_title=\"" + strTitle + "\"";

   }

   if (strAlbumArt.has_char())
   {

      strAlbumArt = " call_albumart=\"" + strAlbumArt + "\"";

   }

#ifdef WINDOWS
   call_async("C:\\core\\time\\Win32\\basis\\app_veriwell_waven.exe", "\"" + strParam + "\" : dont_add_to_playlist play_now" + strTitle + strAlbumArt, "C:\\core\\time\\Win32\\basis\\", SW_SHOW, false);

#elif defined(MACOS)

   //string strPath = file_as_string_dup(::file::path(“HOME”) / “.ca2/mypath/app-core/Waven”);

   ::system("/Applications/Waven.app/Contents/MacOS/Waven \"" + strParam + "\" : dont_add_to_playlist" + strTitle + strAlbumArt);

#else
   call_async("/xcore/time/x64/basis/app", "\"" + strParam + "\" :  app=app-veriwell/waven build_number=basis locale=_std schema=_std dont_add_to_playlist" + strTitle + strAlbumArt, "/xcore/time/x64/basis", SW_SHOW, false);
#endif

}
