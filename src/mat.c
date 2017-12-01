// ===== INITIALIZATION =====

//new empty matrix MxN
extern gsl_matrix * m_new(uint32_t m, uint32_t n)
{
	gsl_matrix *ma = gsl_matrix_alloc(m,n);
	gsl_matrix_set_zero(ma);
	return ma;
}

//new diag matrix MxM
extern gsl_matrix * m_new_diag(uint32_t m)
{
	uint8_t i;
	gsl_matrix *ma = gsl_matrix_alloc(m,m);
	gsl_matrix_set_zero(ma);
	for(i=0;i<m;i++)
	{
		gsl_matrix_set(ma,i,i,1.0f);
	}
	return ma;
}

// ===== GLM LIKE FUNCS =====

//glm.perspective
extern void glmPerspective(double fovy, double aspect, double zNear, double zFar, gsl_matrix *R)
{
	float tanHalfFovy = tan(fovy/2);

	gsl_matrix_set(R,0,0,(double)1/aspect*tanHalfFovy);
	gsl_matrix_set(R,1,1,(double)1/tanHalfFovy);
	gsl_matrix_set(R,2,3,(double)1);
	gsl_matrix_set(R,2,2,zFar/(zNear-zFar));
	gsl_matrix_set(R,3,2,-(zFar + zNear)/(zFar-zNear));
}

//glm.lookAt
extern void glmLookAt(void);
//+normalize [x]
//+cross [x]
//+dot [x]
//+getVectorLength [x]

// ===== TRANSFORMATION =====

//set translation coefs based on XYZ vector, opt transponse
extern void m_setT(gsl_matrix *m, double v1, double v2, double v3, uint8_t t)
{
	gsl_matrix_set(m,0,3,v1);
	gsl_matrix_set(m,1,3,v2);
	gsl_matrix_set(m,2,3,v3);
	if(t) gsl_matrix_transpose(m);
	return;
}

//set rotation by Y coefs based on DEG, opt transponse
extern void m_setRy(gsl_matrix *m, double deg, uint8_t t)
{
	gsl_matrix_set(m,0,0,ZEROCHK(cos(RAD(deg))));
	gsl_matrix_set(m,0,2,ZEROCHK(sin(RAD(deg))));
	gsl_matrix_set(m,2,0,ZEROCHK(-sin(RAD(deg))));
	gsl_matrix_set(m,2,2,ZEROCHK(cos(RAD(deg))));
	if(t) gsl_matrix_transpose(m);
	return;
}

// ===== OPERATIONS =====

//multiply matrices m1,m2, store result inro R
extern void m_mul(gsl_matrix *m1, gsl_matrix *m2, gsl_matrix *R)
{
	gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, m1, m2, 0.0, R);
	return;
}

//export matrix from gsl_matrix struct as double array
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

//get single vector length Xd
extern float getVectorLength(double *vec, uint8_t size)
{
	uint32_t sum = 0;
	int8_t i;
	for(i=0;i<size;i++)
	{
		sum += (uint32_t)vec[i]*(uint32_t)vec[i];
	}
	return (float)sqrt(sum);
}


//normalize single vector Xd
extern void normalize(double *vec, uint8_t size, double *r)
{
	uint8_t i;
	float len;

	r = (double *)malloc(sizeof(double)*size);
	len = getVectorLength(vec, size);

	for(i=0;i<size;i++)
	{
		r[i] = vec[i]/len;
		printf("%f\n",r[i]);
	}

	return;
}

//"dot": scalar product of 2 Xd vectors
extern uint32_t scalar(double *vec1, double *vec2, uint8_t size)
{
	uint8_t i;
	uint32_t sum = 0;

	for(i=0;i<size;i++)
	{
		sum += vec1[i]*vec2[i];
	}
	return sum;
}

//get cross of two 3d vectors
extern void getCrossV3(double *vec1, double *vec2, double *r)
{
	r = (double *)malloc(sizeof(double)*3);
	r[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	r[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	r[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
	return;
}

// ===== DEBUG =====

//printf MxN matrix (debug)
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
