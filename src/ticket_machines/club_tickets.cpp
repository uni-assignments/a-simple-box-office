#include "../../lib/ticket_machines/club_tickets.hpp"
#include "../../lib/exceptions/ticket_unavailable_exception.hpp"
#include "../../lib/exceptions/not_enough_tickets_exception.hpp"

ClubTickets* ClubTickets::instance = NULL;

ClubTickets*  ClubTickets::getInstance(){
    if(instance == NULL){
        instance = new ClubTickets();
    }else
        return instance;
}

ClubTickets::ClubTickets(){}

void ClubTickets::show_schedules(BoxOffice *boxOffice, int id_event, int price, int l, int tickets){
    system("clear");
    std::cout 
        << boxOffice->get_clubs()[id_event]->get_name()
        << "\nHorario de inicio: " << boxOffice->get_clubs()[id_event]->get_starting_time() << ":00"
        << "\nHorario de termino: " << boxOffice->get_clubs()[id_event]->get_ending_time() << ":00"
        << "\nIngressos disponiveis: " << tickets
        << "\nPreço: R$:" << price << ",00"
    << std::endl;    
}

int ClubTickets::get_tickets_available(BoxOffice *boxOffice, int id_event, int ticketsWanted){
    int ticketsAvailable = 0;
    for (int i = 0; i < boxOffice->get_clubs()[id_event]->get_capacity().size(); i++)
        ticketsAvailable += boxOffice->get_clubs()[id_event]->get_capacity()[i];
       
    return ticketsAvailable;    
}

int ClubTickets::get_current_price(BoxOffice *boxOffice, int id_event){
    for (int i = 0; i < boxOffice->get_clubs()[id_event]->get_capacity().size(); i++){
        if(boxOffice->get_clubs()[id_event]->get_capacity()[i] > 0)
	        return i;
    }    
}

void ClubTickets::sell_tickets(BoxOffice *boxOffice, int id_event, int id_user){
    int lote = 0, ticketsWanted, time;
    
    double priceIndex = this->get_current_price(boxOffice, id_event);       
    double individuaPrice = boxOffice->get_clubs()[id_event]->get_prices()[priceIndex];
    int ticketsAvailable = this->get_tickets_available(boxOffice, id_event, ticketsWanted);

    if(boxOffice->get_adults()[id_user] != nullptr)
        this->show_schedules(boxOffice, id_event, individuaPrice, priceIndex, ticketsAvailable - boxOffice->get_clubs()[id_event]->get_elder_amout());
    else 
        this->show_schedules(boxOffice, id_event, individuaPrice, priceIndex, ticketsAvailable);

    std::cout << "\nDigite quantos ingressos você deseja: \n";    
    std::cin >> ticketsWanted;
    
    double totalPrice = this->get_total_price(boxOffice->get_clubs()[id_event], id_event, ticketsWanted);
    
    if(ticketsWanted == 0){
        system("clear");
        throw TicketUnavailableException("","");
    }

    if(ticketsAvailable < ticketsWanted){
        system("clear");
        throw NotEnoughtTicketsException("Os ingressos acabaram", ticketsAvailable);
    } 
    if((ticketsAvailable - boxOffice->get_clubs()[id_event]->get_elder_amout()) < ticketsWanted && boxOffice->get_adults()[id_user] != nullptr){
        system("clear");
        throw TicketUnavailableException("Não existem ingressos de nao idosos", "Não há essa quantidade de  ingressos na sua categoria");
    }
    
    if(boxOffice->get_adults()[id_user] != nullptr){
        if(boxOffice->get_adults()[id_user]->get_budget() < totalPrice){
            system("clear");
            throw TicketUnavailableException("Comprar ingressos", "Você nao possui saldo o suficiente");
        } else {
            for(int i = 0; i < ticketsWanted; i++)
                boxOffice->get_adults()[id_user]->increase_bought_tickets();
            
            boxOffice->get_adults()[id_user]->set_budget(totalPrice);
            boxOffice->add_logged_id(id_user);
            boxOffice->add_bought_club(id_event,ticketsWanted);
            this->change_capacity(boxOffice->get_clubs()[id_event], id_event, ticketsWanted);
            emit_ticket(boxOffice, id_event, ticketsWanted, totalPrice);
        }
    } else{
        if(boxOffice->get_elders()[id_user]->get_budget() < totalPrice){
            system("clear");
            throw TicketUnavailableException("Comprar ingressos", "Você nao possui saldo o suficiente");
        } else { 
            for(int i = 0; i < ticketsWanted; i++)
                boxOffice->get_elders()[id_user]->increase_bought_tickets();
              
            boxOffice->get_elders()[id_user]->set_budget(totalPrice);
            boxOffice->add_bought_club(id_event,ticketsWanted);
            boxOffice->add_logged_id(id_user);
            this->change_capacity(boxOffice->get_clubs()[id_event], id_event, ticketsWanted);
            emit_ticket(boxOffice, id_event, ticketsWanted, totalPrice);
        }
    }  
}

void ClubTickets::emit_ticket(BoxOffice *boxOffice, int id_event, int tickets, int price){
    system("clear");
    std::cout << "================================================================================================\n" << std::endl;
    std::cout 
        << "INGRESSO: "
        << boxOffice->get_clubs()[id_event]->get_name()
        << "\nQuantidade de unidades: " << tickets
        << "\nPreco total: R$:" << price << ",00"
    << std::endl;
    std::cout << "\n================================================================================================" << std::endl;
}
