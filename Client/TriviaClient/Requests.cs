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
    }
}
