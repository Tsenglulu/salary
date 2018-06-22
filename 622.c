#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct ZGGZ
{
	char wo_name[10];//ְ������
	char id[10];//ְ������
	double position_value;//��λ����
	double Pay_salary;//н������
	double duty_allowance;//ְ�����
	double merit_pay;//��Ч����
	double gross_pay;//Ӧ������
	double Personal_income_tax;//��������˰
	double payroll;//ʵ������
}zggz;//�������ݽṹ��

int count=0;//Ա���� ȫ�ֱ���

void add_money(zggz S[])	//����Ӧ������       
{
	int i;
	for(i=0;i<count;i++)
		S[i].gross_pay=S[i].position_value+S[i].Pay_salary+S[i].duty_allowance+S[i].merit_pay;
}


void grsds(zggz S[])		//�����������˰       
{
	int i;
	for(i=0;i<count;i++)
	{
		if(S[i].gross_pay<1500)																									//����С��1500ʱ��������˰																											
			S[i].Personal_income_tax=0;
		else if(S[i].gross_pay<4500)																							//���ʴ���1500С��4500ʱ��������˰
			S[i].Personal_income_tax=(S[i].gross_pay-1500)*0.1;	
		else if(S[i].gross_pay<9000)																							//���ʴ���4500С��9000ʱ��������˰
			S[i].Personal_income_tax=(S[i].gross_pay-4500)*0.2+3000*0.1;														     			
		else if(S[i].gross_pay<35000)																							//���ʴ���9000С��35000ʱ��������˰
			S[i].Personal_income_tax=(S[i].gross_pay-9000)*0.25+4500*0.2+3000*0.1;														    
		else if(S[i].gross_pay<55000)																							//���ʴ���35000С��55000ʱ��������˰
			S[i].Personal_income_tax=(S[i].gross_pay-35000)*0.3+26000*0.25+4500*0.2+3000*0.1;											     
		else if(S[i].gross_pay<80000)																							//���ʴ���55000С��80000ʱ��������˰
			S[i].Personal_income_tax=(S[i].gross_pay-55000)*0.35+20000*0.3+26000*0.25+4500*0.2+3000*0.1;								     					
		else																												//���ʴ���80000ʱ��������˰
			S[i].Personal_income_tax=(S[i].gross_pay-80000)*0.45+25000*0.35+20000*0.35+20000*0.3+26000*0.25+4500*0.2+3000*0.1;		
	}
}


void add_wages(zggz S[])	//����ʵ������	       
{
	int i;
	for(i=0;i<count;i++)
		S[i].payroll=S[i].gross_pay-S[i].Personal_income_tax;
}


int read(zggz t[])			//��ȡְ���������ݺ���
{
	zggz T;
	FILE *fp;//�����ļ�ָ��
    if ((fp = fopen("gx.dat", "rb")) == NULL)
	{   //�����ļ�ʧ�����˳�

		puts("���ܴ��ļ���");
        return 0;
	}

	//����ļ��򿪳ɹ�����ô���ж����� 
		
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
		
	printf("\t��%d��Ա����Ϣ������\n",count);
	fclose(fp);
	return count;		
}


int write(zggz t[])				//����ְ���������ݺ���
{
	int i;
	if(count>0) 
	{
		FILE* fp1=fopen("gz.dat","w");
		if (fp1==NULL)
		{   //�����ļ�ʧ�����˳�

            puts("���ܴ��ļ���");
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
		 printf("����Ϊ��");
	}

    return 0;
}


int find(zggz t[])//��ѯְ���������ݺ���
{
	char gonghao[10];
	int flag=0;//���Ա����û�д���
	int j=0;//��¼Ա�����ڵ�λ��
	int i=0;//��¼Ա�����ڵ�λ��
	printf("\n\n������Ҫ��ѯ�Ĺ���:");
	scanf("%s",gonghao);
	for(i=0;i<count;i++)
	{
		if (strcmp(t[i].id,gonghao)==0)
		{
			flag = 1;
			break;
		}
	}
	
	//������ڸ�Ա������ô�����Ա������Ϣ
 
	if (flag)
	{    
		
		printf("\n");              
		printf("\t\t����:%s\n", t[i].wo_name);
		printf("\t\t����:%s\n", t[i].id);              
		printf("\t\t��λ����:%lf\n", t[i].position_value);              
		printf("\t\tн������:%lf\n", t[i].Pay_salary);              
		printf("\t\tְ�����:%lf\n", t[i].duty_allowance);              
		printf("\t\t��Ч����:%lf\n", t[i].merit_pay);    
		printf("\t\tӦ������:%lf\n", t[i].gross_pay); 
		printf("\t\t��������˰:%lf\n", t[i].Personal_income_tax);
		printf("\t\tʵ������:%lf\n", t[i].payroll);   

	 } 
	 else
	 { 
		 printf("û���ҵ��ñ�ŵ�Ա����\n"); 
	 }
     
	printf("\n");
	system("pause");
    return 0;
}


int list(zggz t[])//���ְ���������ݺ���
{

	int i;
	int asd=count;
	if(asd=!0)
	{
			
		for(i=0;i<count;i++)
		{
			
			 
			printf("\t\t����:%s\n", t[i].wo_name);
			printf("\t\t����:%s\n", t[i].id);              
			printf("\t\t��λ����:%lf\n", t[i].position_value);              
			printf("\t\tн������:%lf\n", t[i].Pay_salary);              
			printf("\t\tְ�����:%lf\n", t[i].duty_allowance);              
			printf("\t\t��Ч����:%lf\n", t[i].merit_pay);    
			printf("\t\tӦ������:%lf\n", t[i].gross_pay); 
			printf("\t\t��������˰:%lf\n", t[i].Personal_income_tax);
			printf("\t\tʵ������:%lf\n", t[i].payroll);  
			printf("\n");

		}
	}
	else
	{ 
		printf("û��Ա����\n");  
	}
	return 0;
}


int modify(zggz t[])//�޸�ְ���������ݺ���
{
	char gonghao[10];
	int flag=0;//���Ա����û�д���
	int i=0;//��¼Ա�����ڵ�λ��
	printf("\n\n������Ҫ�޸ĵĹ���");
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
			printf("\n��Ҫ�޸ĵ��������£�\n");           
			printf("\t\t����:%s\n", t[i].wo_name);
			printf("\t\t����:%s\n", t[i].id);              
			printf("\t\t��λ����:%lf\n", t[i].position_value);              
			printf("\t\tн������:%lf\n", t[i].Pay_salary);              
			printf("\t\tְ�����:%lf\n", t[i].duty_allowance);              
			printf("\t\t��Ч����:%lf\n", t[i].merit_pay);    
			printf("\t\tӦ������:%lf\n", t[i].gross_pay); 
			printf("\t\t��������˰:%lf\n", t[i].Personal_income_tax);
			printf("\t\tʵ������:%lf\n", t[i].payroll);
			printf("\n");
   
				printf("\n�������޸ĺ��position_value��");
				scanf("%f",&t[i].position_value);
				 
				printf("\n�������޸ĺ��Pay_salary��");
			 	scanf("%f",&t[i].Pay_salary);

				printf("\n�������޸ĺ��duty_allowance��");
			 	scanf("%f",&t[i].duty_allowance);


				printf("\n�������޸ĺ��merit_pay��");
			 	scanf("%f",&t[i].merit_pay);
				
					add_money(t);
					grsds(t);
					add_wages(t);

	} 
	else
	{ 
		printf("û���ҵ��ñ�ŵ�Ա����\n"); 
	}
	return 0;
}


int add(zggz t[])
{
	if (count>50)
	{
		printf("Ա����Ϣ������\n");
        return 0;
	} 
	else
	{
        printf("\n");

		printf("\n������Ա���ı�ţ�");
        scanf("%s", t[count].id);
			  		 
        printf("\n������Ա����������");
		scanf("%s",t[count].wo_name);

		printf("\n������Ա����position_value��");
		scanf("%lf",&t[count].position_value);

		printf("\n������Ա����Pay_salary��");
		scanf("%lf",&t[count].Pay_salary);
		
		printf("\n������Ա����duty_allowance��");
		scanf("%lf", &t[count].duty_allowance);
		
		printf("\n������Ա����merit_pay��");
		scanf("%lf", &t[count].merit_pay);
	
		count++;//count���1

			add_money(t);
			grsds(t);
			add_wages(t);

				printf("\nԱ����Ϣ�Ѿ����\n\n");

    }
	return 0;
}

int del(zggz t[])
{
	char gonghao[10];//�洢��Ҫɾ����Ա�����
	int flag=0;//�����û�и�Ա��
	int sum_count=0;//������¼ɾ���˼���Ա����Ϣ
	int i=0;
	int j=0;
	printf("\n������Ҫɾ��Ա���ı�ţ�");
	scanf("%s",gonghao);

	for(i=0;i<=count;i++)
	{
		if(strcmp(t[i].id,gonghao)==0)
		{//�ҵ�����Ҫɾ����Ա�����
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
				
			printf("\n��Ա����Ϣ�Ѿ�ɾ��\n");
			sum_count++;//ɾ����һ��Ա���ͼ�һ
	}

	count = count-sum_count;

	if(flag==1)
	{
		printf("\n��Ա����Ϣ�Ѿ�ɾ��\n");
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
                find(z);//��ѯ
                break;
            case 2:
                modify(z);//�޸�
                break;
            case 3:
                add(z);//���
                break;
            case 4:
                del(z);//ɾ��
                break;
            case 5:
                write(z);//����
                break;
            case 6:
                list(z);//���
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
    printf("     1. ��ѯְ���������ݺ���\n");
    printf("     2. �޸�ְ���������ݺ���\n");
    printf("     3. ���ְ���������ݺ���\n");
    printf("     4. ɾ��ְ���������ݺ���\n");
    printf("     5. ����ְ���������ݺ���\n");
    printf("     6. ���ְ���������ݺ���\n");
	printf("     7. Exit the program\n");
    printf("***********************************\n");
	printf("\t����ѡ��(1-7):");
    scanf("%c",&i);
    option=(int)(i-'0');
    while(option<1||option>7){
        printf("Input Error!\nPlease retype:\n");
        scanf("%d",&option);
    }
    return option;
}

