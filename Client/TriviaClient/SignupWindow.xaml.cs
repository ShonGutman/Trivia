using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Globalization;
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
    /// Interaction logic for SignupWindow.xaml
    /// </summary>
    public partial class SignupWindow : Window
    {
        private Communicator communicator;
        public SignupWindow(Communicator communicator)
        {
            this.communicator = communicator;
            InitializeComponent();
        }


        private void passInfo_Click(object sender, RoutedEventArgs e)
        {
            // Display info message for paasword
            InfoWindow infoWindow = new InfoWindow("password meets the following criteria:\r\n\t " +
                "* - Contains at least one number\r\n\t " +
                "* - Contains at least one lowercase letter\r\n\t " +
                "* - Contains at least one uppercase letter\r\n\t " +
                "* - Contains at least one special character from the set [@!#$%^&*]\r\n\t " +
                "* - Has a length of at least 8 characters");

            infoWindow.ShowDialog();

        }

        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            MainWindow mainWindow = new MainWindow(communicator);
            this.Close();
            mainWindow.Show();
        }


        private void SignupButton_Click(object sender, RoutedEventArgs e)
        {
            //stop because not all input is given
            if (isInputEmpty())
            {
                return;
            }

            string username = UserName_Input.Text;
            string password = Password_input.Text;
            string confirmPassword = ConfirmPassword_input.Text;
            string email = Email_input.Text;
            string phone = Phone_input.Text;
            string address = Street_input.Text + " " + Apt_input.Text + " " + City_input.Text;
            string birthday = getDate();

            if(!password.Equals(confirmPassword))
            {

                //raise error popup response
                ErrorPopup errorWindow = new ErrorPopup("Passwords don't match each other");
                errorWindow.ShowDialog();

                return;
            }

            //create a signup request
            Requests.SignupRequest request = new Requests.SignupRequest(username, password, 
                email, address, phone, birthday); 

            //serialize object and make it fit to protocol
            string json = JsonConvert.SerializeObject(request, Formatting.Indented);

            byte[] msg = Helper.fitToProtocol(json, (int)Requests.RequestId.SIGN_UP_REQUEST_ID);

            //send and scan msg from server
            communicator.sendMsg(msg);
            Responses.GeneralResponse response = communicator.receiveMsg();

            //check if server response is indead signup response
            if (response.id == Responses.ResponseId.SIGN_UP_RESPONSE_ID)
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
                    MainMenuWindow mainMenuWindow = new MainMenuWindow(communicator, username);
                    this.Close();
                    mainMenuWindow.Show();
                }
            }
        }


        private string getDate()
        {
            string formattedDate = "";
            if (Calender_input.SelectedDate.HasValue)
            {
                DateTime selectedDate = Calender_input.SelectedDate.Value;
                // Format the selected date
                formattedDate = selectedDate.ToString("dd.MM.yyyy", CultureInfo.InvariantCulture);
            }
            return formattedDate;
        }

        private bool isInputEmpty()
        {
            if (string.IsNullOrEmpty(UserName_Input.Text) || string.IsNullOrEmpty(Password_input.Text)
                || string.IsNullOrEmpty(ConfirmPassword_input.Text) || string.IsNullOrEmpty(Email_input.Text)
                || string.IsNullOrEmpty(Phone_input.Text) || string.IsNullOrEmpty(Street_input.Text)
                || string.IsNullOrEmpty(Apt_input.Text) || string.IsNullOrEmpty(City_input.Text)
                || !Calender_input.SelectedDate.HasValue)
            {

                // Display error message
                ErrorPopup errorWindow = new ErrorPopup("Please fill all date");
                errorWindow.ShowDialog();

                return true;
            }

            return false;

        }
    }
}
