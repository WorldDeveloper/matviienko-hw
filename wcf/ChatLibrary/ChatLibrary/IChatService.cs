using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ServiceModel;

namespace ChatLibrary
{
    [ServiceContract(SessionMode = SessionMode.Required,
       CallbackContract = typeof(IChatServiceCallback))]
    public interface IChatService
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
}
