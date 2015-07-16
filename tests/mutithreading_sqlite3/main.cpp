#include <iostream>
#include <sqlite3.h>

#include <boost/thread.hpp>

using namespace std;


void init_database() {
    sqlite3 *pDb;

    int rc;

    rc = sqlite3_open("test.sqlite3", &pDb);

    if(rc) {
        cout<<sqlite3_errmsg(pDb);
        exit(0);
    } else {
        cout << "connection is set up."<<endl;

    }

    char *zErrMsg = 0;

    char sql[] = "create table if not exists tb_test ( name text, number integer);";
    rc = sqlite3_exec(pDb, sql,0,0, &zErrMsg);

    if (rc != SQLITE_OK) {
        cout << "SQL error "<<zErrMsg<<endl;
    }


    sqlite3_close(pDb);
}

void insert(sqlite3 *pDb) {
    char *zErrMsg = 0;

    char sql[] = "insert into tb_test values ( 'a', 1);";

    if (SQLITE_OK != sqlite3_exec(pDb, sql,0,0, &zErrMsg)) {
        cout << "SQL error "<<zErrMsg<<endl;
    }
}

int The_Callback(void *a_param, int argc, char **argv, char **column){
    for (int i=0; i< argc; i++)
        printf("%s,\t", argv[i]);
    printf("\n");
    return 0;
}

void read(sqlite3 *pDb) {
    char *zErrMsg = 0;

    char sql[] = "select count(name) from tb_test;";

    if (SQLITE_OK != sqlite3_exec(pDb, sql,The_Callback,0, &zErrMsg)) {
        cout << "SQL error "<<zErrMsg<<endl;
    }
}

boost::mutex mutex;

void worker1() {
    sqlite3 *pDb;

    int rc;

    rc = sqlite3_open("test.sqlite3", &pDb);

    if(rc) {
        cout<<sqlite3_errmsg(pDb);
        exit(0);
    } else {
        cout << "connection is set up."<<endl;
    }

    for (int n=0; n<20; n++) {
        mutex.lock();
        cout << "inserting " << n << endl;
        insert(pDb);
        mutex.unlock();
        boost::this_thread::sleep(boost::posix_time::milliseconds(300));
    }


    sqlite3_close(pDb);
}

void worker2() {
    sqlite3 *pDb;

    int rc;

    rc = sqlite3_open("test.sqlite3", &pDb);

    if(rc) {
        cout<<sqlite3_errmsg(pDb);
        exit(0);
    } else {
        cout << "connection is set up."<<endl;
    }

    for (int n=0; n<100; n++) {
        //mutex.lock();
        cout << "inserting " << n << endl;
        read(pDb);
        //mutex.unlock();
        boost::this_thread::sleep(boost::posix_time::milliseconds(200));
    }


    sqlite3_close(pDb);
}


int main() {
    init_database();
    boost::thread workerThread1(worker1);
    boost::thread workerThread2(worker1);

    boost::thread workerThread3(worker2);

    workerThread1.join();
    workerThread2.join();
    workerThread3.join();
}