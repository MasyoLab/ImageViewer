//==========================================================================
// 動的なマルチキャスト デリゲート [MulticastDelegate.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include <list>
#include <functional>
#include "mdx.h"

_MDX_COMMON_BEGIN

//==========================================================================
//
// class : MulticastDelegate 
// Content : マルチキャスト デリゲート
//
//==========================================================================
template < class... _Args>
class MulticastDelegate final
{
public:
	const size_t _ArgsSize = sizeof...(_Args); // 可変長テンプレートの長さ
private:
	std::list<std::function<void(_Args...)>> m_delegate; // 関数ポインタの管理
public:

	/**
	@brief 関数ポインタの登録
	@caution この関数を直接呼び出さないでください。代わりに、マクロプロキシ関数(AddDynamic0～AddDynamic20)を使ってください。
	*/	
	void __Internal_AddDynamic(const std::function<void(_Args...)>& func)
	{
		m_delegate.push_back(func);
	}

	/**
	@brief 登録された関数ポインタの実行
	*/
	void Broadcast(const _Args&... args)
	{
		// 登録順に実行
		for (auto& function : m_delegate)
			function((args)...);
	}
};
_MDX_COMMON_END
//==========================================================================
//
// マクロプロキシ関数 
//
//==========================================================================
#define AddDynamic0(Func,Class) __Internal_AddDynamic(std::bind(Func, Class))
#define DECLARE_DYNAMIC_MULTICAST_DELEGATE(DelegateName) using DelegateName = mdx::common::MulticastDelegate<>;
#define AddDynamic1(Func,Class) __Internal_AddDynamic(std::bind(Func, Class, std::placeholders::_1))
#define DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(DelegateName,Param1Type) using DelegateName = mdx::common::MulticastDelegate<Param1Type>;
#define AddDynamic2(Func,Class) __Internal_AddDynamic(std::bind(Func, Class, std::placeholders::_1, std::placeholders::_2))
#define DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(DelegateName,Param1Type,Param2Type) using DelegateName = mdx::common::MulticastDelegate<Param1Type,Param2Type>;
#define AddDynamic3(Func,Class) __Internal_AddDynamic(std::bind(Func, Class, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
#define DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(DelegateName,Param1Type,Param2Type,Param3Type) using DelegateName = mdx::common::MulticastDelegate<Param1Type,Param2Type,Param3Type>;
#define AddDynamic4(Func,Class) __Internal_AddDynamic(std::bind(Func, Class, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4))
#define DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(DelegateName,Param1Type,Param2Type,Param3Type,Param4Type) using DelegateName = mdx::common::MulticastDelegate<Param1Type,Param2Type,Param3Type,Param4Type>;
#define AddDynamic5(Func,Class) __Internal_AddDynamic(std::bind(Func, Class, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5))
#define DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(DelegateName,Param1Type,Param2Type,Param3Type,Param4Type,Param5Type) using DelegateName = mdx::common::MulticastDelegate<Param1Type,Param2Type,Param3Type,Param4Type,Param5Type>;
#define AddDynamic6(Func,Class) __Internal_AddDynamic(std::bind(Func, Class, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6))
#define DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(DelegateName,Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type) using DelegateName = mdx::common::MulticastDelegate<Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type>;
#define AddDynamic7(Func,Class) __Internal_AddDynamic(std::bind(Func, Class, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7))
#define DECLARE_DYNAMIC_MULTICAST_DELEGATE_SevenParams(DelegateName,Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type) using DelegateName = mdx::common::MulticastDelegate<Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type>;
#define AddDynamic8(Func,Class) __Internal_AddDynamic(std::bind(Func, Class, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8))
#define DECLARE_DYNAMIC_MULTICAST_DELEGATE_EightParams(DelegateName,Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type) using DelegateName = mdx::common::MulticastDelegate<Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type>;
#define AddDynamic9(Func,Class) __Internal_AddDynamic(std::bind(Func, Class, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9))
#define DECLARE_DYNAMIC_MULTICAST_DELEGATE_NineParams(DelegateName,Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type,Param9Type) using DelegateName = mdx::common::MulticastDelegate<Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type,Param9Type>;
#define AddDynamic10(Func,Class) __Internal_AddDynamic(std::bind(Func, Class, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9, std::placeholders::_10))
#define DECLARE_DYNAMIC_MULTICAST_DELEGATE_TenParams(DelegateName,Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type,Param9Type,Param10Type) using DelegateName = mdx::common::MulticastDelegate<Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type,Param9Type,Param10Type>;
#define AddDynamic11(Func,Class) __Internal_AddDynamic(std::bind(Func, Class, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9, std::placeholders::_10, std::placeholders::_11))
#define DECLARE_DYNAMIC_MULTICAST_DELEGATE_ElevenParams(DelegateName,Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type,Param9Type,Param10Type,Param11Type) using DelegateName = mdx::common::MulticastDelegate<Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type,Param9Type,Param10Type,Param11Type>;
#define AddDynamic12(Func,Class) __Internal_AddDynamic(std::bind(Func, Class, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9, std::placeholders::_10, std::placeholders::_11, std::placeholders::_12))
#define DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwelveParams(DelegateName,Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type,Param9Type,Param10Type,Param11Type,Param12Type) using DelegateName = mdx::common::MulticastDelegate<Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type,Param9Type,Param10Type,Param11Type,Param12Type>;
#define AddDynamic13(Func,Class) __Internal_AddDynamic(std::bind(Func, Class, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9, std::placeholders::_10, std::placeholders::_11, std::placeholders::_12, std::placeholders::_13))
#define DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThirteenParams(DelegateName,Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type,Param9Type,Param10Type,Param11Type,Param12Type,Param13Type) using DelegateName = mdx::common::MulticastDelegate<Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type,Param9Type,Param10Type,Param11Type,Param12Type,Param13Type>;
#define AddDynamic14(Func,Class) __Internal_AddDynamic(std::bind(Func, Class, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9, std::placeholders::_10, std::placeholders::_11, std::placeholders::_12, std::placeholders::_13, std::placeholders::_14))
#define DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourteenParams(DelegateName,Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type,Param9Type,Param10Type,Param11Type,Param12Type,Param13Type,Param14Type) using DelegateName = mdx::common::MulticastDelegate<Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type,Param9Type,Param10Type,Param11Type,Param12Type,Param13Type,Param14Type>;
#define AddDynamic15(Func,Class) __Internal_AddDynamic(std::bind(Func, Class, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9, std::placeholders::_10, std::placeholders::_11, std::placeholders::_12, std::placeholders::_13, std::placeholders::_14, std::placeholders::_15))
#define DECLARE_DYNAMIC_MULTICAST_DELEGATE_FifteenParams(DelegateName,Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type,Param9Type,Param10Type,Param11Type,Param12Type,Param13Type,Param14Type,Param15Type) using DelegateName = mdx::common::MulticastDelegate<Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type,Param9Type,Param10Type,Param11Type,Param12Type,Param13Type,Param14Type,Param15Type>;
#define AddDynamic16(Func,Class) __Internal_AddDynamic(std::bind(Func, Class, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9, std::placeholders::_10, std::placeholders::_11, std::placeholders::_12, std::placeholders::_13, std::placeholders::_14, std::placeholders::_15, std::placeholders::_16))
#define DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixteenParams(DelegateName,Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type,Param9Type,Param10Type,Param11Type,Param12Type,Param13Type,Param14Type,Param15Type,Param16Type) using DelegateName = mdx::common::MulticastDelegate<Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type,Param9Type,Param10Type,Param11Type,Param12Type,Param13Type,Param14Type,Param15Type,Param16Type>;
#define AddDynamic17(Func,Class) __Internal_AddDynamic(std::bind(Func, Class, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9, std::placeholders::_10, std::placeholders::_11, std::placeholders::_12, std::placeholders::_13, std::placeholders::_14, std::placeholders::_15, std::placeholders::_16, std::placeholders::_17))
#define DECLARE_DYNAMIC_MULTICAST_DELEGATE_SeventeenParams(DelegateName,Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type,Param9Type,Param10Type,Param11Type,Param12Type,Param13Type,Param14Type,Param15Type,Param16Type,Param17Type) using DelegateName = mdx::common::MulticastDelegate<Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type,Param9Type,Param10Type,Param11Type,Param12Type,Param13Type,Param14Type,Param15Type,Param16Type,Param17Type>;
#define AddDynamic18(Func,Class) __Internal_AddDynamic(std::bind(Func, Class, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9, std::placeholders::_10, std::placeholders::_11, std::placeholders::_12, std::placeholders::_13, std::placeholders::_14, std::placeholders::_15, std::placeholders::_16, std::placeholders::_17, std::placeholders::_18))
#define DECLARE_DYNAMIC_MULTICAST_DELEGATE_EightteenParams(DelegateName,Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type,Param9Type,Param10Type,Param11Type,Param12Type,Param13Type,Param14Type,Param15Type,Param16Type,Param17Type,Param18Type) using DelegateName = mdx::common::MulticastDelegate<Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type,Param9Type,Param10Type,Param11Type,Param12Type,Param13Type,Param14Type,Param15Type,Param16Type,Param17Type,Param18Type>;
#define AddDynamic19(Func,Class) __Internal_AddDynamic(std::bind(Func, Class, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9, std::placeholders::_10, std::placeholders::_11, std::placeholders::_12, std::placeholders::_13, std::placeholders::_14, std::placeholders::_15, std::placeholders::_16, std::placeholders::_17, std::placeholders::_18, std::placeholders::_19))
#define DECLARE_DYNAMIC_MULTICAST_DELEGATE_NineteenParams(DelegateName,Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type,Param9Type,Param10Type,Param11Type,Param12Type,Param13Type,Param14Type,Param15Type,Param16Type,Param17Type,Param18Type,Param19Type) using DelegateName = mdx::common::MulticastDelegate<Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type,Param9Type,Param10Type,Param11Type,Param12Type,Param13Type,Param14Type,Param15Type,Param16Type,Param17Type,Param18Type,Param19Type>;
#define AddDynamic20(Func,Class) __Internal_AddDynamic(std::bind(Func, Class, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9, std::placeholders::_10, std::placeholders::_11, std::placeholders::_12, std::placeholders::_13, std::placeholders::_14, std::placeholders::_15, std::placeholders::_16, std::placeholders::_17, std::placeholders::_18, std::placeholders::_19, std::placeholders::_20))
#define DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwentyParams(DelegateName,Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type,Param9Type,Param10Type,Param11Type,Param12Type,Param13Type,Param14Type,Param15Type,Param16Type,Param17Type,Param18Type,Param19Type,Param20Type) using DelegateName = mdx::common::MulticastDelegate<Param1Type,Param2Type,Param3Type,Param4Type,Param5Type,Param6Type,Param7Type,Param8Type,Param9Type,Param10Type,Param11Type,Param12Type,Param13Type,Param14Type,Param15Type,Param16Type,Param17Type,Param18Type,Param19Type,Param20Type>;

