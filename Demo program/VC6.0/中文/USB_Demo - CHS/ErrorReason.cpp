#include "stdafx.h"
#include "ErrorReason.h"

void FalseReason(CString s, CString &reason)
{
	if(s == " ") 
	{
		reason = " ";
		return;
	}

	if(s == "00")
    {
        reason = "����ִ�гɹ�.....";
		return;
	}

	if(s == "01")   
    {
        reason = "�������ʧ�� .....";   
		return;
	}

	if(s == "02")   
	{
        reason = "��ַУ����� .....";  
		return;
	}

	if(s == "03")   
	{ 
        reason = "û��ѡ��COM�� .....";
		return;
	}

	if(s == "04")   
	{
		reason = "��д�����س�ʱ .....";  
		return;
	}

	if(s == "05")  
	{
		reason = "���ݰ���ˮ�Ų���ȷ ....."; 
		return;
	}

	if(s == "07")   
	{
        reason = "�����쳣 .....";
		return;
	}

	if(s == "10") 
	{ 
        reason = "����ֵ������Χ .....";  
		return;
	}

	if(s == "80")  
    {
        reason = "�������óɹ� .....";    
		return;
	}
	
	if(s == "81")
	{
	    reason = "��������ʧ�� .....";   
		return;
	}

	if(s == "82") 
	{
        reason = "ͨѶ��ʱ....."; 
		return;
	}

	if(s == "83") 
	{
		reason = "��������.....";   
		return;
    }

	if(s == "84")  
	{
        reason = "���տ����ݳ���.....";
		return;
	}

	if(s == "85") 
	{
		reason = "δ֪�Ĵ���.....";   
		return;
    }

	if(s == "87") 
	{
        reason = "��������������������ʽ����.....";    
		return;
    }

	if(s == "89")  
	{
         reason = "�����ָ����벻����....."; 
		 return;
	}

	if(s == "8A") 
	{
		reason = "�ڶ��ڿ����ʼ�������г��ִ���.....";      
		return;
    } 

	if(s == "8B") 
	{
         reason = "�ڷ���ͻ�����еõ���������к�....."; 
		 return;
    }

	if(s == "8C")
	{
		reason = "������֤ûͨ��.....";  
		return;
    }

	if(s == "8F")
	{
		reason = "�����ָ����벻����.....";  
		return;
    }

	if(s == "90") 
	{
		reason = "����֧���������.....";   
		return;
    }

	if(s == "91")
	{
		reason = "�����ʽ�д���.....";   
		return;
    }

	if(s == "92")  
	{
        reason = "�������FLAG�����У���֧��OPTION ģʽ.....";   
		return;
    }

	if(s == "93")
	{
		reason = "Ҫ������BLOCK������.....";   
		return;
    }

	if(s == "94")
	{
		reason = "Ҫ�����Ķ����Ѿ������������ܽ����޸�.....";  
		return;
    }

	if(s == "95")  
	{
		reason = "�����������ɹ�....."; 
		return;
    }

    if(s == "96")
	{
		reason = "д�������ɹ�.....";   
		return;
	}
}