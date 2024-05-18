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
    }
}
