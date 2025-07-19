////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Logging.hpp>
#include <yq/core/LogFilter.hpp>

#define resourceAlert                  yAlert("resource")
#define resourceCritical               yCritical("resource")
#define resourceDebug                  yDebug("resource")
#define resourceError                  yError("resource")
#define resourceEmergency              yEmergency("resource")
#define resourceFatal                  yFatal("resource")
#define resourceInfo                   yInfo("resource")
#define resourceNotice                 yNotice("resource")
#define resourceWarning                yWarning("resource")

#define resourceFirstAlert(...)        yLogFirstAlert("resource", __VA_ARGS__)
#define resourceFirstCritical(...)     yLogFirstCritical("resource", __VA_ARGS__)
#define resourceFirstDebug(...)        yLogFirstDebug("resource", __VA_ARGS__)
#define resourceFirstError(...)        yLogFirstError("resource", __VA_ARGS__)
#define resourceFirstEmergency(...)    yLogFirstEmergency("resource", __VA_ARGS__)
#define resourceFirstFatal(...)        yLogFirstFatal("resource", __VA_ARGS__)
#define resourceFirstInfo(...)         yLogFirstInfo("resource", __VA_ARGS__)
#define resourceFirstNotice(...)       yLogFirstNotice("resource", __VA_ARGS__)
#define resourceFirstWarning(...)      yLogFirstWarning("resource", __VA_ARGS__)

#define resourceOnceAlert              yLogOnceAlert("resource")             
#define resourceOnceCritical           yLogOnceCritical("resource")          
#define resourceOnceDebug              yLogOnceDebug("resource")             
#define resourceOnceError              yLogOnceError("resource")             
#define resourceOnceEmergency          yLogOnceEmergency("resource")         
#define resourceOnceFatal              yLogOnceFatal("resource")             
#define resourceOnceInfo               yLogOnceInfo("resource")              
#define resourceOnceNotice             yLogOnceNotice("resource")            
#define resourceOnceWarning            yLogOnceWarning("resource")           
