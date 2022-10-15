#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <sstream>
#include <iterator>
#include <stdio.h>
#include <unistd.h>
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
            bool Connect();
            bool Close();
            maolib::json::Json ExcuteCommand(string cmd);

        private:
            bool IsConnected;
            string host_;
            int port_;
            int socket_desc_;
            std::mutex *requestlock;
            maolib::json::Json receiveJson();
            maolib::json::Json receiveSimpleString();
            maolib::json::Json receiveErrors();
            maolib::json::Json receiveIntegers();
            maolib::json::Json receiveBulkString();
            maolib::json::Json receiveArray();
            std::string replaceAll(std::string str, const std::string &replace, const std::string &with);
        };
    }
}