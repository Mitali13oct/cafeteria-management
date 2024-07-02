#include "DbOperation.h"

DatabaseRepository::DatabaseRepository(const std::string &db, const std::string &user, const std::string &password)
{
    init(db, user, password);
}

DatabaseRepository::~DatabaseRepository()
{
    closeConnection();
}

void DatabaseRepository::insert(const std::string &entityName, const std::map<std::string, std::string> &data)
{
    ensureInitialized();
    std::string query = "INSERT INTO " + entityName + " (";
    for (const auto &pair : data)
    {
        query += pair.first + ", ";
    }
    query.pop_back();
    query.pop_back();
    query += ") VALUES (";
    for (size_t i = 0; i < data.size(); ++i)
    {
        query += "?, ";
    }
    query.pop_back();
    query.pop_back();
    query += ")";

    executeQuery(query, data);
    std::cout<<"db\n";
}

void DatabaseRepository::update(const std::string &entityName, const std::map<std::string, std::string> &data, const std::map<std::string, std::string> &filter)
{
    ensureInitialized();
    std::string query = "UPDATE " + entityName + " SET ";
    for (const auto &pair : data)
    {
        query += pair.first + " = ?, ";
    }
    query.pop_back();
    query.pop_back();
    query += " WHERE ";
    for (const auto &pair : filter)
    {
        query += pair.first + " = ? AND ";
    }
    query = query.substr(0, query.size() - 5);

    executeQuery(query, data, filter);
}

sql::ResultSet *DatabaseRepository::selectAll(const std::string &entityName, const std::map<std::string, std::string> &filter, const std::map<std::string, std::string> &orderBy, const std::string &condition, const std::string& groupBy) const
{
    ensureInitialized();
    std::string query = "SELECT * FROM " + entityName;
    std::vector<std::string> queryParams;

    if (!filter.empty())
    {
        query += " WHERE ";
        for (const auto &pair : filter)
        {
           if (condition == "IN") {
                query += pair.first + " " + condition + " " + pair.second + " AND ";
            } else {
                query += pair.first + " " + condition + " ? AND ";
                queryParams.push_back(pair.second);
            }
        }
        query = query.substr(0, query.size() - 5);
    }
    if (!groupBy.empty())
    {
        query += " GROUP BY " + groupBy;
    }
    if (!orderBy.empty())
    {
        query += " ORDER BY ";
        for (const auto &pair : orderBy)
        {
            query += pair.first + " " + (pair.second == "asc" ? "ASC" : "DESC") + ", ";
        }
        query = query.substr(0, query.size() - 2);
    }

    return executeSelectQuery(query, queryParams);
}

sql::ResultSet *DatabaseRepository::selectOne(const std::string &entityName, const std::map<std::string, std::string> &filter)
{
    ensureInitialized();
    if (filter.empty())
    {
        throw std::invalid_argument("Filter is required");
    }

    std::string query = "SELECT * FROM " + entityName + " WHERE ";
    std::vector<std::string> queryParams;

    for (const auto &pair : filter)
    {
        query += pair.first + " = ? AND ";
        queryParams.push_back(pair.second);
    }
    query = query.substr(0, query.size() - 5);
    query += " LIMIT 1";

    return executeSelectQuery(query, queryParams);
}

void DatabaseRepository::remove(const std::string &entityName, const std::map<std::string, std::string> &filter)
{
    ensureInitialized();
    std::string query = "DELETE FROM " + entityName + " WHERE ";
    for (const auto &pair : filter)
    {
        query += pair.first + " = ? AND ";
    }
    query = query.substr(0, query.size() - 5);

    executeQuery(query, filter);
}

void DatabaseRepository::init(const std::string &db, const std::string &user, const std::string &password)
{
    try
    {
        sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
        connection = driver->connect("tcp://127.0.0.1:3306", user, password);
        connection->setSchema(db);
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "Error initializing connection: " << e.what() << std::endl;
        throw;
    }
}

void DatabaseRepository::ensureInitialized() const
{
    if (!connection)
    {
        throw std::runtime_error("Database connection not initialized.");
    }
}

void DatabaseRepository::closeConnection()
{
    if (connection)
    {
        delete connection;
        connection = nullptr;
    }
}

void DatabaseRepository::executeQuery(const std::string &query, const std::map<std::string, std::string> &data, const std::map<std::string, std::string> &filter)
{
    try
    {
        sql::PreparedStatement *pstmt = connection->prepareStatement(query);
        int index = 1;
        for (const auto &pair : data)
        {
            pstmt->setString(index++, pair.second);
        }
        for (const auto &pair : filter)
        {
            pstmt->setString(index++, pair.second);
        }
        pstmt->executeUpdate();
        delete pstmt;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "Error executing query: " << e.what() << std::endl;
        throw;
    }
}

sql::ResultSet *DatabaseRepository::executeSelectQuery(const std::string &query, const std::vector<std::string> &queryParams) const
{
    try
    {
        sql::PreparedStatement *pstmt = connection->prepareStatement(query);
        int index = 1;
        for (const auto &param : queryParams)
        {
            pstmt->setString(index++, param);
        }
        sql::ResultSet *res = pstmt->executeQuery();
        return res;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "Error executing select query: " << e.what() << std::endl;
        throw;
    }
}
