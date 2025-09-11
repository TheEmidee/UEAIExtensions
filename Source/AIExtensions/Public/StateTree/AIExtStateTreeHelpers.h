#pragma once

#include "AITypes.h"

namespace AIExtensions
{
    template < typename T >
    bool CompareNumbers( const T left, const T right, const EGenericAICheck operation )
    {
        switch ( operation )
        {
            case EGenericAICheck::Equal:
                return left == right;
            case EGenericAICheck::NotEqual:
                return left != right;
            case EGenericAICheck::Less:
                return left < right;
            case EGenericAICheck::LessOrEqual:
                return left <= right;
            case EGenericAICheck::Greater:
                return left > right;
            case EGenericAICheck::GreaterOrEqual:
                return left >= right;
            default:
                ensureMsgf( false, TEXT( "Unhandled operator %d" ), operation );
                return false;
        }
    }
}