#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct ZGGZ{
	char wo_name[10];//ְ������
	char id[10];//ְ������
	double position_value, Pay_salary;//��λ���ʡ�н������
	double duty_allowance, merit_pay, gross_pay, Personal_income_tax, payroll;//ְ���������Ч���ʡ�Ӧ�����ʡ���������˰��ʵ������
}zggz;//�������ݽṹ��

int count=0;


void add_money(zggz S[])	//�Լ�ģ�� ����Ӧ������       
{
	int i;
	for(i=0;i<count;i++)
		S[i].gross_pay=S[i].position_value+S[i].Pay_salary+S[i].duty_allowance+S[i].merit_pay;
}


void grsds(zggz S[])		//�Լ�ģ�� �����������˰       
{
	int i;
	for(i=0;i<count;i++)
	{
		if(S[i].gross_pay<1500)																									//����С��500ʱ��������˰																											
			S[i].Personal_income_tax=0;
		else if(S[i].gross_pay<4500)																							//���ʴ���500С��2000ʱ��������˰
			S[i].Personal_income_tax=(S[i].gross_pay-1500)*0.1;	
		else if(S[i].gross_pay<9000)																							//���ʴ���2000С��5000ʱ��������˰
			S[i].Personal_income_tax=(S[i].gross_pay-4500)*0.2+3000*0.1;														     			
		else if(S[i].gross_pay<35000)																							//���ʴ���5000С��20000ʱ��������˰
			S[i].Personal_income_tax=(S[i].gross_pay-9000)*0.25+4500*0.2+3000*0.1;														    
		else if(S[i].gross_pay<55000)																							//���ʴ���20000С��40000ʱ��������˰
			S[i].Personal_income_tax=(S[i].gross_pay-35000)*0.3+26000*0.25+4500*0.2+3000*0.1;											     
		else if(S[i].gross_pay<80000)																							//���ʴ���40000С��60000ʱ��������˰
			S[i].Personal_income_tax=(S[i].gross_pay-55000)*0.35+20000*0.3+26000*0.25+4500*0.2+3000*0.1;								     					
		else																												//���ʴ���100000ʱ��������˰
			S[i].Personal_income_tax=(S[i].gross_pay-80000)*0.45+25000*0.35+20000*0.35+20000*0.3+26000*0.25+4500*0.2+3000*0.1;		
	}
}


void add_wages(zggz S[])	//�Լ�ģ�� ����ʵ������	       
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
		{//�����ļ�ʧ�����˳�
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
		count++;       }
		printf("\n��%d��Ա����Ϣ������\n",count);

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
		{
			//�����ļ�ʧ�����˳�
            puts("���ܴ��ļ���");
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
	printf("\n������Ҫ��ѯ�Ĺ���");
	scanf("%s",gonghao);
	printf("%s",t[0].id);
	printf("%s",gonghao);
	//�����ṹ�����飬�������޸ñ�ŵ�Ա�� ����flag=1����֮flag=0
	for(i=0;i<count;i++)
	{
		
		if (*(t[i].id)==*(gonghao))
		{
			printf("%s",t[i].id);
			flag = 1;
			break;
		}
	}
	
 //������ڸ�Ա������ô�����Ա������Ϣ
 if (flag)
 {              
		printf("���\t����\t�Ա�\tְ��\t����\t����\n");              
		printf("%s\t", t[i].wo_name);
		printf("%s\t", t[i].id);              
		printf("%f\t", t[i].position_value);              
		printf("%f\t", t[i].Pay_salary);              
		printf("%f\t", t[i].duty_allowance);              
		printf("%f\t", t[i].merit_pay);    
		printf("%f\t", t[i].gross_pay); 
		printf("%f\t", t[i].Personal_income_tax);
		printf("%f\t", t[i].payroll);   
	 //����Ա���������ж�����һ����Ա����������Ҫ����Ѱ�ң���j�����Ա����λ��  Ȼ�������Ա������Ϣ             
	 //�ڶ���Ѱ�ҵ���ʼλ��Ӧ�ô�i+1��ʼ ��Ϊ֮ǰ���Ѿ��ҹ���
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
 } else{ printf("û���ҵ��ñ�ŵ�Ա����\n"); }
     
 printf("\n");
 system("pause");
 return 0;
}


int list(zggz t[])//���ְ���������ݺ���
{

	int j;
	int asd=count;
	if(asd=!0)
	{
		printf("%d",count);
		
		for(j=0;j<count;j++)
		{
		
		printf("���\t����\t�Ա�\tְ��\t����\t����\n");              
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
	}else{ printf("û��Ա����\n");  }
	return 0;
}


int modify(zggz t[])//�޸�ְ���������ݺ���
{
	
	//double position_value, Pay_salary, duty_allowance, merit_pay, gross_pay, Personal_income_tax,payroll;
	char gonghao[10];
	int flag=0;//���Ա����û�д���
	int i=0;//��¼Ա�����ڵ�λ��
	printf("������Ҫ��ѯ�Ĺ���");
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
		printf("���\t����\t�Ա�\tְ��\t����\t����\n");              
		printf("%s\t", t[i].wo_name);
		printf("%s\t", t[i].id);              
		printf("%f\t", t[i].position_value);              
		printf("%f\t", t[i].Pay_salary);              
		printf("%f\t", t[i].duty_allowance);              
		printf("%f\t", t[i].merit_pay);    
		printf("%f\t", t[i].gross_pay); 
		printf("%f\t", t[i].Personal_income_tax);
		printf("%f\t", t[i].payroll);     
   
			 printf("\n�������޸�position_value");
			 scanf("%lf",&t[i].position_value);
				 
				 printf("%lf\t", t[i].position_value);

			 printf("\n�������޸�Pay_salary");
			 			 scanf("%lf",&t[i].Pay_salary);
				 //t[i].Pay_salary=a.Pay_salary;

			 printf("\n�������޸�duty_allowance");
			 			 scanf("%lf",&t[i].duty_allowance);
				 //t[i].duty_allowance=a.duty_allowance;

			 printf("\n�������޸�merit_pay");
			 			 scanf("%lf",&t[i].merit_pay);
				 //t[i].merit_pay=a.merit_pay;

				 	add_money(t);
					grsds(t);
					add_wages(t);



 } else{ printf("û���ҵ��ñ�ŵ�Ա����\n"); }
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
                find(z);//��ѯ
                break;
            case 2:
                modify(z);//�޸�
                break;
            case 3:
                add();//���
                break;
            case 4:
                del();//ɾ��
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

