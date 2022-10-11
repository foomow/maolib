#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <sstream>
#include <iterator>
#include <stdio.h>
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <mutex>


#include "../maolib_logger/maolib_logger.h"
#include "../maolib_json/maolib_json.h"

using namespace std;
namespace maolib
{
    namespace redis
    {
        class RedisClient{
            public:
            RedisClient(string host,int port=6379);
            bool Connect();
            bool Close();
            maolib::json::Json ExcuteCommand(string cmd);
            private:
            bool IsConnected;
            string host_;
            int port_;
            int socket_desc_;
            std::mutex* requestlock;
            maolib::json::Json receiveJson();
            maolib::json::Json receiveSimpleString();
            maolib::json::Json receiveErrors();
            maolib::json::Json receiveIntegers();
            maolib::json::Json receiveBulkString();
            maolib::json::Json receiveArray();
        };
    }
}