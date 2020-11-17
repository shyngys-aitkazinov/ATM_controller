#include "../includes/atm_controller.hpp"

// void myprint(){
//     std::cout<<"Hello World 1\n";

//     std::cout<<"Hello World 1\n";


// }

Account::Account(std::string acc_num_val, u_long pin_val){
    account_number = acc_num_val;
    pin_code = pin_val; 
    balance = 0;   
}


bool AtmController::InsertAndValidateCard(){
    // missing validation part for the absense of server and credential checking
    // if (!ValidateCard()){return false;}
    m_state = CARD_IN;
    return true;
}


void AtmController::RegisterAccount(){
        std::string input, pin, pin_dup;
        
        std::cout<<"-Please, write the account number and then press Enter\n";
        std::cout<<"-Note: it should be 5 alphanumeric symbols\n";
        // Account Number
        while(true){
            std::getline(std::cin, input);
            if (input.size() != 5){
                // wrong size
                std::cout<<"-Wrong number of characters\n";
                std::cout<<"-Please, try again\n";
                std::cout<<"-Note: input should be 5 alphanumeric symbols\n";
            }
            else{
                bool temp = false;
                for (const auto &c: input){
                    if (!isalnum(c)){
                        temp = true;
                    }
                }
                // not alphanumeric input
                if(temp){
                    std::cout<<"-Not alphanumeric input\n";
                    std::cout<<"-Please, try again\n";
                    std::cout<<"-Note: input should be 5 alphanumeric symbols\n";
                    continue;
                }
                // duplicate account number
                else if(m_accounts.find(input) != m_accounts.end()){
                    std::cout<<"-Duplicate account number\n";
                    std::cout<<"-Please, try again\n";
                    std::cout<<"-Note: input should be 5 alphanumeric symbols\n";
                    continue;

                }

                break;
            }

        }

        std::cout<<"-Now, please enter your PIN number then press Enter\n";
        std::cout<<"-Note: it should be 4 digits \n";
        // PIN number
        while(true){
            std::getline(std::cin, pin);
            if (pin.size() != 4){
                // wrong size
                std::cout<<"-Wrong number of characters\n";
                std::cout<<"-Please, try again\n";
                std::cout<<"-Note: input should be 4 digits\n";
            }
            else{
                bool temp = false;
                for (const auto &c: pin){
                    if (!isdigit(c)){
                        temp = true;
                    }
                }
                // not numeric input
                if(temp){
                    std::cout<<"-Not numeric input\n";
                    std::cout<<"-Please, try again\n";
                    std::cout<<"-Note: input should be 4 digits\n";
                    continue;
                }
                
                std::cout<<"-Please, repeat your PIN number\n";
                std::getline(std::cin, pin_dup);
                if (pin_dup.compare(pin) != 0){
                    std::cout<<"-You entered different PIN number\n";
                    std::cout<<"-Please, try again\n";
                    std::cout<<"-Note: input should be 4 digits\n";
                    continue;
                }

                break;
            }

        }

        std::cout<<"-You successfully created the account\n";
        std::cout<<"-Returning back to main menu\n";
        std::cout<<"-\n";

        m_accounts.emplace(std::make_pair(input, Account(input, std::stoi(pin))));

}


bool AtmController::AccountLogin(){
    
    int i = 1, temp_num = 0;
    bool format = true;
    std::string input, pin;
    std::vector<std::string> accounts;
    // if no accounts registered
    if (m_accounts.size() == 0){
        std::cout<<"-There is no registered accounts, returning back to the menu\n";
        return false;
    }
    accounts.reserve(m_accounts.size());
    std::cout<<"-Please, enter one digit which is the 1 to N indicating the position in the following list of accounts\n\
-or enter your account number\n";
    std::cout<<"-Enter 0 and Enter, to return back to the menu \n";
    
    for (auto itr = m_accounts.begin(); itr!= m_accounts.end(); itr++)
    {
        accounts.emplace_back(std::get<0>(*itr));
        std::cout<<i<<". "<<std::get<0>(*itr)<<"\n";
        i++;
    }

    while(true){
        std::getline(std::cin, input );

        if (input.size() == 1){
            format = true;
            if (!std::isdigit(input[0])){
                std::cout<<"-Invalid input format, please try again\n";
                continue;
            }
            else{
                temp_num = std::stoi(input);
                if (temp_num > 0 && (unsigned int) temp_num <= m_accounts.size()){
                    m_current_account = accounts[temp_num - 1];
                    break;
                }
                else if(temp_num == 0){
                    return false;
                }
                else{
                    std::cout<<"-Invalid input format, please try again\n";
                    continue;
                }
            }
        }
        else if(input.size() == 5){
            format = false;

            if(m_accounts.find(input)!= m_accounts.end()){
                m_current_account = input;
                break;
            }
            else{
                std::cout<<"-Invalid input format, please try again\n";
                continue;
            }
        }
        else{
            std::cout<<"-Invalid input format, please try again\n";
            continue;

        }
    }
    
    std::cout<<"-Please, enter your PIN code, You will have two attempts\n";
    for (int i = 0; i < 2; i++)
    {
        std::getline(std::cin, pin );
        
        if (format){
            const auto &temp_acc =  m_accounts.at(accounts[temp_num - 1]);
            u_long t;
            try {
                t = std::stoi(pin);
            }
            catch(...){
                std::cout<<"-Wrong or invalid PIN\n";
                continue;
            }
            if (temp_acc.pin_code == t){
                return true;
            }
            std::cout<<"-Second attempt:\n";
        }
        else{
            u_long t;
            try {
                t = std::stoi(pin);
            }
            catch(...){
                std::cout<<"-Wrong or invalid PIN\n";
                continue;
            }
            if (m_accounts.find(input)->second.pin_code == t){
                return true;
            }
            std::cout<<"-Second attempt:\n";
            

        }
    }
    
    return false;
    
    
}
void AtmController::HandleTransaction( u_long amount, int type){

    auto& temp_account = (m_accounts.find(m_current_account)->second);
    switch (type)
    {
    case 0:
        temp_account.balance += amount;
        std::cout<<"-Transaction succeeded\n";
        std::cout<<"-Current Balance: "<<temp_account.balance<<"\n";
        break;
    case 1:
        if(temp_account.balance >=amount){
            std::cout<<"-Transaction succeeded\n";
            temp_account.balance -= amount;
            std::cout<<"-Current Balance: "<<temp_account.balance<<"\n";
        }
        else{
            std::cout<<"-Transaction failed\n";
            std::cout<<"-Current Balance: "<<temp_account.balance<<", but the entered amount is larger\n";
        }
        break;
    default:
        std::cout<<"-Current Balance: "<<temp_account.balance<<"\n";
        break;
    }
    
    return;
}

std::pair<u_long, int> AtmController::m_parse_transaction(std::string &input){
    std::string op, amount;
    u_long money;
    if (input.size() == 1)
    {
        if (input[0] == 'b' ||input[0] == 'B'){
            return std::make_pair(0,2);
        }
        else if(input[0] == 'L' ||input[0] == 'l'){
            return std::make_pair(0,-1);
        }
        else{
            std::cout<<"-Invalid input, please try again\n";
            return std::make_pair(0,-2);
        }
    }
    else{
        op = input.substr(0, input.find(' '));
        amount = input.substr(input.find(' ') + 1, input.npos);
        bool temp = false;
        for (const auto &c: amount){
            if (!isdigit(c)){
                temp = true;
            }
        }
        if(temp){
            std::cout<<"-Invalid input, please try again\n";
            return std::make_pair(0,-2);
        }
        if (op.size() != 1){
            std::cout<<"-Invalid input, please try again\n";
            return std::make_pair(0,-2);
        }
        else{

            if (op[0] == 'W' || op[0] == 'w'){
                money = std::stoi(amount);
                return std::make_pair(money, 1);

            }
            else if (op[0] == 'D' || op[0] == 'd'){
                money = std::stoi(amount);
                return std::make_pair(money, 0);
            }
            else{
                std::cout<<"-Invalid input, please try again\n";
                return std::make_pair(0,-2);
            }

        }

    }


}

void AtmController::Run(){

    std::string input;
    u_long money;
    int type;
    std::pair<long unsigned int, int> mt;

    while(true){

        
    
        switch (m_state)
        {
        case CARD_OUT:
            std::cout<<m_welcoming_message;
            std::getline(std::cin, input);
            if (input.size() == 1){
                if(input[0] == 'c' ||input[0] == 'C'){
                    if(InsertAndValidateCard()){
                        std::cout<<"-The card has been inserted\n";
                        m_state = CARD_IN;
                    }
                    else{
                        std::cout<<"-The card validation failed\n";
                    }
                }
                else if(input[0] == 't' ||input[0] == 'T'){
                    return;
                }
                else{
                    std::cout<<"-Invalid input, please try again\n";
                    std::cout<<"For:\n\
                        -card insertion press C and Enter\n\
                        -program termination press T and Enter\n";
                }
            }
            else{
                std::cout<<"-Invalid input, please try again\n";
                std::cout<<"For:\n\
                    -card insertion press C and Enter\n\
                    -program termination press T and Enter\n";
            }
            break;
        case CARD_IN:
            std::cout<<m_menu;
            std::getline(std::cin, input);
            if (input.size() == 1){
                if(input[0] == 'n' ||input[0] == 'N'){
                    RegisterAccount();
                }
                else if(input[0] == 'l' ||input[0] == 'L'){
                    if (AccountLogin()){
                        m_state = ACCOUNT_MENU;
                    }
                }
                else if(input[0] == 'c' ||input[0] == 'C'){
                    m_state = CARD_OUT;
                }
                else{
                    std::cout<<"-Invalid input, please try again\n";
                    std::cout<<m_menu;

                }
            }
            else{
                std::cout<<"-Invalid input, please try again\n";
                std::cout<<m_menu;
            }
            break;
        case ACCOUNT_MENU:
            std::cout<<m_acccount_menu;
            std::getline(std::cin, input);
            mt = m_parse_transaction(input);
            money = mt.first;
            type = mt.second;
            switch (type)
            {
            case -2:
                break;
            case -1:
                m_state = CARD_IN;
                break;
            case 0:
                HandleTransaction(money, 0);
                break;
            case 1:
                HandleTransaction(money, 1);
                break;
            case 2:
                HandleTransaction(money, 2);
                break;
            default:
                break;
            }
            
            
            break;

        default:
            break;
        }

    }

    

}