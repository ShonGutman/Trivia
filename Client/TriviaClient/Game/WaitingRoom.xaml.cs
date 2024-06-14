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
    /// Interaction logic for WaitingRoom.xaml
    /// </summary>
    /// 
    public partial class WaitingRoom : Window
    {

        private Communicator communicator;
        private string username;
        public WaitingRoom(Communicator communicator, string username)
        {
            this.communicator = communicator;
            this.username = username;

            InitializeComponent();

            _ = getResults();
        }

        private async Task getResults()
        {
            byte[] msg = Helper.fitToProtocol("", (int)Requests.RequestId.GET_GAME_RESULT_REQUEST_ID);

            //send and scan msg from server
            communicator.sendMsg(msg);
            Responses.GeneralResponse response = communicator.receiveMsg();

            //check if server response is indead get question response
            if (response.id == Responses.ResponseId.GET_GAME_RESULTS_RESPONSE_ID)
            {
                Responses.GameResults result = JsonConvert.DeserializeObject<Responses.GameResults>(response.messageJson);

                //move to results page
            }
        }
    }
}
