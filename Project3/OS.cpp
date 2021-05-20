#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <queue>
#include <cstdio>
#include <sstream>
#include <cstring>
#include <vector>
#define INF 987654321
using namespace std;
bool comp(pair<int, int> A, pair<int, int> B);
int getPopPage(int idx);
void printMemState();
void input();
void solve();
void FIFO();
void MIN();
void LRU();
void LFU();
void WS();
int N, M, W, K;
vector<int> pageFrame;
vector<int> pageRef;

int main(){
    input();
    solve();
}

void solve(){
    MIN();
    FIFO();
    LRU();
    LFU();
    WS();
    return;
}

void WS(){
    int pageFault = 0;
    int t = 1;
    int windowFrame[100];
    memset(windowFrame, 0, sizeof(windowFrame));
    cout << "WS" << endl << endl;
    for(int i=0; i<pageRef.size(); i++){
        cout << "TIME : " << t++ << endl;
        cout << "Reference String : " << pageRef[i] << endl;
        bool isExist = false;
        for(int j=i-W-1; j>=0 && j<i; j++){
            if(pageRef[j] == pageRef[i]){
                isExist = true;
                windowFrame[pageRef[i]] = t;
                break;
            }
        }
        if(isExist) {
            int popPage;
            windowFrame[pageRef[i]] = t;
            for(int j=0; j<N; j++){
                if(windowFrame[j] > 0 && windowFrame[j] < t-W){
                    windowFrame[j] = 0;
                    popPage = j;
                    cout << "victim : " << popPage << endl;
                }
            }
            cout << "<< memory state >> \n";
            for(int j=0; j<N; j++){
                if(windowFrame[j] == 0) cout << "- ";
                else cout << j << " ";
            }
            cout << endl << endl;
            continue; // 있으면 다음으로
        } else {
            pageFault++;
            cout << "pageFaultCount : " << pageFault << endl;
            int popPage;
            windowFrame[pageRef[i]] = t;
            for(int j=0; j<N; j++){
                if(windowFrame[j] > 0 && windowFrame[j] < t-W){
                    windowFrame[j] = 0;
                    popPage = j;
                    cout << "victim : " << popPage << endl;
                }
            }
            cout << "Pushed : " << pageRef[i] << endl;
        }
        cout << "<< memory state >> \n";
        for(int j=0; j<N; j++){
            if(windowFrame[j] == 0) cout << "- ";
            else cout << j << " ";
        }
        cout << endl << endl;
    }
    cout << "total Page Fault : " << pageFault << endl << endl;
    return;
}

void LFU(){
    int pageFault = 0;
    int t = 1;
    cout << "LFU" << endl << endl;
    struct freq{
        int tim, freq;
    };
    freq frequentCheck[100];
    for(int i=0; i<100; i++) {
        frequentCheck[i].freq = 0;
        frequentCheck[i].tim = 0;
    }
    for(int i=0; i<pageRef.size(); i++){
        cout << "TIME : " << t++ << endl;
        cout << "Reference String : " << pageRef[i] << endl;
        frequentCheck[pageRef[i]].freq++;
        frequentCheck[pageRef[i]].tim = t;
        bool isExist = false;
        for(int j=0; j<pageFrame.size(); j++){
            if(pageFrame[j] == pageRef[i]) {
                isExist = true;
                break;
            }
        }
        if(isExist) {
            printMemState();
            continue; // 있으면 다음으로
        }
        pageFault++;
        cout << "pageFaultCount : " << pageFault << endl;
        if(pageFrame.size() < M) { // PageFrame의 크기가 M이하 (꽉 차지 않음)
            pageFrame.push_back(pageRef[i]);
        } else {
            int minFreq = INF, recTime = 0;
            int popPage;
            for(int j=0; j<pageFrame.size(); j++){
                if(minFreq > frequentCheck[pageFrame[j]].freq){
                    minFreq = frequentCheck[pageFrame[j]].freq;
                    popPage = pageFrame[j];
                    recTime = frequentCheck[pageFrame[j]].tim;
                } else if(minFreq == frequentCheck[pageFrame[j]].freq && recTime > frequentCheck[pageFrame[j]].tim){
                    popPage = pageFrame[j];
                    recTime = frequentCheck[pageFrame[j]].tim;
                }
            }
            for(int j=0; j<pageFrame.size(); j++){
                if(pageFrame[j] == popPage){
                    pageFrame[j] = pageRef[i];
                    break;
                }
            }
            cout << "victim : " << popPage << endl;
        }
        cout << "Pushed : " << pageRef[i] << endl;
        printMemState();
    }
    cout << "total Page Fault : " << pageFault << endl << endl;
    pageFrame.clear();
    return;
}

void LRU(){
    int pageFault = 0;
    int t = 1;
    cout << "LRU" << endl << endl;
    int timeCheck[20];
    memset(timeCheck, 0, sizeof(timeCheck));
    for(int i=0; i<pageRef.size(); i++){
        cout << "TIME : " << t++ << endl;
        cout << "Reference String : " << pageRef[i] << endl;
        bool isExist = false;
        for(int j=0; j<pageFrame.size(); j++){
            if(pageFrame[j] == pageRef[i]) {
                timeCheck[j] = t;
                isExist = true;
                break;
            }
        }
        if(isExist) {
            printMemState();
            continue; // 있으면 다음으로
        }
        pageFault++;
        cout << "pageFaultCount : " << pageFault << endl;
        if(pageFrame.size() < M) { // PageFrame의 크기가 M이하 (꽉 차지 않음)
            pageFrame.push_back(pageRef[i]);
            timeCheck[pageFrame.size()-1] = t;
        } else {
            int minTime = INF;
            int popPage;
            for(int j=0; j<pageFrame.size(); j++) {
                if(minTime > timeCheck[j]){
                    minTime = timeCheck[j];
                    popPage = pageFrame[j];
                }
            }
            for(int j=0; j<pageFrame.size(); j++){
                if(pageFrame[j] == popPage){
                    pageFrame[j] = pageRef[i];
                    timeCheck[j] = t;
                    break;
                }
            }
            cout << "victim : " << popPage << endl;
        }
        cout << "Pushed : " << pageRef[i] << endl;
        printMemState();
    }
    cout << "total Page Fault : " << pageFault << endl << endl;
    pageFrame.clear();
    return;
}

void FIFO(){
    int pageFault = 0;
    int t = 1;
    cout << "FIFO" << endl << endl;
    queue<int> q;
    for(int i=0; i<pageRef.size(); i++){
        cout << "TIME : " << t++ << endl;
        cout << "Reference String : " << pageRef[i] << endl;
        bool isExist = false;
        for(int j=0; j<pageFrame.size(); j++){
            if(pageFrame[j] == pageRef[i]) {
                isExist = true;
                break;
            }
        }
        if(isExist) {
            printMemState();
            continue; // 있으면 다음으로
        }
        pageFault++;
        cout << "pageFaultCount : " << pageFault << endl;

        if(pageFrame.size() < M) { // PageFrame의 크기가 M이하 (꽉 차지 않음)
            pageFrame.push_back(pageRef[i]);
            q.push(pageRef[i]);
        } else {
            int popPage = q.front(); q.pop();
            for(int j=0; j<pageFrame.size(); j++){
                if(pageFrame[j] == popPage){
                    pageFrame[j] = pageRef[i];
                    break;
                }
            }
            cout << "victim : " << popPage << endl;
            q.push(pageRef[i]);
        }
        cout << "Pushed : " << pageRef[i] << endl;
        printMemState();
    }
    cout << "total Page Fault : " << pageFault << endl << endl;
    pageFrame.clear();
    return;
}

void MIN(){
    int pageFault = 0;
    int t = 1;
    cout << "MIN" << endl << endl;
    for(int i=0; i<pageRef.size(); i++){
        cout << "TIME : " << t++ << endl;
        cout << "Reference String : " << pageRef[i] << endl;
        bool isExist = false;
        for(int j=0; j<pageFrame.size(); j++){
            if(pageFrame[j] == pageRef[i]) {
                isExist = true;
                break;
            }
        }
        if(isExist) {
            printMemState();
            continue; // 있으면 다음으로
        }
        pageFault++;
        cout << "pageFaultCount : " << pageFault << endl;

        if(pageFrame.size() < M) { // PageFrame의 크기가 M이하 (꽉 차지 않음)
            pageFrame.push_back(pageRef[i]);
        } else {
            int popPage = getPopPage(i);
            for(int j=0; j<pageFrame.size(); j++){
                if(pageFrame[j] == popPage){
                    pageFrame[j] = pageRef[i];
                    break;
                }
            }
            cout << "victim : " << popPage << endl;
        }
        cout << "Pushed : " << pageRef[i] << endl;
        printMemState();
    }
    cout << "total Page Fault : " << pageFault << endl << endl;
    pageFrame.clear();
    return;
}

void printMemState(){
    cout << "<< memory state >> \n";
    for(int i=0; i<pageFrame.size(); i++){
        cout << pageFrame[i] << " ";
    }
    cout << endl << endl;
}

int getPopPage(int idx){
    vector<pair<int, int> > v;
    for(int i=0; i<pageFrame.size(); i++) {
        v.push_back(make_pair(pageFrame[i], INF));
        for(int j=idx+1; j<pageRef.size(); j++){
            if(v[i].first == pageRef[j]) {
                v[i].second = j;
                break;
            }
        }
    }
    sort(v.begin(), v.end(), comp);
    return v[0].first;
}

bool comp(pair<int, int> A, pair<int, int> B){
    if(A.second == B.second) return A.first < B.first;
    return A.second > B.second;
}


void input(){
    string line, temp;
	ifstream in("input2.txt");
	getline(in, line);
    stringstream ss(line);
    getline(ss, temp, ' ');
    N = stoi(temp);
    getline(ss, temp, ' ');
    M = stoi(temp);
    getline(ss, temp, ' ');
    W = stoi(temp);
    getline(ss, temp, ' ');
    K = stoi(temp);
    getline(in, line);
    stringstream ss2(line);
    for(int i=0; i<K; i++){
        getline(ss2, temp, ' ');
        pageRef.push_back(stoi(temp));
    }
    return;
}