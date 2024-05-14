﻿using Newtonsoft.Json;
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
            //get userName & password from field in gui
            string userName = userName_Input.Text;
            string password = password_Input.Password;

            //create a login request
            Requests.LoginRequest request = new Requests.LoginRequest(userName, password);

            //serialize object and make it fit to protocol
            string json = JsonConvert.SerializeObject(request, Formatting.Indented);

            byte[] msg = Helper.fitToProtocol(json, (int)Requests.RequestId.LOGIN_REQUEST_ID);

            //send and scan msg from server
            communicator.sendMsg(msg);
            Responses.GeneralResponse response = communicator.receiveMsg();

            if(response.id == Responses.ResponseId.LOGIN_RESPONSE_ID)
            {
                //check if server responsed with success
                if(!Helper.isFailed(response.messageJson))
                {

                }
            }
        }
    }
}
