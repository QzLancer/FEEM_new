#pragma once

namespace ProjectExplorer {

enum class WarningFlags {
    // General settings
    NoWarnings = 0,
    AsErrors =  1 << 0,
    Default =  1 << 1,
    All =  1 << 2,
    Extra =  1 << 3,
    Pedantic =  1 << 4,

    // Any language
    UnusedLocals =  1 << 7,
    UnusedParams =  1 << 8,
    UnusedFunctions =  1 << 9,
    UnusedResult =  1 << 10,
    UnusedValue =  1 << 11,
    Documentation =  1 << 12,
    UninitializedVars =  1 << 13,
    HiddenLocals =  1 << 14,
    UnknownPragma =  1 << 15,
    Deprecated =  1 << 16,
    SignedComparison =  1 << 17,
    IgnoredQualfiers =  1 << 18,

    // C++
    OverloadedVirtual =  1 << 24,
    EffectiveCxx =  1 << 25,
    NonVirtualDestructor =  1 << 26
};

inline WarningFlags operator|(WarningFlags first, WarningFlags second)
{
    return static_cast<WarningFlags>(static_cast<int>(first) | static_cast<int>(second));
}

inline WarningFlags operator&(WarningFlags first, WarningFlags second)
{
    return static_cast<WarningFlags>(static_cast<int>(first) & static_cast<int>(second));
}

inline void operator|=(WarningFlags &first, WarningFlags second)
{
    first = first | second;
}

inline void operator&=(WarningFlags &first, WarningFlags second)
{
    first = first & second;
}

inline WarningFlags operator~(WarningFlags flags)
{
    return static_cast<WarningFlags>(~static_cast<int>(flags));
}

} // namespace ProjectExplorer
