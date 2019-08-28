#pragma once
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<functional>
#include<queue>
namespace utility {

#if 1
	template<class Ty, class _Pr = std::less<typename Ty>>
	class PriorityQueue
	{
	private:
		std::vector<Ty> _vec;
		_Pr _cmp;
	public:
		using iterator = typename std::vector<Ty>::iterator;
		using const_iterator = typename std::vector<Ty>::const_iterator;
	public:
		void push(const Ty& obj) {
			_vec.push_back(obj);
			std::sort(_vec.begin(), _vec.end(), _cmp); // 复杂度有点高 有时间换成 O(N) 插入
		}

		Ty &top() {
			return _vec.back();
		}

		const Ty &top() const {
			return _vec.back();
		}

		void pop() {
			_vec.pop_back();
		}

		void remove(const_iterator iter) {
			_vec.erase(iter);
		}

		size_t size() const {
			return _vec.size();
		}

		bool empty() const {
			return _vec.empty();
		}

		iterator begin() {
			return _vec.begin();
		}

		iterator end() {
			return _vec.end();
		}

		const_iterator begin() const {
			return _vec.cbegin();
		}

		const_iterator end() const {
			return _vec.cend();
		}

		iterator find(const std::function<bool(const Ty&self)> cmp) {
			auto first = _vec.begin();
			auto last = _vec.end();
			while (first != last) {
				if (cmp(*first))return first;
				++first;
			}
			return last;
		}

		const_iterator find(const std::function<bool(const Ty&self)> cmp) const {
			auto first = _vec.cbegin();
			auto last = _vec.cend();
			while (first != last) {
				if (cmp(*first))return first;
				++first;
			}
			return last;
		}
	};
#else
	template<class Ty, class Pr=std::less<Ty> >
	using PriorityQueue = std::priority_queue<Ty, std::vector<Ty>, Pr>;
#endif
	//小顶堆
	template<class Ty>
	using MinPriorityQueue = PriorityQueue<Ty, std::greater<Ty>>;

	//大顶堆
	template<class Ty>
	using MaxPriorityQueue = PriorityQueue<Ty, std::less<Ty>>;
}


