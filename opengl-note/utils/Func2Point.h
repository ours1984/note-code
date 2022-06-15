#pragma once

#include <cstdint>

template <uintptr_t uniqueSignature,typename T> struct Callback;
 
//特例化
template <uintptr_t uniqueSignature,typename Ret, typename... Params>
struct Callback<uniqueSignature,Ret(Params...)>
{
    static Ret callback(Params... args)  //对应静态成员函数
    {
        return func(args...);
    }
    static inline std::function<Ret(Params...)> func; //对应静态函数对象
};

#define REGISTER_CALLBACK_CLASS_LINE(name,line,args)                \
struct name : public Callback<line,args> {}                     

#define REGISTER_CALLBACK_CLASS(name,args) REGISTER_CALLBACK_CLASS_LINE(name,__LINE__,args)

