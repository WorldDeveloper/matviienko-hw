using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ServiceModel;

namespace ChatLibrary
{
    [ServiceContract(CallbackContract = typeof(IChatServiceCallback))]
    public interface IChatService
    {
        [OperationContract(IsOneWay = true)]
        void Join(string name);

        [OperationContract(IsOneWay = true)]
        void Send(string from, string message);

        [OperationContract(IsOneWay = true)]
        void SendPrivate(string from, string to, string message);

        [OperationContract(IsOneWay = true)]
        void Leave(string name);
    }
}
