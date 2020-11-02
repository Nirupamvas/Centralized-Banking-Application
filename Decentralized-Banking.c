#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<dos.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

//structure 
struct details{
	long double balance,income;
    char gender[7],category[10],ac_id[11],phone[11],password[15],profession[15],fname[25],lname[25];
    int alive,listCount,accountCounter;
    struct age{
		int date,month,year;
	}dob;
	struct adress{
		char pin[7],hno[10],colony[15],area[15],district[15];
	}address;
}acc[20];

struct history{
	long double balance,flag;
	char h_id[11],dt[40];
}list[20][20];

//globalvariables
int size=20;
int accountCounter=0;
int employeeIndex;
int accountIndex;
int totalAccounts=100;
char newAccountId[11];
FILE *fp;
FILE *hp;
char fname[]="a11";
char hname[]="a12";

//included methods
void logout();
void login();
void accounts();
void newAccount();
void profile();
void transaction();
void details();
void delete_account();
void withdraw();
void deposit();
void dcash();
void wcash();
void transfer();
void dd();
void cheque();
void masterdetails();
void intrographics();
void accountNumberGenerator();
void debugDetails(int);
void readHistory(int tai,int fai,int tcd,long double ttr);
int search(char tempID[11]);
void displayHistory();
void changePassword();
int intvalidation(int a);
int longDoublevalidation(long double a);
void editDetails();
void writeD();
void readD();
int alphaValidation(char a[25]);
int digitValidation(char a[25]);

//main program

void main()
{
	  	clrscr();
		//masterdetails();
		readD();
	  	logout();
	  	getch();
}

//login
void logout()
{
	int i;
	char tempId[11],tempPassword[15];
	clrscr();
    printf("enter id:	");
	scanf("%s",&tempId);
	printf("enter password:	");
	i=0;
	do{
		tempPassword[i]=getch();
		if(tempPassword[i]=='\r'){
			tempPassword[i]='\0';
			printf("\n");
			break;
		}
		printf("*");
		i++;
	}while(1);



	employeeIndex=search(tempId);
	if(employeeIndex==totalAccounts)
		logout();
	if(strcmp(tempPassword,acc[employeeIndex].password)==0)
		login();
	else{
	printf("wrong password\n");
	getch();
	logout();
	}
}

//search the structure
int search(char tempID[11]){
	int i;
	for (i = 0; i <= accountCounter+1; i++)
	{
		if(strcmp(tempID,acc[i].ac_id)==0){
			return i;
		}
	}
	if(i==accountCounter+1){
		printf("account not found\n");
		getch();
	}
	return totalAccounts;
}

//login for the user
void login()
{
	int ch;
	clrscr();
	printf("welcome %s\n",acc[employeeIndex].fname);
	printf("1.accounts\n2.new\n3.profile\n4.logout\n");
	printf("\nenter your choice: ");
	scanf("%d",&ch);
	switch(ch)
	{
	 case 1:accounts();
		break;
	 case 2:newAccount();
		break;
	 case 3:profile();
		break;
	 case 4:	writeD();
	 			logout();
		break;
	 default:	writeD();
	 			exit(1);
	}
}

void writeD(){
	int i,j;
	remove(fname);
	remove(hname);
	acc[0].accountCounter=accountCounter;
	fp=fopen(fname,"w");
	hp=fopen(hname,"w");
	if(fp==NULL)
	{
		fprintf(stderr,"\n error opened file\n");
		exit(1);
	}
	for(i=0;i<20;i++)
	fwrite(&acc[i],sizeof(struct details),1,fp);

	for(i=0;i<=acc[0].accountCounter;i++)
	{
		for(j=0;j<acc[i].listCount;j++)
		fwrite(&list[i][j],sizeof(struct history),1,hp);
	}
	fclose(hp);
	fclose(fp);

}

void readD(){
	int i,j;
	fp=fopen(fname,"r");
	hp=fopen(hname,"r");
	if(fp==NULL)
	{
		fprintf(stderr,"\n error opened file\n");
		exit(1);
	}
	fread(&acc[0],sizeof(struct details),1,fp);
	accountCounter=acc[0].accountCounter;
	for(i=1;i<=acc[0].accountCounter;i++)
	fread(&acc[i],sizeof(struct details),1,fp);

	
	for(i=0;i<=acc[0].accountCounter;i++)
	{
		for(j=0;j<acc[i].listCount;j++)
		fread(&list[i][j],sizeof(struct history),1,hp);
	}	
	fclose(hp);
	fclose(fp);
	//remove(fname);
	
}

//exisiting accounts
void accounts()
{
	int ch;
	char tempId[11];
	clrscr();
	printf("welcome %s\n",acc[employeeIndex].fname);
	printf("accounts:\n");
	printf("enter account number: ");
	scanf("%s",&tempId);
	accountIndex=search(tempId);
	if(accountIndex>=totalAccounts){
		printf("account not found\n");
		getch();
		login();
	}
	clrscr();
	printf("welcome %s\n",acc[employeeIndex].fname);
	printf("accounts:\naccount no: %s\n",acc[accountIndex].ac_id);
	printf("1.transaction\n2.details\n3.delete account\n4.history\n5.logout\n");
	printf("\nenter your choice: ");
	scanf("%d",&ch);
	switch(ch)
	{
	 case 1:transaction();
		break;
	 case 2:details();
		break;
	 case 3:delete_account();
		break;
	case 4:displayHistory();
	    break;
	 case 5:logout();
		break;
	 default:login();
	 }
}

//creating new account
void newAccount(){
	char tfname[25],tlname[25],tpassword1[15],tpassword2[15],tprofession[15];
	char tphone[11];
	int tage,talive,s,ch,v,i;
	char thno[10],tcolony[15],tarea[15],tdistrict[15],tpin[7];
	int tdate,tmonth,tyear;
	long double tincome;
	accountCounter++;
	accountNumberGenerator();
	strcpy(acc[accountCounter].ac_id,newAccountId);
	printf("%s\n",acc[accountCounter].ac_id);
	do{
		printf("enter first name:	");
		scanf("%s",&tfname);
		v=alphaValidation(tfname);
		if(((strlen(tfname))<=25) && (v==0)){
			strcpy(acc[accountCounter].fname,tfname);
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	do{
		printf("enter last name:	");
		scanf("%s",&tlname);
		v=alphaValidation(tlname);
		if(((strlen(tfname))<=25) && (v==0)){
			strcpy(acc[accountCounter].lname,tlname);
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	do{
		printf("enter phone number:	");
		scanf("%s",&tphone);
		v=digitValidation(tphone);
		if((strlen(tphone))==10 && (v==0)){
			strcpy(acc[accountCounter].phone,tphone);
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	do{
		printf("enter date:	");
		scanf("%d",&tdate);
		s=intvalidation(tdate);
		if((s<=2 && s>0) && (tdate<=31)){
			acc[accountCounter].dob.date=tdate;
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	do{
		printf("enter month:	");
		scanf("%d",&tmonth);
		s=intvalidation(tmonth);
		if((s<=2) && (tmonth<=12)){
			acc[accountCounter].dob.month=tmonth;
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	do{
		printf("enter year:	");
		scanf("%d",&tyear);
		s=intvalidation(tyear);
		if((s==4) && (tyear<=2019) && (tyear>=1919)){
			acc[accountCounter].dob.year=tyear;
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	do{
		printf("select your gender:\n1.male	2.female\n");
		scanf("%d",&ch);
		switch(ch){
			case 1:	printf("you selected male\n");
					strcpy(acc[accountCounter].gender,"male");
					break;
			case 2:	printf("you selected female\n");
					strcpy(acc[accountCounter].gender,"female");
					break;
			default: printf("wrong choice try again\n");
					break;
		}
	}while((ch!=1) && (ch!=2));
	printf("enter address:\n");
	do{
		printf("enter house no:	");
		scanf("%s",&thno);
		if((strlen(thno))<=10){
			strcpy(acc[accountCounter].address.hno,thno);
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	do{
		printf("enter colony:	");
		scanf("%s",&tcolony);
		v=alphaValidation(tcolony);
		if((strlen(tcolony))<=15 && (v==0)){
			strcpy(acc[accountCounter].address.colony,tcolony);
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	do{
		printf("enter area:	");
		scanf("%s",&tarea);
		v=alphaValidation(tarea);
		if((strlen(tarea))<=15 && (v==0)){
			strcpy(acc[accountCounter].address.area,tarea);
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	do{
		printf("enter district:	");
		scanf("%s",&tdistrict);
		v=alphaValidation(tdistrict);
		if((strlen(tdistrict))<=15 && (v==0)){
			strcpy(acc[accountCounter].address.district,tdistrict);
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	do{
		printf("enter areas pincode:	");
		scanf("%s",&tpin);
		v=digitValidation(tpin);
		if((strlen(tpin))==6 && (v==0)){
			strcpy((acc[accountCounter].address.pin),tpin);
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	do{
		printf("enter profession:	");
		scanf("%s",&tprofession);
		v=alphaValidation(tprofession);
		if((strlen(tprofession))<=15 && (v==0)){
			strcpy(acc[accountCounter].profession,tprofession);
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	do{
		printf("select your gender:\n1.general	2.employee\n");
		scanf("%d",&ch);
		switch(ch){
			case 1:	printf("you selected general\n");
					strcpy(acc[accountCounter].category,"general");
					break;
			case 2:	printf("you selected employee\n");
					strcpy(acc[accountCounter].category,"employee");
					break;
			default: printf("wrong choice try again\n");
					break;
		}
	}while((ch!=1) && (ch!=2));
	do{
		if(strcmp(acc[accountCounter].category,"employee")!=0)
			break;
		printf("enter password:	");
		//scanf("%s",&tpassword1);
		i=0;
		do{
			tpassword1[i]=getch();
			if(tpassword1[i]=='\r'){
				tpassword1[i]='\0';
				printf("\n");
				break;
			}
			printf("*");
			i++;
		}while(1);		

		if((strlen(tpassword1))<=15){
			printf("enter conform password:	");
			//scanf("%s",&tpassword2);

			i=0;
			do{
				tpassword2[i]=getch();
				if(tpassword2[i]=='\r'){
					tpassword2[i]='\0';
					printf("\n");
					break;
				}
				printf("*");
				i++;
			}while(1);	

			if(strcmp(tpassword1,tpassword2)==0)
			strcpy(acc[accountCounter].password,tpassword1);
			break;
		}
		printf("wrong format try again\n");
	}while(1);

	do{
		printf("enter income:	");
		scanf("%Lf",&tincome);
		getch();
		s=intvalidation(tincome);
		if(s!=100 && (tincome>999)){
			acc[accountCounter].income=tincome;
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	acc[accountCounter].alive=1;
	acc[accountCounter].listCount=0;
	printf("new account sucessfully created\nyour details are\n");
	accountIndex=accountCounter;
	getch();
	details();

}

//ac_id generator comes in new account function
void accountNumberGenerator()
{
	char temp1[10];
	char temp2[10];
	unsigned long long int counterFormat=1000000;
	unsigned long long int localCounter=accountCounter+counterFormat;
	strcpy(newAccountId,"YOLO");
	sprintf(temp1,"%llu",localCounter);
	strcpy(temp2,&temp1[1]);
	strcat(newAccountId,temp2);
}


//view profile
void profile(){
	int ch;
	clrscr();
	printf("profile:\n\n1.change password\n2.view details\neneter your choice\n");
	scanf("%d",&ch);
	switch(ch){
		case 1:changePassword();
				break;
		case 2:accountIndex=employeeIndex;
				details();
				break;
		default:login();
	}
}

void changePassword(){
	int i;
	char a[15],b[15],c[15];
	clrscr();
	printf("change password:\n\nenter old password\n");
	i=0;
	do{
		a[i]=getch();
		if(a[i]=='\r'){
			a[i]='\0';
			printf("\n");
			break;
		}
		printf("*");
		i++;
	}while(1);	

	printf("enter new password\n");
	i=0;
	do{
		b[i]=getch();
		if(b[i]=='\r'){
			b[i]='\0';
			printf("\n");
			break;
		}
		printf("*");
		i++;
	}while(1);

	printf("enter conform password\n");
	i=0;
	do{
		c[i]=getch();
		if(c[i]=='\r'){
			c[i]='\0';
			printf("\n");
			break;
		}
		printf("*");
		i++;
	}while(1);

	if(strcmp(b,c)!=0){
		printf("new password dosent match\n");
		getch();
		login();
	}
	if(strcmp(a,acc[employeeIndex].password)!=0){
		printf("wrong password\n");
		getch();
		login();
	}
	strcpy(acc[employeeIndex].password,b);
	printf("password updated sucessfully\n");
	getch();
	logout();
}

//transaction
void transaction()
{
	int ch;
	clrscr();
	printf("transaction:\n\n1.withdraw\n2.deposit\n\nenter your choice\n");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:withdraw();
				break;
		case 2:deposit();
				break;
		default:login();
	}


}

//deleteAccount
void delete_account()
{
	if(acc[accountIndex].alive==2)
		printf("\n you have no accounts to delete");
	else
	{
	acc[accountIndex].alive=2;
		printf("\n you have deleted the account");
		}
		getch();
		login();

}

//details
void details()
{
	int ch;
	if(acc[accountIndex].alive==2)
	{
	printf("account not exist");
	getch();
	login();
	}
	printf("name: 			%s %s",acc[accountIndex].fname,acc[accountIndex].lname);
	printf("\nphone number: 		%s",acc[accountIndex].phone);
	printf("\ndate of birth:		%d-%d-%d",acc[accountIndex].dob.date,acc[accountIndex].dob.month,acc[accountIndex].dob.year);
	printf("\ngender: 		%s",acc[accountIndex].gender);
	printf("\naddress: 		%s,%s,%s,%s,%s",acc[accountIndex].address.hno,acc[accountIndex].address.colony,acc[accountIndex].address.area,acc[accountIndex].address.district,acc[accountIndex].address.pin);
	printf("\nprofession: 		%s",acc[accountIndex].profession);
	printf("\ncategory: 		%s",acc[accountIndex].category);
	printf("\nincome: 		%Lf",acc[accountIndex].income);
	printf("\nend of details\n");
	printf("select 1.to edit details\t2.exit	:");
	scanf("%d",&ch);
	switch(ch){
		case 1:	printf("you selected editDetails\n");
				getch();
				editDetails();
				break;
		default: printf("exiting\n");
				getch();
				break;
	}
	login();
}

//transaction: withdraw
void withdraw()
	{
		int ch;
		clrscr();
		printf("withdraw:\n\n1.cash\n2.transfer\n3.dd\n\nenter your choice:\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:wcash();
					break;
			case 2:transfer();
					break;
			case 3:dd();
				   break;
			default:transaction();
		}
	}

//transaction:deposit
	void deposit()
	{
		int ch;
		printf("1.cash\n2.cheque\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:dcash();
				break;
			case 2: cheque();
				break;
			default:login();
		}
	}

//transaction:withdraw:cash
	void wcash()
	{
		int s,a;
		long double amt;
		printf("withdraw cash:\n");
		do{
		printf("enter amount: ");
		scanf("%Lf",&amt);
		a=longDoublevalidation(amt);
		if(a!=100){
			break;
		}
		printf("wrong format try again\n");
		}while(1);
		if(acc[accountIndex].balance>=amt){
			acc[accountIndex].balance=(acc[accountIndex].balance)-amt;
			printf("\nwithdraw sucessfull\nyour balance is %Lf",acc[accountIndex].balance);
			readHistory(accountIndex,accountIndex,1,amt);
			getch();
			accounts();
		}
		else{
			printf("insufficient balance\nyour balance is %Lf", acc[accountIndex].balance);
			getch();
			printf("enter\n1 to try again\n2 to exit");
			scanf("%d",&s);
			switch(s){
				case 1:wcash();
				break;
				case 2:accounts();
				break;
				default:logout();
			}
		}
	}	

	//transfer
	void transfer()
	{
		char sac[11];
		int s,si,a;
		long double amt;
		clrscr();
		printf("transfer\n\n");
		printf("enter account no\n");
		scanf("%s",sac);
		si=search(sac);
		if(si==totalAccounts){
			printf("account not found\n");
			getch();
			login();
		}
		 else{
			do{
			printf("enter amount: ");
			scanf("%Lf",&amt);
			a=longDoublevalidation(amt);
			if(a!=100){
				break;
			}
			printf("wrong format try again\n");
			}while(1);

			if(acc[accountIndex].balance>=amt){
				acc[accountIndex].balance-=amt;
				acc[si].balance+=amt;
				printf("transfer sucessfull\nyour balance is %Lf",acc[accountIndex].balance);
				readHistory(accountIndex,si,1,amt);
				readHistory(si,accountIndex,2,amt);
				getch();
				login();
			}
			else{
				printf("insufficient balance\nyour balance is %Lf", acc[accountIndex].balance);
				getch();
				printf("enter\n1 to try again\n2 to exit\n");
				scanf("%d",&s);
				switch(s){
				case 1:transfer();
						break;
				case 2:accounts();
						break;
				default:logout();
				}
			}
		}
	}

	//demandDraft
	void dd()
	{
		char sac[11];
		int s,si,a;
		long double amt;
		printf("enter account no\n");
		scanf("%s",sac);
		si=search(sac);
		if(si==totalAccounts){
			printf("account not found\n");
			getch();
			login();
		}
		else{
			do{
			printf("enter amount: ");
			scanf("%Lf",&amt);
			a=longDoublevalidation(amt);
			if(a!=100){
				break;
			}
			printf("wrong format try again\n");
			}while(1);
			if(acc[accountIndex].balance>=amt){
				acc[accountIndex].balance=(acc[accountIndex].balance)-amt;
				acc[si].balance=(acc[si].balance)+amt;
				printf("dd sucessfull\nyour balance is %Lf",acc[accountIndex].balance);
				readHistory(accountIndex,si,1,amt);
				readHistory(si,accountIndex,2,amt);
				getch();
				login();
			}
			else{
				printf("insufficient balance\nyour balance is %Lf", acc[accountIndex].balance);
				getch();
				printf("enter\n1 to try again\n2 to exit\n");
				scanf("%d",&s);
				switch(s){
					case 1:transfer();
						break;
					case 2:accounts();
						break;
					default:login();
				}
			}
		}
	}

	//transaction:deposit:cash
	void dcash()
	{
		long double amt;
		int a;
		do{
		printf("enter amount: ");
		scanf("%Lf",&amt);
		a=longDoublevalidation(amt);
		if(a!=100){
			break;
		}
		printf("wrong format try again\n");
		}while(1);
		acc[accountIndex].balance=(acc[accountIndex].balance)+amt;
		printf("balance sucessfully deposited\n");
		readHistory(accountIndex,accountIndex,2,amt);
		//transactionHistory(acc[accountIndex].ac_id,amt,0);
		printf("your balance is %Lf",acc[accountIndex].balance);
		getch();
		login();
	}

	//cheque
	void cheque(){
		char sac[11];
		int s,si,a;
		long double amt;
		printf("enter account no\n");
		scanf("%s",sac);
		si=search(sac);
		if(si==totalAccounts){
			printf("account not found\n");
			getch();
			login();
		}
		else{
			do{
			printf("enter amount: ");
			scanf("%Lf",&amt);
			a=longDoublevalidation(amt);
			if(a!=100){
				break;
			}
			printf("wrong format try again\n");
			}while(1);
			if(acc[si].balance>=amt){
				acc[si].balance=(acc[si].balance)-amt;
				acc[accountIndex].balance=(acc[accountIndex].balance)+amt;
				printf("cheque sucessfull\nyour balance is %Lf",acc[accountIndex].balance);
				readHistory(accountIndex,si,1,amt);
				readHistory(si,accountIndex,2,amt);
				getch();
				login();
			}
			else{
				printf("cheque bounced\n");
				getch();
				printf("enter\n1 to try again\n2 to exit\n");
				scanf("%d",&s);
				switch(s){
				case 1:cheque();
						break;
				case 2:accounts();
						break;
				default:login();
				}
			}
		}
	}


//masterdetails	
void masterdetails()
{
	strcpy(acc[0].ac_id,"1234");
	strcpy(acc[0].password,"1234");
	strcpy(acc[0].fname,"master");
	strcpy(acc[0].lname,"kudo");
	acc[0].dob.date=14;
	acc[0].dob.month=2;
	acc[0].dob.year=1947;
	strcpy(acc[0].gender,"male");
	strcpy(acc[0].address.hno,"3");
	strcpy(acc[0].address.colony,"Solar System");
	strcpy(acc[0].address.area,"Milky Way");
	strcpy(acc[0].address.district,"Universe");
	strcpy(acc[0].address.pin,"143143");
	strcpy(acc[0].profession,"IRONMAN");
	strcpy(acc[0].category,"employee");
	acc[0].balance=1000000;
	acc[0].income=100000;
	strcpy(acc[0].phone,"9900009848");
	acc[0].alive=1;
	acc[0].listCount=0;
}

//history
void readHistory(int tai,int fai,int tcd,long double ttr){
	time_t tt;
	char ttime[40];
	int lc=acc[tai].listCount;
	acc[tai].listCount++;
	time(&tt);
	strcpy(ttime,ctime(&tt));

	strcpy(list[tai][lc].dt,ttime);
	(list[tai][lc].balance)=ttr;
	strcpy(list[tai][lc].h_id,acc[fai].ac_id);
	(list[tai][lc].flag)=(double)tcd;
}

void displayHistory(){
	int i;
	char a[10];
	printf("your transactions are\n");
	for (i = 0; i < acc[accountIndex].listCount; i++)
	{
		if(list[accountIndex][i].flag==1){
			strcpy(a,"debit");
		}
		else{
			strcpy(a,"credit");
		}
		printf("%s  %s  %s  %Lf\n",list[accountIndex][i].dt,list[accountIndex][i].h_id,a,list[accountIndex][i].balance);
	}
	getch();
	login();
}


int intvalidation(int a){
	int s=0;
	if((getchar()!='\n') && (a<=0)){
		while ((getchar()) != '\n');
		return 100;
	}
	while(a>0){
		a=a/10;
		s++;
	}
	return s;
}

int longDoublevalidation(long double a){
	int s=0;
	if((getchar()!='\n') && (a<=0)){
		while ((getchar()) != '\n');
		return 100;
	}
	while(a>0){
		a=a/10;
		s++;
	}
	return s;
}

void editDetails(){
	char tcategory[5],tfname[25],tlname[25],tpassword[15],tprofession[15];
	char tphone[11];
	int tage,s,ch,v;
	char thno[10],tcolony[15],tarea[15],tdistrict[15],tpin[7];
	int tdate,tmonth,tyear;
	long double tincome;
	printf("%s\n",acc[accountIndex].ac_id);
	do{
		printf("enter first name:	");
		scanf("%s",&tfname);
		v=alphaValidation(tfname);
		if(((strlen(tfname))<=25) && (v==0)){
			strcpy(acc[accountIndex].fname,tfname);
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	do{
		printf("enter last name:	");
		scanf("%s",&tlname);
		v=alphaValidation(tlname);
		if(((strlen(tfname))<=25) && (v==0)){
			strcpy(acc[accountIndex].lname,tlname);
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	do{
		printf("enter phone number:	");
		scanf("%s",&tphone);
		v=digitValidation(tphone);
		if((strlen(tphone))==10 && (v==0)){
			strcpy(acc[accountIndex].phone,tphone);
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	do{
		printf("enter date:	");
		scanf("%d",&tdate);
		s=intvalidation(tdate);
		if((s<=2 && s>0) && (tdate<=31)){
			acc[accountIndex].dob.date=tdate;
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	do{
		printf("enter month:	");
		scanf("%d",&tmonth);
		s=intvalidation(tmonth);
		if((s<=2) && (tmonth<=12)){
			acc[accountIndex].dob.month=tmonth;
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	do{
		printf("enter year:	");
		scanf("%d",&tyear);
		s=intvalidation(tyear);
		if((s==4) && (tyear<=2019) && (tyear>=1919)){
			acc[accountIndex].dob.year=tyear;
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	do{
		printf("select your gender:\n1.male	2.female\n");
		scanf("%d",&ch);
		switch(ch){
			case 1:	printf("you selected male\n");
					strcpy(acc[accountIndex].gender,"male");
					break;
			case 2:	printf("you selected female\n");
					strcpy(acc[accountIndex].gender,"female");
					break;
			default: printf("wrong choice try again\n");
					break;
		}
	}while((ch!=1) && (ch!=2));
	printf("enter address:\n");
	do{
		printf("enter house no:	");
		scanf("%s",&thno);
		if((strlen(thno))<=10){
			strcpy(acc[accountIndex].address.hno,thno);
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	do{
		printf("enter colony:	");
		scanf("%s",&tcolony);
		v=alphaValidation(tcolony);
		if((strlen(tcolony))<=15 && (v==0)){
			strcpy(acc[accountIndex].address.colony,tcolony);
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	do{
		printf("enter area:	");
		scanf("%s",&tarea);
		v=alphaValidation(tarea);
		if((strlen(tarea))<=15 && (v==0)){
			strcpy(acc[accountIndex].address.area,tarea);
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	do{
		printf("enter district:	");
		scanf("%s",&tdistrict);
		v=alphaValidation(tdistrict);
		if((strlen(tdistrict))<=15 && (v==0)){
			strcpy(acc[accountIndex].address.district,tdistrict);
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	do{
		printf("enter areas pincode:	");
		scanf("%s",&tpin);
		v=digitValidation(tpin);
		if((strlen(tpin))==6 && (v==0)){
			strcpy((acc[accountIndex].address.pin),tpin);
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	do{
		printf("enter profession:	");
		scanf("%s",&tprofession);
		v=alphaValidation(tprofession);
		if((strlen(tprofession))<=15 && (v==0)){
			strcpy(acc[accountIndex].profession,tprofession);
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	do{
		printf("enter income:	");
		scanf("%Lf",&tincome);
		getch();
		s=intvalidation(tincome);
		if(s!=100 && (tincome>999)){
			acc[accountIndex].income=tincome;
			break;
		}
		printf("wrong format try again\n");
	}while(1);
	printf("details sucessfully updated\nyour details are\n");
	getch();
	details();
}

int alphaValidation(char a[25])
{
	int i,f=0;
	
	for(i=0;i<=(strlen(a));i++)
	{
		if((isdigit(a[i])!=0))
			f=1;
	}
	return f;
}

int digitValidation(char a[25])
{
	int i,f=0;
	
	for(i=0;i<=(strlen(a));i++)
	{
		if((isalpha(a[i])!=0))
			f=1;
	}
	return f;
}
