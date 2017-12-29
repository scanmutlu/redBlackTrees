#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

struct node {
    string name;
    int age;
    string gender;
    string color;
    int maleCount;
    int femaleCount;
    node *left;
    node *right;
    node *parent;
};

struct rbTree {
    node *head;
    int nodeCount;
    void insert(struct node *x);
    void printTree(struct node* x);
    void recolor(struct node*& x);
    void lRotate(struct node* traverser);
    void rRotate(struct node* traverser);
    void countGender(struct node* traverser);
    struct node* findMan(struct node*traverser, int i);
    struct node* findWoman(struct node *traverser, int i);
    struct node* BStreeinsert(struct node*& traverser, struct node*& x);
} rbTree1;

void rbTree::printTree(struct node* x) {
    node* traverse;
    traverse = x;
    if(x != NULL){
        if(x->left){

            printTree(x->left);
        }
        traverse = x;
        while(traverse->parent){
            cout<<"         \t";
            traverse = traverse->parent;
        }
        if(x->parent){
            if(x == x->parent->left) cout<<"|````````"<< "("<<x->color <<")"<<x->name << "  " << x->gender <<x->femaleCount << x->maleCount << endl;
            if(x == x->parent->right) cout<<"L_________"<< "("<<x->color <<")"<<x->name << "  "<< x->gender << x->femaleCount << x->maleCount << endl;

        }else{
            cout<<x->name << '\t' << x->color << x->femaleCount << x->maleCount << endl;
        }


        if(x->right){

            printTree(x->right);
        }


    }

}

void rbTree::countGender(struct node *traver) {

    if (traver->left != NULL)
    {
        countGender(traver->left);
    }
    if (traver->right != NULL)
    {
        countGender(traver->right);
    }

    if(traver->gender.compare("M") == 0)traver->maleCount++;
    if(traver->gender.compare("F") == 0)traver->femaleCount++;

    if(traver->parent !=NULL){
        traver->parent->maleCount += traver->maleCount;
        traver->parent->femaleCount += traver->femaleCount;
    }


}

struct node* rbTree::findMan(struct node *traverser, int i) {
    int male;       // how many male at left.
    if(traverser->left)male = traverser->left->maleCount+1;
    else male = 1;

    if(i==male){
        if(traverser->gender.compare("M")==0)return traverser;
        else findMan(traverser->right,1);
    }else if(male > i){
        findMan(traverser->left,i);
    }else if(traverser->right) findMan(traverser->right,i-male+1);
    else return traverser;



}
struct node* rbTree::findWoman(struct node *traverser, int i) {
    int female;     //how many female at left
    if(traverser->left)female = traverser->left->femaleCount+1;
    else female = 1;

    if(i==female){
        if(traverser->gender.compare("F")==0)return traverser;
        else findWoman(traverser->right,1);
    }else if(female > i){
        findWoman(traverser->left,i);
    }else if(traverser->right) findWoman(traverser->right,i-female+1);
    else return traverser;

}


struct node* rbTree::BStreeinsert(struct node*& traverser, struct node *&x ) {

    if(traverser == NULL) {
        traverser = x;
        return traverser;
    }

    if(traverser->name.compare( x->name ) >0){
        x->parent = traverser;
        BStreeinsert(traverser->left,x);
    }else if (traverser->name.compare(x->name)<0){
        x->parent = traverser;
        BStreeinsert(traverser->right,x);
    }
}

void rbTree::recolor(struct node *&x) { //recolor functlion changing colors parent uncle and grandpa recursively.
    node* uncle ;
    if(x ==NULL || x->parent == NULL || x->parent->parent == NULL) return;
    if(x->parent == x->parent->parent->left){
        uncle = x->parent->parent->right;
    }else if(x->parent == x->parent->parent->right){
        uncle = x->parent->parent->left;
    }
    uncle->color = "B";
    x->parent->color = "B";
    x->parent->parent->color = "R";
    x = x->parent->parent;
    recolor(x);
}

void rbTree::rRotate(struct node* traverser) { 
    if(traverser->left ==NULL)return;

    struct node *leftNode = traverser->left;
    traverser->left = leftNode->right;
    if(leftNode->right)leftNode->right->parent = traverser;
    leftNode->parent = traverser->parent;
    if(traverser->parent == NULL){
        head = leftNode;
    }else if (traverser->parent->left == traverser){
        traverser->parent->left = leftNode;
    }else{
        traverser->parent->right = leftNode;
    }

    leftNode->right = traverser;
    traverser->parent = leftNode;
}

void rbTree::lRotate(struct node* traverser) {
    if(traverser->right ==NULL)return;

    struct node *rightNode = traverser->right;
    traverser->right = rightNode->left;
    if(rightNode->left)rightNode->left->parent  = traverser;
    rightNode->parent = traverser->parent;
    if(traverser->parent == NULL){
        head = rightNode;
    }else if (traverser->parent->left == traverser){
        traverser->parent->left = rightNode;
    }else{
        traverser->parent->right = rightNode;
    }

    rightNode->left = traverser;
    traverser->parent = rightNode;
}


void rbTree::insert(node *x) {
    x->color = "R";
    BStreeinsert(head,x);
    node* uncle;

    while (x != head && x->parent->color.compare("R") ==0 && x->parent->parent != NULL){
        if(x->parent == x->parent->parent->left){
            uncle = x->parent->parent->right;

            if( uncle!= NULL && uncle->color.compare("R") == 0){
                recolor(x);
            }else if(x == x->parent->right){        //left-right case : left Rotate , change color , right rotate
                x = x->parent;
                lRotate(x);
                //string tColor = x->parent->parent->color;
                x->parent->parent->color = "R";
                x->parent->color = "B";
                rRotate(x->parent->parent);

            }else{                                  //left-left case :  change color , right rotate
                //string tColor = x->parent->parent->color;
                x = x->parent;
                x->parent->parent->color = "R";
                x->parent->color = "B";
                rRotate(x);


            }

        }else if(x->parent == x->parent->parent->right){
            uncle = x->parent->parent->left;

            if(uncle != NULL && uncle->color.compare("R") == 0){
                recolor(x);
            }else if(x == x->parent->right){        //right-right case : change color , left rotate
                //string tColor = x->parent->parent->color;
                x = x->parent;
                x->parent->parent->color = "R";
                x->parent->color = "B";
                lRotate(x);



            }else{                                  //right-left case :  right rotate, change color , left Rotate
                x = x->parent;
                rRotate(x);
                //string tColor = x->parent->parent->color;
                x->parent->parent->color = "R";
                x->parent->color = "B";
                lRotate(x->parent->parent);

            }
        }
    }

    head->color = "B";
}


int main(int argc, char** argv) {


    if(argc != 2){
        cout << "Input parameters are wrong.  Ex: ./150130020 input.txt"<< endl;
    }
    string inputName;
    inputName = argv[1];
    ifstream file(inputName.c_str());
    string line;
    while (getline(file,line)) {
        istringstream isStream(line);
        struct node *tempNode = new node;
        string tempStr;

        getline(isStream, tempNode->name, '\t');
        getline(isStream, tempNode->gender, '\t');
        getline(isStream, tempStr);
        istringstream lineStr(tempStr);
        lineStr >> tempNode->age;
        //cout << tempNode->name <<'\t'<<tempNode->gender << '\t' << tempNode->age << endl;
        rbTree1.insert(tempNode);           // insert node to tree
    }
    rbTree1.countGender(rbTree1.head);
    rbTree1.printTree(rbTree1.head);
    node* temp;
    temp = rbTree1.findWoman(rbTree1.head,3);       // finding 3. women, Sending head paremeter firstly
    cout <<"3. Woman : "<< temp->name << endl;
    temp = rbTree1.findMan(rbTree1.head,4);
    cout <<"4. Man :  " << temp->name<< endl;
    return 0;
}

