////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <yq/coord/Geodetic3.hpp>
#include <yq/coord/ecef/ECEFPosition.hpp>
#include <yq/coord/ecef/ECEFVector.hpp>
#include <yq/core/Logging.hpp>
#include <yq/earth/wgs84.hpp>
#include <yq/meta/Meta.hpp>
#include <yq/math/utility.hpp>
#include <yq/math/tolerance/Absolute.hpp>
#include <yq/vector/Vector3.hxx>
#include <numbers>
#include <iomanip>

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
            { 0._deg, -135._deg, 0._m,  -kHRt2*a, -kHRt2*a, 0. },
            
            // cases from the WGS84 documentation
            { 38.80305456_deg, 255.47540844_deg, 1911.755, -1248.597295_km, -4819.433239_km, 3976.500175_km },  // colorado springs
            { -7.95132970_deg, 345.58786950_deg, 106.558, 6118.524122_km, -1572.350853_km, -876.463990_km },    // ascension island
            { -7.26984347_deg, 72.37092177_deg, -64.063, 1916.197142_km, 6029.999007_km, -801.737366_km }, // Diego Garcia
            { 8.72250074_deg, 167.73052625_deg, 39.927, -6160.884370_km, 1339.851965_km, 960.843071_km }, // Kwajalein
            { 21.56149086_deg, 201.76066922_deg, 426.077, -5511.980484_km, -2200.247093_km, 2329.480952_km }, // Hawaii
            { 28.48373800_deg, 279.42769549_deg, -24.005, 918.988120_km, -5534.552966_km, 3023.721377_km }, // Cape Canaveral
            { -34.72900041_deg, 138.64734499_deg, 38.155, -3939.182131_km, 3467.075376_km, -3613.220824_km }, // Australia
            { -34.57370168_deg, 301.48070059_deg, 48.747, 2745.499065_km, -4483.636591_km, -3599.054582_km }, // Argentina
            { 51.45374284_deg, 358.71610888_deg, 163.097, 3981.776642_km, -89.239095_km, 4965.284650_km }, // England
            { 26.20914020_deg, 50.60814451_deg, -13.872, 3633.910757_km, 4425.277729_km, 2799.862795_km }, // Bahrain
            { -0.21515762_deg, 281.50639169_deg, 2922.626, 1272.867310_km, -6252.772219_km, -23.801818_km }, // Ecuador
            { 38.92045032_deg, 282.93377525_deg, 59.098, 1112.168358_km, -4842.861664_km, 3985.487174_km }, // USNO (Annapolis)
            { 64.68794095_deg, 212.88703308_deg, 176.552, -2296.298410_km, -1484.804985_km, 5743.080107_km }, // Alaska Pre-2002 Quake
            { 64.68794025_deg, 212.88703366_deg, 176.570, -2296.298460_km, -1484.805050_km, 5743.080090_km }, // Alaska Post-2002 Quake
            { -41.27264851_deg, 174.77870673_deg, 46.902, -4780.787068_km, 436.877203_km, -4185.258942_km }, // New Zealand
            { -25.74634609_deg, 28.22403736_deg, 1416.405, 5066.232133_km, 2719.226969_km, -2754.392735_km }, // South Africa
            { 37.07756793_deg, 127.02403180_deg, 48.876, -3067.861732_km, 4067.639179_km, 3824.294063_km }, // South Korea
            { -17.57703053_deg, 210.39381438_deg, 99.927, -5246.403866_km, -3077.285554_km, -1913.839459_km } // Tahiti
        };

        const auto& cm  = wgs84();
        Absolute    tolX(1e-2_m);
        Absolute    tolA(1e-6);

        for(auto& k : kCases){
            unit::Degree        lo      = wrap(k.longitude, -180., 180.);
            Geodetic3RM         geo     = { k.latitude, k.longitude, k.altitude };
            ECEFPosition        posX(k.x, k.y, k.z);
            ECEFPosition        pos     = cm.position(geo);
            Geodetic3RM         geo2    = cm.geodetic(posX);
            
#if 0
yInfo() << std::setprecision(12) << 
           "\n"
           "inputs:\n"
           "  latitude>  " << k.latitude.value << "\n"
           "  longitude> " << k.longitude.value << "\n"
           "  altitude>  " << k.altitude.value << "\n"
           "  x>         " << k.x.value << "\n"
           "  y>         " << k.y.value << "\n"
           "  z>         " << k.z.value << "\n"
           "outputs:\n"
           "  x>         " << pos.x.value << "\n"
           "  y>         " << pos.y.value << "\n"
           "  z>         " << pos.z.value << "\n"
           "  latitude>  " << unit::Degree(geo2.latitude).value << "\n"
           "  longitude> " << unit::Degree(geo2.longitude).value << "\n"
           "  altitiude> " << geo.altitude.value
;
#endif
            
            expect(true == is_close(tolX, pos,  posX));
            expect(true == is_close(tolA, geo2.latitude, (unit::Radian) k.latitude));
            expect(true == is_close(tolA, geo2.longitude, (unit::Radian) lo));
            expect(true == is_close(tolX, geo2.altitude, k.altitude));
        }

    };

    return ut::cfg<>.run();
}

