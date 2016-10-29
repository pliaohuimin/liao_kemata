#include "ketama.h"
#include <stdio.h>
#include <string.h>

t_node_info node_list[12];
int init_node()                                                                                                           
{ 
	for ( int ii = 0; ii < 12; ii++ )                       
	{
int jj = ii+1;
//if ( ii >= 2 )
//	jj++;
		snprintf( node_list[ii].data, 22, "data%d", jj );    
		node_list[ii].weight = 1;
//		printf( "node_index:%d, data:%s\n", ii, node_list[ii].data ); 
	}
	return 0;                                                
}

int main( int argc, char* argv[] )
{
	init_node();
	ketama_create_continuum(node_list, 12);

	int statics[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
	for ( int ii = 0; ii < 1000000; ii++ )
	{
		char key[20];
		sprintf( key, "%d", ii );
		t_mcs *server = ketama_get_node(key);
		//printf( "data:%s.point:%u\n", server->data, server->point );
		printf( "i:%d,data:%s\n", ii, server->data );
		if ( strlen(server->data) == 5 && strcmp( server->data, "data1" )==0 )
			statics[0]++;
		else if ( strlen(server->data) == 5 && strcmp( server->data, "data2" )==0 )
			statics[1]++;
		else if ( strlen(server->data) == 5 && strcmp( server->data, "data3" )==0 )
			statics[2]++;
		else if ( strlen(server->data) == 5 && strcmp( server->data, "data4" )==0 )
			statics[3]++;
		else if ( strlen(server->data) == 5 && strcmp( server->data, "data5" )==0 )
			statics[4]++;
		else if ( strlen(server->data) == 5 && strcmp( server->data, "data6" )==0 )
			statics[5]++;
		else if ( strlen(server->data) == 5 && strcmp( server->data, "data7" )==0 )
			statics[6]++;
		else if ( strlen(server->data) == 5 && strcmp( server->data, "data8" )==0 )
			statics[7]++;
		else if ( strlen(server->data) == 5 && strcmp( server->data, "data9" )==0 )
			statics[8]++;
		else if ( strlen(server->data) == 6 && strcmp( server->data, "data10" )==0 )
			statics[9]++;
		else if ( strlen(server->data) == 6 && strcmp( server->data, "data11" )==0 )
			statics[10]++;
		else if ( strlen(server->data) == 6 && strcmp( server->data, "data12" )==0 )
			statics[11]++;
	}
	int all = 0;
	for ( int ii = 0; ii < 12; ii++ )
	{
//		printf( "data%d:%d\n", ii+1,  statics[ii] );
		all += statics[ii];
	}
//	printf( "all:%d\n", all );
	return 0;
}

