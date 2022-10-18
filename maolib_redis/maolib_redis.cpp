#include "maolib_redis.h"

using namespace std;
namespace maolib
{
    namespace redis
    {
        redis_client::redis_client(string host, int port) : host_(host), port_(port), IsSubConnected(false), socket_sub_(-1), IsCmdConnected(false), socket_cmd_(-1), requestlock(new std::mutex())
        {
        }
        bool redis_client::ConnectCmd()
        {
            if (IsCmdConnected)
            {
                logger::error("client is connected");
                return false;
            }
            socket_cmd_ = maolib::client_socket::connect(host_, port_);
            if (socket_cmd_ == -1)
            {
                logger::error("Could not create socket");
                return false;
            }
            IsCmdConnected = true;
            logger::info("command client Connected");
            return true;
        }
        bool redis_client::ConnectSub()
        {
            if (IsSubConnected)
            {
                logger::error("client is connected");
                return false;
            }
            socket_sub_ = maolib::client_socket::connect(host_, port_);
            if (socket_sub_ == -1)
            {
                logger::error("Could not create socket");
                return false;
            }
            IsSubConnected = true;
            logger::info("subscribe client Connected");
            recv_thd = new thread(&redis_client::receive_thread, this);
            return true;
        }
        bool redis_client::CloseCmd()
        {
            if (!IsCmdConnected)
            {
                logger::error("client is disconnected");
                return false;
            }
            maolib::client_socket::close_socket(socket_cmd_);
            IsCmdConnected = false;
            return true;
        }
        void redis_client::receive_thread()
        {
            while (IsSubConnected)
            {
                maolib::json::Json ret = receiveJson(socket_sub_);
                if (ret.getType() != J_NULL)
                    std::thread([](void (*cb)(Json), Json ret)
                                { (*cb)(ret); },
                                callback, ret)
                        .detach();
            }
        }
        bool redis_client::CloseSub()
        {
            if (!IsSubConnected)
            {
                logger::error("client is disconnected");
                return false;
            }
            IsSubConnected = false;
            maolib::client_socket::close_socket(socket_sub_);
            recv_thd->join();
            return true;
        }
        bool redis_client::PSubscribe(string pattern, void (*cb)(Json))
        {
            std::string cmd = "PSUBSCRIBE " + pattern;
            std::string message = parserMessage(cmd);
            if (maolib::client_socket::send(socket_sub_, message) < 0)
            {
                logger::error("subscribe failed");
                return false;
            }
            if (cb != nullptr)
                callback = cb;
            logger::debug("sent");
            return true;
        }
        maolib::json::Json redis_client::ExcuteCommand(string cmd)
        {
            requestlock->lock();
            if (!IsCmdConnected)
            {
                logger::error("client is disconnected");
                requestlock->unlock();
                return maolib::json::Json();
            }
            std::string message = parserMessage(cmd);
            logger::debug("sending msg:%s", message.c_str());
            if (maolib::client_socket::send(socket_cmd_, message) < 0)
            {
                logger::error("send failed");
                requestlock->unlock();
                return maolib::json::Json();
            }
            logger::debug("sent");
            maolib::json::Json ret = receiveJson(socket_cmd_);
            requestlock->unlock();
            return ret;
        }

        maolib::json::Json redis_client::receiveJson(int socket_)
        {
            char type;
            if (maolib::client_socket::recv(socket_, &type, 1) != 1)
            {
                if (socket_ == socket_sub_ && IsSubConnected != false)
                    logger::error("subscribe client receive failed");
                else if (socket_ == socket_cmd_ && IsCmdConnected != false)
                    logger::error("command client receive failed");
                return maolib::json::Json();
            }
            switch (type)
            {
            case '+':
                return receiveSimpleString(socket_);
                break;
            case '-':
                return receiveErrors(socket_);
                break;
            case ':':
                return receiveIntegers(socket_);
                break;
            case '$':
                return receiveBulkString(socket_);
                break;
            case '*':
                return receiveArray(socket_);
                break;
            }
            return maolib::json::Json();
        }
        maolib::json::Json redis_client::receiveSimpleString(int socket_)
        {
            char recvBuff[1];
            int recvLen = 0;
            string response = "";
            do
            {
                maolib::client_socket::recv(socket_, recvBuff, 1);
                response.append(recvBuff, 1);
                recvLen = response.size();
                if (recvLen > 2 && response[recvLen - 1] == '\n' && response[recvLen - 2] == '\r')
                {
                    response = response.substr(0, response.size() - 2);
                    break;
                }
            } while (recvLen > 0);
            response = replaceAll(response, "\\", "\\\\");
            response = replaceAll(response, "\"", "\\\"");
            return maolib::json::Json("\"" + response + "\"");
        }
        maolib::json::Json redis_client::receiveErrors(int socket_)
        {
            char recvBuff[1];
            int recvLen = 0;
            string response = "";
            do
            {
                maolib::client_socket::recv(socket_, recvBuff, 1);
                response.append(recvBuff, 1);
                recvLen = response.size();
                if (recvLen > 2 && response[recvLen - 1] == '\n' && response[recvLen - 2] == '\r')
                {
                    response = response.substr(0, response.size() - 2);
                    break;
                }
            } while (recvLen > 0);
            response = replaceAll(response, "\\", "\\\\");
            response = replaceAll(response, "\"", "\\\"");
            return maolib::json::Json("\"" + response + "\"");
        }
        maolib::json::Json redis_client::receiveIntegers(int socket_)
        {
            char recvBuff[1];
            int recvLen = 0;
            string response = "";
            do
            {
                maolib::client_socket::recv(socket_, recvBuff, 1);
                response.append(recvBuff, 1);
                recvLen = response.size();
                if (recvLen > 2 && response[recvLen - 1] == '\n' && response[recvLen - 2] == '\r')
                {
                    response = response.substr(0, response.size() - 2);
                    break;
                }
            } while (recvLen > 0);
            return maolib::json::Json(response);
        }
        maolib::json::Json redis_client::receiveBulkString(int socket_)
        {
            char recvBuff[1024];
            int recvLen = 0;
            int strLen = 0;
            string response = "";
            do
            {
                recvLen = maolib::client_socket::recv(socket_, recvBuff, 1);
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
                        strLen = stoi(len_str) + 2;
                        break;
                    }
                }
            } while (recvLen > 0);
            response = "";
            do
            {
                recvLen = maolib::client_socket::recv(socket_, recvBuff, strLen > 1024 ? 1024 : strLen);
                response.append(recvBuff, recvLen);
                strLen -= recvLen;
                if (strLen == 0)
                {
                    response = response.substr(0, response.size() - 2);
                    break;
                }
            } while (recvLen > 0);
            response = replaceAll(response, "\\", "\\\\");
            response = replaceAll(response, "\"", "\\\"");
            return maolib::json::Json("\"" + response + "\"");
        }
        maolib::json::Json redis_client::receiveArray(int socket_)
        {
            char recvBuff[1];
            int recvLen = 0;
            string response = "";
            int array_size = 0;
            do
            {
                recvLen = maolib::client_socket::recv(socket_, recvBuff, 1);
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
                json::Json el = receiveJson(socket_);
                ret.Append(el);
            }
            return ret;
        }
        std::string redis_client::replaceAll(std::string str,
                                             const std::string &replace,
                                             const std::string &with)
        {
            if (!replace.empty())
            {
                std::size_t pos = 0;
                while ((pos = str.find(replace, pos)) != std::string::npos)
                {
                    str.replace(pos, replace.length(), with);
                    pos += with.length();
                }
            }
            return str;
        }
        std::string redis_client::parserMessage(std::string cmd)
        {
            std::vector<std::string> segs;
            string seg_str = "";
            char quote = 0;
            for (char ch : cmd)
            {
                if (quote == 0)
                {
                    if (ch == ' ')
                    {
                        if (seg_str != "")
                        {
                            segs.push_back(seg_str);
                            seg_str = "";
                        }
                    }
                    else
                    {
                        if (ch == '\'' || ch == '\"')
                        {
                            quote = ch;
                        }
                        else
                        {
                            seg_str.push_back(ch);
                        }
                    }
                }
                else
                {
                    if (ch == quote)
                    {
                        if (seg_str != "")
                        {
                            segs.push_back(seg_str);
                            seg_str = "";
                        }
                        quote = 0;
                    }
                    else
                    {
                        seg_str.push_back(ch);
                    }
                }
            }
            if (seg_str != "")
            {
                segs.push_back(seg_str);
            }
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
            return message;
        }
    }
}