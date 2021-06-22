//==========================================================================
// 自作スマートポインタ [SharePtr.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include <type_traits>
#include <functional>
#include "mdx.h"

_MDX_COMMON_BEGIN

//==========================================================================
//
// class : SharePtr 
// Content : 自作スマートポインタ
//
//==========================================================================
template <class _Ty>
class SharePtr final {
private:
	// 生ポインタ管理機能
	class _Ptr {
	public:
		_Ty* m_data; // 生ポインタ
	private:
		std::function<void(_Ty*)> m_deleter; // カスタムデリータ
		mutable int64_t m_user_count; // count
	public:
		_Ptr() :m_data(nullptr), m_deleter([](_Ty* p) {if (p != nullptr) delete p; }), m_user_count(0) {}
		_Ptr(_Ty* _ptr) :m_data(_ptr), m_deleter([](_Ty* p) {if (p != nullptr) delete p; }), m_user_count(0) {}
		_Ptr(_Ty* _ptr, const std::function<void(_Ty*)>& _deleter) :m_data(_ptr), m_deleter(_deleter), m_user_count(0) {}
		~_Ptr() {
			destroy();
		}
		int64_t AddUserCount() {
			m_user_count++;
			return m_user_count;
		}
		int64_t GetUserCount() {
			return m_user_count;
		}
		bool Release() {
			m_user_count--;
			return (m_user_count <= 0);
		}
		void destroy() {
			m_deleter(m_data);
			m_data = nullptr;
		}
	};
private:
	_Ptr* m_ptr; // ポインタ管理
public:
	SharePtr() :m_ptr(nullptr) {} // empty SharePtr
	SharePtr(_Ty* _ptr) :m_ptr(new _Ptr(_ptr)) { // empty SharePtr
		m_ptr->AddUserCount();
	}
	SharePtr(_Ty* _ptr, const std::function<void(_Ty*)>& _deleter) :m_ptr(new _Ptr(_ptr, _deleter)) { // empty SharePtr
		m_ptr->AddUserCount();
	}
	SharePtr(nullptr_t) :m_ptr(nullptr) {} // empty SharePtr
	SharePtr(nullptr_t, const std::function<void(_Ty*)>& _deleter) :m_ptr(nullptr) {} // empty SharePtr
	SharePtr(const SharePtr& data) :m_ptr(data.m_ptr) {
		if (check())
			m_ptr->AddUserCount();
	}
	~SharePtr() {
		// 管理していない場合終了
		if (m_ptr == nullptr)
			return;
		// 参照数を減らし、解放可能な場合
		if (m_ptr->Release())
			delete m_ptr;
		m_ptr = nullptr;
	}
	/**
	@brief 監視対象の寿命切れやリンク切れを判定する
	@return 監視オブジェクトが存在する場合は true、そうでない場合 は false
	*/
	bool check() const noexcept {
		if (m_ptr == nullptr)
			return false;
		if (m_ptr->m_data == nullptr)
			return false;
		return true;
	}
	/**
	@brief 所有権を持つユーザー数を取得する。
	@return ユーザー数
	*/
	int64_t use_count() noexcept {
		if (m_ptr != nullptr)
			return m_ptr->GetUserCount();
		return 0;
	}
	/**
	@brief 監視対象とのリンクをクリアする
	*/
	void clear() noexcept {
		// 管理していない場合終了
		if (m_ptr == nullptr)
			return;
		// 参照数を減らしたら解放可能になった
		if (m_ptr->Release())
			delete m_ptr;
		m_ptr = nullptr;
	}
	/**
	@brief 監視対象を破棄する
	*/
	void destroy() {
		if (m_ptr != nullptr)
			m_ptr->destroy();
	}

	// return pointer to resource
	_Ty* operator->() const {
		return m_ptr->m_data;
	}

	// return reference to resource
	_Ty& operator*() const {
		return *m_ptr->m_data;
	}
	void operator =(nullptr_t) {
		clear();
	}
	operator bool() const noexcept {
		return check();
	}
	bool operator!=(nullptr_t) const noexcept {
		return check();
	}
	bool operator==(nullptr_t) const noexcept {
		return !check();
	}
	bool operator==(const SharePtr& _Right) const noexcept {
		if (!check())
			return false;
		if (!_Right.check())
			return false;
		return m_ptr->m_data == _Right.m_ptr->m_data;
	}
	bool operator!=(const SharePtr& _Right) const noexcept {
		if (!check())
			return false;
		if (!_Right.check())
			return false;
		return m_ptr->m_data != _Right.m_ptr->m_data;
	}
	bool operator==(const _Ty& _Right) const noexcept {
		if (!check())
			return false;
		return m_ptr->m_data == &_Right;
	}
	bool operator!=(const _Ty& _Right) const noexcept {
		if (!check())
			return false;
		return m_ptr->m_data != &_Right;
	}
	bool operator==(const _Ty* _Right) const noexcept {
		if (!check())
			return false;
		if (_Right == nullptr)
			return false;
		return m_ptr->m_data == _Right;
	}
	bool operator!=(const _Ty* _Right) const noexcept {
		if (!check())
			return false;
		if (_Right == nullptr)
			return false;
		return m_ptr->m_data != _Right;
	}
	SharePtr& operator=(const SharePtr& data) {
		// コピー元を生成
		auto pCopy = data.m_ptr;
		if (pCopy != nullptr)
			pCopy->AddUserCount();
		// 現在参照しているデータを解放
		clear();
		// 自身にコピー
		m_ptr = pCopy;
		if (check())
			m_ptr->AddUserCount();
		// コピー元を解放
		if (pCopy != nullptr)
			pCopy->Release();
		return *this;
	}
};

_MDX_COMMON_END