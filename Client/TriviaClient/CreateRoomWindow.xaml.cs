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
    /// Interaction logic for CreateRoomWindow.xaml
    /// </summary>
    public partial class CreateRoomWindow : Window
    {
        private Communicator communicator;
        private string username;
        public CreateRoomWindow(Communicator communicator, string username)
        {
            this.communicator = communicator;
            this.username = username;
            InitializeComponent();
            UserLabel.Content = "Hello, " + username;
        }

        private void SendInfo_Click(object sender, RoutedEventArgs e)
        {
            //stop because not all input is given
            if (isInputEmpty())
            {
                return;
            }

            string roomName = RoomName_input.Text;
            uint playersNum = uint.Parse(playersNum_input.Text);
            uint questionNum = uint.Parse(questionNum_input.Text);
            uint timePerQuestion = uint.Parse(pNum_input.Text);

            //create CreateRoomRequest
            Requests.CreateRoomRequest request = new Requests.CreateRoomRequest(roomName,
                playersNum, questionNum, timePerQuestion);

            //serialize object and make it fit to protocol
            string json = JsonConvert.SerializeObject(request, Formatting.Indented);

            byte[] msg = Helper.fitToProtocol(json, (int)Requests.RequestId.CREATE_ROOM_REQUEST_ID);

            //send and scan msg from server
            communicator.sendMsg(msg);
            Responses.GeneralResponse response = communicator.receiveMsg();

            //check if server response is indead login response
            if (response.id == Responses.ResponseId.CREATE_ROOM_RESPONSE_ID)
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
                    //do nothing for now.
                }
            }
        }

        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            MainMenuWindow window = new MainMenuWindow(communicator, username);
            this.Close();
            window.Show();
        }


        private bool isInputEmpty()
        {
            if (string.IsNullOrEmpty(RoomName_input.Text)
                || !uint.TryParse(playersNum_input.Text, out uint num1)
                || !uint.TryParse(questionNum_input.Text, out uint num2)
                || !uint.TryParse(pNum_input.Text, out uint num3))
            {
                
                // Display error message
                ErrorPopup errorWindow = new ErrorPopup("Please fill all data with correct inforamtion");
                errorWindow.ShowDialog();

                return true;
            }

            return false;

        }
    }
}
