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
    /// Interaction logic for HighscoresWindow.xaml
    /// </summary>
    public partial class HighscoresWindow : Window
    {
        private Communicator communicator;
        private string username;
        public HighscoresWindow(Communicator communicator, string username)
        {
            this.communicator = communicator;
            this.username = username;
            InitializeComponent();
            UserLabel.Content = "Hello, " + username;
        }

        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            MainMenuWindow window = new MainMenuWindow(communicator, username);
            this.Close();
            window.Show();
        }
    }
}
