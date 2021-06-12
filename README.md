# OS
<b>2021.1학기 성균관대학교 운영체제 수업</b>  

## Project1 : MFQ Scheduling Simulation  
> • 4개의 RQ를 갖는 MFQ 스케줄링 기법 구현   
• Q0: Time quantum 1인 RR 스케줄링 기법 사용   
• Q1: Time quantum 2인 RR 스케줄링 기법 사용   
• Q2: Time quantum 4인 RR 스케줄링 기법 사용   
• Q3: FCFS 스케줄링 기법 사용


<b>Input</b>  
> 프로세스 개수  
PID / 각 프로세스 별 도착 시간(AT) / Init Queue / # Cycles / 수행 트레이스(CPU-BurstTime, IO-BurstTime) 등  

<b>EXAMPLE</b>  
> input.txt  
5  
1 0 0 5 10 20 18 25 15 10 20 15 16  
2 1 0 6 55 15 40 20 45 18 50 20 40 15 50  
3 3 2 3 17 20 21 8 34  
4 23 1 3 19 28 10 3 5  
5 30 3 4 38 10 42 13 4 10 11  

Result  
> |P1(1)||P2(1)||-P1(2)-||-P2(2)-||--P3(4)--||--P1(4)--||--P2(4)--||------P3(13)------||---P4(6)---||-P1(3)-||------------------------P2(48)------------------------||-------------------P5(38)-------------------||------P4(13)------||----------P3(21)----------||---------P1(18)---------||--------------------P2(40)--------------------||---------------------P5(42)---------------------||-----P4(10)-----||-----------------P3(34)-----------------||-------P1(15)-------||----------------------P2(45)----------------------||--P5(4)--||--P4(5)--||----------P1(20)----------||-----P5(11)-----||-------------------------P2(50)-------------------------||--------P1(16)--------||--0(4)--||--------------------P2(40)--------------------||-------0(15)-------||-------------------------P2(50)-------------------------|  
P1's TT : 470s WT : 321s  
P2's TT : 578s WT : 210s  
P3's TT : 301s WT : 201s  
P4's TT : 350s WT : 285s  
P5's TT : 374s WT : 246s  
  
> Average Turnaround Time : 414.6s  
Average Waiting Time : 252.6s  

</br></br>
## Project2 : Deadlock Detection   
> • N개의 process와 M개의 resource type을 갖는 시스템에서 주어진 request matrix와 allocation matrix를 기준으로 deadlock detection을 수행<br/>
• Graph reduction 기법으로 deadlock detection <br/>
• Multiple resource types & multiple resource units 가정 <br/>
• Deadlock detection 결과로 현재 시스템에 **deadlock이 존재하는지 여부** 및 **deadlocked process list**를 출력 <br/>


<b>Input</b>  
> • 프로세스 개수 (N) 및 resource type 개수 (M), 각 resource type 별 resource unit 개수 (t1, t2, ..., tM)  <br/>
• Allocation matrix (N x M matrix) <br/>
– Aij = # of resource units of type Rj allocated to Pi  <br/>
• Request matrix (N x M matrix) <br/>
– Rij = # of resource units of type Rj requested by Pi <br/>   
> <img width="659" alt="스크린샷 2021-06-12 오후 6 53 05" src="https://user-images.githubusercontent.com/28529201/121772284-6e966f00-cbaf-11eb-9261-9cf2ebc6a95d.png">


<b>Output</b>  
> • Deadlock 상태 여부 <br/>
• Deadlock 상태인 경우 deadlocked process list <br/>

<b>EXAMPLE</b>  
> input.txt  
3 3 3 2 2<br/>
2 1 0<br/>
1 0 0<br/>
0 1 1<br/>
1 1 0<br/>
0 2 1<br/>
0 0 1<br/>

<b>Result</b>   
> DEADLOCK !!   
-----deadlocked process list-----   
Process 1   
Process 2   

</br></br>
## Project3 : Virtual Memory Management   
> • Demand paging system을 위한 page replacement 기법 구현 및 검증<br/>
• 주어진 page reference string을 입력 받아 각 replacement 기법으로 처리했을 경우의<br/>&nbsp;&nbsp;&nbsp;memory residence set 변화 과정 및 page fault 발생 과정 추적/출력   
• 사용한 replacement 기법
>> • MIN   
• FIFO   
• LRU   
• LFU   
• WS Memory Management


<b>Input</b>  
> • N은 process가 갖는 page 개수 (최대 100)   
• Page 번호는 0번부터 시작    
• M은 할당 page frame 개수 (최대 20, WS 기법에서는 비사용)   
• W는 window size (최대 100, WS 기법에서만 사용)      
• K는 page reference string 길이 (최대 1,000)   
• “r1 r2 r3 r4 r5 ∙∙∙ rK”는 page reference string   
> <img width="686" alt="스크린샷 2021-06-12 오후 7 03 28" src="https://user-images.githubusercontent.com/28529201/121772540-e1ecb080-cbb0-11eb-863b-4a688af5eecb.png">

<b>Output</b>  
> MIN   
총 page fault 횟수   
메모리 상태 변화 과정 (page fault 발생 위치 표시)   
FIFO   
총 page fault 횟수   
메모리 상태 변화 과정 (page fault 발생 위치 표시)   
LRU   
총 page fault 횟수   
메모리 상태 변화 과정 (page fault 발생 위치 표시)   
LFU   
총 page fault 횟수   
메모리 상태 변화 과정 (page fault 발생 위치 표시)   
WS   
총 page fault 횟수   
메모리 상태 변화 과정 (page fault 발생 위치 표시)   

<b>EXAMPLE</b>  
> input.txt  
6 3 3 15   
0 1 2 3 2 3 4 5 4 1 3 4 3 4 5   

<b>Result</b>   
> MIN   
>>TIME : 1   
Reference String : 0   
pageFaultCount : 1   
Pushed : 0   
<< memory state >>   
0   
TIME : 2   
Reference String : 1   
pageFaultCount : 2   
Pushed : 1   
<< memory state >>   
0 1   
TIME : 3   
Reference String : 2   
pageFaultCount : 3   
Pushed : 2   
<< memory state >>   
0 1 2   
TIME : 4   
Reference String : 3   
pageFaultCount : 4   
victim : 0   
Pushed : 3   
<< memory state >>   
3 1 2   
TIME : 5   
Reference String : 2   
<< memory state >>   
3 1 2   
TIME : 6   
Reference String : 3   
<< memory state >>   
3 1 2   
TIME : 7   
Reference String : 4   
pageFaultCount : 5   
victim : 2   
Pushed : 4   
<< memory state >>
3 1 4   
TIME : 8   
Reference String : 5   
pageFaultCount : 6   
victim : 3   
Pushed : 5   
<< memory state >>   
5 1 4   
TIME : 9   
Reference String : 4   
<< memory state >>   
5 1 4   
TIME : 10   
Reference String : 1   
<< memory state >>   
5 1 4   
TIME : 11   
Reference String : 3   
pageFaultCount : 7   
victim : 1   
Pushed : 3   
<< memory state >>   
5 3 4   
TIME : 12   
Reference String : 4   
<< memory state >>   
5 3 4   
TIME : 13   
Reference String : 3   
<< memory state >>   
5 3 4   
TIME : 14   
Reference String : 4   
<< memory state >>   
5 3 4   
TIME : 15   
Reference String : 5   
<< memory state >>   
5 3 4   
total Page Fault : 7   </br>

>FIFO   
>> TIME : 1   
Reference String : 0   
pageFaultCount : 1   
Pushed : 0   
<< memory state >>   
0   
TIME : 2   
Reference String : 1   
pageFaultCount : 2   
Pushed : 1   
<< memory state >>   
0 1   
TIME : 3   
Reference String : 2   
pageFaultCount : 3   
Pushed : 2   
<< memory state >>   
0 1 2   
TIME : 4   
Reference String : 3   
pageFaultCount : 4   
victim : 0   
Pushed : 3   
<< memory state >>   
3 1 2   
TIME : 5   
Reference String : 2   
<< memory state >>   
3 1 2      
TIME : 6   
Reference String : 3   
<< memory state >>   
3 1 2   
TIME : 7   
Reference String : 4   
pageFaultCount : 5   
victim : 1   
Pushed : 4   
<< memory state >>   
3 4 2   
TIME : 8   
Reference String : 5   
pageFaultCount : 6   
victim : 2   
Pushed : 5   
<< memory state >>   
3 4 5   
TIME : 9   
Reference String : 4   
<< memory state >>   
3 4 5   
TIME : 10   
Reference String : 1   
pageFaultCount : 7   
victim : 3   
Pushed : 1   
<< memory state >>   
1 4 5   
TIME : 11   
Reference String : 3   
pageFaultCount : 8   
victim : 4   
Pushed : 3   
<< memory state >>   
1 3 5   
TIME : 12   
Reference String : 4   
pageFaultCount : 9   
victim : 5   
Pushed : 4   
<< memory state >>   
1 3 4   
TIME : 13   
Reference String : 3   
<< memory state >>   
1 3 4   
TIME : 14   
Reference String : 4   
<< memory state >>   
1 3 4   
TIME : 15   
Reference String : 5   
pageFaultCount : 10   
victim : 1   
Pushed : 5   
<< memory state >>   
5 3 4   
total Page Fault : 10   

>LRU   
>>TIME : 1   
Reference String : 0   
pageFaultCount : 1   
Pushed : 0   
<< memory state >>   
0   
TIME : 2   
Reference String : 1   
pageFaultCount : 2   
Pushed : 1   
<< memory state >>   
0 1   
TIME : 3   
Reference String : 2   
pageFaultCount : 3   
Pushed : 2   
<< memory state >>   
0 1 2   
TIME : 4   
Reference String : 3   
pageFaultCount : 4   
victim : 0   
Pushed : 3   
<< memory state >>   
3 1 2   
TIME : 5   
Reference String : 2   
<< memory state >>   
3 1 2   
TIME : 6   
Reference String : 3   
<< memory state >>   
3 1 2   
TIME : 7   
Reference String : 4   
pageFaultCount : 5   
victim : 1   
Pushed : 4   
<< memory state >>   
3 4 2   
TIME : 8   
Reference String : 5   
pageFaultCount : 6   
victim : 2   
Pushed : 5   
<< memory state >>   
3 4 5   
TIME : 9   
Reference String : 4   
<< memory state >>   
3 4 5   
TIME : 10   
Reference String : 1   
pageFaultCount : 7   
victim : 3   
Pushed : 1   
<< memory state >>   
1 4 5   
TIME : 11   
Reference String : 3   
pageFaultCount : 8   
victim : 5   
Pushed : 3   
<< memory state >>   
1 4 3   
TIME : 12   
Reference String : 4   
<< memory state >>   
1 4 3   
TIME : 13   
Reference String : 3   
<< memory state >>   
1 4 3   
TIME : 14   
Reference String : 4   
<< memory state >>   
1 4 3   
TIME : 15   
Reference String : 5   
pageFaultCount : 9   
victim : 1   
Pushed : 5   
<< memory state >>   
5 4 3   
total Page Fault : 9   

>LFU   
>>TIME : 1   
Reference String : 0   
pageFaultCount : 1   
Pushed : 0   
<< memory state >>   
0   
TIME : 2   
Reference String : 1   
pageFaultCount : 2   
Pushed : 1   
<< memory state >>   
0 1   
TIME : 3   
Reference String : 2   
pageFaultCount : 3   
Pushed : 2   
<< memory state >>   
0 1 2   
TIME : 4   
Reference String : 3   
pageFaultCount : 4   
victim : 0   
Pushed : 3   
<< memory state >>   
3 1 2   
TIME : 5   
Reference String : 2   
<< memory state >>   
3 1 2   
TIME : 6   
Reference String : 3   
<< memory state >>   
3 1 2   
TIME : 7   
Reference String : 4   
pageFaultCount : 5   
victim : 1   
Pushed : 4   
<< memory state >>   
3 4 2   
TIME : 8   
Reference String : 5   
pageFaultCount : 6   
victim : 4   
Pushed : 5   
<< memory state >>   
3 5 2   
TIME : 9   
Reference String : 4   
pageFaultCount : 7   
victim : 5   
Pushed : 4   
<< memory state >>   
3 4 2   
TIME : 10   
Reference String : 1   
pageFaultCount : 8   
victim : 2   
Pushed : 1   
<< memory state >>   
3 4 1   
TIME : 11   
Reference String : 3   
<< memory state >>   
3 4 1   
TIME : 12   
Reference String : 4   
<< memory state >>   
3 4 1   
TIME : 13   
Reference String : 3   
<< memory state >>   
3 4 1   
TIME : 14   
Reference String : 4   
<< memory state >>   
3 4 1   
TIME : 15   
Reference String : 5   
pageFaultCount : 9   
victim : 1   
Pushed : 5   
<< memory state >>   
3 4 5   
total Page Fault : 9   

>WS   
>>TIME : 1   
Reference String : 0   
pageFaultCount : 1   
Pushed : 0   
<< memory state >>   
"0 - - - - -"   
TIME : 2   
Reference String : 1   
pageFaultCount : 2   
Pushed : 1   
<< memory state >>   
"0 1 - - - -"   
TIME : 3   
Reference String : 2   
pageFaultCount : 3   
Pushed : 2   
<< memory state >>   
"0 1 2 - - -"   
TIME : 4   
Reference String : 3   
pageFaultCount : 4   
Pushed : 3   
<< memory state >>   
"0 1 2 3 - -"   
TIME : 5   
Reference String : 2   
victim : 0   
<< memory state >>   
"- 1 2 3 - -"   
TIME : 6   
Reference String : 3   
victim : 1   
<< memory state >>   
"- - 2 3 - -"   
TIME : 7   
Reference String : 4   
pageFaultCount : 5   
Pushed : 4   
<< memory state >>   
"- - 2 3 4 -"   
TIME : 8   
Reference String : 5   
pageFaultCount : 6   
Pushed : 5   
<< memory state >>   
"- - 2 3 4 5"   
TIME : 9
Reference String : 4
victim : 2
<< memory state >>
"- - - 3 4 5"   
TIME : 10   
Reference String : 1   
pageFaultCount : 7   
victim : 3   
Pushed : 1   
<< memory state >>   
"- 1 - - 4 5"   
TIME : 11   
Reference String : 3   
pageFaultCount : 8   
Pushed : 3   
<< memory state >>   
"- 1 - 3 4 5"   
TIME : 12   
Reference String : 4   
victim : 5   
<< memory state >>   
"- 1 - 3 4 -"   
TIME : 13   
Reference String : 3   
<< memory state >>   
"- 1 - 3 4 -"   
TIME : 14   
Reference String : 4   
victim : 1   
<< memory state >>   
"- - - 3 4 -"   
TIME : 15   
Reference String : 5   
pageFaultCount : 9   
Pushed : 5   
<< memory state >>   
"- - - 3 4 5"   
total Page Fault : 9   



