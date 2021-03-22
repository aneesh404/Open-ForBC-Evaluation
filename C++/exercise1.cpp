#include<iostream>
#include<unordered_map>
#include<list>
#include<vector>
#define capacity 5  

template <typename T>
class Cache {
    private:
        std::list<std::pair<int, T> > cache;
        std::vector<T> data_array;
        std::unordered_map<int, typename std::list<std::pair<int, T>>::iterator> locator;
        ssize_t size;
    public:
        Cache<T>(ssize_t size, std::vector<T> data_array) : size(size), data_array(data_array) { }

        T query (int key) {
            if(locator.find(key) != locator.end()){
                auto itr = locator[key];
                T val = itr->second;
                cache.erase(itr);
                cache.push_front({key,val});
                locator[key] = cache.begin();
                return val;
            }
            if(locator.size() == size){
                locator.erase(cache.back().first);
                cache.pop_back();
            }
            T val = data_array[key-1];
            cache.push_front({key, val});
            locator[key] = cache.begin();
            return val;
        }
        void print_cache() {
            std::cout<<"[";
            for(auto itr = cache.begin();itr!=cache.end();itr++)
                std::cout<<itr->first<<":\""<<itr->second<<"\""<<", ";
            std::cout<<"]"<<"\n";
        }
};

int main(){
    Cache<std::string> instance1(4, {"1","2","3","4","5","6","7","8","9","10"});
    std::cout<<"Corresponding value to 2-> "<<instance1.query(2)<<"\n";
    std::cout<<"Corresponding value to 1-> "<<instance1.query(1)<<"\n";
    std::cout<<"Corresponding value to 3-> "<<instance1.query(3)<<"\n";
    std::cout<<"Corresponding value to 5-> "<<instance1.query(5)<<"\n";
    std::cout<<"Corresponding value to 4-> "<<instance1.query(4)<<"\n";
    instance1.print_cache();
    std::cout<<"Corresponding value to 2-> "<<instance1.query(2)<<"\n";
    std::cout<<"Corresponding value to 4-> "<<instance1.query(4)<<"\n";
    instance1.print_cache();
    return 0;
}