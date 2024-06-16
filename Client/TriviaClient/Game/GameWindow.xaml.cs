using Newtonsoft.Json;
using System;
using System.Windows;
using System.Windows.Controls;
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

        private uint quesCounter = 1;
        private uint scoreCounter = 0;

        private DispatcherTimer timer;
        private DateTime targetTime;
        private DateTime questionRecievedTime;

        private TaskCompletionSource<uint> answerCompletionSource;

        public GameWindow(Communicator communicator, string username, RoomData room)
        {
            InitializeComponent();

            this.communicator = communicator;
            this.username = username;
            this.room = room;

            //set lables to proper values
            UserLabel.Content = "Hello, " + username;
            RoomName.Content = room.roomName;

            setQuestionAndScoreCounter(quesCounter, scoreCounter);

            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromMilliseconds(100);
            timer.Tick += Timer_Tick;

            _ = handleAllGameAsync();
        }

        private void AnswerChoosed(object sender, RoutedEventArgs e)
        {
            if (answerCompletionSource != null && !answerCompletionSource.Task.IsCompleted)
            {
                Button clickedButton = (Button)sender;
                answerCompletionSource.SetResult(uint.Parse((string)clickedButton.Tag));
            }
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

                // Set an empty result since time ran out
                if (answerCompletionSource != null && !answerCompletionSource.Task.IsCompleted)
                {
                    answerCompletionSource.SetResult(0);
                }

            }
            else
            {
                // Display the remaining time with seconds and milliseconds
                Counter.Content = $"{countdown.Seconds:D2}:{countdown.Milliseconds / 10:D2}";
            }
        }

        private async Task handleAllGameAsync()
        {

            while (quesCounter <= room.questionNum)
            {

                Responses.GetQuestion questionMsg = await getNextQuestion();
                Question.Content = questionMsg.question;

                // Set answers
                Ans1.Content = questionMsg.answers["1"];
                Ans2.Content = questionMsg.answers["2"];
                Ans3.Content = questionMsg.answers["3"];
                Ans4.Content = questionMsg.answers["4"];

                // Set the target time to the current time plus the time per question
                questionRecievedTime = DateTime.Now;
                targetTime = DateTime.Now.AddSeconds(this.room.timePerQuestion);
                timer.Start();

                answerCompletionSource = new TaskCompletionSource<uint>();
                uint userAnswer = await answerCompletionSource.Task;
                double answerTime = (DateTime.Now - questionRecievedTime).TotalSeconds;

                timer.Stop();

                uint correctID = await submitAnswer(userAnswer, answerTime);

                if (correctID == userAnswer)
                {
                    scoreCounter++;
                }

                setQuestionAndScoreCounter(++quesCounter, scoreCounter);

            }

            finishedGame();
        }

        private async Task<Responses.GetQuestion> getNextQuestion()
        {
            byte[] msg = Helper.fitToProtocol("", (int)Requests.RequestId.GET_QUESTION_REQUEST_ID);

            //send and scan msg from server
            communicator.sendMsg(msg);
            Responses.GeneralResponse response = communicator.receiveMsg();

            //check if server response is indead get question response
            if (response.id == Responses.ResponseId.GET_QUESTION_RESPONSE_ID)
            {
                return JsonConvert.DeserializeObject<Responses.GetQuestion>(response.messageJson);
            }
            return null;
        }

        private void leaveGame()
        {

        }

        private void finishedGame()
        {
            byte[] msg = Helper.fitToProtocol("", (int)Requests.RequestId.FINISHED_GAME_REQUEST_ID);

            //send and scan msg from server
            communicator.sendMsg(msg);
            Responses.GeneralResponse response = communicator.receiveMsg();

            //check if server response is indead get question response
            if (response.id == Responses.ResponseId.FINISHED_GAME_RESPONSE_ID)
            {
                WaitingRoom window = new WaitingRoom(communicator, username);
                this.Close();
                window.Show();
            }
        }

        private async Task<uint> submitAnswer(uint answerID, double timeForAnswer)
        {

            //create CreateRoomRequest
            Requests.SubmitAnswer request = new Requests.SubmitAnswer(answerID, timeForAnswer);

            //serialize object and make it fit to protocol
            string json = JsonConvert.SerializeObject(request, Formatting.Indented);

            byte[] msg = Helper.fitToProtocol(json, (int)Requests.RequestId.SUBMIT_ANSWER_REQUEST_ID);

            //send and scan msg from server
            communicator.sendMsg(msg);
            Responses.GeneralResponse response = communicator.receiveMsg();

            //check if server response is indead get question response
            if (response.id == Responses.ResponseId.SUBMIT_ANSWER_RESPONSE_ID)
            {
                return JsonConvert.DeserializeObject<Responses.SubmitAnswer>(response.messageJson).correctAnswerID;
            }
            return 0;

        }

        private void setQuestionAndScoreCounter(uint questionNum, uint score)
        {
            QuestionCount.Content = "Question " + questionNum + "/" + room.questionNum;
            Score.Content = "Score: " + score + "/" + room.questionNum;
        }
    }
}
