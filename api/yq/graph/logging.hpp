////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Logging.hpp>
#include <yq/core/LogFilter.hpp>

#define graphAlert                    yAlert("graph")
#define graphCritical                 yCritical("graph")
#define graphDebug                    yDebug("graph")
#define graphError                    yError("graph")
#define graphEmergency                yEmergency("graph")
#define graphFatal                    yFatal("graph")
#define graphInfo                     yInfo("graph")
#define graphNotice                   yNotice("graph")
#define graphWarning                  yWarning("graph")

#define graphFirstAlert(...)          yLogFirstAlert("graph", __VA_ARGS__)
#define graphFirstCritical(...)       yLogFirstCritical("graph", __VA_ARGS__)
#define graphFirstDebug(...)          yLogFirstDebug("graph", __VA_ARGS__)
#define graphFirstError(...)          yLogFirstError("graph", __VA_ARGS__)
#define graphFirstEmergency(...)      yLogFirstEmergency("graph", __VA_ARGS__)
#define graphFirstFatal(...)          yLogFirstFatal("graph", __VA_ARGS__)
#define graphFirstInfo(...)           yLogFirstInfo("graph", __VA_ARGS__)
#define graphFirstNotice(...)         yLogFirstNotice("graph", __VA_ARGS__)
#define graphFirstWarning(...)        yLogFirstWarning("graph", __VA_ARGS__)
