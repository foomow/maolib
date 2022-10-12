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
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, COUNT, ...)                        \
  COUNT

#define _ARGCOUNT(...)                                                         \
  EXPAND(COUNTARG(__VA_ARGS__, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, \
                  87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73,  \
                  72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58,  \
                  57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43,  \
                  42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28,  \
                  27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13,  \
                  12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))

#define __MCONCAT(a, b) __DOCONCAT(a, b)
#define __DOCONCAT(a, b) a##_##b

#define _EXPAND_ARGS(type, a, ...) EXPAND(_EXPAND_ARGS_##a(__VA_ARGS__))
#define _EXPAND_ARGS_2(a, ...)                                                 \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_1(__VA_ARGS__))
#define _EXPAND_ARGS_3(a, ...)                                                 \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_2(__VA_ARGS__))
#define _EXPAND_ARGS_4(a, ...)                                                 \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_3(__VA_ARGS__))
#define _EXPAND_ARGS_5(a, ...)                                                 \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_4(__VA_ARGS__))
#define _EXPAND_ARGS_6(a, ...)                                                 \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_5(__VA_ARGS__))
#define _EXPAND_ARGS_7(a, ...)                                                 \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_6(__VA_ARGS__))
#define _EXPAND_ARGS_8(a, ...)                                                 \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_7(__VA_ARGS__))
#define _EXPAND_ARGS_9(a, ...)                                                 \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_8(__VA_ARGS__))
#define _EXPAND_ARGS_10(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_9(__VA_ARGS__))
#define _EXPAND_ARGS_11(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_10(__VA_ARGS__))
#define _EXPAND_ARGS_12(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_11(__VA_ARGS__))
#define _EXPAND_ARGS_13(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_12(__VA_ARGS__))
#define _EXPAND_ARGS_14(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_13(__VA_ARGS__))
#define _EXPAND_ARGS_15(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_14(__VA_ARGS__))
#define _EXPAND_ARGS_16(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_15(__VA_ARGS__))
#define _EXPAND_ARGS_17(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_16(__VA_ARGS__))
#define _EXPAND_ARGS_18(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_17(__VA_ARGS__))
#define _EXPAND_ARGS_19(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_18(__VA_ARGS__))
#define _EXPAND_ARGS_20(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_19(__VA_ARGS__))
#define _EXPAND_ARGS_21(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_20(__VA_ARGS__))
#define _EXPAND_ARGS_22(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_21(__VA_ARGS__))
#define _EXPAND_ARGS_23(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_22(__VA_ARGS__))
#define _EXPAND_ARGS_24(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_23(__VA_ARGS__))
#define _EXPAND_ARGS_25(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_24(__VA_ARGS__))
#define _EXPAND_ARGS_26(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_25(__VA_ARGS__))
#define _EXPAND_ARGS_27(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_26(__VA_ARGS__))
#define _EXPAND_ARGS_28(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_27(__VA_ARGS__))
#define _EXPAND_ARGS_29(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_28(__VA_ARGS__))
#define _EXPAND_ARGS_30(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_29(__VA_ARGS__))
#define _EXPAND_ARGS_31(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_30(__VA_ARGS__))
#define _EXPAND_ARGS_32(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_31(__VA_ARGS__))
#define _EXPAND_ARGS_33(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_32(__VA_ARGS__))
#define _EXPAND_ARGS_34(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_33(__VA_ARGS__))
#define _EXPAND_ARGS_35(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_34(__VA_ARGS__))
#define _EXPAND_ARGS_36(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_35(__VA_ARGS__))
#define _EXPAND_ARGS_37(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_36(__VA_ARGS__))
#define _EXPAND_ARGS_38(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_37(__VA_ARGS__))
#define _EXPAND_ARGS_39(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_38(__VA_ARGS__))
#define _EXPAND_ARGS_40(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_39(__VA_ARGS__))
#define _EXPAND_ARGS_41(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_40(__VA_ARGS__))
#define _EXPAND_ARGS_42(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_41(__VA_ARGS__))
#define _EXPAND_ARGS_43(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_42(__VA_ARGS__))
#define _EXPAND_ARGS_44(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_43(__VA_ARGS__))
#define _EXPAND_ARGS_45(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_44(__VA_ARGS__))
#define _EXPAND_ARGS_46(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_45(__VA_ARGS__))
#define _EXPAND_ARGS_47(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_46(__VA_ARGS__))
#define _EXPAND_ARGS_48(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_47(__VA_ARGS__))
#define _EXPAND_ARGS_49(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_48(__VA_ARGS__))
#define _EXPAND_ARGS_50(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_49(__VA_ARGS__))
#define _EXPAND_ARGS_51(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_50(__VA_ARGS__))
#define _EXPAND_ARGS_52(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_51(__VA_ARGS__))
#define _EXPAND_ARGS_53(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_52(__VA_ARGS__))
#define _EXPAND_ARGS_54(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_53(__VA_ARGS__))
#define _EXPAND_ARGS_55(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_54(__VA_ARGS__))
#define _EXPAND_ARGS_56(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_55(__VA_ARGS__))
#define _EXPAND_ARGS_57(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_56(__VA_ARGS__))
#define _EXPAND_ARGS_58(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_57(__VA_ARGS__))
#define _EXPAND_ARGS_59(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_58(__VA_ARGS__))
#define _EXPAND_ARGS_60(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_59(__VA_ARGS__))
#define _EXPAND_ARGS_61(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_60(__VA_ARGS__))
#define _EXPAND_ARGS_62(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_61(__VA_ARGS__))
#define _EXPAND_ARGS_63(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_62(__VA_ARGS__))
#define _EXPAND_ARGS_64(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_63(__VA_ARGS__))
#define _EXPAND_ARGS_65(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_64(__VA_ARGS__))
#define _EXPAND_ARGS_66(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_65(__VA_ARGS__))
#define _EXPAND_ARGS_67(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_66(__VA_ARGS__))
#define _EXPAND_ARGS_68(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_67(__VA_ARGS__))
#define _EXPAND_ARGS_69(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_68(__VA_ARGS__))
#define _EXPAND_ARGS_70(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_69(__VA_ARGS__))
#define _EXPAND_ARGS_71(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_70(__VA_ARGS__))
#define _EXPAND_ARGS_72(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_71(__VA_ARGS__))
#define _EXPAND_ARGS_73(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_72(__VA_ARGS__))
#define _EXPAND_ARGS_74(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_73(__VA_ARGS__))
#define _EXPAND_ARGS_75(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_74(__VA_ARGS__))
#define _EXPAND_ARGS_76(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_75(__VA_ARGS__))
#define _EXPAND_ARGS_77(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_76(__VA_ARGS__))
#define _EXPAND_ARGS_78(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_77(__VA_ARGS__))
#define _EXPAND_ARGS_79(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_78(__VA_ARGS__))
#define _EXPAND_ARGS_80(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_79(__VA_ARGS__))
#define _EXPAND_ARGS_81(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_80(__VA_ARGS__))
#define _EXPAND_ARGS_82(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_81(__VA_ARGS__))
#define _EXPAND_ARGS_83(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_82(__VA_ARGS__))
#define _EXPAND_ARGS_84(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_83(__VA_ARGS__))
#define _EXPAND_ARGS_85(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_84(__VA_ARGS__))
#define _EXPAND_ARGS_86(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_85(__VA_ARGS__))
#define _EXPAND_ARGS_87(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_86(__VA_ARGS__))
#define _EXPAND_ARGS_88(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_87(__VA_ARGS__))
#define _EXPAND_ARGS_89(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_88(__VA_ARGS__))
#define _EXPAND_ARGS_90(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_89(__VA_ARGS__))
#define _EXPAND_ARGS_91(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_90(__VA_ARGS__))
#define _EXPAND_ARGS_92(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_91(__VA_ARGS__))
#define _EXPAND_ARGS_93(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_92(__VA_ARGS__))
#define _EXPAND_ARGS_94(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_93(__VA_ARGS__))
#define _EXPAND_ARGS_95(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_94(__VA_ARGS__))
#define _EXPAND_ARGS_96(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_95(__VA_ARGS__))
#define _EXPAND_ARGS_97(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_96(__VA_ARGS__))
#define _EXPAND_ARGS_98(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_97(__VA_ARGS__))
#define _EXPAND_ARGS_99(a, ...)                                                \
  _EXPAND_ARGS_1(a) EXPAND(_EXPAND_ARGS_98(__VA_ARGS__))

#define _EXPAND_ARGS_1(a)                                                      \
   if (typeid(entity->a) == typeid(int)) {                                      \
    int source = json[#a].toInt();                         \
    void *dest = (void *)&entity->a;                                           \
    memcpy(dest, &source, sizeof(int));                                        \
  } else if (typeid(entity->a) == typeid(std::string)) {                       \
    std::string source = json[#a].toStdString();              \
    std::string *dest = (std::string *)&entity->a;                             \
    dest->clear();                                                             \
    dest->append(source);                                                      \
  } else if(typeid(entity->a) == typeid(std::vector<std::string>)){\
    QJsonArray arr=json[#a].toArray();\
    std::vector<std::string>* dest=reinterpret_cast<std::vector<std::string>*>(&entity->a);\
    for (auto el_ : arr)dest->push_back(el_.toString().toStdString());\
  } else if(typeid(entity->a) == typeid(std::vector<double>)){\
    QJsonArray arr=json[#a].toArray();\
    std::vector<double>* dest=reinterpret_cast<std::vector<double>*>(&entity->a);\
    for (auto el_ : arr)dest->push_back(el_.toDouble());\
  } else if(typeid(entity->a) == typeid(std::vector<int>)){\
    QJsonArray arr=json[#a].toArray();\
    std::vector<int>* dest=reinterpret_cast<std::vector<int>*>(&entity->a);\
    for (auto el_ : arr)dest->push_back(el_.toInt());\
  } else if (typeid(entity->a) == typeid(int32_t)) {                            \
    int32_t source = json[#a].toInt();                   \
    void *dest = (void *)&entity->a;                                           \
    memcpy(dest, &source, sizeof(int32_t));                                                            \
  }else if (typeid(entity->a) == typeid(bool)) {                            \
    bool source = json[#a].toBool();                   \
    void *dest = (void *)&entity->a;                                       \
    memcpy(dest, &source, sizeof(bool));                                                           \
  }else if (typeid(entity->a) == typeid(long long)) {                            \
    long long source = json[#a].toDouble();                   \
    void *dest = (void *)&entity->a;                                       \
    memcpy(dest, &source, sizeof(long long));                                                           \
  }else if (typeid(entity->a) == typeid(double)) {                            \
    double source = json[#a].toDouble();                   \
    double *dest = (double *)&entity->a;                                       \
    *dest = source;                                                            \
  }

#define SETUP_DESERIALIZER(type, ...)                                          \
  static void deserialize_json_##type(maolib::json::Json json, type *entity) {        \
    EXPAND(__MCONCAT(_EXPAND_ARGS, _ARGCOUNT(__VA_ARGS__))(__VA_ARGS__))       \
  }

#define DESERIALIZE(type, json, entity) deserialize_json_##type(json, entity)


