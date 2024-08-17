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
            LEAVE_ROOM_REQUEST_ID = 10,
            CLOSE_ROOM_REQUEST_ID = 11,
            START_GAME_REQUEST_ID = 12,
            GET_ROOM_STATE_REQUEST_ID = 13,
            LEAVE_GAME_REQUEST_ID = 14,
            GET_QUESTION_REQUEST_ID = 15,
            SUBMIT_ANSWER_REQUEST_ID = 16,
            FINISHED_GAME_REQUEST_ID = 17,
            GET_GAME_RESULT_REQUEST_ID = 18,
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
            public string roomName { get; set; }
            public uint playersNum { get; set; }
            public uint questionNum { get; set; }
            public uint timePerQuestion { get; set; }

            public CreateRoomRequest(string roomName, uint playersNum, uint questionNum, uint timePerQuestion)
            {
                this.roomName = roomName;
                this.playersNum = playersNum;
                this.questionNum = questionNum;
                this.timePerQuestion = timePerQuestion;
            }
        }

        public class RoomRequest
        {
            public uint roomId { get; set; }

            public RoomRequest(uint roomId)
            {
                this.roomId = roomId;
            }
        }

        public class SubmitAnswer
        {
            public uint answerID { get; set; }

            public double timeForAnswer { get; set; }

            public SubmitAnswer(uint answerID, double timeForAnswer)
            { 
               this.answerID = answerID;
               this.timeForAnswer = timeForAnswer;
            }
        }
    }
}
