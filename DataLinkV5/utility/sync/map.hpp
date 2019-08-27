#pragma once
namespace utility::sync {
	template<class Key, class T>
	class Map
	{
	private:
		std::map<Key, T> std_map_;
		mutable std::mutex map_mutex_;
	public:
		void insert(const Key& inputKey, const T& inputValue) {
			std::lock_guard<std::mutex> lock(map_mutex_);
			std_map_[inputKey] = inputValue;
			lock.unlock();
		}

		bool empty() const {
			std::lock_guard<std::mutex> lock(map_mutex_);
			return std_map_.empty();
		}

		T& operator [](const Key& key) {
			std::lock_guard<std::mutex> lock(map_mutex_);
			return std_map_[key];
		}

		bool exist(const Key& inputKey) {
			std::lock_guard<std::mutex> lock(map_mutex_);
			return  std_map_.find(inputKey) != std_map_.end();
		}

		void erase(const Key& inputKey) {
			std::lock_guard<std::mutex> lock(map_mutex_);
			std_map_.erase(inputKey);
		}

		bool try_get(const Key& inputKey, T& value) {
			std::lock_guard<std::mutex> lock(map_mutex_);
			auto iter = std_map_.find(inputKey);
			if (iter == std_map_.end())
				return false;

			value = iter->second;
			return true;
		}

		size_t size() const {
			std::lock_guard<std::mutex> lock(map_mutex_);
			return std_map_.size();
		}

		auto begin() {
			return std_map_.begin();
		}

		auto end() {
			return std_map_.end();
		}
	};
}