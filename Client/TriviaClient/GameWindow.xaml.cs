﻿using System;
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
    /// Interaction logic for GameWindow.xaml
    /// </summary>
    public partial class GameWindow : Window
    {
        private Communicator communicator;
        private string username;
        public GameWindow(Communicator communicator, string username)
        {
            InitializeComponent();
            this.communicator = communicator;
            this.username = username;
            UserLabel.Content = "Hello, " + username;
        }

        private void Ans1_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Ans2_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Ans3_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Ans4_Click(object sender, RoutedEventArgs e)
        {

        }

        private void EXIT_Click(object sender, RoutedEventArgs e)
        {
            MainWindow mainWindow = new MainWindow(communicator);
            this.Close();
            mainWindow.Show();
        }
    }
}
