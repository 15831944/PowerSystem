
#include "header.h"





unsigned int                    g_fifo_read_index  ;   //fifo 

unsigned int                    g_fifo_write_index ;


unsigned char                    g_uc_fifo_rw_falg ;  
//   _FIFO_WRITE_ENABLE   1

//   _FIFO_READ_ENABLE    2 

//   _FIFO_RW_DISABLE     3


unsigned  int                     g_i_fifo_len_frame  = _FIFO_LEN_FRAME ; //fifo�ĳ��ȣ���fifo��Ҫ�洢����֡������


unsigned  int                     g_i_fifo_len_line  = _FIFO_LEN_LINE ;   //fifo�ĳ��ȣ���fifo��Ҫ�洢���������ߵ�����


stru_Pro_Decode_Data_One_Bit      *  g_p_stru_fifo ;

unsigned int                      g_fifo_len_struct ; //fifo����ȣ��Դ������ÿһλ���ݽṹΪ��λ



void   Fun_Fifo_Len_Init( unsigned int line_len , unsigned int frame_len ) 
{
	g_i_fifo_len_frame  = frame_len ; //fifo�ĳ��ȣ���fifo��Ҫ�洢����֡������

	g_i_fifo_len_line  = line_len ;

	g_fifo_len_struct  = _FRAME_LEN * g_i_fifo_len_frame * g_i_fifo_len_line ;

    g_p_stru_fifo =  new   stru_Pro_Decode_Data_One_Bit [ g_fifo_len_struct  ] ;

	unsigned  int i ;

	for( i = 0 ; i < g_fifo_len_struct ; i ++ )
	{
       ( g_p_stru_fifo + i ) -> uc_line_index = _FIFO_FLAG_NULL ;

       ( g_p_stru_fifo + i ) -> uc_phase_index = _FIFO_FLAG_NULL ;

       ( g_p_stru_fifo + i ) -> uc_bit_index = _FIFO_FLAG_NULL ;

       ( g_p_stru_fifo + i ) -> uc_frame_index = _FIFO_FLAG_NULL ;

	   ( g_p_stru_fifo + i ) -> uc_rw_flag = _FIFO_WRITE_ENABLE ;

	//   *( g_p_stru_fifo + i ).uc_line_index = _FIFO_FLAG_NULL ;
   
	}
	g_fifo_write_index = 0 ;

	g_fifo_read_index = _FIFO_FLAG_NULL ; 

}


//���ٵ��ڴ滺���㹻�󣬲����Ƕ�д��������⣬��Ϊfifo����㹻������������������
//************************************
// Method:    Fun_Fifo_Push_Down
// FullName:  Fun_Fifo_Push_Down
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: stru_Pro_Decode_Data_One_Bit * p_data
// Parameter: unsigned int len
//************************************
int   Fun_Fifo_Push_Down(  stru_Pro_Decode_Data_One_Bit  * p_data  , unsigned int len )
{
  unsigned int i , k ;

for( k = 0 ; k < len ; k ++ )
{//len
  if( ( g_p_stru_fifo + g_fifo_write_index )->uc_rw_flag == _FIFO_READ_ENABLE )
		  
		 return  _FIFO_OVERFLOW ;
  else
  { //not overflow
  //��ȡ8ci ��320�����ݵ���Ӧ����λ��
   for( i = 0 ; i < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; i ++ )
   {
     ( g_p_stru_fifo + g_fifo_write_index )->stru_data_one_bit.trig_point0 [ i ] =
		  p_data->stru_data_one_bit.trig_point0[ i ] ;

     ( g_p_stru_fifo + g_fifo_write_index )->stru_data_one_bit.trig_point1 [ i ] =
		  p_data->stru_data_one_bit.trig_point1[ i ] ;
	 
     ( g_p_stru_fifo + g_fifo_write_index )->stru_data_one_bit.trig_point2 [ i ] =
		  p_data->stru_data_one_bit.trig_point2[ i ] ;

     ( g_p_stru_fifo + g_fifo_write_index )->stru_data_one_bit.trig_point3 [ i ] =
		  p_data->stru_data_one_bit.trig_point3[ i ] ;

     ( g_p_stru_fifo + g_fifo_write_index )->stru_data_one_bit.trig_point4 [ i ] =
		 p_data->stru_data_one_bit.trig_point4[ i ] ;
	 
     ( g_p_stru_fifo + g_fifo_write_index )->stru_data_one_bit.trig_point5 [ i ] =
		 p_data->stru_data_one_bit.trig_point5[ i ] ;
	 
     ( g_p_stru_fifo + g_fifo_write_index )->stru_data_one_bit.trig_point6 [ i ] =
		 p_data->stru_data_one_bit.trig_point6[ i ] ;
	 
     ( g_p_stru_fifo + g_fifo_write_index )->stru_data_one_bit.trig_point7 [ i ] =
		  p_data->stru_data_one_bit.trig_point7[ i ] ;
   }//one bit
	 /////////////////////
     ( g_p_stru_fifo + g_fifo_write_index )->uc_line_index = 
		  p_data->uc_line_index ;

     ( g_p_stru_fifo + g_fifo_write_index )->uc_phase_index = 
		  p_data->uc_phase_index ;

     ( g_p_stru_fifo + g_fifo_write_index )->uc_bit_index = 
		  p_data->uc_bit_index ; 

     ( g_p_stru_fifo + g_fifo_write_index )->uc_frame_index = 
		  p_data->uc_frame_index ; 
   ////////////////
   //fifoдָ�����
   g_fifo_write_index ++ ;
   //���дָ�뵽��������Ƶ���һ����Ԫ
   if( g_fifo_write_index >= g_fifo_len_struct )
   {
	   g_fifo_write_index = 0 ;
   }
   //���¶�Ӧ��Ԫ�Ķ�д��־ 
   ///////////////
   ( g_p_stru_fifo + g_fifo_write_index )->uc_rw_flag = _FIFO_READ_ENABLE ;	
  }//not overflow
 }//len
 return  1 ;
 
}


//************************************
// Method:    Fun_Fifo_Pop_Up
// FullName:  Fun_Fifo_Pop_Up
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: stru_Pro_Decode_Data_One_Bit * p_data
// Parameter: unsigned int len
//************************************
int   Fun_Fifo_Pop_Up(  stru_Pro_Decode_Data_One_Bit  * p_data  , unsigned int len )
{
	unsigned  int i , k ;
	
	for( k = 0 ; k < len ; k ++ )
	{//len
	  if( ( g_p_stru_fifo + g_fifo_read_index )->uc_rw_flag == _FIFO_WRITE_ENABLE )

		 return  _FIFO_EMPTY ;
	  else
	  { //not empty 
		//��ȡ8ci ��320�����ݵ���Ӧ����λ��
		for( i = 0 ; i < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; i ++ )
		{
			( g_p_stru_fifo + g_fifo_read_index )->stru_data_one_bit.trig_point0 [ i ] =
				p_data->stru_data_one_bit.trig_point0[ i ] ;
			
			( g_p_stru_fifo + g_fifo_read_index )->stru_data_one_bit.trig_point1 [ i ] =
				p_data->stru_data_one_bit.trig_point1[ i ] ;
			
			( g_p_stru_fifo + g_fifo_read_index )->stru_data_one_bit.trig_point2 [ i ] =
				p_data->stru_data_one_bit.trig_point2[ i ] ;
			
			( g_p_stru_fifo + g_fifo_read_index )->stru_data_one_bit.trig_point3 [ i ] =
				p_data->stru_data_one_bit.trig_point3[ i ] ;
			
			( g_p_stru_fifo + g_fifo_read_index )->stru_data_one_bit.trig_point4 [ i ] =
				p_data->stru_data_one_bit.trig_point4[ i ] ;
			
			( g_p_stru_fifo + g_fifo_read_index )->stru_data_one_bit.trig_point5 [ i ] =
				p_data->stru_data_one_bit.trig_point5[ i ] ;
			
			( g_p_stru_fifo + g_fifo_read_index )->stru_data_one_bit.trig_point6 [ i ] =
				p_data->stru_data_one_bit.trig_point6[ i ] ;
			
			( g_p_stru_fifo + g_fifo_read_index )->stru_data_one_bit.trig_point7 [ i ] =
				p_data->stru_data_one_bit.trig_point7[ i ] ;
		}//one bit	

			/////////////////////
			( g_p_stru_fifo + g_fifo_read_index )->uc_line_index = 
				p_data->uc_line_index ;

			( g_p_stru_fifo + g_fifo_read_index )->uc_phase_index = 
				p_data->uc_phase_index ;

			
			( g_p_stru_fifo + g_fifo_read_index )->uc_bit_index = 
				p_data->uc_bit_index ; 

			( g_p_stru_fifo + g_fifo_read_index )->uc_frame_index = 
		        p_data->uc_frame_index ; 
			
		////////////////
		//fifoдָ�����
		g_fifo_read_index ++ ;
		//���дָ�뵽��������Ƶ���һ����Ԫ
		if( g_fifo_read_index >= g_fifo_len_struct )
		{
			g_fifo_read_index = 0 ;
		}
		//���¶�Ӧ��Ԫ�Ķ�д��־ 
		///////////////
		( g_p_stru_fifo + g_fifo_read_index )->uc_rw_flag = _FIFO_WRITE_ENABLE ;
	  }//else not empty 
	}//len
 return  1 ;	
}

void    Fun_Fifo_Delete( )
{
	delete [ ]  g_p_stru_fifo ;
}







