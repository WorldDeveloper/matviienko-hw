using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Client
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    [CallbackBehavior(
        ConcurrencyMode = ConcurrencyMode.Single,
        UseSynchronizationContext = false)]
    public partial class MainWindow : Window, ChatClient.ChatRef.IChatCallback
    {
        public ChatClient.ChatRef.ChatClient mProxy;

        public MainWindow()
        {
            InitializeComponent();
            mProxy = new ChatClient.ChatRef.ChatClient(new InstanceContext(this), "WSDualHttpBinding_IChat1");
            mProxy.Open();   
        }

        private void btnJoin_Click(object sender, RoutedEventArgs e)
        {
            if (!string.IsNullOrWhiteSpace(txtUserName.Text))
            mProxy.Join(txtUserName.Text);
           
        }

        private void btnSend_Click(object sender, RoutedEventArgs e)
        {
            //if (!string.IsNullOrWhiteSpace(txtNewMessage.Text))
            //    mProxy.Send(txtUserName.Text, txtNewMessage.Text);
            lblReceivedMesages.Content = lblReceivedMesages.Content + "\n has joined the conversation\n";
        }


        public void NewMessageCallback(string from, string message, bool isPrivate)
        {
            MessageBox.Show("Hello");
        }

        public void NewUserCallback(string name)
        {
            MessageBox.Show("Hello");
        }

        public void UserUnjoinedCallBack(string from)
        {
            MessageBox.Show("Hello");
        }
    }
}
