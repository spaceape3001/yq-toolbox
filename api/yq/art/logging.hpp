////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Logging.hpp>
#include <yq/core/LogFilter.hpp>

#define artAlert                    yAlert("art")
#define artCritical                 yCritical("art")
#define artDebug                    yDebug("art")
#define artError                    yError("art")
#define artEmergency                yEmergency("art")
#define artFatal                    yFatal("art")
#define artInfo                     yInfo("art")
#define artNotice                   yNotice("art")
#define artWarning                  yWarning("art")

#define artFirstAlert(...)          yLogFirstAlert("art", __VA_ARGS__)
#define artFirstCritical(...)       yLogFirstCritical("art", __VA_ARGS__)
#define artFirstDebug(...)          yLogFirstDebug("art", __VA_ARGS__)
#define artFirstError(...)          yLogFirstError("art", __VA_ARGS__)
#define artFirstEmergency(...)      yLogFirstEmergency("art", __VA_ARGS__)
#define artFirstFatal(...)          yLogFirstFatal("art", __VA_ARGS__)
#define artFirstInfo(...)           yLogFirstInfo("art", __VA_ARGS__)
#define artFirstNotice(...)         yLogFirstNotice("art", __VA_ARGS__)
#define artFirstWarning(...)        yLogFirstWarning("art", __VA_ARGS__)
