////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Logging.hpp>
#include <yq/core/LogFilter.hpp>

#define xgAlert                  yAlert("xg")
#define xgCritical               yCritical("xg")
#define xgDebug                  yDebug("xg")
#define xgError                  yError("xg")
#define xgEmergency              yEmergency("xg")
#define xgFatal                  yFatal("xg")
#define xgInfo                   yInfo("xg")
#define xgNotice                 yNotice("xg")
#define xgWarning                yWarning("xg")

#define xgFirstAlert(...)        yLogFirstAlert("xg", __VA_ARGS__)
#define xgFirstCritical(...)     yLogFirstCritical("xg", __VA_ARGS__)
#define xgFirstDebug(...)        yLogFirstDebug("xg", __VA_ARGS__)
#define xgFirstError(...)        yLogFirstError("xg", __VA_ARGS__)
#define xgFirstEmergency(...)    yLogFirstEmergency("xg", __VA_ARGS__)
#define xgFirstFatal(...)        yLogFirstFatal("xg", __VA_ARGS__)
#define xgFirstInfo(...)         yLogFirstInfo("xg", __VA_ARGS__)
#define xgFirstNotice(...)       yLogFirstNotice("xg", __VA_ARGS__)
#define xgFirstWarning(...)      yLogFirstWarning("xg", __VA_ARGS__)

#define xgOnceAlert              yLogOnceAlert("xg")             
#define xgOnceCritical           yLogOnceCritical("xg")          
#define xgOnceDebug              yLogOnceDebug("xg")             
#define xgOnceError              yLogOnceError("xg")             
#define xgOnceEmergency          yLogOnceEmergency("xg")         
#define xgOnceFatal              yLogOnceFatal("xg")             
#define xgOnceInfo               yLogOnceInfo("xg")              
#define xgOnceNotice             yLogOnceNotice("xg")            
#define xgOnceWarning            yLogOnceWarning("xg")           
