/***********************************************************

  Copyright (C), 2017-2018
  FileName:PayrollSystem.c
  Author:郑路璐		Date:2018/6/26
  Function List: 
	add_money() 计算应发工资
	grsds()		计算个人所得税 
	add_wages()	计算实发工资
	read()		读取职工工资数据函数
	write()		保存职工工资数据函数
	find()		查询职工工资数据函数
	list()		浏览职工工资数据函数
	modify()	修改职工工资数据函数
	add()		添加职工工资数据函数
	del()		删除职工工资数据函数
	menu()		菜单函数

***********************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int n=0;	/*员工数 全局变量*/
typedef struct ZGGZ
{
	char wo_name[10];			/*职工姓名*/
	char id[10];				/*职工工号*/
	float position_value;		/*岗位工资*/
	float Pay_salary;			/*薪级工资*/
	float duty_allowance;		/*职务津贴*/
	float merit_pay;			/*绩效工资*/
	float gross_pay;			/*应发工资*/
	float Personal_income_tax;	/*个人所得税*/
	float payroll;				/*实发工资*/
}zggz;


int menu()
{
   int option=0;
    char i=0;
	printf("\n\n\t请选择<1 - 7>:\n");
    printf("\t================================================================\n");
    printf("\t|         1. 查询职工工资数据函数                              |\n");
    printf("\t|         2. 修改职工工资数据函数                              |\n");
    printf("\t|         3. 添加职工工资数据函数                              |\n");
    printf("\t|         4. 删除职工工资数据函数                              |\n");
    printf("\t|         5. 保存职工工资数据函数                              |\n");
    printf("\t|         6. 浏览职工工资数据函数                              |\n");
	printf("\t|         7. Exit the program                                  |\n");
    printf("\t================================================================\n");
	printf("\n\t你的选择是：");
    scanf("%c",&i);
    option=(int)(i-'0');
    while(option<1||option>7){
        printf("Input Error!Please retype:");
        scanf("%d",&option);
    }
    return option;
}


void add_money(zggz S[])			/*计算应发工资*/       
{
	int i;
	for(i=0;i<n;i++)
		S[i].gross_pay=S[i].position_value+S[i].Pay_salary+S[i].duty_allowance+S[i].merit_pay;
}


void grsds(zggz S[])				/*计算个人所得税*/       
{
	int i;
	for(i=0;i<n;i++)
	{
		if(S[i].gross_pay<500)																									//工资小于500时个人所得税																											
			S[i].Personal_income_tax=S[i].gross_pay*0.05;
		else if(S[i].gross_pay<2000)																							//工资大于500小于2000时个人所得税
			S[i].Personal_income_tax=(S[i].gross_pay-500)*0.1+500*0.05;
		else if(S[i].gross_pay<5000)																							//工资大于2000小于5000时个人所得税
			S[i].Personal_income_tax=(S[i].gross_pay-2000)*0.15+1500*0.1+500*0.05;	
		else if(S[i].gross_pay<20000)																							//工资大于5000小于20000时个人所得税
			S[i].Personal_income_tax=(S[i].gross_pay-5000)*0.2+3000*0.15+1500*0.1+500*0.05;															     			
		else if(S[i].gross_pay<40000)																							//工资大于20000小于40000时个人所得税
			S[i].Personal_income_tax=(S[i].gross_pay-20000)*0.25+15000*0.2+3000*0.15+1500*0.1+500*0.05;															    
		else if(S[i].gross_pay<60000)																							//工资大于40000小于60000时个人所得税
			S[i].Personal_income_tax=(S[i].gross_pay-40000)*0.3+20000*0.25+15000*0.2+3000*0.15+1500*0.1+500*0.05;											     
		else if(S[i].gross_pay<80000)																							//工资大于60000小于80000时个人所得税
			S[i].Personal_income_tax=(S[i].gross_pay-60000)*0.35+20000*0.3+20000*0.25+15000*0.2+3000*0.15+1500*0.1+500*0.05;								     					
		else if(S[i].gross_pay<100000)																							    //工资大于80000小于100000时个人所得税
			S[i].Personal_income_tax=(S[i].gross_pay-80000)*0.4+20000*0.35+20000*0.3+20000*0.25+15000*0.2+3000*0.15+1500*0.1+500*0.05;				
		else																													//工资大于100000时个人所得税
			S[i].Personal_income_tax=(S[i].gross_pay-100000)*0.45+20000*0.4+20000*0.35+20000*0.3+20000*0.25+15000*0.2+3000*0.15+1500*0.1+500*0.05;		
	}
}


void add_wages(zggz S[])			/*计算实发工资*/	       
{
	int i;
	for(i=0;i<n;i++)
		S[i].payroll=S[i].gross_pay-S[i].Personal_income_tax;
}


int read(zggz t[])					/*读取职工工资数据函数*/
{
	zggz T;
	FILE *fp;/*定义文件指针*/
    if ((fp = fopen("gx.dat", "rb")) == NULL)
	{		 /*若打开文件失败则退出*/

		puts("不能打开文件！");
        return 0;
	}

	/*如果文件打开成功，那么进行读数据*/ 
		
	while (!feof(fp))       
	{              
		fscanf(fp, "%s\t", &T.wo_name);
		fscanf(fp, "%s\t", &T.id);              
		fscanf(fp, "%f\t", &T.position_value);              
		fscanf(fp, "%f\t", &T.Pay_salary);              
		fscanf(fp, "%f\n", &T.duty_allowance);              
		fscanf(fp, "%f\n", &T.merit_pay);    
		fscanf(fp, "%f\n", &T.gross_pay); 
		fscanf(fp, "%f\n", &T.Personal_income_tax);
		fscanf(fp, "%f\n", &T.payroll);    
		t[n]=T;
		n++;       
	}
		
	printf("\n\n");
	fclose(fp);
	return n;		
}


int modify(zggz t[])				/*修改职工工资数据函数*/
{
	char gonghao[10];
	int flag=0; /*标记员工有没有存在*/
	int i=0;	/*记录员工存在的位置*/
	printf("\n\n\t请输入要修改的工号:");
	scanf("%s",gonghao);
	for(i=0;i<n;i++)
	{
		if (strcmp(t[i].id,gonghao)==0)
		{
			flag = 1;
			break;
		}
	}

	if (flag)
	{              
			printf("\n\t您要修改的内容如下：\n");           
			printf("\t姓名:%s\n", t[i].wo_name);
			printf("\t工号:%s\n", t[i].id);              
			printf("\t岗位工资:%f\n", t[i].position_value);              
			printf("\t薪级工资:%f\n", t[i].Pay_salary);              
			printf("\t职务津贴:%f\n", t[i].duty_allowance);              
			printf("\t绩效工资:%f\n", t[i].merit_pay);    
			printf("\t应发工资:%f\n", t[i].gross_pay); 
			printf("\t个人所得税:%f\n", t[i].Personal_income_tax);
			printf("\t实发工资:%f\n", t[i].payroll);
			printf("\n");
   
			printf("\n\t请输入修改后的position_value：");
				scanf("%f",&t[i].position_value);
			printf("\n\t请输入修改后的Pay_salary：");
				scanf("%f",&t[i].Pay_salary);
			printf("\n\t请输入修改后的duty_allowance：");
				scanf("%f",&t[i].duty_allowance);
			printf("\n\t请输入修改后的merit_pay：");
				scanf("%f",&t[i].merit_pay);
				
			add_money(t);
			grsds(t);
			add_wages(t);
			printf("\n\t修改完毕！修改后结果如下：\n\n");

			printf("\t姓名:%s\n", t[i].wo_name);
			printf("\t工号:%s\n", t[i].id);              
			printf("\t岗位工资:%f\n", t[i].position_value);              
			printf("\t薪级工资:%f\n", t[i].Pay_salary);              
			printf("\t职务津贴:%f\n", t[i].duty_allowance);              
			printf("\t绩效工资:%f\n", t[i].merit_pay);    
			printf("\t应发工资:%f\n", t[i].gross_pay); 
			printf("\t个人所得税:%f\n", t[i].Personal_income_tax);
			printf("\t实发工资:%f\n", t[i].payroll);

			write(t);

	} 
	else
	{ 
		printf("\n\t没有找到该编号的员工！\n"); 
	}
	return 0;
}


int add(zggz t[])				/*增添职工工资数据函数*/
{
	int flag;
	int j;
	if (n>55)
	{
		printf("\t员工信息已满！\n");
        return 0;
	} 
	else
	{
        printf("\n");
		printf("\n\t请按序输入添加的工号:");

		do{
			flag=0;
			scanf("%s", t[n].id);
			for(j=0;j<n;j++)
				if(strcmp(t[n].id,t[j].id)==0)
				{
					printf("\n\t工号已经存在，请重新输入:");
					flag=1;
					break;
				}
			
		}while(flag==1);
			  		 
        printf("\n\t请输入要添加的员工的姓名：");
			scanf("%s",t[n].wo_name);
		printf("\n\t请输入要添加的员工的position_value：");
			scanf("%f",&t[n].position_value);			
		printf("\n\t请输入要添加的员工的Pay_salary：");
			scanf("%f",&t[n].Pay_salary);
		printf("\n\t请输入要添加的员工的duty_allowance：");
			scanf("%f",&t[n].duty_allowance);
		printf("\n\t请输入要添加的员工的merit_pay：");
			scanf("%f",&t[n].merit_pay);
		
		n++;//n后加1
		add_money(t);
		grsds(t);
		add_wages(t);
		write(t);
		printf("\n\t员工信息已经添加\n\n");

    }
	return 0;
}

int del(zggz t[])					/*删除职工工资数据函数*/
{
	char gonghao[10];/*存储需要删除的员工编号*/
	int flag=0;		 /*标记有没有该员工*/
	int sum_n=0; /*用来记录删除了几个员工信息*/
	int i=0;
	int j=0;
	printf("\n\t请输入要删除员工的编号：");
	scanf("%s",gonghao);

	for(i=0;i<=n;i++)
	{
		if(strcmp(t[i].id,gonghao)==0)
		{ /*找到了需要删除的员工编号*/
			flag=1;
			break;				  
		}
	}	

	if(flag==1)
	{
		for(j=i;j<n;j++)
		{
			t[j]=t[j+1];
		}
				
			printf("\n\t该员工已被删除成功！\n");
			sum_n++;/*删除了一个员工就+1*/
	}

	n = n-sum_n;

	if(flag==0)
	{
		printf("\n\t\t该员工信息不存在！\n");
	}
	write(t);
	return 0;
}

int write(zggz t[])					/*保存职工工资数据函数*/
{
	int i;
	if(n>0) 
	{
		FILE* fp1=fopen("gx.dat","w");
		if (fp1==NULL)
		{   /*若打开文件失败则退出*/

            puts("不能打开文件！");
            return 0;
		}

		for(i=0;i<n;i++)
		{
		    fprintf(fp1, "%s ", t[i].wo_name);
	        fprintf(fp1, "%s ", t[i].id);              
	       	fprintf(fp1, "%f ", t[i].position_value);              
			fprintf(fp1, "%f ", t[i].Pay_salary);              
			fprintf(fp1, "%f ", t[i].duty_allowance);              
			fprintf(fp1, "%f ", t[i].merit_pay);    
			fprintf(fp1, "%f ", t[i].gross_pay); 
			fprintf(fp1, "%f ", t[i].Personal_income_tax);
			fprintf(fp1, "%f \n", t[i].payroll);
		}
		printf("\n\t保存完毕\n");
		fclose(fp1);
	}else
	{
		 printf("\t\n人数为空\n");
	}

    return 0;
}


int find(zggz t[])					/*查询职工工资数据函数*/
{
	char gonghao[10];
	int flag=0; /*标记员工有没有存在*/
	int i=0;	/*记录员工存在的位置*/
	printf("\n\n\t请输入要查询的工号:");
	scanf("%s",gonghao);
	for(i=0;i<n;i++)
	{
		if (strcmp(t[i].id,gonghao)==0)
		{
			flag = 1;
			break;
		}
	}
	
	/*如果存在该员工，那么输出该员工的信息*/
 
	if (flag)
	{    
		
		printf("\n");              
		printf("\t姓名:%s\n", t[i].wo_name);
		printf("\t工号:%s\n", t[i].id);              
		printf("\t岗位工资:%f\n", t[i].position_value);              
		printf("\t薪级工资:%f\n", t[i].Pay_salary);              
		printf("\t职务津贴:%f\n", t[i].duty_allowance);              
		printf("\t绩效工资:%f\n", t[i].merit_pay);    
		printf("\t应发工资:%f\n", t[i].gross_pay); 
		printf("\t个人所得税:%f\n", t[i].Personal_income_tax);
		printf("\t实发工资:%f\n", t[i].payroll);  
		printf("\n\t查询完毕!\n");

	 } 
	 else
	 { 
		 printf("\n\t没有找到该编号的员工！\n"); 
	 }
     
	 printf("\n");
	 system("pause");
     return 0;
}


int list(zggz t[])					/*浏览职工工资数据函数*/
{

	int i;
	int k;
	int flag;
	int j;
	int m=1;
	int asd=n;
	printf("\n");
	printf("\t====================================\n");
    printf("\t|         1. 分批浏览              |\n");
    printf("\t|         2. 全部浏览              |\n");
	printf("\t|         3. Exit the program      |\n");
    printf("\t====================================\n");
	scanf("\t%d",&k);
	do
	{
		flag=0;
		if(k!=1&&k!=2&&k!=3)
		{
			flag=1;
			printf("\t您输入的选择不存在，请重新输入：");
			scanf("\t%d",&k);
		}
	}while(flag);

	if(asd=!0)
	{
		if(k==1)
		{
			printf("\t请输入每次浏览的数量(建议小于10)：");
			scanf("\t%d",&j);
			i=0;
			while(i<n&&m==1)
			{
				printf("\t姓名:%s\n", t[i].wo_name);
				printf("\t工号:%s\n", t[i].id);              
				printf("\t岗位工资:%f\n", t[i].position_value);              
				printf("\t薪级工资:%f\n", t[i].Pay_salary);              
				printf("\t职务津贴:%f\n", t[i].duty_allowance);              
				printf("\t绩效工资:%f\n", t[i].merit_pay);    
				printf("\t应发工资:%f\n", t[i].gross_pay); 
				printf("\t个人所得税:%f\n", t[i].Personal_income_tax);
				printf("\t实发工资:%f\n", t[i].payroll);  
				printf("\n");
				i++;
				if(i%j==0)
				{
					printf("\t继续浏览吗？(0否/1是)");
					scanf("\t%d",&m);
				}
			}
			printf("\n");
			printf("\t工资数据已经浏览完毕！");
			printf("\n");
		}
		if(k==2)
		{
			
			for(i=0;i<n;i++)
			{
				printf("\t姓名:%s\n", t[i].wo_name);
				printf("\t工号:%s\n", t[i].id);              
				printf("\t岗位工资:%f\n", t[i].position_value);              
				printf("\t薪级工资:%f\n", t[i].Pay_salary);              
				printf("\t职务津贴:%f\n", t[i].duty_allowance);              
				printf("\t绩效工资:%f\n", t[i].merit_pay);    
				printf("\t应发工资:%f\n", t[i].gross_pay); 
				printf("\t个人所得税:%f\n", t[i].Personal_income_tax);
				printf("\t实发工资:%f\n", t[i].payroll);  
				printf("\t工资数据已经浏览完毕！");
				printf("\n");
			}
		}
		if(k==3)
		{
			return 0;
		}
	}
	else
	{ 
		printf("\t\t没有员工！\n");  
	}
	return 0;
}


int main()
{
	zggz z[50];
	read(z);
	add_money(z);	//核算工资
	grsds(z);		//核算工资
	add_wages(z);	//核算工资
	printf("\t###  欢迎使用广西民族大学软件与信息安全学院职工工资管理系统  ###\n");

    do{ 
        switch(menu()){
            case 1:
                find(z);	//查询
                break;
            case 2:
                modify(z);	//修改
                break;
            case 3:
                add(z);		//添加
                break;
            case 4:
                del(z);		//删除
                break;
            case 5:
                write(z);	//保存
                break;
            case 6:
                list(z);	//浏览
				break;
            case 7:
                goto exit;
        }
    }while(1);
    exit:
    return 0;
}


