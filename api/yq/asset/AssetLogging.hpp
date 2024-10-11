////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Logging.hpp>
#include <yq/core/LogFilter.hpp>

#define assetAlert                  yAlert("asset")
#define assetCritical               yCritical("asset")
#define assetDebug                  yDebug("asset")
#define assetError                  yError("asset")
#define assetEmergency              yEmergency("asset")
#define assetFatal                  yFatal("asset")
#define assetInfo                   yInfo("asset")
#define assetNotice                 yNotice("asset")
#define assetWarning                yWarning("asset")

#define assetFirstAlert(...)        yLogFirstAlert("asset", __VA_ARGS__)
#define assetFirstCritical(...)     yLogFirstCritical("asset", __VA_ARGS__)
#define assetFirstDebug(...)        yLogFirstDebug("asset", __VA_ARGS__)
#define assetFirstError(...)        yLogFirstError("asset", __VA_ARGS__)
#define assetFirstEmergency(...)    yLogFirstEmergency("asset", __VA_ARGS__)
#define assetFirstFatal(...)        yLogFirstFatal("asset", __VA_ARGS__)
#define assetFirstInfo(...)         yLogFirstInfo("asset", __VA_ARGS__)
#define assetFirstNotice(...)       yLogFirstNotice("asset", __VA_ARGS__)
#define assetFirstWarning(...)      yLogFirstWarning("asset", __VA_ARGS__)

#define assetOnceAlert              yLogOnceAlert("asset")             
#define assetOnceCritical           yLogOnceCritical("asset")          
#define assetOnceDebug              yLogOnceDebug("asset")             
#define assetOnceError              yLogOnceError("asset")             
#define assetOnceEmergency          yLogOnceEmergency("asset")         
#define assetOnceFatal              yLogOnceFatal("asset")             
#define assetOnceInfo               yLogOnceInfo("asset")              
#define assetOnceNotice             yLogOnceNotice("asset")            
#define assetOnceWarning            yLogOnceWarning("asset")           
