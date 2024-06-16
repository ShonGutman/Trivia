using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TriviaClient.Responses;

namespace TriviaClient.Requests___Responses___Objects
{
    public class PersonalGameResult
    {
        public string username { get; set; }
        public uint numRightAnswers { get; set; }

        public PersonalGameResult(string username, uint numRightAnswers)
        {
            this.username = username;
            this.numRightAnswers = numRightAnswers;
        }
    }

}
