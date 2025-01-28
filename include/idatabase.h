#ifndef IDATABASE_H
#define IDATABASE_H

#include "predefine.h"
#include <string>
#include <vector>
#include <map>

class IDatabase
{
public:
    explicit IDatabase();
    virtual ~IDatabase() = 0;

    virtual void Connect(Result<void>, const std::string& connectionString) = 0;
    virtual void disConnect(Result<void>) = 0;
    virtual void isConnected(Result<void>) = 0;

    // 执行查询操作
    virtual void executeQuery(Result< std::vector<std::map<std::string, std::string>> >, const std::string& query) = 0;

    // 执行非查询操作（如插入、更新、删除）
    virtual void executeNonQuery(Result<void>, const std::string& query) = 0;

    virtual void Insert(Result<void>, const std::string& tableName, const std::map<std::string, std::string>& data) = 0;
    virtual void Update(Result<void>, const std::string& tableName, const std::map<std::string, std::string>& data, const std::string& condition) = 0;
    virtual void Remove(Result<void>, const std::string& tableName, const std::string& condition) = 0;

private:
    bool connected;
};

#endif // IDATABASE_H