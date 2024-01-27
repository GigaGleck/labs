#ifndef OOPPROG2_SIGNAL_H
#define OOPPROG2_SIGNAL_H

#include <iostream>
#include <vector>
#include <limits>
#include <cstring>
#include <stdexcept>

namespace Prog2 {
    class Segment {
        
        private:
            int status;
            int duration;
        
        public:

        Segment(int value_status, int value_duration);
        Segment(std::vector<int> segment);
        ~Segment();

        void Extension(int time);
            
        void operator~();
        
        void Shortening(int time);

        void Format();
        
        int getstatus();

        int getduration();

        void setstatus(int value_status);

        void setduration(int value_duration); 
    };

    class Signal {
        
        private:
            std::vector<Segment> wave;

            void Split(int position, int duration_split);

        public:
            Signal(int value_status, int value_duration);
            
            Signal(std::vector<int> signal);

            ~Signal();

            void Inverse();

            void Signal::operator+=(std::vector<Segment> new_wave);

            void Signal::operator*(int counts);

            void Insert(int position, std::vector<Segment> new_wave);

            void Erase(int position, int time);
            
            int getSignal(int position);

            void Format();
    };
    bool truebin(std::string);

}


#endif //OOPPROG2_SIGNAL_H