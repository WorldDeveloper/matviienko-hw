using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using WMPLib;
using System.Windows.Forms;
using System.Reflection;
using System.IO;
using System.Drawing;

using System.Runtime.InteropServices;


namespace console_radio
{
    class TrayIcon
    {
        private NotifyIcon mNotifyIcon;
        private ContextMenu mMenu;
        private MenuItem mPauseMenu;
        private MenuItem mPlayMenu;
        private MenuItem mRemoveStationMenu;
        private MenuItem mNextStationMenu;
        private MenuItem mPreviousStationMenu;
        private MenuItem mManageWindowMenu;
        private MenuItem mAutoRunMenu;
        private MenuItem[] mVolumeValueMenu;

        private Player mPlayer;

        public TrayIcon(Player player)
        {
            mNotifyIcon = new NotifyIcon();
            Assembly currentAssembly = Assembly.GetExecutingAssembly();

            mNotifyIcon.Icon = new Icon("Icon.ico");
            mNotifyIcon.Visible = true;

            mPlayer = player;
            mMenu = new ContextMenu();

            MenuItem mSettings = new MenuItem("Settings");
            mManageWindowMenu = new MenuItem("Show Window", new EventHandler(ShowWindow_Click));
            mAutoRunMenu = new MenuItem("Run at stratup", new EventHandler(AutoStart_Click));
            mSettings.MenuItems.Add(mManageWindowMenu);
            mSettings.MenuItems.Add(mAutoRunMenu);

            MenuItem mEditStations = new MenuItem("Manage stations");
            mEditStations.MenuItems.Add(new MenuItem("Add URL", new EventHandler(AddStation_Click)));
            mRemoveStationMenu = new MenuItem("Remove current URL", new EventHandler(RemoveStation_Click));
            mEditStations.MenuItems.Add(mRemoveStationMenu);

            MenuItem mVolume = new MenuItem("Volume");
            mVolumeValueMenu = new MenuItem[5];
            for (int i = 0; i < 5; ++i)
            {
                mVolumeValueMenu[i] = new MenuItem(Convert.ToString(i*25), new EventHandler(Volume_Click));
                mVolume.MenuItems.Add(mVolumeValueMenu[i]);
            }
            mVolumeValueMenu[4].Checked = true;


            mPlayMenu = new MenuItem("Play", new EventHandler(Play_Click));
            mPauseMenu = new MenuItem("Pause", new EventHandler(Pause_Click));

            mNextStationMenu = new MenuItem("Next station", new EventHandler(NextStation_Click));
            mPreviousStationMenu = new MenuItem("Previous station", new EventHandler(PreviousStation_Click));


            mMenu.MenuItems.Add(new MenuItem("Exit", new EventHandler(CleanExit)));
            mMenu.MenuItems.Add("-");
            mMenu.MenuItems.Add(mSettings);
            mMenu.MenuItems.Add(mEditStations);
            mMenu.MenuItems.Add(mVolume);
            mMenu.MenuItems.Add("-");
            mMenu.MenuItems.Add(mPreviousStationMenu);
            mMenu.MenuItems.Add(mNextStationMenu);
            mMenu.MenuItems.Add("-");
            mMenu.MenuItems.Add(mPlayMenu);
            mMenu.MenuItems.Add(mPauseMenu);

            mPlayMenu.Enabled = false;
            mNotifyIcon.ContextMenu = mMenu;
            mNotifyIcon.MouseClick += new MouseEventHandler(TrayIcon_Click);
            mNotifyIcon.MouseMove += new MouseEventHandler(Notify_MouseMove);

            ShowWindow(mShowWindow);

            if (mPlayer.ValidStation)
                mNotifyIcon.ShowBalloonTip(5000, "Invisble Radio", mPlayer.Title + " starts playing", ToolTipIcon.Info);
            else
                mNotifyIcon.ShowBalloonTip(5000, "Invisble Radio", "Playlist is empty", ToolTipIcon.Info);

        }

        private void Notify_MouseMove(Object sender, MouseEventArgs e)
        {
            string title = "Invisible Radio";
            if (mPlayer.Title != "") title += ": " + mPlayer.Title;
            mNotifyIcon.Text = title;
            if (!mPlayer.ValidStation)
            {
                mPlayMenu.Enabled = false;
                mPauseMenu.Enabled = false;
                mRemoveStationMenu.Enabled = false;
            }
            else
            {
                if (mPlayer.PlayState != WMPPlayState.wmppsPlaying)
                {
                    mPlayMenu.Enabled = true;
                    mPauseMenu.Enabled = false;
                }
                else
                {
                    mPlayMenu.Enabled = false;
                    mPauseMenu.Enabled = true;
                }

                mRemoveStationMenu.Enabled = true;
            }

            if (mPlayer.StationsCount > 1)
            {
                mNextStationMenu.Enabled = true;
                mPreviousStationMenu.Enabled = true;
            }
            else
            {
                mNextStationMenu.Enabled = false;
                mPreviousStationMenu.Enabled = false;
            }
        }


        private void Play_Click(object sender, EventArgs e)
        {
           if (mPlayer.Play())
            mNotifyIcon.ShowBalloonTip(5000, "Invisble Radio", mPlayer.Title + " starts playing", ToolTipIcon.Info);
           else
               mNotifyIcon.ShowBalloonTip(5000, "Invisble Radio", "Error: can't play this station", ToolTipIcon.Error);
        }


        private void Pause_Click(object sender, EventArgs e)
        {
            mPlayer.Pause();
            //mPauseMenu.Enabled = false;
            //mPlayMenu.Enabled = true;            
        }

        private void NextStation_Click(object sender, EventArgs e)
        {
            mPlayer.NextStation();
            mNotifyIcon.ShowBalloonTip(5000, "Invisble Radio", mPlayer.Title + " starts playing", ToolTipIcon.Info);
        }

        private void PreviousStation_Click(object sender, EventArgs e)
        {
            mPlayer.PreviousStation();
            mNotifyIcon.ShowBalloonTip(5000, "Invisble Radio", mPlayer.Title + " starts playing", ToolTipIcon.Info);
        }

        private void AddStation_Click(object sender, EventArgs e)
        {
            ShowWindow(1);

            if (mPlayer.AddStation())
                mNotifyIcon.ShowBalloonTip(5000, "Invisble Radio", mPlayer.Title + " starts playing", ToolTipIcon.Info);
            else
                mNotifyIcon.ShowBalloonTip(5000, "Invisble Radio", "Error: station wasn't added", ToolTipIcon.Error);

            ShowWindow(0);
        }

        private void RemoveStation_Click(object sender, EventArgs e)
        {
            if (!mPlayer.ValidStation)
            {
                return;
            } 

            string prevTitle = mPlayer.Title;
            if (mPlayer.RemoveStation())
                mNotifyIcon.ShowBalloonTip(5000, "Invisble Radio", prevTitle + " was successfully removed.\n" + mPlayer.Title + " starts playing", ToolTipIcon.Info);
            if (!mPlayer.ValidStation)
                mNotifyIcon.ShowBalloonTip(5000, "Invisble Radio", "Playlist is empty", ToolTipIcon.Info);
        }


        private void CleanExit(object sender, EventArgs e)
        {
            ShowWindow(1);

            mNotifyIcon.Visible = false;
            Application.Exit();
            Environment.Exit(1);
        }

        private void TrayIcon_Click(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left && mPlayer.StationsCount>1)
            {
                mPlayer.NextStation();
                mNotifyIcon.ShowBalloonTip(5000, "Invisble Radio", mPlayer.Title + " starts playing", ToolTipIcon.Info);
            }
        }

        private void AutoStart_Click(object sender, EventArgs e)
        {
            string path = Directory.GetCurrentDirectory();
            string loc = System.Reflection.Assembly.GetEntryAssembly().Location;

            if (!mAutoRunMenu.Checked)
            {
                Microsoft.Win32.RegistryKey key = Microsoft.Win32.Registry.CurrentUser.OpenSubKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);
                key.SetValue("Invisible Radio",loc);                
            }
            else
            {
                Microsoft.Win32.RegistryKey key = Microsoft.Win32.Registry.CurrentUser.OpenSubKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);
                key.DeleteValue("Invisible Radio", false);
            }
            mAutoRunMenu.Checked = !mAutoRunMenu.Checked; 
        }

        private void ShowWindow_Click(object sender, EventArgs e)
        {
            ShowWindow(mShowWindow);
        }

        private void Volume_Click(object sender, EventArgs e)
        {

            for (int i = 0; i < 5; ++i)
            {
                if (sender == mVolumeValueMenu[i])
                {
                    mVolumeValueMenu[i].Checked = true;
                    mPlayer.Volume = i * 25;
                }
                else
                    mVolumeValueMenu[i].Checked = false;
            }
        }

        [DllImport("kernel32.dll", ExactSpelling = true)]
        private static extern IntPtr GetConsoleWindow();
        private static IntPtr mThisConsole = GetConsoleWindow();


        [DllImport("user32.dll")]
        private static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);
        private static Int32 mShowWindow = 0;

        private void ShowWindow(int show)
        {
            ShowWindow(mThisConsole, show);

            if (show == 0)
            {
                mManageWindowMenu.Text = "Show Window";
                mShowWindow = 1;
            }
            else
            {
                mManageWindowMenu.Text = "Hide Window";
                mShowWindow = 0;
            }
        }
    }
}
