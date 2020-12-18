#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

#define NTer 2000 // save teacher's max number
#define Nsal 5000 // save salary records' max number
#define Ncol 5 // save the nubmer of college
#define Njob 4 // save the nubmer of jobs

/*************************Operation Functions*********************************/
void menu();
// welcome page
void Welcome();
// to thanks for using
void QuitTks();
// operation 1 to 6
void ope1();
void ope2();
void ope3();
void ope4();
void ope5();
int  ope6();
/*****************************************************************************/

/*****************************Check Functions*********************************/
int checkten(int L,int R); 
// keep user inputing until it's valid, then return the number
double checkdb();
/*
int checkten(int L,int R);
int checkten_z(char * inp,int L,int R); 
// to judge whether it's just a num
// if so return 1, otherwise return 0*/
void checkid(char * inpid, int judgeexist);
// check the id's format invalid or not
// if judgeexist == 1 , until input exist then return;
// if judgeexist == 2 , until input not exist return;
// until valid then stop with inpid valid
int checkname(char * inpname);
int checkmon(int * mon,char * id);
/*****************************************************************************/

/*************************Storage Functions*********************************/
void inpter(int tid,int notfirst); // insert or change teacher by cntid 
void inpsal(int sid,int notfirst); // insert or change salary  by cntid
void deleteter(char * id); // delete teacher by id
void deletesal(char * id); // delete salary by id
void savetolocter(); // save function
void savetolocsal();
void loadlocter(char * loc); // load function
void loadlocsal(char * loc);
// ExampleSaldata.dat ExampleTerdata.dat
// saldata.dat terdata.dat
/*****************************************************************************/

/*************************Algorithm Functions*********************************/
int showter(int mode,char * cc); // show information of teacher
void showsal(int mode,char * cc,int mon); // show information of salary
int searchsalid(char * id,int month); // search cntind by id
int searchterid(char * id); // search cntind by id
void sortter_id(); // sort by id
void sortsal_id(); // 1st id, 2nd month
void calcolavg_sort(int mon); // calculate different college's average
void caljobavg_sort(int mon); // calculate different job's average
void swapter(struct Teacher *a,struct Teacher *b); // swap function
void swapsal(struct Salary *a,struct Salary *b);
void swapcol(struct College *a,struct College *b);
void swapjob(struct Job *a,struct Job *b);
void FreshSalName(int salind); // sync tername to salary
char * d2s(double a, char * r); // convert double to string
/*****************************************************************************/



/****************************Structs******************************************/
struct Teacher{
	char id[11];
	char name[31];
	int collegeid;
	int jobid;
}ter[NTer],tmpt; // use tmp to change
int tercnt=0; // count the number of all teacher
char col_sec[Ncol+1][31]={"","Information","Engineer","Theory","Arts","Biology"}; // college nubmer to name
char job_sec[Njob+1][31]={"","Professor","Ass-Professor","Teacher","Tutor"}; // job nubmer to name

struct Salary{
	char id[11];
	char name[31];
	int collegeid;
	int jobid;
	int month;
	double basicsal, addsal, subsal, theosal, truesal;
}sal[Nsal],tmps;
int salcnt=0; // count the number of all records

struct College
{
	int collegeid;
	double thavg,travg;
}col[6],tmpc;

struct Job
{
	int jobid;
	double thavg,travg;
}job[6],tmpj;
/*****************************************************************************/



int main()
{
	Welcome();
	menu();

	return 0;
}



void menu()
{
	while(1)
	{
		system("cls");
		printf("please input the number before the operation:\n");
		printf("[1]---insert data and save\n");
		printf("[2]---update data and delete\n");
		printf("[3]---search data and show\n");
		printf("[4]---statist data and analyse\n");
		printf("[5]---load data from local\n");
		printf("[6]---save to local and quit\n");
		printf("INPUT the number HERE and press ENTER:____\b\b\b");
		
		// LB: invalid input: 
		int nope = checkten(1, 6);

		if(nope == 1) ope1();
		if(nope == 2) ope2();
		if(nope == 3) ope3();
		if(nope == 4) ope4();
		if(nope == 5) ope5();
		if(nope == 6 && ope6()) break;
	}

	QuitTks();
}

void ope1()
{
	while(1)
	{
		system("cls");
		printf("[[Welcome to insert data and save Funtion]]\n");
		printf("please choose the following options you wanna do by Index\n");
		printf("[1]---insert the teacher's basic information\n");
		printf("[2]---insert one salary information\n");
		printf("[3]---save to local and back to last menu\n");
		printf("Please input the index:___\b\b");


		int nope = checkten(1,3);
		

		if(nope == 1) // insert new ter's inf
		{
			printf("Input the Teacher's ID:__________\b\b\b\b\b\b\b\b\b\b");
			char tmpid[20];
			checkid(tmpid,2);
			
			strcpy(ter[tercnt].id,tmpid);

			inpter(tercnt,0);
			
			
			tercnt++;
			sortter_id(); // after insert, sort it.
		}

		if(nope == 2)// insert new sal's inf
		{
			showter(1,NULL);
			printf("Please input the id of the teacher: ID:__________\b\b\b\b\b\b\b\b\b\b");
			char tmpid[20];
			checkid(tmpid,1);
			strcpy(sal[salcnt].id,tmpid);

			inpsal(salcnt,0);

			

			salcnt++;
			sortsal_id();
		}

		if(nope == 3)
		{
			savetolocter();
			savetolocsal();
			break;
		}

	}
}

void ope2()
{
	while(1)
	{
		system("cls");
		printf("[[Welcome to update data and delete Funtion]]\n");
		printf("please choose the following options you wanna do by Index\n");
		printf("[1]---update one's information by ID\n");
		printf("[2]---update one's information by NAME\n");
		printf("[3]---delete one's information by ID\n");
		printf("[4]---save to local and back to last menu\n");
		printf("Please input the index:___\b\b");

		int nope = checkten(1,4);

		if(nope == 1)
		{
			//showter(1,NULL);showsal(1,NULL,0);
			printf("please input the ID of the teacher,ID:__________\b\b\b\b\b\b\b\b\b\b");
			char inpid[21];
			checkid(inpid,1);
			int terid=showter(3,inpid);
			showsal(3,inpid,0);
			printf("if you wanna change basic information,input 13\n");
			printf("if you wanna change salary information,input the month nubmer you wanna change\n");
			printf("INPUT:_____\b\b\b");
			
			int changemon=checkten(1,13);
			if(changemon == 13)
			{
				printf("\n------Rewrite the information now-----\n");
				inpter(terid,1);
				sortter_id();
			}
			else
			{
				// todo: month existence
				if(checkmon(&changemon,inpid)==0){printf("you've tried too many times,press enter to return;\n");getchar();getchar();continue;}
				int salid=searchsalid(inpid,changemon);
				printf("\n------Rewrite the information now-----\n");
				inpsal(salid,1);
				sortsal_id();
			}
			//printf("successful changed \n");
		}

		if(nope == 2)
		{
			//showter(1,NULL);showsal(1,NULL,0);
			printf("please input the name of the teacher,NAME:__________\b\b\b\b\b\b\b\b\b\b");

			char inpna[31];
			if(checkname(inpna)==0)
			{
				printf("you've tried too many times,press enter to return;\n");getchar();getchar();
				continue;
			}
			showter(2,inpna);
			showsal(2,inpna,0);

			// to get the id 	
			printf("please input the id of the teacher you wanna change:ID:__________\b\b\b\b\b\b\b\b\b\b");
			char inpid[21];
			checkid(inpid,1);
			int terid=searchterid(inpid);

			printf("if you wanna change basic information,input 13\n");
			printf("if you wanna change salary information,input the month nubmer you wanna change\n");
			printf("INPUT:_____\b\b\b");
			
			int changemon=checkten(1,13);
			if(changemon == 13)
			{
				printf("\n------Rewrite the information now-----\n");
				inpter(terid,1);
				sortter_id();
			}
			else
			{
				// todo: month existence
				if(checkmon(&changemon,inpid)==0){printf("you've tried too many times,press enter to return;\n");getchar();getchar();continue;}
				int salid=searchsalid(inpid,changemon);
				printf("\n------Rewrite the information now-----\n");
				inpsal(salid,1);
				sortsal_id();
			}
			//printf("successful changed \n");
		}

		if(nope == 3)
		{
			showter(1,NULL);showsal(1,NULL,0);
			printf("please input the ID of the teacher you wanna delete,ID:__________\b\b\b\b\b\b\b\b\b\b");
			char inpid[21];
			checkid(inpid,1);
			
			printf("****************************TO BE DELETED INFORMATION***************************\n");
			showter(3,inpid);
			showsal(3,inpid,0);
			printf("ARE YOU SURE TO DELETE ALL THESE ABOVE?? (press y to confirm, n or anykey to cancle)_____\b\b");
			char deope;
			
			scanf("%c",&deope);
			if(deope != 'Y' && deope != 'y')
			{	
				printf("delete operation cancled\n");
				continue;
			}
			printf("IT CAN NOT BE BACKUP REALLY SURE???? (press y to confirm, n or anykey to cancle) _____\b\b");
			getchar();
			scanf("%c",&deope);
			if(deope != 'Y' && deope != 'y')
			{	
				printf("delete operation cancled\n");
				printf("PRESS ENTER TO CONTINUE.\n");getchar();getchar();
				continue;
			}
			if(deope == 'Y' or deope == 'y')
			{
				deletesal(inpid); // todo
				deleteter(inpid); // todo
				
				sortter_id();
				sortsal_id();
				printf("successful deleted\n");
				printf("****************************AFTER DELETED***************************\n");
				showter(1,NULL);
				showsal(1,NULL,0);
				printf("PRESS ENTER TO CONTINUE.\n");getchar();getchar();
			}

		}

		if(nope == 4)
		{
			savetolocter();
			savetolocsal();
			break;
		}

	}

}

void ope3()
{
	while(1)
	{
		system("cls");
		printf("[[Welcome to search data and show Funtion]]\n");
		printf("please choose the following options you wanna do by Index\n");
		printf("[1]---show all the teacher's basic information\n");
		printf("[2]---show the chosen month's all teachers' salary information\n");
		printf("[3]---show the given ID and month's teacher's all information\n");
		printf("[4]---show the given NAME and month's teacher's all information\n");
		printf("[5]---quit\n");
		printf("Please input the index:___\b\b");

		int nope = checkten(1,5);				
		
		if(nope == 1)
		{
			showter(1,NULL);
			printf("PRESS ENTER TO CONTINUE.\n");getchar();getchar();
		}

		if(nope == 2)
		{
			printf("please input the month you wanna show:___\b\b");
			int chomon=checkten(1,12);
			showsal(1,NULL,chomon);
			printf("PRESS ENTER TO CONTINUE.\n");getchar();getchar();
		}

		if(nope == 3)
		{
			printf("please input the id of the teacher you wanna show:ID:__________\b\b\b\b\b\b\b\b\b\b");
			char inpid[21];
			checkid(inpid,1);
			printf("please input the month you wanna show:___\b\b");
			int chomon=checkten(1,12);
			showter(3,inpid);
			showsal(3,inpid,chomon);
			printf("PRESS ENTER TO CONTINUE.\n");getchar();getchar();
		}

		if(nope == 4)
		{
			printf("please input the name of the teacher,NAME:__________\b\b\b\b\b\b\b\b\b\b");
			char inpna[31];
			if(checkname(inpna)==0)
			{
				printf("you've tried too many times,press enter to return;\n");getchar();getchar();
				continue;
			}
			printf("please input the month you wanna show:___\b\b");
			int chomon=checkten(1,12);
			showter(2,inpna);
			showsal(2,inpna,chomon);
			printf("PRESS ENTER TO CONTINUE.\n");getchar();getchar();
		}

		if(nope == 5)
		{
			break;
		}
	}

}

void ope4()
{
	while(1)
	{
		system("cls");
		printf("[[Welcome to statist data and analyse Funtion]]\n");
		printf("please choose the following options you wanna do by Index\n");
		printf("[1]---statist the different college's average salary\n");
		printf("[2]---statist the different job's average salary\n");
		printf("[3]---quit\n");
		printf("Please input the index:___\b\b");

		int nope = checkten(1,3);
		if(nope == 1)
		{
			printf("please input the month you want to statist:____\b\b");
			int chomon=checkten(1,12);
			calcolavg_sort(chomon); // cal and sort

			int i;
			printf("\n---------Statist Data(sorted by True Salary)-------------\n");
			printf("|No\t|College\t|True Salary\t|Theory Salary\t|\n");
			printf("---------------------------------------------------------\n");
			for(i=1;i<=Ncol;i++)
			{
				printf("|%d\t|%-15s|%-15.2f|%-15.2f|\n",i,col_sec[col[i].collegeid],col[i].travg,col[i].thavg);
			}
			printf("---------------------------------------------------------\n");
			printf("PRESS ENTER TO CONTINUE.\n");getchar();getchar();
		}	
		
		if(nope == 2)
		{
			printf("please input the month you want to statist:____\b\b");
			int chomon=checkten(1,12);
			caljobavg_sort(chomon); // cal and sort

			int i;
			printf("\n---------Statist Data(sorted by Theory Salary)-----------\n");
			printf("|No\t|Job\t\t|True Salary\t|Theory Salary\t|\n");
			printf("---------------------------------------------------------\n");
			for(i=1;i<=Njob;i++)
			{
				printf("|%d\t|%-15s|%-15.2f|%-15.2f|\n",i,job_sec[job[i].jobid],job[i].travg,job[i].thavg);
			}
			printf("---------------------------------------------------------\n");
			printf("PRESS ENTER TO CONTINUE.\n");getchar();getchar();
		}

		if(nope == 3)
		{
			break;
		}

	}

}

void ope5()
{
	printf("which data do you want to load? (1.example data 2.last saved data)____\b\b");
	int nope=checkten(1,2);
	printf("are you sure? IT will overwrite current data.(press y to confirm, n or anykey to cancle)___\b\b");
	char no;
	getchar();
	scanf("%c",&no);
	if(no == 'y' or no == 'Y')
	{
		if(nope == 1)
		{
			char tr[]="ExampleTerdata.dat";
			loadlocter(tr);
			char ts[]="ExampleSaldata.dat";
			loadlocsal(ts);
		}
		if(nope == 2)
		{
			char tr[]="terdata.dat";
			loadlocter(tr);
			char ts[]="saldata.dat";
			loadlocsal(ts);
			
		}
		showter(1,NULL);
		showsal(1,NULL,0);
		printf("successful loaded [%d]Teacher Information,[%d]Salary Infromation\n\n",tercnt,salcnt);
		printf("PRESS ENTER TO CONTINUE.\n");getchar();getchar();

	}
	else
	{
		printf("operation cancled\n");
		printf("PRESS ENTER TO CONTINUE.\n");getchar();getchar();
	}

}

int ope6()
{
	printf("ARE YOU SURE TO QUIT? (press y to confirm, n or anykey to cancle)____\b\b");
	char deope;
	getchar();
	scanf("%c",&deope);
	if(deope != 'Y' && deope != 'y')
	{	

		printf("quit operation cancled\n");
		return 0;
	}
	printf("you really sure to quit???? (press y to confirm, n or anykey to cancle) ____\b\b");
	getchar();
	scanf("%c",&deope);
	if(deope != 'Y' && deope != 'y')
	{	
		printf("quit operation cancled\n");
		return 0;
	}
	if(deope == 'Y' or deope == 'y')
	{

		printf("Saving and Quiting....\n");
		return 1;

	}
	return 0;
}

void Welcome()
{
	//system("mode con:cols=180 lines=40");
	system("color 0b");
	
	


	printf("-------------------------------------------------------------\n");
	printf("|       Welcome to use the Salary Manage System             |\n");
	printf("|                   Date : 2020.12.17                       |\n");
	printf("|                 Author : ShuoCHN                          |\n");
	printf("|                Version : 1.0.0                            |\n");
	printf("-------------------------------------------------------------\n");

	Sleep(1000);
	system("cls");
	printf("                      ********\n");
	printf("                             *\n");
	printf("                             *\n");
	printf("                      ********\n");
	printf("                             *\n");
	printf("                             *\n");
	printf("                      ********\n");

	Sleep(1000);
	system("cls");
	printf("                      ********\n");
	printf("                             *\n");
	printf("                             *\n");
	printf("                      ********\n");
	printf("                      *       \n");
	printf("                      *       \n");
	printf("                      ********\n");

	Sleep(1000);
	system("cls");
	printf("                             *\n");
	printf("                             *\n");
	printf("                             *\n");
	printf("                             *\n");
	printf("                             *\n");
	printf("                             *\n");
	printf("                             *\n");
	Sleep(1000);

}

void QuitTks()
{
	system("cls");
	printf("-------------------------------------------------------------\n");
	printf("|       Thank you very much for using the system            |\n");
	printf("|       If you have any suggestion,please email me          |\n");
	printf("|               Author : ShuoCHN                            |\n");
	printf("|                Email : zhaoshuo100@foxmail.com            |\n");
	printf("-------------------------------------------------------------\n");

}

// --------------------------CHECK SECTION-----------------------------------

int checkten(int L,int R)
{
	char opeinp[20];
	
	scanf("%s",opeinp);
	while ((atoi(opeinp)) == 0 or (atoi(opeinp)) > R or (atoi(opeinp)) < L )
	{
		printf("your input is invalid,please input again(just number from %d to %d):____\b\b\b",L,R);
		scanf("%s",opeinp);
	}
	return atoi(opeinp);
}

double checkdb()
{
	char opeinp[20];
	
	scanf("%s",opeinp);
	while ((atof(opeinp)) == 0)
	{
		printf("your input is invalid,please input again(just a real number):________\b\b\b\b\b\b\b\b");
		scanf("%s",opeinp);
	}
	return atof(opeinp);
}


void checkid(char * inpid, int judgeexist) 
{// if judgeexist == 1 , until input exist then return;
 // if judgeexist == 2 , until input not exist return;
	rewind(stdin);
	while(scanf("%s",inpid))
	{
		rewind(stdin);
		if(inpid[10] != '\0')
		{ // check 10 digit to stop
			printf("your ID format is invalid,please make sure it is consist of 10 nubmers,ID:__________\b\b\b\b\b\b\b\b\b\b");
			continue;
		}

		int i;
		for(i = 0; i < 10; i++)
		{
			if(inpid[i] > '9' or inpid[0] < '0')
			{
				printf("your ID format is invalid,please make sure it is consist of 10 nubmers,ID:__________\b\b\b\b\b\b\b\b\b\b");
				break;
			}
		}

		if(i==10)
		{ 	// format valid
			// to check existence
			int f=0; // 0 not exist; 1 exist 
			
			for(i = 0;i < tercnt; i++)
			{
				if(strcmp(ter[i].id, inpid) == 0)
				{
					f=1;
					//printf("your ID input is existed, please make sure it's new one's id,ID:__________\b\b\b\b\b\b\b\b\b\b");
					break;
				} 
			}
			if(judgeexist==1)
			{
				if(f==0)
				{
					printf("your ID input is not existed, please make sure it's above one's id,ID:__________\b\b\b\b\b\b\b\b\b\b");
					continue;
				}
				if(f==1)
				{
					return ;
				}
			}
			if(judgeexist==2)
			{
				if(f==1)
				{
					printf("your ID input is existed, please make sure it's new one's id,ID:__________\b\b\b\b\b\b\b\b\b\b");
					continue;
				}
				if(f==0)
				{
					return ;
				}
			}
		}
	}
	return ; // no use,just done for warning
}

int checkname(char * inpname)
{
	int t=0;
	rewind(stdin);
	while(1)
	{
		gets(inpname);

		rewind(stdin);
		int i;
		for(i=0;i<tercnt;i++)
		{
			if(strcmp(ter[i].name,inpname) == 0)
			{
				return 1;
			}
		}
		printf("your name input is not existed, please make sure it's above one's name,NAME:__________\b\b\b\b\b\b\b\b\b\b");
		t++;
		if(t==5) break;
	}
	return 0;
}

int checkmon(int * mon,char * id)
{
	int t=1; // tried too many times
	while(1)
	{
		t++;
		if(searchsalid(id,*mon)!=-1) return 1;

		printf("%d month do not have salary information\n",*mon);
		printf("please resure and then INPUT:_____\b\b\b");

		*mon=checkten(1,12);
		if(t==5) break;
	}
	return 0;	
}


/**********************************Storage Functions*************************************************/
void inpter(int tid,int notfirst)
{
	printf("Input the Teacher's NAME:______________\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	rewind(stdin);
	gets(ter[tid].name); // to ignored the sperate by space
	printf("Input the college index of the teacher:\n1.Information,2.Engineer,3.Theory,4.Art,5.Biology. INPUT:___\b\b");
	ter[tid].collegeid=checkten(1,5);
	printf("Input the job index of the teacher:\n1.Professor,2.Ass-Professor,3.Teacher,4.Tutor. INPUT:___\b\b");
	ter[tid].jobid=checkten(1,4);


	struct Salary * sa;
	for(sa=sal;sa<sal+salcnt;sa++)
	{
		if(strcmp(sa->id,ter[tid].id)==0)
		{
			strcpy(sa->name,ter[tid].name);
			sa->jobid = ter[tid].jobid;
			sa->collegeid = ter[tid].collegeid;
		}
	}

	if(notfirst == 0) tercnt++;
	showter(3,ter[tid].id);
	if(notfirst == 0) tercnt--;
	printf("BELOW INFORMATION SAVED SUCCESSFULly \n");
	printf("PRESS ENTER TO CONTINUE.\n");getchar();getchar();

}

void inpsal(int sid,int notfirst)
{
	printf("please input the month(nubmer from 1 to 12):______\b\b\b");
	sal[sid].month=checkten(1,12);
	printf("please input the basic salary:________\b\b\b\b\b\b\b\b");
	sal[sid].basicsal=checkdb();
	printf("please input the additional salary:________\b\b\b\b\b\b\b\b");
	sal[sid].addsal=checkdb();
	printf("please input the subtract salary:________\b\b\b\b\b\b\b\b");
	sal[sid].subsal=checkdb();

	sal[sid].theosal=sal[sid].basicsal+sal[sid].addsal;
	sal[sid].truesal=sal[sid].theosal-sal[sid].subsal;

	FreshSalName(sid);
	if(notfirst == 0) salcnt++;
	showsal(3,sal[sid].id,sal[sid].month);
	if(notfirst == 0) salcnt--;
	printf("BELOW INFORMATION SAVED SUCCESSFULlY \n");
	printf("PRESS ENTER TO CONTINUE.\n");getchar();getchar();


}

void deleteter(char * id)
{
	// through swap and cnt-- to complete the delete operation
	swapter(&ter[tercnt-1],&ter[searchterid(id)]);
	tercnt--;
}
void deletesal(char * id)
{
	int i;
	for(i=0;i<salcnt;i++)
	{
		if(strcmp(sal[i].id,id) == 0)
		{
			swapsal(&sal[i],&sal[salcnt-1]);
			salcnt--;
		}
		FreshSalName(i); // to check bug
	}
}

void savetolocter()
{
	// (id,name,colid,jobid)
	FILE * f1;
	f1=fopen("terdata.dat","w+");
	if(f1==NULL){printf("save to local unaviliable\n");return;}
	int i;
	for(i=0;i<tercnt;i++)
	{
		char tline[101]="(", tnum[5];
		strcat(tline,ter[i].id);
		strcat(tline,",");
		strcat(tline,ter[i].name);
		strcat(tline,",");
		strcat(tline,itoa(ter[i].collegeid,tnum,10));
		strcat(tline,",");
		strcat(tline,itoa(ter[i].jobid,tnum,10));
		strcat(tline,")");
		fprintf(f1, "%s\n", tline);
	}
	fclose(f1);
}

void savetolocsal()
{
	FILE * f1;
	f1=fopen("saldata.dat","w+");
	if(f1==NULL){printf("save to local unaviliable\n");return;}
	int i;

	for(i=0;i<salcnt;i++)
	{
		char tline[201]="(", tnum[12];
		strcat(tline,sal[i].id);
		strcat(tline,",");
		strcat(tline,sal[i].name);
		strcat(tline,",");
		strcat(tline,itoa(sal[i].collegeid,tnum,10));
		strcat(tline,",");
		strcat(tline,itoa(sal[i].jobid,tnum,10));
		strcat(tline,",");
		strcat(tline,itoa(sal[i].month,tnum,10));
		strcat(tline,",");
		strcat(tline,d2s(sal[i].basicsal,tnum));
		strcat(tline,",");
		strcat(tline,d2s(sal[i].addsal,tnum));
		strcat(tline,",");
		strcat(tline,d2s(sal[i].subsal,tnum));
		strcat(tline,",");
		strcat(tline,d2s(sal[i].theosal,tnum));
		strcat(tline,",");
		strcat(tline,d2s(sal[i].truesal,tnum));
		strcat(tline,")");
		fprintf(f1, "%s\n", tline);
	}
	fclose(f1);

}

void loadlocter(char * loc)
{
	FILE * f1;
	f1=fopen(loc,"r");
	if(f1==NULL){printf("load to here unaviliable\n");return;}
	
	tercnt=0;
	char tinp[100];
	while(fgets(tinp,300,f1)!=NULL && tinp[0]!=10)
	{
		char tid[11],tna[31];
		int tcd,tjd;
		int i;
		for(i=1;i<=10;i++) tid[i-1]=tinp[i]; // get id
		int tcnt=0;
		for(i=12;tinp[i]!=',';i++) tna[tcnt++]=tinp[i]; // get name
		tna[tcnt]='\0';
		tcd=atoi(&tinp[i+1]);// get college
		tjd=atoi(&tinp[i+3]);// get job

		strcpy(ter[tercnt].id,tid);
		strcpy(ter[tercnt].name,tna);
		ter[tercnt].collegeid=tcd;
		ter[tercnt].jobid=tjd;
		tercnt++;

		//(1234567890,de d,1,1)
	}
	fclose(f1);
	sortter_id();
}


void loadlocsal(char * loc)
{
	FILE * f1;
	f1=fopen(loc,"r");
	if(f1==NULL){printf("load to here unaviliable\n");return;}
	
	salcnt=0;
	char tinp[200];
	while(fgets(tinp,300,f1)!=NULL && tinp[0]!=10)
	{
		char tid[11],tna[31];
		int tcd,tjd;
		double t1,t2,t3,t4,t5;

		int i;
		for(i=1;i<=10;i++) tid[i-1]=tinp[i];
		int tcnt=0;
		for(i=12;tinp[i]!=',';i++) tna[tcnt++]=tinp[i];
		tna[tcnt]='\0';
		tcd=atoi(&tinp[++i]);i++;
		tjd=atoi(&tinp[++i]);i+=2;
		char tmon[4];tcnt=0;
		for(;tinp[i]!=',';i++) tmon[tcnt++]=tinp[i]; 
			tmon[tcnt]='\0';
		int mon=atoi(tmon);
		char tc[15];tcnt=0;

		for(i++;tinp[i]!=',';i++) tc[tcnt++]=tinp[i]; 
			tc[tcnt]='\0';t1=atof(tc);tcnt=0;
		for(i++;tinp[i]!=',';i++) tc[tcnt++]=tinp[i]; 
			tc[tcnt]='\0';t2=atof(tc);tcnt=0;
		for(i++;tinp[i]!=',';i++) tc[tcnt++]=tinp[i]; 
			tc[tcnt]='\0';t3=atof(tc);tcnt=0;
		for(i++;tinp[i]!=',';i++) tc[tcnt++]=tinp[i]; 
			tc[tcnt]='\0';t4=atof(tc);tcnt=0;
		for(i++;tinp[i]!=')';i++) tc[tcnt++]=tinp[i]; 
			tc[tcnt]='\0';t5=atof(tc);tcnt=0;

		strcpy(sal[salcnt].id,tid);
		strcpy(sal[salcnt].name,tna);
		sal[salcnt].collegeid=tcd;
		sal[salcnt].jobid=tjd;
		sal[salcnt].month=mon;
		sal[salcnt].basicsal=t1;
		sal[salcnt].addsal=t2;
		sal[salcnt].subsal=t3;
		sal[salcnt].theosal=t4;
		sal[salcnt].truesal=t5;

		salcnt++;

	}
	fclose(f1);

}

// -------------------------ALGORITHM SECTION-------------------------------

int showter(int mode,char * cc)
{	// mode == 1: show all information
	// mode == 2: show NAME(tc)'s infromation
	// mode == 3: show ID(tc)'s information
	int re=-1;
	struct Teacher * tc;
	printf("\n---------------------------Basic Information---------------------\n");
	printf("|ID\t\t|NAME\t\t|COLLEGE\t|JOB\t\t|\n");
	printf("-----------------------------------------------------------------\n");	
	for(tc=ter;tc<ter+tercnt;tc++)
	{
		if(mode == 1) printf("|%s\t|%-15s|%-15s|%-15s|\n",tc->id,tc->name,col_sec[tc->collegeid],job_sec[tc->jobid]);
		if(mode == 2 && (strcmp(tc->name,cc) == 0) ) printf("|%s\t|%-15s|%-15s|%-15s|\n",tc->id,tc->name,col_sec[tc->collegeid],job_sec[tc->jobid]);
		if(mode == 3 && (strcmp(tc->id,cc) == 0) ) 
		{
			re=tc-ter; // return his cntid
			printf("|%s\t|%-15s|%-15s|%-15s|\n",tc->id,tc->name,col_sec[tc->collegeid],job_sec[tc->jobid]);
		}
	}
	printf("-----------------------------------------------------------------\n\n");
	return re;
}


void showsal(int mode,char * cc,int mon)
{	// mode == 1: show all information
	// mode == 2: show NAME(tc)'s infromation
	// mode == 3: show ID(tc)'s information
	// if mon == 0 then cout every information
	// if mon == 1~12 then just cout the month's information
	struct Salary * sa;
	printf("\n-------------------------------------------------Salary Information------------------------------------------------------\n");
	printf("|Month\t|ID\t\t|NAME\t\t|Basic($)\t|Allowance($)\t|Subtract($)\t|Theory($)\t|True($) \t|\n");
	printf("-------------------------------------------------------------------------------------------------------------------------\n");
	for(sa=sal;sa<sal+salcnt;sa++)
	{
		if(mode == 1 && (mon==0?1:sa->month==mon)) printf("|%d\t|%-15s|%-15s|%-15.2f|%-15.2f|%-15.2f|%-15.2f|%-15.2f|\n",sa->month,sa->id,
			sa->name,sa->basicsal,sa->addsal,sa->subsal,sa->theosal,sa->truesal);
		if(mode == 2 && (strcmp(sa->name,cc) == 0) && (mon==0?1:(sa->month==mon))) printf("|%d\t|%-15s|%-15s|%-15.2f|%-15.2f|%-15.2f|%-15.2f|%-15.2f|\n",sa->month,sa->id,
			sa->name,sa->basicsal,sa->addsal,sa->subsal,sa->theosal,sa->truesal);
		if(mode == 3 && (strcmp(sa->id,cc) == 0) && (mon==0?1:(sa->month==mon))) printf("|%d\t|%-15s|%-15s|%-15.2f|%-15.2f|%-15.2f|%-15.2f|%-15.2f|\n",sa->month,sa->id,
			sa->name,sa->basicsal,sa->addsal,sa->subsal,sa->theosal,sa->truesal);
	}
	printf("-------------------------------------------------------------------------------------------------------------------------\n\n");
}

int searchterid(char * id)
{
	int i;
	for(i=0; i < tercnt;i++)
	{
		if(strcmp(ter[i].id,id)== 0) return i;
	}
	return -1;
}

int searchsalid(char * id,int month)
{
	int i;
	for(i=0;i<salcnt;i++)
	{
		if(strcmp(id,sal[i].id)==0 && sal[i].month == month) return i;
	}
	return -1;
}

void swapter(struct Teacher *a,struct Teacher *b)
{ // to swap all the information in struct teacher
	struct Teacher *t = &tmpt;
	
	t->collegeid = a->collegeid;
	a->collegeid = b->collegeid;
	b->collegeid = t->collegeid;
	t->jobid	 = a->jobid;
	a->jobid	 = b->jobid;
	b->jobid	 = t->jobid;

	strcpy((*t).id,   (*a).id);
	strcpy((*a).id,   (*b).id);
	strcpy((*b).id,   (*t).id);
	strcpy((*t).name, (*a).name);
	strcpy((*a).name, (*b).name);
	strcpy((*b).name, (*t).name);
}

void swapsal(struct Salary *a,struct Salary *b)
{
	struct Salary *t = &tmps;

	t->month	 = a->month;
	a->month	 = b->month;
	b->month	 = t->month;

	t->basicsal	 = a->basicsal;
	a->basicsal	 = b->basicsal;
	b->basicsal	 = t->basicsal;

	t->addsal	 = a->addsal;
	a->addsal	 = b->addsal;
	b->addsal	 = t->addsal;

	t->subsal	 = a->subsal;
	a->subsal	 = b->subsal;
	b->subsal	 = t->subsal;

	t->theosal	 = a->theosal;
	a->theosal	 = b->theosal;
	b->theosal	 = t->theosal;

	t->truesal	 = a->truesal;
	a->truesal	 = b->truesal;
	b->truesal	 = t->truesal;


	strcpy((*t).id,   (*a).id);
	strcpy((*a).id,   (*b).id);
	strcpy((*b).id,   (*t).id);
	strcpy((*t).name, (*a).name);
	strcpy((*a).name, (*b).name);
	strcpy((*b).name, (*t).name);
}

void swapcol(struct College *a,struct College *b)
{
	struct College * t = &tmpc;

	t->thavg	 = a->thavg;
	a->thavg	 = b->thavg;
	b->thavg	 = t->thavg;

	t->travg	 = a->travg;
	a->travg	 = b->travg;
	b->travg	 = t->travg;

	t->collegeid	 = a->collegeid;
	a->collegeid	 = b->collegeid;
	b->collegeid	 = t->collegeid;
}

void swapjob(struct Job *a,struct Job *b)
{
	struct Job * t = &tmpj;

	t->thavg	 = a->thavg;
	a->thavg	 = b->thavg;
	b->thavg	 = t->thavg;

	t->travg	 = a->travg;
	a->travg	 = b->travg;
	b->travg	 = t->travg;

	t->jobid	 = a->jobid;
	a->jobid	 = b->jobid;
	b->jobid	 = t->jobid;
}


void sortter_id()
{ // make the ter list sorted by the id
	int i,j;
	for(i=0;i<tercnt;i++)
		for(j=tercnt-1;j>i;j--)
			if(strcmp(ter[j].id,ter[j-1].id)<0)			
				swapter(&ter[j],&ter[j-1]);
}

void sortsal_id()
{ // make the sal list sorted by the 1:id 2:month
	int i,j;
	for(i=0;i<salcnt;i++)
		for(j=salcnt-1;j>i;j--)
		{
			if(strcmp(sal[j].id,sal[j-1].id)<0)			
				swapsal(&sal[j],&sal[j-1]);
			if(strcmp(sal[j].id,sal[j-1].id) == 0)
				if(sal[j].month < sal[j-1].month)
					swapsal(&sal[j],&sal[j-1]);	
		}
}

void calcolavg_sort(int mon)
{
	int i,j;
	for(i=1;i<=Ncol;i++)
	{
		double thsum=0,trsum=0,cnt=0; // th->theory tr->true

		for(j=0;j<salcnt;j++)
		{
			if(sal[j].collegeid == i && sal[j].month == mon)
			{
				thsum += sal[j].theosal;
				trsum += sal[j].truesal;
				cnt++;
			}
		}
		col[i].collegeid = i;
		col[i].thavg= thsum?thsum/cnt:0;
		col[i].travg= trsum?trsum/cnt:0;
	}

	for(i=1;i<=Ncol;i++)
		for(j=Ncol;j>i;j--)
		{
			if(col[j].travg > col[j-1].travg)			
				swapcol(&col[j],&col[j-1]);
			if(col[j].travg == col[j-1].travg)
				if(sal[j].collegeid < sal[j-1].collegeid)
					swapcol(&col[j],&col[j-1]);	
		}
}

void caljobavg_sort(int mon)
{
	int i,j;
	for(i=1;i<=Njob;i++)
	{
		double thsum=0,trsum=0,cnt=0; // th->theory tr->true

		for(j=0;j<salcnt;j++)
		{
			if(sal[j].jobid == i && sal[j].month == mon)
			{
				thsum += sal[j].theosal;
				trsum += sal[j].truesal;
				cnt++;
			}
		}
		job[i].jobid = i;
		job[i].thavg= thsum?thsum/cnt:0;
		job[i].travg= trsum?trsum/cnt:0;
	}

	for(i=1;i<=Njob;i++)
		for(j=Njob;j>i;j--)
		{
			if(job[j].thavg > job[j-1].thavg)			
				swapjob(&job[j],&job[j-1]);
			if(job[j].travg == job[j-1].travg)
				if(sal[j].jobid < sal[j-1].jobid)
					swapjob(&job[j],&job[j-1]);	
		}
}


void FreshSalName(int salind)
{
	int i;
	for(i=0; i<tercnt;i++)
	{
		
		if(strcmp(ter[i].id,sal[salind].id) == 0) 
		{
			strcpy(sal[salind].name,ter[i].name);
			
			sal[salind].collegeid=ter[i].collegeid;
			sal[salind].jobid=ter[i].jobid;
			break;
		}
		
	}
}

char * d2s(double a,char * r)
{
	sprintf(r,"%.2f",a);
	return r;
}

