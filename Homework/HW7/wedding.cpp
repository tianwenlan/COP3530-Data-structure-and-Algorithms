/*
AUTHOR: Wenlan Tian
Problem:UVa 11450 Wedding shopping
Algorithm: DP
Date: Nov, 2014
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int memo[200][20];
int gList[20][20];
int ng[20];
int tc, m, g;

int shop(int money, int curG) {
	if (money < 0)
		return -1e6;
	if (curG == g)
		return m - money;

	if (memo[money][curG] != -1)
		return memo[money][curG];

	int ans = -1e6;
	for (int i = 0; i < ng[curG]; i++) {
		ans = max(ans, shop(money - gList[curG][i], curG + 1));
	}

	return memo[money][curG] = ans;
}

int main() {
	scanf("%d", &tc);
	while (tc--) {
		scanf("%d %d", &m, &g);

		for (int i = 0; i < g; i++) {
			scanf("%d", &ng[i]);
			for (int j = 0; j < ng[i]; j++) {
				scanf("%d", &gList[i][j]);
			}
		}

		memset(memo, -1, 200 * 20 * 4);
		int ans = shop(m, 0);

		if (ans > 0)
			printf("%d\n", ans);
		else
			printf("no solution\n");
	}

	return 0;
}

/*
AUTHOR: Wenlan Tian
Solution for "Blueberries" (www.spoj.com/problems/RPLB)
Algorithm: DP
Date: Nov, 2014
*/

#include<cstdio>

int max,k,n;
bool done[1001][1001];
int val[1000];

void solve(int i, int acc){
	if(acc > k) return;

	if(acc > max) max = acc;

	done[i][acc] = true;

	if(i < n-1 && !done[i+1][acc]) solve(i+1,acc);
	acc+=val[i];
	if(acc > k) return;
	if(acc > max) max = acc;
	if(i < n-2 && !done[i+2][acc]) solve(i+2,acc);
}

int main(){
	int t,i,j,c;
	for(scanf("%d",&t),c=1;c<=t;c++){
		max = 0;
		scanf("%d%d",&n,&k);
		for(i=0;i<n;i++){
			for(j=0;j<=k;j++) done[i][j] = false;
			scanf("%d",val+i);
		}
		solve(0,0);
		printf("Scenario #%d: %d\n",c,max);
	}
	return 0;
}



/*Auther: Wenlan Tian
 *Problem:207. Three-coloring of binary trees
 *Problem code: THREECOL (http://www.spoj.com/problems/THREECOL/)
 *Date: Nov, 2014
 */

#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<algorithm>

using namespace std;

int dpMax [10010][2];
int dpMin [10010][2];
int N;
string inp;
int children[10010][2];

void calculate(int n, int isGreen){
    if (n==N)  return;
    if (dpMax[n][isGreen]!=-1) return;
    if (isGreen){
        if (inp[n]=='0'){
            dpMax[n][isGreen] = 1;
            dpMin[n][isGreen] = 1;
        }else if (inp[n]=='1'){
            calculate(children[n][0],!isGreen);
            dpMax[n][isGreen] = 1+dpMax[children[n][0]][!isGreen];
            dpMin[n][isGreen] = 1+dpMin[children[n][0]][!isGreen];
        }else{
            calculate(children[n][0],!isGreen);
            calculate(children[n][1],!isGreen);
            dpMax[n][isGreen] = 1+dpMax[children[n][0]][!isGreen]+dpMax[children[n][1]][!isGreen];
            dpMin[n][isGreen] = 1+dpMin[children[n][0]][!isGreen]+dpMin[children[n][1]][!isGreen];
        }
    }else{
        if (inp[n]=='0'){
            dpMax[n][isGreen] = 0;
            dpMin[n][isGreen] = 0;
        }else if (inp[n]=='1'){
            calculate(children[n][0],!isGreen);
            calculate(children[n][0],isGreen);
            dpMax[n][isGreen] = max(dpMax[children[n][0]][isGreen], dpMax[children[n][0]][!isGreen]);
            dpMin[n][isGreen] = min(dpMin[children[n][0]][isGreen], dpMin[children[n][0]][!isGreen]);
        }else{
            calculate(children[n][0],!isGreen);
            calculate(children[n][0],isGreen);
            calculate(children[n][1],!isGreen);
            calculate(children[n][1],isGreen);
            dpMax[n][isGreen] = max(dpMax[children[n][0]][isGreen]+dpMax[children[n][1]][!isGreen], dpMax[children[n][0]][!isGreen]+dpMax[children[n][1]][isGreen]);
            dpMin[n][isGreen] = min(dpMin[children[n][0]][isGreen]+dpMin[children[n][1]][!isGreen], dpMin[children[n][0]][!isGreen]+dpMin[children[n][1]][isGreen]);
        }
    }
}

int node;
void form_tree(){
    if (node==N) return;
    int c_node = node;
    node++;
    if (inp[c_node]=='1'){
        children[c_node][0] = node;
        form_tree();
    }else if (inp[c_node]=='2'){
        children[c_node][0] = node;
        form_tree();
        children[c_node][1] = node;
        form_tree();
    }
}

int main(){
    int t;
    cin>>t;
    while(t--){
        cin>>inp;
        N = inp.size();
        memset(dpMax, -1, sizeof dpMax);
        node = 0;
        form_tree();
        calculate(0,0);
        calculate(0,1);
        printf("%d %d\n", max(dpMax[0][0],dpMax[0][1]), min(dpMin[0][0], dpMin[0][1]));
    }
}
