#pragma once
#include<mutex>
#include<list>

namespace utility::sync {
	template<class T>
	class List
	{
	private:
		mutable std::list<T> list_;
		mutable std::mutex list_mutex_;
	public:
		void push_back(const T& val) {
			std::lock_guard<std::mutex> lock(list_mutex_);
			list_.push_back(val);
			lock.unlock();
		}

		bool empty() const {
			std::lock_guard<std::mutex> lock(list_mutex_);
			return list_.empty();
		}

		T& front() {
			std::lock_guard<std::mutex> lock(list_mutex_);
			return list_.front();
		}

		const T& front() const {
			std::lock_guard<std::mutex> lock(list_mutex_);
			return list_.front();
		}

		void pop_front() {
			std::lock_guard<std::mutex> lock(list_mutex_);
			list_.pop_front();
		}

		size_t size() const {
			std::lock_guard<std::mutex> lock(list_mutex_);
			return list_.size();
		}
	};
}