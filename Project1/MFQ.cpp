#include<iostream>
#include<algorithm>
#include <string>
#include <fstream>
#include <queue>
#include <cstdio>
#include <sstream>
#define INF 987654321
using namespace std;
struct process {
    int pid, at, Q, progress, step, occup;
    vector<int> burst;
};
struct processTimeStruct{
    int pid, AT, BT, TT, WT;
};
struct compare {
	bool operator()(process A, process B) {
		return A.at > B.at; //arriving time 작은 순서
	}
};
void input();
void printCPU();
void IOToReady();
void createToReady();
vector<int> parseStrToVec(string str, char ch);
priority_queue<process, vector<process>, compare> rq;
priority_queue<process, vector<process>, compare> MFQ[4];
priority_queue<process, vector<process>, compare> IO, IOTemp, IOReadyQ;
vector<process> exitV;
vector<processTimeStruct> processTimeVec;
vector<int> CPU;
int timeQuantum[4] = {1, 2, 4, INF};
int curTime = 1, totalProcNum = 0;
int main(){
    input();
    totalProcNum = rq.size();
    createToReady();
    while(1) {
        if(exitV.size() == totalProcNum) break;
        while(!IO.empty()) {
            process cur = IO.top(); IO.pop();
            cur.progress++;
            // cout << cur.pid << " " << cur.progress << endl;
            if(cur.progress == cur.burst[cur.step]){
                cur.step++;
                cur.progress = 0;
                cur.at = curTime;
                IOReadyQ.push(cur);
                continue;
            }
            IOTemp.push(cur);
        }
        IO = IOTemp;
        while(!IOTemp.empty()) IOTemp.pop();
        bool flag = false;
        for(int i=0; i<4; i++){
            if(!MFQ[i].empty()){
                process cur = MFQ[i].top(); MFQ[i].pop();
                CPU.push_back(cur.pid); flag = true;
                cur.progress++;
                cur.occup++;
                if(cur.progress == cur.burst[cur.step]){
                    createToReady();
                    IOToReady();
                    cur.at = curTime;
                    cur.step++;
                    cur.occup = 0;
                    cur.progress = 0;
                    if(cur.Q == 3) cur.Q = 3;
                    else cur.Q == 0 ? cur.Q = 0 : cur.Q = cur.Q-1;
                    // cout << "pid : " << cur.pid << " go to MFQ" << cur.Q << endl;
                    if(cur.step == cur.burst.size()) {
                        for(int j=0; j<processTimeVec.size(); j++){
                            if(processTimeVec[j].pid == cur.pid) processTimeVec[j].TT = curTime - processTimeVec[j].AT;
                        }
                        exitV.push_back(cur);
                    }
                    else {
                        // cout << cur.pid << "go to sleep" << endl;
                        IO.push(cur);
                    }
                    break;
                } else if(cur.occup == timeQuantum[i]){
                    createToReady();
                    IOToReady();
                    cur.at = curTime;
                    cur.occup = 0;
                    cur.Q == 3 ? cur.Q = 3 : cur.Q = cur.Q+1;
                    if(i <= 2) MFQ[i+1].push(cur);
                    else MFQ[i].push(cur);
                    // cout << "timeQuantume !! pid : " << cur.pid << " go to MFQ" << i << endl;
                    break;
                }
                MFQ[i].push(cur);
                break;
            }
        }
        if(!flag) {
            CPU.push_back(0);
            IOToReady();
        }
        curTime++;
    }
    printCPU();
    return 0;
}

void input(){
    string line;
	ifstream in("input.txt");
	getline(in, line);
	int lineNum = atoi(line.c_str());
    processTimeVec.push_back({0, 0, 0, 0});
    for(int i=0; i<lineNum; i++) {
        getline(in, line);
        vector<int> tmp, temp = parseStrToVec(line, ' ');
        process p = {temp[0], temp[1], temp[2], 0, 0, 0};
        processTimeVec.push_back({temp[0], temp[1], 0, 0, 0});
        for(int i=0; i<temp[3]*2-1; i++) {
            if((4+i) % 2 == 0) processTimeVec[temp[0]].BT += temp[4+i];
            tmp.push_back(temp[4+i]);
        }
        p.burst = tmp;
        rq.push(p);
    }
    return;
}

vector<int> parseStrToVec(string str, char ch) { // string 파싱
    vector<int> res;
	stringstream ss(str);
	string temp;
	while (getline(ss, temp, ch)) res.push_back(stoi(temp));
	return res;
}

void printCPU(){
    cout << endl;
    vector<pair<int, int> > v;
    int before = CPU[0];
    if(CPU.size() > 0) v.push_back({CPU[0], 1});
    for(int i=1; i<CPU.size(); i++) {
        if(CPU[i] != CPU[i-1]) v.push_back({CPU[i], 1});
        else v[v.size()-1].second++;
    }
    for(int i=0; i<v.size(); i++){
        cout << "|";
        for(int j=0; j<v[i].second/2; j++) cout << "-";
        if(v[i].first == 0) cout << "0" << "(" << v[i].second << ")";
        else cout << "P" << v[i].first << "(" << v[i].second << ")";
        for(int j=0; j<v[i].second/2; j++) cout << "-";
        cout << "|";
    }
    float TTSum = 0, WTSum = 0;
    for(int i=1; i<processTimeVec.size(); i++){
        TTSum += processTimeVec[i].TT;
        WTSum += processTimeVec[i].TT - processTimeVec[i].BT;
    }
    cout << endl;
    cout << "Average Turnaround Time : " << TTSum / totalProcNum << endl;
    cout << "Average Waiting Time : " << WTSum / totalProcNum << endl;
    return;
}

void createToReady(){
    while(!rq.empty()) {
        if(rq.top().at <= curTime) {
            process p = rq.top(); rq.pop();
            MFQ[p.Q].push(p);
        } else {
            break;
        }
    }
    return;
}

void IOToReady(){
    while(!IOReadyQ.empty()){
        process cur = IOReadyQ.top(); IOReadyQ.pop();
        // cout << "IO " << cur.pid << " moved to MFQ" << cur.Q << endl;
        MFQ[cur.Q].push(cur);
    }
    return;
}
