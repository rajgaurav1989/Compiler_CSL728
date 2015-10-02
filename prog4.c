void abc(int i)
{	
	int a = 0 ;
	for (i = 0 ; i < 10 ; i++)
		a++ ;
	
}

int main()
{
	int i , j ,k = 0 ,a = 0 ,l , m;
	for (i = 0 ; i < 10 ; i++)
		for (j = 0 ; j < 10 ; j++)
			k++ ;

	for (i = 0 ; i < 10 ; i++) 
		k++ ;
	abc(k) ;
	for (i = 0 ; i < 10 ; i++)
		for(j = 0 ; j < 10 ; j++)
			a++;
	return 0 ;
}
dfdgdS