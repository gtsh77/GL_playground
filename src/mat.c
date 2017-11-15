extern gsl_matrix * m_init(uint32_t m, uint32_t n)
{
	gsl_matrix *ma = gsl_matrix_alloc(m,n);
	gsl_matrix_set_zero(ma);
	return ma;
}

extern void m_translate(gsl_matrix *m, double *vec3)
{
	gsl_matrix_set(m,0,0,vec3[0]);
	gsl_matrix_set(m,1,1,vec3[1]);
	gsl_matrix_set(m,2,2,vec3[2]);
	return;
}

extern void m_rotate_y(gsl_matrix *m, double deg)
{
	gsl_matrix_set(m,0,0,cos(RAD(deg)));
	gsl_matrix_set(m,0,2,sin(RAD(deg)));
	gsl_matrix_set(m,2,0,-sin(RAD(deg)));
	gsl_matrix_set(m,2,2,cos(RAD(deg)));
}

extern void m_mul(gsl_matrix *m1, gsl_matrix *m2)
{
	gsl_matrix_mul_elements (m1, m2);
}

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

extern double * m_array(gsl_matrix *ma, uint8_t m, uint8_t n)
{
	uint8_t i,j;
	double *array;
	array = (double *)malloc(m*n*sizeof(double));
	for(i=0;i<n;i++)
	{
		printf("\n");
		for(j=0;j<m;j++)
		{
			array[i*m+j] = gsl_matrix_get(ma,i,j);
		}
	}
	return array;
}