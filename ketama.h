static const int count_base = 160;
typedef int (*compfn)( const void*, const void* ); 

typedef struct struct_node_info
{       
	char data[22];
	unsigned long weight;
} t_node_info;

typedef struct
{
	unsigned int point;  // point on circle
	char data[22];
} t_mcs;

t_mcs *tContinuum;
static int total_counts = 0;

int ketama_create_continuum(const t_node_info *node_info, const unsigned node_num);

int ketama_compare( t_mcs *a, t_mcs *b );
unsigned int ketama_hashi( char* inString );
t_mcs* ketama_get_node( char* key);
void ketama_md5(const char* in, unsigned char *digest);
unsigned int ketama_hashi( char* inString );
