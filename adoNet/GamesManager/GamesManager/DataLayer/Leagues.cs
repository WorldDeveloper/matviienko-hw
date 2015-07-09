using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataLayer
{
    public class League
    {
        public Guid ID { get; set; }
        public string Name { get; set; }
        public string PictureUrl { get; set; }

        public League(Guid id, string name, string pictureUrl = "")
        {
            ID = id;
            Name = name;
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
                    command.CommandText = "GetLeague";
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
                            PictureUrl = reader["PictureUrl"].ToString();
                        }
                    }
                }
            }
        }

        public int RemoveFromDB()
        {
            using (SqlConnection conn = DataLayer.DB.GetSqlConnection())
            {
                using (SqlCommand command = conn.CreateCommand())
                {
                    command.CommandText = "RemoveLeague";
                    command.CommandType = CommandType.StoredProcedure;
                    SqlParameter guid = new SqlParameter("@ID", SqlDbType.UniqueIdentifier);
                    guid.Value = ID;
                    command.Parameters.Add(guid);

                    SqlParameter result = new SqlParameter("@result", SqlDbType.Int);
                    result.Direction = ParameterDirection.ReturnValue;
                    command.Parameters.Add(result);

                    conn.Open();
                    command.ExecuteNonQuery();

                    return (int)result.Value;
                }
            }
        }

        public int UpdateInDB()
        {
            using (SqlConnection conn = DataLayer.DB.GetSqlConnection())
            {
                using (SqlCommand command = conn.CreateCommand())
                {
                    command.CommandText = "UpdateLeague";
                    command.CommandType = CommandType.StoredProcedure;
                    SqlParameter guid = new SqlParameter("@ID", SqlDbType.UniqueIdentifier);
                    guid.Value = ID;
                    command.Parameters.Add(guid);

                    SqlParameter name = new SqlParameter("@Name", SqlDbType.NVarChar, 50);
                    name.Value = Name;
                    command.Parameters.Add(name);

                    SqlParameter pictureUrl = new SqlParameter("@PictureUrl", SqlDbType.NVarChar, -1);
                    pictureUrl.Value = PictureUrl;
                    command.Parameters.Add(pictureUrl);

                    SqlParameter result = new SqlParameter("@result", SqlDbType.Int);
                    result.Direction = ParameterDirection.ReturnValue;
                    command.Parameters.Add(result);

                    conn.Open();
                    command.ExecuteNonQuery();

                    return (int)result.Value;
                }
            }
        }

        public int AddToDB()
        {
            using (SqlConnection conn = DataLayer.DB.GetSqlConnection())
            {
                using (SqlCommand command = conn.CreateCommand())
                {
                    command.CommandText = "AddLeague";
                    command.CommandType = CommandType.StoredProcedure;

                    SqlParameter guid = new SqlParameter("@Guid", SqlDbType.UniqueIdentifier);
                    guid.Value = ID;
                    command.Parameters.Add(guid);

                    SqlParameter name = new SqlParameter("@Name", SqlDbType.NVarChar, 50);
                    name.Value = Name;
                    command.Parameters.Add(name);

                    SqlParameter pictureUrl = new SqlParameter("@PictureUrl", SqlDbType.NVarChar, -1);
                    pictureUrl.Value = PictureUrl;
                    command.Parameters.Add(pictureUrl);

                    SqlParameter result = new SqlParameter("@result", SqlDbType.Int);
                    result.Direction = ParameterDirection.ReturnValue;
                    command.Parameters.Add(result);

                    conn.Open();
                    command.ExecuteNonQuery();

                    return (int)result.Value;
                }
            }
        }

    }

    public class Leagues : IEnumerable
    {
        private List<CbItem> mLeaguesList;

        public Leagues()
        {
            mLeaguesList = new List<CbItem>();
            using (SqlConnection conn = DataLayer.DB.GetSqlConnection())
            {
                using (SqlCommand command = conn.CreateCommand())
                {
                    command.CommandText = "GetLeaguesList";
                    command.CommandType = CommandType.StoredProcedure;
                    conn.Open();

                    using (SqlDataReader reader = command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            CbItem league = new CbItem((Guid)reader["Id"], reader["Name"].ToString());
                            mLeaguesList.Add(league);
                        }
                    }
                }

            }
        }

        public IEnumerator GetEnumerator()
        {
            return mLeaguesList.GetEnumerator();
        }
    }

}
