using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;

using WMPLib;
using System.Threading;
using System.IO;
using System.Text.RegularExpressions;

namespace console_radio
{
    class Player
    {
        private WindowsMediaPlayer mPlayer = new WMPLib.WindowsMediaPlayer();
        private List<string> mPlaylist = new List<string>();
        private string mPlaylistPath = "playlist.txt";
        private int mCurrentStation = 0;

        public Player()
        {
            mPlayer.settings.volume = 100;
            OpenPlaylist();
            if (mPlaylist.Count == 0)
            {
                Console.WriteLine("Playlist is empty");
                return;
            }
            mPlayer.URL = mPlaylist[mCurrentStation];
            mPlayer.controls.play();
        }

        public string Title
        {
            get
            {
                if (mPlaylist.Count > 0) return mPlayer.currentMedia.name;
                return "Playlist is empty";
            }
        }
        public int Volume
        {
            set { mPlayer.settings.volume = value; }
        }

        public bool Play()
        {
            mPlayer.controls.play();
            int attempt = 0;
            while (mPlayer.playState != WMPPlayState.wmppsPlaying)
            {
                Thread.Sleep(1000);
                if (++attempt > 15)
                {
                    Console.WriteLine("Error: can't play station {0}", mPlayer.URL);
                    return false;
                }
            }
            return true;
        }

        public void Pause()
        {
            mPlayer.controls.pause();
        }

        public void NextStation()
        {
            if (mPlaylist.Count < 2) return;
            mCurrentStation = ++mCurrentStation % mPlaylist.Count;
            mPlayer.URL = mPlaylist[mCurrentStation];
            Play();
        }

        public void PreviousStation()
        {
            if (mPlaylist.Count < 2) return;

            if (mCurrentStation > 0) mCurrentStation--;
            else mCurrentStation = mPlaylist.Count - 1;

            mPlayer.URL = mPlaylist[mCurrentStation];
            Play();
        }


        public WMPPlayState PlayState
        {
            get { return mPlayer.playState; }
        }

        private bool LinkIsValid(string link)
        {
            Regex linkParser = new Regex(@"^((https)|(http))://[a-zA-Z0-9\.\-/:]+", RegexOptions.IgnoreCase);
            Match match = linkParser.Match(link);
            if (!match.Success)
            {
                Console.WriteLine("Error: incorrect url.");
                return false;
            }
            return true;
        }

        private void OpenPlaylist()
        {
            try
            {
                using (StreamReader sr = new StreamReader(mPlaylistPath))
                {
                    while (sr.Peek() >= 0)
                    {
                        String link = sr.ReadLine();
                        if (LinkIsValid(link)) mPlaylist.Add(link);
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("The playlist could not be read: {0}", e.Message);
                Console.WriteLine("The process failed: {0}\n", e.ToString());
            }
        }

        private void SavePlaylist()
        {
            StringBuilder sb = new StringBuilder();

            foreach (string station in mPlaylist)
            {
                sb.AppendLine(station);
            }

            using (StreamWriter outfile = new StreamWriter(mPlaylistPath))
            {
                outfile.Write(sb.ToString());
            }
        }

        public bool AddStation()
        {
            string input;

            Console.Write("\nAdd station URL: ");
            input = Console.ReadLine();

            if (!LinkIsValid(input))
            {
                Console.WriteLine("Station wasn't added");
                return false;
            }

            foreach (string link in mPlaylist)
            {
                if (link == input)
                {
                    Console.WriteLine("Station wasn't added: duplicated record");
                    return false;
                }
            }
            Console.WriteLine("\t... adding new station");
           
            mPlayer.URL = input;
            if (!Play())
            {
                mPlayer.URL = mPlaylist[mCurrentStation];
                return false;
            }

            mPlaylist.Add(input);
            mCurrentStation = mPlaylist.Count - 1;

            SavePlaylist();
            Console.WriteLine("\t... station {0} was successfully added!", mPlayer.currentMedia.name);
            Console.WriteLine("\t... {0} is playing now", mPlayer.currentMedia.name);
            return true;
        }

        public bool ValidStation
        {
            get { return !(mPlaylist.Count == 0 || mCurrentStation >= mPlaylist.Count || mCurrentStation < 0); }
        }

        public int StationsCount
        {
            get { return mPlaylist.Count; }
        }

        public bool RemoveStation()
        {
            Console.WriteLine("\nRemove station: {0}", mPlayer.URL);
            string curStationName = mPlayer.currentMedia.name;
            mPlayer.controls.stop();

            mPlaylist.RemoveAt(mCurrentStation);
            SavePlaylist();
            Console.WriteLine("\t... station {0} was successfully removed", curStationName);

            if (mPlaylist.Count > 0)
            {
                mCurrentStation = mCurrentStation % mPlaylist.Count;
                mPlayer.URL = mPlaylist[mCurrentStation];
                mPlayer.controls.play();
                Console.WriteLine("\t... {0} is playing now", mPlayer.currentMedia.name);
                return true;
            }
            else
            {
                mPlayer.URL = "";
                Console.WriteLine("\nPlaylist is empty");
            }
            return false;
        }
    }
}
