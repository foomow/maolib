#include "maolib_redis.h"

using namespace std;
namespace maolib
{
    namespace redis
    {
        RedisClient::RedisClient(string host, int port) : host_(host), port_(port), IsConnected(false), socket_desc_(-1),requestlock(new std::mutex())
        {
        }
        bool RedisClient::Connect()
        {
            if (IsConnected)
            {
                logger::error("client is connected");
                return false;
            }

            struct sockaddr_in server;

            socket_desc_ = socket(AF_INET, SOCK_STREAM, 0);
            if (socket_desc_ == -1)
            {
                logger::error("Could not create socket");
                return false;
            }

            server.sin_addr.s_addr = inet_addr(host_.c_str());
            server.sin_family = AF_INET;
            server.sin_port = htons(port_);

            if (connect(socket_desc_, (struct sockaddr *)&server, sizeof(server)) < 0)
            {
                logger::error("connect error");
                return false;
            }
            IsConnected = true;
            logger::info("Connected");
            return true;
        }
        bool RedisClient::Close()
        {
            if (!IsConnected)
            {
                logger::error("client is disconnected");
                return false;
            }
            close(socket_desc_);
            IsConnected = false;
            return true;
        }
        maolib::json::Json RedisClient::ExcuteCommand(string cmd)
        {
            requestlock->lock();
            if (!IsConnected)
            {
                logger::error("client is disconnected");
                requestlock->unlock();
                return maolib::json::Json();
            }
            std::istringstream stream(cmd);
            std::vector<std::string> segs((std::istream_iterator<std::string>(stream)),
                                          std::istream_iterator<std::string>());
            int seg_count = 0;
            string message = "";
            for (string seg : segs)
            {
                if (seg != "")
                {
                    message += "$" + to_string(seg.size()) + "\r\n" + seg + "\r\n";
                    seg_count++;
                }
            }
            message = "*" + to_string(seg_count) + "\r\n" + message;
            logger::debug("sending msg:%s", message.c_str());
            if (send(socket_desc_, message.c_str(), message.size(), 0) < 0)
            {
                logger::error("send failed");
                requestlock->unlock();
                return maolib::json::Json();
            }
            logger::debug("sent");
            maolib::json::Json ret=receiveJson();
            requestlock->unlock();
            return ret;
        }

        maolib::json::Json RedisClient::receiveJson()
        {
            char type;
            if (recv(socket_desc_, &type, 1, 0) != 1)
            {
                logger::error("receive failed");
                return maolib::json::Json();
            }
            switch (type)
            {
            case '+':
                return receiveSimpleString();
                break;
            case '-':
                return receiveErrors();
                break;
            case ':':
                return receiveIntegers();
                break;
            case '$':
                return receiveBulkString();
                break;
            case '*':
                return receiveArray();
                break;
            }
            return maolib::json::Json();
        }
        maolib::json::Json RedisClient::receiveSimpleString()
        {
            char recvBuff[1];
            int recvLen = 0;
            string response = "";
            do
            {
                recv(socket_desc_, recvBuff, 1, 0);
                response.append(recvBuff, 1);
                recvLen=response.size();
                if (recvLen > 2 && response[recvLen - 1] == '\n' && response[recvLen - 2] == '\r')
                {
                    response = response.substr(0, response.size() - 2);
                    break;
                }
            } while (recvLen > 0);
            return maolib::json::Json("\"" + response + "\"");
        }
        maolib::json::Json RedisClient::receiveErrors()
        {
            char recvBuff[1];
            int recvLen = 0;
            string response = "";
            do
            {
                recv(socket_desc_, recvBuff, 1, 0);
                response.append(recvBuff, 1);
                recvLen=response.size();
                if (recvLen > 2 && response[recvLen - 1] == '\n' && response[recvLen - 2] == '\r')
                {
                    response = response.substr(0, response.size() - 2);
                    break;
                }
            } while (recvLen > 0);
            return maolib::json::Json("\"" + response + "\"");
        }
        maolib::json::Json RedisClient::receiveIntegers()
        {
            char recvBuff[1];
            int recvLen = 0;
            string response = "";
            do
            {
                recv(socket_desc_, recvBuff, 1, 0);
                response.append(recvBuff, 1);
                recvLen=response.size();
                if (recvLen > 2 && response[recvLen - 1] == '\n' && response[recvLen - 2] == '\r')
                {
                    response = response.substr(0, response.size() - 2);
                    break;
                }
            } while (recvLen > 0);
            return maolib::json::Json(response);
        }
        maolib::json::Json RedisClient::receiveBulkString()
        {
            char recvBuff[1024];
            int recvLen = 0;
            int strLen=0;
            string response = "";
            do
            {
                recvLen = recv(socket_desc_, recvBuff, 1, 0);
                response.append(recvBuff, 1);
                int pos = response.find("\r\n");
                if (pos >= 0)
                {
                    string len_str = response.substr(0, pos + 1);
                    if (len_str == "-1")
                    {
                        return maolib::json::Json();
                    }
                    else
                    {
                        strLen=stoi(len_str)+2;
                        break;
                    }
                }
            } while (recvLen > 0);
            response = "";
            do
            {
                recvLen = recv(socket_desc_, recvBuff, strLen>1024?1024:strLen, 0);
                response.append(recvBuff, recvLen);
                strLen-=recvLen;
                if (strLen==0)
                {
                    response = response.substr(0, response.size() - 2);
                    break;
                }
            } while (recvLen > 0);
            return maolib::json::Json("\"" + response + "\"");
        }
        maolib::json::Json RedisClient::receiveArray()
        {
            char recvBuff[1];
            int recvLen = 0;
            string response = "";
            int array_size = 0;
            do
            {
                recvLen = recv(socket_desc_, recvBuff, 1, 0);
                response.append(recvBuff, recvLen);
                int pos = response.find("\r\n");
                if (pos >= 0)
                {
                    string len_str = response.substr(0, pos);
                    if (len_str == "-1")
                    {
                        return maolib::json::Json();
                    }
                    else
                    {
                        array_size = stoi(len_str);
                        response = response.substr(pos + 2);
                        break;
                    }
                }
            } while (recvLen > 0);
            json::Json ret = json::Json("[]");
            for (int i = 0; i < array_size; i++)
            {
                json::Json el=receiveJson();
                ret.Append(el);
            }
            return ret;
        }
    }
}