#ifndef FAKE_DB_H
#define FAKE_DB_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>

class Query
{
public:
    Query (std::string&);
    virtual ~Query(){};
public:
    //tokenizer
    void parse_token();
    //checks whether such a DB already exists
    bool doesSuchDBExist(int index, std::string& str) const;
    //checks if the entered line matches the DB syntax
    virtual bool isRightSyntax() = 0;
protected:
    std::string m_instruct;
    std::vector<std::string> m_vec;
};

class QueryIUDS : public Query
{
public:
    QueryIUDS(std::string& str) : Query(str){};
    virtual ~QueryIUDS(){};
public:
    //checks if the given DB properties are entered correctly
    virtual bool isPropertyTrue (int index) const;
    //stores data describing DB
    void saveInfoDB(std::string&);
    //checks if the property type matches
    virtual bool isTypeTrue(int index) const;
protected:
    std::fstream m_file;
    std::vector<std::string> m_infoDB;
};

class QueryUDS : public QueryIUDS
{
public:
    QueryUDS(std::string& str) : QueryIUDS(str){};
    virtual ~QueryUDS(){};
public:
    //stores DB data
    void saveDataDB(int index);
    void helpSaveDataDB(std::string);
protected:
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_dataDB;
};

class Create : public Query
{
public:
    Create(std::string&);
    virtual ~Create(){};
public:
    bool isRightSyntax() override;
    bool isTypeTrue(std::string&) const;
    //Adds the created DB to the database list
    void addNameToTheDBList();
};

class Insert: public QueryIUDS
{
public:
    Insert(std::string&);
    virtual ~Insert(){};
public:
    bool isRightSyntax() override;
    bool isPropertyTrue(int index) const override;
    //Adds information to the selected DB
    void addDataToTheDB();
};

class Update: public QueryUDS
{
public:
    Update(std::string&);
    virtual ~Update(){};
public:
    bool isRightSyntax() override;
    bool isTypeTrue(int index) const override;
    //updates DB data
    void updateDataToTheDB();
    void helpUpdateDataToTheDB(std::string);
    //updates DB list
    void updateFileDB();
private:
    int indexWhere;
};

class Delete: public QueryUDS
{
public:
    Delete(std::string& str);
    virtual ~Delete(){};
public:
    bool isRightSyntax() override;
    //delete DB data
    void deleteDataToTheDB();
    //updates DB data
    void updateFileDB();
    //delete DB
    void deleteDB();
    //removes the DB name from the database list
    void removFileNameOfDBList();
};

class Select : public QueryUDS
{
public:
    Select(std::string& str);
    virtual ~Select(){};
public:
    bool isRightSyntax() override;
    //selects data from the selected DB
    void selectDataToTheDB();
    //prints the selected data
    void print();
};

#endif //FAKE_DB_H

