////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Pose3.hpp"
#include <yq/strings.hpp>
#include <yq/basic/DelayInit.hpp>
#include <yq/meta/Init.hpp>

using namespace yq;

YQ_TYPE_IMPLEMENT(yq::Pose3D)
YQ_TYPE_IMPLEMENT(yq::Pose3F)

static void reg_pose3_math()
{
    {
        auto w = writer<Pose3D>();
        w.description("3D pos in double");
        w.property(szOrientation, &Pose3D::orientation).description(szOrientation_Pose).alias(szOri);
        w.property(szPosition, &Pose3D::position).description(szPosition_Pose).alias(szPos);
    }

    {
        auto w = writer<Pose3F>();
        w.description("3D pos in float");
        w.property(szOrientation, &Pose3F::orientation).description(szOrientation_Pose).alias(szOri);
        w.property(szPosition, &Pose3F::position).description(szPosition_Pose).alias(szPos);
    }
}

YQ_INVOKE(reg_pose3_math();)

#include "Pose3.hxx"
