//#include<iostream>
//#include<queue>
//using namespace std;
//const long LEN = 362880;
//
//struct node{
//    int state[9];
//    int distance;
//};
//
//int start[9];
//int goal[9];
//int visited[9] = {0};
//long int factory[] = {1,1,2,6,120,720,5040,40320,362880};
//
//int direction[4][2] = {{-1, 0}, {0,-1}, {1,0}, {0,1}};
//
//bool cantor(int str[], int n){
//    
//    long result = 0;
//    for(int i=0; i<n; i++){
//        int counted = 0;
//        for(int j=i; j<n; j++){
//            if(str[i]<str[j])
//            ++counted;
//        }
//        result += factory[n-i-1]*counted;
//    }
//    if(!visited[result]){
//        visited[result] = 1;
//        return 1;
//    }
//    else return 0;
//}
//
//int bfs(){
//    node head;
//    memcmp(head.state, start, sizeof(head.state));
//    head.distance = 0;
//    queue<node>q;
//    cantor(head.state, 9);//对起点的visited赋值
//    q.push(head);
//
//    while(!q.empty()){
//        
//        head = q.front();
//        q.pop();
//        int z;
//        for(z=0;z<9; z++){
//            if(head.state[z]==0)
//            break;
//        }
//        int x = z%3;
//        int y = z/3;
//        for(int i=0; i<4; i++){
//            int nx = x + direction[i][0];
//            int ny = y + direction[i][1];
//            int nz = nx + ny*3;
//            if(nx>=0 && nx<3 && ny>=0 && ny<3){
//                node newnode;
//                memcpy(&newnode,&head, sizeof(struct node));
//                swap(newnode.state[z], newnode.state[nz]);
//                newnode.distance++;
//                if(memcmp(newnode.state, goal, sizeof(goal))==0)
//                return newnode.distance;
//                if(cantor(newnode.state, 9))
//                q.push(newnode);        
//            }
//        }
//    }
//    return -1;
//}
//
//int main(){
//    for(int i=0; i<9; i++)cin>>start[i];
//    for(int i=0; i<9; i++)cin>>goal[i];
//    int num = bfs();
//    if(num==-1)cout<<"Impossible"<<endl;
//    else cout<<num<<endl;
//    return 0;
//}
//
