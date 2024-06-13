

#include <bits//stdc++.h>
using namespace std;
void introduction()
{
    cout<<endl;
    cout<<"\033[1;31m                                                     HELLO BUDDY\033[0m";
    cout<<endl<<endl<<endl<<endl;
    cout << "\033[1;34m                                              THE       RUSTIC       PUZZLE \033[0m" << endl;
    cout<<endl<<endl<<endl;
    cout<<"this Game is about a farmer Harry and his village comprise various levels and challenges ";
    cout<<"\n so , here you are playing the role of the farmer , there will be many problems statements \n related to his livlihood , will come and you have to help his character ";
    cout<<" to solve those challenges \n \n ";


}
int solverope(vector<vector<pair<char,int>>>& grid, int n, int m,int c)
{int mincell=0;
    priority_queue<pair<int,pair<int,int>>>pq;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(grid[i][j].first=='C')
            {
                pq.push({grid[i][j].second,{i,j}});
                grid[i][j].first='-';
            }
        }
    }
    while(c>0)
    {
        auto topi=pq.top();
        pq.pop();

        grid[topi.second.first][topi.second.second].first='C';
        c-=topi.first;
        mincell++;

    }
    return mincell;
}
void solveUsingDP(vector<vector<pair<char,int>>>& grid, int n, int m, int i, int j, vector<vector<int>>& dp)
{
    // Check bounds
    if (i >= n || j >= m) return ;

    // Check if the cell is occupied or invalid for cow placement
    if (grid[i][j].first == '*' || grid[i][j].first == 'B') return ;



    // Check for adjacent buffaloes, ensuring we're within bounds
    int deltas[8][2] = {{-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}};
    for (auto& delta : deltas)
    {
        int ni = i + delta[0], nj = j + delta[1];
        if (ni >= 0 && ni < n && nj >= 0 && nj < m && grid[ni][nj].first == 'B')
        {
            return; // Can't place a cow here due to adjacent buffalo
            break; // No need to continue checking other adjacent cells
        }
    }

    grid[i][j].first='C';
}
int minimizecell(vector<vector<pair<char,int>>>& grid, int n, int m, int i, int j,  int c,vector<vector<bool>>&visited)
{
    // Base case: out of bounds
    if (i >= n ||i<0|| j >= m||j<0) return  1e9;



    // Base case: no more ropes to use
    if (c <= 0) return 0;

    // Base case: already computed
    int down,left,right,up;

    if(visited[i][j] == false)
    {
        visited[i][j] = true;
        if(grid[i][j].first=='C')
        {
            right = minimizecell(grid, n, m, i, j + 1,  c-grid[i][j].second,visited) + 1;

            // Recursive calls for all possible movements
            down = minimizecell(grid, n, m, i + 1, j,  c-grid[i][j].second,visited) + 1;
/*left = minimizecell(grid, n, m, i, j - 1,  c-grid[i][j].second,visited) + 1;
            up = minimizecell(grid, n, m, i - 1, j,  c-grid[i][j].second,visited) + 1;
*/
            // Find the minimum number of cells needed

        }
        else
        {
            right = minimizecell(grid, n, m, i, j + 1, c,visited);

            // Recursive calls for all possible movements
            down = minimizecell(grid, n, m, i + 1, j, c,visited);
            /*left = minimizecell(grid, n, m, i, j - 1,  c,visited);
            up = minimizecell(grid, n, m, i - 1, j,  c,visited);*/
        }
    }

    // Memoize the result

    return min(right, min(down, min(left, up)));
}

int  puzzle1()
{
    //vector<vector<vector<int>>>dp(n,vector<int>(m,vector<int>()))
    cout<<" Hello Buddy , so this is the first level , Harry want to purchase a stable ";
    cout<<endl<<"suggest the dimension of the stable ";
    int n,m;
    cout<<"enter the dimensions \n";
    cin>>n;
    cout <<" * ";
    cin>>m;
    cout<<"Graceful!! , you have bought this land :- \n";
    for(int i=0; i<n; i++)
    {

        for(int j=0; j<m; j++)
        {

            cout<<"  -  ";
        }
        cout<<endl<<endl;
    }
    vector<vector<pair<char,int>>>grid(n,vector<pair<char,int>>(m, {'-',0}));
    for(auto &i:grid)
    {
        for(auto &j:i)
        {
            j.second=rand()%5;
            if(j.second==0)
                j.second++;
        }
    }

    cout<<" Now , in that stable , Harry want to install the cattle-feed at certain places so suggest him the places where he can install";
    int c=0;
    int ans=1;
    while(ans)
    {
        cout<<"enter the row-col number where u want to install";
        int r,c;
        cin>>r>>c;
        grid[r][c].first='*';
        cout<<"wanna add more ?";
        cin>>ans;

    }
    cout<<"Now the grid is :- \n";
    for(int i=0; i<n; i++)
    {

        for(int j=0; j<m; j++)
        {

            cout<<grid[i][j].first<<"   ";
        }
        cout<<endl<<endl;
    }
    int tempm=m;
    for(int i=0; i<tempm; i++)
    {
        int k,l;
        k=rand()%n;
        l=rand()%m;
        if(grid[k][l].first!='*')
            grid[k][l].first='B';
        else
        {
            tempm++;

        }

    }
    cout<<"Now , Harry want to buy cows for his stable but he has several problems to deal before installing the cows in his stable;\n";
    cout<<"1. He had several buffaloes earlier which he now shifted in this new stable , and being known of cattle behavior he realized";
    cout<<" that  A COW AND BUFFALO MUST BE ATLEAST ONE GRID AWAY , THEY CAN'T BE PLACED EITHER DIAGONALLY OR LEFT-RIGHT WISE ADJACENT ";
    cout<<" \n 2. He had installed cattle feed spaces so in that place neither buffalo nor cow can be placed "<<endl;
    cout<<"\n 3. Around the feed spaces , not more than four cattles can be placed , all around , including diagonals "<<endl;

    cout<<" With these restrictions,Harry have to obtain no. of maximum cows that he can place ";
    cout<<endl<<endl<<"now the final grid structure of the stable is:- \n";
    for(int i=0; i<n; i++)
    {

        for(int j=0; j<m; j++)
        {

            cout<<grid[i][j].first<<"   ";
        }
        cout<<endl<<endl;
    }
    vector<vector<int>>dp(n,vector<int>(m,-1));
    int countcow=0;
    for(int i=0; i<n; i++)
    {

        for(int j=0; j<m; j++)
        {
            solveUsingDP(grid, n,m,i,j,dp);
        }
    }

    for(auto i:grid)
    {
        for(auto j:i)
        {
            if(j.first=='C')
                countcow++;
        }

    }
    int v=0;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(grid[i][j].first=='*')
            {
                int deltas[8][2] = {{-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}};
                for (auto& delta : deltas)
                {
                    int ni = i + delta[0], nj = j + delta[1];
                    if (ni >= 0 && ni < n && nj >= 0 && nj < m && (grid[ni][nj].first == 'B'||grid[ni][nj].first == 'C'))
                    {
                        v++;// No need to continue checking other adjacent cells
                        if(v>4)
                        {
                            countcow--;
                            grid[ni][nj].first='-';
                        }
                    }
                }
            }
        }
    }
    for(auto i:grid)
    {

        for(auto j:i)
        {
            cout<<j.first<<"        ";
        }
        cout<<endl;
    }

    cout<<countcow<<" no . of cows are needed , now farmer want to optimize his land by using it for other works so he tries to minimise the cows 's space by inculcating ";
    cout<<"them in single cells according to the ropes that each cell possess as given :- \n";
    for(auto i:grid)
    {

        for(auto j:i)
        {
            cout<<j.second<<"        ";
        }
        cout<<endl;
    }
    vector<vector<bool>>visited(n,vector<bool>(m,false));
    //int r=minimizecell(grid,n,m,0,0,countcow,visited);
    int r = solverope(grid,n,m,countcow);
    cout<<r<<endl<<endl;
    int finalcount=0;
    for(auto i:grid)
    {

        for(auto j:i)
        {
            cout<<j.first<<"        ";
            if(j.first=='C')
                finalcount+=j.second;
        }
        cout<<endl;
    }
    return finalcount;
}
struct info{
public:
    int weight;
    double capacity;

};
int fo(vector<info>&cows,int ind,int w,vector<vector<int>>&dp)
{
    if(ind==0)
    {
        if(cows[ind].weight<=w)
        {
            return cows[ind].capacity;
        }
        else
            return 0;
    }
    if(dp[ind][w]!=-1)
        return dp[ind][w];
    int ntake=fo(cows,ind-1,w,dp);
    int take=INT_MIN;
    if(cows[ind].weight<=w)
    {
        take=fo(cows,ind-1,w-cows[ind].weight,dp)+cows[ind].capacity;
    }
    return dp[ind][w]=max(take,ntake);
}
void puzzle3(int c)
{
    cout<<" here's another puzzle waiting for u ....Mr. Harry !!";
    cout<<endl<<" so now , since  "<<c<<" cows are maximum number that Harry can accommodate in his stable by minimizing his stable 's size of coverage .\n";
    /* so i thought like that user have to maximize the profit according to how much he could fetch milk from the no. of cows he finally decided to buy
    so basically problem is , in those jot of cows all have different capacities of milk that they can fetch , also all have different weights , harry have to lend
    a truck to brought that many cows so he make an average prediction of weight according to the count of cows he had , but at market place , he have to maximize that no. of cows
    who can provide him max amount of milk so help him to maximize that count such that truck weight should not exceed ...
    to make it more interactive , i am thinking to make a time game , i'll dynamically generate this data , i'll give some time to user to fast-fast generate an optimal prediction by just looking at the data
    and after that my internal algorithm of 0/1 knapsack will give optimal answer , then i'll compare the answer and will give him points according to that ....
    */
    cout<<"so , now Harry want to purchase the cows for which he rented a ship that has particular capacity , so since no. of cows are "<<c<<" so on an average weight of cow which is 400kgs";
    cout<<"  so , he rented ship of "<<c*400<<" kgs according to the count he has \n Now , his major task is to ship the cows in his ship that will fetch him maximum amount of milk as every cow has different capacity of producing milk ";
    cout<<" and along with its maximization , harry also have to think of his ship's capacity \n";
    cout<<"\n Cause you are harry now , enter your weight , which is to be added in the final capacity\n";
    int f;
    cin>>f;
    int finalcapacity=c*400+f;
    vector<info>cows(c);
    for(auto &i:cows)
    {
        i.weight=350+rand()%200;
        i.capacity=rand()%8+2;

    }
    cout<<"So , here is all the details of the cows on the shop :- \n";
    cout<<"............................................................................................................................\n";
    cout<<" COW       ";
    int counter=1;
    for(auto i:cows)
    {
        cout<<counter++<<"        ";
    }
    cout<<"\n............................................................................................................................\n";
    cout<<" WEIGHTS       ";
    for(auto i:cows)
    {
        cout<<i.weight<<"        ";
    }
     cout<<"\n............................................................................................................................\n";
    cout<<" CAPACITY     ";
    for(auto i:cows)
    {
        cout<<i.capacity<<"        ";
    }
    cout<<endl;
    vector<info>ans(c);
    vector<vector<int>>dp(cows.size()+1,vector<int>(finalcapacity+1,-1));
    int anss=fo(cows,cows.size()-1,finalcapacity,dp);
   /* for(int w=cows[0].weight;w<=finalcapacity;w++)
    {
        dp[0][w]=cows[0].capacity;
    }
   for(int i = 1; i < cows.size(); i++) {
    for(int w = 0; w <= finalcapacity; w++) {
        int ntake = dp[i - 1][w];
        int take = 0; // Initialize to 0
        if(cows[i].weight <= w) { // Corrected condition
            take = cows[i].capacity + dp[i - 1][w - cows[i].weight];
        }
        dp[i][w] = max(take, ntake);
    }
}
*/
    cout<<endl;

    int an=dp[cows.size()-1][finalcapacity];
    cout<<an;
}
int main()
{
    introduction();
    int c=puzzle1();
    puzzle3(c);

}
