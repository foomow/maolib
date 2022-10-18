#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <sstream>
#include <iterator>
#include <stdio.h>
#include <mutex>

#include "../maolib_logger/maolib_logger.h"
#include "../maolib_json/maolib_json.h"
#include "../maolib_socket/maolib_socket.h"

using namespace std;
namespace maolib
{
    namespace redis
    {
        class redis_client
        {
        public:
            redis_client(string host, int port = 6379);
            bool ConnectCmd();
            bool ConnectSub();
            bool CloseCmd();
            bool CloseSub();
            bool PSubscribe(string pattern,void (*cb)(Json)=nullptr);
            maolib::json::Json ExcuteCommand(string cmd);
            void receive_thread();

        private:
            bool IsCmdConnected;
            bool IsSubConnected;
            thread* recv_thd;
            string host_;
            int port_;
            int socket_cmd_;
            int socket_sub_;
            std::mutex *requestlock;
            maolib::json::Json receiveJson(int socket_);
            maolib::json::Json receiveSimpleString(int socket_);
            maolib::json::Json receiveErrors(int socket_);
            maolib::json::Json receiveIntegers(int socket_);
            maolib::json::Json receiveBulkString(int socket_);
            maolib::json::Json receiveArray(int socket_);
            std::string replaceAll(std::string str, const std::string &replace, const std::string &with);
            std::string parserMessage(std::string cmd);
            void (*callback)(Json);
        };
    }
}