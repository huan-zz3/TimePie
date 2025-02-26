#include "sqlite3db.h"

Sqlite3Database::~Sqlite3Database()
{
    if (db_)
    {
        sqlite3_close(db_);
    }
}

Result<void> Sqlite3Database::Connect(const std::string &connectionString)
{
    if (sqlite3_open(connectionString.c_str(), &db_) == SQLITE_OK)
    {
        connected = true;
        return Result<void>::Success();
    }
    else
    {
        connected = false;
        return Result<void>::Error(sqlite3_errmsg(db_));
    }
}

Result<void> Sqlite3Database::disConnect()
{
    if (db_)
    {
        sqlite3_close(db_);
        db_ = nullptr;
        connected = false;
        return Result<void>::Success();
    }
    else
    {
        return Result<void>::Error("Database is not connected.");
    }
}

// 定义一个名为 Sqlite3Database 的类中的成员函数 isConnected
// 该函数用于检查数据库是否已连接，并根据连接状态设置结果
Result<void> Sqlite3Database::isConnected()
{
    // 检查成员变量 connected 的值，以确定数据库是否已连接
    if (connected)
    {
        // 如果 connected 为 true，表示数据库已连接，调用 result 的 Success 方法
        return Result<void>::Success();
    }
    else
    {
        return Result<void>::Error("Database is not connected.");
    }
}

// 定义一个函数executeQuery，用于执行SQL查询
Result<std::vector<std::map<std::string, std::string>>> Sqlite3Database::executeQuery(const std::string &query)
{
    // 检查数据库是否已连接
    if (!connected)
    {
        // 如果未连接，调用result的Error方法返回错误信息
        return Result<std::vector<std::map<std::string, std::string>>>::Error("Database is not connected.");
    }

    // 定义一个指向错误信息的指针
    char *errMsg;
    // 定义一个用于存储查询结果的向量，每个元素是一个字符串到字符串的映射
    std::vector<std::map<std::string, std::string>> rows;

    // 执行SQL查询，使用sqlite3_exec函数
    // db_是数据库连接对象，query.c_str()是将查询字符串转换为C风格字符串
    // callback是用于处理查询结果的回调函数，&rows是传递给回调函数的用户数据
    // &errMsg用于存储错误信息
    if (sqlite3_exec(db_, query.c_str(), callback, &rows, &errMsg) != SQLITE_OK)
    {
        // 如果查询执行失败，调用result的Error方法返回错误信息
        auto result = Result<std::vector<std::map<std::string, std::string>>>::Error(errMsg);
        sqlite3_free(errMsg);
        return result;
    }
    else
    {
        // 如果查询执行成功，调用result的Success方法返回查询结果
        return Result<std::vector<std::map<std::string, std::string>>>::Success(rows);
    }
}

// 定义一个名为 executeNonQuery 的函数，用于执行不返回结果集的 SQL 查询
Result<void> Sqlite3Database::executeNonQuery(const std::string &query)
{
    // 检查数据库是否已连接
    if (!connected)
    {
        // 如果未连接，则调用 result 的 Error 方法返回错误信息 "Database is not connected."
        return Result<void>::Error("Database is not connected.");
    }

    char *errMsg;

    if (sqlite3_exec(db_, query.c_str(), 0, 0, &errMsg) != SQLITE_OK)
    {
        auto result = Result<void>::Error(errMsg);
        // std::cout << errMsg << std::endl;
        sqlite3_free(errMsg);
        return result;
    }
    else
    {
        return Result<void>::Success();
    }
}

// 定义一个函数，用于向SQLite数据库中插入数据
Result<void> Sqlite3Database::Insert(const std::string &tableName, const std::map<std::string, std::string> &data)
{
    // 检查数据库是否已连接
    if (!connected)
    {
        // 如果未连接，设置错误信息并返回
        return Result<void>::Error("Database is not connected.");
    }

    // 初始化列名和值的字符串
    std::string columns;
    std::string values;

    // 遍历数据映射，构建列名和值
    for (const auto &pair : data)
    {
        // 将列名添加到columns字符串，并加上逗号和空格
        columns += pair.first + ", ";
        // 将值添加到values字符串，并用单引号包围，加上逗号和空格
        values += "'" + pair.second + "', ";
    }

    columns.pop_back(); // Remove the last comma
    columns.pop_back(); // Remove the last space
    values.pop_back();  // Remove the last comma
    values.pop_back();  // Remove the last space

    std::string query = "INSERT INTO " + tableName + " (" + columns + ") VALUES (" + values + ");";

    return executeNonQuery(query);
}

// 定义一个函数，用于更新数据库中的数据
Result<void> Sqlite3Database::Update(const std::string &tableName, const std::map<std::string, std::string> &data, const std::string &condition)
{
    // 检查数据库是否已连接
    if (!connected)
    {
        // 如果未连接，则返回错误信息
        return Result<void>::Error("Database is not connected.");
    }

    // 初始化一个字符串，用于存储SQL语句中的SET子句
    std::string setClause;

    // 遍历传入的数据映射，构建SET子句
    for (const auto &pair : data)
    {
        // 将键值对转换为"key = 'value', "的格式，并添加到SET子句中
        setClause += pair.first + " = '" + pair.second + "', ";
    }

    setClause.pop_back(); // Remove the last comma
    setClause.pop_back(); // Remove the last space

    std::string query = "UPDATE " + tableName + " SET " + setClause + " WHERE " + condition + ";";

    return executeNonQuery(query);
}

// 定义Sqlite3Database类的Remove成员函数
// 参数result用于存储操作结果，tableName表示要删除记录的表名，condition表示删除记录的条件
Result<void> Sqlite3Database::Remove(const std::string &tableName, const std::string &condition)
{
    // 检查数据库是否已连接
    if (!connected)
    {
        // 如果数据库未连接，设置错误信息并返回
        return Result<void>::Error("Database is not connected.");
    }

    // 构建SQL删除语句
    // "DELETE FROM " + tableName + " WHERE " + condition + ";"
    // 例如，如果tableName是"user"，condition是"id = 1"，则生成的SQL语句为"DELETE FROM user WHERE id = 1;"
    std::string query = "DELETE FROM " + tableName + " WHERE " + condition + ";";

    // 执行非查询SQL语句，即删除操作
    return executeNonQuery(query);
}

// 定义一个回调函数，用于处理SQLite查询结果
int Sqlite3Database::callback(void *data, int argc, char **argv, char **azColName)
{
    // 将传入的void指针转换为std::vector<std::map<std::string, std::string>>类型的引用
    auto &rows = *reinterpret_cast<std::vector<std::map<std::string, std::string>> *>(data);
    // 创建一个map用于存储当前行的数据
    std::map<std::string, std::string> row;

    // 遍历每一列
    for (int i = 0; i < argc; i++)
    {
        // 将列名和对应的值存入map中，如果值为NULL，则存储空字符串
        row[azColName[i]] = argv[i] ? argv[i] : "";
    }

    // 将当前行的数据添加到结果集中
    rows.push_back(std::move(row));
    // 返回0表示回调函数执行成功
    return 0;
}
