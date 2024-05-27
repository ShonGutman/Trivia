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
    /// Interaction logic for JoinRoomWindow.xaml
    /// </summary>
    public partial class JoinRoomWindow : Window
    {
        private Communicator communicator;
        private string username;
        private BackgroundWorker background_worker_get_rooms = new BackgroundWorker();
        private BackgroundWorker background_worker_get_players = new BackgroundWorker();
        public JoinRoomWindow(Communicator communicator, string username)
        {
            this.communicator = communicator;
            this.username = username;
            InitializeComponent();
            UserLabel.Content = "Hello, " + username;

            startRefreshRoomsThread();

        }

        private void background_worker_get_rooms_RunWorkerCompleted(object? sender, RunWorkerCompletedEventArgs e)
        {

        }

        private void background_worker_get_rooms_ProgressChanged(object? sender, ProgressChangedEventArgs e)
        {
            if (e.UserState is List<RoomData> allRooms)
            {
                RoomsList.ItemsSource = allRooms;
            }

        }

        private void background_worker_get_rooms_DoWork(object? sender, DoWorkEventArgs e)
        {
            while (!background_worker_get_rooms.CancellationPending)
            {
                List<RoomData> rooms = QueryAllRooms();

                background_worker_get_rooms.ReportProgress(0, rooms);

                // Wait for 2 seconds before the next request
                Thread.Sleep(2000);
            }
        }



        private void RoomsList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (background_worker_get_players.IsBusy)
            {
                background_worker_get_players.CancelAsync();
            }

            RoomData room = (RoomData)RoomsList.SelectedItem;

            playersLable.Visibility = Visibility.Visible;

            startRefreshPlayersTgread(room.roomId);

            PlayerList.Visibility = Visibility.Visible;
        }

        private void JoinRoom_Click(object sender, RoutedEventArgs e)
        {

        }

        private void ExitButton_Click(object sender, RoutedEventArgs e)
        {

        }

        public List<RoomData> QueryAllRooms()
        {

            byte[] msg = Helper.fitToProtocol("", (int)Requests.RequestId.GET_ALL_ROOMS_REQUEST_ID);

            //send and scan msg from server
            communicator.sendMsg(msg);
            Responses.GeneralResponse response = communicator.receiveMsg();



            try
            {

                Responses.AllRooms allRoomsResponse = JsonConvert.DeserializeObject<Responses.AllRooms>(response.messageJson);
                return allRoomsResponse.Rooms;
            }

            catch
            {
                return null;
            }


        }

        public List<string> QueryAllPlayersInRoom(uint roomId)
        {
            //create CreateRoomRequest
            Requests.GetAllPlayersInRoom request = new Requests.GetAllPlayersInRoom(roomId);

            //serialize object and make it fit to protocol
            string json = JsonConvert.SerializeObject(request, Formatting.Indented);

            byte[] msg = Helper.fitToProtocol(json, (int)Requests.RequestId.GET_PLAYERS_IN_ROOM_REQUEST_ID);

            //send and scan msg from server
            communicator.sendMsg(msg);
            Responses.GeneralResponse response = communicator.receiveMsg();



            try
            {

                Responses.AllPllayers allPlayers = JsonConvert.DeserializeObject<Responses.AllPllayers>(response.messageJson);
                return allPlayers.PlayersInRoom;
            }

            catch
            {
                return null;
            }


        }


        public void startRefreshRoomsThread()
        {
            background_worker_get_rooms.DoWork += background_worker_get_rooms_DoWork;
            background_worker_get_rooms.ProgressChanged += background_worker_get_rooms_ProgressChanged;
            background_worker_get_rooms.RunWorkerCompleted += background_worker_get_rooms_RunWorkerCompleted;

            background_worker_get_rooms.WorkerSupportsCancellation = true;
            background_worker_get_rooms.WorkerReportsProgress = true;

            if (!background_worker_get_rooms.IsBusy)
            {
                background_worker_get_rooms.RunWorkerAsync();
            }
        }

        public void startRefreshPlayersTgread(uint roomId)
        {
            background_worker_get_players.DoWork += background_worker_get_players_DoWork;
            background_worker_get_players.ProgressChanged += background_worker_get_players_ProgressChanged;
            background_worker_get_players.RunWorkerCompleted += background_worker_get_players_RunWorkerCompleted;

            background_worker_get_players.WorkerSupportsCancellation = true;
            background_worker_get_players.WorkerReportsProgress = true;

            if (!background_worker_get_players.IsBusy)
            {
                background_worker_get_players.RunWorkerAsync(roomId);
            }
        }

        private void background_worker_get_players_RunWorkerCompleted(object? sender, RunWorkerCompletedEventArgs e)
        {

        }

        private void background_worker_get_players_ProgressChanged(object? sender, ProgressChangedEventArgs e)
        {
            if (e.UserState is List<string> allPlayers)
            {
                PlayerList.ItemsSource = allPlayers;
            }
        }

        private void background_worker_get_players_DoWork(object? sender, DoWorkEventArgs e)
        {
            while (!background_worker_get_rooms.CancellationPending)
            {
                List<string> players = QueryAllPlayersInRoom((uint)e.Argument);

                background_worker_get_rooms.ReportProgress(0, players);

                // Wait for 4 seconds before the next request
                Thread.Sleep(4000);
            }
        }
    }
}
