#include "Signal.h"

#include <iostream>
#include <vector>
#include <limits>
#include <cstring>
#include <stdexcept>

namespace Prog2 {

    template<class T>
    T getNum(T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max()) {
        T a;
        while(true) {
            std::cin >> a;
            if(std::cin.eof()) // обнаружен конец файла
                throw std::runtime_error("Failed to read number: EOF");
            else if(std::cin.bad()) // обнаружена невосстановимая ошибка входного потока
                throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
            // прочие ошибки (неправильный формат ввода) либо число не входит в заданный диапазон
            else if(std::cin.fail() || a < min || a > max) {
                std::cin.clear(); // очищаем флаги состояния потока
                // игнорируем все символы до конца строки
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You are wrong; repeat please!" << std::endl;
            }
            else // успешный ввод
                return a;
        }
    }

    std::string getBinline() {
        std::string a;
        while(true) {
            getline(std::cin, a);
            if(std::cin.eof()) // обнаружен конец файла
                throw std::runtime_error("Failed to read number: EOF");
            else if(std::cin.bad()) // обнаружена невосстановимая ошибка входного потока
                throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
            // прочие ошибки (неправильный формат ввода) либо число не входит в заданный диапазон
            else if(std::cin.fail() || !truebin(a)) {
                std::cin.clear(); // очищаем флаги состояния потока
                // игнорируем все символы до конца строки
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You are wrong; repeat please!" << std::endl;
            }
            else // успешный ввод
                return a;
        }
    }    

    bool truebin(std::string newstring){
        for (int i = 0; i < newstring.length(); i++){
            if (newstring[i] != '0' && newstring[i] != '1') return false;
        }
        return true;
    }

    Segment::Segment(int value_status, int value_duration){
        status = value_status;
        duration = value_duration;
    }

    Segment::Segment(std::vector<int> segment){
        status = segment[0];
        duration = 1;
        for(int i = 0; i < segment.size(); i++){
            if(segment[i] == segment[i + 1]) duration++;
        }
    }

    Segment::~Segment(){

    }
    
    int Segment::getstatus(){
        return status;
    }

    int Segment::getduration(){
        return duration;
    }

    void Segment::setstatus(int value_status){
        status = value_status;
    }

    void Segment::setduration(int value_duration){
        duration = value_duration;
    } 

    void Segment::operator~(){
        this->setstatus(1 - this->getstatus());
    }

    void Segment::Extension(int time){
        duration += time;
    }

    void Segment::Shortening(int time){
        if (time > duration) duration = 0;
        else duration -= time;
    }

    void Segment::Format(){
        for(int i = 0; i < duration; i++){
            if(status == 0) std::cout << "_";
            else std::cout << "-";
        }
        std::cout << std::endl;
    }

    void Signal::Split(int position, int duration_split){
        wave.insert(wave.begin() + position, Segment(wave[position - 1].getstatus(), duration_split));
        wave[position].setduration(wave[position].getduration() - duration_split);
    }

    Signal::Signal(int value_status, int value_duration){
        wave.push_back(Segment(value_status, value_duration));
    }
            
    Signal::Signal(std::vector<int> signal){
        std::vector<int> segment;
        segment.push_back(signal[0]);
        for(int i = 1; i < signal.size(); i++){
            if(signal[i] == signal[i-1]) segment.push_back(signal[i]);
            else{
                wave.push_back(Segment(segment));
                segment.clear();
                segment.push_back(signal[i]);
            }
        }
        wave.push_back(Segment(segment));
    }

    Signal::~Signal(){
            wave.clear();
        }

    void Signal::Inverse(){
        for(int i = 0; i < wave.size(); i++){
            wave[i].setstatus(1 - wave[i].getstatus());
        }
    }

    void Signal::operator+=(std::vector<Segment> new_wave){
        if(wave[wave.size()-1].getstatus() == new_wave[0].getstatus()){
            wave[wave.size()-1].setduration(wave[wave.size()-1].getduration() + new_wave[0].getduration());
            wave.insert(wave.end(), new_wave.begin() + 1, new_wave.end());
        }
            else wave.insert(wave.end(), new_wave.begin(), new_wave.end());
        }

    void Signal::operator*(int counts){
        std::vector<Segment> copy(wave);
        for (int i = 0; i < counts; i++){
            wave.insert(wave.end(), copy.begin(), copy.end());
        }
    }

    void Signal::Insert(int position, std::vector<Segment> new_wave){
        std::vector<int> res1;
        std::vector<int> res2;
        for (int i = 0; i < wave.size(); i++){
            res1.insert(res1.end(), wave[i].getduration(), wave[i].getstatus());
            }
            for (int i = 0; i < new_wave.size(); i++){
                res2.insert(res2.end(), new_wave[i].getduration(), new_wave[i].getstatus());
            }
            if (position < res1.size()){
                    res1.insert(res1.begin() + position, res2.begin(), res2.end());
            }
            else{
                res1.insert(res1.end(), res2.begin(), res2.end());
            }
            wave.clear();
            wave.insert(wave.begin(), Signal(res1).wave.begin(), Signal(res1).wave.end());
        }

    void Signal::Erase(int position, int time){
        std::vector<int> res;
        for (int i = 0; i < wave.size(); i++){
            res.insert(res.end(), wave[i].getduration(), wave[i].getstatus());
        }
        if (position == 0){
            if(time >= res.size()) res.clear();
            else{
                res.erase(res.begin(), res.begin() + time);
            }
        }
        else if(position > res.size()){
            return;
        }
        else if(position + time >= res.size()){
            res.erase(res.begin()+position, res.end());
        }
        else{
            res.erase(res.begin(), res.end());
        }
        wave.clear();
        wave.insert(wave.begin(), Segment(res));
    }
            
    int Signal::getSignal(int position){
        std::vector<int> res;
        int pos;
        for(int i = 0; i < wave.size(); i++){
            res.insert(res.end(), wave[i].getduration(), wave[i].getstatus());
            }
        try{
            if (position <= res.size()) return wave[pos].getstatus();
            else {
                throw std::runtime_error("Out of range");
            }
        }
        catch(...){
            throw;
            return -1;
        }
    }

    void Signal::Format(){
        for(int i = 0; i < wave.size(); i++){
            if(i > 0){
                if (wave[i - 1].getstatus() == 1) std::cout << "\\";
                else std::cout << "/";
            }
            for(int i = 0; i < wave[i].getduration(); i++){
                if (wave[i - 1].getstatus() == 1) std::cout <<  "¯";
                else std::cout << "_";
            }
        }
        std::cout << std::endl;
    }
}