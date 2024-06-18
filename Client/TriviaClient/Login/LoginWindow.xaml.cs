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
    /// Interaction logic for LoginWindow.xaml
    /// </summary>
    public partial class LoginWindow : Window
    {
        private Communicator communicator;

        //ctor
        public LoginWindow(Communicator communicator)
        {
            this.communicator = communicator;
            InitializeComponent();
        }

        // Handles the click event of the Login button.
        private void LoginButton_Click(object sender, RoutedEventArgs e)
        {
            //stop because not all input is given
            if(isInputEmpty())
            { 
                return; 
            }

            //get userName & password from field in gui
            string username = userName_Input.Text;
            string password = password_Input.Password;

            //create a login request
            Requests.LoginRequest request = new Requests.LoginRequest(username, password);

            //serialize object and make it fit to protocol
            string json = JsonConvert.SerializeObject(request, Formatting.Indented);

            byte[] msg = Helper.fitToProtocol(json, (int)Requests.RequestId.LOGIN_REQUEST_ID);

            //send and scan msg from server
            communicator.sendMsg(msg);
            Responses.GeneralResponse response = communicator.receiveMsg();

            //check if server response is indead login response
            if(response.id == Responses.ResponseId.LOGIN_RESPONSE_ID)
            {
                //check if server responsed was failed
                if(Helper.isFailed(response.messageJson))
                {
                  
                    Responses.ErrorResponse errorResponse = JsonConvert.DeserializeObject<Responses.ErrorResponse>(response.messageJson);

                    //raise error popup with server's response
                    ErrorPopup errorWindow = new ErrorPopup(errorResponse.message);
                    errorWindow.ShowDialog();
                }

                else
                {
                    MainMenuWindow mainMenuWindow = new MainMenuWindow(communicator, username);
                    this.Close();
                    mainMenuWindow.Show();
                }
            }
        }

        private bool isInputEmpty()
        {
            if (string.IsNullOrEmpty(userName_Input.Text) || string.IsNullOrEmpty(password_Input.Password))
            {

                // Display error message
                ErrorPopup errorWindow = new ErrorPopup("Please enter both username and password.");
                errorWindow.ShowDialog();

                return true;
            }

            return false;
        }

        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            MainWindow mainWindow = new MainWindow(communicator);
            this.Close();
            mainWindow.Show();
        }

        private void ForgotPass_Click(object sender, RoutedEventArgs e)
        {

        }

        private void ChangePAss_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
