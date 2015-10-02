void abc(int i)
{	
	int a = 0 ;
	for (i = 0 ; i < 10 ; i++)
		a++ ;
	int j = 0 , k = 0,l,m;
	for (i = 0 ; i < 10 ; i++)
		for(j = 0 ; j < 10 ; j++)
			for(k = 0 ; k < 10 ; k++)
				a++ ;
	i = 0 , j =0 , k = 0 ;
	for (i = 0 ; i < 10 ; i++)
		for(j = 0 ; j < 10 ; j++)
			for(k = 0 ; k < 10 ; k++)
				for (l = 0 ; l < 10 ; l++)
					for (m = 0 ; m < 10 ; m++)
						a++ ;
	while (i < 10)
	{
		while (j < 10)
		{	while (k < 10)
			{
				a++;
				k++;
			}
			j++ ;
		}
		i++;
	}
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
			for(k = 0 ; k < 10 ; k++)
				a++ ;
	int b ;
	for (i = 0 ; i < 10 ; i++)
	{
		b = a ;
		for(j = 0 ; j < 10 ; j++)
			for(k = 0 ; k < 10 ; k++)
				for (l = 0 ; l < 10 ; l++)
					for (m = 0 ; m < 10 ; m++)
						a++ ;
	}
	return 0 ;
}