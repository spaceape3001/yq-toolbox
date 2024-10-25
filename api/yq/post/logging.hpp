////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Logging.hpp>
#include <yq/core/LogFilter.hpp>

#define postAlert                    yAlert("post")
#define postCritical                 yCritical("post")
#define postDebug                    yDebug("post")
#define postError                    yError("post")
#define postEmergency                yEmergency("post")
#define postFatal                    yFatal("post")
#define postInfo                     yInfo("post")
#define postNotice                   yNotice("post")
#define postWarning                  yWarning("post")

#define postFirstAlert(...)          yLogFirstAlert("post", __VA_ARGS__)
#define postFirstCritical(...)       yLogFirstCritical("post", __VA_ARGS__)
#define postFirstDebug(...)          yLogFirstDebug("post", __VA_ARGS__)
#define postFirstError(...)          yLogFirstError("post", __VA_ARGS__)
#define postFirstEmergency(...)      yLogFirstEmergency("post", __VA_ARGS__)
#define postFirstFatal(...)          yLogFirstFatal("post", __VA_ARGS__)
#define postFirstInfo(...)           yLogFirstInfo("post", __VA_ARGS__)
#define postFirstNotice(...)         yLogFirstNotice("post", __VA_ARGS__)
#define postFirstWarning(...)        yLogFirstWarning("post", __VA_ARGS__)

#define postOnceAlert                yLogOnceAlert("post")             
#define postOnceCritical             yLogOnceCritical("post")          
#define postOnceDebug                yLogOnceDebug("post")             
#define postOnceError                yLogOnceError("post")             
#define postOnceEmergency            yLogOnceEmergency("post")         
#define postOnceFatal                yLogOnceFatal("post")             
#define postOnceInfo                 yLogOnceInfo("post")              
#define postOnceNotice               yLogOnceNotice("post")            
#define postOnceWarning              yLogOnceWarning("post")       
