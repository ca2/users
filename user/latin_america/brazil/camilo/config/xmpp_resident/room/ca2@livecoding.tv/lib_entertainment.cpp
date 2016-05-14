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

   audio_announce(hi5_user("xmetrix") / "never_gonna_give_you_up.asciimedia");

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

   audio_announce(hi5_user("xmetrix") / "never_gonna_give_you_up.asciimedia");

   set_user_data("global", "last_rr", now.m_time);

   return str;

}



stringa wsa(string strUser)
{

   stringa stra;

   ::file::path path;

   index iIndex = 0;

   while (Application.file().exists(path = m_pcomm->get_base_path() / "audio/hidden/welcome" + ::str::from(iIndex++) / strUser + ".wav"))
   {
      stra.add(path);
   }

   return stra;

}

void ws(string strUser, bool bDoorBel) // welcome sound
{

   strUser.make_lower();

   stringa stra = wsa(strUser);

   if (stra.get_size() > 0)
   {

      index iIndex = atoi(file_as_string_dup(m_pcomm->get_base_path() / "audio/hidden/welcome0" / strUser + ".txt"));

      if (iIndex >= stra.get_size())
      {

         iIndex = 0;

      }

      audio_announce(stra[iIndex]);

      iIndex++;

      file_put_contents_dup(m_pcomm->get_base_path() / "audio/hidden/welcome0" / strUser + ".txt", ::str::from(iIndex));

   }
   else if (bDoorBel)
   {

      doorbell();

   }
   else
   {

      Application.play_audio(m_pcomm->get_base_path() / "audio/hidden/welcome.wav");

   }

}


void doorbell() // welcome sound
{

   Application.play_audio(m_pcomm->get_base_path() / "audio/hidden/doorbell.mp3");

}


void bye() // welcome sound
{
   Application.play_audio(m_pcomm->get_base_path() / "audio/hidden/youlater.wav");
}
void sound_for_follower() // welcome sound
{
   Application.play_audio(m_pcomm->get_base_path() / "audio/hidden/follower.wav");
}
