// CxxSwizzle
// Copyright (c) 2013, Piotr Gwiazdowski <gwiazdorrr+github at gmail.com>

#pragma once

#include <cassert>

#ifdef _MSC_VER
//! VS2013 does not support thread_local in a nice way.
#define thread_local __declspec(thread)
#endif

namespace
{
    static const size_t c_max_depth = 16;

    //! Current mask, ready to use. Faster access than index based.
    thread_local raw_mask_type g_currentMask;

    //! Stack of all masks. When if "pops", it goes back to the previous one.
    thread_local raw_mask_type g_multipliedMasks[c_max_depth];

    //! Need to save unmultiplied ones too, as else needs to do reverse
    //! logical and with the last single mask. Need one less than multiplied masks.
    thread_local raw_mask_type g_singleMasks[c_max_depth - 1];
    
    //! Current mask position.
    thread_local int g_masksCount = 0;

}

//! A struct that will update the masks when needed.
struct mask_pusher
{
    //! Each thread should call this for masks to be initialised with correct values.
    static void init_for_thread()
    {
        g_currentMask = static_cast<raw_mask_type>(mask_type(true));
        g_multipliedMasks[0] = g_currentMask;
    }

    template <typename T>
    static mask_pusher push(T&& condition)
    {
        return{ static_cast<mask_type>(condition) };
    }

    struct invert {};
    static mask_pusher push(invert)
    {
        return{ !static_cast<const mask_type&>(g_singleMasks[g_masksCount + 1]) };
    }

    struct lask_mask_all_true {};
    static bool push(lask_mask_all_true)
    {
        return static_cast<mask_type>(g_currentMask) == static_cast<mask_type>(true);
    }


    inline mask_pusher(const mask_type& mask)
    {
        assert(g_masksCount < c_max_depth - 1);

        // save the mask for later negation in "else"
        g_singleMasks[g_masksCount] = static_cast<raw_mask_type>(mask);

        // compute and store the new mask
        auto newMask = mask & static_cast<mask_type>(g_currentMask);
        g_currentMask = g_multipliedMasks[++g_masksCount] = static_cast<raw_mask_type>(newMask);
    }

    inline ~mask_pusher()
    {
        // pop!
        assert(g_masksCount > 0);
        g_currentMask = g_multipliedMasks[--g_masksCount];
    }

    inline operator bool() const
    {
        // let the mask type decide what it means by being "true"; for VC this means
        // at least one value being set IIRC
        return static_cast<bool>(static_cast<mask_type>(g_currentMask));
    }
};

//!
struct masked_assign_policy
{
    template<typename T>
    static void assign(T& target, const T& value)
    {
        target(g_currentMask) = value;
    }
};

#define MASKED_IF(x)    if(auto current_mask_holder = mask_pusher::push(x))
#define MASKED_ELSE     if(mask_pusher::invert{})
#define MASKED_BREAK    if(mask_pusher::lask_mask_all_true{})

#ifdef _MSC_VER
#undef thread_local
#endif