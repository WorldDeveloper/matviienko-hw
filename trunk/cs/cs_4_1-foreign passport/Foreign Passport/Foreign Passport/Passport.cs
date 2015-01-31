using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PassportNS
{
    class Passport
    {
        public string PassportNo { get; private set; }
        public string Surname { get; private set; }
        public string Name { get; private set; }
        public string PatronymicName { get; private set; }
        public DateTime BirthDate { get; private set; }
        public  string BirthPlace { get; private set; }
        public string Sex { get; private set; }
        public string Authority { get; private set; }
        public DateTime IssueDate { get; private set; }
        public string SpecialNotes { get; private set; }
        public string FamilyStatus { get; private set; }
        public string ResidencePlace { get; private set; }
       
        public Passport(string passportNo, string surname, string name, string patronymicName,
            DateTime birthDate, string birthPlace, string sex, string authority, DateTime issueDate,
            string residencePlace, string familyStatus="", string specialNotes="")
        {
            PassportNo = passportNo;
            Surname=surname;
            Name = name;
            PatronymicName = patronymicName;
            BirthDate = birthDate;
            BirthPlace = birthPlace;
            Sex = sex;
            Authority = authority;
            IssueDate = issueDate;
            SpecialNotes = specialNotes;
            FamilyStatus = familyStatus;
            ResidencePlace = residencePlace;
        }

        public void AddSpecialNotes(string specialNote) { SpecialNotes += "\n\t"+specialNote; }
        public void AddFamilyStatus(string familyStatus) { FamilyStatus += "\n\t" + familyStatus; }
        public void AddResidencePlace(string residencePlace) { ResidencePlace += "\n\t" + residencePlace; }

        public virtual void Print()
        {
            Console.WriteLine("Passport No:{0}", PassportNo);
            Console.WriteLine("Surname: {0}",Surname);
            Console.WriteLine("Name: {0}", Name);
            Console.WriteLine("Patronymic name: {0}", PatronymicName);
            Console.WriteLine("Date of birth: {0}", BirthDate.ToString("dd.MM.yyyy"));
            Console.WriteLine("Place of birth: {0}", BirthPlace);
            Console.WriteLine("Sex: {0}", Sex);
            Console.WriteLine("Authority: {0}", Authority);
            Console.WriteLine("Date of issue: {0}", IssueDate.ToString("dd.MM.yyyy"));
            Console.WriteLine("Special notes: {0}", SpecialNotes);
            Console.WriteLine("Family status: {0}", FamilyStatus);
            Console.WriteLine("Residence place: {0}", ResidencePlace);
        }
    }
}
