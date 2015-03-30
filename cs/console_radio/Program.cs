using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WMPLib;
using System.Threading;
using System.Windows.Forms;


namespace console_radio
{
    class Program
    {      
        
        static void Main(string[] args)
        {
            Console.Title = "Invisible Radio";
            Player player = new Player();
            TrayIcon trayIcon = new TrayIcon(player);
            Application.Run();
        }
    }
}
