#ifndef _LISTNODE_HPP_
#define _LISTNODE_HPP_

template<typename Q>
struct ListNode {
    ListNode* next;
    ListNode* pre;
    Q val;

    ListNode() : next(nullptr) {}
    ListNode(Q _val) : val(_val), pre(nullptr), next(nullptr) {}
    ListNode(Q _val, ListNode* _next) : val(_val), next(_next) {}
    ListNode(Q _val, ListNode* _pre, ListNode* _next) : val(_val), pre(_pre), next(_next) {}
    ListNode(const ListNode<Q>* rhs) : val(rhs->val), pre(rhs->pre), next(rhs->next) {}
};


#endif