using System;
using System.Collections;
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

            //sort results from highest to lowest. (credit: https://stackoverflow.com/questions/3309188/how-to-sort-a-listt-by-a-property-in-the-object)
            this.results = results.OrderBy(o => o.numRightAnswers).ToList();

            InitializeComponent();

            showResults();
        }

        public void showResults()
        {
            //there is always at least one player
            winner1.Text = results[0].username + " - " + results[0].numRightAnswers;

            if (results.Count > 1)
            {
                winner2.Text = results[1].username + " - " + results[1].numRightAnswers;
            }

            else
            {
                //there is no second player in game
                winner2.Text = "";
            }

            if (results.Count > 2)
            {
                winner3.Text = results[2].username + " - " + results[2].numRightAnswers;
            }
            
            else
            {
                //there is no third player in game
                winner2.Text = "";
            }

            string restPlayers = "";

            if (results.Count > 3)
            {
                for(int i = 3; i < results.Count; i++)
                {
                    restPlayers += results[i].username + " - " + results[i].numRightAnswers + '\n';
                }
            }

            rest.Text = restPlayers;
        }

        private void EXIT_Click(object sender, RoutedEventArgs e)
        {
            MainMenuWindow mainWindow = new MainMenuWindow(communicator, username);
            this.Close();
            mainWindow.Show();
        }
    }



}
