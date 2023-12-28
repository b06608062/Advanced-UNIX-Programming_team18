#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

// 定義一個結構體來表示定時器節點
typedef struct TimerNode {
  struct timeval end_time; // 定時器結束時間
  struct TimerNode *next;  // 指向下一個定時器節點的指針
} TimerNode;

TimerNode *head = NULL; // 定義一個指向定時器鏈表頭部的全局指針

// 釋放所有定時器節點的內存
void freeTimers() {
  while (head) {
    TimerNode *temp = head;
    head = head->next;
    free(temp);
  }
}

// 插入一個新的定時器到鏈表中，並保持鏈表按結束時間排序
void insertTimer(struct timeval end_time) {
  TimerNode *node = (TimerNode *)malloc(sizeof(TimerNode));
  node->end_time = end_time;
  node->next = NULL;

  // 如果鏈表為空或新定時器的結束時間最早，則將其插入到鏈表頭部
  if (!head || timercmp(&end_time, &head->end_time, <)) {
    node->next = head;
    head = node;
    alarm(end_time.tv_sec - time(NULL)); // 設置新的 alarm
  } else {
    // 否則，遍歷鏈表，找到適合的插入位置
    TimerNode *current = head;
    while (current->next && timercmp(&end_time, &current->next->end_time, >)) {
      current = current->next;
    }
    node->next = current->next;
    current->next = node;
  }
}

// 當定時器信號被觸發時執行的處理函數
void alarmHandler(int sig) {
  if (head) {
    TimerNode *temp = head;
    head = head->next;
    free(temp);

    // 如果鏈表中還有其他定時器，則設置下一個定時器
    if (head) {
      struct timeval now;
      gettimeofday(&now, NULL);
      alarm(head->end_time.tv_sec - now.tv_sec);
    }
  }
  printf("Alarm!\n");
}

// 設置一個新的定時器
void setAlarm(int sec) {
  struct timeval now, end_time;
  gettimeofday(&now, NULL);
  end_time.tv_sec = now.tv_sec + sec;
  end_time.tv_usec = now.tv_usec;

  insertTimer(end_time); // 將新定時器插入到鏈表中
}

// 清除所有定時器
void clearAlarm() {
  freeTimers(); // 釋放所有定時器節點的內存
  alarm(0);     // 取消當前的 alarm
}

int main() {
  signal(SIGALRM, alarmHandler); // 設置信號處理函數

  // 測試設置和清除定時器的邏輯
  setAlarm(2); // 在程式開始後2秒設置定時器
  sleep(1);
  setAlarm(6); // 在程式開始後1秒設置定時器，將在總共7秒後觸發
  sleep(1);
  setAlarm(3); // 在程式開始後2秒設置定時器，將在總共5秒後觸發
  sleep(4);
  clearAlarm(); // 在程式開始後6秒清除所有定時器

  return 0;
}
