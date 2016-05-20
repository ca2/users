


// remark: initial does mean "official default" is certainly a rough guess
string  initial_locality_time_zone(string strCountry, string strLocality)
{

   if (strCountry == "br")
   {

      return "brt";

   }
   else if (strCountry == "ua")
   {

      return "eest";

   }
   else if (strCountry == "us")
   {

      return "pdt";

   }
   else if (strCountry == "jp")
   {

      return "jst";

   }
   else if (strCountry == "de")
   {

      return "cest";

   }
   else if (strCountry == "fr")
   {

      return "cest";

   }
   else if (strCountry == "pt")
   {

      return "west";

   }
   else if (strCountry == "es")
   {

      return "cest";

   }
   else if (strCountry == "it")
   {

      return "cest";

   }
   else if (strCountry == "ar")
   {

      return "art";

   }
   else if (strCountry == "cl")
   {

      return "clst";

   }
   else if (strCountry == "uk")
   {

      return "bst";

   }
   else if (strCountry == "nl")
   {

      return "cest";

   }
   else if (strCountry == "cn")
   {

      return "cst";

   }
   else if (strCountry == "tw")
   {

      return "cst";

   }
   else if (strCountry == "ru")
   {

      return "msk";

   }
   else if (strCountry == "pl")
   {

      return "cest";

   }
   else if (strCountry == "am")
   {

      return "amt";

   }
   else if (strCountry == "dk")
   {

      return "cest";

   }
   else if (strCountry == "se")
   {

      return "cest";

   }
   else if (strCountry == "fi")
   {

      return "eest";

   }
   else if (strCountry == "ua")
   {

      return "eest";

   }
   else if (strCountry == "no")
   {

      return "cest";

   }
   else if (strCountry == "no")
   {

      return "cest";

   }
   else if (strCountry == "be")
   {

      return "cest";

   }
   else if (strCountry == "at")
   {

      return "cest";

   }
   else if (strCountry == "lu")
   {

      return "cest";

   }
   else if (strCountry == "li")
   {

      return "cest";

   }
   else if (strCountry == "ch")
   {

      return "cest";

   }
   else if (strCountry == "au")
   {

      return "aest";

   }
   else if (strCountry == "nz")
   {

      return "nzst";

   }
   else if (strCountry == "kr")
   {

      return "kst";

   }
   else if (strCountry == "ph")
   {

      return "pht";

   }
   else if (strCountry == "my")
   {

      return "myt";

   }
   else if (strCountry == "hk")
   {

      return "hkt";

   }
   else if (strCountry == "vn")
   {

      return "ict";

   }
   else if (strCountry == "in")
   {

      return "ist";

   }
   else
   {

      return "utc";

   }

}



double  time_zone(string str)
{
   str.make_lower();
   //Московское время (UTC+3)
   if (str == "msk")
   {

      return 3.0;

   }
   else if (str == "brt")
   {

      return -3.0;

   }
   else if (str == "cet")
   {

      return 1.0;

   }
   else if (str == "cest")
   {

      return 2.0;

   }
   else if (str == "eest")
   {

      return 3.0;

   }
   else if (str == "pdt")
   {

      return -7.0;

   }
   else if (str == "est")
   {

      return -5.0;

   }
   else if (str == "edt")
   {

      return -4.0;

   }
   else if (str == "jst")
   {

      return 9.0;

   }
   else if (str == "west")
   {

      return 1.0;

   }
   else if (str == "art")
   {

      return -3.0;

   }
   else if (str == "clst")
   {

      return -3.0;

   }
   else if (str == "bst")
   {

      return 1.0;

   }
   else if (str == "cst")
   {

      return 8.0;

   }
   else if (str == "amt")
   {

      return 4.0;

   }
   else if (str == "aest")
   {

      return 10.0;

   }
   else if (str == "nzst")
   {

      return 12.0;

   }
   else if (str == "kst")
   {

      return 9.0;

   }
   else if (str == "pht")
   {

      return 8.0;

   }
   else if (str == "myt")
   {

      return 8.0;

   }
   else if (str == "hkt")
   {

      return 8.0;

   }
   else if (str == "ict")
   {

      return 7.0;

   }
   else if (str == "utc")
   {

      return 0.0;

   }
   else if (str == "alphatime")
   {

      return -2.0;

   }
   else if (str == "ist")
   {

      return 5.5;

   }
   else
   {

      return 1000000.0; // earth?

   }

}


::datetime::time_span user_time_span(string strUser)
{

   double dUTCOffset = user_time_zone(strUser);

   return ::datetime::time_span(0, (int)dUTCOffset, (int)(fmod(fabs(dUTCOffset), 1.0) * 60.0), 0);

}

string utc_offset_string(double dUTCOffset)
{

   if (dUTCOffset == 1000000.0)
   {

      return "";

   }
   else if (dUTCOffset == 0.0)
   {

      return "UTC";

   }
   else if (utc_offset_invalid(dUTCOffset))
   {

      return "(" + str_signed(dUTCOffset) + " : invalid UTC?)";

   }
   else
   {

      string strUTCOffset;

      strUTCOffset = "UTC " + str_signed_int(dUTCOffset);

      double dMod = fmod(fabs(dUTCOffset), 1.0);

      if (dMod > 0.0)
      {

         string strMinutes;

         strMinutes.Format("%02d", (int)(60.0 * dMod));

         strUTCOffset += ":" + strMinutes;

      }

      return strUTCOffset;

   }

}


string user_time_span_text(string strUser)
{

   return utc_offset_string(user_time_zone(strUser));

}


::datetime::time user_time(string strUser)
{

   return ::datetime::time::get_current_time() + user_time_span(strUser);

}


string user_time_text(string strUser, string strLang, bool bTimeZone = false)
{

   ::datetime::time now = user_time(strUser);

   string strZone;

   if (bTimeZone)
   {

      strZone = get_user_data(strUser, "time_zone_text");

      if (strZone.has_char())
      {

         strZone.make_upper();

         strZone += " ";

      }

      strZone += user_time_span_text(strUser);

      strZone = " " + strZone;

   }

   string strSpeakText;

   return System.datetime().international().get_gmt_date_time(now, _t("%Y-%m-%d %H:%M:%S")) + strZone;

}