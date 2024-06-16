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
using TriviaClient.Requests___Responses___Objects;

namespace TriviaClient.Game
{
    /// <summary>
    /// Interaction logic for ResultsWindow.xaml
    /// </summary>
    /// 
    public partial class ResultsWindow : Window
    {

        private Communicator communicator;
        private string username;
        private List<PersonalGameResult> results;
        public ResultsWindow(Communicator communicator, string username, List<PersonalGameResult> results)
        {
            this.communicator = communicator;
            this.username = username;
            this.results = results;

            InitializeComponent();
        }
    }
}
