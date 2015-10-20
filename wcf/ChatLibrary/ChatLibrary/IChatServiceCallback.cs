using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ServiceModel;

namespace ChatLibrary
{

    public interface IChatServiceCallback
    {
        [OperationContract(IsOneWay = true)]
        void NewUserCallback(string name);

        [OperationContract(IsOneWay = true)]
        void NewMessageCallback(string from, string message, bool isPrivate);

        [OperationContract(IsOneWay = true)]
        void UserUnjoinedCallBack(string from);
    }
}
