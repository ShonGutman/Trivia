using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    public class RoomData
    {
        public uint roomId {  get; set; }
        public string roomName { get; set; }
        public uint playersNum { get; set; }
        public uint questionNum { get; set; }
        public uint timePerQuestion { get; set; }
        public bool isActive { get; set; }

        public RoomData(uint roomId, string roomName, uint playersNum, uint questionNum, uint timePerQuestion, bool isActive)
        {
            this.roomId = roomId;
            this.roomName = roomName;
            this.playersNum = playersNum;
            this.questionNum = questionNum;
            this.timePerQuestion = timePerQuestion;
            this.isActive = isActive;
        }

        public override string ToString()
        {
            return roomName;
        }
    }
}
