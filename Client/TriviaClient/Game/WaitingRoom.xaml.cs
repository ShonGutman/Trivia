using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
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
using TriviaClient.Game;

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

            // Call getResults asynchronously
            Application.Current.Dispatcher.Invoke(async () => await getResults());

        }

        private async Task getResults()
        {
            byte[] msg = Helper.fitToProtocol("", (int)Requests.RequestId.GET_GAME_RESULT_REQUEST_ID);

            // Use Task.Run to run the server communication on a background thread
            await Task.Run(() =>
            {
                //send and scan msg from server
                communicator.sendMsg(msg);
                Responses.GeneralResponse response = communicator.receiveMsg();

                //check if server response is indeed get question response
                if (response.id == Responses.ResponseId.GET_GAME_RESULTS_RESPONSE_ID)
                {
                    Responses.GameResults result = JsonConvert.DeserializeObject<Responses.GameResults>(response.messageJson);

                    // Update UI on the UI thread
                    Application.Current.Dispatcher.Invoke(() =>
                    {
                        ResultsWindow window = new ResultsWindow(communicator, username, result.results);
                        this.Close();
                        window.Show();
                    });
                }
            });
        }
    }
}
