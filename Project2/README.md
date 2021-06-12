# OS
<b>2021.1학기 성균관대학교 운영체제 수업  
Project2 : Deadlock Detection </b>  
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



