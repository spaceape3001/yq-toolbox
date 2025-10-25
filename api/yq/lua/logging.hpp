////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Logging.hpp>
#include <yq/core/LogFilter.hpp>

#define luaAlert                  yAlert("lua")
#define luaCritical               yCritical("lua")
#define luaDebug                  yDebug("lua")
#define luaError                  yError("lua")
#define luaEmergency              yEmergency("lua")
#define luaFatal                  yFatal("lua")
#define luaInfo                   yInfo("lua")
#define luaNotice                 yNotice("lua")
#define luaWarning                yWarning("lua")

#define luaFirstAlert(...)        yLogFirstAlert("lua", __VA_ARGS__)
#define luaFirstCritical(...)     yLogFirstCritical("lua", __VA_ARGS__)
#define luaFirstDebug(...)        yLogFirstDebug("lua", __VA_ARGS__)
#define luaFirstError(...)        yLogFirstError("lua", __VA_ARGS__)
#define luaFirstEmergency(...)    yLogFirstEmergency("lua", __VA_ARGS__)
#define luaFirstFatal(...)        yLogFirstFatal("lua", __VA_ARGS__)
#define luaFirstInfo(...)         yLogFirstInfo("lua", __VA_ARGS__)
#define luaFirstNotice(...)       yLogFirstNotice("lua", __VA_ARGS__)
#define luaFirstWarning(...)      yLogFirstWarning("lua", __VA_ARGS__)

#define luaOnceAlert              yLogOnceAlert("lua")             
#define luaOnceCritical           yLogOnceCritical("lua")          
#define luaOnceDebug              yLogOnceDebug("lua")             
#define luaOnceError              yLogOnceError("lua")             
#define luaOnceEmergency          yLogOnceEmergency("lua")         
#define luaOnceFatal              yLogOnceFatal("lua")             
#define luaOnceInfo               yLogOnceInfo("lua")              
#define luaOnceNotice             yLogOnceNotice("lua")            
#define luaOnceWarning            yLogOnceWarning("lua")           
