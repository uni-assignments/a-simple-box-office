#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector> 

#include "./lib/users/user.hpp"
#include "./lib/users/kid.hpp"
#include "./lib/users/adult.hpp"
#include "./lib/users/elder.hpp"

#include "./lib/events/event.hpp"
#include "./lib/events/infant_event.hpp"
#include "./lib/events/adult_event.hpp"


std::vector<User> parse_users(std::vector<std::string> StringArray){
    std::vector<User> users;
    std::vector<std::string> aux;
    
    for(std::string str : StringArray){
        std::stringstream ss(str);
        std::string token;
        
        while (std::getline(ss, token, ',')){ 
            aux.push_back(token);
        }         
        
        if(std::string(aux[1]) == "crianca"){     
            Kid new_kid(std::stoi(aux[0]), std::string(aux[1]), std::string(aux[2]), std::stoi(aux[3]), ::atof(aux[4].c_str()), users[std::stoi(aux[5])]);
            users.push_back(new_kid);
        
        } else if(std::string(aux[1]) == "adulto"){
            Adult new_adult(std::stoi(aux[0]),aux[1], aux[2],std::stoi(aux[3]),::atof(aux[4].c_str()));
            users.push_back(new_adult);    

        } else {
            Elder new_elder(std::stoi(aux[0]),aux[1], aux[2],std::stoi(aux[3]),::atof(aux[4].c_str()));
            users.push_back(new_elder);    
        }
        aux.clear();
    } 

   return users;
}

// std::vector<Event::Event> parse_events(std::vector<std::string> StringArray){
//     std::vector<User> events;
//     std::vector<std::string> aux;
    
//     for(std::string str : StringArray){
//         std::stringstream ss(str);
//         std::string token;
        
//         while (std::getline(ss, token, ',')){ 
//             aux.push_back(token);
//         }         
        
//         if(std::string(aux[1]) == "infantil"){    
        
//         } else if(std::string(aux[1]) == "adulto"){   
//             if(std::string(aux[2]) == "show") {

//             } else{

//             }
//         } else {

//         }
//         aux.clear();
//     } 

//    return events;
// }

std::vector<std::string> read_file(std::string fileName){
    
    std::string object;
    std::vector<std::string> objectsArray;
    std::ifstream inFile;


    inFile.open(fileName);
    if (!inFile) {
        std::cerr << "Unable to open file\n";
        exit(2); 
    } 

    while(!inFile.eof()){
        getline(inFile, object);
        objectsArray.push_back(object);
    }
    inFile.close();

    return objectsArray;
}


int main(int argc, const char** argv) {
    
    std::ifstream inFile;
    std::vector<std::string> UsersArray;
    std::vector<std::string> EventsArray;
    std::vector<User> Users;

    if(argc != 3) {
        std::cerr << "There arent enough arguments\n";
        exit(1);
    }
    
    UsersArray = read_file(argv[1]);
    EventsArray = read_file(argv[2]);
    Users = parse_users(UsersArray);


    return 0;
}