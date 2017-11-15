extern gsl_matrix * m4init(void)
{
	gsl_matrix *m = gsl_matrix_alloc(4,4);
	gsl_matrix_set_zero(m);
	return m;
}

extern void m_translate(gsl_matrix *m, double *vec3)
{
	gsl_matrix_set(m,0,0,vec3[0]);
	gsl_matrix_set(m,1,1,vec3[1]);
	gsl_matrix_set(m,2,2,vec3[2]);
	return;
}

// extern void m_rotate_y(gsl_matrix *m)
// {

// }

extern void m_print(gsl_matrix *ma, uint8_t m, uint8_t n)
{
	uint8_t i,j;
	for(i=0;i<n;i++)
	{
		printf("\n");
		for(j=0;j<m;j++)
		{
			printf("%.12f  ",gsl_matrix_get(ma,i,j));
		}
	}
	return;
}