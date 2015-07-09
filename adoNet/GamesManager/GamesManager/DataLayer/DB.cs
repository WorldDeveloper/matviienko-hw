using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataLayer
{
    public class DB
    {
        public static string ConnectionString
        {
            get
            {
                return ConfigurationManager.ConnectionStrings["DBGames"].ConnectionString;
            }
        }

        public static SqlConnection GetSqlConnection()
        {
            return new SqlConnection(ConnectionString);
        }


    }
}
