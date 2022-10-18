#pragma once
#include <iostream>
#include <list>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#include "maolib_json.h"
#define EXPAND(...) __VA_ARGS__
#define COUNTARG(                                                              \
    a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16,     \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, COUNT, ...)                                                 \
  COUNT

#define _ARGCOUNT(...)                                                        \
  EXPAND(COUNTARG(__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58,                    \
                  57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, \
                  42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, \
                  27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, \
                  12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))

#define __MCONCAT(a, b) __DOCONCAT(a, b)
#define __DOCONCAT(a, b) a##_##b

#define _EXPAND_ARGS(type, a, ...) EXPAND(_EXPAND_ARGS_##a(__VA_ARGS__))
#define _EXPAND_ARGS_2(a, ...) \
  _EXPAND_ARGS_1(a)            \
  EXPAND(_EXPAND_ARGS_1(__VA_ARGS__))
#define _EXPAND_ARGS_3(a, ...) \
  _EXPAND_ARGS_1(a)            \
  EXPAND(_EXPAND_ARGS_2(__VA_ARGS__))
#define _EXPAND_ARGS_4(a, ...) \
  _EXPAND_ARGS_1(a)            \
  EXPAND(_EXPAND_ARGS_3(__VA_ARGS__))
#define _EXPAND_ARGS_5(a, ...) \
  _EXPAND_ARGS_1(a)            \
  EXPAND(_EXPAND_ARGS_4(__VA_ARGS__))
#define _EXPAND_ARGS_6(a, ...) \
  _EXPAND_ARGS_1(a)            \
  EXPAND(_EXPAND_ARGS_5(__VA_ARGS__))
#define _EXPAND_ARGS_7(a, ...) \
  _EXPAND_ARGS_1(a)            \
  EXPAND(_EXPAND_ARGS_6(__VA_ARGS__))
#define _EXPAND_ARGS_8(a, ...) \
  _EXPAND_ARGS_1(a)            \
  EXPAND(_EXPAND_ARGS_7(__VA_ARGS__))
#define _EXPAND_ARGS_9(a, ...) \
  _EXPAND_ARGS_1(a)            \
  EXPAND(_EXPAND_ARGS_8(__VA_ARGS__))
#define _EXPAND_ARGS_10(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_9(__VA_ARGS__))
#define _EXPAND_ARGS_11(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_10(__VA_ARGS__))
#define _EXPAND_ARGS_12(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_11(__VA_ARGS__))
#define _EXPAND_ARGS_13(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_12(__VA_ARGS__))
#define _EXPAND_ARGS_14(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_13(__VA_ARGS__))
#define _EXPAND_ARGS_15(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_14(__VA_ARGS__))
#define _EXPAND_ARGS_16(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_15(__VA_ARGS__))
#define _EXPAND_ARGS_17(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_16(__VA_ARGS__))
#define _EXPAND_ARGS_18(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_17(__VA_ARGS__))
#define _EXPAND_ARGS_19(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_18(__VA_ARGS__))
#define _EXPAND_ARGS_20(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_19(__VA_ARGS__))
#define _EXPAND_ARGS_21(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_20(__VA_ARGS__))
#define _EXPAND_ARGS_22(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_21(__VA_ARGS__))
#define _EXPAND_ARGS_23(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_22(__VA_ARGS__))
#define _EXPAND_ARGS_24(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_23(__VA_ARGS__))
#define _EXPAND_ARGS_25(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_24(__VA_ARGS__))
#define _EXPAND_ARGS_26(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_25(__VA_ARGS__))
#define _EXPAND_ARGS_27(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_26(__VA_ARGS__))
#define _EXPAND_ARGS_28(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_27(__VA_ARGS__))
#define _EXPAND_ARGS_29(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_28(__VA_ARGS__))
#define _EXPAND_ARGS_30(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_29(__VA_ARGS__))
#define _EXPAND_ARGS_31(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_30(__VA_ARGS__))
#define _EXPAND_ARGS_32(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_31(__VA_ARGS__))
#define _EXPAND_ARGS_33(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_32(__VA_ARGS__))
#define _EXPAND_ARGS_34(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_33(__VA_ARGS__))
#define _EXPAND_ARGS_35(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_34(__VA_ARGS__))
#define _EXPAND_ARGS_36(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_35(__VA_ARGS__))
#define _EXPAND_ARGS_37(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_36(__VA_ARGS__))
#define _EXPAND_ARGS_38(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_37(__VA_ARGS__))
#define _EXPAND_ARGS_39(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_38(__VA_ARGS__))
#define _EXPAND_ARGS_40(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_39(__VA_ARGS__))
#define _EXPAND_ARGS_41(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_40(__VA_ARGS__))
#define _EXPAND_ARGS_42(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_41(__VA_ARGS__))
#define _EXPAND_ARGS_43(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_42(__VA_ARGS__))
#define _EXPAND_ARGS_44(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_43(__VA_ARGS__))
#define _EXPAND_ARGS_45(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_44(__VA_ARGS__))
#define _EXPAND_ARGS_46(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_45(__VA_ARGS__))
#define _EXPAND_ARGS_47(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_46(__VA_ARGS__))
#define _EXPAND_ARGS_48(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_47(__VA_ARGS__))
#define _EXPAND_ARGS_49(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_48(__VA_ARGS__))
#define _EXPAND_ARGS_50(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_49(__VA_ARGS__))
#define _EXPAND_ARGS_51(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_50(__VA_ARGS__))
#define _EXPAND_ARGS_52(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_51(__VA_ARGS__))
#define _EXPAND_ARGS_53(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_52(__VA_ARGS__))
#define _EXPAND_ARGS_54(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_53(__VA_ARGS__))
#define _EXPAND_ARGS_55(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_54(__VA_ARGS__))
#define _EXPAND_ARGS_56(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_55(__VA_ARGS__))
#define _EXPAND_ARGS_57(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_56(__VA_ARGS__))
#define _EXPAND_ARGS_58(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_57(__VA_ARGS__))
#define _EXPAND_ARGS_59(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_58(__VA_ARGS__))
#define _EXPAND_ARGS_60(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_59(__VA_ARGS__))
#define _EXPAND_ARGS_61(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_60(__VA_ARGS__))
#define _EXPAND_ARGS_62(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_61(__VA_ARGS__))
#define _EXPAND_ARGS_63(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_62(__VA_ARGS__))
#define _EXPAND_ARGS_64(a, ...) \
  _EXPAND_ARGS_1(a)             \
  EXPAND(_EXPAND_ARGS_63(__VA_ARGS__))

#define _EXPAND_ARGS_1(a)                                                             \
  if (typeid(entity->a) == typeid(int))                                               \
  {                                                                                   \
    *((int *)&entity->a) = json[#a].toInt();                                          \
  }                                                                                   \
  else if (typeid(entity->a) == typeid(std::string))                                  \
  {                                                                                   \
    ((std::string *)&entity->a)->clear();                                             \
    ((std::string *)&entity->a)->append(json[#a].toStdString());                      \
  }                                                                                   \
  else if (typeid(entity->a) == typeid(double))                                       \
  {                                                                                   \
    *((double *)&entity->a) = json[#a].toDouble();                                    \
  }                                                                                   \
  else if (typeid(entity->a) == typeid(long))                                         \
  {                                                                                   \
    *((long *)&entity->a) = json[#a].toLong();                                        \
  }                                                                                   \
  else if (typeid(entity->a) == typeid(long long))                                    \
  {                                                                                   \
    *((long long *)&entity->a) = json[#a].toLLong();                                  \
  }                                                                                   \
  else if (typeid(entity->a) == typeid(std::vector<int>))                             \
  {                                                                                   \
    ((std::vector<int> *)&entity->a)->clear();                                        \
    for (int i = 0; i < json[#a].Size(); i++)                                         \
    {                                                                                 \
      ((std::vector<int> *)&entity->a)->push_back(json[#a][i].toInt());               \
    }                                                                                 \
  }                                                                                   \
  else if (typeid(entity->a) == typeid(std::vector<double>))                          \
  {                                                                                   \
    ((std::vector<double> *)&entity->a)->clear();                                     \
    for (int i = 0; i < json[#a].Size(); i++)                                         \
    {                                                                                 \
      ((std::vector<double> *)&entity->a)->push_back(json[#a][i].toDouble());         \
    }                                                                                 \
  }                                                                                   \
  else if (typeid(entity->a) == typeid(std::vector<long>))                            \
  {                                                                                   \
    ((std::vector<long> *)&entity->a)->clear();                                       \
    for (int i = 0; i < json[#a].Size(); i++)                                         \
    {                                                                                 \
      ((std::vector<long> *)&entity->a)->push_back(json[#a][i].toLong());             \
    }                                                                                 \
  }                                                                                   \
  else if (typeid(entity->a) == typeid(std::vector<long long>))                       \
  {                                                                                   \
    ((std::vector<long long> *)&entity->a)->clear();                                  \
    for (int i = 0; i < json[#a].Size(); i++)                                         \
    {                                                                                 \
      ((std::vector<long long> *)&entity->a)->push_back(json[#a][i].toLLong());       \
    }                                                                                 \
  }                                                                                   \
  else if (typeid(entity->a) == typeid(std::vector<std::string>))                     \
  {                                                                                   \
    ((std::vector<std::string> *)&entity->a)->clear();                                \
    for (int i = 0; i < json[#a].Size(); i++)                                         \
    {                                                                                 \
      ((std::vector<std::string> *)&entity->a)->push_back(json[#a][i].toStdString()); \
    }                                                                                 \
  }

#define SETUP_DESERIALIZER(type, ...)                                        \
  static void deserialize_json_##type(maolib::json::Json json, type *entity) \
  {                                                                          \
    EXPAND(__MCONCAT(_EXPAND_ARGS, _ARGCOUNT(__VA_ARGS__))(__VA_ARGS__))     \
  }

#define DESERIALIZE(type, json, entity) deserialize_json_##type(json, entity)
