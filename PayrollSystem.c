/***********************************************************

  Copyright (C), 2017-2018
  FileName:PayrollSystem.c
  Author:֣·�		Date:2018/6/26
  Function List: 
	add_money() ����Ӧ������
	grsds()		�����������˰ 
	add_wages()	����ʵ������
	read()		��ȡְ���������ݺ���
	write()		����ְ���������ݺ���
	find()		��ѯְ���������ݺ���
	list()		���ְ���������ݺ���
	modify()	�޸�ְ���������ݺ���
	add()		���ְ���������ݺ���
	del()		ɾ��ְ���������ݺ���
	menu()		�˵�����

***********************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct ZGGZ
{
	char wo_name[10];			/*ְ������*/
	char id[10];				/*ְ������*/
	double position_value;		/*��λ����*/
	double Pay_salary;			/*н������*/
	double duty_allowance;		/*ְ�����*/
	double merit_pay;			/*��Ч����*/
	double gross_pay;			/*Ӧ������*/
	double Personal_income_tax;	/*��������˰*/
	double payroll;				/*ʵ������*/
}zggz;

int count=0;	/*Ա���� ȫ�ֱ���*/

int menu()
{
   int option=0;
    char i=0;
	printf("\n\n\t��ѡ��<1 - 7>:\n");
    printf("\t================================================================\n");
    printf("\t|         1. ��ѯְ���������ݺ���                              |\n");
    printf("\t|         2. �޸�ְ���������ݺ���                              |\n");
    printf("\t|         3. ���ְ���������ݺ���                              |\n");
    printf("\t|         4. ɾ��ְ���������ݺ���                              |\n");
    printf("\t|         5. ����ְ���������ݺ���                              |\n");
    printf("\t|         6. ���ְ���������ݺ���                              |\n");
	printf("\t|         7. Exit the program                                  |\n");
    printf("\t================================================================\n");
	printf("\n\t���ѡ���ǣ�");
    scanf("%c",&i);
    option=(int)(i-'0');
    while(option<1||option>7){
        printf("Input Error!Please retype:");
        scanf("%d",&option);
    }
    return option;
}


void add_money(zggz S[])			/*����Ӧ������*/       
{
	int i;
	for(i=0;i<count;i++)
		S[i].gross_pay=S[i].position_value+S[i].Pay_salary+S[i].duty_allowance+S[i].merit_pay;
}


void grsds(zggz S[])				/*�����������˰*/       
{
	int i;
	for(i=0;i<count;i++)
	{
		if(S[i].gross_pay<500)																									//����С��500ʱ��������˰																											
			S[i].Personal_income_tax=S[i].gross_pay*0.05;
		else if(S[i].gross_pay<2000)																							//���ʴ���500С��2000ʱ��������˰
			S[i].Personal_income_tax=(S[i].gross_pay-500)*0.1+
									 500*0.05;
		else if(S[i].gross_pay<5000)																							//���ʴ���2000С��5000ʱ��������˰
			S[i].Personal_income_tax=(S[i].gross_pay-2000)*0.15+
									 1500*0.1+500*0.05;	
		else if(S[i].gross_pay<20000)																							//���ʴ���5000С��20000ʱ��������˰
			S[i].Personal_income_tax=(S[i].gross_pay-5000)*0.2+
									 3000*0.15+1500*0.1+500*0.05;															     			
		else if(S[i].gross_pay<40000)																							//���ʴ���20000С��40000ʱ��������˰
			S[i].Personal_income_tax=(S[i].gross_pay-20000)*0.25+
									 15000*0.2+3000*0.15+1500*0.1+500*0.05;															    
		else if(S[i].gross_pay<60000)																							//���ʴ���40000С��60000ʱ��������˰
			S[i].Personal_income_tax=(S[i].gross_pay-40000)*0.3+
									 20000*0.25+15000*0.2+3000*0.15+1500*0.1+500*0.05;											     
		else if(S[i].gross_pay<80000)																							//���ʴ���60000С��80000ʱ��������˰
			S[i].Personal_income_tax=(S[i].gross_pay-60000)*0.35+
									 20000*0.3+20000*0.25+15000*0.2+3000*0.15+1500*0.1+500*0.05;								     					
	else if(S[i].gross_pay<100000)																							    //���ʴ���80000С��100000ʱ��������˰
			S[i].Personal_income_tax=(S[i].gross_pay-80000)*0.4+
									 20000*0.35+20000*0.3+20000*0.25+15000*0.2+3000*0.15+1500*0.1+500*0.05;				
		else																													//���ʴ���100000ʱ��������˰
			S[i].Personal_income_tax=(S[i].gross_pay-100000)*0.45+
									 20000*0.4+20000*0.35+20000*0.3+20000*0.25+15000*0.2+3000*0.15+1500*0.1+500*0.05;		
	}
}


void add_wages(zggz S[])			/*����ʵ������*/	       
{
	int i;
	for(i=0;i<count;i++)
		S[i].payroll=S[i].gross_pay-S[i].Personal_income_tax;
}


int read(zggz t[])					/*��ȡְ���������ݺ���*/
{
	zggz T;
	FILE *fp;/*�����ļ�ָ��*/
    if ((fp = fopen("gx.dat", "rb")) == NULL)
	{		 /*�����ļ�ʧ�����˳�*/

		puts("���ܴ��ļ���");
        return 0;
	}

	/*����ļ��򿪳ɹ�����ô���ж�����*/ 
		
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
		
	printf("\n\n");
	fclose(fp);
	return count;		
}


int modify(zggz t[])				/*�޸�ְ���������ݺ���*/
{
	char gonghao[10];
	int flag=0; /*���Ա����û�д���*/
	int i=0;	/*��¼Ա�����ڵ�λ��*/
	printf("\n\n\t������Ҫ�޸ĵĹ���:");
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
			printf("\n\t��Ҫ�޸ĵ��������£�\n");           
			printf("\t����:%s\n", t[i].wo_name);
			printf("\t����:%s\n", t[i].id);              
			printf("\t��λ����:%lf\n", t[i].position_value);              
			printf("\tн������:%lf\n", t[i].Pay_salary);              
			printf("\tְ�����:%lf\n", t[i].duty_allowance);              
			printf("\t��Ч����:%lf\n", t[i].merit_pay);    
			printf("\tӦ������:%lf\n", t[i].gross_pay); 
			printf("\t��������˰:%lf\n", t[i].Personal_income_tax);
			printf("\tʵ������:%lf\n", t[i].payroll);
			printf("\n");
   
			printf("\n\t�������޸ĺ��position_value��");
				scanf("%lf",&t[i].position_value);
			printf("\n\t�������޸ĺ��Pay_salary��");
				scanf("%lf",&t[i].Pay_salary);
			printf("\n\t�������޸ĺ��duty_allowance��");
				scanf("%lf",&t[i].duty_allowance);
			printf("\n\t�������޸ĺ��merit_pay��");
				scanf("%lf",&t[i].merit_pay);
				
			add_money(t);
			grsds(t);
			add_wages(t);
			printf("\n\t�޸���ϣ��޸ĺ������£�\n\n");

			printf("\t����:%s\n", t[i].wo_name);
			printf("\t����:%s\n", t[i].id);              
			printf("\t��λ����:%lf\n", t[i].position_value);              
			printf("\tн������:%lf\n", t[i].Pay_salary);              
			printf("\tְ�����:%lf\n", t[i].duty_allowance);              
			printf("\t��Ч����:%lf\n", t[i].merit_pay);    
			printf("\tӦ������:%lf\n", t[i].gross_pay); 
			printf("\t��������˰:%lf\n", t[i].Personal_income_tax);
			printf("\tʵ������:%lf\n", t[i].payroll);

			write(t);

	} 
	else
	{ 
		printf("\n\tû���ҵ��ñ�ŵ�Ա����\n"); 
	}
	return 0;
}


int add(zggz t[])				/*����ְ���������ݺ���*/
{
	int flag;
	int j;
	if (count>55)
	{
		printf("\tԱ����Ϣ������\n");
        return 0;
	} 
	else
	{
        printf("\n");
		printf("\n\t�밴��������ӵĹ���:");

		do{
			flag=0;
			scanf("%s", t[count].id);
			for(j=0;j<count;j++)
				if(strcmp(t[count].id,t[j].id)==0)
				{
					printf("\n\t�����Ѿ����ڣ�����������:");
					flag=1;
					break;
				}
			
		}while(flag==1);
			  		 
        printf("\n\t������Ҫ��ӵ�Ա����������");
			scanf("%s",t[count].wo_name);
		printf("\n\t������Ҫ��ӵ�Ա����position_value��");
			scanf("%lf",&t[count].position_value);
			
		printf("\n\t������Ҫ��ӵ�Ա����Pay_salary��");
			scanf("%lf",&t[count].Pay_salary);
		printf("\n\t������Ҫ��ӵ�Ա����duty_allowance��");
			scanf("%lf",&t[count].duty_allowance);
		printf("\n\t������Ҫ��ӵ�Ա����merit_pay��");
			scanf("%lf",&t[count].merit_pay);
		
		count++;//count���1
		add_money(t);
		grsds(t);
		add_wages(t);
		write(t);
		printf("\n\tԱ����Ϣ�Ѿ����\n\n");

    }
	return 0;
}

int del(zggz t[])					/*ɾ��ְ���������ݺ���*/
{
	char gonghao[10];/*�洢��Ҫɾ����Ա�����*/
	int flag=0;		 /*�����û�и�Ա��*/
	int sum_count=0; /*������¼ɾ���˼���Ա����Ϣ*/
	int i=0;
	int j=0;
	printf("\n\t������Ҫɾ��Ա���ı�ţ�");
	scanf("%s",gonghao);

	for(i=0;i<=count;i++)
	{
		if(strcmp(t[i].id,gonghao)==0)
		{ /*�ҵ�����Ҫɾ����Ա�����*/
			flag=1;
			break;				  
		}
	}	

	if(flag==1)
	{
		for(j=i;j<count;j++)
		{
			t[j]=t[j+1];
		}
				
			printf("\n\t��Ա���ѱ�ɾ���ɹ���\n");
			sum_count++;/*ɾ����һ��Ա����+1*/
	}

	count = count-sum_count;

	if(flag==0)
	{
		printf("\n\t\t��Ա����Ϣ�����ڣ�\n");
	}
	write(t);
	return 0;
}

int write(zggz t[])					/*����ְ���������ݺ���*/
{
	int i;
	if(count>0) 
	{
		FILE* fp1=fopen("gz.dat","w");
		if (fp1==NULL)
		{   /*�����ļ�ʧ�����˳�*/

            puts("���ܴ��ļ���");
            return 0;
		}

		for(i=0;i<count;i++)
		{
		    fprintf(fp1, "%s ", t[i].wo_name);
	        fprintf(fp1, "%s ", t[i].id);              
	       	fprintf(fp1, "%lf ", t[i].position_value);              
			fprintf(fp1, "%lf ", t[i].Pay_salary);              
			fprintf(fp1, "%lf ", t[i].duty_allowance);              
			fprintf(fp1, "%lf ", t[i].merit_pay);    
			fprintf(fp1, "%lf ", t[i].gross_pay); 
			fprintf(fp1, "%lf ", t[i].Personal_income_tax);
			fprintf(fp1, "%lf \n", t[i].payroll);
		}
		printf("\n\t�������\n");
		fclose(fp1);
	}else
	{
		 printf("\t\n����Ϊ��\n");
	}

    return 0;
}


int find(zggz t[])					/*��ѯְ���������ݺ���*/
{
	char gonghao[10];
	int flag=0; /*���Ա����û�д���*/
	int i=0;	/*��¼Ա�����ڵ�λ��*/
	printf("\n\n\t������Ҫ��ѯ�Ĺ���:");
	scanf("%s",gonghao);
	for(i=0;i<count;i++)
	{
		if (strcmp(t[i].id,gonghao)==0)
		{
			flag = 1;
			break;
		}
	}
	
	/*������ڸ�Ա������ô�����Ա������Ϣ*/
 
	if (flag)
	{    
		
		printf("\n");              
		printf("\t����:%s\n", t[i].wo_name);
		printf("\t����:%s\n", t[i].id);              
		printf("\t��λ����:%lf\n", t[i].position_value);              
		printf("\tн������:%lf\n", t[i].Pay_salary);              
		printf("\tְ�����:%lf\n", t[i].duty_allowance);              
		printf("\t��Ч����:%lf\n", t[i].merit_pay);    
		printf("\tӦ������:%lf\n", t[i].gross_pay); 
		printf("\t��������˰:%lf\n", t[i].Personal_income_tax);
		printf("\tʵ������:%lf\n", t[i].payroll);  
		printf("\n\t��ѯ���!\n");

	 } 
	 else
	 { 
		 printf("\n\tû���ҵ��ñ�ŵ�Ա����\n"); 
	 }
     
	 printf("\n");
	 system("pause");
     return 0;
}


int list(zggz t[])					/*���ְ���������ݺ���*/
{

	int i;
	int n;
	int flag;
	int j;
	int m=1;
	int asd=count;
	printf("\n");
	printf("\t====================================\n");
    printf("\t|         1. �������              |\n");
    printf("\t|         2. ȫ�����              |\n");
	printf("\t|         3. Exit the program      |\n");
    printf("\t====================================\n");
	scanf("\t%d",&n);
	do
	{
		flag=0;
		if(n!=1&&n!=2&&n!=3)
		{
			flag=1;
			printf("\t�������ѡ�񲻴��ڣ����������룺");
			scanf("\t%d",&n);
		}
	}while(flag);

	if(asd=!0)
	{
		if(n==1)
		{
			printf("\t������ÿ�����������(����С��10)��");
			scanf("\t%d",&j);
			i=0;
			while(i<count&&m==1)
			{
				printf("\t����:%s\n", t[i].wo_name);
				printf("\t����:%s\n", t[i].id);              
				printf("\t��λ����:%lf\n", t[i].position_value);              
				printf("\tн������:%lf\n", t[i].Pay_salary);              
				printf("\tְ�����:%lf\n", t[i].duty_allowance);              
				printf("\t��Ч����:%lf\n", t[i].merit_pay);    
				printf("\tӦ������:%lf\n", t[i].gross_pay); 
				printf("\t��������˰:%lf\n", t[i].Personal_income_tax);
				printf("\tʵ������:%lf\n", t[i].payroll);  
				printf("\n");
				i++;
				if(i%j==0)
				{
					printf("\t���������(0��/1��)");
					scanf("\t%d",&m);
				}
			}
			printf("\n");
			printf("\t���������Ѿ������ϣ�");
			printf("\n");
		}
		if(n==2)
		{
			
			for(i=0;i<count;i++)
			{
				printf("\t����:%s\n", t[i].wo_name);
				printf("\t����:%s\n", t[i].id);              
				printf("\t��λ����:%lf\n", t[i].position_value);              
				printf("\tн������:%lf\n", t[i].Pay_salary);              
				printf("\tְ�����:%lf\n", t[i].duty_allowance);              
				printf("\t��Ч����:%lf\n", t[i].merit_pay);    
				printf("\tӦ������:%lf\n", t[i].gross_pay); 
				printf("\t��������˰:%lf\n", t[i].Personal_income_tax);
				printf("\tʵ������:%lf\n", t[i].payroll);  
				printf("\t���������Ѿ������ϣ�");
				printf("\n");
			}
		}
		if(n==3)
		{
			return 0;
		}
	}
	else
	{ 
		printf("\t\tû��Ա����\n");  
	}
	return 0;
}


int main()
{
	zggz z[50];
	read(z);
	add_money(z);	//���㹤��
	grsds(z);		//���㹤��
	add_wages(z);	//���㹤��
	printf("\t###  ��ӭʹ�ù��������ѧ�������Ϣ��ȫѧԺְ�����ʹ���ϵͳ  ###\n");

    do{ 
        switch(menu()){
            case 1:
                find(z);	//��ѯ
                break;
            case 2:
                modify(z);	//�޸�
                break;
            case 3:
                add(z);		//���
                break;
            case 4:
                del(z);		//ɾ��
                break;
            case 5:
                write(z);	//����
                break;
            case 6:
                list(z);	//���
				break;
            case 7:
                goto exit;
        }
    }while(1);
    exit:
    return 0;
}


