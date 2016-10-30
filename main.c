#include "ketama.h"
#include <stdio.h>
#include <string.h>

// node_info, weight
t_node_info node_list[11] = 
{
{ "data1", 1 },
{ "data2", 1 },
//{ "data3", 1 },
{ "data4", 1 },
{ "data5", 1 },
{ "data6", 1 },
{ "data7", 1 },
{ "data8", 1 },
{ "data9", 1 },
{ "data10", 1 },
{ "data11", 1 },
{ "data12", 1 }
};

int statics[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

int init_node()                                                                                                           
{ 
	for ( int ii = 0; ii < 12; ii++ )                       
	{
		int jj = ii+1;
		snprintf( node_list[ii].data, 22, "data%d", jj );    
		node_list[ii].weight = 1;
//		printf( "node_index:%d, data:%s\n", ii, node_list[ii].data ); 
	}
	return 0;                                                
}

void add2static(char *data)
{
	if ( strlen(data) == 5 && strcmp( data, "data1" )==0 )
		statics[0]++;
	else if ( strlen(data) == 5 && strcmp( data, "data2" )==0 )
		statics[1]++;
	else if ( strlen(data) == 5 && strcmp( data, "data3" )==0 )
		statics[2]++;
	else if ( strlen(data) == 5 && strcmp( data, "data4" )==0 )
		statics[3]++;
	else if ( strlen(data) == 5 && strcmp( data, "data5" )==0 )
		statics[4]++;
	else if ( strlen(data) == 5 && strcmp( data, "data6" )==0 )
		statics[5]++;
	else if ( strlen(data) == 5 && strcmp( data, "data7" )==0 )
		statics[6]++;
	else if ( strlen(data) == 5 && strcmp( data, "data8" )==0 )
		statics[7]++;
	else if ( strlen(data) == 5 && strcmp( data, "data9" )==0 )
		statics[8]++;
	else if ( strlen(data) == 6 && strcmp( data, "data10" )==0 )
		statics[9]++;
	else if ( strlen(data) == 6 && strcmp( data, "data11" )==0 )
		statics[10]++;
	else if ( strlen(data) == 6 && strcmp( data, "data12" )==0 )
		statics[11]++;
}

void showStatics()
{
	int all = 0;
	for ( int ii = 0; ii < 12; ii++ )
	{
		printf( "data%d:%d\n", ii+1,  statics[ii] );
		all += statics[ii];
	}
	printf( "all:%d\n", all );
}

int main( int argc, char* argv[] )
{
	t_continuum continuum;
//	init_node();
	unsigned node_num = sizeof(node_list)/sizeof(t_node_info);
	ketama_create_continuum(&continuum, node_list, node_num);

	for ( int ii = 0; ii < 1000000; ii++ )
	{
		char key[20];
		sprintf( key, "%d", ii );
		t_mcs *server = ketama_get_node(&continuum, key);
//		printf( "i:%d,data:%s,point:%u\n", ii, server->data, server->point );
		add2static(server->data);
	}
	showStatics();
	return 0;
}

