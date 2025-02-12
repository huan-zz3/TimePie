#ifndef IDATABASE_H
#define IDATABASE_H

#include "predefine.h"
#include <string>
#include <vector>
#include <map>

class IDatabase
{
public:
    explicit IDatabase(){};
    virtual ~IDatabase(){};

    virtual Result<void> Connect(const std::string& connectionString) = 0;
    virtual Result<void> disConnect() = 0;
    virtual Result<void> isConnected() = 0;

    // 执行查询操作
    virtual Result< std::vector<std::map<std::string, std::string>> > executeQuery(const std::string& query) = 0;

    // 执行非查询操作（如插入、更新、删除）
    virtual Result<void> executeNonQuery(const std::string& query) = 0;

    virtual Result<void> Insert(const std::string& tableName, const std::map<std::string, std::string>& data) = 0;
    virtual Result<void> Update(const std::string& tableName, const std::map<std::string, std::string>& data, const std::string& condition) = 0;
    virtual Result<void> Remove(const std::string& tableName, const std::string& condition) = 0;

protected:
    bool connected;
};

#endif // IDATABASE_H