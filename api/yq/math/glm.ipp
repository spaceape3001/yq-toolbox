////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "glm_types.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/io/StreamOps.hpp>
#include <yq-toolbox/meta/Init.hpp>

using namespace yq;

YQ_TYPE_IMPLEMENT(glm::mat2)
YQ_TYPE_IMPLEMENT(glm::mat3)
YQ_TYPE_IMPLEMENT(glm::mat4)

YQ_TYPE_IMPLEMENT(glm::dmat2)
YQ_TYPE_IMPLEMENT(glm::dmat3)
YQ_TYPE_IMPLEMENT(glm::dmat4)

YQ_TYPE_IMPLEMENT(glm::vec1)
YQ_TYPE_IMPLEMENT(glm::vec2)
YQ_TYPE_IMPLEMENT(glm::vec3)
YQ_TYPE_IMPLEMENT(glm::vec4)

YQ_TYPE_IMPLEMENT(glm::dvec1)
YQ_TYPE_IMPLEMENT(glm::dvec2)
YQ_TYPE_IMPLEMENT(glm::dvec3)
YQ_TYPE_IMPLEMENT(glm::dvec4)

    
//  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

static void reg_glm_math () {

    {
        auto w = writer<glm::mat2>();
        w.description("GLM's 2x2 matrix in float");
    }

    {
        auto w = writer<glm::mat3>();
        w.description("GLM's 3x3 matrix in float");
    }

    {
        auto w = writer<glm::mat4>();
        w.description("GLM's 4x4 matrix in float");
    }

    {
        auto w = writer<glm::dmat2>();
        w.description("GLM's 2x2 matrix in double");
    }

    {
        auto w = writer<glm::dmat3>();
        w.description("GLM's 3x3 matrix in double");
    }

    {
        auto w = writer<glm::dmat4>();
        w.description("GLM's 4x4 matrix in double");
    }
    
    {
        auto w = writer<glm::vec2>();
        w.description("GLM's 2D vector in float");
    }
    
    {
        auto w = writer<glm::vec3>();
        w.description("GLM's 3D vector in float");
    }

    {
        auto w = writer<glm::vec4>();
        w.description("GLM's 4D vector in float");
    }

    {
        auto w = writer<glm::dvec2>();
        w.description("GLM's 2D vector in double");
    }
    
    {
        auto w = writer<glm::dvec3>();
        w.description("GLM's 3D vector in double");
    }

    {
        auto w = writer<glm::dvec4>();
        w.description("GLM's 4D vector in double");
    }
}

YQ_INVOKE(reg_glm_math();)

