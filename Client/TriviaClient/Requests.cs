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
            LOGOUT_REQUEST_ID = 3,
            JOIN_ROOM_REQUEST_ID = 4,
            CREATE_ROOM_REQUEST_ID = 5,
            GET_ALL_ROOMS_REQUEST_ID = 6,
            GET_PLAYERS_IN_ROOM_REQUEST_ID = 7,
            GET_PERSONAL_SCORE_REQUEST_ID = 8,
            GET_HIGHEST_SCORE_REQUEST_ID = 9,
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

        public class CreateRoomRequest
        {
            string roomName { get; set; }
            uint playersNum { get; set; }
            uint questionNum { get; set; }
            uint timePerQuestion { get; set; }

            public CreateRoomRequest(string roomName, uint playersNum, uint questionNum, uint timePerQuestion)
            {
                this.roomName = roomName;
                this.playersNum = playersNum;
                this.questionNum = questionNum;
                this.timePerQuestion = timePerQuestion;
            }
        }
    }
}
