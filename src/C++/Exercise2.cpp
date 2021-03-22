#include <vector>
#include<thread>
#include<mutex>
#include<iostream>
#include <algorithm>

#define VSIZE 100000


class Logger{
    public:
        Logger() : percentage(0.0) {}

        void completion_update(float percentage){
            percentage_mutex.lock();
            this->percentage = percentage;
            percentage_mutex.unlock();
        }

        void std_out(){
            while(true){
                is_finished_mutex.lock();
                if(is_finished) {
                    std::cout.flush();
                    break;
                }
                is_finished_mutex.unlock();
                std::cout.flush();
                percentage_mutex.lock();
                std::cout<<"Completed:" << percentage *100 << " %\n";
                std::cout.flush();
                percentage_mutex.unlock();
            }
        }

        void run(){
            std::cout << is_finished;
            log = std::thread(&Logger::std_out, this);
        }

        void logging_start(){
            is_finished = false;
            std::cout << is_finished;
            run();
        }

        void logging_end(){
            is_finished_mutex.lock();
            is_finished = true;
            is_finished_mutex.unlock();
            log.join();
        }       


    private: 
        std::mutex is_finished_mutex;
        bool is_finished = false;
        std::mutex percentage_mutex;
        float percentage;    
        std::thread log;

};

class VectorOps{
    public:
    VectorOps(std::vector<int> v1, std::vector<int> v2) : v1(v1), v2(v2), log(std::make_unique<Logger>()) { }
    
    std::vector<int> sum(){
        log->logging_start();

        std::vector<int>result(v1.size(),0);
        for(int i=0;i<v1.size();i++){
            result[i] = v1[i]+v2[i];
            log->completion_update((float)(i+1)/v1.size());
        }

        log->logging_end();
        return result;
    }

    ~VectorOps() {
        auto ptr = log.release();
        delete ptr;
    }
    private:
        std::unique_ptr<Logger> log;
        std::vector<int> v1;
        std::vector<int> v2;        
};

int main(){
    std::vector<int>v1(VSIZE,0),v2(VSIZE,0);
    std::srand(time(NULL));
    std::generate(v1.begin(),v1.end(),rand);
    std::generate(v2.begin(),v2.end(),rand);
    VectorOps *op = new VectorOps(v1,v2);
    auto summation = op->sum();
    return 0;
}