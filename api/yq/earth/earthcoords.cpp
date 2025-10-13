////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>

using namespace yq;

#include "BNSDPosition.ipp"

#if 0
#include "BNSD.hpp"
#include "BSNU.hpp"
#include "ECEF.hpp"
#include "ECI.hpp"
#include "LENU.hpp"
#include "LNED.hpp"
#include "TENU.hpp"
#include "TNED.hpp"



YQ_TYPE_IMPLEMENT(yq::ECEFAcceleration)
YQ_TYPE_IMPLEMENT(yq::ECEFAngularAcceleration)
YQ_TYPE_IMPLEMENT(yq::ECEFAngularVelocity)
YQ_TYPE_IMPLEMENT(yq::ECEFDisplacement)
YQ_TYPE_IMPLEMENT(yq::ECEFForce)
YQ_TYPE_IMPLEMENT(yq::ECEFOrientation)
YQ_TYPE_IMPLEMENT(yq::ECEFPosition)
YQ_TYPE_IMPLEMENT(yq::ECEFRotation)
YQ_TYPE_IMPLEMENT(yq::ECEFTensor)
YQ_TYPE_IMPLEMENT(yq::ECEFVector)
YQ_TYPE_IMPLEMENT(yq::ECEFVelocity)

YQ_TYPE_IMPLEMENT(yq::ECIAcceleration)
YQ_TYPE_IMPLEMENT(yq::ECIAngularAcceleration)
YQ_TYPE_IMPLEMENT(yq::ECIAngularVelocity)
YQ_TYPE_IMPLEMENT(yq::ECIDisplacement)
YQ_TYPE_IMPLEMENT(yq::ECIForce)
YQ_TYPE_IMPLEMENT(yq::ECIOrientation)
YQ_TYPE_IMPLEMENT(yq::ECIPosition)
YQ_TYPE_IMPLEMENT(yq::ECIRotation)
YQ_TYPE_IMPLEMENT(yq::ECITensor)
YQ_TYPE_IMPLEMENT(yq::ECIVector)
YQ_TYPE_IMPLEMENT(yq::ECIVelocity)


namespace {
    void reg_earthcoords()
    {
    }


    YQ_INVOKE(reg_earthcoords();)
}


#endif
