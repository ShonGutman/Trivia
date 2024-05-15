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

        private void SignupButton_Click(object sender, RoutedEventArgs e)
        {
            string username = UserName_Input.Text;
            string password = Password_input.Text;
            string confirmPassword = ConfirmPassword_input.Text;
            string email = Email_input.Text;
            string phone = Phone_input.Text;
            string address = Street_input.Text + " " + Apt_input.Text + " " + City_input.Text;
            string birthday = getDate();

            if(!password.Equals(confirmPassword))
            {
                //do smth (later)...
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

            if (response.id == Responses.ResponseId.SIGN_UP_RESPONSE_ID)
            {
                //check if server responsed with success
                if (!Helper.isFailed(response.messageJson))
                {

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
    }
}
