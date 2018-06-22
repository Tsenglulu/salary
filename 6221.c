#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct ZGGZ{
	char wo_name[10];//职工姓名
	char id[10];//职工工号
	double position_value, Pay_salary;//岗位工资、薪级工资
	double duty_allowance, merit_pay, gross_pay, Personal_income_tax, payroll;//职务津贴、绩效工资、应发工资、个人所得税和实发工资
}zggz;//工资数据结构体

int count=0;


void add_money(zggz S[])	//自检模块 计算应发工资       
{
	int i;
	for(i=0;i<count;i++)
		S[i].gross_pay=S[i].position_value+S[i].Pay_salary+S[i].duty_allowance+S[i].merit_pay;
}


void grsds(zggz S[])		//自检模块 计算个人所得税       
{
	int i;
	for(i=0;i<count;i++)
	{
		if(S[i].gross_pay<1500)																									//工资小于500时个人所得税																											
			S[i].Personal_income_tax=0;
		else if(S[i].gross_pay<4500)																							//工资大于500小于2000时个人所得税
			S[i].Personal_income_tax=(S[i].gross_pay-1500)*0.1;	
		else if(S[i].gross_pay<9000)																							//工资大于2000小于5000时个人所得税
			S[i].Personal_income_tax=(S[i].gross_pay-4500)*0.2+3000*0.1;														     			
		else if(S[i].gross_pay<35000)																							//工资大于5000小于20000时个人所得税
			S[i].Personal_income_tax=(S[i].gross_pay-9000)*0.25+4500*0.2+3000*0.1;														    
		else if(S[i].gross_pay<55000)																							//工资大于20000小于40000时个人所得税
			S[i].Personal_income_tax=(S[i].gross_pay-35000)*0.3+26000*0.25+4500*0.2+3000*0.1;											     
		else if(S[i].gross_pay<80000)																							//工资大于40000小于60000时个人所得税
			S[i].Personal_income_tax=(S[i].gross_pay-55000)*0.35+20000*0.3+26000*0.25+4500*0.2+3000*0.1;								     					
		else																												//工资大于100000时个人所得税
			S[i].Personal_income_tax=(S[i].gross_pay-80000)*0.45+25000*0.35+20000*0.35+20000*0.3+26000*0.25+4500*0.2+3000*0.1;		
	}
}


void add_wages(zggz S[])	//自检模块 计算实发工资	       
{
	int i;
	for(i=0;i<count;i++)
		S[i].payroll=S[i].gross_pay-S[i].Personal_income_tax;
}


int read(zggz t[])			//读取职工工资数据函数
{
	zggz T;
	FILE *fp;//定义文件指针
       if ((fp = fopen("gx.dat", "rb")) == NULL)
		{//若打开文件失败则退出
        puts("不能打开文件！");
        return 0;
		}
		//如果文件打开成功，那么进行读数据 
		
		
		while (!feof(fp))       
		{              
		fscanf(fp, "%s\t", &T.wo_name);
		fscanf(fp, "%s\t", &T.id);              
		fscanf(fp, "%lf\t", &T.position_value);              
		fscanf(fp, "%lf\t", &T.Pay_salary);              
		fscanf(fp, "%lf\n", &T.duty_allowance);              
		fscanf(fp, "%lf\n", &T.merit_pay);    
		fscanf(fp, "%lf\n", &T.gross_pay); 
		fscanf(fp, "%lf\n", &T.Personal_income_tax);
		fscanf(fp, "%lf\n", &T.payroll);    
		t[count]=T;
		count++;       }
		printf("\n有%d个员工信息被读入\n",count);

		fclose(fp);
		return count;		
}


int write(zggz t[])				//保存职工工资数据函数
{
	int i;
	 if(count>0)
	 {
		FILE* fp1=fopen("gz.dat","w");
		if (fp1==NULL)
		{
			//若打开文件失败则退出
            puts("不能打开文件！");
            return 0;
		}
		for(i=0;i<count;i++)
		{
			printf("\n");
		    fprintf(fp1, "%s\n", t[i].wo_name);
	        fprintf(fp1, "%s\t", t[i].id);              
	       	fprintf(fp1, "%lf\t", t[i].position_value);              
			fprintf(fp1, "%lf\t", t[i].Pay_salary);              
			fprintf(fp1, "%lf\n", t[i].duty_allowance);              
			fprintf(fp1, "%lf\n", t[i].merit_pay);    
			fprintf(fp1, "%lf\n", t[i].gross_pay); 
			fprintf(fp1, "%lf\n", t[i].Personal_income_tax);
			fprintf(fp1, "%lf\n", t[i].payroll);
		}	
		fclose(fp1);
	}else
	 {
		 printf("人数为空");
	 }

    return 0;
}


int find(zggz t[])//查询职工工资数据函数
{
	char gonghao[10];
	int flag=0;//标记员工有没有存在
	int j=0;//记录员工存在的位置
	int i=0;//记录员工存在的位置
	printf("\n请输入要查询的工号");
	scanf("%s",gonghao);
	printf("%s",t[0].id);
	printf("%s",gonghao);
	//遍历结构体数组，查找有无该编号的员工 若有flag=1，反之flag=0
	for(i=0;i<count;i++)
	{
		
		if (*(t[i].id)==*(gonghao))
		{
			printf("%s",t[i].id);
			flag = 1;
			break;
		}
	}
	
 //如果存在该员工，那么输出该员工的信息
 if (flag)
 {              
		printf("编号\t姓名\t性别\t职称\t年龄\t工资\n");              
		printf("%s\t", t[i].wo_name);
		printf("%s\t", t[i].id);              
		printf("%f\t", t[i].position_value);              
		printf("%f\t", t[i].Pay_salary);              
		printf("%f\t", t[i].duty_allowance);              
		printf("%f\t", t[i].merit_pay);    
		printf("%f\t", t[i].gross_pay); 
		printf("%f\t", t[i].Personal_income_tax);
		printf("%f\t", t[i].payroll);   
	 //由于员工数组中有多个编号一样的员工，所以需要继续寻找，用j来标记员工的位置  然后输出该员工的信息             
	 //第二次寻找的起始位置应该从i+1开始 因为之前的已经找过了
	 for (j = i+1; j<count; j++)
	 {                     
		 if (t[j].id == gonghao)
		 {                            
		printf("%s\t", t[j].wo_name);
		printf("%s\t", t[j].id);              
		printf("%f\t", t[j].position_value);              
		printf("%f\t", t[j].Pay_salary);              
		printf("%f\t", t[j].duty_allowance);              
		printf("%f\t", t[j].merit_pay);    
		printf("%f\t", t[j].gross_pay); 
		printf("%f\t", t[j].Personal_income_tax);
		printf("%f\t", t[j].payroll);
		 }
	 }
 } else{ printf("没有找到该编号的员工！\n"); }
     
 printf("\n");
 system("pause");
 return 0;
}


int list(zggz t[])//浏览职工工资数据函数
{

	int j;
	int asd=count;
	if(asd=!0)
	{
		printf("%d",count);
		
		for(j=0;j<count;j++)
		{
		
		printf("编号\t姓名\t性别\t职称\t年龄\t工资\n");              
		printf("%s\t", t[j].wo_name);
		printf("%s\t", t[j].id);
		printf("%f\t", t[j].position_value);              
		printf("%f\t", t[j].Pay_salary);              
		printf("%f\t", t[j].duty_allowance);              
		printf("%f\t", t[j].merit_pay);    
		printf("%f\t", t[j].gross_pay); 
		printf("%f\t", t[j].Personal_income_tax);
		printf("%f\t", t[j].payroll);
		printf("\n");

		}
	}else{ printf("没有员工！\n");  }
	return 0;
}


int modify(zggz t[])//修改职工工资数据函数
{
	
	//double position_value, Pay_salary, duty_allowance, merit_pay, gross_pay, Personal_income_tax,payroll;
	char gonghao[10];
	int flag=0;//标记员工有没有存在
	int i=0;//记录员工存在的位置
	printf("请输入要查询的工号");
	scanf("%s",gonghao);
	for(i=0;i<count;i++)
	{
		if (*(t[i].id)==*(gonghao))
		{
			flag = 1;
			break;
		}
	}

 if (flag)
 {              
		printf("编号\t姓名\t性别\t职称\t年龄\t工资\n");              
		printf("%s\t", t[i].wo_name);
		printf("%s\t", t[i].id);              
		printf("%f\t", t[i].position_value);              
		printf("%f\t", t[i].Pay_salary);              
		printf("%f\t", t[i].duty_allowance);              
		printf("%f\t", t[i].merit_pay);    
		printf("%f\t", t[i].gross_pay); 
		printf("%f\t", t[i].Personal_income_tax);
		printf("%f\t", t[i].payroll);     
   
			 printf("\n请输入修改position_value");
			 scanf("%lf",&t[i].position_value);
				 
				 printf("%lf\t", t[i].position_value);

			 printf("\n请输入修改Pay_salary");
			 			 scanf("%lf",&t[i].Pay_salary);
				 //t[i].Pay_salary=a.Pay_salary;

			 printf("\n请输入修改duty_allowance");
			 			 scanf("%lf",&t[i].duty_allowance);
				 //t[i].duty_allowance=a.duty_allowance;

			 printf("\n请输入修改merit_pay");
			 			 scanf("%lf",&t[i].merit_pay);
				 //t[i].merit_pay=a.merit_pay;

				 	add_money(t);
					grsds(t);
					add_wages(t);



 } else{ printf("没有找到该编号的员工！\n"); }
	return 0;
}



int add()
{
	return 0;
}
int del()
{
	return 0;
}



int main()
{
	zggz z[50];
	int menu();
	read(z);
	add_money(z);
	grsds(z);
	add_wages(z);

    do{ 
        switch(menu()){
            case 1:
                find(z);//查询
                break;
            case 2:
                modify(z);//修改
                break;
            case 3:
                add();//添加
                break;
            case 4:
                del();//删除
                break;
            case 5:
                write(z);//保存
                break;
            case 6:
                list(z);//浏览
				break;
            case 7:
                goto exit;
        }
    }while(1);
    exit:
    return 0;
}

int menu()
{
   int option=0;
    char i=0;
    printf("*************Main Menu*************\n");
    printf("     1. 查询职工工资数据函数\n");
    printf("     2. 修改职工工资数据函数\n");
    printf("     3. 添加职工工资数据函数\n");
    printf("     4. 删除职工工资数据函数\n");
    printf("     5. 保存职工工资数据函数\n");
    printf("     6. 浏览职工工资数据函数\n");
	printf("     7. Exit the program\n");
    printf("***********************************\n");
	printf("\t请您选择(1-7):");
    scanf("%c",&i);
    option=(int)(i-'0');
    while(option<1||option>7){
        printf("Input Error!\nPlease retype:\n");
        scanf("%d",&option);
    }
    return option;
}

