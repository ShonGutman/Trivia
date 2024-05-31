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

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for RoomDataWindow.xaml
    /// </summary>
    public partial class RoomDataWindow : Window
    {
        private Communicator communicator;
        private string username;
        private BackgroundWorker background_worker_get_players = new BackgroundWorker();
        public RoomDataWindow(Communicator communicator, string username, bool isAdmin)
        {
            this.communicator = communicator;
            this.username = username;
            InitializeComponent();
            UserLabel.Content = "Hello, " + username;

            if(isAdmin)
            {
                StartButton.Visibility = Visibility.Visible;
                CloseButton.Visibility = Visibility.Visible;
            }

            else
            {
                LeaveRoom.Visibility = Visibility.Visible;
            }

            startRefreshPlayersThread();

        }

        private void CloseButton_Click(object sender, RoutedEventArgs e)
        {
            byte[] msg = Helper.fitToProtocol("", (int)Requests.RequestId.CLOSE_ROOM_REQUEST_ID);

            //send and scan msg from server
            communicator.sendMsg(msg);
            Responses.GeneralResponse response = communicator.receiveMsg();

            //check if server response is indead logout response
            if (response.id == Responses.ResponseId.CLOSE_ROOM_RESPONSE_ID)
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
                    MainMenuWindow mainWindow = new MainMenuWindow(communicator, username);
                    this.Close();
                    mainWindow.Show();
                }
            }
        }

        private void StartButton_Click(object sender, RoutedEventArgs e)
        {

        }

        private void LeaveRoom_Click(object sender, RoutedEventArgs e)
        {
            byte[] msg = Helper.fitToProtocol("", (int)Requests.RequestId.LEAVE_ROOM_REQUEST_ID);

            //send and scan msg from server
            communicator.sendMsg(msg);
            Responses.GeneralResponse response = communicator.receiveMsg();

            //check if server response is indead leave room response
            if (response.id == Responses.ResponseId.LEAVE_ROOM_RESPONSE_ID)
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
                    MainMenuWindow mainWindow = new MainMenuWindow(communicator, username);
                    this.Close();
                    mainWindow.Show();
                }
            }
        }

        public object QueryAllPlayers()
        {

            try
            {
                byte[] msg = Helper.fitToProtocol("", (int)Requests.RequestId.GET_ROOM_STATE_REQUEST_ID);

                //send and scan msg from server
                communicator.sendMsg(msg);
                Responses.GeneralResponse response = communicator.receiveMsg();

                //check if server response is indead room status response
                if (response.id == Responses.ResponseId.GET_ROOM_STATE_RESPONSE_ID)
                {
                    //check if server responsed was failed
                    if (Helper.isFailed(response.messageJson))
                    {

                        Responses.ErrorResponse errorResponse = JsonConvert.DeserializeObject<Responses.ErrorResponse>(response.messageJson);

                        return errorResponse;
                    }

                    else
                    {
                        return JsonConvert.DeserializeObject<Responses.RoomStatus>(response.messageJson);
                    }
                }

                return null;
            }

            catch (Exception e) 
            {
                return null;
            }
        }

        public void startRefreshPlayersThread()
        {
            background_worker_get_players.DoWork += background_worker_get_players_DoWork;
            background_worker_get_players.ProgressChanged += background_worker_get_players_ProgressChanged;
            background_worker_get_players.RunWorkerCompleted += background_worker_get_players_RunWorkerCompleted;

            background_worker_get_players.WorkerSupportsCancellation = true;
            background_worker_get_players.WorkerReportsProgress = true;

            if (!background_worker_get_players.IsBusy)
            {
                background_worker_get_players.RunWorkerAsync();
            }


        }

        private void background_worker_get_players_RunWorkerCompleted(object? sender, RunWorkerCompletedEventArgs e)
        {
        }

        private void background_worker_get_players_ProgressChanged(object? sender, ProgressChangedEventArgs e)
        {
            if (e.UserState is Responses.ErrorResponse errorResponse)
            {
                background_worker_get_players.CancelAsync();

                ErrorPopup popup = new ErrorPopup("Room was closed!");
                popup.ShowDialog();

                //move to menu
                MainMenuWindow window = new MainMenuWindow(communicator, username);
                this.Close();
                window.Show();
            }

            else if(e.UserState is Responses.RoomStatus roomStatus)
            {
                if(roomStatus.hasGameBegun)
                {
                    //move to game window :)
                }

                else
                {
                    UsersList.ItemsSource = roomStatus.PlayersInRoom;
                }
            }
        }

        private void background_worker_get_players_DoWork(object? sender, DoWorkEventArgs e)
        {
            while (!background_worker_get_players.CancellationPending)
            {
                object serverResponse = QueryAllPlayers();

                background_worker_get_players.ReportProgress(0, serverResponse);

                // Wait for a half of a second before the next request
                Thread.Sleep(700);
            }
        }
    }
}
