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
            UserLabel.Content = username;

            setHighScores();
        }

        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            MainMenuWindow window = new MainMenuWindow(communicator, username);
            this.Close();
            window.Show();
        }

        private void setHighScores()
        {
            byte[] msg = Helper.fitToProtocol("", (int)Requests.RequestId.GET_HIGHEST_SCORE_REQUEST_ID);

            //send and scan msg from server
            communicator.sendMsg(msg);
            Responses.GeneralResponse response = communicator.receiveMsg();

            //check if server response is indead high score response
            if (response.id == Responses.ResponseId.GET_HIGHEST_SCORE_RESPONSE_ID)
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
                    Responses.HigheseScores highScoresResponse = JsonConvert.DeserializeObject<Responses.HigheseScores>(response.messageJson);

                    Dictionary<string, int> scores = JsonConvert.DeserializeObject<Dictionary<string, int>>(highScoresResponse.HighScore);

                    // Get the top 3 pairs sorted by int value in descending order
                    var top3Pairs = scores.OrderByDescending(kvp => kvp.Value).Take(3).ToList();


                    if (top3Pairs.Count > 0)
                    {
                        highscore1.Content = top3Pairs[0].Key + " : " + top3Pairs[0].Value;
                    }

                    else if (top3Pairs.Count > 1)
                    {
                        highscore2.Content = top3Pairs[1].Key + " : " + top3Pairs[1].Value;
                    }

                    else if (top3Pairs.Count > 2)
                    {
                        highscore3.Content = top3Pairs[2].Key + " : " + top3Pairs[2].Value;
                    }


                }

            }
        }
    }
}
