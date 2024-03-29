#ifndef PUPPETSHOW_H
#define PUPPETSHOW_H
 
#include "infant_event.hpp"

class PuppetShow: public InfantEvent {

    private:
        std::vector<int> theaterSchedules;

    public:
        PuppetShow();
        PuppetShow(int id, std::string category, std::string name, int n_responsible, std::vector<int> capacity, std::vector<float> prices,
            std::vector<int> theaterSchedules);
    
        
        static void print_puppet_shows(std::map<int,PuppetShow*> puppetShows);

        std::vector<int> get_schedules(){return theaterSchedules;}  
};
 
#endif