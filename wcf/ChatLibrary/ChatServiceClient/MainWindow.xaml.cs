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
using ChatLibrary;
using System.Threading;
using System.Collections.ObjectModel;

namespace ChatServiceClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private ChatClient mClient;
        public ObservableCollection<string> mUsers;

        public MainWindow()
        {
            InitializeComponent();
            txtUserName.Focus();
            mUsers = new ObservableCollection<string>();
            lstUsers.ItemsSource = mUsers;
            rbPublic.IsChecked = true;


        }

        private void btnJoin_Click(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrWhiteSpace(txtUserName.Text))
                return;

            if (btnJoin.Content.ToString() == "Join")
            {
                mClient = new ChatClient();
                mClient.Start(mClient, txtUserName.Text, this);
                btnJoin.IsDefault = false;
                btnSend.IsDefault = true;
                txtNewMessage.Focus();
            }
            else
            {
                mClient.Leave(txtUserName.Text);
                btnSend.IsDefault = false;
                btnJoin.IsDefault = true;
            }
        }

        private void btnSend_Click(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrWhiteSpace(txtNewMessage.Text))
                return;

            if (rbPublic.IsChecked == true)
            {
                mClient.SendMessage(txtUserName.Text, txtNewMessage.Text);
            }
            else if (lstUsers.SelectedItem != null)
            {
                mClient.SendPrivateMessage(txtUserName.Text, lstUsers.SelectedItem.ToString(), txtNewMessage.Text);
            }
            else if (lstUsers.SelectedItem == null && rbPrivate.IsChecked == true)
            {
                MessageBox.Show("Select a private user", "Chat", MessageBoxButton.OK, MessageBoxImage.Asterisk);
            }
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            if (btnJoin.Content.ToString() == "Leave")
            {
                mClient.Leave(txtUserName.Text);
            }
        }

        private void lstUsers_GotFocus(object sender, RoutedEventArgs e)
        {
           
        }

        private void rbPublic_Checked(object sender, RoutedEventArgs e)
        {
            txtNewMessageHint.Text = "Public message";
            txtNewMessage.Focus();
        }

        private void rbPrivate_Checked(object sender, RoutedEventArgs e)
        {
            if (lstUsers.SelectedItem != null)
                txtNewMessageHint.Text = "Message to " + lstUsers.SelectedItem.ToString();

            txtNewMessage.Focus();
        }

        private void lstUsers_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (lstUsers.SelectedItem != null)
                txtNewMessageHint.Text = "Message to " + lstUsers.SelectedItem.ToString();

            rbPrivate.IsChecked = true;

            txtNewMessage.Focus();
        }
    }
}
