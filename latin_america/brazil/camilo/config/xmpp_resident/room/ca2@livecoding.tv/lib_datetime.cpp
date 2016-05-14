


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

