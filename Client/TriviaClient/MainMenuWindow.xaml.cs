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
    /// Interaction logic for MainMenuWindow.xaml
    /// </summary>
    public partial class MainMenuWindow : Window
    {

        private Communicator communicator;
        public MainMenuWindow(Communicator communicator)
        {
            this.communicator = communicator;
            InitializeComponent();
        }

        private void Signout_Click(object sender, RoutedEventArgs e)
        {

        }

        private void JoinRoom_Click(object sender, RoutedEventArgs e)
        {

        }

        private void CreateRoom_Click(object sender, RoutedEventArgs e)
        {

        }

        private void MyStatus_Click(object sender, RoutedEventArgs e)
        {

        }

        private void BestScores_Click(object sender, RoutedEventArgs e)
        {

        }

        private void backButton_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Exit_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
