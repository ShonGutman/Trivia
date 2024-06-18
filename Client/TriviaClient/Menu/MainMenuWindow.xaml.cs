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
using TriviaClient.Question;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for MainMenuWindow.xaml
    /// </summary>
    public partial class MainMenuWindow : Window
    {

        private Communicator communicator;
        private string username;
        public MainMenuWindow(Communicator communicator, string username)
        {
            this.communicator = communicator;
            this.username = username;
            InitializeComponent();
            UserLabel.Content = "Hello, " + username;

        }

        private void Signout_Click(object sender, RoutedEventArgs e)
        {
            byte[] msg = Helper.fitToProtocol("", (int)Requests.RequestId.LOGOUT_REQUEST_ID);

            //send and scan msg from server
            communicator.sendMsg(msg);
            Responses.GeneralResponse response = communicator.receiveMsg();

            //check if server response is indead logout response
            if (response.id == Responses.ResponseId.LOGOUT_RESPONSE_ID)
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
                    MainWindow mainWindow = new MainWindow(communicator);
                    this.Close();
                    mainWindow.Show();
                }
            }
        }

        private void JoinRoom_Click(object sender, RoutedEventArgs e)
        {
            JoinRoomWindow window = new JoinRoomWindow(communicator, username);
            this.Close();
            window.Show();
        }

        private void CreateRoom_Click(object sender, RoutedEventArgs e)
        {
            CreateRoomWindow window = new CreateRoomWindow(communicator, username);
            this.Close();
            window.Show();
        }

        private void MyStatus_Click(object sender, RoutedEventArgs e)
        {
            StatisticsWindow window = new StatisticsWindow(communicator, username);
            this.Close();
            window.Show();
        }

        private void BestScores_Click(object sender, RoutedEventArgs e)
        {
            HighscoresWindow window = new HighscoresWindow(communicator, username);
            this.Close();
            window.Show();
        }

        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void AddQuesrion_Click(object sender, RoutedEventArgs e)
        {
            AddQuestionWindow window = new AddQuestionWindow(communicator, username);
            this.Close();
            window.Show();
        }
    }
}
