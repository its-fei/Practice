//LRU算法
//思路：能够迅速get和put，并且要维护一个cache能够将热点数据放在最前面

#include <iostream>
#include <unordered_map>
#include <list>
#include <optional>

class LRU {
private:
	int capacity;
	std::unordered_map<int,std::list<std::pair<int,int>>::iterator> cacheMap;
	std::list<std::pair<int, int>> cache; // front = most recently used
public:
    LRU(int cap):capacity(cap){
        //避免map重复hash
        if (capacity >0) cacheMap.reserve(capacity);
    }

    // 命中返回 value，未命中返回 -1
	std::optional<int> get(int key) {
		auto it = cacheMap.find(key);
		if (it == cacheMap.end()) return std::nullopt;
		
        // 将该节点移动到最前面
		cache.splice(cache.begin(), cache, it->second);
		return it->second->second;
	}
	
	void set(int key, int value) {
		auto it = cacheMap.find(key);   //it是pair类型
		if (it != cacheMap.end()) {
            // 已存在，更新并移动到前面
            it->second->second = value;
			cache.splice(cache.begin(), cache, it->second);
            return;
		}

        // 新插入：若达到容量，删除尾部最老元素
        if (capacity <= 0) return;
        if (cache.size() >= capacity) {
            auto last = cache.back();
            cacheMap.erase(last.first);
            cache.pop_back();
        }

        // 插入到头部并记录迭代器
		// cache.splice(cache.begin(), cache, it->second);
        cache.emplace_front(key,value);
		cacheMap[key] = cache.begin();	
	}
};


int main() {
    LRU* lru = new LRU(2);
    lru->set(1,11);
    lru->set(2,22);
    lru->set(3,33);
    auto v = lru->get(2);
    std::cout << "lru get 2: " << (v? std::to_string(*v):"miss") << std::endl;
    lru->set(1,111);
    v = lru->get(3);
    std::cout << "lru get 3: " << (v? std::to_string(*v):"miss") << std::endl;  //已淘汰key = 3
    return 0;

}