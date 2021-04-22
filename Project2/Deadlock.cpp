#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <queue>
#include <cstdio>
#include <sstream>
#include <cstring>
using namespace std;
#define MatSize 100
int N = 0, M = 0; // N : Number of Process,  M : Number of ResourceType
vector<int> ResourceUnit; // Number of ResourceUnit;
int Alloc[MatSize][MatSize], Req[MatSize][MatSize];
int finish[MatSize];
vector<int> getRemainUnit();
void input();


int main(){
    input();
    for(int t=0; t<N; t++){
        vector<int> Remain = getRemainUnit();
        bool isDeadLockFlag = false;
        for(int i=0; i<N; i++){
            if(finish[i]) continue;
            bool isAllocableFlag = false;
            for(int j=0; j<M; j++){
                if(Req[i][j] > Remain[j]) { // 할당 불가능
                    isAllocableFlag = true;
                    break;
                }
            }
            if(!isAllocableFlag) { // 할당 가능하다면
                finish[i] = 1;
                isDeadLockFlag = true;
                for(int j=0; j<M; j++){
                    Alloc[i][j] = 0;
                    Req[i][j] = 0;
                }
                break;
            } 
        }
        if(!isDeadLockFlag) { // deadlock
            cout << "DEADLOCK !! \n";
            cout << "-----deadlocked process list-----" << endl;
            for(int i=0; i<N; i++) if(!finish[i]) cout << "Process " << i+1 << endl; 
            return 0;
        }
    }
    cout << "There is no Deadlock Process\n";
    return 0;
}

vector<int> getRemainUnit(){ // 남은 Resource 구하기
    vector<int> Remain;
    for(int i=0; i<M; i++){
        int cnt = 0;
        for(int j=0; j<N; j++){
            cnt += Alloc[j][i];
        }
        Remain.push_back(ResourceUnit[i] - cnt);
    }
    return Remain;
}

void input(){ // input처리
    memset(finish, 0, sizeof(finish));
    memset(Alloc, 0, sizeof(Alloc));
    memset(Req, 0, sizeof(Req));
    string line, temp;
	ifstream in("input.txt");
	getline(in, line);
    stringstream ss(line);
    getline(ss, temp, ' ');
    N = stoi(temp);
    getline(ss, temp, ' ');
    M = stoi(temp);
    while(getline(ss, temp, ' ')) ResourceUnit.push_back(stoi(temp));
    for(int i=0; i<N; i++){
        getline(in, line);
        stringstream ss(line);
        for(int j=0; j<M; j++){
            getline(ss, temp, ' ');
            Alloc[i][j] = stoi(temp);
        }
    }
    for(int i=0; i<N; i++){
        getline(in, line);
        stringstream ss(line);
        for(int j=0; j<M; j++){
            getline(ss, temp, ' ');
            Req[i][j] = stoi(temp);
        }
    }
    return;
}