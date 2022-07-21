////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    /*! \brief Greatest common divisor in template parameters
    */
    template <int, int> struct GCD;
    template <int A> struct GCD<A,0> { 
        static constexpr const int VALUE = A;
    };
    
    ;
    template <int A, int B> 
    struct GCD {
       static constexpr const int P         = (A>B)?(A-B):(B-A);
       static constexpr const int VALUE     = GCD<B,P>::VALUE;
    };

    //  This is a FIXED fraction
    template <int N, int D=(int) 1>
    struct FRACTION {
        static_assert(D != 0, "Denominator can never be zero!");
        
        static constexpr const int    NUM     = N;
        static constexpr const int    DEN     = D;
        static constexpr const int    CF      = GCD<N,D>::VALUE;
        static constexpr const int    PNUM    = N / CF;
        static constexpr const int    PDEN    = D / CF;
        static constexpr const int    SNUM = (D<0)?-PNUM:PNUM;
        static constexpr const int    SDEN = (D<0)?-PDEN:PDEN;
        
        using Simplified    = FRACTION<SNUM,SDEN>;
        
        template <class F>
        using Add = typename FRACTION<N*F::DEN+F::NUM*D,D*F::DEN>::Simplified;

        template <class F>
        using Sub = typename FRACTION<N*F::DEN-F::NUM*D,D*F::DEN>::Simplified;
        
        template <class F>
        using Mult = typename FRACTION<N*F::NUM,D*F::DEN>::Simplified;
        
        template <class F>
        using Div = typename FRACTION<N*F::DEN,D*F::NUM>::Simplified;
    };


    namespace dim {
        
        template <typename T>
        struct RESOLVE {
            static constexpr const bool defined = false;
            using Type  = T;
        };

        template <
            typename T,
            typename L,
            typename A,
            typename M,
            typename K,
            typename C,
            typename Q,
            typename I
        >
        struct DIM {
            typedef T   TimeD;
            typedef L   LengthD;
            typedef A   AngleD;
            typedef M   MassD;
            typedef K   TemperatureD;
            typedef C   CurrentD;
            typedef Q   MatterD;
            typedef I   IntensityD;

            template <class E> using _mult_impl_ = DIM<
                typename T::template Add<typename E::TimeD>,
                typename L::template Add<typename E::LengthD>,
                typename A::template Add<typename E::AngleD>,
                typename M::template Add<typename E::MassD>,
                typename K::template Add<typename E::TemperatureD>,
                typename C::template Add<typename E::CurrentD>,
                typename Q::template Add<typename E::MatterD>,
                typename I::template Add<typename E::IntensityD>
            >;
            
            template <class E> using _div_impl_ = DIM<
                typename T::template Sub<typename E::TimeD>,
                typename L::template Sub<typename E::LengthD>,
                typename A::template Sub<typename E::AngleD>,
                typename M::template Sub<typename E::MassD>,
                typename K::template Sub<typename E::TemperatureD>,
                typename C::template Sub<typename E::CurrentD>,
                typename Q::template Sub<typename E::MatterD>,
                typename I::template Sub<typename E::IntensityD>
            >;

            template <int N, int D> using _pow_impl_ = DIM<
                typename T::template Mult<FRACTION<N,D>>,
                typename L::template Mult<FRACTION<N,D>>,
                typename A::template Mult<FRACTION<N,D>>,
                typename M::template Mult<FRACTION<N,D>>,
                typename K::template Mult<FRACTION<N,D>>,
                typename C::template Mult<FRACTION<N,D>>,
                typename Q::template Mult<FRACTION<N,D>>,
                typename I::template Mult<FRACTION<N,D>>
            >;
            
            template <class E> using _mult_ = typename RESOLVE<_mult_impl_<E>> :: Type;
            template <class E> using _div_  = typename RESOLVE<_div_impl_<E>> :: Type;
            template <int N, int D> using _pow_ = typename RESOLVE<_pow_impl_<N,D>> :: Type;
        };
    
        template <int T, int L, int A, int M, int K, int C, int Q, int I> 
            using Dim = DIM<FRACTION<T>, FRACTION<L>, FRACTION<A>, FRACTION<M>, FRACTION<K>, FRACTION<C>, FRACTION<Q>, FRACTION<I>>;

        template <typename A, typename B> using _mult_      = typename A::template _mult_impl_<B>;
        template <typename A, typename B> using _div_       = typename A::template _div_impl_<B>;
        template <typename A, int N>      using _power_     = typename A::template _pow_impl_<N,1>;
        template <typename A>             using _inv_       = typename A::template _pow_impl_<-1,1>;
        template <typename A, int D>      using _root_      = typename A::template _pow_impl_<1,D>;
        template <typename A>             using _square_    = typename A::template _pow_impl_<2,1>;
        template <typename A>             using _cube_      = typename A::template _pow_impl_<3,1>;

#define YQ_DIM( dimName, ... )                                  \
        struct dimName : public __VA_ARGS__ {                   \
            static constexpr const char* szName   = #dimName;   \
        };                                                      \
        template <> struct RESOLVE<__VA_ARGS__ > {              \
            static constexpr const bool defined = false;        \
            using Type = dimName;                               \
        };                                                      

    
    YQ_DIM(None,         Dim<0,0,0,0,0,0,0,0>)
    YQ_DIM(Time,         Dim<1,0,0,0,0,0,0,0>)
    YQ_DIM(Length,       Dim<0,1,0,0,0,0,0,0>)
    YQ_DIM(Angle,        Dim<0,0,1,0,0,0,0,0>)
    YQ_DIM(Mass,         Dim<0,0,0,1,0,0,0,0>)
    YQ_DIM(Temperature,  Dim<0,0,0,0,1,0,0,0>)
    YQ_DIM(Current,      Dim<0,0,0,0,0,1,0,0>)
    YQ_DIM(Matter,       Dim<0,0,0,0,0,0,1,0>)
    YQ_DIM(Intensity,    Dim<0,0,0,0,0,0,0,1>)

    //  The permutations cannot be easily ordered, not even alphabetically because
    //  of the derived nature of the other units

    YQ_DIM(Frequency,                    _inv_<Time>)
    YQ_DIM(TimeSquare,                   _square_<Time>)
    YQ_DIM(PerLength,                    _inv_<Length>)
    YQ_DIM(Area,                         _square_<Length>)
    YQ_DIM(Volume,                       _cube_<Length>)
    YQ_DIM(SolidAngle,                   _square_<Angle>)
    YQ_DIM(PerAngle,                     _inv_<Angle>)
    YQ_DIM(PerMatter,                    _inv_<Matter>)

    YQ_DIM(Speed,                        _div_<Length,Time>)
    YQ_DIM(Acceleration,                 _div_<Speed,Time>)
    YQ_DIM(FrequencyRate,                _div_<Frequency,Time>)

    YQ_DIM(AngularVelocity,              _div_<Angle, Time>)
    YQ_DIM(AngularAcceleration,          _div_<AngularVelocity, Time>)

    YQ_DIM(AreaFlow,                     _div_<Area, Time>)
    YQ_DIM(VolumeFlow,                   _div_<Volume, Time>)
    YQ_DIM(VolumeFlowRate,               _div_<VolumeFlow, Time>)
    YQ_DIM(MassFlow,                     _div_<Mass, Time>)
    YQ_DIM(MassFlowRate,                 _div_<MassFlow, Time>)


    YQ_DIM(Force,                        _mult_<Mass,Acceleration>)
    YQ_DIM(ForceRate,                    _div_<Force,Time>)
    YQ_DIM(Energy,                       _mult_<Force,Length>)
    YQ_DIM(Impulse,                      _mult_<Force, Time> )
    YQ_DIM(Power,                        _div_<Energy, Time>)
    YQ_DIM(PowerDensity,                 _div_<Power,Volume>)
    YQ_DIM(SpecificEnergy,               _div_<Energy, Mass>)
    YQ_DIM(SpecificMolecularEnergy,      _div_<Energy,Matter>)
    YQ_DIM(Heat,                         _div_<Energy,Temperature>)
    YQ_DIM(SpecificHeat,                 _div_<SpecificEnergy, Temperature>)
    YQ_DIM(SpecificMolecularHeat,        _div_<SpecificMolecularEnergy, Temperature>)
    YQ_DIM(Pressure,                     _div_<Force,Area>)
    YQ_DIM(LinearDensity,                _div_<Mass,Length>)
    YQ_DIM(ArealDensity,                 _div_<Mass,Area>)
    YQ_DIM(Density,                      _div_<Mass,Volume>)

    YQ_DIM(SpecificVolume,               _div_<Volume,Mass> )
    YQ_DIM(SpecificMass,                 _div_<Mass,Matter>)
    YQ_DIM(PowerArealDensity,            _div_<Power,Area>)
    YQ_DIM(RadiantIntensity,             _div_<Power,SolidAngle>)

    YQ_DIM(Charge,                       _mult_<Current,Time>   )
    YQ_DIM(Voltage,                      _div_<Power,Current> )
    YQ_DIM(ElectricField,                _div_<Voltage,Length> )
    YQ_DIM(Resistance,                   _div_<Voltage,Current> )
    YQ_DIM(Conductance,                  _inv_<Resistance>)
    YQ_DIM(Capacitance,                  _div_<Charge,Voltage>)
    YQ_DIM(MagneticFlux,                 _mult_<Voltage, Time>)
    YQ_DIM(Inductance,                   _div_<MagneticFlux, Current>)
    YQ_DIM(MagneticFluxDensity,          _div_<MagneticFlux,Area>)

    YQ_DIM(ThermalGradient,              _div_<Temperature,Length>)
    YQ_DIM(ChargeMolecularDensity,       _div_<Charge, Matter>)
    YQ_DIM(ThermalChange,                _div_<Temperature, Time>)
    YQ_DIM(Curvature,                    _div_<Length,Angle>)
    YQ_DIM(InverseCurvature,             _inv_<Curvature>)
    YQ_DIM(Torque,                       _div_<Energy,Angle>)
    
    YQ_DIM(LuminousFlux,                 _mult_<Intensity,SolidAngle>)
    YQ_DIM(Illuminance,                  _div_<LuminousFlux, Area>)
    YQ_DIM(CatalyticActivity,            _div_<Matter, Time>)
    YQ_DIM(Permeability,                 _div_<Inductance, Length>)
    YQ_DIM(Permittivity,                 _div_<Capacitance, Length>)
    YQ_DIM(Radiance,                     _div_<RadiantIntensity, Area>)
    YQ_DIM(PowerSolidAngleLinearDensity, _div_<RadiantIntensity, Length>)
    
#undef YQ_DIM    
    }

}
