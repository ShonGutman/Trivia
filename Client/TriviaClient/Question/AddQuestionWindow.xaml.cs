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

namespace TriviaClient.Question
{
    /// <summary>
    /// Interaction logic for AddQuestionWindow.xaml
    /// </summary>
    public partial class AddQuestionWindow : Window
    {
        private Communicator communicator;
        private string username;
        public AddQuestionWindow(Communicator communicator, string username)
        {
            this.communicator = communicator;
            this.username = username;
            InitializeComponent();
            UserLabel.Content = username;
        }

        private bool isInputEmpty()
        {
            if (string.IsNullOrEmpty(question_input.Text) 
                || string.IsNullOrEmpty(firstAns.Text) || string.IsNullOrEmpty(secAns.Text) || 
                string.IsNullOrEmpty(thirdAns.Text) || string.IsNullOrEmpty(forthAns.Text)
                || (firstAnsCheckBox.IsChecked != true && secAnsCheckBox.IsChecked != true
                && thirdAnsCheckBox.IsChecked != true && forthAnsCheckBox.IsChecked != true))
            {
                // Display error message
                ErrorPopup errorWindow = new ErrorPopup("Please enter the question, the answers\nand pick which will be the correct ans");
                errorWindow.ShowDialog();

                return true;
            }
            else
            {
                int checkedCount = 0;
                if (firstAnsCheckBox.IsChecked == true) checkedCount++;
                if (secAnsCheckBox.IsChecked == true) checkedCount++;
                if (thirdAnsCheckBox.IsChecked == true) checkedCount++;
                if (forthAnsCheckBox.IsChecked == true) checkedCount++;

                if (checkedCount != 1)
                {
                    // Display error message
                    ErrorPopup errorWindow = new ErrorPopup("Please pick exactly one correct answer.");
                    errorWindow.ShowDialog();

                    return true;
                }
            }

            return false;

        }

        private void SendInfo_Click(object sender, RoutedEventArgs e)
        {
            //stop because not all input is given
            if (isInputEmpty())
            {
                return;
            }

            //get the input
            string question = question_input.Text;
            string correct = " ";
            string incorrect1 = " ", incorrect2 = " ", incorrect3 = " ";
            if (firstAnsCheckBox.IsChecked == true)
            {
                correct = firstAns.Text;
                incorrect1 = secAns.Text;
                incorrect2 = thirdAns.Text;
                incorrect3 = forthAns.Text;
            }
            else if (secAnsCheckBox.IsChecked == true)
            {
                correct = secAns.Text;
                incorrect1 = firstAns.Text;
                incorrect2 = thirdAns.Text;
                incorrect3 = forthAns.Text;
            }
            else if (thirdAnsCheckBox.IsChecked == true)
            {
                correct = thirdAns.Text;
                incorrect1 = secAns.Text;
                incorrect2 = firstAns.Text;
                incorrect3 = forthAns.Text;
            }
            else if (forthAnsCheckBox.IsChecked == true)
            {
                correct = forthAns.Text;
                incorrect1 = secAns.Text;
                incorrect2 = thirdAns.Text;
                incorrect3 = firstAns.Text;
            }


            //create a send question request
            Requests.sendQuestionRequest request = new Requests.sendQuestionRequest(question, correct, incorrect1, incorrect2, incorrect3);

            //serialize object and make it fit to protocol
            string json = JsonConvert.SerializeObject(request, Formatting.Indented);

            byte[] msg = Helper.fitToProtocol(json, (int)Requests.RequestId.SEND_QUESTION_REQUEST_ID);

            //send and scan msg from server
            communicator.sendMsg(msg);
            Responses.GeneralResponse response = communicator.receiveMsg();

            //check if server response is indeed a send question response
            if (response.id == Responses.ResponseId.SEND_QUESTION_RESPONSE_ID)
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
                    MainMenuWindow window = new MainMenuWindow(communicator, username);
                    this.Close();
                    window.Show();
                }
            }
        }

        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            MainMenuWindow window = new MainMenuWindow(communicator, username);
            this.Close();
            window.Show();
        }

    }
}
