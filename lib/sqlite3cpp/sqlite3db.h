#ifndef SQLITE3DB_H
#define SQLITE3DB_H

#include "result.hpp"

#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <map>

class Sqlite3Database
{
public:
    Sqlite3Database() : db_(nullptr) {}

    // 析构函数，用于清理Sqlite3Database对象
    ~Sqlite3Database();

    Result<void> Connect(const std::string& connectionString);
    Result<void> disConnect();
    Result<void> isConnected();

    Result<std::vector<std::map<std::string, std::string>>> executeQuery(const std::string& query);
    Result<void> executeNonQuery(const std::string& query);

    Result<void> Insert(const std::string& tableName, const std::map<std::string, std::string>& data);
    Result<void> Update(const std::string& tableName, const std::map<std::string, std::string>& data, const std::string& condition);
    Result<void> Remove(const std::string& tableName, const std::string& condition);

private:
    static int callback(void* data, int argc, char** argv, char** azColName);
    bool connected;
    sqlite3* db_;
};

#endif // SQLITE3DB_H