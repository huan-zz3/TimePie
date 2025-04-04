#ifndef SQLITE3DB_H
#define SQLITE3DB_H

#include "idatabase.h"
#include <sqlite3.h>
#include <iostream>

class Sqlite3Database : public IDatabase
{
public:
    Sqlite3Database() : IDatabase(), db_(nullptr) {}

    // 析构函数，用于清理Sqlite3Database对象
    ~Sqlite3Database() override;

    Result<void> Connect(const std::string& connectionString) override;
    Result<void> disConnect() override;
    Result<void> isConnected() override;

    Result<std::vector<std::map<std::string, std::string>>> executeQuery(const std::string& query) override;
    Result<void> executeNonQuery(const std::string& query) override;

    Result<void> Insert(const std::string& tableName, const std::map<std::string, std::string>& data) override;
    Result<void> Update(const std::string& tableName, const std::map<std::string, std::string>& data, const std::string& condition) override;
    Result<void> Remove(const std::string& tableName, const std::string& condition) override;

private:
    static int callback(void* data, int argc, char** argv, char** azColName);

    sqlite3* db_;
};

#endif // SQLITE3DB_H