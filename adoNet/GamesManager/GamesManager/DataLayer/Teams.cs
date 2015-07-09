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
    public class Team
    {
        public Guid ID { get; set; }
        public string Name { get; set; }
        public short Wins { get; set; }
        public short Losses { get; set; }
        public short Draws { get; set; }
        public string PictureUrl { get; set; }


        //public Team(SqlDataReader reader)
        //{
        //    ID = (Guid)reader["Id"];
        //    Name = reader["Name"].ToString();
        //    Wins = (short)reader["Wins"];
        //    Losses = (short)reader["Losses"];
        //    Draws = (short)reader["Draws"];
        //    PictureUrl = reader["PictureUrl"].ToString();
        //}

        public Team(Guid guid, string name, short wins, short losses, short draws, string pictureUrl="")
        {
            ID = guid;
            Name = name;
            Wins = wins;
            Losses = losses;
            Draws = draws;
            PictureUrl = pictureUrl;
        }

        public override string ToString()
        {
            return Name;
        }

        public void GetFromDB()
        {
            using (SqlConnection conn = DataLayer.DB.GetSqlConnection())
            {
                using (SqlCommand command = conn.CreateCommand())
                {
                    command.CommandText = "GetTeam";
                    command.CommandType = CommandType.StoredProcedure;
                    SqlParameter guid = new SqlParameter("@ID", SqlDbType.UniqueIdentifier);
                    guid.Value = ID;
                    command.Parameters.Add(guid);

                    conn.Open();
                    using (SqlDataReader reader = command.ExecuteReader())
                    {
                        if (reader.Read())
                        {
                            Name = reader["Name"].ToString();
                            Wins = (short)reader["Wins"];
                            Losses = (short)reader["Losses"];
                            Draws = (short)reader["Draws"];
                            PictureUrl = reader["PictureUrl"].ToString();
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
                    command.CommandText = "RemoveTeam";
                    command.CommandType = CommandType.StoredProcedure;

                    SqlParameter guid = new SqlParameter("@Id", SqlDbType.UniqueIdentifier);
                    guid.Value = ID;
                    command.Parameters.Add(guid);

                    SqlParameter result = new SqlParameter("@Result", SqlDbType.Int);
                    result.Direction=ParameterDirection.ReturnValue;
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
                    command.CommandText = "AddTeam";
                    command.CommandType = CommandType.StoredProcedure;

                    SqlParameter guid = new SqlParameter("@Id", SqlDbType.UniqueIdentifier);
                    guid.Value = ID;
                    command.Parameters.Add(guid);

                    SqlParameter name = new SqlParameter("@Name", SqlDbType.NVarChar, 50);
                    name.Value = Name;
                    command.Parameters.Add(name);

                    SqlParameter wins = new SqlParameter("@Wins", SqlDbType.SmallInt);
                    wins.Value = Wins;
                    command.Parameters.Add(wins);

                    SqlParameter losses = new SqlParameter("@Losses", SqlDbType.SmallInt);
                    losses.Value = Losses;
                    command.Parameters.Add(losses);

                    SqlParameter draws = new SqlParameter("@Draws", SqlDbType.SmallInt);
                    draws.Value = Draws;
                    command.Parameters.Add(draws);

                    SqlParameter pictureUrl = new SqlParameter("@PictureUrl", SqlDbType.NVarChar, -1);
                    pictureUrl.Value = PictureUrl;
                    command.Parameters.Add(pictureUrl);

                    SqlParameter result = new SqlParameter("@Result", SqlDbType.Int);
                    result.Direction = ParameterDirection.ReturnValue;
                    command.Parameters.Add(result);

                    connection.Open();
                    command.ExecuteNonQuery();

                    return (int)result.Value;
                }
            }
        }

        public int UpdateInDB()
        {
            using (SqlConnection connection = DataLayer.DB.GetSqlConnection())
            {
                using (SqlCommand command = connection.CreateCommand())
                {
                    command.CommandText = "UpdateTeam";
                    command.CommandType = CommandType.StoredProcedure;

                    SqlParameter guid = new SqlParameter("@Id", SqlDbType.UniqueIdentifier);
                    guid.Value = ID;
                    command.Parameters.Add(guid);

                    SqlParameter name = new SqlParameter("@Name", SqlDbType.NVarChar, 50);
                    name.Value = Name;
                    command.Parameters.Add(name);

                    SqlParameter wins = new SqlParameter("@Wins", SqlDbType.SmallInt);
                    wins.Value = Wins;
                    command.Parameters.Add(wins);

                    SqlParameter losses = new SqlParameter("@Losses", SqlDbType.SmallInt);
                    losses.Value = Losses;
                    command.Parameters.Add(losses);

                    SqlParameter draws = new SqlParameter("@Draws", SqlDbType.SmallInt);
                    draws.Value = Draws;
                    command.Parameters.Add(draws);

                    SqlParameter pictureUrl = new SqlParameter("@PictureUrl", SqlDbType.NVarChar, -1);
                    pictureUrl.Value = PictureUrl;
                    command.Parameters.Add(pictureUrl);

                    SqlParameter result = new SqlParameter("@Result", SqlDbType.Int);
                    result.Direction = ParameterDirection.ReturnValue;
                    command.Parameters.Add(result);

                    connection.Open();
                    command.ExecuteNonQuery();

                    return (int)result.Value;
                }
            }
        }

    }


    public class Teams:IEnumerable
    {
        private List<CbItem> mTeamsList;

        public Teams()
        {
            mTeamsList = new List<CbItem>();
            using (SqlConnection conn = DataLayer.DB.GetSqlConnection())
            {
                using (SqlCommand command = conn.CreateCommand())
                {
                    command.CommandText = "GetTeamsList";
                    command.CommandType = CommandType.StoredProcedure;
                    conn.Open();

                    using (SqlDataReader reader = command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            CbItem team = new CbItem((Guid)reader["Id"], reader["Name"].ToString());
                            mTeamsList.Add(team);
                        }
                    }
                }

            }
        }

        public IEnumerator GetEnumerator()
        {
            return mTeamsList.GetEnumerator();
        }
    }
}
