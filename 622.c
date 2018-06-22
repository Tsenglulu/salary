#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct ZGGZ
{
	char wo_name[10];//职工姓名
	char id[10];//职工工号
	double position_value;//岗位工资
	double Pay_salary;//薪级工资
	double duty_allowance;//职务津贴
	double merit_pay;//绩效工资
	double gross_pay;//应发工资
	double Personal_income_tax;//个人所得税
	double payroll;//实发工资
}zggz;//工资数据结构体

int count=0;//员工数 全局变量

void add_money(zggz S[])	//计算应发工资       
{
	int i;
	for(i=0;i<count;i++)
		S[i].gross_pay=S[i].position_value+S[i].Pay_salary+S[i].duty_allowance+S[i].merit_pay;
}


void grsds(zggz S[])		//计算个人所得税       
{
	int i;
	for(i=0;i<count;i++)
	{
		if(S[i].gross_pay<1500)																									//工资小于1500时个人所得税																											
			S[i].Personal_income_tax=0;
		else if(S[i].gross_pay<4500)																							//工资大于1500小于4500时个人所得税
			S[i].Personal_income_tax=(S[i].gross_pay-1500)*0.1;	
		else if(S[i].gross_pay<9000)																							//工资大于4500小于9000时个人所得税
			S[i].Personal_income_tax=(S[i].gross_pay-4500)*0.2+3000*0.1;														     			
		else if(S[i].gross_pay<35000)																							//工资大于9000小于35000时个人所得税
			S[i].Personal_income_tax=(S[i].gross_pay-9000)*0.25+4500*0.2+3000*0.1;														    
		else if(S[i].gross_pay<55000)																							//工资大于35000小于55000时个人所得税
			S[i].Personal_income_tax=(S[i].gross_pay-35000)*0.3+26000*0.25+4500*0.2+3000*0.1;											     
		else if(S[i].gross_pay<80000)																							//工资大于55000小于80000时个人所得税
			S[i].Personal_income_tax=(S[i].gross_pay-55000)*0.35+20000*0.3+26000*0.25+4500*0.2+3000*0.1;								     					
		else																												//工资大于80000时个人所得税
			S[i].Personal_income_tax=(S[i].gross_pay-80000)*0.45+25000*0.35+20000*0.35+20000*0.3+26000*0.25+4500*0.2+3000*0.1;		
	}
}


void add_wages(zggz S[])	//计算实发工资	       
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
	{   //若打开文件失败则退出

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
		count++;       
	}
		
	printf("\t有%d个员工信息被读入\n",count);
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
		{   //若打开文件失败则退出

            puts("不能打开文件！");
            return 0;
		}

		for(i=0;i<count;i++)
		{
			printf("\n");
		    fprintf(fp1, "%s\n", t[i].wo_name);
	        fprintf(fp1, "%s\n", t[i].id);              
	       	fprintf(fp1, "%lf\n", t[i].position_value);              
			fprintf(fp1, "%lf\n", t[i].Pay_salary);              
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
	printf("\n\n请输入要查询的工号:");
	scanf("%s",gonghao);
	for(i=0;i<count;i++)
	{
		if (strcmp(t[i].id,gonghao)==0)
		{
			flag = 1;
			break;
		}
	}
	
	//如果存在该员工，那么输出该员工的信息
 
	if (flag)
	{    
		
		printf("\n");              
		printf("\t\t姓名:%s\n", t[i].wo_name);
		printf("\t\t工号:%s\n", t[i].id);              
		printf("\t\t岗位工资:%lf\n", t[i].position_value);              
		printf("\t\t薪级工资:%lf\n", t[i].Pay_salary);              
		printf("\t\t职务津贴:%lf\n", t[i].duty_allowance);              
		printf("\t\t绩效工资:%lf\n", t[i].merit_pay);    
		printf("\t\t应发工资:%lf\n", t[i].gross_pay); 
		printf("\t\t个人所得税:%lf\n", t[i].Personal_income_tax);
		printf("\t\t实发工资:%lf\n", t[i].payroll);   

	 } 
	 else
	 { 
		 printf("没有找到该编号的员工！\n"); 
	 }
     
	printf("\n");
	system("pause");
    return 0;
}


int list(zggz t[])//浏览职工工资数据函数
{

	int i;
	int asd=count;
	if(asd=!0)
	{
			
		for(i=0;i<count;i++)
		{
			
			 
			printf("\t\t姓名:%s\n", t[i].wo_name);
			printf("\t\t工号:%s\n", t[i].id);              
			printf("\t\t岗位工资:%lf\n", t[i].position_value);              
			printf("\t\t薪级工资:%lf\n", t[i].Pay_salary);              
			printf("\t\t职务津贴:%lf\n", t[i].duty_allowance);              
			printf("\t\t绩效工资:%lf\n", t[i].merit_pay);    
			printf("\t\t应发工资:%lf\n", t[i].gross_pay); 
			printf("\t\t个人所得税:%lf\n", t[i].Personal_income_tax);
			printf("\t\t实发工资:%lf\n", t[i].payroll);  
			printf("\n");

		}
	}
	else
	{ 
		printf("没有员工！\n");  
	}
	return 0;
}


int modify(zggz t[])//修改职工工资数据函数
{
	char gonghao[10];
	int flag=0;//标记员工有没有存在
	int i=0;//记录员工存在的位置
	printf("\n\n请输入要修改的工号");
	scanf("%s",gonghao);
	for(i=0;i<count;i++)
	{
		if (strcmp(t[i].id,gonghao)==0)
		{
			flag = 1;
			break;
		}
	}

	if (flag)
	{              
			printf("\n您要修改的内容如下：\n");           
			printf("\t\t姓名:%s\n", t[i].wo_name);
			printf("\t\t工号:%s\n", t[i].id);              
			printf("\t\t岗位工资:%lf\n", t[i].position_value);              
			printf("\t\t薪级工资:%lf\n", t[i].Pay_salary);              
			printf("\t\t职务津贴:%lf\n", t[i].duty_allowance);              
			printf("\t\t绩效工资:%lf\n", t[i].merit_pay);    
			printf("\t\t应发工资:%lf\n", t[i].gross_pay); 
			printf("\t\t个人所得税:%lf\n", t[i].Personal_income_tax);
			printf("\t\t实发工资:%lf\n", t[i].payroll);
			printf("\n");
   
				printf("\n请输入修改后的position_value：");
				scanf("%f",&t[i].position_value);
				 
				printf("\n请输入修改后的Pay_salary：");
			 	scanf("%f",&t[i].Pay_salary);

				printf("\n请输入修改后的duty_allowance：");
			 	scanf("%f",&t[i].duty_allowance);


				printf("\n请输入修改后的merit_pay：");
			 	scanf("%f",&t[i].merit_pay);
				
					add_money(t);
					grsds(t);
					add_wages(t);

	} 
	else
	{ 
		printf("没有找到该编号的员工！\n"); 
	}
	return 0;
}


int add(zggz t[])
{
	if (count>50)
	{
		printf("员工信息已满！\n");
        return 0;
	} 
	else
	{
        printf("\n");

		printf("\n请输入员工的编号：");
        scanf("%s", t[count].id);
			  		 
        printf("\n请输入员工的姓名：");
		scanf("%s",t[count].wo_name);

		printf("\n请输入员工的position_value：");
		scanf("%lf",&t[count].position_value);

		printf("\n请输入员工的Pay_salary：");
		scanf("%lf",&t[count].Pay_salary);
		
		printf("\n请输入员工的duty_allowance：");
		scanf("%lf", &t[count].duty_allowance);
		
		printf("\n请输入员工的merit_pay：");
		scanf("%lf", &t[count].merit_pay);
	
		count++;//count后加1

			add_money(t);
			grsds(t);
			add_wages(t);

				printf("\n员工信息已经添加\n\n");

    }
	return 0;
}

int del(zggz t[])
{
	char gonghao[10];//存储需要删除的员工编号
	int flag=0;//标记有没有该员工
	int sum_count=0;//用来记录删除了几个员工信息
	int i=0;
	int j=0;
	printf("\n请输入要删除员工的编号：");
	scanf("%s",gonghao);

	for(i=0;i<=count;i++)
	{
		if(strcmp(t[i].id,gonghao)==0)
		{//找到了需要删除的员工编号
			flag=1;
			break;				  
		}
	}	

	if(flag)
	{
		for(j=i;j<count;j++)
		{
			t[j]=t[j+1];
		}
				
			printf("\n该员工信息已经删除\n");
			sum_count++;//删除了一个员工就加一
	}

	count = count-sum_count;

	if(flag==1)
	{
		printf("\n该员工信息已经删除\n");
	}
	write(t);
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
                add(z);//添加
                break;
            case 4:
                del(z);//删除
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

