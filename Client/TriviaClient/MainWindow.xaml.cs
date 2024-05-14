using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        private Communicator communicator;

        //ctor
        public MainWindow()
        {
            communicator = new Communicator();
            InitializeComponent();
        }

        //ctor
        public MainWindow(Communicator communicator)
        {
            this.communicator = communicator;
            InitializeComponent();
        }

        // Handles the click event of the Login button.
        private void LoginButton_Click(object sender, RoutedEventArgs e)
        {

            // Create a new instance of the LoginWindow.
            LoginWindow loginWindow = new LoginWindow(communicator);

            this.Close();
            loginWindow.Show();

        }

        private void SignupButton_Click(object sender, RoutedEventArgs e)
        {
        }
    }
}