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

    void Connect(Result<void> result, const std::string& connectionString) override;

    void disConnect(Result<void> result) override;

    void isConnected(Result<void> result) override;

    void executeQuery(Result<std::vector<std::map<std::string, std::string>>> result, const std::string& query) override;

    void executeNonQuery(Result<void> result, const std::string& query) override;

    void Insert(Result<void> result, const std::string& tableName, const std::map<std::string, std::string>& data) override;

    void Update(Result<void> result, const std::string& tableName, const std::map<std::string, std::string>& data, const std::string& condition) override;

    void Remove(Result<void> result, const std::string& tableName, const std::string& condition) override;

private:
    static int callback(void* data, int argc, char** argv, char** azColName);

    sqlite3* db_;
};

#endif // SQLITE3DB_H