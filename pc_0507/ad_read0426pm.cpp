
#include "stdafx.h"

#include "mmsystem.h" 

#include "timer.h"

#include "protocol.h"

#include  "meter_read_cmd_encode.h"

#include  "global.h"

#include  "init.h"

#include  "fifo.h"

#include  "ad_read.h"






SHORT         g_s_ad_fifo_buffer[ _AD_DATA_FIFO_LEN ] ; // Receive AD data buffer  

HANDLE        hThread_AD_Read  ; 

HANDLE        hEvent_Read_AD_Data  ;

HANDLE        hEvent_AD_Read_Data_Error ;

unsigned char g_uc_active_line_index[ _AD_SAMPLE_CHANNEL_MAX ] ;//�洢��Ҫ��ȡ�ĳ��ߵ��±�
//����g_uc_line_active_numberΪ3��g_uc_active_line_index[ 0 ]Ϊ2 ��g_uc_active_line_index[ 1]Ϊ6 ��g_uc_active_line_index[ 2 ]Ϊ9
//˵����2����6 �� 9 �����ߵ���������Ч��,�����±��0��19  

unsigned char g_uc_active_line_trig_index[ _AD_SAMPLE_CHANNEL_MAX ] ;
//ÿ�������Ϲ���㴥���Ĵ�����һ�߽���ȡ�����ݴ洢���봥��λ�ö�Ӧ�Ĵ洢���У�ȡֵΪ0-7����һλ������Ҫ8�δ���
//���������Ӧ����ĳ���Ϊ9 ����g_uc_active_line_index[ x ] = 9 ��g_uc_active_line_trig_index�� 9 �� = 3 ��
//���´ζ�ȡ����320������Ϊ��3�δ��������ݣ���Ӧ�洢��TRIG_POINT3��λ���ϡ�



unsigned char g_uc_line_active_number  ; //��Ҫ��ȡ�ĳ��ߵ�����Ŀ�����籾����Ҫ��ȡ�ܹ�6�����ߵ����ݣ� 1 - 20

unsigned char g_uc_data_index_line = 0 ;//ÿ����Ҫ��ȡ�ĳ��ߵ�ָ��0 - 19 

unsigned char g_uc_data_index_bit = 0 ;//ÿ����Ҫ��ȡ��64λ�е���һλ��ָ��0 -63

unsigned char g_uc_data_index_trig = 0 ;//ÿ����Ҫ��ȡ����һ�δ�����ָ�룬0 - 7 

bool          g_bflag_one_bit_read = false ;







void  Fun_AD_Read_Index_Init( )
{
	g_uc_data_index_line = 0 ;
	
    g_uc_data_index_bit = 0 ;

    g_uc_data_index_trig = 0 ;
}


//10 * 2 line , 64 bit ,8 trig , 320 data
SHORT  uc_s_line_data[ 20 ] [ 64 ][ 8 ] [ 320 ] ;

 

stru_AD_Sample_Data_One_Bit      g_stru_ad_data_one_bit_line[ _AD_SAMPLE_CHANNEL_MAX ] ;

//���ݽ��ն�ȡ��Ϻ󣬵�ĳ�������ϵ����ݶ�ȡ��8�Σ�
//����ȡ����8��trig���ݣ���Ҫ���н��룬һ�²������ݸ������߳�
unsigned char    uc_data_decode_line_index  ;//���ν��������λ��������

unsigned char    uc_data_decode_bit_index[ _AD_SAMPLE_CHANNEL_MAX ] ; //ÿ�������ϱ��ν����Ϊ�ڼ���bit���ݣ�ȡֵ��Χ0 - 63
//ÿ�յ�8��trig���ݺ󣬸ñ�־λ������1���������µ�һbit������Ҫ���롣


HANDLE     hThread_Data_decode ;

HANDLE     hEvent_Data_Decode ;

HANDLE     hEvent_Data_Decode_Error ;


typedef   struct
{

} stru_Active_Line_Phase ;


/*
unsigned char  Fun_Get_Phase_Index( unsigned char line_index )
{
   unsigned char  phase_index = 0 ;

   switch( line_index )
   {
     case _PHASE_A :
	{

			 break ;
	}
}

}
*/
//��ȡ����ʱ֪�����δ�����Ҫ��ȡ����������ߣ���1-20���������ߣ���������������������Ӧ����˲���Ҫ֪����ľ������ݡ�
//_AD_READ_DATA_LEN_PER_TRIG    320 * 10
void CALLBACK Thread_AD_Read( )
{
  int i  , k ;

  unsigned  char line_index = 0 ;  //�õ���Ҫ��ȡ�ĳ��ߵ��±�
  
//  unsigned  char phase_index = 0 ;
  
  unsigned char  trig_index = 0 ;

  ULONG   read_len = _AD_READ_DATA_LEN_PER_TRIG * 8 * 20 ; //20 line ,8 trig , 320 per trig

  stru_Pro_Decode_Data_One_Bit    stru_pro_decode_data ; 

  do //��ѭ��
  {
    if( WaitForSingleObject( hEvent_Read_AD_Data , 0 ) == WAIT_OBJECT_0 )//start read ad data 
	{
	   if(!PCI8664_ReadDeviceProAD_Npt( hDevice_AD, g_s_ad_fifo_buffer, read_len , &nRetSizeWords ) )
		{
			AfxMessageBox( "AD Card Read  error!");

			SetEvent( hEvent_AD_Read_Data_Error ) ;			
		}
	   if( nRetSizeWords == read_len )//��ȡ����Ӧ���ݳ��ȵ�����
	   {
         for( i = 0 ; i < g_uc_line_active_number ; i ++ )
		 {
			 line_index = g_uc_active_line_index[ i ] ;  //�õ���Ҫ��ȡ�ĳ��ߵ��±�

			 trig_index = g_uc_active_line_trig_index[ line_index ] ;

			 switch( trig_index )
			 {
			 case _TRIG_POINT_0 :
				 {
				   for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
				   {
					 g_stru_ad_data_one_bit_line[ line_index ].trig_point0[ k ] = g_s_ad_fifo_buffer[ 
					    line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
				   }

                   g_uc_active_line_trig_index[ i ] ++ ;

                   break ;
				 }
			 case _TRIG_POINT_1 :
				 {
					 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
					 {
						 g_stru_ad_data_one_bit_line[ line_index ].trig_point1[ k ] = g_s_ad_fifo_buffer[ 
							 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
					 }

                     g_uc_active_line_trig_index[ i ] ++ ;					 

					 break ;
				 }
			 case _TRIG_POINT_2 :
				 {
					 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
					 {
						 g_stru_ad_data_one_bit_line[ line_index ].trig_point2[ k ] = g_s_ad_fifo_buffer[ 
							 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
					 }
					 
                     g_uc_active_line_trig_index[ i ] ++ ;					 
					 
					 break ;
				 }
			 case _TRIG_POINT_3 :
				 {
					 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
					 {
						 g_stru_ad_data_one_bit_line[ line_index ].trig_point3[ k ] = g_s_ad_fifo_buffer[ 
							 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
					 }
					 
                     g_uc_active_line_trig_index[ i ] ++ ;					 
					 
					 break ;
				 }
			 case _TRIG_POINT_4 :
				 {
					 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
					 {
						 g_stru_ad_data_one_bit_line[ line_index ].trig_point4[ k ] = g_s_ad_fifo_buffer[ 
							line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
					 }
					 
                     g_uc_active_line_trig_index[ i ] ++ ;					 
					 
					 break ;
				 }
			 case _TRIG_POINT_5 :
				 {
					 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
					 {
						 g_stru_ad_data_one_bit_line[ line_index ].trig_point5[ k ] = g_s_ad_fifo_buffer[ 
							 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
					 }
					 
                     g_uc_active_line_trig_index[ i ] ++ ;					 
					 
					 break ;
				 }
			 case _TRIG_POINT_6 :
				 {
					 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
					 {
						 g_stru_ad_data_one_bit_line[ line_index ].trig_point6[ k ] = g_s_ad_fifo_buffer[ 
							 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
					 }
					 
                     g_uc_active_line_trig_index[ i ] ++ ;					 
					 
					 break ;
				 }
			 case _TRIG_POINT_7 :
				 {
					 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
					 {
						 g_stru_ad_data_one_bit_line[ line_index ].trig_point7[ k ] = g_s_ad_fifo_buffer[ 
							 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
					 }
					 
                     g_uc_active_line_trig_index[ i ] ++ ;					 
					 
					 break ;
				 }
			   default:
				 break ;
			 }//switch 

			 if( g_uc_active_line_trig_index[ i ] >= 8 )//��Ӧ�����ϵ����ݽ��ճ���8�Σ������յ���һbit������
			 {
				g_uc_active_line_trig_index[ i ] = 0 ; //trig����ָ�븴λ��0 ��׼��������һbit��8��trig���� 
			 
				uc_data_decode_line_index =  line_index ;
				
				uc_data_decode_bit_index[ line_index ] ++ ;					  
				
			//	SetEvent( hEvent_Data_Decode ) ;
                //����Ӧ��ad���ݼ����ݵĳ��ߺ�bitλ��Ϣѹ���ջ
				Fun_Fifo_Push_Down(  &g_stru_ad_data_one_bit_line[ line_index ] , 1 ) ;;
			 }
				 		 
		 }//for,read line data
	   }//
	   
	 }
  } 
  while ( 1 ) ;//��ѭ��

}

void  Fun_Thread_AD_Read_Init( )
{
	/////////////create a thread
	hThread_AD_Read = CreateThread( 0, 0, ( pfun_callback)Thread_AD_Read , 0 , 
		0 , &dwThreadID1 ) ;
	
	SetThreadPriority( hThread_AD_Read , THREAD_PRIORITY_NORMAL ) ; 
	
	hEvent_Read_AD_Data = CreateEvent( NULL , true , false , NULL) ;
	
	hEvent_AD_Read_Data_Error = CreateEvent( NULL , true , false , NULL) ;
}


void CALLBACK Thread_Data_Decode( )
{
//uc_data_decode_line_index =  line_index ;
				
//uc_data_decode_bit_index[ line_index ] ++ ;
/*
int  i , k ;

	for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
	{
		g_stru_ad_data_one_bit_line[ line_index ].trig_point7[ k ] = g_s_ad_fifo_buffer[ 
			line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
					 }	
*/
}


void  Fun_Thread_Data_Decode_Init( )
{
	/////////////create a thread
	hThread_Data_decode = CreateThread( 0, 0, ( pfun_callback)Thread_Data_Decode , 0 , 
		0 , &dwThreadID1 ) ;
	
	SetThreadPriority( Thread_Data_Decode , THREAD_PRIORITY_NORMAL ) ; 
	
	hEvent_Data_Decode  = CreateEvent( NULL , true , false , NULL) ;
	
	hEvent_Data_Decode_Error = CreateEvent( NULL , true , false , NULL) ;
}