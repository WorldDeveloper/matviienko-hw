using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataLayer
{
    public class CbItem
    {
        public Guid ID { get; set; }
        public string Name { get; set; }

        public CbItem(Guid guid, string name)
        {
            ID = guid;
            Name = name;
        }

        public override string ToString()
        {
            return Name;
        }
    }
}
