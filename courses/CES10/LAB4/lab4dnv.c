#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int main(){
	bool first=true;
	int t;
	scanf("%d",&t);
	for(int T=1;T<=t;T++){
		char str[20][81];
		bool fail[20];
		int rank[1000][20];
		int ticket[20];
		int n;
		scanf("%d",&n);
		(void) getchar();
		for(int i=0;i<n;i++)
			scanf("%[^\n]", str[i]);
		
		int people=0;
		char tmp[1000];
		while( gets(tmp) ){
			if( tmp[0]=='\0' )
				break;
			int count=0,k=0;
			for(int i=0;tmp[i]!='\0';i++)
				if( tmp[i]==' ' )
					rank[people][k++]=count-1,count=0;
				else
					count=count*10+tmp[i]-'0';
			rank[people++][k++]=count-1;
		}
		for(int i=0;i<n;i++)
			fail[i]=false;

		if( !first )
			putchar('\n');
		first=false;

		int exist=n;
		while( true ){
			int min=2e9;
			bool found=false;

			for(int i=0;i<n;i++)
				ticket[i]=0;
			for(int i=0;i<people;i++){
				for(int j=0;j<n;j++)
					if( !fail[rank[i][j]] ){
						ticket[rank[i][j]]++;
						break;
					}
			}
			for(int i=0;i<n;i++){
				if( ticket[i]>people/2.0 ){ 
					printf("%s\n",str[i]);
					found=true;
				}
				if( !fail[i]&&min>ticket[i] )
					min=ticket[i];
			}
			if( found )
				break;

			for(int i=0;i<n;i++)
				if( ticket[i]==min )
					fail[i]=true,exist--;
			if( exist<=0 ){
				for(int i=0;i<n;i++)
					if( ticket[i]==min )
						printf("%s\n",str[i]);
				break;
			}
		}
		
	}
	return 0;
}
