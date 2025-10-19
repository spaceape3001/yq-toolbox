////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq/meta/Meta.hpp>
#include <yq/math/utility.hpp>
#include <yq/math/tolerance/Absolute.hpp>
#include <yq/coord/Geodetic3.hpp>
#include <yq/coord/ecef/ECEFPosition.hpp>
#include <yq/coord/ecef/ECEFVector.hpp>
#include <yq/earth/wgs84.hpp>
#include <yq/vector/Vector3.hxx>
#include <yq/core/Logging.hpp>
#include <numbers>

namespace ut = boost::ut;

using namespace ut;
using namespace yq;

    
int main()
{
    log_to_std_output();
    Meta::freeze();
    
    "down/up"_test = []{
        static constexpr const double kHRt2 = 0.5*std::numbers::sqrt2_v<double>;
        static constexpr const double kHRt3 = 0.5*std::numbers::sqrt3_v<double>;

        static const struct {
            unit::Radian    latitude, longitude;
            unit::Meter     altitude;
            double          ex, ey, ez;
        } kCases[] = {
            {   0._deg, 0._deg, 0._m, -1., 0., 0. },
            {   0._deg, 30._deg, 0._m, -kHRt3, -0.5, 0. },
            {   0._deg, 45._deg, 0._m, -kHRt2, -kHRt2, 0. },
            {   0._deg, 90._deg, 0._m, 0., -1., 0. },
            {   0._deg, 135._deg, 0._m, kHRt2, -kHRt2, 0. },
            {   0._deg, 180._deg, 0._m, 1., 0., 0. },
            {   0._deg, -90._deg, 0._m, 0., 1., 0. },
            {   0._deg, -45._deg, 0._m, -kHRt2, kHRt2, 0. },
            {   0._deg, -135._deg, 0._m, kHRt2, kHRt2, 0. },
            {  30._deg, 0._deg, 0._m, -kHRt3, 0.0, -0.5 },
            {  90._deg, 0._deg, 0._m, 0., 0., -1. },
            { -90._deg, 0._deg, 0._m, 0., 0., 1. }
        };
        
        const auto& cm  = wgs84();
        Absolute    tol(1e-6);
        
        for(auto& k : kCases){
            Geodetic3RM     geo{ k.latitude, k.longitude, k.altitude };
            ECEFVector      down    = cm.down(geo);
            
            expect(true == is_close(tol, down, k.ex, k.ey, k.ez));
            
            ECEFVector      up      = cm.up(geo);
            expect(true == is_close(tol, up, -k.ex, -k.ey, -k.ez));

            ECEFPosition    pos = cm.position(geo);
            down                = cm.down(pos);
            up                  = cm.up(pos);
            //expect(true == is_close(tol, down, k.ex, k.ey, k.ez));
            //expect(true == is_close(tol, up, -k.ex, -k.ey, -k.ez));
        }
    };

    "position/geodetic"_test = []{
        static constexpr const double kHRt2 = 0.5*std::numbers::sqrt2_v<double>;
        static constexpr const double kHRt3 = 0.5*std::numbers::sqrt3_v<double>;
        
        static constexpr const unit::Meter a  = 6378137.0_m;

        static const struct {
            unit::Degree    latitude, longitude;
            unit::Meter     altitude;
            unit::Meter     x, y, z;
        } kCases[] = {
            // first... equatorial points
            { 0._deg, 0._deg, 0._m, a, 0., 0. },
            { 0._deg, 30._deg, 0._m,   kHRt3*a, 0.5*a, 0. },
            { 0._deg, 45._deg, 0._m,   kHRt2*a, kHRt2*a, 0. },
            { 0._deg, 135._deg, 0._m,  -kHRt2*a, kHRt2*a, 0. },
            { 0._deg, -30._deg, 0._m,   kHRt3*a, -0.5*a, 0. },
            { 0._deg, -45._deg, 0._m,   kHRt2*a, -kHRt2*a, 0. },
            { 0._deg, -135._deg, 0._m,  kHRt2*a, -kHRt2*a, 0. },
            
            // cases from the WGS84 documentation
            { 38.80305456_deg, 255.47540844_deg, 1911.755, -1248.597295_km, -4819.433239_km, 3976.500175_km },  // colorado springs
            { -7.95132970_deg, 345.58786950_deg, 106.558, 6118.524122_km, -1572.350853_km, -876.463990_km }     // ascension island
        };

        const auto& cm  = wgs84();
        Absolute    tolX(1e-3_m);
        Absolute    tolA(1e-6);

        for(auto& k : kCases){
            unit::Degree        lo  = wrap(k.longitude, -180., 180.);
            Geodetic3RM         geo = { k.latitude, k.longitude, k.altitude };
            ECEFPosition        posX(k.x, k.y, k.z);
            ECEFPosition        pos = cm.position(geo);
            
           // yInfo() << "wgs84 [" << pos << " difference]: " << (pos-posX).length().value;
            
            expect(true == is_close(tolX, pos,  posX));
            
            Geodetic3RM         geo2    = cm.geodetic(posX);
            expect(true == is_close(tolA, geo2.latitude, (unit::Radian) k.latitude));
            expect(true == is_close(tolA, geo2.longitude, (unit::Radian) lo));
            expect(true == is_close(tolX, geo2.altitude, k.altitude));
        }

    };

    return ut::cfg<>.run();
}

