
#include "stdafx.h"

#include   "global.h"

#include   "init.h"

#include   "timer.h"

#include   "data_transfer.h"






BYTE    g_uc_send_io_data[ 16 ] ;

BYTE    g_uc_recv_io_data[ 16 ] ;

unsigned char   g_uc_PC_RX_Buf[ 16 ] ; //pc����дָ��������Ŷ�д������ָ��ķ�������


unsigned char     g_uc_zero_pass_times = 0 ;//���յ��Ĺ�������

unsigned char     g_uc_zero_times = 0 ;


#define           _ZERO_TIMES    5


#define     _DEBUG_MESSAGE_ZERO_TIMES_SHOW
 //************************************




// Method:    Fun_PC_CLK_Init
// FullName:  Fun_PC_CLK_Init
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void  Fun_PC_CLK_Init()
{
	int i ;

	if( g_ad_device_init == false )
	{
		hDevice_AD = PCI8664_CreateDevice( 0 );
		
		if( hDevice_AD == INVALID_HANDLE_VALUE ) 
		{
			AfxMessageBox( "init error!") ;
			
			g_ad_device_init =  false ;
		}
		else
		{
			g_ad_device_init = true ;
		}
	}
    
	for( i = 0 ; i < 16 ; i ++ )
	{
		g_uc_send_io_data[ i ] = 0x00 ;
	}
	
    g_uc_send_io_data[ 8 ] = 0x00 ;//clk  �͵�ƽ��������pc�����ݣ�mcu�½��ض�ȡ���ݡ�

    g_uc_send_io_data[ 9 ] = 0x00 ;//trig  �͵�ƽ��������mcu��ʼtrig�źš�
				
	PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //������ݺ�clk�ź�
	
}
//************************************
// Method:    Fun_Send_Data_Set
// FullName:  Fun_Send_Data_Set
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: unsigned char data
//************************************
void Fun_Send_Data_Set( unsigned char data )
{
	g_uc_send_io_data[0] = data & 0x01 ;  
    
	g_uc_send_io_data[1] = ( data >> 1 ) & 0x01 ; 
	
	g_uc_send_io_data[2] = ( data >> 2 ) & 0x01 ; 
	
	g_uc_send_io_data[3] = ( data >> 3 ) & 0x01 ; 
	
	g_uc_send_io_data[4] = ( data >> 4 ) & 0x01 ; 
	
	g_uc_send_io_data[5] = ( data >> 5 ) & 0x01 ;
	
	g_uc_send_io_data[6] = ( data >> 6 ) & 0x01 ; 
	
	g_uc_send_io_data[7] = ( data >> 7 ) & 0x01 ; 
	
	g_uc_send_io_data[8] = 0x00 ;
	
	g_uc_send_io_data[9] = 0x00 ; 
	
	g_uc_send_io_data[10] = 0x00 ;
	
	g_uc_send_io_data[11] = 0x00 ;
	
	g_uc_send_io_data[12] = 0x00 ;
	
	g_uc_send_io_data[13] = 0x00 ;
	
	g_uc_send_io_data[14] = 0x00 ;
	
	g_uc_send_io_data[15] = 0x00 ; 
	
}



//************************************
// Method:    Fun_Recv_Data_Set
// FullName:  Fun_Recv_Data_Set
// Access:    public 
// Returns:   unsigned char
// Qualifier:
// Parameter: BYTE * data
//************************************
unsigned char Fun_Recv_Data_Set( BYTE  * data )
{
	unsigned char   recv_data = 0x00 ;
	
	int  i ;
	
	for( i = 0 ;i < 8 ; i ++ )
	{
		recv_data += ( * ( data + i ) & 0x01 ) << i  ;
	} 
    return  recv_data ; 
	
}

//************************************
// Method:    Fun_PC_Recv_Data
// FullName:  Fun_PC_Recv_Data
// Access:    public 
// Returns:   int,1:read or write ok ,the caller get the feedback 
                    //datas from the buffer g_uc_PC_RX_Buf[ 16 ]
// Qualifier:
// Parameter: int len
// Parameter: unsigned char start_flag
//************************************
int  Fun_PC_Recv_Data( int len , unsigned char start_flag ) 
{
	return  1 ;
}


int   Fun_PC_Recv_Data( unsigned char start_flag )
{

	LARGE_INTEGER    time1 ;
	
	double   db_freq ,  db_space ;
	
	LONGLONG db_start , db_end ; 
	
	unsigned int  data = 0x00 ;

	unsigned char   recv_data ;
	
	//��ȡָ��ظ���len�ֽڳ���
	bool bflag_recv_start = false ;

	int len = 0x0F ; 
	
	
	unsigned char recv_data_index = 0 ;	
	//get frequence 
	QueryPerformanceFrequency( &time1 ) ;
	
    db_freq = ( double ) time1.QuadPart  ;

	Fun_Operation_Timer_Set( 600 ) ;
	
  do 
  {  
	 if( WaitForSingleObject( hEvent_Operation_Timer_Timeout  , 0 ) == WAIT_OBJECT_0 ) 
	 {
        return   _TIMEOUT ;
	 }
	 else
	 {
	   g_uc_send_io_data[ 8 ] = 0x01 ;//ʹCLK��������ߵ�ƽ
		
	   PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //���clk�ź�
		
		QueryPerformanceCounter( &time1 ) ;  //�õ���ʼʱ��
		
		db_start = time1.QuadPart ;
		
		do
		{    
			QueryPerformanceCounter( &time1 ) ;  //�õ���ǰʱ��
			
			db_end = time1.QuadPart ;
			
			db_space = ( double ) ( db_end- db_start ) ; //ʱ���
			
			db_space = db_space / db_freq ;
			
		}   
		while( db_space < _100K_CLK ) ;  //ʱ���С��100K
		
		//�͵�ƽʱ�䵽,��ȡ����
		
		PCI8664_GetDeviceDI( hDevice_AD , g_uc_recv_io_data ) ;

		recv_data = Fun_Recv_Data_Set( g_uc_recv_io_data ) ;

        //recv_data = (unsigned char ) data & 0xFF ;
		
		if( recv_data == start_flag && bflag_recv_start ==  false ) //the start of readback data
		{
			bflag_recv_start = true ;
			
			g_uc_PC_RX_Buf[ 0 ] = recv_data ;
			
			recv_data_index ++ ; 

		    Fun_Operation_Timer_Set( 600 ) ;
		}
		else if( bflag_recv_start == true )
		{
			g_uc_PC_RX_Buf[ recv_data_index ] = recv_data ;

			recv_data_index ++ ;

		//	if( recv_data_index == _UP_FRAME_DATA_LEN_BYTE )

			//	 len = g_uc_PC_RX_Buf[ recv_data_index ] + _UP_FRAME_DATA_LEN_BYTE + 2 ;

		//	len = 16 ;
		    Fun_Operation_Timer_Set( 600 ) ;
			
		}

		/////////////////////////////
		g_uc_send_io_data[ 8 ] = 0x00 ;  //ʹCLK�������di��ƽ
		
		PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;

		//��ʱ100K�����ֵ͵�ƽ
		QueryPerformanceCounter( &time1 ) ;  //�õ���ʼʱ��
		
		db_start = time1.QuadPart ;
		
		do
		{    
			QueryPerformanceCounter( &time1 ) ;  //�õ���ǰʱ��
			
			db_end = time1.QuadPart ;
			
			db_space = ( double ) ( db_end- db_start ) ; //ʱ���
			
			db_space = db_space / db_freq ;
			
		}   while( db_space < _100K_CLK ) ;  //ʱ���С��100K
		
	} //else , not timeout
  }
  while( recv_data_index < len  ) ;//�ж϶�ȡ���ݵĸ���
                          //�Ƿ�ﵽЭ��涨�����ݳ��ȣ����򷵻ؼ�����ȡ��һ���ֽ�

//   Fun_Protocol_Show_Recv( g_uc_PC_RX_Buf  , _SHOW ) ;

  //return g_uc_PC_RX_Buf ;
  return  1 ;

}


//************************************
// Method:    Fun_PC_Send_Data
// FullName:  Fun_PC_Send_Data
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: unsigned char * buf
// Parameter: int len
//************************************
void  Fun_PC_Send_Data( unsigned char * buf , int len )
{
	LARGE_INTEGER    time1 ;
	
	double   db_freq ,  db_space ;
	
	LONGLONG db_start , db_end ; 

	int i ;		
	//get frequence 
	QueryPerformanceFrequency( &time1 ) ;
	
    db_freq = ( double ) time1.QuadPart  ;

   //����ָ�� 
   for( i = 0 ; i < len ; i ++ )
   {     
	  // send_data = buf[ i ] | _BIT8_CLK_HIGH  ;  //ʹCLK��������ߵ�ƽ��ͬʱ������ݷ��õ��Ͱ�λ

	   Fun_Send_Data_Set( buf[ i ] ) ; 

	   g_uc_send_io_data[ 8 ] = 0x01 ;

	   PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //������ݺ�clk�ź�
	   
	   QueryPerformanceCounter( &time1 ) ;  //�õ���ʼʱ��
	   
	   db_start = time1.QuadPart ;
	   ////////��ʱ100k , ���ָߵ�ƽ
	   do
	   {    
		   QueryPerformanceCounter( &time1 ) ;  //�õ���ǰʱ��
		   
		   db_end = time1.QuadPart ;
		   
		   db_space = ( double ) ( db_end- db_start ) ; //ʱ���
		   
		   db_space = db_space / db_freq ;
		   
	   }   
	   while( db_space < _100K_CLK ) ;  //ʱ���С��100K
	   
	   g_uc_send_io_data[ 8 ] = 0x00   ;  //ʹCLK�������di��ƽ��ͬʱ������ݷ��õ��Ͱ�λ
	   
	   PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;
	   ////////��ʱ100k �����ֵ͵�ƽ
	   QueryPerformanceCounter( &time1 ) ;  //�õ���ʼʱ��
	   
	   db_start = time1.QuadPart ;
	   
	   do
	   {    
		   QueryPerformanceCounter( &time1 ) ;  //�õ���ǰʱ��
		   
		   db_end = time1.QuadPart ;
		   
		   db_space = ( double ) ( db_end- db_start ) ; //ʱ���
		   
		   db_space = db_space / db_freq ;
		   
	   }   
	   while( db_space < _100K_CLK ) ;  //ʱ���С��100K
   }//for
	
}



int  Fun_PC_Zero_Cap( int zero_pass_number )
{
	unsigned char recv_data = 0 ; 
	
	g_uc_zero_pass_times = 0 ;

	unsigned char    uc_handshake_ok_times = 0 ;
	
	//����ָ�� 
	do
	{   
	   g_uc_zero_times = 0 ;

	   do //
	   {					
			//ÿ�εȴ��������ȷ��ʱ�������ʱ���򷵻�
			if( WaitForSingleObject( hEvent_Operation_Timer_Timeout  , 0 ) == WAIT_OBJECT_0 ) 
			{
				return   _TIMEOUT ;
			}
			//////////////
			recv_data = 0xFF ;

			PCI8664_GetDeviceDI( hDevice_AD , g_uc_recv_io_data ) ;
			
			recv_data = Fun_Recv_Data_Set( g_uc_recv_io_data ) ;//20ms���Զ�����
			
			recv_data = (unsigned char ) recv_data & 0xFF ;

		//	Fun_Read_And_Show_Data( recv_data ) ;
			
 			if( recv_data == _ZERO_PASS_FLAG  ) //the flag of the DTU zero pass
			{
			  g_uc_zero_times ++ ;

              if( g_uc_zero_times >= _ZERO_TIMES )
			  {
				g_uc_zero_times = 0 ;

				Fun_Operation_Timer_Stop( ) ; //��׽�ɹ���ֹͣ��ʱ���Է���ʱ�����
				
                g_uc_zero_pass_times ++ ;
 
				//����һ��clk�ܲ�����clk����200k�����һ�����ݽ�������
				g_uc_send_io_data[ 8 ] = 0x01 ;//ʹCLK�������gao��ƽ
				
				PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //���clk high �ź�			
				/////////////////////////////////////////////

			//	Fun_Operation_Timer_Set( _MILLSECOND_20  ) ; //��׽�ɹ���ֹͣ��ʱ���Է���ʱ�����
                Fun_Delay_Usecond( 1000 ) ;  //100us 

				uc_handshake_ok_times = 0 ; 



				do 
				{								   
				   recv_data = 0xFF ;

				   PCI8664_GetDeviceDI( hDevice_AD , g_uc_recv_io_data ) ;
				
				   recv_data = Fun_Recv_Data_Set( g_uc_recv_io_data ) ;//20ms���Զ�����
				
			       recv_data = (unsigned char ) recv_data & 0xFF ;

				   //Fun_Read_And_Show_Data( recv_data ) ;

				   if( recv_data == _ZERO_HANDSHAKE_FLAG )//0x00
				   {
					   uc_handshake_ok_times ++ ;

					   if( uc_handshake_ok_times >= _ZERO_TIMES )
					   {
						   break ;
					   }
				   }
				   else //if recv_dat not 0x00
				   {
                       uc_handshake_ok_times = 0 ;
				   }

				   if( WaitForSingleObject( hEvent_Operation_Timer_Timeout  , 0 ) == WAIT_OBJECT_0 ) 
				   {
					   return   _TIMEOUT ;
				   }

				} while ( 1 );

			   g_uc_send_io_data[ 8 ] = 0x00 ;//ʹCLK�������di��ƽ
					
			   PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //���clk high �ź�			

           //    Fun_Operation_Timer_Set( _MILLSECOND_20  ) ;
			   ////////////////////////////////
               #ifdef   _DEBUG_MESSAGE_ZERO_TIMES_SHOW
				{
					CString    str1 ;
					
					str1.Format( "����������%d" , g_uc_zero_pass_times ) ;
					
					g_plab_zero_times->SetWindowText( str1 ) ;
					
				}
              #endif
				break ;//��׽����㣬���β�׽���̽�������ʼ�´β�׽����
			  }//if 3 times

			}//if zero cap			 
		    else //not zero cap
			{
		       g_uc_zero_times = 0 ;
			}

		}//�ߵ�ƽ�ȴ���㲻����ѯ���� 
		while( 1 ) ;
	}
	while( g_uc_zero_pass_times < zero_pass_number  ) ;//�ж϶�ȡ���ݵĸ���
                          //�Ƿ�ﵽЭ��涨�����ݳ��ȣ����򷵻ؼ�����ȡ��һ���ֽ� ;//�����β�׽����ѭ��
 return 1 ;
}



//************************************
// Method:    Fun_PC_Zero_Cap_Firstly
// FullName:  Fun_PC_Zero_Cap_Firstly
// Access:    public 
// Returns:   int
// Qualifier:
//************************************
int  Fun_PC_Zero_Cap_Firstly( )
{
	
	int error_flag = 0  ;	
	
	unsigned char recv_data = 0 ; 
 		
//	Fun_Operation_Timer_Set( _MILLSECOND_20 ) ;//start other circle timer

	g_uc_zero_times = 0 ;
		
	do //
	{					
	  //ÿ�εȴ��������ȷ��ʱ�������ʱ���򷵻�
	  if( WaitForSingleObject( hEvent_Operation_Timer_Timeout  , 0 ) == WAIT_OBJECT_0 ) 
	  {
		 return   _TIMEOUT ;
	  }
	  //////////////
	  recv_data = 0xFF ;

	  PCI8664_GetDeviceDI( hDevice_AD , g_uc_recv_io_data ) ;
			
	  recv_data = Fun_Recv_Data_Set( g_uc_recv_io_data ) ;//20ms���Զ�����
			
	  recv_data = (unsigned char ) recv_data & 0xFF ;
			
	  if( recv_data == _ZERO_PASS_FLAG  ) //the flag of the DTU zero pass
	  {
        g_uc_zero_times ++ ;

		if( g_uc_zero_times >= _ZERO_TIMES )
		{
		  g_uc_zero_times = 0 ;
		  
		  Fun_Operation_Timer_Stop( ) ; //��׽�ɹ���ֹͣ��ʱ���Է���ʱ�����

		  for( int i = 0 ; i < 65535 ; i ++ ) ;
				
		  //����һ��clk�ܲ�����clk����200k�����һ�����ݽ�������
		  g_uc_send_io_data[ 8 ] = 0x01 ;//ʹCLK�������gao��ƽ
				
		  PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //���clk high �ź�			
	
		  //��һ���������Ͽ�ʼ���յ���������		
          error_flag = Fun_PC_Recv_Data( 16 , 0x68 ) ;

		  if( error_flag == _TIMEOUT )
		  {
            return _TIMEOUT ;
		  }
				
		  ////////////////////////////////
		  break ;//��׽����㣬���β�׽���̽�������ʼ�´β�׽����
		}//if three times

	  }//if zero cap 
	  else
	  {
		  g_uc_zero_times = 0 ;
	  }
	}//�ߵ�ƽ�ȴ���㲻����ѯ���� 
	while( 1 ) ;

  return 1 ;
}




int  Fun_PC_Trig_Pulse_Init(  bool   edge_type )
{
  if( edge_type == _FAILING_EDGE )
  {
	/////clk high 	
	g_uc_send_io_data[ 9 ] = 0x01 ;
	  
	PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //������ݺ�clk�ź�
  }
  if( edge_type == _RAISING_EDGE )
  {
	  /////clk high 	
	  g_uc_send_io_data[ 9 ] = 0x00 ;
	  
	  PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //������ݺ�clk�ź�
  }

  return 1 ;
}



int  Fun_PC_Trig_Pulse(  bool   edge_type )
{
	LARGE_INTEGER    time1 ;
	
	double   db_freq ,  db_space ;
	
	LONGLONG db_start , db_end ; 
		
	//get frequence 
	QueryPerformanceFrequency( &time1 ) ;
	
	db_freq = ( double ) time1.QuadPart  ;

	if( edge_type == _RAISING_EDGE )
	{
	    /////clk high and wait fot the zero pass	
	    g_uc_send_io_data[ 9 ] = 0x01 ;
	
	    PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //������ݺ�clk�ź�

		//////////////////////////////////��ʱ			
	    QueryPerformanceCounter( &time1 ) ;  //�õ���ʼʱ��
	
	    db_start = time1.QuadPart ;
	    //��ʱ���clk�ź�		
	   do
	   {    
		  QueryPerformanceCounter( &time1 ) ;  //�õ���ǰʱ��
		
		  db_end = time1.QuadPart ;
		
		  db_space = ( double ) ( db_end- db_start ) ; //ʱ���
		
		  db_space = db_space / db_freq ;
		
	   }   
	   while( db_space < _100K_CLK ) ;  //ʱ���С��100K
	   /////clk low	
	   g_uc_send_io_data[ 9 ] = 0x00 ;
	   
	   PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //������ݺ�clk�ź�	
	}
	else if( edge_type == _FAILING_EDGE )
	{
		/////clk high and wait fot the zero pass	
		g_uc_send_io_data[ 9 ] = 0x00 ;
		
		PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //������ݺ�clk�ź�
		
		//////////////////////////////////��ʱ			
		QueryPerformanceCounter( &time1 ) ;  //�õ���ʼʱ��
		
		db_start = time1.QuadPart ;
		//��ʱ���clk�ź�		
		do
		{    
			QueryPerformanceCounter( &time1 ) ;  //�õ���ǰʱ��
			
			db_end = time1.QuadPart ;
			
			db_space = ( double ) ( db_end- db_start ) ; //ʱ���
			
			db_space = db_space / db_freq ;
			
		}   
		while( db_space < _100K_CLK ) ;  //ʱ���С��100K
		/////clk low	
		g_uc_send_io_data[ 9 ] = 0x01 ;
		
		PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //������ݺ�clk�ź�	
	}
	   return 1 ;
}



