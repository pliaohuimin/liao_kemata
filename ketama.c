#include <openssl/md5.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "ketama.h"

int ketama_create_continuum(const t_node_info *node_info, const unsigned node_num)
{
	if ( node_info == NULL || node_num == 0 ) 
	{
		return 0;
	}

	total_counts = node_num*count_base;
	t_mcs tmpContinuum[total_counts];
	int total_weight = 0;
	unsigned cont = 0;
	for ( unsigned ii = 0; ii < node_num; ii++ )
	{
		total_weight += node_info[ii].weight;
	}
	for ( unsigned ii = 0; ii < node_num; ii++ )
	{
		float pct = (float)node_info[ii].weight / (float)total_weight;
		unsigned int node_count = floorf( pct * 40.0 * (float)node_num );
		for ( unsigned kk = 0; kk < node_count; kk++ )
		{
			char key[30];
			unsigned char digest[16];
			sprintf( key, "%s-%d", node_info[ii].data, kk );
			ketama_md5(key,digest);

			for( int jj = 0; jj < 4; jj++ )
			{
				tmpContinuum[cont].point = ( digest[3+jj*4] << 24 )
					| ( digest[2+jj*4] << 16 )
					| ( digest[1+jj*4] <<  8 )
					|   digest[jj*4];

				memcpy( tmpContinuum[cont].data, node_info[ii].data, 22 );
				cont++;
			}
		}
	}

	qsort( (void*) &tmpContinuum, cont, sizeof( t_mcs ), (compfn)ketama_compare );

	tContinuum = malloc( sizeof( t_mcs )*node_num*count_base );
	memcpy(tContinuum, &tmpContinuum, sizeof( t_mcs ) * total_counts );
	return 1;
}

int ketama_compare( t_mcs *a, t_mcs *b )
{
	return ( a->point < b->point ) ?  -1 : ( ( a->point > b->point ) ? 1 : 0 );
}

t_mcs* ketama_get_node( char* key)
{
	unsigned int h = ketama_hashi(key);
	int highp = total_counts;
	int lowp = 0, midp;
	unsigned int midval, midval1;

	while ( 1 )
	{
		midp = (int)( ( lowp+highp ) / 2 );

		if ( midp == total_counts )
			return &( tContinuum[0] ); // if at the end, roll back to zeroth

		midval = tContinuum[midp].point;
		midval1 = midp == 0 ? 0 : tContinuum[midp-1].point;

		if ( h <= midval && h > midval1 )
			return &( tContinuum[midp] );

		if ( midval < h )
			lowp = midp + 1;
		else
			highp = midp - 1;

		if ( lowp > highp )
			return &( tContinuum[0] );
	}
}

unsigned int ketama_hashi( char* inString )
{
	unsigned char digest[16];
	ketama_md5( inString, digest );
	return (unsigned int)(( digest[3] << 24 )
			| ( digest[2] << 16 )
			| ( digest[1] <<  8 )
			|   digest[0] );
}

void ketama_md5(const char* key, unsigned char *digest)
{
	MD5_CTX context;
	MD5_Init( &context );
	MD5_Update( &context, key, strlen(key) );
	MD5_Final( digest, &context );
}
