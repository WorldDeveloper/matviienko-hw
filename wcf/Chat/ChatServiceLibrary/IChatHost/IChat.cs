using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace ChatHost
{
    [ServiceContract(SessionMode = SessionMode.Required,
        CallbackContract = typeof(IChatCallback))]
    public interface IChat
    {
        [OperationContract]
        bool Join(string name);

        [OperationContract]
        void Send(string from, string message);

        [OperationContract]
        void SendPrivate(string from, string to, string message);

        [OperationContract]
        void Leave(string name);
    }

    public interface IChatCallback
    {
        [OperationContract(IsOneWay = true)]
        void NewUserCallback(string name);

        [OperationContract(IsOneWay = true)]
        void NewMessageCallback(string from, string message, bool isPrivate);

        [OperationContract(IsOneWay = true)]
        void UserUnjoinedCallBack(string from);
    }
}
