using System;
using System.Windows;
using System.Windows.Threading;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for GameWindow.xaml
    /// </summary>
    public partial class GameWindow : Window
    {
        private Communicator communicator;
        private string username;
        private RoomData room;

        private int quesCounter = 0;
        private int scoreCounter = 0;

        private DispatcherTimer timer;
        private DateTime targetTime;

        public GameWindow(Communicator communicator, string username, RoomData room)
        {
            InitializeComponent();

            this.communicator = communicator;
            this.username = username;
            this.room = room;

            UserLabel.Content = "Hello, " + username;
            QuestionCount.Content = room.questionNum;

            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromMilliseconds(100);
            timer.Tick += Timer_Tick;

            // Set the target time to the current time plus the time per question
            targetTime = DateTime.Now.AddSeconds(this.room.timePerQuestion);

            Loaded += GameWindow_Loaded;
        }

        private void GameWindow_Loaded(object sender, RoutedEventArgs e)
        {
            timer.Start();
            UpdateTimer(); // Initial update
        }

        private void Ans1_Click(object sender, RoutedEventArgs e)
        {
            // Handle answer 1 click
        }

        private void Ans2_Click(object sender, RoutedEventArgs e)
        {
            // Handle answer 2 click
        }

        private void Ans3_Click(object sender, RoutedEventArgs e)
        {
            // Handle answer 3 click
        }

        private void Ans4_Click(object sender, RoutedEventArgs e)
        {
            // Handle answer 4 click
        }

        private void EXIT_Click(object sender, RoutedEventArgs e)
        {
            MainWindow mainWindow = new MainWindow(communicator);
            this.Close();
            mainWindow.Show();
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            UpdateTimer();
        }

        private void UpdateTimer()
        {
            var countdown = targetTime - DateTime.Now;

            if (countdown <= TimeSpan.Zero)
            {
                // Stop the timer if the countdown is finished
                timer.Stop();
                Counter.Content = "00:00";
                // You can add any additional logic you need to handle when the countdown reaches zero
            }
            else
            {
                // Display the remaining time with seconds and milliseconds
                Counter.Content = $"{countdown.Seconds:D2}:{countdown.Milliseconds / 10:D2}";
            }
        }
    }
}
