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


        public Game() { }

        public Game(Guid id, int number, CbItem team1, CbItem team2, byte result, byte team1BidPercent,
            byte team2BidPercent, DateTime date, CbItem league, bool isFinished)
        {
            ID = id;
            Number = number;
            Team1 = team1;
            Team2 = team2;
            Result = result;
            Team1BidPercent = team1BidPercent;
            Team2BidPercent = team2BidPercent;
            Date = date;
            League = league;
            IsFinished = isFinished;
        }

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


        public int RemoveFromDB()
        {
            using (SqlConnection connection = DataLayer.DB.GetSqlConnection())
            {
                using (SqlCommand command = connection.CreateCommand())
                {
                    command.CommandText = "RemoveGame";
                    command.CommandType = CommandType.StoredProcedure;

                    SqlParameter guid = new SqlParameter("@Id", SqlDbType.UniqueIdentifier);
                    guid.Value = ID;
                    command.Parameters.Add(guid);

                    SqlParameter result = new SqlParameter("@Result", SqlDbType.Int);
                    result.Direction = ParameterDirection.ReturnValue;
                    command.Parameters.Add(result);


                    connection.Open();
                    command.ExecuteNonQuery();


                    return (int)result.Value;
                }
            }
        }

        public int AddToDB()
        {
            using (SqlConnection connection = DataLayer.DB.GetSqlConnection())
            {
                using (SqlCommand command = connection.CreateCommand())
                {
                    command.CommandText = "AddGame";
                    command.CommandType = CommandType.StoredProcedure;

                    SqlParameter guid = new SqlParameter("@Id", SqlDbType.UniqueIdentifier);
                    guid.Value = ID;
                    command.Parameters.Add(guid);

                    SqlParameter number = new SqlParameter("@Number", SqlDbType.Int);
                    number.Value = Number;
                    command.Parameters.Add(number);

                    SqlParameter team1 = new SqlParameter("@Team1", SqlDbType.UniqueIdentifier);
                    team1.Value = Team1.ID;
                    command.Parameters.Add(team1);

                    SqlParameter team2 = new SqlParameter("@Team2", SqlDbType.UniqueIdentifier);
                    team2.Value = Team2.ID;
                    command.Parameters.Add(team2);

                    SqlParameter result = new SqlParameter("@Result", SqlDbType.TinyInt);
                    result.Value = Result;
                    command.Parameters.Add(result);

                    SqlParameter team1BidPercent = new SqlParameter("@Team1BidPercent", SqlDbType.TinyInt);
                    team1BidPercent.Value = Team1BidPercent;
                    command.Parameters.Add(team1BidPercent);

                    SqlParameter team2BidPercent = new SqlParameter("@Team2BidPercent", SqlDbType.TinyInt);
                    team2BidPercent.Value = Team2BidPercent;
                    command.Parameters.Add(team2BidPercent);

                    SqlParameter date = new SqlParameter("@Date", SqlDbType.DateTime2, 0);
                    date.Value = Date;
                    command.Parameters.Add(date);

                    SqlParameter league = new SqlParameter("@League", SqlDbType.UniqueIdentifier);
                    league.Value = League.ID;
                    command.Parameters.Add(league);

                    SqlParameter isFinished = new SqlParameter("@IsFinished", SqlDbType.Bit);
                    isFinished.Value = IsFinished;
                    command.Parameters.Add(isFinished);

                    SqlParameter returnedValue = new SqlParameter("@ReturnedValue", SqlDbType.Int);
                    returnedValue.Direction = ParameterDirection.ReturnValue;
                    command.Parameters.Add(returnedValue);

                    connection.Open();
                    command.ExecuteNonQuery();

                    return (int)returnedValue.Value;
                }
            }
        }

        public int UpdateInDB()
        {
            using (SqlConnection connection = DataLayer.DB.GetSqlConnection())
            {
                using (SqlCommand command = connection.CreateCommand())
                {
                    command.CommandText = "UpdateGame";
                    command.CommandType = CommandType.StoredProcedure;

                    SqlParameter guid = new SqlParameter("@Id", SqlDbType.UniqueIdentifier);
                    guid.Value = ID;
                    command.Parameters.Add(guid);

                    SqlParameter number = new SqlParameter("@Number", SqlDbType.Int);
                    number.Value = Number;
                    command.Parameters.Add(number);

                    SqlParameter team1 = new SqlParameter("@Team1", SqlDbType.UniqueIdentifier);
                    team1.Value = Team1.ID;
                    command.Parameters.Add(team1);

                    SqlParameter team2 = new SqlParameter("@Team2", SqlDbType.UniqueIdentifier);
                    team2.Value = Team2.ID;
                    command.Parameters.Add(team2);

                    SqlParameter result = new SqlParameter("@Result", SqlDbType.TinyInt);
                    result.Value = Result;
                    command.Parameters.Add(result);

                    SqlParameter team1BidPercent = new SqlParameter("@Team1BidPercent", SqlDbType.TinyInt);
                    team1BidPercent.Value = Team1BidPercent;
                    command.Parameters.Add(team1BidPercent);

                    SqlParameter team2BidPercent = new SqlParameter("@Team2BidPercent", SqlDbType.TinyInt);
                    team2BidPercent.Value = Team2BidPercent;
                    command.Parameters.Add(team2BidPercent);

                    SqlParameter date = new SqlParameter("@Date", SqlDbType.DateTime2, 0);
                    date.Value = Date;
                    command.Parameters.Add(date);

                    SqlParameter league = new SqlParameter("@League", SqlDbType.UniqueIdentifier);
                    league.Value = League.ID;
                    command.Parameters.Add(league);

                    SqlParameter isFinished = new SqlParameter("@IsFinished", SqlDbType.Bit);
                    isFinished.Value = IsFinished;
                    command.Parameters.Add(isFinished);

                    SqlParameter returnedValue = new SqlParameter("@ReturnedValue", SqlDbType.Int);
                    returnedValue.Direction = ParameterDirection.ReturnValue;
                    command.Parameters.Add(returnedValue);

                    connection.Open();
                    command.ExecuteNonQuery();

                    return (int)returnedValue.Value;
                }
            }
        }


    }

    public class Games : IEnumerable
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
