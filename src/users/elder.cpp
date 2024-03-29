#include "../../lib/users/elder.hpp"

Elder::Elder(){}

Elder::Elder(int id, std::string category, std::string name, int age, float budget){
    this->id = id;
    this->category = category;
    this->name = name;
    this->age = age;
    this->budget = budget;
}

void Elder::print_elders(std::map<int,Elder*> elders){
    std::map<int, Elder*>::iterator itr; 
    int id;
    
    for (itr = elders.begin(); itr != elders.end(); ++itr) {
        std::cout 
            << "\nId: " << itr->second->get_id() 
            << "\nNome: " << itr->second->get_name() 
            << "\nCategoria: Idoso" 
            << "\nIdade: " << itr->second->get_age() 
            << "\nSaldo: " << itr->second->get_budget()
        << std::endl; 

        
    } 
}
