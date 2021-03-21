#include<iostream>
#include<vector>
#include<fstream>
#include<string>
class Cache{
    private:
        // std::unordered_map<int,char>cache;
        std::vector<std::pair <int,std::string> >cache;
        std::vector<std::string>data_array;
    public:
    void fillDataArray(void);
    std::string elementCall(int key);
    void showCache();
    Cache(){
        cache = {std::make_pair(1,"A"),std::make_pair(2,"B")};
        data_array = {"A", "B", "C", "D", "E", "F", "G", "H", "I"};
    }
};

// void Cache::fillDataArray(void){
//     std::ifstream infile;
//     infile.open("input1.txt");
//     infile >> data_array;
//     infile.close();
// }

void Cache::showCache(){
    for(auto itr=cache.begin();itr!=cache.end();itr++){
        std::cout<<itr->first;
        std::cout<<itr->second;
    }
}

std::string Cache::elementCall(int key){
    std::string value;
    std::vector<std::pair <int,std::string> >::iterator itr;
    for(itr = cache.begin();itr!=cache.end();itr++){
        if(itr->first == key){
            int k = itr->first;
            value = itr->second;
            cache.erase(itr);
            cache.insert(cache.begin(),std::make_pair(k,value));
            break;
        }
    }
    cache.insert(cache.begin(),std::make_pair(key,data_array[key-1]));
    return value;
}




int main(){
    Cache ins1;
    std::cout<<ins1.elementCall(5);
    std::cout<<"\n";
    ins1.showCache();
    return 0;
}