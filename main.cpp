#include <iostream>
#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)


int tests_run;

class Node {
  public:
    int val;
    Node *next=NULL;
    Node(int vala) {
        val = vala;
        next=NULL;
    }
    static Node * initialize(int arr[],int size){
        if(size==0)
            return NULL;
        Node * in=new Node(arr[0]);
        Node * temp=in;
        for(int i=1;i<size;i++){
            temp->next=new Node(arr[i]);
            temp=temp->next;
        }
        return in;
    }
    static void printNodes(Node * in){
        if(!in)
            printf("Empty list\n");
        Node * temp=in;
        while(temp){
            printf("%d, ",temp->val);
            temp=temp->next;
        }
    };
    static void releaseAll(Node * in){
        Node * temp=in;
        while(temp){
            free(temp);
            temp=temp->next;
        }
    }
    static Node * moveEvensToEnd(Node * in) {
        Node * pre_node=NULL;
        Node * even_list=NULL;
        Node * even_node=NULL;
        Node * ori_node=in;
        Node * ori_list=in;
       // Node * temp=ori_list;

        while(ori_node){
            //printf("%d",ori_node->val);

            if(ori_node->val%2==0){ //the current node is even

                if(even_list)
                    even_node->next = ori_node;
                else
                    even_list=ori_node;
                even_node=ori_node;
                ori_node = ori_node->next;
                even_node->next = NULL;
                if(pre_node)
                    pre_node->next=ori_node;
                else
                    ori_list=ori_node;
            }else{//the current node is not even
                pre_node=ori_node;
                ori_node=ori_node->next;
            }
        }


        if(pre_node)
             pre_node->next=even_list;
        else // if there is no odd number in the input or the input is NULL
            return even_list;
        return ori_list;
    }
};


class Unit_Test{
  public:
    static char * test_moveEvensToEnd(){
        //case 1
        int myList[] = {1, 5, 3, 6, 4, 1, 3};
        int size=sizeof(myList) / sizeof(int);
        Node * in =Node::initialize(myList,size);

        int answer_list[] ={1, 5, 3, 1, 3, 6, 4};
        Node * answer=Node::initialize(answer_list,size);
        mu_assert((char*)"test_moveEvensToEnd, result != [1, 5, 3, 1, 3, 6, 4]", compare_list(Node::moveEvensToEnd(in),answer)==0);
        Node::releaseAll(in);

        //case 2
        int myList2[] = {1, 2, 3, 6, 4, 1, 8};
        size=sizeof(myList2) / sizeof(int);

        in = Node::initialize(myList2,size);
        int answer_list2[] ={1, 3, 1, 2, 6, 4, 8};
        answer=Node::initialize(answer_list2,size);
        mu_assert((char*)"test_moveEvensToEnd, result != [1, 3, 1, 2, 6, 4, 8]", compare_list(Node::moveEvensToEnd(in),answer)==0);
        Node::releaseAll(in);

        //case 3
        int myList3[] = {1, 1, 1, 2, 1, 1, 1};
        size=sizeof(myList3) / sizeof(int);

        in = Node::initialize(myList3,size);
        int answer_list3[] ={1, 1, 1, 1, 1, 1, 2};
        answer=Node::initialize(answer_list3,size);
        mu_assert((char*)"test_moveEvensToEnd, result != [1, 1, 1, 1, 1, 1, 2]", compare_list(Node::moveEvensToEnd(in),answer)==0);
        Node::releaseAll(in);

        //case 4
        int myList4[] = {2,2};
        size=sizeof(myList4) / sizeof(int);

        in = Node::initialize(myList4,size);
        int answer_list4[] ={2,2};
        answer=Node::initialize(answer_list4,size);
        mu_assert((char*)"test_moveEvensToEnd, result != [1]", compare_list(Node::moveEvensToEnd(in),answer)==0);
        Node::releaseAll(in);

        //case 5
        int myList5[] = {};
        size=sizeof(myList5) / sizeof(int);

        in = Node::initialize(myList5,size);
        int answer_list5[] ={};
        answer=Node::initialize(answer_list5,size);
        mu_assert((char*)"test_moveEvensToEnd, result != []", compare_list(Node::moveEvensToEnd(in),answer)==0);
        Node::releaseAll(in);

        return 0;
    };

    static char * allTests(){
        mu_run_test(test_moveEvensToEnd);
        return 0;
    }

    static int unitTest(){
        char *result = allTests();
        if (result != 0) {
            printf("%s\n", result);
        }else {
            printf("ALL TESTS PASSED\n");
        }
        // printf("Tests run: %d\n", tests_run);

        return result != 0;
    }

    static int compare_list(Node* list1, Node *list2){
        while(list1&&list2){
            if(list1->val!=list2->val)
                return 1;
            list1=list1->next;
            list2=list2->next;
        }
        if((!list1)&&(!list2))
            return 0;
        return 1;
    }
};

 int main() {
     Unit_Test::unitTest();

     int myList[] = {6, 2, 3, 1, 4, 1, 9};
     int size=sizeof(myList) / sizeof(int);

     Node * in =  Node::initialize(myList,size);
     Node * list= Node::moveEvensToEnd(in);
     Node::printNodes(list);
     Node::releaseAll(list);
     return 0;
}


