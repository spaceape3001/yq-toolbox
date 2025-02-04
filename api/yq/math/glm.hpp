////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/config/glm.hpp>
#include <iosfwd>

namespace log4cpp { class CategoryStream; }
namespace yq { class Stream; }

std::ostringstream& operator<<(std::ostringstream&, const glm::vec2&);
std::ostringstream& operator<<(std::ostringstream&, const glm::vec3&);
std::ostringstream& operator<<(std::ostringstream&, const glm::vec4&);
std::ostringstream& operator<<(std::ostringstream&, const glm::dvec2&);
std::ostringstream& operator<<(std::ostringstream&, const glm::dvec3&);
std::ostringstream& operator<<(std::ostringstream&, const glm::dvec4&);
std::ostringstream& operator<<(std::ostringstream&, const glm::mat2&);
std::ostringstream& operator<<(std::ostringstream&, const glm::mat3&);
std::ostringstream& operator<<(std::ostringstream&, const glm::mat4&);
std::ostringstream& operator<<(std::ostringstream&, const glm::dmat2&);
std::ostringstream& operator<<(std::ostringstream&, const glm::dmat3&);
std::ostringstream& operator<<(std::ostringstream&, const glm::dmat4&);

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const glm::vec2&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const glm::vec3&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const glm::vec4&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const glm::dvec2&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const glm::dvec3&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const glm::dvec4&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const glm::mat2&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const glm::mat3&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const glm::mat4&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const glm::dmat2&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const glm::dmat3&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const glm::dmat4&);

yq::Stream& operator<<(yq::Stream&, const glm::vec2&);
yq::Stream& operator<<(yq::Stream&, const glm::vec3&);
yq::Stream& operator<<(yq::Stream&, const glm::vec4&);
yq::Stream& operator<<(yq::Stream&, const glm::dvec2&);
yq::Stream& operator<<(yq::Stream&, const glm::dvec3&);
yq::Stream& operator<<(yq::Stream&, const glm::dvec4&);
yq::Stream& operator<<(yq::Stream&, const glm::mat2&);
yq::Stream& operator<<(yq::Stream&, const glm::mat3&);
yq::Stream& operator<<(yq::Stream&, const glm::mat4&);
yq::Stream& operator<<(yq::Stream&, const glm::dmat2&);
yq::Stream& operator<<(yq::Stream&, const glm::dmat3&);
yq::Stream& operator<<(yq::Stream&, const glm::dmat4&);
