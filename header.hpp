#ifndef HEADER
#define HEADER
#include <iostream>
#include <exception>
#include <fstream>
#include <string>
#include <sstream>

class TransactionFileHandler {
public:
    TransactionFileHandler(const std::string& filename);
    virtual ~TransactionFileHandler();
    bool getline(std::string& line);

private:
    std::ifstream m_file;
};

class InvalidCommandException {
public:
    InvalidCommandException(const std::string& str);
    virtual const std::string& what() const;

private:
    std:: string m_data;
};


class InsufficientFundsException  {
public:
    InsufficientFundsException(const std::string& str);
    virtual const std::string& what() const;

    private:
    std:: string m_data; 
};


class TransactionProcessor {
public:
    TransactionProcessor(const std::string& file_name);
    void check();


private:
    void check_instruction_size(const std::vector<std::string>& instruction);
    void check_instruction(const std::string& instruction);
    void check_argument(const std::string& argument);
    void check_deposit(int count);


    TransactionFileHandler m_file;
    int deposit;
    
};

#endif //HEADER