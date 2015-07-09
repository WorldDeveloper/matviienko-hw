using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SqlClient;
using System.Collections;
using System.Data;

namespace DataLayer
{
    public class Game
    {
        public Guid ID { get; set; }
        public int Number { get; set; }
        public CbItem Team1 { get; set; }
        public CbItem Team2 { get; set; }
        public byte Result { get; set; }
        public byte Team1BidPercent { get; set; }
        public byte Team2BidPercent { get; set; }
        public DateTime Date { get; set; }
        public CbItem League { get; set; }
        public bool IsFinished { get; set; }

        public void GetFromDB(Guid id)
        {
            using (SqlConnection connection = DataLayer.DB.GetSqlConnection())
            {
                using (SqlCommand command = connection.CreateCommand())
                {
                    command.CommandText = "GetGame";
                    command.CommandType = CommandType.StoredProcedure;

                    SqlParameter guid = new SqlParameter("@Id", SqlDbType.UniqueIdentifier);
                    guid.Value = id;
                    command.Parameters.Add(guid);
                    connection.Open();
                    using (SqlDataReader reader = command.ExecuteReader())
                    {
                        if (reader.Read())
                        {
                            ID = id;
                            Number = (int)reader["Number"];
                            Team1 = new CbItem((Guid)reader["Team1Id"], reader["Team1Name"].ToString());
                            Team2 = new CbItem((Guid)reader["Team2Id"], reader["Team2Name"].ToString());
                            Result = (byte)reader["Result"];
                            Team1BidPercent = (byte)reader["Team1BidPercent"];
                            Team2BidPercent = (byte)reader["Team2BidPercent"];
                            Date = (DateTime)reader["Date"];
                            League = new CbItem((Guid)reader["LeagueId"], reader["LeagueName"].ToString());
                            IsFinished = (bool)reader["IsFinished"];
                        }
                    }
                }
            }
        }



    }

    public class Games:IEnumerable
    {
         private List<CbItem> mGamesItems;

        public Games()
        {
            mGamesItems = new List<CbItem>();
            using (SqlConnection conn = DataLayer.DB.GetSqlConnection())
            {
                using (SqlCommand command = conn.CreateCommand())
                {
                    command.CommandText = "GetTeamsFromGames";
                    command.CommandType = CommandType.StoredProcedure;
                    conn.Open();

                    using (SqlDataReader reader = command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            Guid ID = (Guid)reader["Id"];
                            StringBuilder sb = new StringBuilder(reader["Team1Name"].ToString());
                            sb.Append(" vs ");
                            sb.Append(reader["Team2Name"].ToString());
                            sb.Append(" on ");
                            sb.Append(reader["Date"].ToString());
                            CbItem item = new CbItem(ID, sb.ToString());
                            mGamesItems.Add(item);
                        }
                    }
                }
            }
        }

        public IEnumerator GetEnumerator()
        {
            return mGamesItems.GetEnumerator();
        }
    }


}
