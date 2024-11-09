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

#define pbxAlert                     yAlert("pbx")
#define pbxCritical                  yCritical("pbx")
#define pbxDebug                     yDebug("pbx")
#define pbxError                     yError("pbx")
#define pbxEmergency                 yEmergency("pbx")
#define pbxFatal                     yFatal("pbx")
#define pbxInfo                      yInfo("pbx")
#define pbxNotice                    yNotice("pbx")
#define pbxWarning                   yWarning("pbx")

#define pbxFirstAlert(...)           yLogFirstAlert("pbx", __VA_ARGS__)
#define pbxFirstCritical(...)        yLogFirstCritical("pbx", __VA_ARGS__)
#define pbxFirstDebug(...)           yLogFirstDebug("pbx", __VA_ARGS__)
#define pbxFirstError(...)           yLogFirstError("pbx", __VA_ARGS__)
#define pbxFirstEmergency(...)       yLogFirstEmergency("pbx", __VA_ARGS__)
#define pbxFirstFatal(...)           yLogFirstFatal("pbx", __VA_ARGS__)
#define pbxFirstInfo(...)            yLogFirstInfo("pbx", __VA_ARGS__)
#define pbxFirstNotice(...)          yLogFirstNotice("pbx", __VA_ARGS__)
#define pbxFirstWarning(...)         yLogFirstWarning("pbx", __VA_ARGS__)

#define pbxOnceAlert                 yLogOnceAlert("pbx")             
#define pbxOnceCritical              yLogOnceCritical("pbx")          
#define pbxOnceDebug                 yLogOnceDebug("pbx")             
#define pbxOnceError                 yLogOnceError("pbx")             
#define pbxOnceEmergency             yLogOnceEmergency("pbx")         
#define pbxOnceFatal                 yLogOnceFatal("pbx")             
#define pbxOnceInfo                  yLogOnceInfo("pbx")              
#define pbxOnceNotice                yLogOnceNotice("pbx")            
#define pbxOnceWarning               yLogOnceWarning("pbx")       
