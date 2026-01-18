////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Logging.hpp>
#include <yq/core/LogFilter.hpp>

#define b3Alert                    yAlert("b3")
#define b3Critical                 yCritical("b3")
#define b3Debug                    yDebug("b3")
#define b3Error                    yError("b3")
#define b3Emergency                yEmergency("b3")
#define b3Fatal                    yFatal("b3")
#define b3Info                     yInfo("b3")
#define b3Notice                   yNotice("b3")
#define b3Warning                  yWarning("b3")

#define b3FirstAlert(...)          yLogFirstAlert("b3", __VA_ARGS__)
#define b3FirstCritical(...)       yLogFirstCritical("b3", __VA_ARGS__)
#define b3FirstDebug(...)          yLogFirstDebug("b3", __VA_ARGS__)
#define b3FirstError(...)          yLogFirstError("b3", __VA_ARGS__)
#define b3FirstEmergency(...)      yLogFirstEmergency("b3", __VA_ARGS__)
#define b3FirstFatal(...)          yLogFirstFatal("b3", __VA_ARGS__)
#define b3FirstInfo(...)           yLogFirstInfo("b3", __VA_ARGS__)
#define b3FirstNotice(...)         yLogFirstNotice("b3", __VA_ARGS__)
#define b3FirstWarning(...)        yLogFirstWarning("b3", __VA_ARGS__)
