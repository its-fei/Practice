#include <iostream>

//题目：反转单向链表


//单向链表
struct ListNode{
	int val;
	ListNode* next;
    ListNode(int value):val(value), next(nullptr) {};
};

//思路：双指针。pre前向指针，cur当前指针。
//将cur的next指针保存下来，然后断开指针指向前向指针，双指针向后移动，cur为空时结束，此时pre指向头结点指针进行返回。
ListNode* reverseListNode(ListNode* head) {
	ListNode* pre = nullptr;
	ListNode* cur = head;
	while (cur != nullptr) {
		ListNode* tmp = cur->next;
		cur->next = pre;
		pre = cur;
		cur = tmp;
	}
	return pre;
}

int main() {
    //创建链表
    ListNode* root = new ListNode(1);
    root->next = new ListNode(2);
    root->next->next = new ListNode(3);

    std::cout << "Original list: ";
    for (ListNode* p = root; p != nullptr; p = p->next) {
        std::cout << p->val << "  " ;
    }
    std::cout << std::endl;

    //反转链表
    ListNode* res = reverseListNode(root);
    std::cout << "Reversed list: ";
    for (ListNode* p = res; p != nullptr; p = p->next) {
        std::cout << p->val << "  " ;
    }
    std::cout << std::endl;

    //释放内存
    ListNode* cur = res;
    while (cur) {
        ListNode* next = cur->next;
        delete cur;
        cur = next;
    }
    return 0;
}
// 打印结果：
// Original list: 1  2  3  
// Reversed list: 3  2  1