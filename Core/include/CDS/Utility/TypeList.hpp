/**
  * @file    : TypeList.h
  * @brief   : A List of Types, using template<...> to represent the boundary case
  * @author  : Yi'chen Wu
  * @version : V1.0.0
  * @date    : 2022-10-08
*/

#include <type_traits>

template<typename ... Types>
class TypeList;

template<typename HeadType, typename ... FollowingTypes> 
class TypeList<HeadType, FollowingTypes ...>;


/*
    Size
*/
template<typename ListType> struct Size;

template<>
struct Size<TypeList<>>
{
	const static int Result = 0;
};

template<typename HeadType, typename ... FollowingTypes>
struct Size<TypeList<HeadType, FollowingTypes ...>>
{
    const static int temp = Size<TypeList<FollowingTypes...>>::Result;
    const static int Result = (temp == 0) ? 1 : temp + 1;
};


/*
    index
*/ 

template<typename ListType, int index> struct At;

template<typename HeadType, typename ... FollowingTypes>
struct At<TypeList<HeadType, FollowingTypes ...>, 0>
{
    using Result = HeadType;
};

template<typename HeadType, typename ... FollowingTypes, int index>
struct At<TypeList<HeadType, FollowingTypes ...>, index>
{
    using Result = typename At<TypeList<FollowingTypes...>, index - 1>::Result;
};


/*
    find
*/

template<typename ListType, typename TargetType> struct IndexOf;

template<typename HeadType, typename ... FollowingTypes>
struct IndexOf<TypeList<HeadType, FollowingTypes...>, HeadType>
{
	const static int Result = 0;
};

// couldn't find the TargetType
template<typename TargetType>
struct IndexOf<TypeList<>, TargetType>
{
	const static int Result = -1;
};

template<typename HeadType, typename ... FollowingTypes, typename TargetType>
struct IndexOf<TypeList<HeadType, FollowingTypes...>, TargetType>
{
	const static int temp = IndexOf<TypeList<FollowingTypes...>, TargetType>::Result;
	const static int Result = (temp == -1) ?  - 1 : temp + 1;
};


/*
    Append
*/

template<typename ListType, typename newType> struct Append;

template<typename ... Types, typename NewType>
struct Append<TypeList<Types...>, NewType>
{
	using Result = TypeList<Types..., NewType>;
};


/*
    Concat
*/

template<typename lListType, typename rListType> struct Concat;

template<typename ... lTypes, typename ... rTypes>
struct Concat<TypeList<lTypes...>, TypeList<rTypes...>>
{
    using Result = TypeList<lTypes..., rTypes...>;
};


/*
    Remove
*/

template<typename ListType, typename RemoveType> struct Remove;

template<typename RemoveType>
struct Remove<TypeList<>, RemoveType>
{
	using Result = TypeList<>;
};

template<typename HeadType, typename ... FollowingTypes> 
struct Remove<TypeList<HeadType, FollowingTypes...>, HeadType>
{
	using Result = typename Remove<TypeList<FollowingTypes...>, HeadType>::Result;
};

template<typename HeadType, typename ... FollowingTypes, typename RemoveType>
struct Remove<TypeList<HeadType, FollowingTypes...>, RemoveType>
{
	using Result = typename Concat<TypeList<HeadType>, typename Remove<TypeList<FollowingTypes...>, RemoveType>::Result>::Result;
};


/*
    去重
*/

template<typename ListType> struct NoDuplicate;

template<>
struct NoDuplicate<TypeList<>>
{
	using Result = TypeList<>;
};

template<typename HeadType, typename ... FollowingTypes>
struct NoDuplicate<TypeList<HeadType, FollowingTypes...>>
{
	using Result = typename Concat<TypeList<HeadType>, typename Remove<typename NoDuplicate<TypeList<FollowingTypes...>>::Result, HeadType>::Result>::Result;
};


/*
    Replace
*/

template<typename ListType, typename SrcType, typename TarType> struct Replace;

template<typename SrcType, typename TarType>
struct Replace<TypeList<>, SrcType, TarType>
{
	using Result = TypeList<>;
};

template<typename HeadType, typename ... FollowingTypes, typename TarType>
struct Replace<TypeList<HeadType, FollowingTypes...>, HeadType, TarType>
{
	using Result = typename Concat<TypeList<TarType>, typename Replace<TypeList<FollowingTypes...>, HeadType, TarType>::Result>::Result;
};

template<typename HeadType, typename ... FollowingTypes, typename SrcType, typename TarType>
struct Replace<TypeList<HeadType, FollowingTypes...>, SrcType, TarType>
{
	using Result = typename Concat<TypeList<HeadType>, typename Replace<TypeList<FollowingTypes...>, SrcType, TarType>::Result>:: Result;
};


/*
    Sort
*/


