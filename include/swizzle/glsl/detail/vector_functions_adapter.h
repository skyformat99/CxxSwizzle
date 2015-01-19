// CxxSwizzle
// Copyright (c) 2013, Piotr Gwiazdowski <gwiazdorrr+github at gmail.com>
#pragma once

#include <cmath>
#include <swizzle/detail/utils.h>

namespace swizzle
{
    namespace detail
    {
        namespace glsl
        {
            //! A class providing static functions matching GLSL's vector functions. Uses naive approach, i.e.
            //! everything is done components-wise, using stdlib's math functions.
            //! VectorType must have arithmetic operators, binary and unary.
            template <class Base, template <class, size_t> class VectorType, class ScalarType, size_t Size>
            class vector_functions_adapter : public Base
            {
            public:
                typedef VectorType<ScalarType, Size> vector_type;
                typedef const VectorType<ScalarType, Size>& vector_arg_type;
                typedef VectorType<bool, Size> bool_vector_type;
                typedef ScalarType scalar_type;
                typedef const ScalarType& scalar_arg_type;

            private:

                struct not_available;


                //! Fires Func for each component an assigns back the result

                template <typename Func, typename... Args>
                static vector_type construct_static(Func func, Args&&... args)
                {
                    vector_type result;
                    detail::static_for2<0, Size>(func, result, std::forward<Args>(args)...);
                    return result;
                }

                template <class T, class Func>
                static VectorType<T, Size> construct(Func func)
                {
                    VectorType<T, Size> result;
                    detail::static_for<0, Size>([&](size_t i) -> void { result[i] = func(i); });
                    return result;
                }


            private:

                struct functor_sin
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type x)
                    {
                        using namespace std;
                        result.static_at<i>() = sin(x.static_at<i>());
                    }
                };

                struct functor_cos
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type x)
                    {
                        using namespace std;
                        result.static_at<i>() = cos(x.static_at<i>());
                    }
                };

                struct functor_tan
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type x)
                    {
                        using namespace std;
                        result.static_at<i>() = tan(x.static_at<i>());
                    }
                };

                struct functor_asin
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type x)
                    {
                        using namespace std;
                        result.static_at<i>() = asin(x.static_at<i>());
                    }
                };

                struct functor_acos
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type x)
                    {
                        using namespace std;
                        result.static_at<i>() = acos(x.static_at<i>());
                    }
                };

                struct functor_atan
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type x)
                    {
                        using namespace std;
                        result.static_at<i>() = atan(x.static_at<i>());
                    }

                    template <size_t i> void operator()(vector_type& result, vector_arg_type y, vector_arg_type x)
                    {
                        using namespace std;
                        result.static_at<i>() = atan2(y.static_at<i>(), x.static_at<i>());
                    }
                };

                struct functor_mul
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type x, scalar_arg_type y)
                    {
                        result.static_at<i>() = x.static_at<i>() * y;
                    }
                };

                struct functor_pow
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type x, scalar_arg_type y)
                    {
                        using namespace std;
                        result.static_at<i>() = pow(x.static_at<i>(), y);
                    }

                    template <size_t i> void operator()(vector_type& result, vector_arg_type x, vector_arg_type y)
                    {
                        using namespace std;
                        result.static_at<i>() = pow(x.static_at<i>(), y.static_at<i>());
                    }
                };

                struct functor_abs
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type x)
                    {
                        using namespace std;
                        result.static_at<i>() = abs(x.static_at<i>());
                    }
                };

                struct functor_exp
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type x)
                    {
                        using namespace std;
                        result.static_at<i>() = exp(x.static_at<i>());
                    }
                };

                struct functor_log
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type x)
                    {
                        using namespace std;
                        result.static_at<i>() = log(x.static_at<i>());
                    }
                };

                struct functor_exp2
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type x)
                    {
                        using namespace std;
                        result.static_at<i>() = exp2(x.static_at<i>());
                    }
                };

                struct functor_log2
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type x)
                    {
                        using namespace std;
                        result.static_at<i>() = log2(x.static_at<i>());
                    }
                };

                struct functor_sqrt
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type x)
                    {
                        using namespace std;
                        result.static_at<i>() = sqrt(x.static_at<i>());
                    }
                };

                struct functor_inversesqrt
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type x)
                    {
                        using namespace std;
                        result.static_at<i>() = rsqrt(x.static_at<i>());
                    }
                };

                struct functor_sign
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type x)
                    {
                        using namespace std;
                        result.static_at<i>() = sign(x.static_at<i>());
                    }
                };

                struct functor_fract
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type x)
                    {
                        using namespace std;
                        scalar_type xx = x.static_at<i>();
                        result.static_at<i>() = xx - floor(xx);
                    }
                };

                struct functor_mod
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type x, vector_arg_type y)
                    {
                        operator() < i > (result, x, y.static_at<i>());
                    }

                    template <size_t i> void operator()(vector_type& result, vector_arg_type x, scalar_arg_type y)
                    {
                        using namespace std;
                        auto xx = x.static_at<i>();
                        result.static_at<i>() = xx - y * floor(xx / y);
                    }
                };

                struct functor_min
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type x, vector_arg_type y)
                    {
                        operator() < i > (result, x, y.static_at<i>());
                    }

                    template <size_t i> void operator()(vector_type& result, vector_arg_type x, scalar_arg_type y)
                    {
                        using namespace std;
                        result.static_at<i>() = min(x.static_at<i>(), y);
                    }
                };

                struct functor_max
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type x, vector_arg_type y)
                    {
                        operator() < i > (result, x, y.static_at<i>());
                    }

                    template <size_t i> void operator()(vector_type& result, vector_arg_type x, scalar_arg_type y)
                    {
                        using namespace std;
                        result.static_at<i>() = max(x.static_at<i>(), y);
                    }
                };

                struct functor_clamp
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type x, vector_arg_type a, vector_arg_type b)
                    {
                        operator() < i > (result, x, a.static_at<i>(), b.static_at<i>());
                    }

                    template <size_t i> void operator()(vector_type& result, vector_arg_type x, scalar_arg_type a, scalar_arg_type b)
                    {
                        using namespace std;
                        result.static_at<i>() = max(min(x.static_at<i>(), b), a);
                    }
                };

                struct functor_mix
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type x, vector_arg_type y, vector_arg_type a)
                    {
                        operator() < i > (result, x, y, a.static_at<i>());
                    }

                    template <size_t i> void operator()(vector_type& result, vector_arg_type x, vector_arg_type y, scalar_arg_type a)
                    {
                        using namespace std;
                        result.static_at<i>() = x.static_at<i>() + a * (y.static_at<i>() - x.static_at<i>());
                    }
                };

                struct functor_step
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type edge, vector_arg_type x)
                    {
                        operator() < i > (result, x, edge.static_at<i>(), x);
                    }

                    template <size_t i> void operator()(vector_type& result, scalar_arg_type edge, vector_arg_type x)
                    {
                        using namespace std;
                        result.static_at<i>() = x > edge ? 1 : 0;
                    }
                };


                struct functor_smoothstep
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type edge0, vector_arg_type edge1, vector_arg_type x)
                    {
                        operator() < i > (result, edge0.static_at<i>(), edge1.static_at<i>(), x);
                    }

                    template <size_t i> void operator()(vector_type& result, scalar_arg_type edge0, scalar_arg_type edge1, vector_arg_type x)
                    {
                        using namespace std;
                        auto t = (x.static_at<i>() - edge0) / (edge1 - edge0);
                        t = min(max(t, scalar_arg_type(0)), scalar_arg_type(1));
                        result.static_at<i>() = t * t * (3 - 2 * t);
                    }
                };

                struct functor_dot
                {
                    template <size_t i> void operator()(scalar_type& result, vector_arg_type x, vector_arg_type y)
                    {
                        result += x.static_at<i>() * y.static_at<i>();
                    }
                };

                struct functor_floor
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type x)
                    {
                        using namespace std;
                        result.static_at<i>() = floor(x.static_at<i>());
                    }
                };

                struct functor_ceil
                {
                    template <size_t i> void operator()(vector_type& result, vector_arg_type x)
                    {
                        using namespace std;
                        result.static_at<i>() = ceil(x.static_at<i>());
                    }
                };


            public:

                static vector_type call_radians(vector_arg_type degrees)
                {
                    static const scalar_type deg_to_rad = 3.14159265358979323846 / 180;
                    return construct_static(functor_mul{}, degrees, deg_to_rad);
                }

                static vector_type call_degrees(vector_arg_type radians)
                {
                    static const scalar_type deg_to_rad = 3.14159265358979323846 / 180;
                    return construct_static(functor_mul{}, degrees, deg_to_rad);
                }

                #define SIMPLE_TRANSFORM_UNARY(name) \
                static vector_type call_##name(vector_arg_type x) \
                {\
                    return construct_static(functor_##name{}, x);\
                }

                #define SIMPLE_TRANSFORM_BINARY_V_V(name) \
                static vector_type call_##name(vector_arg_type x, vector_arg_type y) \
                {\
                    return construct_static(functor_##name{}, x, y);\
                }

                #define SIMPLE_TRANSFORM_BINARY_V_S(name) \
                static vector_type call_##name(vector_arg_type x, scalar_arg_type y) \
                {\
                    return construct_static(functor_##name{}, x, y);\
                }

                SIMPLE_TRANSFORM_UNARY(sin)
                SIMPLE_TRANSFORM_UNARY(cos)
                SIMPLE_TRANSFORM_UNARY(tan)
                SIMPLE_TRANSFORM_UNARY(asin)
                SIMPLE_TRANSFORM_UNARY(acos)
                SIMPLE_TRANSFORM_UNARY(atan)
                SIMPLE_TRANSFORM_BINARY_V_V(atan)
                SIMPLE_TRANSFORM_UNARY(abs)
                SIMPLE_TRANSFORM_BINARY_V_V(pow)
                SIMPLE_TRANSFORM_BINARY_V_S(pow)
                SIMPLE_TRANSFORM_UNARY(exp)
                SIMPLE_TRANSFORM_UNARY(log)
                SIMPLE_TRANSFORM_UNARY(exp2)
                SIMPLE_TRANSFORM_UNARY(log2)
                SIMPLE_TRANSFORM_UNARY(sqrt)
                SIMPLE_TRANSFORM_UNARY(inversesqrt)
                SIMPLE_TRANSFORM_UNARY(sign)
                SIMPLE_TRANSFORM_UNARY(fract)
                SIMPLE_TRANSFORM_UNARY(floor)
                SIMPLE_TRANSFORM_UNARY(ceil)
                SIMPLE_TRANSFORM_BINARY_V_V(mod)
                SIMPLE_TRANSFORM_BINARY_V_S(mod)

                SIMPLE_TRANSFORM_BINARY_V_V(min)
                SIMPLE_TRANSFORM_BINARY_V_S(min)
                SIMPLE_TRANSFORM_BINARY_V_V(max)
                SIMPLE_TRANSFORM_BINARY_V_S(max)


                static vector_type call_clamp(vector_arg_type x, vector_arg_type minVal, vector_arg_type maxVal)
                {
                    return construct_static(functor_clamp{}, x, minVal, maxVal);
                }

                static vector_type call_clamp(vector_arg_type x, scalar_arg_type minVal, scalar_arg_type maxVal)
                {
                    return construct_static(functor_clamp{}, x, minVal, maxVal);
                }

                static vector_type call_mix(vector_arg_type x, vector_arg_type y, vector_arg_type a)
                {
                    return construct_static(functor_mix{}, x, y, a);
                }

                static vector_type call_mix(vector_arg_type x, vector_arg_type y, scalar_arg_type a)
                {
                    return construct_static(functor_mix{}, x, y, a);
                }

                static vector_type call_step(vector_arg_type edge, vector_arg_type x)
                {
                    return construct_static(functor_step{}, edge, x);
                }

                static vector_type call_step(scalar_arg_type edge, vector_arg_type x)
                {
                    return construct_static(functor_step{}, edge, x);
                }

                static vector_type call_smoothstep(vector_arg_type edge0, vector_arg_type edge1, vector_arg_type x)
                {
                    return construct_static(functor_smoothstep{}, edge0, edge1, x);
                }

                static vector_type call_smoothstep(scalar_arg_type edge0, scalar_arg_type edge1, vector_arg_type x)
                {
                    return construct_static(functor_smoothstep{}, edge0, edge1, x);
                }

                static vector_type call_reflect(vector_arg_type I, vector_arg_type N)
                {
                    //return (I - 2 * call_dot(I, N) * N);
                    scalar_type dot2 = 2 * call_dot(I, N);
                    vector_type n = N;
                    n *= dot2;

                    vector_type i = I;
                    i -= n;
                    return i;
                }

                // Geometric functions
                static scalar_type call_length(vector_arg_type x)
                {
                    scalar_type dot = call_dot(x, x);
                    return sqrt(dot);
                }

                static scalar_type call_distance(vector_arg_type p0, const vector_arg_type p1)
                {
                    return call_length(p0 - p1);
                }

                static scalar_type call_dot(vector_arg_type x, vector_arg_type y)
                {
                    scalar_type result = 0;
                    detail::static_for2<0, Size>(functor_dot{}, result, x, y);
                    return result;
                }

                static vector_type call_normalize(vector_arg_type x)
                {
                    using namespace std;
                    scalar_type dot = call_dot(x, x);
                    return vector_type(x) * rsqrt(dot);
                }

                static typename std::conditional<Size == 3, vector_type, not_available>::type call_cross(const vector_type& x, const vector_type& y)
                {
                    auto rx = x[1] * y[2] - x[2] * y[1];
                    auto ry = x[2] * y[0] - x[0] * y[2];
                    auto rz = x[0] * y[1] - x[1] * y[0];
                    return vector_type(rx, ry, rz);
                }

                static bool_vector_type call_lessThan(vector_arg_type x, vector_arg_type y)
                {
                    return construct<bool>([&](size_t i) -> bool { return x[i] < y[i]; });
                }

                static bool_vector_type call_lessThanEqual(vector_arg_type x, vector_arg_type y)
                {
                    return construct<bool>([&](size_t i) -> bool { return x[i] <= y[i]; });
                }

                static bool_vector_type call_greaterThan(vector_arg_type x, vector_arg_type y)
                {
                    return construct<bool>([&](size_t i) -> bool { return x[i] > y[i]; });
                }

                static bool_vector_type call_greaterThanEqual(vector_arg_type x, vector_arg_type y)
                {
                    return construct<bool>([&](size_t i) -> bool { return x[i] >= y[i]; });
                }

                static bool_vector_type call_equal(vector_arg_type x, vector_arg_type y)
                {
                    return construct<bool>([&](size_t i) -> bool { return x[i] == y[i]; });
                }

                static bool_vector_type call_notEqual(vector_arg_type x, vector_arg_type y)
                {
                    return construct<bool>([&](size_t i) -> bool { return x[i] != y[i]; });
                }

                static bool call_any(typename std::conditional<std::is_same<ScalarType, bool>::value, vector_arg_type, not_available>::type x)
                {
                    bool result = false;
                    detail::static_for<0, Size>([&](size_t i) -> void { result |= x[i]; });
                    return result;
                }

                static bool call_all(typename std::conditional< std::is_same<scalar_type, bool>::value, vector_arg_type, not_available>::type x)
                {
                    bool result = true;
                    detail::static_for<0, Size>([&](size_t i) -> void { result &= x[i]; });
                    return result;
                }

                static vector_type call_not(typename std::conditional< std::is_same<scalar_type, bool>::value, vector_arg_type, not_available>::type x)
                {
                    return construct<bool>([&](size_t i) -> bool { return !x[i]; });
                }
            };
        }
    }
}