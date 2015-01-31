using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PassportNS;

namespace Foreign_PassportNS
{
    class ForeignPassport:Passport
    {
        public string Type { get; private set; }
        public string CountryCode { get; private set; }
        public string Nationality { get; private set; }
        public string PersonalNo { get; private set; }
        public DateTime ExpiryDate { get; private set; }
        public string Visas { get; private set; }

        public ForeignPassport(
            string type,
            string countryCode,
            string nationality,
            string personalNo, 
            DateTime expiryDate,
            string visas,
            string passportNo,
            string surname,
            string name,
            string patronymicName,
            DateTime birthDate,
            string birthPlace,
            string sex,
            string authority,
            DateTime issueDate,
            string residencePlace,
            string familyStatus="",
            string specialNotes="")
            :base( passportNo, surname, name, patronymicName,
             birthDate, birthPlace, sex, authority, issueDate,
            residencePlace,  familyStatus="",  specialNotes="")
        {
            Type = type;
            CountryCode = countryCode;
            Nationality = nationality;
            PersonalNo = personalNo;
            ExpiryDate = expiryDate;
            Visas = visas;
        }


        public void AddVisa(string visa) { Visas += "\n\t" + visa; }

        public override  void Print()
        {
            Console.WriteLine("Type: {0}", Type);
            Console.WriteLine("Country code: {0}", CountryCode);
            Console.WriteLine("Passport No: {0}", PassportNo);
            Console.WriteLine("Surname: {0}", Surname);
            Console.WriteLine("Name: {0}", Name);
            Console.WriteLine("Nationality: {0}", Nationality);
            Console.WriteLine("Date of birth: {0}", BirthDate.ToString("dd.MM.yyyy"));
            Console.WriteLine("Nationality: {0}", Nationality);
            Console.WriteLine("Personal No: {0}", PersonalNo);
            Console.WriteLine("Expiry date: {0}", ExpiryDate);
            Console.WriteLine("Visas: {0}", Visas);
            Console.WriteLine("Personal No:{0}", PersonalNo);
            Console.WriteLine("Sex: {0}", Sex); 
            Console.WriteLine("Place of birth: {0}", BirthPlace);
            Console.WriteLine("Authority: {0}", Authority);
            Console.WriteLine("Date of issue: {0}", IssueDate.ToString("dd.MM.yyyy"));
            Console.WriteLine("Date of expiry: {0}", ExpiryDate.ToString("dd.MM.yyyy"));
            Console.WriteLine("Special notes: {0}", SpecialNotes);
            Console.WriteLine("Visas: {0}", Visas);       
        }
    }
}
