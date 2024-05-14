using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    namespace Requests
    {

       public enum RequestId : uint
        {
	        LOGIN_REQUEST_ID = 1,
	        SIGN_UP_REQUEST_ID = 2,
	        ERROR_REQUEST_ID = 99
        }
        public class LoginRequest
        {
            public string username { get; set; }
            public string password {  get; set; }

            public LoginRequest(string username, string password)
            {
                this.username = username;
                this.password = password;
            }
        }

        public class SignupRequest
        {
            public string username { get; set; }
            public string password { get; set; }
            public string email { get; set; }
            public string address { get; set; }
            public string phoneNumber { get; set; }
            public string birthday { get; set; }

            public SignupRequest(string username, string password, string email, string address, string phoneNumber, string birthday)
            {
                this.username = username;
                this.password = password;
                this.email = email;
                this.address = address;
                this.phoneNumber = phoneNumber;
                this.birthday = birthday;
            }
        }
    }
}
