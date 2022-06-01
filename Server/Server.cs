using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Server
{
    public class Server
    {
        private List<IPEndPoint> _Clients = new List<IPEndPoint>();

        private enum  PACKET_TYPE : byte
        {
            CONNECT = 0, PREPARE, HIT, RESETMAINBALL, END
        }

        private UdpClient _server;
        
        public void Start(int port)
        {
            var ip = GetLocalIPAddress();
            _server = new UdpClient(port, ip.AddressFamily);
            _server.BeginReceive(ReceiveCallback, null);
            Thread.Sleep(Timeout.Infinite);
        }

        private void ReceiveCallback(IAsyncResult result)
        {
            Console.WriteLine("Receivecallback");
            var endPoint = new IPEndPoint(0, 0);
            byte[] data = _server.EndReceive(result, ref endPoint);
            if (data.Length > 0)
            {
                byte type = data[0];
                switch (type)
                {
                    case (byte)PACKET_TYPE.CONNECT:
                    {
                        _Clients.Add(endPoint);
                        byte[] id = { (byte)_Clients.Count };
                        _server.Send(id, 1, endPoint);
                        break;
                    }
                    case (byte)PACKET_TYPE.PREPARE:
                    {
                        if(_Clients[0] == endPoint)
                        {
                            _server.Send(data, data.Length, _Clients[1]);
                        }
                        else
                        {
                            _server.Send(data, data.Length, _Clients[0]);
                        }
                        break;
                    }


                }
            }
            _server.BeginReceive(ReceiveCallback, null);
        }

        private IPAddress GetLocalIPAddress()
        {
            var host = Dns.GetHostEntry(Dns.GetHostName());
            foreach (var ip in host.AddressList)
            {
                if (ip.AddressFamily == AddressFamily.InterNetwork)
                {
                    return ip;
                }
            }
            throw new Exception("No network adapters with an IPv4 address in the system!");
        }
    }
}
