using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TriviaClient.Responses;

namespace TriviaClient
{
    public class Helper
    {

        /// <summary>
        /// check if msg if failed
        /// </summary>
        /// <param name="jsonMsg"> the json data received rom sever</param>
        /// <returns> true if fail, false if not</returns>
        public static bool isFailed(string jsonMsg)
        {
            
            try
            {
                JObject jsonObject = JObject.Parse(jsonMsg);

                return (int)jsonObject["status"] == (int)Responses.STATUS.FAIL;
            }

            catch
            {
                return false;
            }

        }

        /// <summary>
        /// convert binary to decimal number
        /// </summary>
        /// <param name="bitsArray"> the binary bytes</param>
        /// <returns> decimal result</returns>
        public static uint convertBinToDec(byte[] bitsArray)
        {
            byte[] reversed = bitsArray.Reverse().ToArray();
            return BitConverter.ToUInt32(reversed, 0);
        }

        /// <summary>
        /// convert integer into binary array of 4 bytes
        /// </summary>
        /// <param name="num"> integer to convert</param>
        /// <returns> result in binary</returns>
        public static byte[] convertIntToBin(uint num)
        {
            return BitConverter.GetBytes(num);
        }

        /// <summary>
        /// Fits a message and a code into a binary buffer according to the protocol.
        /// </summary>
        /// <param name="msg"> The message string to be included in the byte[] </param>
        /// <param name="code"> The code representing the message type</param>
        /// <returns> The binary buffer containing the message and code formatted according to the protocol.</returns>
        public static byte[] fitToProtocol(string msg, uint code)
        {
            List<byte> resultList = new List<byte>();

            //add according to protocol 
            resultList.Add((byte)code);
            resultList.AddRange(convertIntToBin((uint)msg.Length).Reverse());
            resultList.AddRange(Encoding.UTF8.GetBytes(msg));

            //convert to array
            return resultList.ToArray();
        }
    }
}
