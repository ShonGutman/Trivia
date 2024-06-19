using System;
using System.Windows;

namespace TriviaClient.Login
{
    /// <summary>
    /// Interaction logic for ForgotPasswordWindow.xaml
    /// </summary>
    public partial class ForgotPasswordWindow : Window
    {
        private Communicator communicator;
        private string sentCode;

        public ForgotPasswordWindow(Communicator communicator)
        {
            InitializeComponent();
            this.communicator = communicator;
        }

        private void SendCodeButton_Click(object sender, RoutedEventArgs e)
        {
            string email = EmailTextBox.Text;
            if (string.IsNullOrEmpty(email))
            {
                ErrorPopup errorWindow = new ErrorPopup("Please enter email");
                errorWindow.ShowDialog();
                return;
            }

            // TODO : SEND THE AUTH CODE
        }

        private void ConfirmCode_Click(object sender, RoutedEventArgs e)
        {
            string enteredCode = AuthCodeTextBox.Text;
            if (enteredCode == sentCode)
            {
                //TODO
            }
            else
            {
                ErrorPopup errorWindow = new ErrorPopup("Incorrect authentication code. Please try again.");
                errorWindow.ShowDialog();
                return;
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
