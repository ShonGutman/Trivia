using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    namespace Responses
    {
        public enum ResponseId : uint
        {
            LOGIN_RESPONSE_ID = 1,
            SIGN_UP_RESPONSE_ID = 2,
            LOGOUT_RESPONSE_ID = 3,
            JOIN_ROOM_RESPONSE_ID = 4,
            CREATE_ROOM_RESPONSE_ID = 5,
            GET_ALL_ROOMS_RESPONSE_ID = 6,
            GET_PLAYERS_IN_ROOM_RESPONSE_ID = 7,
            GET_PERSONAL_SCORE_RESPONSE_ID = 8,
            GET_HIGHEST_SCORE_RESPONSE_ID = 9,
            LEAVE_ROOM_RESPONSE_ID = 10,
            CLOSE_ROOM_RESPONSE_ID = 11,
            START_GAME_RESPONSE_ID = 12,
            GET_ROOM_STATE_RESPONSE_ID = 13,
            LEAVE_GAME_RESPONSE_ID = 14,
            GET_QUESTION_RESPONSE_ID = 15,
            SUBMIT_ANSWER_RESPONSE_ID = 16,
            FINISHED_GAME_RESPONSE_ID = 17,
            GET_GAME_RESULTS_RESPONSE_ID = 18,
            GENERAL_ERROR_RESPONSE_ID = 99
        }

        public enum STATUS : uint
        {
            SUCCESS = 100,
            FAIL = 101
        }

        public class GeneralResponse
        {
            public ResponseId id { get; set; }
            public string messageJson { get; set; }

            public GeneralResponse(ResponseId id, string messageJson)
            {
                this.id = id;
                this.messageJson = messageJson;
            }
        }

        public class ErrorResponse
        {
            public STATUS status { get; set; }
            public string message { get; set; }

            public ErrorResponse(STATUS status, string message)
            {
                this.status = status;
                this.message = message;
            }
        }

        public class UserStatistics
        {
            public int numGames { get; set; }
            public int numRightAnswers { get; set; }
            public int numWrongAnswers { get; set; }
            public double averageTimeForAnswer { get; set; }

            public UserStatistics(int numGames, int numRightAnswers, int numWrongAnswers, double averageTimeForAnswer)
            {
                this.numGames = numGames;
                this.numRightAnswers = numRightAnswers;
                this.numWrongAnswers = numWrongAnswers;
                this.averageTimeForAnswer = averageTimeForAnswer;
            }
        }
        public class PersonalStatsResponse
        {

            public STATUS Status { get; set; }
            public string UserStatistics { get; set; }

            public PersonalStatsResponse(STATUS status, string UserStatistics)
            {
                this.Status = status;
                this.UserStatistics = UserStatistics;
            }
        }

    public class HigheseScores
        {
            public STATUS Status { get; set; }
            public string HighScore { get; set; }

            public HigheseScores(STATUS status, string HighScore)
            {
                this.Status = status;
                this.HighScore = HighScore;
            }
        }

        public class AllRooms
        {
            public STATUS Status { get; set; }
            public List<RoomData> Rooms { get; set; }

            public AllRooms(STATUS status, List<RoomData> Rooms)
            {
                Status = status;
                this.Rooms = Rooms;
            }

        }

        public class AllPllayers
        {
            public STATUS Status { get; set; }
            public List<string> PlayersInRoom { get; set; }

            public AllPllayers(STATUS status, List<string> PlayersInRoom)
            {
                Status = status;
                this.PlayersInRoom = PlayersInRoom;
            }
        }


        public class RoomStatus
        {
            public STATUS Status { get; set; }
            public bool hasGameBegun { get; set; }

            public List<string> PlayersInRoom { get; set; }

            public RoomStatus(STATUS status, bool hasGameBegun, List<string> PlayersInRoom)
            {
                Status = status;
                this.hasGameBegun = hasGameBegun;
                this.PlayersInRoom = PlayersInRoom;
            }
        }

        public class GetQuestion
        {
            public STATUS Status { get; set; }
            public string question {  get; set; }

           public Dictionary<string, string> answers {  get; set; }

            public GetQuestion(STATUS status, string question, Dictionary<string, string> answers)
            {
                Status = status;
                this.question = question;
                this.answers = answers;
            }


        }
    }

}
