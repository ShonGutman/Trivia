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

namespace TriviaClient.Login
{
    /// <summary>
    /// Interaction logic for ChangePasswordWindow.xaml
    /// </summary>
    public partial class ChangePasswordWindow : Window
    {
        private Communicator communicator;

        public ChangePasswordWindow(Communicator communicator)
        {
            this.communicator = communicator;
            InitializeComponent();
        }

        private bool isInputEmpty()
        {
            if (string.IsNullOrEmpty(userName_Input_Change.Text) 
                || string.IsNullOrEmpty(OldPassword_Input.Text)
                || string.IsNullOrEmpty(newPass_Input.Text))
            {

                // Display error message
                ErrorPopup errorWindow = new ErrorPopup("Please enter all fields");
                errorWindow.ShowDialog();

                return true;
            }

            return false;
        }

        private void ChangePasswordButton_Click(object sender, RoutedEventArgs e)
        {
            //stop because not all input is given
            if (isInputEmpty())
            {
                return;
            }

            //get userName & password from field in gui
            string username = userName_Input_Change.Text;
            string currentPassword = OldPassword_Input.Text;
            string newPassword = newPass_Input.Text;

            // Create a change password request
            Requests.ChangePasswordRequest changePasswordRequest = new Requests.ChangePasswordRequest(username, currentPassword, newPassword);

            // Serialize the change password request
            string changePasswordJson = JsonConvert.SerializeObject(changePasswordRequest, Formatting.Indented);

            byte[] changePasswordMsg = Helper.fitToProtocol(changePasswordJson, (int)Requests.RequestId.CHANGE_PASSWORD_REQUEST_ID);

            // Send the change password request to the server
            communicator.sendMsg(changePasswordMsg);
            Responses.GeneralResponse changePasswordResponse = communicator.receiveMsg();

            // Check if server response is indeed a change password response
            if (changePasswordResponse.id == Responses.ResponseId.CHANGE_PASSWORD_RESPONSE_ID)
            {
                // Check if the server response indicates success or failure
                if (Helper.isFailed(changePasswordResponse.messageJson))
                {
                    Responses.ErrorResponse errorResponse = JsonConvert.DeserializeObject<Responses.ErrorResponse>(changePasswordResponse.messageJson);

                    // Raise error popup with server's response
                    ErrorPopup errorWindow = new ErrorPopup(errorResponse.message);
                    errorWindow.ShowDialog();
                }
                else
                {
                    // Password change was successful

                    // Display info message for paasword
                    InfoWindow infoWindow = new InfoWindow("Password changed successfully!");
                    infoWindow.ShowDialog();

                    LoginWindow loginWindow = new LoginWindow(communicator);
                    this.Close();
                    loginWindow.Show();
                }
            }
        }

        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            LoginWindow loginWindow = new LoginWindow(communicator);
            this.Close();
            loginWindow.Show();
        }
    }
}
