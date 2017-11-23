//new diag matrix MxN
extern gsl_matrix * m_new_diag(uint32_t m, uint32_t n)
{
	gsl_matrix *ma = gsl_matrix_alloc(m,n);
	gsl_matrix_set_zero(ma);
	gsl_matrix_set(ma,0,0,1.0f);
	gsl_matrix_set(ma,1,1,1.0f);
	gsl_matrix_set(ma,2,2,1.0f);	
	gsl_matrix_set(ma,3,3,1.0f);
	return ma;
}

//new empty matrix MxN
extern gsl_matrix * m_new(uint32_t m, uint32_t n)
{
	gsl_matrix *ma = gsl_matrix_alloc(m,n);
	gsl_matrix_set_zero(ma);
	return ma;
}

//set T coef, use array
extern void m_setT(gsl_matrix *m, double v1, double v2, double v3, uint8_t t)
{
	gsl_matrix_set(m,0,3,v1);
	gsl_matrix_set(m,1,3,v2);
	gsl_matrix_set(m,2,3,v3);
	if(t) gsl_matrix_transpose(m);
	return;
}

//set Ry coef, use array
extern void m_setRy(gsl_matrix *m, double deg, uint8_t t)
{
	gsl_matrix_set(m,0,0,ZEROCHK(cos(RAD(deg))));
	gsl_matrix_set(m,0,2,ZEROCHK(sin(RAD(deg))));
	gsl_matrix_set(m,2,0,ZEROCHK(-sin(RAD(deg))));
	gsl_matrix_set(m,2,2,ZEROCHK(cos(RAD(deg))));
	if(t) gsl_matrix_transpose(m);
	return;
}

//multiply matrices m1,m2, store result inro R
extern void m_mul(gsl_matrix *m1, gsl_matrix *m2, gsl_matrix *R)
{
	gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, m1, m2, 0.0, R);
	return;
}

//printf MxN matrix
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

//export from matrix struct into double arr
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