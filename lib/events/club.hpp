#ifndef CLUB_H
#define CLUB_H

#include "../../lib/events/adult_event.hpp"

class Club: public AdultEvent {

    private:
        int startingTime;
        int endingTime;

    public:  
        
        Club();
        Club(int id, std::string category, std::string name, int responsible, std::vector<int> capacity, std::vector<float> prices,
            int elderAmount, int startingTime, int endingTime);

        static void print_clubs(std::map<int,Club*> clubs);

        int get_starting_time(){return startingTime;}
        int get_ending_time(){return endingTime;} 
};
 
#endif