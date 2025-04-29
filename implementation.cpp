#include "header.hpp"

TransactionFileHandler::TransactionFileHandler(const std::string& filename) {
    try {
    m_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    m_file.open(filename);
    }
    catch(const std::ios_base::failure& e) {
        std::cout << "error when open file " << e.what() << std::endl;
    } 
}

TransactionFileHandler::~TransactionFileHandler() {
    m_file.close();
}

bool TransactionFileHandler::getline(std::string& line) {
     if (!m_file.eof() && std::getline(m_file, line)) {
        return true;
     }
     return false;
}

InvalidCommandException::InvalidCommandException(const std::string& str) : m_data{str}{}

const std::string& InvalidCommandException::what() const {
    return m_data;
}

InsufficientFundsException::InsufficientFundsException(const std::string& str) : m_data{str} {}

const std::string& InsufficientFundsException::what() const{
    return m_data;
}

TransactionProcessor::TransactionProcessor(const std::string& file_name) : m_file(file_name), deposit{0} {}

void TransactionProcessor::check_instruction_size(const std::vector<std::string>& instruction) {
    if(instruction.size() != 2) {
           std::throw_with_nested(InvalidCommandException("Invalid argument"));
    }
    return;       
}

void TransactionProcessor::check_instruction(const std::string& instruction){
    if ((instruction != "DEPOSIT") && (instruction != "WITHDRAW")) {
        std::throw_with_nested(InvalidCommandException(instruction));
    }
    return; 
}
void TransactionProcessor::check_argument(const std::string& argument){
    for (const auto& i : argument) { 
        if ( i < '0' || i > '9') {
           std::throw_with_nested(InvalidCommandException(argument));
        }   
    }
    return; 
}

void TransactionProcessor::check_deposit(int count){
    if (deposit < count) {
        std::throw_with_nested(InsufficientFundsException(std::to_string(count)));
    }
    return;
}

void TransactionProcessor::check() {
    std::cout << "Starting Transaction Processor...\n" << std::endl;
    std::string line;
    int number_of_line = 0;
    int successful_commands = 0;
    int skipped_commands = 0;

    while (m_file.getline(line)) {
        ++number_of_line;
        std::stringstream ss(line);
        std::string word;
        std::vector<std::string> words;
        while (ss >> word && words.size() < 2) {
            words.push_back(word);
        }
        try {
            check_instruction_size(words);
            check_instruction(words[0]);
            check_argument(words[1]);
            if (words[0] == "DEPOSIT") {
                deposit += std::stoi(words[1]);
                std::cout << "[INFO] Processing: DEPOSIT " << words[1] << std::endl;
                ++successful_commands;
            }
            else if (words[0] == "WITHDRAW") {
                check_deposit(std::stoi(words[1]));
                deposit -= std::stoi(words[1]);
                std::cout << "[INFO] Processing: WITHRAW " << words[1] << std::endl;
                ++successful_commands;

            }
        }
        catch (const InvalidCommandException& e) {
            std::cerr << "Line: " << number_of_line << " [ERROR] InvalidCommandException: Unknown command: " << e.what() << std::endl;
            ++skipped_commands;
        }
        catch (const InsufficientFundsException& e) {
             std::cerr << "Line: " << number_of_line << " [ERROR] InsufficientFundsException: Not enough balance for withdrawal of " << e.what() << std::endl;
            ++skipped_commands;
        }
        catch (...) {
            std::cerr << "Line: " << number_of_line << "Unknown exception" << std::endl;
            ++skipped_commands;
        }
        line.clear();
    }
    std::cout << "\nTransaction Summary:\n" << std::endl;
    std::cout << "- Final Balance: " << deposit << std::endl;
    std::cout << "- Successful Commands: " << successful_commands << std::endl;
    std::cout << "- Skipped Commands (Errors): " << skipped_commands << std::endl;
    return;
}