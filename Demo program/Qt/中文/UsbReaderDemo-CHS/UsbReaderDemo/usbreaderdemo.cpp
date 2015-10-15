#include "usbreaderdemo.h"

UsbReaderDemo::UsbReaderDemo(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	cardReader = new Reader(this);
}

QString UsbReaderDemo::formatStr(QString str)
{
	QRegExp regExp("[^a-fA-F0-9]");
	return str.replace(regExp,"");
}

void UsbReaderDemo::showStatue(QPlainTextEdit *text, int Code)
{
	QString msg;
	switch (Code)
	{
	case 0x00:
		msg = QString::fromLocal8Bit("����ִ�гɹ� .....");
		break;
	case 0x01:
		msg = QString::fromLocal8Bit("�������ʧ�� .....");
		break;
	case 0x02:
		msg = QString::fromLocal8Bit("��ַУ����� .....");
		break;
	case 0x03:
		msg = QString::fromLocal8Bit("û��ѡ��COM�� .....");
		break;
	case 0x04:
		msg = QString::fromLocal8Bit("��д�����س�ʱ .....");
		break;
	case 0x05:
		msg = QString::fromLocal8Bit("���ݰ���ˮ�Ų���ȷ .....");
		break;
	case 0x07:
		msg = QString::fromLocal8Bit("�����쳣 .....");
		break;
	case 0x0A:
		msg = QString::fromLocal8Bit("����ֵ������Χ .....");
		break;
	case 0x80:
		msg = QString::fromLocal8Bit("�������óɹ� .....");
		break;
	case 0x81:
		msg = QString::fromLocal8Bit("��������ʧ�� .....");
		break;
	case 0x82:
		msg = QString::fromLocal8Bit("ͨѶ��ʱ.....");
		break;
	case 0x83:
		msg = QString::fromLocal8Bit("��������.....");
		break;
	case 0x84:
		msg = QString::fromLocal8Bit("���տ����ݳ���.....");
		break;
	case 0x85:
		msg = QString::fromLocal8Bit("δ֪�Ĵ���.....");
		break;
	case 0x87:
		msg = QString::fromLocal8Bit("��������������������ʽ����.....");
		break;
	case 0x89:
		msg = QString::fromLocal8Bit("�����ָ����벻����.....");
		break;
	case 0x8A:
		msg = QString::fromLocal8Bit("�ڶ��ڿ����ʼ�������г��ִ���.....");
		break;
	case 0x8B:
		msg = QString::fromLocal8Bit("�ڷ���ͻ�����еõ���������к�.....");
		break;
	case 0x8C:
		msg = QString::fromLocal8Bit("������֤ûͨ��.....");
		break;
	case 0x8F:
		msg = QString::fromLocal8Bit("�����ָ����벻����.....");
		break;
	case 0x90:
		msg = QString::fromLocal8Bit("����֧���������.....");
		break;
	case 0x91:
		msg = QString::fromLocal8Bit("�����ʽ�д���.....");
		break;
	case 0x92:
		msg = QString::fromLocal8Bit("�������FLAG�����У���֧��OPTION ģʽ.....");
		break;
	case 0x93:
		msg = QString::fromLocal8Bit("Ҫ������BLOCK������.....");
		break;
	case 0x94:
		msg = QString::fromLocal8Bit("Ҫ�����Ķ����Ѿ������������ܽ����޸�.....");
		break;
	case 0x95:
		msg = QString::fromLocal8Bit("�����������ɹ�.....");
		break;
	case 0x96:
		msg = QString::fromLocal8Bit("д�������ɹ�.....");
		break;
	}
	text->appendPlainText(msg);
}

void UsbReaderDemo::convertStr(unsigned char *after, QString before, int length)
{
	for(int i=0;i<length;i++)
	{
		after[i] = before.mid(2*i,2).toInt(0,16);
	}
}

void UsbReaderDemo::showData(QPlainTextEdit *text, unsigned char *data, int position, int length)
{
	QString msg = "";
	for(int i=0;i<length;i++)
	{
		msg += QString("%1").arg(int(data[position+i]), 2, 16, QChar('0')).toUpper() + ' ';
	}
	text->appendPlainText(msg);
}

void UsbReaderDemo::showData(QPlainTextEdit *text,char *data, int position, int length)
{
	for(int i=0;i<length;i++)
	{
		if(data[position+i]<0)
			data[position+i] += 256;
	}
	showData(text, (unsigned char*)data, position, length);
}

//System Setting
void UsbReaderDemo::on_setsernumButton_clicked()
{
	unsigned char buffer;
	unsigned char newValue[8] = {0};
	QString serNum = formatStr(ui.sernumEdit->text());
	convertStr(newValue,serNum,8);
	int result = cardReader->SetSerNum(newValue,&buffer);
	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text, result);
	showStatue(text, buffer);
	text->appendPlainText(""); //new line
}

void UsbReaderDemo::on_readsernumButton_clicked()
{
	unsigned char buffer[9] = {0};
	int result = cardReader->GetSerNum(buffer);
	QPlainTextEdit *text = ui.dataEdit;	//There is a bug. You must do it like this.
	showStatue(text, result);
	showData(text,buffer,1,8);
	text->appendPlainText(""); //new line
}

void UsbReaderDemo::on_setledButton_clicked()
{
	int freq = ui.ledcycleEdit->text().toInt();
	int duration = ui.ledtimesEdit->text().toInt();
	unsigned char buffer;
	int result = cardReader->ControlLED(freq, duration, &buffer);
	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text, result);
	showStatue(text, buffer);
	text->appendPlainText(""); //new line
}

void UsbReaderDemo::on_setbuzzerButton_clicked()
{
	int freq = ui.bzrcycleEdit->text().toInt();
	int duration = ui.bzrtimesEdit->text().toInt();
	unsigned char buffer;
	int result = cardReader->ControlBuzzer(freq, duration, &buffer);
	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text, result);
	showStatue(text, buffer);
	text->appendPlainText(""); //new line
}

void UsbReaderDemo::on_getverButton_clicked()
{
	char VersionNum[11] = {0};	//version number
	int result = cardReader->GetVersionNum(VersionNum);
	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text, result);
	if (result == 0)
		showData(text,VersionNum, 1, 11);
	else
		showStatue(text, VersionNum[0]);
	text->appendPlainText(""); //new line
}

////14443A-MF
void UsbReaderDemo::on_mfRead_clicked()
{
	unsigned char mode1 = ui.readKeyB->isChecked();
	unsigned char mode2 = ui.readAll->isChecked();
	unsigned char mode = (mode1<<1) | mode2;	//reading model
	unsigned char blk_add = ui.readStart->currentText().toInt(0,16);	//block address
	unsigned char num_blk = ui.readNum->currentText().toInt(0,16);	//block number
    unsigned char snr[6];	//key
	QString snrStr = formatStr(ui.readKey->currentText());	//format the string
	convertStr(snr, snrStr, 6);	//conert to unsigned char
	unsigned char *buffer = new unsigned char[16*num_blk];	//data read
	
	int result = cardReader->MF_Read(mode,blk_add,num_blk,snr,buffer);

	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text, result);
	if (result == 0)
	{
		text->appendPlainText(QString::fromLocal8Bit("����:"));
		showData(text,snr,0,4);
		text->appendPlainText(QString::fromLocal8Bit("����������:"));
		showData(text,buffer,0,16*num_blk);
	}
	else
		showStatue(text, buffer[0]);
	text->appendPlainText(""); //new line
}

void UsbReaderDemo::on_mfWrite_clicked()
{
	unsigned char mode1 = ui.writeKeyB->isChecked();
	unsigned char mode2 = ui.writeAll->isChecked();
	unsigned char mode = (mode1<<1) | mode2;	//writing model
	unsigned char blk_add = ui.writeStart->currentText().toInt(0,16);	//block address
	unsigned char num_blk = ui.writeNum->currentText().toInt(0,16);	//block number
    unsigned char snr[6];	//key
	QString snrStr = formatStr(ui.writeKey->currentText());	//format the string
	convertStr(snr, snrStr, 6);	//conert to unsigned char
	unsigned char *buffer = new unsigned char[16*num_blk];	//data write
	QString bufferStr = formatStr(ui.writeData->text());
	convertStr(buffer,bufferStr,16*num_blk);
	
	int result = cardReader->MF_Write(mode,blk_add,num_blk,snr,buffer);

	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text, result);
	if (result == 0)
	{
		text->appendPlainText(QString::fromLocal8Bit("����:"));
		showData(text,snr,0,4);
	}
	else
		showStatue(text, buffer[0]);
	text->appendPlainText(""); //new line
}

void UsbReaderDemo::on_mfInit_clicked()
{
	unsigned char mode1 = ui.initKeyB->isChecked();
	unsigned char mode2 = ui.initAll->isChecked();
	unsigned char mode = (mode1<<1) | mode2;	//reading model
	unsigned char SectNum = ui.initSector->text().toInt(0,16); //sector 
    unsigned char snr[6];	//key
	QString snrStr = formatStr(ui.initKey->text());	//format the string
	convertStr(snr, snrStr, 6);	//conert to unsigned char
	unsigned char value[4];	//initialize value
	QString valueStr = formatStr(ui.initValue->text());	//format the string
	convertStr(value, valueStr, 4);	//conert to unsigned char
	
	int result = cardReader->MF_InitValue(mode, SectNum, snr, value);

	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text, result);
	if (result == 0)
	{
		text->appendPlainText(QString::fromLocal8Bit("����:"));
		showData(text,snr,0,4);
	}
	else
		showStatue(text, snr[0]);
	text->appendPlainText(""); //new line
}

void UsbReaderDemo::on_mfDeval_clicked()
{
	unsigned char mode1 = ui.decKeyB->isChecked();
	unsigned char mode2 = ui.decAll->isChecked();
	unsigned char mode = (mode1<<1) | mode2;	//reading model
	unsigned char SectNum = ui.decSector->text().toInt(0,16); //sector 
    unsigned char snr[6];	//key
	QString snrStr = formatStr(ui.decKey->text());	//format the string
	convertStr(snr, snrStr, 6);	//conert to unsigned char
	unsigned char value[4];	//initialize value
	QString valueStr = formatStr(ui.decValue->text());	//format the string
	convertStr(value, valueStr, 4);	//conert to unsigned char
	
	int result = cardReader->MF_Dec(mode, SectNum, snr, value);

	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text, result);
	if (result == 0)
	{
		text->appendPlainText(QString::fromLocal8Bit("����:"));
		showData(text,snr,0,4);
	}
	else
		showStatue(text, snr[0]);
	text->appendPlainText(""); //new line
}

void UsbReaderDemo::on_mfInval_clicked()
{
	unsigned char mode1 = ui.incKeyB->isChecked();
	unsigned char mode2 = ui.incAll->isChecked();
	unsigned char mode = (mode1<<1) | mode2;	//reading model
	unsigned char SectNum = ui.incSector->text().toInt(0,16); //sector 
    unsigned char snr[6];	//key
	QString snrStr = formatStr(ui.incKey->text());	//format the string
	convertStr(snr, snrStr, 6);	//conert to unsigned char
	unsigned char value[4];	//initialize value
	QString valueStr = formatStr(ui.incValue->text());	//format the string
	convertStr(value, valueStr, 4);	//conert to unsigned char
	
	int result = cardReader->MF_Inc(mode, SectNum, snr, value);

	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text, result);
	if (result == 0)
	{
		text->appendPlainText(QString::fromLocal8Bit("����:"));
		showData(text,snr,0,4);
	}
	else
		showStatue(text, snr[0]);
	text->appendPlainText(""); //new line
}

void UsbReaderDemo::on_mfCardNum_clicked()
{
	unsigned char mode;
	if (ui.snrAll->isChecked())
		mode = 0x52;
	else
		mode = 0x26;
	unsigned char halt = ui.snrHalt->isChecked();
    unsigned char snr;
	unsigned char value[4];	//card number
	QString valueStr = formatStr(ui.incValue->text());	//format the string
	convertStr(value, valueStr, 4);	//conert to unsigned char
	
	int result = cardReader->MF_Getsnr(mode, halt, &snr, value);

	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text, result);
	if (result == 0)
	{
		if (snr==0x00)
			text->appendPlainText(QString::fromLocal8Bit("ֻ��һ�ſ�....."));
		else
			text->appendPlainText(QString::fromLocal8Bit("�ж��ſ�......"));
		text->appendPlainText(QString::fromLocal8Bit("����:"));
		showData(text,value,0,4);
	}
	else
		showStatue(text, snr);
	text->appendPlainText(""); //new line
}

//Ultralight
void UsbReaderDemo::on_utsnRead_clicked()
{
	unsigned char snr[7];
	unsigned char mode = ui.utsnAll->isChecked();
	int result = cardReader->UL_Request(mode, snr);
	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text, result);
	if (result == 0)
	{
		text->appendPlainText(QString::fromLocal8Bit("����:"));
		showData(text,snr,0,7);
	}
	else
		showStatue(text, snr[0]);
	text->appendPlainText(""); //new line
}

void UsbReaderDemo::on_utHalt_clicked()
{
	int result = cardReader->MF_Halt();
	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text,result);
	text->appendPlainText(""); //new line
}

void UsbReaderDemo::on_utblockRead_clicked()
{
	unsigned char mode = ui.utreadAll->isChecked();
	unsigned char blk_add = ui.utreadBlock->currentItem()->text().toInt();
	unsigned char snr[7];
	unsigned char buffer[16];
	int result = cardReader->UL_HLRead(mode,blk_add,snr,buffer);
	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text, result);
	if (result == 0)
	{
		text->appendPlainText(QString::fromLocal8Bit("����:"));
		showData(text,snr,0,7);
		text->appendPlainText(QString::fromLocal8Bit("����������:"));
		showData(text,buffer,0,16);
	}
	else
		showStatue(text,buffer[0]);
	text->appendPlainText(""); //new line
}

void UsbReaderDemo::on_utwriteWrite_clicked()
{
	unsigned char mode = ui.utwriteAll->isChecked();
	unsigned char blk_add = ui.utwriteBlock->currentItem()->text().toInt();
	unsigned char snr[7]={0};
	unsigned char buffer[4];
	QString bufferStr = formatStr(ui.utwriteData->text());
	convertStr(buffer, bufferStr, 4);
	int result = cardReader->UL_HLWrite(mode,blk_add,snr,buffer);
	QPlainTextEdit *text = ui.dataEdit;
	if (result == 0)
	{
		showStatue(text, result);
		text->appendPlainText(QString::fromLocal8Bit("����:"));
		showData(text,snr,0,7);
	}
	else
		if (result == 10)
		{
			text->appendPlainText(QString::fromLocal8Bit("����....."));
			showStatue(text, result);	
		}// something different
		else
			showStatue(text,snr[0]);
	text->appendPlainText(""); //new line
}

//14443B
void UsbReaderDemo::on_BRequest_clicked()
{
	unsigned char buffer[256];
	int result = cardReader->TypeB_Request(buffer);
	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text, result);
	if(result == 0)
	{
		text->appendPlainText(QString::fromLocal8Bit("���������ݳ���:"));
		showData(text,buffer,0,1);
		text->appendPlainText(QString::fromLocal8Bit("����������:"));
		showData(text,buffer,1,buffer[0]);
	}
	else
		showStatue(text,buffer[0]);
	text->appendPlainText(""); //new line
}

void UsbReaderDemo::on_BTransfer_clicked()
{
	int cmdSize = ui.Blength->text().toInt(0,16);
	unsigned char buffer[256];
	unsigned char *cmd = new unsigned char[cmdSize];
	QString cmdStr = formatStr(ui.BData->text());
	convertStr(cmd, cmdStr, cmdSize);
	int result = cardReader->TypeB_TransCOS(cmd, cmdSize,buffer);
	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text, result);
	if(result == 0)
	{
		text->appendPlainText(QString::fromLocal8Bit("����������:"));
		showData(text,buffer,0,8);
	}
	else
		showStatue(text, buffer[0]);
	text->appendPlainText(""); //new line
}

void UsbReaderDemo::on_BUid_clicked()
{
	unsigned char mode = 0x26;
	unsigned char halt = 0x00;
	unsigned char value[8];
	unsigned char snr;
	QPlainTextEdit *text = ui.dataEdit;
	int result = cardReader->TYPEB_SFZSNR(mode,halt,&snr,value);
	showStatue(text, result);
	if(result == 0)
	{
		try
		{
			if(snr==0x00)
					text->appendPlainText(QString::fromLocal8Bit("ֻ��һ�ſ�....."));
			else
				text->appendPlainText(QString::fromLocal8Bit("�ж��ſ�....."));
			showData(text,value,0,8);
		}
		catch(...)
		{
			//feel sorry.Bug disappear again.Must do it like this
		}
	}
	else
		showStatue(text,snr);
	text->appendPlainText(""); //new line
}


//15693
void UsbReaderDemo::on_isoInventory_clicked()
{
	unsigned char Cardnumber;
	unsigned char pBuffer[256];
	int result = cardReader->ISO15693_Inventory(&Cardnumber, pBuffer);
	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text, result);
	if(result==0)
	{
		text->appendPlainText(QString::fromLocal8Bit("����:"));
		text->appendPlainText(QString("%1").arg(Cardnumber,2,16,QChar('0')).toUpper());
		text->appendPlainText(QString::fromLocal8Bit("����������Ϊ:"));
		showData(text,pBuffer,0,10*Cardnumber);
		for (int i=0;i<Cardnumber;i++)
		{
			text->appendPlainText(QString::fromLocal8Bit("��%1�ſ�������:").arg(i+1));
			QString cardData;
			for (int j=0;j<8;j++)
			{
				cardData += QString("%1 ").arg(pBuffer[Cardnumber*10 - (i*10+j) - 1], 2, 16, QChar('0')).toUpper();
			}
			text->appendPlainText(cardData);
		}
	}
	else
		showStatue(text, Cardnumber);
	text->appendPlainText(""); //new line
}

void UsbReaderDemo::on_isoRead_clicked()
{
	unsigned char flags = ui.isoreadFlag->text().toInt(0,16);
	unsigned char blk_add = ui.isoreadStart->text().toInt(0,16);
	unsigned char num_blk = ui.isoreadNum->text().toInt(0,16);
	unsigned char uid[8];
	QString uidStr = formatStr(ui.isoreadUID->text());
	convertStr(uid,uidStr,8);
	unsigned char buffer[256];
	int n;
	if(flags == 0x42)
		n = 5;
	else
		n = 4;
	int result = cardReader->ISO15693_Read(flags,blk_add,num_blk,uid,buffer);
	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text,result);
	if(result == 0)
	{
		text->appendPlainText(QString::fromLocal8Bit("��־λ:"));
		showData(text,buffer,0,1);
		text->appendPlainText(QString::fromLocal8Bit("����������:"));
		showData(text,buffer,1,n*num_blk);
	}
	else
		showStatue(text,buffer[0]);
	text->appendPlainText("");
}

void UsbReaderDemo::on_isoWrite_clicked()
{
	unsigned char flags = ui.isowriteFlag->text().toInt(0,16);
	unsigned char blk_add = ui.isowriteStart->text().toInt(0,16);
	unsigned char num_blk = ui.isowriteNum->text().toInt(0,16);
	unsigned char uid[8];
	QString uidStr = formatStr(ui.isoreadUID->text());
	convertStr(uid,uidStr,8);
	unsigned char data[256];
	int n;
	if(flags == 0x42)
		n = 5;
	else
		n = 4;
	QString dataStr = formatStr(ui.isowriteData->text());
	convertStr(data,dataStr,num_blk*n);
	int result = cardReader->ISO15693_Write(flags,blk_add,num_blk,uid,data);
	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text,result);
	if(result != 0)
		showStatue(text,data[0]);
	text->appendPlainText("");
}

//no data
void UsbReaderDemo::on_isoGet_clicked()
{
	unsigned char flag = ui.isogetFlag->text().toInt(0,16);
	unsigned char uid[8];
	unsigned char Buffer[255]={0};
	QString uidStr = formatStr(ui.isogetUID->text());
	convertStr(uid,uidStr,8);
	int result = cardReader->ISO15693_GetSysInfo(flag, uid, Buffer);
	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text, result);
	if ( result == 0 )
	{
		text->appendPlainText(QString::fromLocal8Bit("��־λ:"));
		showData(text,Buffer,0,1);
		text->appendPlainText("INFO Flags:");
		showData(text,Buffer,1,1);
		text->appendPlainText("UID:");
		showData(text,Buffer,2,8);
		text->appendPlainText("DSFID:");
		showData(text,Buffer,10,1);
		text->appendPlainText("AFI");
		showData(text,Buffer,11,1);
		text->appendPlainText("Other fields:");
		showData(text,Buffer,12,5);
	}
	else 
		showStatue(text, Buffer[0]);
	text->appendPlainText("");
}

void UsbReaderDemo::on_blockLock_clicked()
{
	unsigned char flags = ui.blklockFlag->text().toInt(0,16);
	unsigned char num_blk = ui.lockBlock->text().toInt(0,16);
	unsigned char uid[8];
	QString uidStr = formatStr(ui.blklockUID->text());
	convertStr(uid,uidStr,8);
	unsigned char buffer;
	int result = cardReader->ISO15693_Lock(flags, num_blk, uid, &buffer);
	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text, result);
	showStatue(text, buffer);
	text->appendPlainText("");
}

void UsbReaderDemo::on_cardSelect_clicked()
{
	unsigned char flags = ui.cardselFlag->text().toInt(0,16);
	unsigned char uid[8];
	QString uidStr = formatStr(ui.cardselUID->text());
	convertStr(uid,uidStr,8);
	unsigned char buffer;
	int result = cardReader->ISO15693_Select(flags, uid, &buffer);
	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text, result);
	showStatue(text, buffer);
	text->appendPlainText("");
}

void UsbReaderDemo::on_afiWrite_clicked()
{
	unsigned char flags = ui.afiwriteFlag->text().toInt(0,16);
	unsigned char uid[8];
	QString uidStr = formatStr(ui.afiwriteUID->text());
	convertStr(uid,uidStr,8);
	unsigned char afi = ui.writeAFI->text().toInt(0,16);
	unsigned char buffer;
	int result = cardReader->ISO15693_WriteAFI(flags, afi,uid, &buffer);
	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text, result);
	showStatue(text, buffer);
	text->appendPlainText("");
}

void UsbReaderDemo::on_afiLock_clicked()
{
	unsigned char flags = ui.afilockFlag->text().toInt(0,16);
	unsigned char uid[8];
	QString uidStr = formatStr(ui.afilockUID->text());
	convertStr(uid,uidStr,8);
	unsigned char buffer;
	int result = cardReader->ISO15693_LockAFI(flags,uid, &buffer);
	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text, result);
	showStatue(text, buffer);
	text->appendPlainText("");
}

//Reader received unknown command
void UsbReaderDemo::on_dsfidWrite_clicked()
{
	unsigned char flags = ui.dsfidwriteFlag->text().toInt(0,16);
	unsigned char uid[8];
	QString uidStr = formatStr(ui.dsfidwriteUID->text());
	convertStr(uid,uidStr,8);
	unsigned char DSFID = ui.writeDSFID->text().toInt(0,16);
	unsigned char buffer;
	int result = cardReader->ISO15693_WriteDSFID(flags, DSFID, uid, &buffer);
	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text, result);
	showStatue(text, buffer);
	text->appendPlainText("");
}

void UsbReaderDemo::on_dsfidLock_clicked()
{
	unsigned char flags = ui.dsfidlockFlag->text().toInt(0,16);
	unsigned char uid[8];
	QString uidStr = formatStr(ui.lockdsfidUID->text());
	convertStr(uid,uidStr,8);
	unsigned char buffer;
	int result = cardReader->ISO15693_LockDSFID(flags,uid, &buffer);
	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text, result);
	showStatue(text, buffer);
	text->appendPlainText("");
}

//Check sequence error
void UsbReaderDemo::on_blksecGet_clicked()
{
	unsigned char flags = ui.blksecFlag->text().toInt(0,16);
	unsigned char blkAddr = ui.blksecStart->text().toInt(0,16);
	unsigned char blkNum = ui.blksecNum->text().toInt(0,16);
	unsigned char uid[8];
	QString uidStr = formatStr(ui.blksecUID->text());
	convertStr(uid,uidStr,8);
	unsigned char *pBuffer = new unsigned char[blkNum+1];
	int result = cardReader->ISO15693_GetMulSecurity(flags,blkAddr,blkNum,uid,pBuffer);
	QPlainTextEdit *text = ui.dataEdit;
	showStatue(text,result);
	if(result == 0)
	{
		text->appendPlainText(QString::fromLocal8Bit("��־λ:"));
		showData(text,pBuffer,0,1);
		text->appendPlainText(QString::fromLocal8Bit("�鰲ȫλ:"));
		showData(text,pBuffer,1,blkNum);
	}
	else
		showStatue(text,pBuffer[0]);
	text->appendPlainText("");
}	  

UsbReaderDemo::~UsbReaderDemo()
{

}
