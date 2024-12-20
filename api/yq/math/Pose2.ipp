////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Pose2.hpp"

#include <yq/strings.hpp>
#include <yq/units.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>

#include "Pose2.hxx"

using namespace yq;

YQ_TYPE_IMPLEMENT(yq::Pose2D)
YQ_TYPE_IMPLEMENT(yq::Pose2F)

static void reg_pose2_math()
{
    {
        auto w = writer<Pose2D>();
        w.description("2D pos in double");
        w.property(szOrientation, &Pose2D::orientation).description(szOrientation_Pose).alias(szOri);
        w.property(szPosition, &Pose2D::position).description(szPosition_Pose).alias(szPos);
    }

    {
        auto w = writer<Pose2F>();
        w.description("2D pos in float");
        w.property(szOrientation, &Pose2F::orientation).description(szOrientation_Pose).alias(szOri);
        w.property(szPosition, &Pose2F::position).description(szPosition_Pose).alias(szPos);
    }
}

YQ_INVOKE(reg_pose2_math();)

