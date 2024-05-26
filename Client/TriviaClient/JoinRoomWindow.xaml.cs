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
        private BackgroundWorker background_worker = new BackgroundWorker();
        public JoinRoomWindow(Communicator communicator, string username)
        {
            this.communicator = communicator;
            this.username = username;
            InitializeComponent();
            UserLabel.Content = "Hello, " + username;

            startRefreshTread();

        }

        private void background_worker_RunWorkerCompleted(object? sender, RunWorkerCompletedEventArgs e)
        {

        }

        private void background_worker_ProgressChanged(object? sender, ProgressChangedEventArgs e)
        {
            if (e.UserState is List<RoomData> allRooms)
            {
                List<string> names = new List<string>();
                foreach (RoomData roomData in allRooms)
                {
                    names.Add(roomData.ToString());
                }

                RoomsList.ItemsSource = names;
            }

        }

        private void background_worker_DoWork(object? sender, DoWorkEventArgs e)
        {
            while (!background_worker.CancellationPending)
            {
                List<RoomData> reponse = QueryAllRooms();

                background_worker.ReportProgress(0, reponse);

                // Wait for 2 seconds before the next request
                Thread.Sleep(2000);
            }
        }



        private void RoomsList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

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


        public void startRefreshTread()
        {
            background_worker.DoWork += background_worker_DoWork;
            background_worker.ProgressChanged += background_worker_ProgressChanged;
            background_worker.RunWorkerCompleted += background_worker_RunWorkerCompleted;

            background_worker.WorkerSupportsCancellation = true;
            background_worker.WorkerReportsProgress = true;

            if (!background_worker.IsBusy)
            {
                background_worker.RunWorkerAsync();
            }
        }
    }
}
