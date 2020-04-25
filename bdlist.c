#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/slab.h>

struct birthday {
  int day;
  int month;
  int year;
  struct list_head list;
};

LIST_HEAD(birthday_list);list
struct birthday *createBirthday(int day, int month, int year) {
/* TODO: 생일을 위한 메모리를 할당하고, 인자들을 채워 생일을 완성하세요. */
  struct birthday *birth;
  birth=kmalloc(sizeof(*birth), GFP_KERNEL);
  birth->day=day;
  birth->month=month;
  birth->year=year;
  return birth;
}

int simple_init(void) {
  printk("INSTALL MODULE: bdlist\n");
  /* TODO: 생일 목록을 하나씩 생성하는대로 연결리스트에 연결시키세요(노드 삽입). */
  /* TODO: 완성된 연결리스트를 탐색하는 커널 함수를 사용하여 출력하세요. */
  struct birthday *birth1;
  struct birthday *birth2;
  struct birthday *birth3;
  struct birthday *birth4;
  struct birthday *birth5;

  birth1=createBirthday(13,4,1987);
  birth2=createBirthday(14,1,1964);
  birth3=createBirthday(2,6,1964);
  birth4=createBirthday(13,8,1986);
  birth5=createBirthday(10,6,1990);


  printk("Loading Module\n");
  list_add(&birth1->list, &birthday_list);
  list_add(&birth2->list, &birthday_list);
  list_add(&birth3->list, &birthday_list);
  list_add(&birth4->list, &birthday_list);
  list_add(&birth5->list, &birthday_list);
  
  struct birthday *ptr;
  list_for_each_entry(ptr,&birthday_list, list){
    printk("OS Module : Day %d. %d. %d\n",ptr->day,ptr->month,ptr->year);
  }
  
  return 0;
}

void simple_exit(void) {
  /* 모듈을 제거할 때는 생성한 연결 리스트도 하나씩 제거하며 끝내도록 하세요. */
  /* 제거를 하기 전에 리스트가 "비어있을 경우""에 대한 예외처리를 하는게 좋겠죠? */
  if(list_empty(&birthday_list))
  {
    printk("List is Empty\n");
    return;
  }
  /* TODO: 이제 본격적으로 연결리스트를 탐색하면서 하나씩 제거하도록 하시면 됩니다. */
  struct birthday *temp;
  struct list_head *ptr, *next;

  list_for_each_safe(ptr,next,&birthday_list)
  {
    temp=list_entry(ptr,struct birthday, list);
    printk("OS Module : Removing %d. %d. %d\n", temp->day, temp->month, temp->year);
    list_del(ptr);
    kfree(temp);
  }

  printk("REMOVE MODULE: bdlist\n");
  return;
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("make a list of birthdays and print");
MODULE_AUTHOR("황지원_2016007274");
