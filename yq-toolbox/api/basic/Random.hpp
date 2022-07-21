////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <cstdint>
#include <vector>

namespace yq {

    /*! \brief Random 64-bit number from the kernel
    */
    uint64_t        randU64();

    /*! \brief Basic Random number

        This produces a uniform random number between [0,1)
    */
    double      urand();

    /*! \brief Generates random number between two values
        \param minVal   minimum value
        \param maxVal   maximum value
        \return Returns a random value betwene the mininum up to (but not including) maxVal.
    */
    double      random(double minVal, double maxVal);

    /*! \brief Generates random number between two values
        \param minVal   minimum value
        \param maxVal   maximum value
        \return Returns a random value betwene the mininum up to (but not including) maxVal.
    */
    float       random(float minVal, float maxVal);

    /*! \brief Generates random number between two values
        \param minVal   minimum value
        \param maxVal   maximum value
        \return Returns a random value betwene the mininum up to (but not including) maxVal.
    */
    int8_t      random(int8_t minVal, int8_t maxVal);

    /*! \brief Generates random number between two values
        \param minVal   minimum value
        \param maxVal   maximum value
        \return Returns a random value betwene the mininum up to (but not including) maxVal.
    */
    int16_t     random(int16_t minVal, int16_t maxVal);

    /*! \brief Generates random number between two values
        \param minVal   minimum value
        \param maxVal   maximum value
        \return Returns a random value betwene the mininum up to (but not including) maxVal.
    */
    int32_t     random(int32_t minVal, int32_t maxVal);

    /*! \brief Generates random number between two values
        \note WARNING, this routine uses doubles, so for more than 53-bits, it's advised to use the getrandom() routine instead.
        \param minVal   minimum value
        \param maxVal   maximum value
        \return Returns a random value betwene the mininum up to (but not including) maxVal.
    */
    int64_t     random(int64_t minVal, int64_t maxVal);

    /*! \brief Generates random number between two values
        \param minVal   minimum value
        \param maxVal   maximum value
        \return Returns a random value betwene the mininum up to (but not including) maxVal.
    */
    uint8_t     random(uint8_t minVal, uint8_t maxVal);

    /*! \brief Generates random number between two values
        \param minVal   minimum value
        \param maxVal   maximum value
        \return Returns a random value betwene the mininum up to (but not including) maxVal.
    */
    uint16_t    random(uint16_t minVal, uint16_t maxVal);

    /*! \brief Generates random number between two values
        \param minVal   minimum value
        \param maxVal   maximum value
        \return Returns a random value betwene the mininum up to (but not including) maxVal.
    */
    uint32_t    random(uint32_t minVal, uint32_t maxVal);

    /*! \brief Generates random number between two values
        \note WARNING, this routine uses doubles, so for more than 53-bits, it's advised to use the getrandom() routine instead.
        \param minVal   minimum value
        \param maxVal   maximum value
        \return Returns a random value betwene the mininum up to (but not including) maxVal.
    */
    uint64_t    random(uint64_t minVal, uint64_t maxVal);

    /*! \brief Randomly selects vector element
        \param vec      The vector of items
        \param def      What to return if the vector is EMPTY
        \return An element from the vector.
    */
    template <typename T>
    T           random(const std::vector<T>& vec, T def=T())
    {
        if(vec.empty())
            return def;
        return vec[random(0, vec.size())];
    }
}
