#include <iostream>
#include <algorithm>
using namespace std;

struct process
{
      int runned_time = 0;
      int arrival_time, burst_time, start_time,end_time, waiting_time, turnaround_time;
      int status;
};
process process_queue[100];
int number_of_process = 0;
double total_waiting_time = 0,total_turnAround_time = 0;
void Arrival_Time_Sorting()
{
      struct process temp;
      int i, j;
      for(i = 0; i < number_of_process - 1; i++)
      {
            for(j = i + 1; j < number_of_process; j++)
            {
                  if(process_queue[i].arrival_time > process_queue[j].arrival_time)
                  {
                        temp = process_queue[i];
                        process_queue[i] = process_queue[j];
                        process_queue[j] = temp;
                  }
            }
      }
}

 bool isAllFinished() 
 {
      for(int i = 0; i < number_of_process; i++)
      {
           if (process_queue[i].status != 2)
               return false;
      }
     return true;
 }

void calculateTurnAroundAndWaitingTime() 
 {
      for(int i = 0; i < number_of_process; i++)
      {
           process_queue[i].waiting_time = process_queue[i].end_time - process_queue[i].arrival_time - process_queue[i].burst_time;
          process_queue[i].turnaround_time = process_queue[i].end_time - process_queue[i].arrival_time;
          total_waiting_time += process_queue[i].waiting_time;
          total_turnAround_time += process_queue[i].turnaround_time;
      }

 }
int main() {
    int time = 0, burst_time = 0, largest;
    cin>>number_of_process;
    for (int i=0;i<number_of_process;i++) {
        std::cout<<"enter detail for process "<<i<<endl;
        cin>>process_queue[i].arrival_time>>process_queue[i].burst_time;
        process_queue[i].status = 0;
    }
        
    Arrival_Time_Sorting();
    cout<<"\nArrival Time\tBurst Time\n";
    for(int i=0; i < number_of_process; i++)
    {
        cout<<process_queue[i].arrival_time<<"\t"<<process_queue[i].burst_time<<endl;
    }
    process_queue[99].burst_time = 9999;
    time = process_queue[0].arrival_time;
     while( !isAllFinished())
      {
         //cout<<"enter"<<time<<"\t"<<largest<<endl;
            largest = 99;
            for(int i = 0; i < number_of_process; i++)
            {
                  if(process_queue[i].arrival_time <= time && process_queue[i].status != 2 && process_queue[i].burst_time                   < process_queue[largest].burst_time)
                  {
                        largest = i;
                  }
            }
            
            //cout<<"findout"<<time<<"\t"<<largest<<endl; 
           // cout<<"status";
             if (process_queue[largest].status == 0) {
                   process_queue[largest].status = 1;
                   process_queue[largest].start_time = time;    
            }
                time +=1;
              process_queue[largest].runned_time += 1;
            if (process_queue[largest].runned_time == process_queue[largest].burst_time ){
                process_queue[largest].status = 2;
                   process_queue[largest].end_time = time; 
            }
         
      }
    
    calculateTurnAroundAndWaitingTime();
    cout<<"\nArrival Time\tBurst Time\tStart Time\tEnd Time\tWaiting Time\tTurnAround TIme\n";
    for(int i=0; i < number_of_process; i++)
    {
        cout<<process_queue[i].arrival_time<<"\t"<<process_queue[i].burst_time<<"\t"<<process_queue[i].start_time<<"\t"<<process_queue[i].end_time<<"\t"<<process_queue[i].waiting_time<<"\t"<<process_queue[i].turnaround_time<<endl;
    }
    
    cout<<"\nAverage Waiting Time:-\t"<<total_waiting_time/number_of_process<<endl;
    cout<<"\nAverage TuenAround Time:-\t"<<total_turnAround_time/number_of_process<<endl;
  return 0;
}
