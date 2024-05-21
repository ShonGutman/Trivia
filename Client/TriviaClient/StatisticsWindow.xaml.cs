using Newtonsoft.Json;
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
    /// Interaction logic for StatisticsWindow.xaml
    /// </summary>
    public partial class StatisticsWindow : Window
    {
        private Communicator communicator;
        private string username;
        public StatisticsWindow(Communicator communicator, string username)
        {
            this.communicator = communicator;
            this.username = username;
            InitializeComponent();
            UserLabel.Content = username;

            setPersonalStatus();
        }

        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            MainMenuWindow window = new MainMenuWindow(communicator, username);
            this.Close();
            window.Show();
        }

        private void setPersonalStatus()
        {
            byte[] msg = Helper.fitToProtocol("", (int)Requests.RequestId.GET_PERSONAL_SCORE_REQUEST_ID);

            //send and scan msg from server
            communicator.sendMsg(msg);
            Responses.GeneralResponse response = communicator.receiveMsg();

            //check if server response is indead login response
            if (response.id == Responses.ResponseId.GET_PERSONAL_SCORE_RESPONSE_ID)
            {
                //check if server responsed was failed
                if (Helper.isFailed(response.messageJson))
                {

                    Responses.ErrorResponse errorResponse = JsonConvert.DeserializeObject<Responses.ErrorResponse>(response.messageJson);

                    //raise error popup with server's response
                    ErrorPopup errorWindow = new ErrorPopup(errorResponse.message);
                    errorWindow.ShowDialog();
                }

                else
                {
                    Responses.PersonalStatsResponse statsResponse = JsonConvert.DeserializeObject<Responses.PersonalStatsResponse>(response.messageJson);

                    Responses.HighScore highScores = JsonConvert.DeserializeObject<Responses.HighScore>(statsResponse.HighScore);

                    //set lables
                    numOfGames.Content = "number of games: " + highScores.numGames;
                    numPfRightAns.Content = "number of right answers: " + highScores.numRightAnswers;
                    numOfWrongAns.Content = "number of wrong answers: " + highScores.numWrongAnswers;
                    AvgTimeForAns.Content = "average time for answer: " + highScores.averageTimeForAnswer;
                }
            }
        }
    }
}
