#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Check if there are enough command-line arguments
    if (argc < 4) {
        printf("Usage: %s hostname username password\n", argv[0]);
        return 1; // Exit with an error code
    }

    char hostname[80];
    char username[20];
    char password[40];

    strncpy(hostname, argv[1], sizeof(hostname)-1);
    hostname[sizeof(hostname) - 1] = '\0';

    strncpy(username, argv[2], sizeof(username)-1);
    username[sizeof(username) - 1] = '\0';

    strncpy(password, argv[3], sizeof(password)-1);
    password[sizeof(password) - 1] = '\0';

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize the MySQL connection
    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    // Connect to the MariaDB database
    if (mysql_real_connect(conn, hostname, username, password, "slurm_acct_db", 3306, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return 1;
    }

    // Execute an SQL query to show tables
    if (mysql_query(conn, "SHOW TABLES")) {
        fprintf(stderr, "mysql_query() failed\n");
        mysql_close(conn);
        return 1;
    }

    // Get the result set
    res = mysql_store_result(conn);

    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed\n");
        mysql_close(conn);
        return 1;
    }

    // Fetch and print the table names
    while ((row = mysql_fetch_row(res))) {
        printf("%s\n", row[0]);
    }

    // Free the result set and close the connection
    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}
