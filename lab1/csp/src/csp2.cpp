#include<bits/stdc++.h>
using namespace std;
#define input_file "C:\\Users\\86186\\Desktop\\mid\\input\\input0.txt"
#define output_file "C:\\Users\\86186\\Desktop\\mid\\output\\output0.txt"
struct person{
    int work;
    bool request[400][10];
};
int main(){
    cout<<"start"<<endl;
    ifstream in;
    //ofstream out;
    auto cinbackup=cin.rdbuf(in.rdbuf());
    //auto coutbackup=cout.rdbuf(out.rdbuf());
    in.open(input_file,ios::in);
    //out.open(output_file,ios::out);
    cin.rdbuf(in.rdbuf());
    //cout.rdbuf(out.rdbuf());
    cout<<"read finish"<<endl;
    int n,d,s;
    int flag=0;
    int temp;
    int works[400][10];//记录id
    scanf("%d,%d,%d",&n,&d,&s);
    getchar();//用来处理那个回车
    if(n>199){
        cout<<"too many people"<<endl;
        return 0;
    }
    person people[200];
    for(int i=1;i<=n;i++){
        people[i].work=0;
        for(int j=0;j<d;j++){
            for(int k=0;k<s;k++){
                scanf("%d,",&temp);
                if(temp==1){
                    people[i].request[j][k]=true;
                }
                else if(temp==0){
                    people[i].request[j][k]=false;
                }
                else{
                    cout<<"wrong input"<<endl;
                    return 0;
                }
            }
            getchar();//用来处理那个回车
        }
    }//输入用逗号隔开，以此考验我的应变能力
    /*for(int i=1;i<=n;i++){
        for(int j=0;j<d;j++){
            for(int k=0;k<s;k++){
                cout<<people[i].request[j][k]<<" ";
            }
            cout<<endl;
        }
    }*///输入成功
    cout<<n<<d<<s<<endl;
    
    int i=0,j=0,k=0;
    int pre_id=0;//上一个工作的人的id
    int min_work=0;//当前工作最少的人的工作量
    int min_id=0;//当前工作最少的人的id
    int ave_work=d*s/n;//目标平均工作量，也就是底线
    int remain_work=d*s;//剩余工作量
    int temp_work=ave_work;
    int find_id=0;//准备分配给的人的id
    int find_work=0;//准备分配给的人的之前工作量

    for(j=0;j<d;j++){
        for(k=0;k<s;k++){//进入一阶段大循环
            cout<<"running..."<<endl;
            find_id=0;
            find_work=temp_work;//初始化
            if((ave_work-min_work)*2>=remain_work){
                cout<<"jump!"<<endl;
                goto label2;//如果剩余工作量不多了，就直接跳到第二阶段
            }
            
            for(i=1;i<=n;i++){//第一找：愿做且未达标中，找最小
                if(people[i].request[j][k]==true&&people[i].work<find_work&&i!=pre_id){
                    find_id=i;
                    find_work=people[i].work;
                }
            }
            if(find_id){
                works[j][k]=find_id;
                people[find_id].work++;
                remain_work--;
                pre_id=find_id;
                min_work=ave_work;
                min_id=0;
                for(int i1=1;i1<=n;i1++){
                    if(people[i1].work<min_work){
                        min_work=people[i1].work;
                        min_id=i1;
                    }
                }
                continue;
            }//第一找结束，没找到才有下面的，不然下一个循环
            
            find_id=0;
            find_work=ave_work;
            for(i=1;i<=n;i++){//第二找，没达标中找最小，不管愿不愿意做
                if(people[i].work<find_work&&i!=pre_id){
                    find_id=i;
                    find_work=people[i].work;
                }
            }
            if(find_id){
                works[j][k]=find_id;
                people[find_id].work++;
                remain_work--;
                pre_id=find_id;
                min_work=ave_work;
                min_id=0;
                for(int i1=1;i1<=n;i1++){
                    if(people[i1].work<min_work){
                        min_work=people[i1].work;
                        min_id=i1;
                    }
                }
                continue;
            }//第二找结束，没找到才有下面的，不然下一个循环

            find_id=0;
            find_work=ave_work;
            for(i=1;i<=n;i++){//第三找，大家都达标了，愿做就行
                if(people[i].request[j][k]==true&&i!=pre_id){
                    find_id=i;
                    find_work=people[i].work;
                }
            }
            if(find_id){
                works[j][k]=find_id;
                people[find_id].work++;
                remain_work--;
                pre_id=find_id;
                min_work=ave_work;
                min_id=0;
                for(int i1=1;i1<=n;i1++){
                    if(people[i1].work<min_work){
                        min_work=people[i1].work;
                        min_id=i1;
                    }
                }
                continue;
            }//第三找结束，没找到才有下面的，不然下一个循环

            find_id=0;
            find_work=ave_work;
            for(i=1;i<=n;i++){//第四找，大家都达标了都不愿做，谁都行
                if(i!=pre_id){
                    find_id=i;
                    find_work=people[i].work;
                }
            }
            if(find_id){
                works[j][k]=find_id;
                people[find_id].work++;
                remain_work--;
                pre_id=find_id;
                min_work=ave_work;
                min_id=0;
                for(int i1=1;i1<=n;i1++){
                    if(people[i1].work<min_work){
                        min_work=people[i1].work;
                        min_id=i1;
                    }
                }
                continue;
            }//第四找结束，下一个循环
        }
    }
    cout<<"first over"<<j<<k<<endl;

    label2://二阶段：给工作最少的人猛补工作
    cout<<"j="<<j<<"k="<<k<<endl;
    int j1,k1;
    flag=0;
    for(j1=j;j1<d;j1++){
        for(k1=k;k1<s;k1++){
            if(flag==0){
                works[j1][k1]=min_id;
                people[min_id].work++;
                pre_id=min_id;
                flag++;
            }//给那个需要猛补工作的人
            else{
                find_id=0;
                find_work=ave_work;
                for(i=1;i<=n;i++){//先找没达标且愿意做的人
                    if(people[i].work<find_work&&people[i].request[j][k]==true&&i!=pre_id){
                        find_id=i;
                        find_work=people[i].work;
                    }
                }
                if(find_id){
                    works[j1][k1]=find_id;
                    people[find_id].work++;
                    pre_id=find_id;
                    flag--;
                    continue;
                }

                find_id=0;
                find_work=ave_work;
                for(i=1;i<=n;i++){//再找没达标的人
                    if(people[i].work<find_work&&i!=pre_id){
                        find_id=i;
                        find_work=people[i].work;
                    }
                }
                if(find_id){
                    works[j1][k1]=find_id;
                    people[find_id].work++;
                    pre_id=find_id;
                    flag--;
                    continue;
                }

                find_id=0;
                find_work=ave_work;
                for(i=1;i<=n;i++){//再找愿意做的人
                    if(people[i].request[j][k]==true&&i!=pre_id){
                        find_id=i;
                        find_work=people[i].work;
                    }
                }
                if(find_id){
                    works[j1][k1]=find_id;
                    people[find_id].work++;
                    pre_id=find_id;
                    flag--;
                    continue;
                }

                find_id=0;
                find_work=ave_work;
                for(i=1;i<=n;i++){//最后找谁都行
                    if(i!=pre_id){
                        find_id=i;
                        find_work=people[i].work;
                    }
                }
                if(find_id){
                    works[j1][k1]=find_id;
                    people[find_id].work++;
                    pre_id=find_id;
                    flag--;
                    continue;
                }
            }//给了其他人
        }
    }
    //分完了

    //输出
    int count=0;
    for(j=0;j<d;j++){
        for(k=0;k<s;k++){
            cout<<works[j][k]<<",\n"[k==s-1];
            if(people[works[j][k]].request[j][k]==true){
                count++;
            }
        }
    }
    cout<<count<<endl;
    cin.rdbuf(cinbackup);
    //cout.rdbuf(coutbackup);
    in.close();
    //out.close();
    return 0;
}