using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Security.RightsManagement;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    public class Communicator
    {
        public const int MSG_LENGTH_BYTES = 4;

        private int _serverPort = 0;
        private string _serverIP = "";
        private NetworkStream _stream;
        
        //ctor
        public Communicator(int serverPort = 8826, string serverIP = "127.0.0.1")
        {
            _serverPort = serverPort;
            _serverIP = serverIP;

            TcpClient tcpClient = new TcpClient(_serverIP, _serverPort);
            _stream = tcpClient.GetStream();
        }

        /// <summary>
        /// sends msg to server
        /// </summary>
        /// <param name="msg"> msg to be sent</param>
        public void sendMsg(byte[] msg)
        {
            _stream.Write(msg, 0, msg.Length);
            _stream.Flush();
        }

        /// <summary>
        /// receives back a message from the server
        /// </summary>
        /// <returns>an object of general response</returns>
        public Responses.GeneralResponse receiveMsg()
        {
            //read the id of the msg (which response it is)
            Responses.ResponseId id = (Responses.ResponseId)_stream.ReadByte();

            //read the length of the msg
            byte[] lengthBytes = new byte[MSG_LENGTH_BYTES];
            _stream.Read(lengthBytes, 0, MSG_LENGTH_BYTES);
            
            uint length = Helper.convertBinToDec(lengthBytes);

            //read the msg from the stream
            byte[] msgJsonBytes = new byte[length];
            _stream.Read(msgJsonBytes, 0, (int)length);

            string jsonMsg = Encoding.UTF8.GetString(msgJsonBytes);

            return new Responses.GeneralResponse(id, jsonMsg);
        }
    }
}
