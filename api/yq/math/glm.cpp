////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "glm_types.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/core/StreamOps.hpp>
#include <yq/meta/Init.hpp>
#include <sstream>
#include <log4cpp/CategoryStream.hh>

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

//  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

yq::Stream& operator<<(yq::Stream&out, const glm::vec2&v)
{
    return out << "(" << v.x << "," << v.y << ")";
}

yq::Stream& operator<<(yq::Stream&out, const glm::vec3&v)
{
    return out << "(" << v.x << "," << v.y << "," << v.z << ")";
}

yq::Stream& operator<<(yq::Stream&out, const glm::vec4&v)
{
    return out << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
}

yq::Stream& operator<<(yq::Stream&out, const glm::dvec2&v)
{
    return out << "(" << v.x << "," << v.y << ")";
}

yq::Stream& operator<<(yq::Stream&out, const glm::dvec3&v)
{
    return out << "(" << v.x << "," << v.y << "," << v.z << ")";
}

yq::Stream& operator<<(yq::Stream&out, const glm::dvec4&v)
{
    return out << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
}

yq::Stream& operator<<(yq::Stream&out, const glm::mat2&v)
{
    out << '[';
    out << '[' << v[0][0] << ',' << v[1][0] << ']';
    out << '[' << v[0][1] << ',' << v[1][1] << ']';
    out << ']';
    return out;
}

yq::Stream& operator<<(yq::Stream&out, const glm::mat3&v)
{
    out << '[';
    out << '[' << v[0][0] << ',' << v[1][0] << ',' << v[2][0] << ']';
    out << '[' << v[0][1] << ',' << v[1][1] << ',' << v[2][1] << ']';
    out << '[' << v[0][2] << ',' << v[1][2] << ',' << v[2][2] << ']';
    out << ']';
    return out;
}

yq::Stream& operator<<(yq::Stream&out, const glm::mat4&v)
{
    out << '[';
    out << '[' << v[0][0] << ',' << v[1][0] << ',' << v[2][0] << ',' << v[3][0] << ']';
    out << '[' << v[0][1] << ',' << v[1][1] << ',' << v[2][1] << ',' << v[3][1] << ']';
    out << '[' << v[0][2] << ',' << v[1][2] << ',' << v[2][2] << ',' << v[3][2] << ']';
    out << '[' << v[0][3] << ',' << v[1][3] << ',' << v[2][3] << ',' << v[3][3] << ']';
    out << ']';
    return out;
}

yq::Stream& operator<<(yq::Stream&out, const glm::dmat2&v)
{
    out << '[';
    out << '[' << v[0][0] << ',' << v[1][0] << ']';
    out << '[' << v[0][1] << ',' << v[1][1] << ']';
    out << ']';
    return out;
}

yq::Stream& operator<<(yq::Stream&out, const glm::dmat3&v)
{
    out << '[';
    out << '[' << v[0][0] << ',' << v[1][0] << ',' << v[2][0] << ']';
    out << '[' << v[0][1] << ',' << v[1][1] << ',' << v[2][1] << ']';
    out << '[' << v[0][2] << ',' << v[1][2] << ',' << v[2][2] << ']';
    out << ']';
    return out;
}

yq::Stream& operator<<(yq::Stream&out, const glm::dmat4&v)
{
    out << '[';
    out << '[' << v[0][0] << ',' << v[1][0] << ',' << v[2][0] << ',' << v[3][0] << ']';
    out << '[' << v[0][1] << ',' << v[1][1] << ',' << v[2][1] << ',' << v[3][1] << ']';
    out << '[' << v[0][2] << ',' << v[1][2] << ',' << v[2][2] << ',' << v[3][2] << ']';
    out << '[' << v[0][3] << ',' << v[1][3] << ',' << v[2][3] << ',' << v[3][3] << ']';
    out << ']';
    return out;
}

//  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

std::ostringstream& operator<<(std::ostringstream&out, const glm::vec2&v)
{
    out << "(" << v.x << "," << v.y << ")";
    return out;
}

std::ostringstream& operator<<(std::ostringstream&out, const glm::vec3&v)
{
    out << "(" << v.x << "," << v.y << "," << v.z << ")";
    return out;
}

std::ostringstream& operator<<(std::ostringstream&out, const glm::vec4&v)
{
    out << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
    return out;
}

std::ostringstream& operator<<(std::ostringstream&out, const glm::dvec2&v)
{
    out << "(" << v.x << "," << v.y << ")";
    return out;
}

std::ostringstream& operator<<(std::ostringstream&out, const glm::dvec3&v)
{
    out << "(" << v.x << "," << v.y << "," << v.z << ")";
    return out;
}

std::ostringstream& operator<<(std::ostringstream&out, const glm::dvec4&v)
{
    out << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
    return out;
}

std::ostringstream& operator<<(std::ostringstream&out, const glm::mat2&v)
{
    out << "[";
    out << "[" << v[0][0] << "," << v[1][0] << "]";
    out << "[" << v[0][1] << "," << v[1][1] << "]";
    out << "]";
    return out;
}

std::ostringstream& operator<<(std::ostringstream&out, const glm::mat3&v)
{
    out << "[";
    out << "[" << v[0][0] << "," << v[1][0] << "," << v[2][0] << "]";
    out << "[" << v[0][1] << "," << v[1][1] << "," << v[2][1] << "]";
    out << "[" << v[0][2] << "," << v[1][2] << "," << v[2][2] << "]";
    out << "]";
    return out;
}

std::ostringstream& operator<<(std::ostringstream&out, const glm::mat4&v)
{
    out << "[";
    out << "[" << v[0][0] << "," << v[1][0] << "," << v[2][0] << "," << v[3][0] << "]";
    out << "[" << v[0][1] << "," << v[1][1] << "," << v[2][1] << "," << v[3][1] << "]";
    out << "[" << v[0][2] << "," << v[1][2] << "," << v[2][2] << "," << v[3][2] << "]";
    out << "[" << v[0][3] << "," << v[1][3] << "," << v[2][3] << "," << v[3][3] << "]";
    out << "]";
    return out;
}

std::ostringstream& operator<<(std::ostringstream&out, const glm::dmat2&v)
{
    out << "[";
    out << "[" << v[0][0] << "," << v[1][0] << "]";
    out << "[" << v[0][1] << "," << v[1][1] << "]";
    out << "]";
    return out;
}

std::ostringstream& operator<<(std::ostringstream&out, const glm::dmat3&v)
{
    out << "[";
    out << "[" << v[0][0] << "," << v[1][0] << "," << v[2][0] << "]";
    out << "[" << v[0][1] << "," << v[1][1] << "," << v[2][1] << "]";
    out << "[" << v[0][2] << "," << v[1][2] << "," << v[2][2] << "]";
    out << "]";
    return out;
}

std::ostringstream& operator<<(std::ostringstream&out, const glm::dmat4&v)
{
    out << "[";
    out << "[" << v[0][0] << "," << v[1][0] << "," << v[2][0] << "," << v[3][0] << "]";
    out << "[" << v[0][1] << "," << v[1][1] << "," << v[2][1] << "," << v[3][1] << "]";
    out << "[" << v[0][2] << "," << v[1][2] << "," << v[2][2] << "," << v[3][2] << "]";
    out << "[" << v[0][3] << "," << v[1][3] << "," << v[2][3] << "," << v[3][3] << "]";
    out << "]";
    return out;
}

//  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&out, const glm::vec2&v)
{
    return out << "(" << v.x << "," << v.y << ")";
}

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&out, const glm::vec3&v)
{
    return out << "(" << v.x << "," << v.y << "," << v.z << ")";
}

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&out, const glm::vec4&v)
{
    return out << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
}

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&out, const glm::dvec2&v)
{
    return out << "(" << v.x << "," << v.y << ")";
}

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&out, const glm::dvec3&v)
{
    return out << "(" << v.x << "," << v.y << "," << v.z << ")";
}

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&out, const glm::dvec4&v)
{
    return out << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
}

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&out, const glm::mat2&v)
{
    out << '[';
    out << '[' << v[0][0] << ',' << v[1][0] << ']';
    out << '[' << v[0][1] << ',' << v[1][1] << ']';
    out << ']';
    return out;
}

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&out, const glm::mat3&v)
{
    out << '[';
    out << '[' << v[0][0] << ',' << v[1][0] << ',' << v[2][0] << ']';
    out << '[' << v[0][1] << ',' << v[1][1] << ',' << v[2][1] << ']';
    out << '[' << v[0][2] << ',' << v[1][2] << ',' << v[2][2] << ']';
    out << ']';
    return out;
}

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&out, const glm::mat4&v)
{
    out << '[';
    out << '[' << v[0][0] << ',' << v[1][0] << ',' << v[2][0] << ',' << v[3][0] << ']';
    out << '[' << v[0][1] << ',' << v[1][1] << ',' << v[2][1] << ',' << v[3][1] << ']';
    out << '[' << v[0][2] << ',' << v[1][2] << ',' << v[2][2] << ',' << v[3][2] << ']';
    out << '[' << v[0][3] << ',' << v[1][3] << ',' << v[2][3] << ',' << v[3][3] << ']';
    out << ']';
    return out;
}

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&out, const glm::dmat2&v)
{
    out << '[';
    out << '[' << v[0][0] << ',' << v[1][0] << ']';
    out << '[' << v[0][1] << ',' << v[1][1] << ']';
    out << ']';
    return out;
}

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&out, const glm::dmat3&v)
{
    out << '[';
    out << '[' << v[0][0] << ',' << v[1][0] << ',' << v[2][0] << ']';
    out << '[' << v[0][1] << ',' << v[1][1] << ',' << v[2][1] << ']';
    out << '[' << v[0][2] << ',' << v[1][2] << ',' << v[2][2] << ']';
    out << ']';
    return out;
}

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&out, const glm::dmat4&v)
{
    out << '[';
    out << '[' << v[0][0] << ',' << v[1][0] << ',' << v[2][0] << ',' << v[3][0] << ']';
    out << '[' << v[0][1] << ',' << v[1][1] << ',' << v[2][1] << ',' << v[3][1] << ']';
    out << '[' << v[0][2] << ',' << v[1][2] << ',' << v[2][2] << ',' << v[3][2] << ']';
    out << '[' << v[0][3] << ',' << v[1][3] << ',' << v[2][3] << ',' << v[3][3] << ']';
    out << ']';
    return out;
}
