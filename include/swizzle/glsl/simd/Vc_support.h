#pragma once

#include <vc/vector.h>
#include <swizzle/glsl/naive/vector_helper.h>

namespace swizzle
{
    namespace glsl
    {
        typedef Vc::float_v float_v;

        template <size_t Size>
        struct vector_helper<float_v, Size>
        {
            //! These can be incomplete types at this point.
            typedef std::array<float_v::VectorType::Base, Size> data_type;

            template <size_t... indices>
            struct proxy_generator
            {
                typedef detail::indexed_proxy< vector<float_v, sizeof...(indices)>, data_type, indices...> type;
            };

            //! A factory of 1-component proxies.
            template <size_t x>
            struct proxy_generator<x>
            {
                typedef float_v type;
            };

            typedef detail::vector_base< Size, proxy_generator, data_type > base_type;

            static float_v::VectorType::Base convert_other_scalar_type(const float_v& other)
            {
                return other.data();
            }
        };
    }

    namespace detail
    {
        inline const Vc::float_v& decay(const Vc::float_v& x) { return x; }
        inline Vc::float_v& decay(Vc::float_v& x) { return x; }
        inline Vc::float_v decay(Vc::float_v&& x) { return std::move(x); }

        template <>
        struct get_vector_type_impl<Vc::float_v>
        {
            typedef glsl::vector<Vc::float_v, 1> type;
        };

#ifdef ENABLE_SIMD

        template <>
        struct get_vector_type_impl<float> : get_vector_type_impl<Vc::float_v>
        {};

        template <>
        struct get_vector_type_impl<double> : get_vector_type_impl<Vc::float_v>
        {};

#endif
    }
}


//! Vc's unary operators are defined in a weird way that
//! doesn't like ADL and can't do the implicit cast from
//! double. Hence this and following operators are
//! defined explicitly.
inline Vc::float_v operator+(float x, Vc::float_v::AsArg y)
{
    return Vc::float_v(x) + y;
}

inline Vc::float_v operator-(float x, Vc::float_v::AsArg y)
{
    return Vc::float_v(x) - y;
}

inline Vc::float_v operator*(float x, Vc::float_v::AsArg y)
{
    return Vc::float_v(x) * y;
}

inline Vc::float_v operator/(float x, Vc::float_v::AsArg y)
{
    return Vc::float_v(x) / y;
}


namespace Vc
{
    //! Vc doesn't come with pow function, so we're gonna go
    //! with the poor man's version of it.
    inline float_v pow(float_v::AsArg x, float_v::AsArg y)
    {
        return exp(y * log(x));
    }
}