using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PassportNS;
using Foreign_PassportNS;

namespace Foreign_Passport
{
    class Program
    {
        static void Main(string[] args)
        {
            ForeignPassport passport = new ForeignPassport("p", "UKR", "Ukraine", "1111111111", new DateTime(2019,1,1), "01.01.2015 Australia",
                "AA 111111", "Ivanov", "Ivan", "Ivanovych", new DateTime(1990, 1, 1), 
                "Ukraine", "male", "Ministry of Internal Affairs of Ukraine", 
                new DateTime(2006, 1,1), "01.01.2006 Odessa", "single", "blood group A");

            passport.AddVisa("15.01.2015 Canada");
            passport.AddSpecialNotes("some note");

            passport.Print();
            
        }
    }
}
