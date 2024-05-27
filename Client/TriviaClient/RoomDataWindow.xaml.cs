using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for RoomDataWindow.xaml
    /// </summary>
    public partial class RoomDataWindow : Window
    {
        private Communicator communicator;
        private string username;
        public RoomDataWindow(Communicator communicator, string username, bool isAdmin)
        {
            this.communicator = communicator;
            this.username = username;
            InitializeComponent();
            UserLabel.Content = "Hello, " + username;

            if(isAdmin)
            {
                StartButton.Visibility = Visibility.Visible;
                CloseButton.Visibility = Visibility.Visible;
            }

            else
            {
                LeaveRoom.Visibility = Visibility.Visible;
            }

        }

        private void CloseButton_Click(object sender, RoutedEventArgs e)
        {

        }

        private void StartButton_Click(object sender, RoutedEventArgs e)
        {

        }

        private void LeaveRoom_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
