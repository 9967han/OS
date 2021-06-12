# OS
<b>2021.1학기 성균관대학교 운영체제 수업  
Project3 : Virtual Memory Management   
 </b>  
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
