#ifndef STATE_H
#define STATE_H

class State {
    private:
        unsigned int limit;
        unsigned int counter;
        unsigned int evaluations;


    public:
        State() :limit(0), counter(0), evaluations(0) {};

        inline void set_limit(unsigned int limit) { this->limit = limit; }
        inline unsigned int iterations() { return this->limit; }
        inline void count() { ++(this->counter); }
        inline void count_evaluations() { ++(this->evaluations); }
        inline unsigned int total() { return this->counter; }
        inline unsigned int total_evaluations() { return this->evaluations; }
        inline void reset() { 
            this->counter = 0;
            this->evaluations = 0;
        }
        inline bool enough() { return this->evaluations >= this->limit; }
        inline bool enough(unsigned int to_evaluate) { return this->evaluations + to_evaluate >= this->limit; }
};

extern State state;

#endif

